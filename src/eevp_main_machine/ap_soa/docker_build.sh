#!/bin/bash

GEN_DIR="adaptive_autosar"
GEN_URL="ssh://git@bitbucket.mobis.co.kr:7999/eevp_mb/adaptive_autosar.git"
BUILD_DIR="build"
THIS_DIR=$(dirname "$(readlink -f "${0}")")
THIS_CMD=$(basename "$(readlink -f "${0}")")
PARA_SDK="/home/popcornsar/work/para-sdk"
CLEAN=false
BUILD_PARA_ROOT=false
ENABLE_TEST=OFF
IP_ADDRESS=""
SDK_PATH="/opt/distro-mobis-eevpmb/4.0.12"
BUILD_WITH_SDK=false
PARA_CORE="/tmp/para-root"
PARA_CONF="${PARA_CORE}/etc"
PARA_DATA="${PARA_CORE}/var"
PARA_APPL="${PARA_CORE}/opt"

function help() {
    echo "${THIS_CMD} [options]"
    echo "  --use-sdk [path]: sdk build(might be /opt/distro-mobis-eevpmb/4.0.12)"
    echo "  -t|--test : enable gtest"
    echo "  -c|--cean : clean install/build"
    echo "  -p|--para-root : build PARA_ROOT"
    echo "  --ip-address [IP]: ip-address"
}

function build_para_root() {
    local para_core="${1}"
    local para_conf="${2}"
    local para_data="${3}"
    local para_appl="${4}"
    local ip_address="${5}"

    # create default directory
    for dir in "${para_core}/bin" "${para_conf}" "${para_data}" "${para_appl}"; do
        mkdir -p "${dir}"
    done

    local binaries=("CM" "EM" "PHM" "dlt-daemon" "iox-roudi")

    for bin in "${binaries[@]}"; do
        cp "${PARA_SDK}"/bin/"${bin}" "${para_core}"/bin/
    done

    cp "${PARA_SDK}"/etc/* "${para_conf}"/
    cp "${THIS_DIR:?}"/"${GEN_DIR}"/config/dlt/dlt.conf "${para_conf}"/dlt.conf
    cp "${THIS_DIR:?}"/"${GEN_DIR}"/config/dlt/dlt_logstorage.conf "${para_data}"/dlt_logstorage.conf
    # change /appdata to $para_data in dlt.conf
    sed -i "s#/appdata#${para_data}#g" "${para_conf}"/dlt.conf

    GEN_BASE="${THIS_DIR:?}/${GEN_DIR}/gen/gen_ara/implementation/EEVP_Main_Machine"
    local manifests=("CM" "EM" "PHM")

    for fc in "${manifests[@]}"; do
        cp -r "${GEN_BASE}"/"${fc}"/manifest/* "${para_conf}"/
    done

    for fc in "UCM" "VUCM"; do
        if [ ${fc} == "UCM" ]; then
            mkdir -p "${para_appl}"/${fc}/etc
        fi
        cp "${PARA_SDK}"/opt/${fc}/bin/${fc} "${para_core}"/bin/${fc}

        cp -r "${GEN_BASE}"/"${fc}"/manifest/exec/* "${para_conf}"/exec/
        cp -r "${GEN_BASE}"/"${fc}"/manifest/interface/* "${para_conf}"/interface/
        if [ ${fc} == "UCM" ]; then
            cp -r "${GEN_BASE}"/"${fc}"/manifest/ucm "${para_appl}"/${fc}/etc/
        fi
    done

    # update ip address
    if [ -z "${ip_address}" ]; then
        ip_list=$(ifconfig eth0 | sed -n 's/.*inet \([0-9.]*\) .*/\1/p')

        if [ "${#ip_list[@]}" -ne 1  ]; then
            echo "check ifconfig eth0 : ${ip_list}"
        else
            ip_address=${ip_list[0]}
            echo "Your Device's IP is ${ip_address} for Docker"
        fi
    fi

    if [ -n "${ip_address}" ]; then
        for f in "${para_conf}"/com/*.json; do
            echo "Update IP of ${f} to ${ip_address}"
            sed -i 's/"unicast-address" : ".*"/"unicast-address" : "'"${ip_address}"'"/' "${f}"
        done

        f="${para_conf}/machine/EEVP_Main_Machine.json"
        echo "Update IP of ${f} to ${ip_address}"
        sed -i '/"endpoints" : \[/,/],/ s/"ip-address" : ".*"/"ip-address" : "'"${ip_address}"'"/' "${f}"
    fi
}

while [ ${#} -gt 0 ]; do

    case "${1}" in
        -t | --test)
            ENABLE_TEST=OK
            ;;
        -c | --clean)
            CLEAN=true
            ;;
        -p | --para-root)
            BUILD_PARA_ROOT=true
            ;;
        --use-sdk)
            BUILD_WITH_SDK=true
            shift
            SDK_PATH="${1}"
            ;;
        --ip-address)
            shift
            IP_ADDRESS="${1}"
            ;;
        *)
            help
            exit 1
    esac

    shift
done

if ${BUILD_WITH_SDK}; then
    if [ ! -d "${SDK_PATH}" ]; then
        echo "Invalid SDK Path : ${SDK_PATH}"
        exit
    fi
    PARA_SDK="${SDK_PATH}/sysroots/cortexa53-crypto-poky-linux/usr"
fi

if [ ! -d "${THIS_DIR:?}/${GEN_DIR}" ]; then
    echo "You need to clone ${GEN_URL} outside of docker because of id"
    exit
fi

if ${CLEAN}; then
    rm -rf "${THIS_DIR:?}/${BUILD_DIR}" > /dev/null 2>&1
    rm -rf "${PARA_CORE}" > /dev/null 2>&1
fi

if [ ! -d "${THIS_DIR:?}/${BUILD_DIR}" ]; then
    if ! mkdir "${THIS_DIR:?}/${BUILD_DIR}"; then
        exit 1
    fi
fi

if ! cmake -DCMAKE_INSTALL_PREFIX="${PARA_CORE}" \
      -DPARA_SDK="${PARA_SDK}" \
      -DBUILD_IN_DOCKER=ON \
      -DGEN_DIR="${THIS_DIR:?}/${GEN_DIR}" \
      -DENABLE_TEST=${ENABLE_TEST} \
    -S "${THIS_DIR}" -B "${THIS_DIR}/${BUILD_DIR}"; then
    echo "Failed to cmake"
    exit 1
fi

if ! make --directory="${THIS_DIR}/${BUILD_DIR}" -j32 install; then
    echo "Failed to build"
    exit
fi

if ${BUILD_PARA_ROOT} && ! ${BUILD_WITH_SDK}; then
    if mkdir -p "${PARA_CORE}"; then
        build_para_root "${PARA_CORE}" "${PARA_CONF}" "${PARA_DATA}" "${PARA_APPL}" \
                        "${IP_ADDRESS}"
    fi

    echo "======== Check the environment variables before run VDI ========"
    echo "export PARA_CORE=${PARA_CORE}"
    echo "export PARA_CONF=${PARA_CORE}/etc"
    echo "export PARA_DATA=${PARA_CORE}/var"
    echo "export PARA_APPL=${PARA_CORE}/opt"
    echo "======================================================================="
fi

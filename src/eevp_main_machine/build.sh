#!/bin/sh
#
# 모듈 빌드 스크립트 (POSIX sh 버전)
# - modules 변수 안에서 모듈명|인자 형식으로 정의
# - 인자가 없으면 '|' 뒤를 비워두면 됨
# - 모듈 제외하려면 해당 줄 맨 앞에 '#' 붙이면 됨
# - 모듈 추가/삭제는 modules 변수 내용만 수정하면 됨
#

modules="
ap_sm|-c -p
ap_ipchandler|
ap_soa_wiper|
ap_intelligent_wiper|
"

echo "$modules" | while IFS="|" read -r dir args; do
    # 빈 줄 또는 주석(#)은 건너뛰기
    [ -z "$dir" ] && continue
    case "$dir" in
        \#*) continue ;;  # 주석 처리된 모듈 스킵
    esac

    echo ">> Building $dir"
    bash "$PWD/$dir/docker_build.sh" $args
done


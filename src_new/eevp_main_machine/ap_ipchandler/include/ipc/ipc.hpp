/* Copyright 2024 Hyundai Mobis Co., Ltd. All rights reserved */

#ifndef IPC_H
#define IPC_H

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 4)

struct __attribute__((aligned(8))) CpInfo
{
    std::uint8_t system_ctrl_req;
    std::uint8_t brand;
    char vehicle[3];
    std::uint8_t region;
    std::uint8_t ecotype;
    std::uint8_t driverside;
    std::uint8_t mild_48v;
    std::uint8_t connectivity;
    char part_no[10];
    char supplier_code[4];
    char manufact_date[4];
    char serial_no[10];
    char hw_version[3];     // FIXME : need to discuss with 이은별, request to change UINT to ascii
    char mcu_sw_version[5];
    char eth_db_version[6];
    char can_db_version[6];
    char oem_sw_version[3];
    char oem_hw_version[3];
    std::uint16_t vbat_level;
    std::uint8_t acc;
    std::uint8_t ign1;
    std::uint8_t ign3;
    std::uint16_t acc_cnt;
    std::uint16_t ign1_cnt;
    std::uint16_t ign3_cnt;
    std::uint64_t acc_on_time;
    std::uint64_t ign1_on_time;
    std::uint64_t ign3_on_time;
    std::uint16_t boot_cycle_cnt;
    std::uint8_t ert_act;
    std::uint8_t dcu_wk;
    std::uint8_t ccic_wk;
    std::uint8_t bltn_cam_wk;
    std::uint8_t bus_load_hsb1;
    std::uint8_t bus_load_hsb2;
    std::uint8_t bus_load_hsm;
    std::uint8_t bus_load_fdp1;
    std::uint8_t bus_load_fdp2;
    std::uint8_t bus_load_fdc;
    std::uint8_t bus_load_fde;
    std::uint8_t bus_load_hsi;
    std::uint8_t bus_load_hsd;
    std::uint8_t bus_status_hsb1;
    std::uint8_t bus_status_hsb2;
    std::uint8_t bus_status_hsm;
    std::uint8_t bus_status_fdp1;
    std::uint8_t bus_status_fdp2;
    std::uint8_t bus_status_fdc;
    std::uint8_t bus_status_fde;
    std::uint8_t bus_status_hsi;
    std::uint8_t bus_status_hsd;
    std::uint8_t current_time_mode;
    std::uint64_t current_time_offset;
    std::int16_t current_utc_offset;
    std::uint32_t mcu_boot_reason;
};

struct __attribute__((aligned(8))) ApInfo
{
    std::uint8_t system_ctrl_resp;
    std::uint8_t ap_sw_version[5];
    std::uint8_t esw_sw_version[5];
    std::uint8_t hwire_req_dcu_rst;
    std::uint8_t hwire_req_icu_wk;
    std::uint8_t hwire_req_esw_rst;
    std::uint8_t hwire_req_dcu_phy_rst;
    std::uint8_t hwire_req_hu_phy_rst;
    std::uint8_t hwire_req_esw_wk;
    std::uint8_t hwire_req_dcu_phy_wk;
    std::uint8_t hwire_req_hu_phy_wk;
    std::uint8_t asm_request;
    std::uint16_t gmac0_status[3];
    std::uint16_t pfe_mac0_status[3];
    std::uint16_t pfe_mac1_status[3];
    std::uint16_t pfe_mac2_status[3];
    std::uint32_t pnc_status[7];        // every 1s
    std::uint8_t crank_inhibit_command; // every 1s
    std::uint8_t stmin_status[32];      // every 1s
};

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#ifdef ENABLE_IPC_SHM
#include <ipc-shm/ipc-a53i-cfg.h>
#include <ipc-shm/ipc-api.h>
#include <ipc-shm/ipc-typedef.h>
#else
typedef unsigned char ipc_return_t;
#define ipc_ret_ok 0
#endif

typedef void (*IPC_RxCallback) (void *buf, std::size_t size);
ipc_return_t IPCSendApInfo(const ApInfo *ap_info);
void RegisterIPCRxCallback(IPC_RxCallback callback);

#endif  // IPC_H

#include "../type.h"
#ifdef _MAC_TOP_H_
#include "../include/mac_top.h"
#else
#include "../mac_def.h"
#endif
#define DIAGNOSIS_DELAY 100
u32 diagnosis_PCIE_cfg_spc_multi_rule(struct mac_ax_adapter *adapter, u32 *check_number);
u32 diagnosis_PCIE_cfg_spc_HCI_PCIE(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_Beacon_TX_multi_rule(struct mac_ax_adapter *adapter, u32 *check_number);
u32 diagnosis_Beacon_TX_DMAC_STA_SCH(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_Beacon_TX_CMAC_PTCL(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_Beacon_TX_CMAC_SCH(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_multi_rule(struct mac_ax_adapter *adapter, u32 *check_number);
u32 diagnosis_TX_Hang_HAXIDMA_PCIE(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_HAXIDMA_USB(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_DMAC_Common(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_DMAC_Dispatcher(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_DMAC_STA_scheduler(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_CMAC_Common(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_CMAC_SCH(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_CMAC_PTCL(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_CMAC_TRXPTCL(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_TX_Hang_CMAC_RMAC(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_RX_Hang_HAXIDMA_PCIE(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_RX_Hang_HAXIDMA_USB(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_RX_Hang_DMAC_STA_scheduler(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_RX_Hang_CMAC_TRXPTCL(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_RX_Hang_CMAC_RMAC(struct mac_ax_adapter *adapter, u32 *checker_number);
u32 diagnosis_PCIE_cfg_spc(struct mac_ax_adapter *adapter, u32 *total_check_number);
u32 diagnosis_Beacon_TX(struct mac_ax_adapter *adapter, u32 *total_check_number);
u32 diagnosis_TX_Hang(struct mac_ax_adapter *adapter, u32 *total_check_number);
u32 diagnosis_RX_Hang(struct mac_ax_adapter *adapter, u32 *total_check_number);

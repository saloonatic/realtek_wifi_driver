#include "mac_priv.h"
#include "diagnosis.h"
u32 diagnosis_PCIE_cfg_spc_multi_rule(struct mac_ax_adapter *adapter, u32 *check_number)
{
#if MAC_AX_PCIE_SUPPORT
	struct mac_ax_priv_ops *p_ops = adapter_to_priv_ops(adapter);
	u32 ret = 0;
	u32 reg1 = 0, cnt = 0;
	u32 cnt1 = 0;
	*check_number = 0;

#ifdef PHL_FEATURE_NIC
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
		*check_number += 1;
		cnt = 0;
		ret = p_ops->read_pcie_cfg_spc(adapter, 0x80, &reg1);
		if ((reg1 & 0x1FF) != 0x142)
			cnt += 1;

		ret = p_ops->read_pcie_cfg_spc(adapter, 0x80, &reg1);
		if ((reg1 & 0x1FF) != 0x143)
			cnt += 1;

		if (cnt == 2) {
			ret = p_ops->read_pcie_cfg_spc(adapter, 0x80, &reg1);
			if ((reg1 & 0x1FF) != 0x142)
				PLTFM_MSG_ERR("Reg: 0x80 => %x, " \
					      "ASPM control not setting L1/CLKPM\n",
					      reg1);

			ret = p_ops->read_pcie_cfg_spc(adapter, 0x80, &reg1);
			if ((reg1 & 0x1FF) != 0x143)
				PLTFM_MSG_ERR("Reg: 0x80 => %x, " \
					      "ASPM control not setting L0s/L1/CLKPM\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#endif // AP/NIC Compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D))
		return cnt1;
	reg1 = 0;
	cnt = 0;
	p_ops = NULL;
	ret = 0;
#endif // End of Interface compile flag
	return MACSUCCESS;
}

u32 diagnosis_PCIE_cfg_spc_HCI_PCIE(struct mac_ax_adapter *adapter, u32 *check_number)
{
#if MAC_AX_PCIE_SUPPORT
	struct mac_ax_priv_ops *p_ops = adapter_to_priv_ops(adapter);
	u32 ret = 0;
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		ret = p_ops->read_pcie_cfg_spc(adapter, 0x4, &reg1);
		if ((reg1 & 0xF) != 0x7) {
			PLTFM_MSG_ERR("Reg: 0x4 => %x, " \
				      "Bus Master Error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		ret = p_ops->read_pcie_cfg_spc(adapter, 0x44, &reg1);
		if ((reg1 & 0x3) != 0) {
			PLTFM_MSG_ERR("Reg: 0x44 => %x, " \
				      "D-state not D0\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		ret = p_ops->read_pcie_cfg_spc(adapter, 0x94, &reg1);
		if ((reg1 & 0x800) != 0x800) {
			PLTFM_MSG_ERR("Reg: 0x94 => %x, " \
				      "no LTR Support\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#ifdef PHL_FEATURE_NIC
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		ret = p_ops->read_pcie_cfg_spc(adapter, 0x98, &reg1);
		if ((reg1 & 0x400) != 0x400) {
			PLTFM_MSG_ERR("Reg: 0x98 => %x, " \
				      "no LTR Enable\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#endif // AP/NIC Compile flag
#ifdef PHL_FEATURE_NIC
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852D_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
		*check_number += 1;
		ret = p_ops->read_pcie_cfg_spc(adapter, 0x168, &reg1);
		if ((reg1 & 0xF) != 0xF) {
			PLTFM_MSG_ERR("Reg: 0x168 => %x, " \
				      "not setting ASPM L1ss\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#endif // AP/NIC Compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		ret = p_ops->read_pcie_cfg_spc(adapter, 0x104, &reg1);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: 0x104 => %x, " \
				      "AER UNCORR_ERR_STS\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		ret = p_ops->read_pcie_cfg_spc(adapter, 0x110, &reg1);
		if ((reg1 & 0xFFFFDFFF) != 0) {
			PLTFM_MSG_ERR("Reg: 0x110 => %x, " \
				      "AER CORR_ERR_STS\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	p_ops = NULL;
	ret = 0;
#endif // End of Interface compile flag
	return MACSUCCESS;
}

u32 diagnosis_Beacon_TX_multi_rule(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	u32 cnt1 = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
		if ((reg1 & 0x2) != 0x2)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P0 => %x, " \
					      "MultiRule Port0 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P0 => %x, " \
					      "MultiRule Port0 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
			if ((reg1 & 0x2) != 0x2)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P0 => %x, " \
					      "MultiRule Port0 tx report is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
		if ((reg1 & 0x1000) != 0x1000)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P0 => %x, " \
					      "MultiRule Port0 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P0 => %x, " \
					      "MultiRule Port0 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P0);
			if ((reg1 & 0x1000) != 0x1000)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P0 => %x, " \
					      "MultiRule Port0 BCN tx is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
		if ((reg1 & 0x2) != 0x2)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P1 => %x, " \
					      "MultiRule Port1 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P1 => %x, " \
					      "MultiRule Port1 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
			if ((reg1 & 0x2) != 0x2)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P1 => %x, " \
					      "MultiRule Port1 tx report is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
		if ((reg1 & 0x1000) != 0x1000)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P1 => %x, " \
					      "MultiRule Port1 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P1 => %x, " \
					      "MultiRule Port1 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P1);
			if ((reg1 & 0x1000) != 0x1000)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P1 => %x, " \
					      "MultiRule Port1 BCN tx is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
		if ((reg1 & 0x2) != 0x2)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P2 => %x, " \
					      "MultiRule Port2 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P2 => %x, " \
					      "MultiRule Port2 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
			if ((reg1 & 0x2) != 0x2)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P2 => %x, " \
					      "MultiRule Port2 tx report is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
		if ((reg1 & 0x1000) != 0x1000)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P2 => %x, " \
					      "MultiRule Port2 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P2 => %x, " \
					      "MultiRule Port2 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P2);
			if ((reg1 & 0x1000) != 0x1000)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P2 => %x, " \
					      "MultiRule Port2 BCN tx is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
		if ((reg1 & 0x2) != 0x2)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P3 => %x, " \
					      "MultiRule Port3 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P3 => %x, " \
					      "MultiRule Port3 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
			if ((reg1 & 0x2) != 0x2)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P3 => %x, " \
					      "MultiRule Port3 tx report is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
		if ((reg1 & 0x1000) != 0x1000)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P3 => %x, " \
					      "MultiRule Port3 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P3 => %x, " \
					      "MultiRule Port3 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P3);
			if ((reg1 & 0x1000) != 0x1000)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P3 => %x, " \
					      "MultiRule Port3 BCN tx is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
		if ((reg1 & 0x2) != 0x2)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P4 => %x, " \
					      "MultiRule Port4 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P4 => %x, " \
					      "MultiRule Port4 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
			if ((reg1 & 0x2) != 0x2)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P4 => %x, " \
					      "MultiRule Port4 tx report is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
		if ((reg1 & 0xc00) == 0xc00)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
		if ((reg1 & 0x4) == 0x4)
			cnt += 1;

		reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
		if ((reg1 & 0x1000) != 0x1000)
			cnt += 1;

		if (cnt == 3) {
			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
			if ((reg1 & 0xc00) == 0xc00)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P4 => %x, " \
					      "MultiRule Port4 is AP\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
			if ((reg1 & 0x4) == 0x4)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P4 => %x, " \
					      "MultiRule Port4 is not enable\n",
					      reg1);

			reg1 = MAC_REG_R32(R_AX_PORT_CFG_P4);
			if ((reg1 & 0x1000) != 0x1000)
				PLTFM_MSG_ERR("Reg: R_AX_PORT_CFG_P4 => %x, " \
					      "MultiRule Port4 BCN tx is not enable\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt1;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_Beacon_TX_DMAC_STA_SCH(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_0);
		if ((reg1 & 0xffff) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_0 => %x, " \
				      "MACID is paused\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_Beacon_TX_CMAC_PTCL(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_BCNQ_CTRL);
		if ((reg1 & 0x1) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_BCNQ_CTRL => %x, " \
				      "BCN Queues is locked\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_Beacon_TX_CMAC_SCH(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CTN_TXEN);
		if ((reg1 & 0x1b00) != 0x1b00) {
			PLTFM_MSG_ERR("Reg: R_AX_CTN_TXEN => %x, " \
				      "BCN/HI/MGNQ Queue cannot contention\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_multi_rule(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	u32 cnt1 = 0;
	*check_number = 0;

#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_ACH0_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		MAC_REG_W32(R_AX_TX_PPDU_CNT, 2);
		reg1 = MAC_REG_R32(R_AX_TX_PPDU_CNT);
		PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
		reg2 = MAC_REG_R32(R_AX_TX_PPDU_CNT);
		if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000))
			cnt += 1;

		if (cnt == 2) {
			reg1 = MAC_REG_R32(R_AX_ACH0_PAGE_INFO_V1);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_AX_ACH0_PAGE_INFO_V1 => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			MAC_REG_W32(R_AX_TX_PPDU_CNT, 2);
			reg1 = MAC_REG_R32(R_AX_TX_PPDU_CNT);
			PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
			reg2 = MAC_REG_R32(R_AX_TX_PPDU_CNT);
			if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000))
				PLTFM_MSG_ERR("Reg: B0 TX_PPDU_CNT[2 OFDM] => %x, " \
					      "OFDM counter should be incremantal " \
					      "Otherwise Response TX may stuck\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_AX_ACH0_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		MAC_REG_W32(R_AX_TX_PPDU_CNT, 2);
		reg1 = MAC_REG_R32(R_AX_TX_PPDU_CNT);
		PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
		reg2 = MAC_REG_R32(R_AX_TX_PPDU_CNT);
		if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000))
			cnt += 1;

		if (cnt == 2) {
			reg1 = MAC_REG_R32(R_AX_ACH0_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_AX_ACH0_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			MAC_REG_W32(R_AX_TX_PPDU_CNT, 2);
			reg1 = MAC_REG_R32(R_AX_TX_PPDU_CNT);
			PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
			reg2 = MAC_REG_R32(R_AX_TX_PPDU_CNT);
			if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000))
				PLTFM_MSG_ERR("Reg: B0 TX_PPDU_CNT[2 OFDM] => %x, " \
					      "OFDM counter should be incremantal " \
					      "Otherwise Response TX may stuck\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		cnt = 0;
		reg1 = MAC_REG_R32(R_BE_CH0_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH1_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH2_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH3_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH4_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH5_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH6_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH7_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH8_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH9_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH10_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		reg1 = MAC_REG_R32(R_BE_CH11_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0)
			cnt += 1;

		MAC_REG_W32(R_BE_WMTX_PKTCNT, 2);
		reg1 = MAC_REG_R32(R_BE_WMTX_PKTCNT);
		PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
		reg2 = MAC_REG_R32(R_BE_WMTX_PKTCNT);
		if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000))
			cnt += 1;

		if (cnt == 13) {
			reg1 = MAC_REG_R32(R_BE_CH0_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH0_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH1_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH1_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH2_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH2_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH3_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH3_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH4_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH4_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH5_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH5_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH6_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH6_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH7_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH7_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH8_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH8_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH9_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH9_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH10_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH10_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			reg1 = MAC_REG_R32(R_BE_CH11_PAGE_INFO);
			if ((reg1 & 0x1FFF) != 0)
				PLTFM_MSG_ERR("Reg: R_BE_CH11_PAGE_INFO => %x, " \
					      "Used page for ACH0, no TX for consumption.\n",
					      reg1);

			MAC_REG_W32(R_BE_WMTX_PKTCNT, 2);
			reg1 = MAC_REG_R32(R_BE_WMTX_PKTCNT);
			PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
			reg2 = MAC_REG_R32(R_BE_WMTX_PKTCNT);
			if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000))
				PLTFM_MSG_ERR("Reg: B0 R_BE_WMTX_PKTCNT[2 OFDM] => %x, " \
					      "OFDM counter should be incremantal " \
					      "Otherwise Response TX may stuck\n",
					      reg1);

			cnt1 += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A))
		return cnt1;
	reg1 = 0;
	reg2 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_HAXIDMA_PCIE(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_HAXI_INIT_CFG1);
		if ((reg1 & 0x28080) != 0x8080) {
			PLTFM_MSG_ERR("Reg: R_AX_HAXI_INIT_CFG1 => %x, " \
				      "HAXIDMA Setting Error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_HAXI_DMA_STOP1);
		if ((reg1 & 0xFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_HAXI_DMA_STOP1 => %x, " \
				      "HAXIDMA Stop\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH1_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH1_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH1, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH1_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH1_PAGE_INFO => %x, " \
				      "Used page for ACH1, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH2_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH2_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH2, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH2_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH2_PAGE_INFO => %x, " \
				      "Used page for ACH2, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH3_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH3_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH3, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH3_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH3_PAGE_INFO => %x, " \
				      "Used page for ACH3, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH4_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH4_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH4, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH4_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH4_PAGE_INFO => %x, " \
				      "Used page for ACH4, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH5_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH5_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH5, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH5_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH5_PAGE_INFO => %x, " \
				      "Used page for ACH5, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH6_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH6_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH6, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH6_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH6_PAGE_INFO => %x, " \
				      "Used page for ACH6, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH7_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH7_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH7, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_ACH7_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_ACH7_PAGE_INFO => %x, " \
				      "Used page for ACH7, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH8_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH8_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH8, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH8_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH8_PAGE_INFO => %x, " \
				      "Used page for ACH8, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH9_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH9_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH9, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH9_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH9_PAGE_INFO => %x, " \
				      "Used page for ACH9, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH10_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH10_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH10, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH10_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH10_PAGE_INFO => %x, " \
				      "Used page for ACH10, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH11_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH11_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH11, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH11_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH11_PAGE_INFO => %x, " \
				      "Used page for ACH11, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH12_PAGE_INFO_V1);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH12_PAGE_INFO_V1 => %x, " \
				      "Used page for ACH12, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CH12_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CH12_PAGE_INFO => %x, " \
				      "Used page for ACH12, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_CH12_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_CH12_PAGE_INFO => %x, " \
				      "Used page for ACH12, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_CH12_15_PAGE_INFO);
		if ((reg1 & 0x1FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_CH12_15_PAGE_INFO => %x, " \
				      "Used page for ACH12, no TX for consumption.\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_DBG_ERR_FLAG_V1);
		if ((reg1 & 0x18) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_DBG_ERR_FLAG_V1 => %x, " \
				      "PCIE TRX Stuck event!\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_HAXIDMA_USB(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_USB_ENDPOINT_3);
		if ((reg1 & 0x7F8000) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_USB_ENDPOINT_3 => %x, " \
				      "TX EPs are paused\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_USB_ENDPOINT_3_V1);
		if ((reg1 & 0x7F8000) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_USB_ENDPOINT_3_V1 => %x, " \
				      "TX EPs are paused\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_USB_WLAN0_1);
		if ((reg1 & 0x100) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_USB_WLAN0_1 => %x, " \
				      "TX flush mode enabled\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_USB_WLAN0_1_V1);
		if ((reg1 & 0x100) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_USB_WLAN0_1_V1 => %x, " \
				      "TX flush mode enabled\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_DMAC_Common(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(0x8400);
		if ((reg1 & 0xFFFF0000) != 0xFFFF0000) {
			PLTFM_MSG_ERR("Reg: 0x8400 => %x, " \
				      "DMAC function enable setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(0x8404);
		if ((reg1 & 0xFFFF0000) != 0xF9F0000) {
			PLTFM_MSG_ERR("Reg: 0x8404 => %x, " \
				      "DMAC Clock enable setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT || \
MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(0x8400);
		if ((reg1 & 0xFFFF4000) != 0xFFFF4000) {
			PLTFM_MSG_ERR("Reg: 0x8400 => %x, " \
				      "DMAC function enable setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT || \
MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(0x8404);
		if ((reg1 & 0xF9F0000) != 0xF9F0000) {
			PLTFM_MSG_ERR("Reg: 0x8404 => %x, " \
				      "DMAC Clock enable setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_DMAC_ERR_ISR);
		if ((reg1 & 0x7FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_DMAC_ERR_ISR => %x, " \
				      "DMAC Error Indication\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_DMAC_ERR_ISR);
		if ((reg1 & 0x7FFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_DMAC_ERR_ISR => %x, " \
				      "DMAC Error Indication\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_DMAC_Dispatcher(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_DMAC_MACID_DROP_0);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_DMAC_MACID_DROP_0 => %x, " \
				      "DMAC MACID_DROP_0 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_DMAC_MACID_DROP_1);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_DMAC_MACID_DROP_1 => %x, " \
				      "DMAC MACID_DROP_1 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_DMAC_MACID_DROP_2);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_DMAC_MACID_DROP_2 => %x, " \
				      "DMAC MACID_DROP_2 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_DMAC_MACID_DROP_3);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_DMAC_MACID_DROP_3 => %x, " \
				      "DMAC MACID_DROP_3 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_MACID_DROP0);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_MACID_DROP0 => %x, " \
				      "DMAC MACID_DROP_0 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_MACID_DROP1);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_MACID_DROP1 => %x, " \
				      "DMAC MACID_DROP_1 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_MACID_DROP2);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_MACID_DROP2 => %x, " \
				      "DMAC MACID_DROP_2 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_MACID_DROP3);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_MACID_DROP3 => %x, " \
				      "DMAC MACID_DROP_30 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_MACID_DROP4);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_MACID_DROP4 => %x, " \
				      "DMAC MACID_DROP_4 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_MACID_DROP5);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_MACID_DROP5 => %x, " \
				      "DMAC MACID_DROP_5 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_MACID_DROP6);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_MACID_DROP6 => %x, " \
				      "DMAC MACID_DROP_6 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_MACID_DROP7);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_MACID_DROP7 => %x, " \
				      "DMAC MACID_DROP_7 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_DMAC_STA_scheduler(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_0);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_0 => %x, " \
				      "MACID PAUSE 0 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_1);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_1 => %x, " \
				      "MACID PAUSE 1 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_2);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_2 => %x, " \
				      "MACID PAUSE 2 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_3);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_3 => %x, " \
				      "MACID PAUSE 3 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_STA_PAUSE_BITMAP0);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_STA_PAUSE_BITMAP0 => %x, " \
				      "MACID PAUSE 0 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_STA_PAUSE_BITMAP1);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_STA_PAUSE_BITMAP1 => %x, " \
				      "MACID PAUSE 1 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_STA_PAUSE_BITMAP2);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_STA_PAUSE_BITMAP2 => %x, " \
				      "MACID PAUSE 2 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_STA_PAUSE_BITMAP3);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_STA_PAUSE_BITMAP3 => %x, " \
				      "MACID PAUSE 3 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_STA_PAUSE_BITMAP4);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_STA_PAUSE_BITMAP4 => %x, " \
				      "MACID PAUSE 4 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_STA_PAUSE_BITMAP5);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_STA_PAUSE_BITMAP5 => %x, " \
				      "MACID PAUSE 5 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_STA_PAUSE_BITMAP6);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_STA_PAUSE_BITMAP6 => %x, " \
				      "MACID PAUSE 6 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_BE_STA_PAUSE_BITMAP7);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_BE_STA_PAUSE_BITMAP7 => %x, " \
				      "MACID PAUSE 7 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_CMAC_Common(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(0xC000);
		if ((reg1 & 0xF000003F) != 0xF000003F) {
			PLTFM_MSG_ERR("Reg: 0xC000 => %x, " \
				      "CMAC function enable setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(0xC004);
		if ((reg1 & 0x4000003F) != 0x4000003F) {
			PLTFM_MSG_ERR("Reg: 0xC004 => %x, " \
				      "CMAC Clock enable setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_CMAC_SCH(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CMAC_MACID_DROP_0);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CMAC_MACID_DROP_0 => %x, " \
				      "CMAC MACID_DROP_0 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CMAC_MACID_DROP_1);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CMAC_MACID_DROP_1 => %x, " \
				      "CMAC MACID_DROP_1 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CMAC_MACID_DROP_2);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CMAC_MACID_DROP_2 => %x, " \
				      "CMAC MACID_DROP_2 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CMAC_MACID_DROP_3);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_CMAC_MACID_DROP_3 => %x, " \
				      "CMAC MACID_DROP_3 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_MBSSID_DROP_0);
		if ((reg1 & 0x1FFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_MBSSID_DROP_0 => %x, " \
				      "MBSSID_DROP has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_MACID_SLEEP_0);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_MACID_SLEEP_0 => %x, " \
				      "MACID_SLEEP_0 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_MACID_SLEEP_1);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_MACID_SLEEP_1 => %x, " \
				      "MACID_SLEEP_1 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_MACID_SLEEP_2);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_MACID_SLEEP_2 => %x, " \
				      "MACID_SLEEP_2 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_MACID_SLEEP_3);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_MACID_SLEEP_3 => %x, " \
				      "MACID_SLEEP_3 has been setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CTN_TXEN);
		if ((reg1 & 0xFFFF) != 0xFFFF) {
			PLTFM_MSG_ERR("Reg: R_AX_CTN_TXEN => %x, " \
				      "Contension TXEN setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_CTN_DRV_TXEN);
		if ((reg1 & 0xFFFF) != 0xFFFF) {
			PLTFM_MSG_ERR("Reg: R_AX_CTN_DRV_TXEN => %x, " \
				      "Contension DRV TXEN setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_CMAC_PTCL(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#ifdef PHL_FEATURE_NIC
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(0xC600);
		if ((reg1 & 0x3) != 0x3) {
			PLTFM_MSG_ERR("Reg: 0xC600 => %x, " \
				      "HW mode TX setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#endif // AP/NIC Compile flag
#ifdef PHL_FEATURE_AP
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(0xC600);
		if ((reg1 & 0x3) != 0) {
			PLTFM_MSG_ERR("Reg: 0xC600 => %x, " \
				      "HW mode TX setting error\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#endif // AP/NIC Compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_CMAC_TRXPTCL(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_MAC_LOOPBACK);
		if ((reg1 & 0x1) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_MAC_LOOPBACK => %x, " \
				      "\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_TX_Hang_CMAC_RMAC(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		MAC_REG_W32(R_AX_RX_DBG_CNT_SEL, 0);
		reg1 = MAC_REG_R32(R_AX_RX_DBG_CNT_SEL);
		PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
		reg2 = MAC_REG_R32(R_AX_RX_DBG_CNT_SEL);
		if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000)) {
			PLTFM_MSG_ERR("Reg: B0 RX_CNT[0 OFDM_OK] => %x, " \
				      "OFDM counter should be incremantal " \
				      "RX might be stuck\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_BE_8922A_SUPPORT || \
MAC_BE_8934A_SUPPORT || \
MAC_BE_8952A_SUPPORT)
	if (is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A)) {
		*check_number += 1;
		MAC_REG_W32(R_BE_RX_DBG_CNT_SEL, 0);
		reg1 = MAC_REG_R32(R_BE_RX_DBG_CNT_SEL);
		PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
		reg2 = MAC_REG_R32(R_BE_RX_DBG_CNT_SEL);
		if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000)) {
			PLTFM_MSG_ERR("Reg: B0 R_BE_RX_DBG_CNT_SEL[0 OFDM_OK] => %x, " \
				      "OFDM counter should be incremantal " \
				      "RX might be stuck\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8922A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8934A) ||
	    is_chip_id(adapter, MAC_BE_CHIP_ID_8952A))
		return cnt;
	reg1 = 0;
	reg2 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_RX_Hang_HAXIDMA_PCIE(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_DBG_ERR_FLAG_V1);
		if ((reg1 & 0x18) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_DBG_ERR_FLAG_V1 => %x, " \
				      "PCIE TRX Stuck event!\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_RX_Hang_HAXIDMA_USB(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_USB_ENDPOINT_3);
		if ((reg1 & 0x4000) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_USB_ENDPOINT_3 => %x, " \
				      "RX EP is paused\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_USB_ENDPOINT_3_V1);
		if ((reg1 & 0x4000) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_USB_ENDPOINT_3_V1 => %x, " \
				      "RX EP is paused\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_USB_WLAN0_1);
		if ((reg1 & 0x200) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_USB_WLAN0_1 => %x, " \
				      "RX flush mode enabled\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_USB_WLAN0_1_V1);
		if ((reg1 & 0x200) != 0x0) {
			PLTFM_MSG_ERR("Reg: R_AX_USB_WLAN0_1_V1 => %x, " \
				      "RX flush mode enabled\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_RX_Hang_DMAC_STA_scheduler(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_0);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_0 => %x, " \
				      "MACID PAUSE 0 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_1);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_1 => %x, " \
				      "MACID PAUSE 1 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_2);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_2 => %x, " \
				      "MACID PAUSE 2 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_SS_MACID_PAUSE_3);
		if ((reg1 & 0xFFFFFFFF) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_SS_MACID_PAUSE_3 => %x, " \
				      "MACID PAUSE 3 has beed setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_RX_Hang_CMAC_TRXPTCL(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_MAC_LOOPBACK);
		if ((reg1 & 0x1) != 0) {
			PLTFM_MSG_ERR("Reg: R_AX_MAC_LOOPBACK => %x, " \
				      "MAC LB mode setted\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
		if (!check_mac_en(adapter, MAC_AX_BAND_1, MAC_AX_CMAC_SEL)) {
			*check_number += 1;
			reg1 = MAC_REG_R32(R_AX_MAC_LOOPBACK_C1);
			if ((reg1 & 0x1) != 0) {
				PLTFM_MSG_ERR("Reg: R_AX_MAC_LOOPBACK_C1 => %x, " \
					      "MAC C1 LB mode setted\n",
					      reg1);
				cnt += 1;
			}
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_RX_Hang_CMAC_RMAC(struct mac_ax_adapter *adapter, u32 *check_number)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_MGNT_FLTR);
		if ((reg1 & 0xFFFFFFFF) != 0x55555555) {
			PLTFM_MSG_ERR("Reg: R_AX_MGNT_FLTR => %x, " \
				      "Rx mgmt filter misconfiguration\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#ifdef PHL_FEATURE_NIC
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
		if (!check_mac_en(adapter, MAC_AX_BAND_1, MAC_AX_CMAC_SEL)) {
			*check_number += 1;
			reg1 = MAC_REG_R32(R_AX_MGNT_FLTR_C1);
			if ((reg1 & 0xFFFFFFFF) != 0x55555555) {
				PLTFM_MSG_ERR("Reg: R_AX_MGNT_FLTR_C1 => %x, " \
					      "C1 Rx mgmt filter misconfiguration\n",
					      reg1);
				cnt += 1;
			}
		}
	}
#endif // End of IC compile flag
#endif // AP/NIC Compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		reg1 = MAC_REG_R32(R_AX_DATA_FLTR);
		if ((reg1 & 0xFFFFFFFF) != 0x55555555) {
			PLTFM_MSG_ERR("Reg: R_AX_DATA_FLTR => %x, " \
				      "Rx data filter misconfiguration\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#ifdef PHL_FEATURE_NIC
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
		if (!check_mac_en(adapter, MAC_AX_BAND_1, MAC_AX_CMAC_SEL)) {
			*check_number += 1;
			reg1 = MAC_REG_R32(R_AX_DATA_FLTR_C1);
			if ((reg1 & 0xFFFFFFFF) != 0x55555555) {
				PLTFM_MSG_ERR("Reg: R_AX_DATA_FLTR_C1 => %x, " \
					      "C1 Rx data filter misconfiguration\n",
					      reg1);
				cnt += 1;
			}
		}
	}
#endif // End of IC compile flag
#endif // AP/NIC Compile flag
#if (MAC_AX_8852A_SUPPORT || \
MAC_AX_8852B_SUPPORT || \
MAC_AX_8851B_SUPPORT || \
MAC_AX_8852BT_SUPPORT || \
MAC_AX_8852C_SUPPORT || \
MAC_AX_8852D_SUPPORT || \
MAC_AX_8192XB_SUPPORT)
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		*check_number += 1;
		MAC_REG_W32(R_AX_RX_DBG_CNT_SEL, 0);
		reg1 = MAC_REG_R32(R_AX_RX_DBG_CNT_SEL);
		PLTFM_DELAY_MS(DIAGNOSIS_DELAY);
		reg2 = MAC_REG_R32(R_AX_RX_DBG_CNT_SEL);
		if ((reg2 & 0xFFFF0000) <= (reg1 & 0xFFFF0000)) {
			PLTFM_MSG_ERR("Reg: B0 RX_CNT[0 OFDM_OK] => %x, " \
				      "OFDM counter should be incremantal " \
				      "RX might be stuck\n",
				      reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		return cnt;
	reg1 = 0;
	reg2 = 0;
	cnt = 0;
	ops = NULL;
	return MACSUCCESS;
}

u32 diagnosis_PCIE_cfg_spc(struct mac_ax_adapter *adapter, u32 *total_check_number)
{
	u32 cnt = 0;
#if MAC_AX_PCIE_SUPPORT
	u32 check_number = 0;

	*total_check_number = 0;
#endif
#if MAC_AX_PCIE_SUPPORT
	if (adapter->hw_info->intf == MAC_AX_INTF_PCIE) {
		check_number = 0;
		cnt += diagnosis_PCIE_cfg_spc_multi_rule(adapter, &check_number);
		*total_check_number += check_number;
	}
#endif
#if MAC_AX_PCIE_SUPPORT
	if (adapter->hw_info->intf == MAC_AX_INTF_PCIE) {
		check_number = 0;
		cnt += diagnosis_PCIE_cfg_spc_HCI_PCIE(adapter, &check_number);
		*total_check_number += check_number;
	}
#endif
	if (cnt > 0) {
		PLTFM_MSG_ERR("#####################################\n");
		PLTFM_MSG_ERR("####PCIE_cfg_spc Error counter:%d####\n", cnt);
		PLTFM_MSG_ERR("#####################################\n\n");
	}

	return cnt;
}

u32 diagnosis_Beacon_TX(struct mac_ax_adapter *adapter, u32 *total_check_number)
{
	u32 cnt = 0;
	u32 check_number = 0;

	*total_check_number = 0;
	check_number = 0;
	cnt += diagnosis_Beacon_TX_multi_rule(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_Beacon_TX_DMAC_STA_SCH(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_Beacon_TX_CMAC_PTCL(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_Beacon_TX_CMAC_SCH(adapter, &check_number);
	*total_check_number += check_number;
	if (cnt > 0) {
		PLTFM_MSG_ERR("##################################\n");
		PLTFM_MSG_ERR("####Beacon_TX Error counter:%d####\n", cnt);
		PLTFM_MSG_ERR("##################################\n\n");
	}

	return cnt;
}

u32 diagnosis_TX_Hang(struct mac_ax_adapter *adapter, u32 *total_check_number)
{
	u32 cnt = 0;
	u32 check_number = 0;

	*total_check_number = 0;
	check_number = 0;
	cnt += diagnosis_TX_Hang_multi_rule(adapter, &check_number);
	*total_check_number += check_number;
#if MAC_AX_PCIE_SUPPORT
	if (adapter->hw_info->intf == MAC_AX_INTF_PCIE) {
		check_number = 0;
		cnt += diagnosis_TX_Hang_HAXIDMA_PCIE(adapter, &check_number);
		*total_check_number += check_number;
	}
#endif
#if MAC_AX_USB_SUPPORT
	if (adapter->hw_info->intf == MAC_AX_INTF_USB) {
		check_number = 0;
		cnt += diagnosis_TX_Hang_HAXIDMA_USB(adapter, &check_number);
		*total_check_number += check_number;
	}
#endif
	check_number = 0;
	cnt += diagnosis_TX_Hang_DMAC_Common(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TX_Hang_DMAC_Dispatcher(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TX_Hang_DMAC_STA_scheduler(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TX_Hang_CMAC_Common(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TX_Hang_CMAC_SCH(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TX_Hang_CMAC_PTCL(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TX_Hang_CMAC_TRXPTCL(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TX_Hang_CMAC_RMAC(adapter, &check_number);
	*total_check_number += check_number;
	if (cnt > 0) {
		PLTFM_MSG_ERR("################################\n");
		PLTFM_MSG_ERR("####TX_Hang Error counter:%d####\n", cnt);
		PLTFM_MSG_ERR("################################\n\n");
	}

	return cnt;
}

u32 diagnosis_RX_Hang(struct mac_ax_adapter *adapter, u32 *total_check_number)
{
	u32 cnt = 0;
	u32 check_number = 0;

	*total_check_number = 0;
#if MAC_AX_PCIE_SUPPORT
	if (adapter->hw_info->intf == MAC_AX_INTF_PCIE) {
		check_number = 0;
		cnt += diagnosis_RX_Hang_HAXIDMA_PCIE(adapter, &check_number);
		*total_check_number += check_number;
	}
#endif
#if MAC_AX_USB_SUPPORT
	if (adapter->hw_info->intf == MAC_AX_INTF_USB) {
		check_number = 0;
		cnt += diagnosis_RX_Hang_HAXIDMA_USB(adapter, &check_number);
		*total_check_number += check_number;
	}
#endif
	check_number = 0;
	cnt += diagnosis_RX_Hang_DMAC_STA_scheduler(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_RX_Hang_CMAC_TRXPTCL(adapter, &check_number);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_RX_Hang_CMAC_RMAC(adapter, &check_number);
	*total_check_number += check_number;
	if (cnt > 0) {
		PLTFM_MSG_ERR("################################\n");
		PLTFM_MSG_ERR("####RX_Hang Error counter:%d####\n", cnt);
		PLTFM_MSG_ERR("################################\n\n");
	}

	return cnt;
}


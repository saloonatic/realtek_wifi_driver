/******************************************************************************
 *
 * Copyright(c) 2019 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 ******************************************************************************/

#include "wow_diag.h"
#include "mac_priv.h"

u32 c2h_wow_evt_done_ack_hdl(struct mac_ax_adapter *adapter,
			     struct rtw_c2h_info *info)
{
	struct mac_wow_diag_info *diag_info = &adapter->wow_diag_info;

	switch (info->c2h_func) {
	case FWCMD_H2C_FUNC_WOW_REQ_RX_PKT:
		PLTFM_MSG_ALWAYS("[WOW][EVT]Received WOW_REQ_RX_PKT done ack\n");
		if (info->h2c_return == MACSUCCESS)
			diag_info->evt_dack |= BIT(FWCMD_H2C_FUNC_WOW_REQ_RX_PKT);
		else
			PLTFM_MSG_ERR("[WOW][EVT]WOW_REQ_RX_PKT failed\n");
		break;
	case FWCMD_H2C_FUNC_WOW_REQ_MEM:
		PLTFM_MSG_ALWAYS("[WOW][EVT]Received WOW_REQ_MEM done ack\n");
		if (info->h2c_return == MACSUCCESS)
			diag_info->evt_dack |= BIT(FWCMD_H2C_FUNC_WOW_REQ_MEM);
		else
			PLTFM_MSG_ERR("[WOW][EVT]WOW_REQ_MEM failed\n");
		break;
	case FWCMD_H2C_FUNC_WOW_REQ_ROLE_INFO:
		PLTFM_MSG_ALWAYS("[WOW][EVT]Received REQ_ROLE_INFO done ack\n");
		if (info->h2c_return == MACSUCCESS)
			diag_info->evt_dack |= BIT(FWCMD_H2C_FUNC_WOW_REQ_ROLE_INFO);
		else
			PLTFM_MSG_ERR("[WOW][EVT]WOW_REQ_ROLE_INFO failed\n");
		break;
	case FWCMD_H2C_FUNC_WOW_REQ_BB_RF_REG:
		PLTFM_MSG_ALWAYS("[WOW][EVT]Received REQ_BB_RF_REG done ack\n");
		if (info->h2c_return == MACSUCCESS)
			diag_info->evt_dack |= BIT(FWCMD_H2C_FUNC_WOW_REQ_BB_RF_REG);
		else
			PLTFM_MSG_ERR("[WOW][EVT]WOW_REQ_BB_RF_REG failed\n");
		break;
	default:
		PLTFM_MSG_ERR("[WOW][EVT]Unknown wow done ack\n");
		break;
	}

	return MACSUCCESS;
}

u32 c2h_wow_diag_rpt_hdl(struct mac_ax_adapter *adapter, u8 *buf,
			 u32 len, struct rtw_c2h_info *info)
{
	struct mac_ax_wow_diag_rpt *diag_rpt =
		&adapter->wow_diag_info.diag_rpt;
	struct mac_wow_diag_info *diag_info = &adapter->wow_diag_info;
	u8 *c2h_sm = &diag_info->diag_c2h_sm[FWCMD_C2H_FUNC_WOW_DIAG_RPT];
	u8 *c2h_content = buf + FWCMD_HDR_LEN;
	u8 idx;

	PLTFM_MSG_ALWAYS("[DIAG][RPT]------ Start ------\n");

	PLTFM_MEMCPY(diag_rpt, c2h_content,
		     sizeof(struct mac_ax_wow_diag_rpt));

	if (diag_rpt->err_code == B_WOW_DIAG_NOT_SUPPORT) {
		PLTFM_MSG_ALWAYS("WOW_DIAG_NOT_SUPPORT\n");
	} else {
		PLTFM_MSG_ALWAYS("wow_start_tsf_h=%x, wow_start_tsf_l=%x\n",
				 diag_rpt->tsf_h, diag_rpt->tsf_l);
		PLTFM_MSG_ALWAYS("wow diagnostic error code:%x\n",
				 diag_rpt->err_code);

		for (idx = FWCMD_C2H_FUNC_WOW_DIAG_GTK; idx < WOW_DIAG_MAX; idx++) {
			if (diag_rpt->err_code & BIT(idx))
				c2h_sm[idx] = WOW_DIAG_C2H_WAITING;
			PLTFM_MSG_TRACE("sm[%d]=%d\n", idx, c2h_sm[idx]);
		}
	}

	if (*c2h_sm == WOW_DIAG_C2H_WAITING)
		*c2h_sm = WOW_DIAG_C2H_DONE;
	else
		PLTFM_MSG_ERR("Wrong C2H state:%d\n", *c2h_sm);

	PLTFM_MSG_ALWAYS("[DIAG][RPT]------ End ------\n");

	return MACSUCCESS;
}

u32 c2h_wow_diag_gtk_hdl(struct mac_ax_adapter *adapter, u8 *buf,
			 u32 len, struct rtw_c2h_info *info)
{
	struct mac_ax_wow_diag_gtk_info diag_gtk_info;
	struct mac_ax_wow_diag_gtk *diag_gtk = &diag_gtk_info.diag_gtk;
	struct mac_ax_wow_diag_gtk_tx *gtk_tx = &diag_gtk_info.gtk_tx[0];
	struct mac_ax_sta_diag_err_rpt *err_rpt =
		&adapter->wow_diag_info.err_rpt;
	u8 *c2h_sm = &adapter->wow_diag_info.diag_c2h_sm[FWCMD_C2H_FUNC_WOW_DIAG_GTK];
	u8 *c2h_content = buf + FWCMD_HDR_LEN;
	u8 idx, bcn_latest_cnt;

	PLTFM_MEMCPY(&diag_gtk_info, c2h_content,
		     sizeof(struct mac_ax_wow_diag_gtk_info));

	PLTFM_MSG_ALWAYS("[DIAG][GTK]------ Start ------\n");

	PLTFM_MSG_ALWAYS("m1_rcv(%d) m2_enq(%d) m2_success(%d)\n",
			 diag_gtk->m1_rcv, diag_gtk->m2_enq, diag_gtk->m2_suc);
	PLTFM_MSG_ALWAYS("m2_mac_drop(%d) m2_life_drop(%d)\n",
			 diag_gtk->mac_drop, diag_gtk->life_drop);
	PLTFM_MSG_ALWAYS("m2_retry_drop(%d) other_err(%d)\n",
			 diag_gtk->retry_drop, diag_gtk->other_err);
	PLTFM_MSG_ALWAYS("m1_rcv_last(%d) m2_enq_last(%d)\n",
			 diag_gtk->m1_rcv_last, diag_gtk->m2_enq_last);
	PLTFM_MSG_ALWAYS("m2_mac_drop_last(%d) m2_life_drop_last(%d)\n",
			 diag_gtk->mac_drop_last, diag_gtk->life_drop_last);
	PLTFM_MSG_ALWAYS("m2_retry_drop_last(%d) other_err_last(%d)\n",
			 diag_gtk->retry_drop_last, diag_gtk->other_err_last);

	for (idx = 0; idx < GTK_TX_DIAG_MAX; idx++) {
		PLTFM_MSG_ALWAYS("Tx[%d] enq_tsf_h=%x enq_tsf_l=%x\n",
				 idx, gtk_tx[idx].enq_tsf_h, gtk_tx[idx].enq_tsf_l);
		PLTFM_MSG_ALWAYS("Tx[%d] cb_tsf_h=%x cb_tsf_l=%x\n",
				 idx, gtk_tx[idx].cb_tsf_h, gtk_tx[idx].cb_tsf_l);
		PLTFM_MSG_ALWAYS("Tx[%d] ret_type(%x) result(%x)\n",
				 idx, gtk_tx[idx].ret_type, gtk_tx[idx].result);
		PLTFM_MSG_ALWAYS("Tx[%d] ser_l0(%x) ser_l1(%x)\n",
				 idx, gtk_tx[idx].ser_l0, gtk_tx[idx].ser_l1);
	}

	PLTFM_MSG_ALWAYS("m2_tx_idx(%d)\n", diag_gtk_info.tx_idx);
	PLTFM_MSG_ALWAYS("bcn_early_cnt(%x) bcn_ok_cnt(%x)\n",
			 diag_gtk_info.bcn_early_cnt, diag_gtk_info.bcn_ok_cnt);

	bcn_latest_cnt = 0;
	for (idx = 0; idx < WOW_DIAG_LATEST_BCN; idx++) {
		if (BIT(idx) & diag_gtk_info.bcn_ok_latest_mask)
			bcn_latest_cnt++;
	}
	PLTFM_MSG_ALWAYS("bcn_ok_latest_mask(%x)\n",
			 diag_gtk_info.bcn_ok_latest_mask);
	PLTFM_MSG_ALWAYS("rcv cnt of last %d bcns (%d)\n",
			 WOW_DIAG_LATEST_BCN, bcn_latest_cnt);
	err_rpt->wow_err |= B_ERR_WOW_DIAG_TRX;

	if (*c2h_sm == WOW_DIAG_C2H_WAITING)
		*c2h_sm = WOW_DIAG_C2H_DONE;
	else
		PLTFM_MSG_ERR("Wrong C2H state:%d\n", *c2h_sm);

	PLTFM_MSG_ALWAYS("[DIAG][GTK]------ End ------\n");

	return MACSUCCESS;
}

u32 c2h_wow_diag_ap_lost_hdl(struct mac_ax_adapter *adapter, u8 *buf,
			     u32 len, struct rtw_c2h_info *info)
{
	struct mac_ax_wow_diag_aplost_info diag_aplost_info;
	struct mac_ax_wow_diag_aplost *diag_aplost =
		&diag_aplost_info.diag_aplost;
	struct mac_ax_sta_diag_err_rpt *err_rpt =
		&adapter->wow_diag_info.err_rpt;
	u8 *c2h_content = buf + FWCMD_HDR_LEN;
	u8 *c2h_sm =
		&adapter->wow_diag_info.diag_c2h_sm[FWCMD_C2H_FUNC_WOW_DIAG_AP_LOST];

	PLTFM_MEMCPY(&diag_aplost_info, c2h_content,
		     sizeof(struct mac_ax_wow_diag_aplost_info));

	PLTFM_MSG_ALWAYS("[DIAG][AP LOST]------ Start ------\n");

	PLTFM_MSG_ALWAYS("bcn_cnt(%d) tx_success_cnt(%d)\n",
			 diag_aplost->bcn_cnt, diag_aplost->tx_success_cnt);
	PLTFM_MSG_ALWAYS("tx_fail_cnt(%d) tx_fail_rsn(%d)\n",
			 diag_aplost->tx_fail_cnt, diag_aplost->tx_fail_rsn);
	PLTFM_MSG_ALWAYS("disconnect_cnt(%d) disconnect_limit(%d)\n",
			 diag_aplost->disconnect_cnt, diag_aplost->disconnect_limit);
	PLTFM_MSG_ALWAYS("retry_cnt(%d) retry_limit(%d)\n",
			 diag_aplost->retry_cnt, diag_aplost->retry_limit);
	err_rpt->wow_err |= B_ERR_WOW_DIAG_TRX;

	if (*c2h_sm == WOW_DIAG_C2H_WAITING)
		*c2h_sm = WOW_DIAG_C2H_DONE;
	else
		PLTFM_MSG_ERR("Wrong C2H state:%d\n", *c2h_sm);

	PLTFM_MSG_ALWAYS("[DIAG][AP LOST]------ End ------\n");

	return MACSUCCESS;
}

u32 c2h_wow_diag_ser_hdl(struct mac_ax_adapter *adapter, u8 *buf,
			 u32 len, struct rtw_c2h_info *info)
{
	struct mac_ax_wow_diag_ser_info diag_ser_info;
	struct mac_ax_wow_diag_ser *diag_ser =
		&diag_ser_info.dig_ser;
	struct max_ax_wow_diag_tsf_info *l1_tsf =
		&diag_ser_info.l1_tsf[0];
	u8 *c2h_content = buf + FWCMD_HDR_LEN;
	u8 idx;
	u8 *c2h_sm =
		&adapter->wow_diag_info.diag_c2h_sm[FWCMD_C2H_FUNC_WOW_DIAG_SER];

	PLTFM_MEMCPY(&diag_ser_info, c2h_content,
		     sizeof(struct mac_ax_wow_diag_ser_info));

	PLTFM_MSG_ALWAYS("[DIAG][SER]------ Start ------\n");

	PLTFM_MSG_ALWAYS("l1_cnt(%d)\n", diag_ser->l1_cnt);

	for (idx = 0; idx < WOW_DIAG_SER_L1_MAX; idx++) {
		PLTFM_MSG_ALWAYS("l1_tsf[%d]=0x%x,0x%x\n",
				 idx, l1_tsf[idx].tsf_h, l1_tsf[idx].tsf_l);
	}

	if (*c2h_sm == WOW_DIAG_C2H_WAITING)
		*c2h_sm = WOW_DIAG_C2H_DONE;
	else
		PLTFM_MSG_ERR("Wrong C2H state:%d\n", *c2h_sm);

	PLTFM_MSG_ALWAYS("[DIAG][SER]------ End ------\n");

	return MACSUCCESS;
}

static struct c2h_proc_func c2h_proc_wow_diag[] = {
	{FWCMD_C2H_FUNC_WOW_DIAG_RPT, c2h_wow_diag_rpt_hdl},
	{FWCMD_C2H_FUNC_WOW_DIAG_GTK, c2h_wow_diag_gtk_hdl},
	{FWCMD_C2H_FUNC_WOW_DIAG_AP_LOST, c2h_wow_diag_ap_lost_hdl},
	{FWCMD_C2H_FUNC_WOW_DIAG_SER, c2h_wow_diag_ser_hdl},
	{FWCMD_C2H_FUNC_WOW_DIAG_RX_EVT, NULL},
	{FWCMD_C2H_FUNC_WOW_DIAG_KEEPALIVE, NULL},
	{FWCMD_C2H_FUNC_WOW_DIAG_ARP, NULL},
	{FWCMD_C2H_FUNC_WOW_DIAG_NS, NULL},
	{FWCMD_C2H_FUNC_WOW_DIAG_PMF, NULL},
	{FWCMD_C2H_FUNC_WOW_DIAG_PER_WAKE, NULL},
	{FWCMD_C2H_FUNC_WOW_DIAG_NLO, NULL},
	{FWCMD_C2H_FUNC_WOW_DIAG_STA_CSA, NULL},
	{FWCMD_C2H_FUNC_NULL, NULL},
};

u32 c2h_wow_diag(struct mac_ax_adapter *adapter, u8 *buf, u32 len,
		 struct rtw_c2h_info *info)
{
	struct c2h_proc_func *proc = c2h_proc_wow_diag;
	u32 (*handler)(struct mac_ax_adapter *adapter, u8 *buf, u32 len,
		       struct rtw_c2h_info *info) = NULL;
	u32 hdr0;
	u32 func;

	PLTFM_MSG_TRACE("%s,cat(%d)class(%d)func(%d)len(%d)\n", __func__,
			info->c2h_cat, info->c2h_class, info->c2h_func, len);

	hdr0 = ((struct fwcmd_hdr *)buf)->hdr0;
	hdr0 = le32_to_cpu(hdr0);

	func = GET_FIELD(hdr0, C2H_HDR_FUNC);

	while (proc->id != FWCMD_C2H_FUNC_NULL) {
		if (func == proc->id && proc->handler) {
			handler = proc->handler;
			break;
		}
		proc++;
	}

	if (!handler) {
		PLTFM_MSG_ERR("%s null func handler id: %X", __func__, func);
		return MACNOITEM;
	}

	return handler(adapter, buf, len, info);
}

u32 c2h_wow_evt_dump_rx_hdl(struct mac_ax_adapter *adapter,
			    u8 *buf, u32 len, struct rtw_c2h_info *info)
{
	struct mac_wow_diag_info *diag_info = &adapter->wow_diag_info;
	u8 *c2h_sm = &diag_info->evt_c2h_sm[FWCMD_C2H_FUNC_WOW_DUMP_RX];

	PLTFM_MSG_ALWAYS("[WOW][EVT][DUMP RX]------ Start ------\n");

	if (*c2h_sm == WOW_DIAG_C2H_WAITING)
		*c2h_sm = WOW_DIAG_C2H_DONE;
	else
		PLTFM_MSG_ERR("Wrong C2H state:%d\n", *c2h_sm);

	PLTFM_MSG_ALWAYS("[WOW][EVT][DUMP RX]------ End ------\n");

	return MACSUCCESS;
}

u32 c2h_wow_evt_dump_mem_hdl(struct mac_ax_adapter *adapter,
			     u8 *buf, u32 len, struct rtw_c2h_info *info)
{
	struct mac_wow_diag_info *diag_info = &adapter->wow_diag_info;
	u8 *c2h_sm = &diag_info->evt_c2h_sm[FWCMD_C2H_FUNC_WOW_DUMP_MEM];

	PLTFM_MSG_ALWAYS("[WOW][EVT][DUMP MEM] ------ Start ------\n");

	if (*c2h_sm == WOW_DIAG_C2H_WAITING)
		*c2h_sm = WOW_DIAG_C2H_DONE;
	else
		PLTFM_MSG_ERR("Wrong C2H state:%d\n", *c2h_sm);

	PLTFM_MSG_ALWAYS("[WOW][EVT][DUMP MEM]------ End ------\n");

	return MACSUCCESS;
}

u32 c2h_wow_evt_dump_role_hdl(struct mac_ax_adapter *adapter,
			      u8 *buf, u32 len, struct rtw_c2h_info *info)
{
	struct mac_wow_diag_info *diag_info = &adapter->wow_diag_info;
	u8 *c2h_sm = &diag_info->evt_c2h_sm[FWCMD_C2H_FUNC_WOW_DUMP_ROLE];

	PLTFM_MSG_ALWAYS("[WOW][EVT][DUMP ROLE]------ Start ------\n");

	if (*c2h_sm == WOW_DIAG_C2H_WAITING)
		*c2h_sm = WOW_DIAG_C2H_DONE;
	else
		PLTFM_MSG_ERR("Wrong C2H state:%d\n", *c2h_sm);

	PLTFM_MSG_ALWAYS("[WOW][EVT][DUMP ROLE]------ End ------\n");

	return MACSUCCESS;
}

u32 c2h_wow_evt_dump_bb_rf_reg_hdl(struct mac_ax_adapter *adapter,
				   u8 *buf, u32 len, struct rtw_c2h_info *info)
{
	struct mac_wow_diag_info *diag_info = &adapter->wow_diag_info;
	u8 *c2h_sm = &diag_info->evt_c2h_sm[FWCMD_C2H_FUNC_WOW_DUMP_BB_RF_REG];

	PLTFM_MSG_ALWAYS("[WOW][EVT][DUMP BB RF REG]------ Start ------\n");

	if (*c2h_sm == WOW_DIAG_C2H_WAITING)
		*c2h_sm = WOW_DIAG_C2H_DONE;
	else
		PLTFM_MSG_ERR("[DUMP BB RF REG]Wrong C2H state:%d\n", *c2h_sm);

	PLTFM_MSG_ALWAYS("[WOW][EVT][DUMP BB RF REG]------ End ------\n");

	return MACSUCCESS;
}

static struct c2h_proc_func c2h_proc_wow_tri_evt[] = {
	{FWCMD_C2H_FUNC_WOW_DUMP_RX, c2h_wow_evt_dump_rx_hdl},
	{FWCMD_C2H_FUNC_WOW_DUMP_MEM, c2h_wow_evt_dump_mem_hdl},
	{FWCMD_C2H_FUNC_WOW_DUMP_ROLE, c2h_wow_evt_dump_role_hdl},
	{FWCMD_C2H_FUNC_WOW_DUMP_BB_RF_REG, c2h_wow_evt_dump_bb_rf_reg_hdl},
	{FWCMD_C2H_FUNC_NULL, NULL},
};

u32 c2h_wow_tri_evt(struct mac_ax_adapter *adapter, u8 *buf, u32 len,
		    struct rtw_c2h_info *info)
{
	struct c2h_proc_func *proc = c2h_proc_wow_tri_evt;
	u32 (*handler)(struct mac_ax_adapter *adapter, u8 *buf, u32 len,
		       struct rtw_c2h_info *info) = NULL;
	u32 hdr0;
	u32 func;

	hdr0 = ((struct fwcmd_hdr *)buf)->hdr0;
	hdr0 = le32_to_cpu(hdr0);

	func = GET_FIELD(hdr0, C2H_HDR_FUNC);

	while (proc->id != FWCMD_C2H_FUNC_NULL) {
		if (func == proc->id && proc->handler) {
			handler = proc->handler;
			break;
		}
		proc++;
	}

	if (!handler) {
		PLTFM_MSG_ERR("%s, null func handler id: %X", __func__, func);
		return MACNOITEM;
	}

	return handler(adapter, buf, len, info);
}

u32 send_h2c_wow_diag_ctrl(struct mac_ax_adapter *adapter,
			   u8 stop)
{
	u32 ret = MACSUCCESS;
	struct h2c_info h2c_info = { 0 };
	struct fwcmd_wow_diag_ctrl *content;
	u8 *c2h_sm =
		&adapter->wow_diag_info.diag_c2h_sm[FWCMD_C2H_FUNC_WOW_DIAG_RPT];

	h2c_info.agg_en = 0;
	h2c_info.content_len = sizeof(struct fwcmd_wow_diag_ctrl);
	h2c_info.h2c_cat = FWCMD_H2C_CAT_MAC;
	h2c_info.h2c_class = FWCMD_H2C_CL_WOW_DIAG;
	h2c_info.h2c_func = FWCMD_H2C_FUNC_WOW_DIAG_CTRL;
	h2c_info.rec_ack = 0;
	h2c_info.done_ack = 0;

	content = (struct fwcmd_wow_diag_ctrl *)
		   PLTFM_MALLOC(h2c_info.content_len);

	if (!content) {
		PLTFM_MSG_ERR("%s: malloc fail\n", __func__);
		return MACNPTR;
	}

	content->dword0 =
		cpu_to_le32(stop ? FWCMD_H2C_WOW_DIAG_CTRL_STOP : 0);
	ret = mac_h2c_common(adapter, &h2c_info, (u32 *)content);
	if (ret) {
		PLTFM_MSG_ERR("[WOW][DIAG]Tx H2C fail (%d)\n", ret);
	} else {
		*c2h_sm = WOW_DIAG_C2H_WAITING;
		PLTFM_MSG_TRACE("[WOW][DIAG]Waiting DIAG_RPT C2H");
	}
	PLTFM_FREE(content, h2c_info.content_len);

	return ret;
}

u32 mac_req_wow_diag_rpt(struct mac_ax_adapter *adapter,
			 struct mac_ax_sta_diag_err_rpt *rpt_out)
{
	struct mac_wow_diag_info *diag_info = &adapter->wow_diag_info;
	struct mac_ax_wow_diag_rpt *diag_rpt = &diag_info->diag_rpt;
	struct mac_ax_sta_diag_err_rpt *err_rpt = &diag_info->err_rpt;
	u8 *diag_sm = &diag_info->diag_c2h_sm[0];
	u8 *evt_sm = &diag_info->evt_c2h_sm[0];
	u32 ret = MACSUCCESS;
	u8 cnt, idx;
	u32 c2h_to_poll;

	if (adapter->sm.fwdl != MAC_AX_FWDL_INIT_RDY)
		return MACNOFW;

	PLTFM_MEMSET(err_rpt, 0, sizeof(struct mac_ax_sta_diag_err_rpt));
	PLTFM_MEMSET(diag_sm, WOW_DIAG_C2H_IDLE, WOW_DIAG_MAX);
	if (diag_info->evt_en) {
		PLTFM_MEMSET(evt_sm, WOW_DIAG_C2H_IDLE, WOW_TRI_EVT_MAX);
		for (idx = 0; idx < WOW_TRI_EVT_MAX; idx++) {
			if (BIT(idx) & diag_info->evt_en)
				evt_sm[idx] = WOW_DIAG_C2H_WAITING;
		}
	}

	ret = send_h2c_wow_diag_ctrl(adapter, WOW_DIAG_REQ_STOP);
	if (ret) {
		err_rpt->wow_err |= B_ERR_WOW_DIAG_H2C_ENQ;
		//TODO: API to dump FW debug
		return ret;
	}

	cnt = WOW_DIAG_POLL_CNT;
	while (diag_sm[FWCMD_C2H_FUNC_WOW_DIAG_RPT] != WOW_DIAG_C2H_DONE) {
		PLTFM_DELAY_MS(WOW_DIAG_POLL_MS);
		if (--cnt == 0) {
			diag_sm[FWCMD_C2H_FUNC_WOW_DIAG_RPT] = WOW_DIAG_C2H_IDLE;
			err_rpt->wow_err |= B_ERR_WOW_DIAG_C2H_POLL;
			PLTFM_MSG_ERR("[WOW][DIAG]Poll report fail\n");
			return MACPOLLTO;
		}
	}
	diag_sm[FWCMD_C2H_FUNC_WOW_DIAG_RPT] = WOW_DIAG_C2H_IDLE;

	if (diag_rpt->err_code == B_WOW_DIAG_NOT_SUPPORT) {
		PLTFM_MSG_TRACE("[WOW][DIAG]FW not support\n");
		return MACSUCCESS;
	}

	c2h_to_poll = diag_rpt->err_code;
	cnt = WOW_DIAG_POLL_CNT;
	while (c2h_to_poll) {
		PLTFM_DELAY_MS(WOW_DIAG_POLL_MS);
		for (idx = 0; idx < WOW_DIAG_MAX; idx++) {
			if (BIT(idx) & c2h_to_poll) {
				if (diag_sm[idx] == WOW_DIAG_C2H_DONE) {
					diag_sm[idx] = WOW_DIAG_C2H_IDLE;
					c2h_to_poll &= ~(BIT(idx));
				}
			}
		}
		if (--cnt == 0) {
			err_rpt->err |= B_ERR_WOW_DIAG_C2H_POLL;
			PLTFM_MSG_ERR("[WOW][DIAG]Poll C2H(0x%x) fail\n", c2h_to_poll);
			ret = MACPOLLTO;
			break;
		}
	}

	if (diag_info->evt_en) {
		PLTFM_MSG_TRACE("[WOW][EVT]Start to poll EVT(0x%x)\n",
				diag_info->evt_en);
		c2h_to_poll = diag_info->evt_en;
		cnt = WOW_EVT_POLL_CNT;
		while (c2h_to_poll) {
			PLTFM_DELAY_MS(WOW_EVT_POLL_MS);
			for (idx = 0; idx < WOW_TRI_EVT_MAX; idx++) {
				if (BIT(idx) & c2h_to_poll) {
					if (evt_sm[idx] == WOW_DIAG_C2H_DONE) {
						evt_sm[idx] = WOW_DIAG_C2H_IDLE;
						c2h_to_poll &= ~(BIT(idx));
					}
				}
			}
			if (--cnt == 0) {
				PLTFM_MSG_ERR("[WOW][EVT]Poll C2H(0x%x) fail\n",
					      c2h_to_poll);
				err_rpt->err |= B_ERR_WOW_DIAG_C2H_POLL;
				ret = MACPOLLTO;
				break;
			}
		}
		diag_info->evt_en = 0;
	}

	if (rpt_out) {
		PLTFM_MEMCPY(rpt_out, err_rpt,
			     sizeof(struct mac_ax_sta_diag_err_rpt));
	} else {
		PLTFM_MSG_ERR("[WOW][DIAG] Input NULL Report\n");
		ret = MACNPTR;
	}

	return ret;
}

u32 send_h2c_evt_req_rx_pkt(struct mac_ax_adapter *adapter)
{
	u32 ret = MACSUCCESS;
	struct h2c_info h2c_info = { 0 };
	struct fwcmd_wow_req_rx_pkt *content;
	struct wow_tri_evt_parm *evt_parm = &adapter->wow_diag_info.evt_parm;

	h2c_info.agg_en = 0;
	h2c_info.content_len = sizeof(struct fwcmd_wow_req_rx_pkt);
	h2c_info.h2c_cat = FWCMD_H2C_CAT_MAC;
	h2c_info.h2c_class = FWCMD_H2C_CL_WOW_TRI_EVT;
	h2c_info.h2c_func = FWCMD_H2C_FUNC_WOW_REQ_RX_PKT;
	h2c_info.rec_ack = 0;
	h2c_info.done_ack = 1;

	content =
		(struct fwcmd_wow_req_rx_pkt *)PLTFM_MALLOC(h2c_info.content_len);

	if (!content) {
		PLTFM_MSG_ERR("%s: malloc fail\n", __func__);
		return MACNPTR;
	}
	content->dword0 =
		cpu_to_le32(SET_WORD(evt_parm->pkt_num,
				     FWCMD_H2C_WOW_REQ_RX_PKT_PKT_NUM) |
			    SET_WORD(evt_parm->pld_size,
				     FWCMD_H2C_WOW_REQ_RX_PKT_PLD_SIZE));

	ret = mac_h2c_common(adapter, &h2c_info, (u32 *)content);
	if (ret)
		PLTFM_MSG_ERR("[WOW][EVT]REQ_RX_PKT H2C fail (%d)\n", ret);

	PLTFM_FREE(content, h2c_info.content_len);

	return ret;
}

u32 send_h2c_evt_req_mem(struct mac_ax_adapter *adapter)
{
	u32 ret = MACSUCCESS;
	struct h2c_info h2c_info = { 0 };
	struct fwcmd_wow_req_mem *content;
	struct wow_tri_evt_parm *evt_parm = &adapter->wow_diag_info.evt_parm;

	h2c_info.agg_en = 0;
	h2c_info.content_len = sizeof(struct fwcmd_wow_req_mem);
	h2c_info.h2c_cat = FWCMD_H2C_CAT_MAC;
	h2c_info.h2c_class = FWCMD_H2C_CL_WOW_TRI_EVT;
	h2c_info.h2c_func = FWCMD_H2C_FUNC_WOW_REQ_MEM;
	h2c_info.rec_ack = 0;
	h2c_info.done_ack = 1;

	content = (struct fwcmd_wow_req_mem *)
		PLTFM_MALLOC(h2c_info.content_len);

	if (!content) {
		PLTFM_MSG_ERR("%s: malloc fail\n", __func__);
		return MACNPTR;
	}
	content->dword0 =
	cpu_to_le32((evt_parm->heap_info ? FWCMD_H2C_WOW_REQ_MEM_HEAP_INFO : 0) |
		(evt_parm->mem_info ? FWCMD_H2C_WOW_REQ_MEM_MEM_INFO : 0) |
		(evt_parm->wow_start ? FWCMD_H2C_WOW_REQ_MEM_WOW_START : 0) |
		(evt_parm->wow_end ? FWCMD_H2C_WOW_REQ_MEM_WOW_END : 0));

	ret = mac_h2c_common(adapter, &h2c_info, (u32 *)content);
	if (ret)
		PLTFM_MSG_ERR("[WOW][EVT]REQ_MEM H2C fail (%d)\n", ret);

	PLTFM_FREE(content, h2c_info.content_len);

	return ret;
}

u32 send_h2c_evt_req_role_info(struct mac_ax_adapter *adapter)
{
	u32 ret = MACSUCCESS;
	struct h2c_info h2c_info = { 0 };

	h2c_info.agg_en = 0;
	h2c_info.content_len = 0;
	h2c_info.h2c_cat = FWCMD_H2C_CAT_MAC;
	h2c_info.h2c_class = FWCMD_H2C_CL_WOW_TRI_EVT;
	h2c_info.h2c_func = FWCMD_H2C_FUNC_WOW_REQ_ROLE_INFO;
	h2c_info.rec_ack = 0;
	h2c_info.done_ack = 1;

	ret = mac_h2c_common(adapter, &h2c_info, NULL);
	if (ret)
		PLTFM_MSG_ERR("[WOW][EVT]REQ_ROLE_INFO H2C fail (%d)\n", ret);

	return ret;
}

u32 send_h2c_evt_req_bb_rf_reg(struct mac_ax_adapter *adapter)
{
	u32 ret = MACSUCCESS;
	struct h2c_info h2c_info = { 0 };
	struct fwcmd_wow_req_bb_rf_reg *content;
	struct wow_tri_evt_parm *evt_parm = &adapter->wow_diag_info.evt_parm;

	h2c_info.agg_en = 0;
	h2c_info.content_len = sizeof(struct fwcmd_wow_req_bb_rf_reg);
	h2c_info.h2c_cat = FWCMD_H2C_CAT_MAC;
	h2c_info.h2c_class = FWCMD_H2C_CL_WOW_TRI_EVT;
	h2c_info.h2c_func = FWCMD_H2C_FUNC_WOW_REQ_BB_RF_REG;
	h2c_info.rec_ack = 0;
	h2c_info.done_ack = 1;

	content = (struct fwcmd_wow_req_bb_rf_reg *)
		PLTFM_MALLOC(h2c_info.content_len);

	if (!content) {
		PLTFM_MSG_ERR("%s: malloc fail\n", __func__);
		return MACNPTR;
	}
	content->dword0 =
	cpu_to_le32((evt_parm->bb ? FWCMD_H2C_WOW_REQ_BB_RF_REG_BB : 0) |
		(evt_parm->rf ? FWCMD_H2C_WOW_REQ_BB_RF_REG_RF : 0));

	ret = mac_h2c_common(adapter, &h2c_info, (u32 *)content);
	if (ret)
		PLTFM_MSG_ERR("[WOW][EVT]REQ_BB_RF_REG H2C fail (%d)\n", ret);

	PLTFM_FREE(content, h2c_info.content_len);

	return ret;
}

static u32(*send_evt[WOW_TRI_EVT_MAX])(struct mac_ax_adapter *adapter) = {
	send_h2c_evt_req_rx_pkt,
	send_h2c_evt_req_mem,
	send_h2c_evt_req_role_info,
	send_h2c_evt_req_bb_rf_reg,
};

u32 mac_req_wow_tri_evt(struct mac_ax_adapter *adapter)
{
	struct mac_wow_diag_info *diag_info = &adapter->wow_diag_info;
	u32 ret = MACSUCCESS;
	u8 idx, cnt;

	if (!diag_info->evt_en)
		PLTFM_MSG_ALWAYS("[WOW][EVT]en=0x%x\n", diag_info->evt_en);

	diag_info->evt_dack = 0;
	for (idx = 0; idx < WOW_TRI_EVT_MAX; idx++)
		diag_info->evt_c2h_sm[idx] = WOW_DIAG_C2H_IDLE;

	if (diag_info->evt_en) {
		for (idx = 0; idx < WOW_TRI_EVT_MAX; idx++) {
			if (BIT(idx) & diag_info->evt_en) {
				if (send_evt[idx])
					ret = send_evt[idx](adapter);
			}
		}
	}

	cnt = WOW_DIAG_POLL_CNT;
	while (diag_info->evt_dack != diag_info->evt_en) {
		PLTFM_DELAY_MS(WOW_DIAG_POLL_MS);
		if (--cnt == 0) {
			PLTFM_MSG_ERR("[WOW][EVT]Poll done ack(0x%x) fail\n",
				      diag_info->evt_dack);
			ret = MACPOLLTO;
			break;
		}
	}

	diag_info->evt_en = diag_info->evt_dack;

	return ret;
}

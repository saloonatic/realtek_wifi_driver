/******************************************************************************
 *
 * Copyright(c) 2019 - 2021 Realtek Corporation.
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
 *****************************************************************************/
#ifndef __RTW_CSA_H_
#define __RTW_CSA_H_

#if CONFIG_DFS
#define CSA_IE_LEN 3 /* Length of Channel Switch Announcement element */
#define ECSA_IE_LEN 4 /* Length of Extended Channel Switch Announcement element */
#define CSA_SWITCH_MODE 0
#define CSA_NEW_CH 1
#define CSA_SWITCH_COUNT 2
#define MAX_CSA_CNT 10

#define WAIT_BCN_TIMES 5

#define CS_WR_DATA_LEN 5 /* Length of Channel Switch Wrapper element */

#ifdef CONFIG_ECSA_PHL
#define MCC_ECSA_DELAY_START_TIME 3000 /* ms */

enum ecsa_state_t {
	ECSA_ST_NONE,
	ECSA_ST_SW_START, /* ready to switch */
	ECSA_ST_SW_DONE /* switch done */
};

enum csa_trigger_type {
	/* AP mode trigger channel switch via driver core layer */
	CSA_AP_CORE_SWITCH_CH,

	/* AP mode trigger channel switch via chan_switch command from hostapd or wpa_supplicant */
	CSA_AP_CFG80211_SWITCH_CH,

	/* STA mode receive CSA/ECSA IE from associating AP */
	CSA_STA_RX_CSA_IE,

	/* STA mode disconnect with DFS AP and DFS region not supported, so switching AP mode to non-DFS channel */
	CSA_STA_DISCONNECT_ON_DFS
};

enum ecsa_mr_case {
	ECSA_SINGLE_ROLE,
	ECSA_MR_SCC_STA_AP,
	ECSA_MR_UNSUPPORTED
};

enum core_layer_ecsa_type{
	ECSA_CORE_TYPE_NONE = 0,
	ECSA_CORE_TYPE_AP = 1,
	ECSA_CORE_TYPE_STA = 2,
	ECSA_CORE_TYPE_SCC_STA_AP = 3 /* Concurrent: one STA mode and one AP mode*/
};

struct core_ecsa_info {
	enum ecsa_state_t state;
	enum core_layer_ecsa_type core_ecsa_type;
	enum phl_ecsa_start_reason ecsa_allow_case;
	u32 ecsa_delay_time;

	/* @channel_width defined in 802.11-2016, Table 9-252 VHT operation information subfields
	* The format of the Wide Bandwidth Channel Switch subelement is the same as the
	* Wide Bandwidth Channel Switch element (see 9.4.2.161) except for the following:
	* A value 0 in the New Channel Width field signifies only a 40 MHz BSS bandwidth
	* 0 for 40 MHz
	* 1 for 80 MHz, 160 MHz or 80+80 MHz
	* 2 for 160 MHz (deprecated)
	* 3 for non-contiguous 80+80 MHz (deprecated)
	* 255 for initial value, defined by driver
	*/
	u8 channel_width;
	struct createbss_parm *bss_param;
	struct rtw_phl_ecsa_param phl_ecsa_param;
	struct _ADAPTER *trigger_iface; /* interface which trigger core layer ECSA flow */
	struct _ADAPTER *execute_iface; /* interface which actually execute PHL ECSA FG */
};

__inline static void set_ecsa_state(struct core_ecsa_info *ecsa_info, enum ecsa_state_t state)
{
	ecsa_info->state = state;
}

__inline static bool check_ecsa_state(struct core_ecsa_info *ecsa_info, enum ecsa_state_t state)
{
	if (ecsa_info->state == state)
		return _TRUE;
	return _FALSE;
}

#define SET_ECSA_STATE(adapter, state) set_ecsa_state(&((adapter)->ecsa_info), (state))
#define CHK_ECSA_STATE(adapter, state) check_ecsa_state(&((adapter)->ecsa_info), (state))

void reset_ecsa_param(struct _ADAPTER *a);
bool rtw_is_ecsa_enabled(struct _ADAPTER *a);
bool rtw_mr_is_ecsa_running(struct _ADAPTER *a);
bool rtw_hal_is_csa_support(struct _ADAPTER *a);
void rtw_ecsa_update_sta_mlme(struct _ADAPTER_LINK *alink, u8 *pframe, u32 packet_len);
void rtw_build_css_ie(struct _ADAPTER *a, struct rtw_phl_ecsa_param *ecsa_param);
void rtw_build_sec_offset_ie(struct _ADAPTER *a, u8 seconday_offset);
void rtw_build_wide_bw_cs_ie(struct _ADAPTER *a, struct rtw_chan_def new_chandef);
void rtw_cfg80211_build_csa_beacon(
	struct _ADAPTER *a,
	struct cfg80211_csa_settings *params,
	struct rtw_chan_def csa_chdef
);
void rtw_ecsa_update_probe_resp(struct xmit_frame *xframe);
void rtw_ecsa_update_beacon(void *priv, struct rtw_wifi_role_t *role, struct rtw_wifi_role_link_t *rlink);
bool rtw_ap_check_ecsa_allow(
	void *priv,
	struct rtw_wifi_role_t *role,
	struct rtw_chan_def chan_def,
	enum phl_ecsa_start_reason reason,
#ifdef CONFIG_PHL_ECSA_EXTEND_OPTION
	u32 *extend_option,
#endif
	u32 *delay_start_ms
);
void rtw_ecsa_mr_update_chan_info_by_role(
	void *priv,
	struct rtw_wifi_role_t *role,
	struct rtw_wifi_role_link_t *rlink,
	struct rtw_chan_def new_chan_def
);
bool rtw_ecsa_check_tx_resume_allow(void *priv, struct rtw_wifi_role_t *role);
void rtw_ecsa_complete(void *priv, struct rtw_wifi_role_t *role);
bool rtw_trigger_phl_ecsa_start(struct _ADAPTER *trigger_iface, enum csa_trigger_type trigger_type);
bool rtw_hal_trigger_csa_start(struct _ADAPTER *a, enum csa_trigger_type trigger_type,
	u8 csa_mode, u8 ecsa_op_class, u8 csa_switch_cnt,
	u8 csa_band, u8 csa_ch, u8 csa_bw, u8 csa_offset,
	u8 csa_ch_width, u8 csa_ch_freq_seg0, u8 csa_ch_freq_seg1);
bool rtw_hal_dfs_trigger_csa(struct _ADAPTER *a,
	enum csa_trigger_type trigger_type,
	u8 band_idx, u8 u_ch, u8 u_bw, u8 u_offset);
#endif /* CONFIG_ECSA_PHL */
#endif /* CONFIG_DFS */

#endif

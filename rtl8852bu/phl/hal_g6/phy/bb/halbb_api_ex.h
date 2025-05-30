/******************************************************************************
 *
 * Copyright(c) 2020 Realtek Corporation.
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
#ifndef _HALBB_API_EX_H_
#define _HALBB_API_EX_H_
#include "halbb_ic_hw_info.h"
#include "halbb_api.h"
/*@--------------------------[Prptotype]-------------------------------------*/
struct bb_info;
#define MAX_MR_NUM 3
struct bb_mcc_i {
	enum role_type type;
	struct rtw_chan_def *chandef;
	u32 *macid_bitmap;
	u8 macid_map_len;
	u8 self_macid;
};

struct bb_mr_i {
	struct rtw_chan_def chandef;
	u8 *all_macid; /* all used macid bitmap */
	u8 all_macid_len;
};

struct bb_mrdm_i {
	enum phl_phy_idx phy_idx;
	struct bb_mr_i mr_info[MAX_MR_NUM];
	u8 mr_num;
};

u8 halbb_ex_cn_report(struct bb_info * bb);
u8 halbb_ex_evm_1ss_report(struct bb_info *bb);
u8 halbb_ex_evm_max_report(struct bb_info *bb);
u8 halbb_ex_evm_min_report(struct bb_info *bb);

bool halbb_tx_cfr_byrate_sup(struct bb_info *bb);
u16 halbb_cfg_cmac_tx_ant(struct bb_info *bb, enum rf_path tx_path);
void halbb_gpio_setting_all(struct bb_info *bb, u8 rfe_idx);
void halbb_gpio_setting(struct bb_info *bb, u8 gpio_idx, enum bb_path path,
			bool inv, enum bb_rfe_src_sel src);
u8 halbb_get_txsc(struct bb_info *bb, u8 pri_ch, u8 central_ch,
		  enum channel_width cbw, enum channel_width dbw);
u8 halbb_get_txsb(struct bb_info *bb, u8 pri_ch, u8 central_ch,
		  enum channel_width cbw, enum channel_width dbw);
void halbb_bb_reset_all(struct bb_info *bb, enum phl_phy_idx phy_idx);
bool halbb_bb_reset_cmn(struct bb_info *bb, bool en, enum phl_phy_idx phy_idx);
void halbb_reset_bb(struct bb_info *bb);

u32 halbb_read_rf_reg_dbg(struct bb_info *bb, enum rf_path path, u32 addr);

u32 halbb_read_rf_reg(struct bb_info *bb, enum rf_path path, u32 addr, u32 mask);

bool halbb_write_rf_reg(struct bb_info *bb, enum rf_path path, u32 addr, u32 mask,
			u32 data);
bool halbb_rf_set_bb_reg(struct bb_info *bb, u32 addr, u32 bit_mask, u32 data);
u32 halbb_rf_get_bb_reg(struct bb_info *bb, u32 addr, u32 mask);
void halbb_ctrl_rf_mode(struct bb_info *bb, enum phl_rf_mode mode);

void halbb_ctrl_rf_mode_rx_path(struct bb_info *bb, enum rf_path rx_path);

bool halbb_ctrl_tx_path_bb_afe_map(struct bb_info *bb, u8 mapping_idx);

bool halbb_ctrl_rx_path(struct bb_info *bb, enum rf_path rx_path,
			       enum phl_phy_idx phy_idx);

bool halbb_ctrl_tx_path_pmac(struct bb_info *bb, enum rf_path tx_path,
			     enum phl_phy_idx phy_idx);

bool halbb_cfg_rx_path(struct bb_info *bb, enum bb_path rx_path,
			       enum phl_phy_idx phy_idx);

bool halbb_cfg_tx_path_pmac(struct bb_info *bb, enum bb_path tx_path,
			     enum phl_phy_idx phy_idx);

bool halbb_cfg_tx_path(struct bb_info *bb, enum bb_path tx_path,
			     enum phl_phy_idx phy_idx);

void halbb_ctrl_trx_path(struct bb_info *bb, enum rf_path tx_path, u8 tx_nss,
			 enum rf_path rx_path, u8 rx_nss);

void halbb_cfg_trx_path(struct bb_info *bb, struct bb_tx_path_en_info tx_path_i,
		        struct bb_rx_path_en_info rx_path_i, enum mlo_dbcc_mode_type mode);

void halbb_tssi_bb_reset(struct bb_info *bb);

void halbb_dfs_en(struct bb_info *bb, bool en);
void halbb_adc_ctrl_en(struct bb_info *bb, bool en, enum phl_phy_idx phy_idx);
void halbb_adc_en(struct bb_info *bb, bool en);
bool halbb_adc_cfg(struct bb_info *bb, enum channel_width bw, enum rf_path path,
		   enum phl_phy_idx phy_idx);

void halbb_tssi_cont_en(struct bb_info *bb, bool en, enum rf_path path);

void halbb_bb_reset_en(struct bb_info *bb, bool en, enum phl_phy_idx phy_idx);

bool halbb_ctrl_bw(struct bb_info *bb, u8 pri_ch, enum band_type band, enum channel_width bw,
		   enum phl_phy_idx phy_idx);

bool halbb_ctrl_bw_ch(struct bb_info *bb, u8 pri_ch, u8 central_ch_seg0,
		      u8 central_ch_seg1, enum band_type band,
		      enum channel_width bw, enum phl_phy_idx phy_idx);
#if (HLABB_CODE_BASE_NUM >= 32)
bool halbb_pre_ctrl_bw_ch(struct bb_info *bb, enum phl_phy_idx phy_idx);

bool halbb_post_ctrl_bw_ch(struct bb_info *bb, enum phl_phy_idx phy_idx);
#endif
void halbb_ctrl_rx_cca(struct bb_info *bb, bool cca_en, enum phl_phy_idx phy_idx);

bool halbb_query_cck_en(struct bb_info *bb, enum phl_phy_idx phy_idx);

void halbb_ctrl_cck_en(struct bb_info *bb, bool cck_enable,
		       enum phl_phy_idx phy_idx);

void halbb_ctrl_ofdm_en(struct bb_info *bb, bool ofdm_enable,
			enum phl_phy_idx phy_idx);

void halbb_ctrl_btg(struct bb_info *bb, bool btg);

void halbb_ctrl_btc_preagc(struct bb_info *bb, bool bt_en);

void halbb_btg_bt_rx(struct bb_info *bb, bool en, enum phl_phy_idx phy_idx);

void halbb_nbtg_bt_tx(struct bb_info *bb, bool en, enum phl_phy_idx phy_idx);

void halbb_pop_en(struct bb_info *bb, bool en, enum phl_phy_idx phy_idx);

bool halbb_querry_pop_en(struct bb_info *bb, enum phl_phy_idx phy_idx);

bool halbb_set_pd_lower_bound(struct bb_info *bb, u8 bound,
			      enum channel_width bw, enum phl_phy_idx phy_idx);

bool halbb_set_pd_lower_bound_cck(struct bb_info *bb, u8 bound,
			      enum channel_width bw, enum phl_phy_idx phy_idx);

u8 halbb_querry_pd_lower_bound(struct bb_info *bb, bool get_en_info,
			       enum phl_phy_idx phy_idx);

u8 halbb_get_losel(struct bb_info *bb);

void halbb_set_ant(struct bb_info *bb, u8 ant);

void halbb_syn_sel(struct bb_info *bb, enum rf_path path, bool val,
		   enum phl_phy_idx phy_idx);

void halbb_bb_wrap_set_pow_by_rate_all(struct bb_info *bb, enum phl_phy_idx phy_idx);

void halbb_bb_wrap_set_pwr_limit_rua_all(struct bb_info *bb, enum phl_phy_idx phy_idx);

void halbb_bb_wrap_set_pwr_limit_all(struct bb_info *bb, enum phl_phy_idx phy_idx);

void halbb_bb_wrap_set_pwr_ofst_mode_all(struct bb_info *bb, enum phl_phy_idx phy_idx);

void halbb_bb_wrap_set_pwr_ofst_bw_all(struct bb_info *bb, enum phl_phy_idx phy_idx);

void halbb_bb_wrap_set_pwr_limit_en(struct bb_info *bb, enum phl_phy_idx phy_idx);

void halbb_bb_wrap_set_max_pwr_limit(struct bb_info *bb, enum phl_phy_idx phy_idx, s16 max_limit);
enum rtw_hal_status halbb_emlsr_en(struct bb_info *bb, bool en);

#if (HLABB_CODE_BASE_NUM >= 32)
bool halbb_ctrl_mlo(struct bb_info *bb, enum mlo_dbcc_mode_type mode);
#endif

void halbb_set_igi(struct bb_info *bb, u8 lna_idx, bool tia_idx, u8 rxbb_idx,
		   enum rf_path path);
void halbb_set_tx_pow_pattern_shap(struct bb_info *bb, u8 ch,
				   bool is_ofdm, enum phl_phy_idx phy_idx);
void halbb_set_tx_pow_per_path_lmt(struct bb_info *bb, s16 pwr_lmt_a, s16 pwr_lmt_b);
void halbb_set_tx_pow_ref(struct bb_info *bb, enum phl_phy_idx phy_idx);

void halbb_normal_efuse_verify(struct bb_info *bb, s8 rx_gain_offset,
			       enum rf_path rx_path, enum phl_phy_idx phy_idx);

u8 halbb_upd_mcc_macid(struct bb_info *bb, struct bb_mcc_i *mi);

void halbb_mcc_stop(struct bb_info *bb);

u8 halbb_mcc_start(struct bb_info *bb, struct bb_mcc_i *mi_1,
		   struct bb_mcc_i *mi_2);

u8 halbb_mrdm_start(struct bb_info *bb, u8 phy_type, struct bb_mrdm_i *mrdm);

void halbb_mrdm_stop(struct bb_info *bb, u8 phy_type);

u8 halbb_upd_mrdm_macid(struct bb_info *bb, struct bb_mrdm_i *mrdm);

void halbb_normal_efuse_verify_cck(struct bb_info *bb, s8 rx_gain_offset,
				   enum rf_path rx_path,
				   enum phl_phy_idx phy_idx);
enum rtw_hal_status halbb_config_cmac_tbl(struct bb_info *bb, struct rtw_phl_stainfo_t *phl_sta_i,
			void *cctrl,
			void *cctl_info_mask);
extern bool halbb_lps_info(struct bb_info *bb, u16 mac_id);

extern bool halbb_lps_save_ch_info(struct bb_info *bb);

extern bool halbb_lps_info_status_chk(struct bb_info *bb);

void halbb_agc_fix_gain(struct bb_info *bb, bool enable, enum rf_path path,
			enum phl_phy_idx phy_idx);
void halbb_agc_elna_idx(struct bb_info *bb, bool elna_idx, enum rf_path path,
			enum phl_phy_idx phy_idx);
void halbb_agc_tia_shrink(struct bb_info *bb, bool shrink_en, bool shrink_init,
			  enum rf_path path, enum phl_phy_idx phy_idx);
void halbb_npath_en_update(struct bb_info *bb, bool npath_en);
#endif

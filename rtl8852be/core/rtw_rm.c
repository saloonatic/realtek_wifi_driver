/******************************************************************************
 *
 * Copyright(c) 2007 - 2019 Realtek Corporation.
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

#include <drv_types.h>
#ifdef CONFIG_RTW_80211K
#include "rtw_rm_fsm.h"
#include "rtw_rm_util.h"
#endif

#define pstr(s) s+strlen(s)
#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

u8 rm_post_event_hdl(_adapter *padapter, u8 *pbuf)
{
#ifdef CONFIG_RTW_80211K
	struct rm_event *pev = (struct rm_event *)pbuf;

	_rm_post_event(padapter, pev->rmid, pev->evid);
	rm_handler(padapter, pev);
#endif
	return H2C_SUCCESS;
}

void rm_update_cap(u8 *frame_head, _adapter *pa, u32 pktlen, int offset)
{
#ifdef CONFIG_RTW_80211K
	u8 *res;
	sint len;

	res = rtw_get_ie(frame_head + offset, _EID_RRM_EN_CAP_IE_, &len,
			 pktlen - offset);
	if (res != NULL)
		_rtw_memcpy((void *)pa->rmpriv.rm_en_cap_def, (res + 2),
			    MIN(len, sizeof(pa->rmpriv.rm_en_cap_def)));
#endif
}

#ifdef CONFIG_RTW_80211K
struct cmd_meas_type_ {
	u8 id;
	char *name;
};

char *rm_type_req_name(u8 meas_type) {

	switch (meas_type) {
	case basic_req:
		return "basic_req";
	case cca_req:
		return "cca_req";
	case rpi_histo_req:
		return "rpi_histo_req";
	case ch_load_req:
		return "ch_load_req";
	case noise_histo_req:
		return "noise_histo_req";
	case bcn_req:
		return "bcn_req";
	case frame_req:
		return "frame_req";
	case sta_statis_req:
		return "sta_statis_req";
	}
	return "unknown_req";
};

char *rm_type_rep_name(u8 meas_type) {

	switch (meas_type) {
	case basic_rep:
		return "basic_rep";
	case cca_rep:
		return "cca_rep";
	case rpi_histo_rep:
		return "rpi_histo_rep";
	case ch_load_rep:
		return "ch_load_rep";
	case noise_histo_rep:
		return "noise_histo_rep";
	case bcn_rep:
		return "bcn_rep";
	case frame_rep:
		return "frame_rep";
	case sta_statis_rep:
		return "sta_statis_rep";
	}
	return "unknown_rep";
};

char *rm_en_cap_name(enum rm_cap_en en)
{
	switch (en) {
	case RM_LINK_MEAS_CAP_EN:
		return "RM_LINK_MEAS_CAP_EN";
	case RM_NB_REP_CAP_EN:
		return "RM_NB_REP_CAP_EN";
	case RM_PARAL_MEAS_CAP_EN:
		return "RM_PARAL_MEAS_CAP_EN";
	case RM_REPEAT_MEAS_CAP_EN:
		return "RM_REPEAT_MEAS_CAP_EN";
	case RM_BCN_PASSIVE_MEAS_CAP_EN:
		return "RM_BCN_PASSIVE_MEAS_CAP_EN";
	case RM_BCN_ACTIVE_MEAS_CAP_EN:
		return "RM_BCN_ACTIVE_MEAS_CAP_EN";
	case RM_BCN_TABLE_MEAS_CAP_EN:
		return "RM_BCN_TABLE_MEAS_CAP_EN";
	case RM_BCN_MEAS_REP_COND_CAP_EN:
		return "RM_BCN_MEAS_REP_COND_CAP_EN";

	case RM_FRAME_MEAS_CAP_EN:
		return "RM_FRAME_MEAS_CAP_EN";
	case RM_CH_LOAD_CAP_EN:
		return "RM_CH_LOAD_CAP_EN";
	case RM_NOISE_HISTO_CAP_EN:
		return "RM_NOISE_HISTO_CAP_EN";
	case RM_STATIS_MEAS_CAP_EN:
		return "RM_STATIS_MEAS_CAP_EN";
	case RM_LCI_MEAS_CAP_EN:
		return "RM_LCI_MEAS_CAP_EN";
	case RM_LCI_AMIMUTH_CAP_EN:
		return "RM_LCI_AMIMUTH_CAP_EN";
	case RM_TRANS_STREAM_CAT_MEAS_CAP_EN:
		return "RM_TRANS_STREAM_CAT_MEAS_CAP_EN";
	case RM_TRIG_TRANS_STREAM_CAT_MEAS_CAP_EN:
		return "RM_TRIG_TRANS_STREAM_CAT_MEAS_CAP_EN";

	case RM_AP_CH_REP_CAP_EN:
		return "RM_AP_CH_REP_CAP_EN";
	case RM_RM_MIB_CAP_EN:
		return "RM_RM_MIB_CAP_EN";
	case RM_OP_CH_MAX_MEAS_DUR0:
		return "RM_OP_CH_MAX_MEAS_DUR0";
	case RM_OP_CH_MAX_MEAS_DUR1:
		return "RM_OP_CH_MAX_MEAS_DUR1";
	case RM_OP_CH_MAX_MEAS_DUR2:
		return "RM_OP_CH_MAX_MEAS_DUR2";
	case RM_NONOP_CH_MAX_MEAS_DUR0:
		return "RM_NONOP_CH_MAX_MEAS_DUR0";
	case RM_NONOP_CH_MAX_MEAS_DUR1:
		return "RM_NONOP_CH_MAX_MEAS_DUR1";
	case RM_NONOP_CH_MAX_MEAS_DUR2:
		return "RM_NONOP_CH_MAX_MEAS_DUR2";

	case RM_MEAS_PILOT_CAP0:
		return "RM_MEAS_PILOT_CAP0";		/* 24-26 */
	case RM_MEAS_PILOT_CAP1:
		return "RM_MEAS_PILOT_CAP1";
	case RM_MEAS_PILOT_CAP2:
		return "RM_MEAS_PILOT_CAP2";
	case RM_MEAS_PILOT_TRANS_INFO_CAP_EN:
		return "RM_MEAS_PILOT_TRANS_INFO_CAP_EN";
	case RM_NB_REP_TSF_OFFSET_CAP_EN:
		return "RM_NB_REP_TSF_OFFSET_CAP_EN";
	case RM_RCPI_MEAS_CAP_EN:
		return "RM_RCPI_MEAS_CAP_EN";		/* 29 */
	case RM_RSNI_MEAS_CAP_EN:
		return "RM_RSNI_MEAS_CAP_EN";
	case RM_BSS_AVG_ACCESS_DELAY_CAP_EN:
		return "RM_BSS_AVG_ACCESS_DELAY_CAP_EN";

	case RM_AVALB_ADMIS_CAPACITY_CAP_EN:
		return "RM_AVALB_ADMIS_CAPACITY_CAP_EN";
	case RM_ANT_CAP_EN:
		return "RM_ANT_CAP_EN";
	case RM_RSVD:
	case RM_MAX:
	default:
		break;
	}
	return "unknown";
}

void _dump_buf(u8 *ptr, u32 len, const char *caller)
{
#if (RM_MORE_DBG_MSG)
	u8 str[128];
	int i;

	printk("%s()len=%d\n",caller ,len);
	memset(str, 0, sizeof(str));
	for (i=0;i<len;i++) {
		sprintf(str+strlen(str),"%02x ",*ptr++);
		if ((i+1)%16==0) {
			printk("%s\n",str);
			memset(str, 0, sizeof(str));
		}
	}
	if ((i+1)%16!=0)
		printk("%s\n",str);
#endif
}
#define dump_buf(a, b) _dump_buf(a, b, __func__)

int rm_en_cap_chk_and_set(struct rm_obj *prm, enum rm_cap_en en)
{
	int idx;
	u8 cap;


	if (en >= RM_MAX)
		return _FALSE;

	idx = en / 8;
	cap = prm->psta->padapter->rmpriv.rm_en_cap_def[idx];

	if (!(cap & BIT(en - (idx*8)))) {
		RTW_INFO("RM: %s incapable\n",rm_en_cap_name(en));
		rm_set_rep_mode(prm, MEAS_REP_MOD_INCAP);
		return _FALSE;
	}
	return _SUCCESS;
}

/* for caller outside rm */
u8 rm_add_nb_req(_adapter *padapter, struct sta_info *psta)
{
	struct rm_obj *prm;

	prm = rm_alloc_rmobj(padapter);

	if (prm == NULL) {
		RTW_ERR("RM: unable to alloc rm obj for requeset\n");
		return _FALSE;
	}

	prm->psta = psta;
	prm->q.category = RTW_WLAN_CATEGORY_RADIO_MEAS;
	prm->q.diag_token = rm_gen_dialog_token(padapter);
	prm->q.m_token = rm_gen_meas_token(padapter);
	prm->rmid = rm_gen_rmid(padapter, prm, RM_MASTER);
	prm->q.action_code = RM_ACT_NB_REP_REQ;

	#if 0
	if (pmac) { /* find sta_info according to bssid */
		pmac += 4; /* skip mac= */
		if (hwaddr_parse(pmac, bssid) == NULL) {
			sprintf(pstr(s), "Err: \nincorrect mac format\n");
			return _FAIL;
		}
		psta = rm_get_sta(padapter, 0xff, bssid);
	}
	#endif

	/* enquee rmobj */
	rm_enqueue_rmobj(padapter, prm, _FALSE);

	RTW_INFO("RM: rmid=%x add req to " MAC_FMT "\n",
		prm->rmid, MAC_ARG(psta->phl_sta->mac_addr));

	return _SUCCESS;
}

static u8 *build_wlan_hdr(_adapter *padapter, struct xmit_frame *pmgntframe,
	struct sta_info *psta, u16 frame_type)
{
	u8 *pframe;
	u16 *fctrl;
	struct pkt_attrib *pattr;
	struct rtw_ieee80211_hdr *pwlanhdr;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct _ADAPTER_LINK *padapter_link = psta->padapter_link;
	struct link_mlme_ext_info *pmlmeinfo = &padapter_link->mlmeextpriv.mlmext_info;


	/* update attribute */
	pattr = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, padapter_link, pattr);

	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_ctl);
	*(fctrl) = 0;

	_rtw_memcpy(pwlanhdr->addr1, psta->phl_sta->mac_addr, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, padapter_link->mac_addr, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	RTW_INFO("RM: dst = " MAC_FMT "\n", MAC_ARG(pwlanhdr->addr1));

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFragNum(pframe, 0);

	set_frame_sub_type(pframe, WIFI_ACTION);

	pframe += sizeof(struct rtw_ieee80211_hdr_3addr);
	pattr->pktlen = sizeof(struct rtw_ieee80211_hdr_3addr);

	return pframe;
}

void rm_set_rep_mode(struct rm_obj *prm, u8 mode)
{

	RTW_INFO("RM: rmid=%x set %s\n",
		prm->rmid,
		mode|MEAS_REP_MOD_INCAP?"INCAP":
		mode|MEAS_REP_MOD_REFUSE?"REFUSE":
		mode|MEAS_REP_MOD_LATE?"LATE":"");

	prm->p.m_mode |= mode;
}

int issue_null_reply(struct rm_obj *prm)
{
	int len=0, my_len;
	u8 *pframe, m_mode;
	_adapter *padapter = prm->psta->padapter;
	struct pkt_attrib *pattr;
	struct xmit_frame *pmgntframe;
	struct xmit_priv *pxmitpriv = &(padapter->xmitpriv);


	m_mode = prm->q.m_mode;
	if (m_mode || prm->q.rpt == 0) {
		RTW_INFO("RM: rmid=%x reply (%s repeat=%d)\n",
			prm->rmid,
			m_mode&MEAS_REP_MOD_INCAP?"INCAP":
			m_mode&MEAS_REP_MOD_REFUSE?"REFUSE":
			m_mode&MEAS_REP_MOD_LATE?"LATE":"no content",
			prm->q.rpt);
	}

	switch (prm->q.action_code) {
	case RM_ACT_RADIO_MEAS_REQ:
		len = 8;
		break;
	case RM_ACT_NB_REP_REQ:
		len = 3;
		break;
	case RM_ACT_LINK_MEAS_REQ:
		len = 3;
		break;
	default:
		break;
	}

	if (len==0)
		return _FALSE;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	if (pmgntframe == NULL) {
		RTW_ERR("RM: %s alloc xmit_frame fail\n",__func__);
		return _FALSE;
	}
	pattr = &pmgntframe->attrib;
	pframe = build_wlan_hdr(padapter, pmgntframe, prm->psta, WIFI_ACTION);
	pframe = rtw_set_fixed_ie(pframe, 3, &prm->p.category, &pattr->pktlen);

	my_len = 0;
	if (len>5) {
		prm->p.len = len - 3 - 2;
		pframe = rtw_set_fixed_ie(pframe, len - 3,
			&prm->p.e_id, &my_len);
	}

	pattr->pktlen += my_len;
	pattr->last_txcmdsz = pattr->pktlen;
	dump_mgntframe(padapter, pmgntframe);

	return _SUCCESS;
}

int ready_for_scan(struct rm_obj *prm)
{
	_adapter *padapter = prm->psta->padapter;
	u8 ssc_chk;

	if (!rtw_is_adapter_up(padapter))
		return _FALSE;

	ssc_chk = rtw_sitesurvey_condition_check(padapter, _FALSE);

	if (ssc_chk == SS_ALLOW)
		return _SUCCESS;

	return _FALSE;
}

int rm_get_chset(struct rm_obj *prm)
{
	int i,meas_ch_amount=0;
	u8 op_class=0, val8;
	struct rtw_ieee80211_channel *pch_set;

	pch_set = &prm->q.ch_set[0];

	_rtw_memset(pch_set, 0,
		sizeof(struct rtw_ieee80211_channel) * RTW_CHANNEL_SCAN_AMOUNT);

	op_class = prm->q.op_class;
	if (prm->q.ch_num == 0) {
		/* ch_num=0   : scan all ch in operating class */
		meas_ch_amount = rm_get_ch_set(op_class, pch_set, RTW_CHANNEL_SCAN_AMOUNT);

	} else if (prm->q.ch_num == 255) {
		/* 802.11 p.1066 */
		/* ch_num=255 : If the Channel Number is 255 and includes
		 * AP Channel Report subelements
		 */
		meas_ch_amount = rm_get_ch_set_from_bcn_req_opt(&prm->q.opt.bcn, pch_set, RTW_CHANNEL_SCAN_AMOUNT);
	} else {
		pch_set[0].hw_value = prm->q.ch_num;
		pch_set[0].band = rtw_get_band_by_op_class(op_class);
		meas_ch_amount = 1;
		RTW_INFO("RM: meas_ch->hw_value = %u\n", pch_set->hw_value);
	}

	/* get means channel */
	prm->q.ch_set_ch_amount = meas_ch_amount;

#if (RM_MORE_DBG_MSG)
	RTW_INFO("survey (%d) channels\n", meas_ch_amount);
#endif
	return 0;
}

int rm_sitesurvey(struct rm_obj *prm)
{
	int meas_ch_amount=0;
	struct rtw_ieee80211_channel *pch_set;
	struct sitesurvey_parm *parm;


	RTW_INFO("RM: rmid=%x %s\n",prm->rmid, __func__);

	parm = rtw_malloc(sizeof(*parm));
	if (parm == NULL)
		return _FAIL;

	rm_get_chset(prm);
	pch_set = &prm->q.ch_set[0];

	meas_ch_amount = MIN(prm->q.ch_set_ch_amount, RTW_CHANNEL_SCAN_AMOUNT);
	_rtw_memset(parm, 0, sizeof(struct sitesurvey_parm));
	_rtw_memcpy(parm->ch, pch_set, sizeof(struct rtw_ieee80211_channel) * meas_ch_amount);

	_rtw_memcpy(&parm->ssid[0], &prm->q.opt.bcn.ssid, IW_ESSID_MAX_SIZE);

	parm->ssid_num = 1;
	parm->scan_mode = prm->q.scan_mode;
	parm->ch_num = meas_ch_amount;
	parm->rrm_token = prm->rmid;
	parm->duration = prm->q.meas_dur;
	parm->scan_type = RTW_SCAN_RRM;
	/* parm.bw = BW_20M; */

	rtw_sitesurvey_cmd(prm->psta->padapter, parm);
	rtw_mfree(parm, sizeof(*parm));

	return _SUCCESS;
}

static int rm_parse_ch_load_s_elem(struct rm_obj *prm, u8 *pbody, int req_len)
{
	u8 *popt_id;
	int i, p=0; /* position */
	int len = req_len;


	prm->q.opt_s_elem_len = len;
#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: opt_s_elem_len=%d\n", len);
#endif
	while (len) {

		switch (pbody[p]) {
		case ch_load_rep_info:
			/* check RM_EN */
			rm_en_cap_chk_and_set(prm, RM_CH_LOAD_CAP_EN);

			_rtw_memcpy(&(prm->q.opt.clm.rep_cond),
				&pbody[p+2], sizeof(prm->q.opt.clm.rep_cond));

			RTW_INFO("RM: ch_load_rep_info=%u:%u\n",
				prm->q.opt.clm.rep_cond.cond,
				prm->q.opt.clm.rep_cond.threshold);
			break;
		default:
			break;

		}
		len = len - (int)pbody[p+1] - 2;
		p = p + (int)pbody[p+1] + 2;
#if (RM_MORE_DBG_MSG)
		RTW_INFO("RM: opt_s_elem_len=%d\n",len);
#endif
	}
	return _SUCCESS;
}

static int rm_parse_noise_histo_s_elem(struct rm_obj *prm,
	u8 *pbody, int req_len)
{
	u8 *popt_id;
	int i, p=0; /* position */
	int len = req_len;


	prm->q.opt_s_elem_len = len;
#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: opt_s_elem_len=%d\n", len);
#endif

	while (len) {

		switch (pbody[p]) {
		case noise_histo_rep_info:
			/* check RM_EN */
			rm_en_cap_chk_and_set(prm, RM_NOISE_HISTO_CAP_EN);

			_rtw_memcpy(&(prm->q.opt.nhm.rep_cond),
				&pbody[p+2], sizeof(prm->q.opt.nhm.rep_cond));

			RTW_INFO("RM: noise_histo_rep_info=%u:%u\n",
				prm->q.opt.nhm.rep_cond.cond,
				prm->q.opt.nhm.rep_cond.threshold);
			break;
		default:
			break;

       		}
		len = len - (int)pbody[p+1] - 2;
		p = p + (int)pbody[p+1] + 2;
#if (RM_MORE_DBG_MSG)
		RTW_INFO("RM: opt_s_elem_len=%d\n",len);
#endif
	}
	return _SUCCESS;
}

static int rm_parse_bcn_req_s_elem(struct rm_obj *prm, u8 *pbody, int req_len)
{
	u8 *popt_id;
	int i, p=0; /* position */
	int len = req_len;
	int ap_ch_rpt_idx = 0;
	struct _RT_OPERATING_CLASS *op;


	/* opt length,2:pbody[0]+ pbody[1] */
	/* first opt id : pbody[18] */

	prm->q.opt_s_elem_len = len;
#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: opt_s_elem_len=%d\n", len);
#endif

	popt_id = prm->q.opt.bcn.opt_id;
	while (len && prm->q.opt.bcn.opt_id_num < BCN_REQ_OPT_MAX_NUM) {

		switch (pbody[p]) {
		case bcn_req_ssid:
			RTW_INFO("bcn_req_ssid\n");

#if (DBG_BCN_REQ_WILDCARD)
			RTW_INFO("DBG set ssid to WILDCARD\n");
#else
#if (DBG_BCN_REQ_SSID)
			RTW_INFO("DBG set ssid to %s\n",DBG_BCN_REQ_SSID_NAME);
			i = strlen(DBG_BCN_REQ_SSID_NAME);
			prm->q.opt.bcn.ssid.SsidLength = i;
			_rtw_memcpy(&(prm->q.opt.bcn.ssid.Ssid), DBG_BCN_REQ_SSID_NAME,
				MIN(i, sizeof(prm->q.opt.bcn.ssid.Ssid)-1));

#else /* original */
			prm->q.opt.bcn.ssid.SsidLength = pbody[p+1];
			_rtw_memcpy(&(prm->q.opt.bcn.ssid.Ssid), &pbody[p+2],
				MIN(pbody[p+1], sizeof(prm->q.opt.bcn.ssid.Ssid)-1));
#endif
#endif

			RTW_INFO("RM: bcn_req_ssid=%s\n",
				prm->q.opt.bcn.ssid.Ssid);

			popt_id[prm->q.opt.bcn.opt_id_num++] = pbody[p];
			break;

		case bcn_req_rep_info:
			/* check RM_EN */
			rm_en_cap_chk_and_set(prm, RM_BCN_MEAS_REP_COND_CAP_EN);

			_rtw_memcpy(&(prm->q.opt.bcn.rep_cond),
				&pbody[p+2], sizeof(prm->q.opt.bcn.rep_cond));

			RTW_INFO("bcn_req_rep_info=%u:%u\n",
				prm->q.opt.bcn.rep_cond.cond,
				prm->q.opt.bcn.rep_cond.threshold);

			/*popt_id[prm->q.opt.bcn.opt_id_num++] = pbody[p];*/
			break;

		case bcn_req_rep_detail:
#if DBG_BCN_REQ_DETAIL
			prm->q.opt.bcn.rep_detail = 2; /* all IE in beacon */
#else
			prm->q.opt.bcn.rep_detail = pbody[p+2];
#endif
			popt_id[prm->q.opt.bcn.opt_id_num++] = pbody[p];

#if (RM_MORE_DBG_MSG)
			RTW_INFO("RM: report_detail=%d\n",
				prm->q.opt.bcn.rep_detail);
#endif
			break;

		case bcn_req_last_bcn_rpt_ind:
			prm->q.opt.bcn.rep_last_bcn_ind = pbody[p+2];
#if (RM_MORE_DBG_MSG)
			RTW_INFO("RM: bcn_req_last_bcn_rpt_ind=%d\n",
				prm->q.opt.bcn.rep_last_bcn_ind);
#endif
			break;

		case bcn_req_req:
			RTW_INFO("RM: bcn_req_req\n");

			prm->q.opt.bcn.req_start = rtw_malloc(pbody[p+1]);

			if (prm->q.opt.bcn.req_start == NULL) {
				RTW_ERR("RM: req_start malloc fail!!\n");
				break;
			}

			for (i = 0; i < pbody[p+1]; i++)
				*((prm->q.opt.bcn.req_start)+i) =
					pbody[p+2+i];

			prm->q.opt.bcn.req_len = pbody[p+1];
			popt_id[prm->q.opt.bcn.opt_id_num++] = pbody[p];
			break;

		case bcn_req_ap_ch_rep:
#if (RM_MORE_DBG_MSG)
			RTW_INFO("RM: bcn_req_ap_ch_rep\n");
#endif
			if (ap_ch_rpt_idx > BCN_REQ_OPT_AP_CH_RPT_MAX_NUM) {
				RTW_ERR("RM: bcn_req_ap_ch_rep over size\n");
				break;
			}
			popt_id[prm->q.opt.bcn.opt_id_num++] = pbody[p];

			/* get channel list
			 * EID:len:op-class:ch-list
			 */
			op = rtw_malloc(sizeof (*op));
			op->global_op_class = pbody[p + 2];
			i = pbody[p + 1] - 1; /* ch list len; (-1) is op class */

#if (RM_MORE_DBG_MSG)
			RTW_INFO("%d op class %d has %d ch\n",
				ap_ch_rpt_idx,op->global_op_class,i);
#endif
			op->Len = i;
			memcpy(op->Channel, &pbody[p + 3],
				MIN(i, MAX_CH_NUM_IN_OP_CLASS));
			prm->q.opt.bcn.ap_ch_rpt[ap_ch_rpt_idx++] = op;
			prm->q.opt.bcn.ap_ch_rpt_num = ap_ch_rpt_idx;
			break;

		default:
			break;

       		}
		len = len - (int)pbody[p+1] - 2;
		p = p + (int)pbody[p+1] + 2;
#if (RM_MORE_DBG_MSG)
		RTW_INFO("RM: opt_s_elem_len=%d\n",len);
#endif
	}

	return _SUCCESS;
}

static int rm_parse_meas_req(struct rm_obj *prm, u8 *pbody)
{
	int p; /* position */
	int req_len;


	req_len = (int)pbody[1];
	p = 5;

	prm->q.op_class = pbody[p++];
	prm->q.ch_num = pbody[p++];
	prm->q.rand_intvl = le16_to_cpu(*(u16*)(&pbody[p]));
	p+=2;
	prm->q.meas_dur = le16_to_cpu(*(u16*)(&pbody[p]));
	p+=2;

	if (prm->q.m_type == bcn_req) {
		/*
		 * 0: passive
		 * 1: active
		 * 2: bcn_table
		 */
		prm->q.scan_mode = pbody[p++];

		/* BSSID */
		_rtw_memcpy(&(prm->q.bssid), &pbody[p], 6);
		p+=6;

		/*
		 * default, used when Reporting detail subelement
		 * is not included in Beacon Request
		 */
		prm->q.opt.bcn.rep_detail = 2;
	}

	if (req_len-(p-2) <= 0) /* without sub-element */
		return _SUCCESS;

	switch (prm->q.m_type) {
	case bcn_req:
		rm_parse_bcn_req_s_elem(prm, &pbody[p], req_len-(p-2));
		break;
	case ch_load_req:
		rm_parse_ch_load_s_elem(prm, &pbody[p], req_len-(p-2));
		break;
	case noise_histo_req:
		rm_parse_noise_histo_s_elem(prm, &pbody[p], req_len-(p-2));
		break;
	default:
		break;
	}

	return _SUCCESS;
}

/* receive measurement request */
int rm_recv_radio_mens_req(_adapter *padapter,
	union recv_frame *precv_frame, struct sta_info *psta)
{
	struct rm_obj *prm;
	struct rm_priv *prmpriv = &padapter->rmpriv;
	u8 *pdiag_body = (u8 *)(precv_frame->u.hdr.rx_data +
		sizeof(struct rtw_ieee80211_hdr_3addr));
	u8 *pmeas_body = &pdiag_body[5];
	u8 rmid, update = 0;


#if 0
	/* search existing rm_obj */
	rmid = psta->phl_sta->aid << 16
		| pdiag_body[2] << 8
		| RM_SLAVE;

	prm = rm_get_rmobj(padapter, rmid);
	if (prm) {
		RTW_INFO("RM: Found an exist meas rmid=%u\n", rmid);
		update = 1;
	} else
#endif
	prm = rm_alloc_rmobj(padapter);

	if (prm == NULL) {
		RTW_ERR("RM: unable to alloc rm obj for requeset\n");
		return _FALSE;
	}

	prm->psta = psta;
	prm->q.diag_token = pdiag_body[2];
	prm->q.rpt = le16_to_cpu(*(u16*)(&pdiag_body[3]));

	/* Figure 8-104 Measurement Requested format */
	prm->q.e_id = pmeas_body[0];
	prm->q.m_token = pmeas_body[2];
	prm->q.m_mode = pmeas_body[3];
	prm->q.m_type = pmeas_body[4];
	prm->rmid = rm_gen_rmid(padapter, prm, RM_SLAVE);

	RTW_INFO("RM: rmid=%x, bssid " MAC_FMT "\n", prm->rmid,
		MAC_ARG(prm->psta->phl_sta->mac_addr));

#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: element_id = %d\n", prm->q.e_id);
	RTW_INFO("RM: length = %d\n", (int)pmeas_body[1]);
	RTW_INFO("RM: meas_token = %d\n", prm->q.m_token);
	RTW_INFO("RM: meas_mode = %d\n", prm->q.m_mode);
	RTW_INFO("RM: meas_type = %d\n", prm->q.m_type);
#endif

	if (prm->q.e_id != _MEAS_REQ_IE_) /* 38 */
		return _FALSE;

	switch (prm->q.m_type) {
	case bcn_req:
		RTW_INFO("RM: recv beacon_request\n");
		switch (prm->q.scan_mode) {
		case bcn_req_passive:
			rm_en_cap_chk_and_set(prm, RM_BCN_PASSIVE_MEAS_CAP_EN);
			break;
		case bcn_req_active:
			rm_en_cap_chk_and_set(prm, RM_BCN_ACTIVE_MEAS_CAP_EN);
			break;
		case bcn_req_bcn_table:
			rm_en_cap_chk_and_set(prm, RM_BCN_TABLE_MEAS_CAP_EN);
			break;
		default:
			rm_set_rep_mode(prm, MEAS_REP_MOD_INCAP);
			break;
		}
		break;
	case ch_load_req:
		RTW_INFO("RM: recv ch_load_request\n");
		rm_en_cap_chk_and_set(prm, RM_CH_LOAD_CAP_EN);
		break;
	case noise_histo_req:
		RTW_INFO("RM: recv noise_histogram_request\n");
		rm_en_cap_chk_and_set(prm, RM_NOISE_HISTO_CAP_EN);
		break;
	default:
		RTW_INFO("RM: recv unknown request type 0x%02x\n",
			prm->q.m_type);
		rm_set_rep_mode(prm, MEAS_REP_MOD_INCAP);
		goto done;
       }
	rm_parse_meas_req(prm, pmeas_body);
done:
	if (!update)
		rm_enqueue_rmobj(padapter, prm, _FALSE);

	return _SUCCESS;
}

/* receive measurement report */
int rm_recv_radio_mens_rep(_adapter *padapter,
	union recv_frame *precv_frame, struct sta_info *psta)
{
	int ret = _FALSE;
	struct rm_obj *prm;
	u32 rmid, len;
	u8 *pdiag_body = (u8 *)(precv_frame->u.hdr.rx_data +
		sizeof(struct rtw_ieee80211_hdr_3addr));
	u8 *pmeas_body = &pdiag_body[3];


	rmid = psta->phl_sta->aid << 16
		| pdiag_body[2] << 8
		| RM_MASTER;

	prm = rm_get_rmobj(padapter, rmid);
	if (prm == NULL) {
		/* not belong to us, report to upper */
		rtw_cfg80211_rx_rrm_action(psta->padapter, precv_frame);
		return _TRUE;
	}

	prm->p.action_code = pdiag_body[1];
	prm->p.diag_token = pdiag_body[2];

	/* Figure 8-140 Measuremnt Report format */
	prm->p.e_id = pmeas_body[0];
	prm->p.m_token = pmeas_body[2];
	prm->p.m_mode = pmeas_body[3];
	prm->p.m_type = pmeas_body[4];

	RTW_INFO("RM: rmid=%x, bssid " MAC_FMT "\n", prm->rmid,
		MAC_ARG(prm->psta->phl_sta->mac_addr));

#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: element_id = %d\n", prm->p.e_id);
	RTW_INFO("RM: length = %d\n", (int)pmeas_body[1]);
	RTW_INFO("RM: meas_token = %d\n", prm->p.m_token);
	RTW_INFO("RM: meas_mode = %d\n", prm->p.m_mode);
	RTW_INFO("RM: meas_type = %d\n", prm->p.m_type);
#endif
	if (prm->p.e_id != _MEAS_RSP_IE_) /* 39 */
		return _FALSE;

	RTW_INFO("RM: recv %s\n", rm_type_rep_name(prm->p.m_type));
	rm_post_event(padapter, prm->rmid, RM_EV_recv_rep);

	/* report to upper via ioctl */
	if ((prm->from_ioctl == true) &&
		prm->q.m_type == bcn_req) {
		len = pmeas_body[1] + 2; /* 2 : EID(1B)  length(1B) */
		indicate_beacon_report(prm->psta->phl_sta->mac_addr,
			1, len, pmeas_body);
	}

	return ret;
}

/* receive link measurement request */
int rm_recv_link_mens_req(_adapter *padapter,
	union recv_frame *precv_frame, struct sta_info *psta)
{
	struct rm_obj *prm;
	struct rm_priv *prmpriv = &padapter->rmpriv;
	u8 *pdiag_body = (u8 *)(precv_frame->u.hdr.rx_data +
		sizeof(struct rtw_ieee80211_hdr_3addr));
	u8 *pmeas_body = &pdiag_body[3];
	u8 rmid, update = 0;
	int i;


	prm = rm_alloc_rmobj(padapter);

	if (prm == NULL) {
		RTW_ERR("RM: unable to alloc rm obj for requeset\n");
		return _FALSE;
	}

	prm->psta = psta;
	prm->q.action_code = pdiag_body[1];
	prm->q.diag_token = pdiag_body[2];

	prm->q.tx_pwr_used = pmeas_body[0];
	prm->q.tx_pwr_max = pmeas_body[1];
	prm->q.rx_pwr = precv_frame->u.hdr.attrib.phy_info.rx_power;
	prm->q.rx_rate = precv_frame->u.hdr.attrib.data_rate;
	prm->q.rx_bw = precv_frame->u.hdr.attrib.bw;
	prm->q.rx_rsni = rm_get_frame_rsni(prm, precv_frame);
	prm->rmid = rm_gen_rmid(padapter, prm, RM_SLAVE);

	RTW_INFO("RM: rmid=%x, bssid" MAC_FMT " rx_pwr=%ddBm, rate=%s\n",
		prm->rmid, MAC_ARG(prm->psta->phl_sta->mac_addr), prm->q.rx_pwr,
		MGN_RATE_STR(prm->q.rx_rate));

#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: tx_pwr_used =%d dBm\n", prm->q.tx_pwr_used);
	RTW_INFO("RM: tx_pwr_max  =%d dBm\n", prm->q.tx_pwr_max);
#endif

	if (!update)
		rm_enqueue_rmobj(padapter, prm, _FALSE);

	return _SUCCESS;
}

/* receive link measurement report */
int rm_recv_link_mens_rep(_adapter *padapter,
	union recv_frame *precv_frame, struct sta_info *psta)
{
	int ret = _FALSE;
	struct rm_obj *prm;
	u32 rmid;
	u8 *pdiag_body = (u8 *)(precv_frame->u.hdr.rx_data +
		sizeof(struct rtw_ieee80211_hdr_3addr));
	u8 *pmeas_body = pdiag_body + 3;
	s8 val;


	rmid = psta->phl_sta->aid << 16
		| pdiag_body[2] << 8
		| RM_MASTER;

	prm = rm_get_rmobj(padapter, rmid);
	if (prm == NULL) {
		/* not belong to us, report to upper */
		rtw_cfg80211_rx_rrm_action(psta->padapter, precv_frame);
		return _TRUE;
	}

	RTW_INFO("RM: rmid=%x, bssid " MAC_FMT "\n", prm->rmid,
		MAC_ARG(prm->psta->phl_sta->mac_addr));

	prm->p.action_code = pdiag_body[1];
	prm->p.diag_token = pdiag_body[2];

#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: action_code = %d\n", prm->p.action_code);
	RTW_INFO("RM: diag_token  = %d\n", prm->p.diag_token);
	RTW_INFO("RM: xmit_power  = %d dBm\n", pmeas_body[2]);
	RTW_INFO("RM: link_margin = %d dBm\n", pmeas_body[3]);
	RTW_INFO("RM: xmit_ant    = %d\n", pmeas_body[4]);
	RTW_INFO("RM: recv_ant    = %d\n", pmeas_body[5]);
	RTW_INFO("RM: RCPI        = %d\n", pmeas_body[6]);
	RTW_INFO("RM: RSNI        = %d\n", pmeas_body[7]);
#endif
	RTW_INFO("RM: recv link meas report ...\n");
	ret = rm_post_event(padapter, prm->rmid, RM_EV_recv_rep);

	return ret;
}


int rm_radio_mens_nb_rep(_adapter *padapter,
	union recv_frame *precv_frame, struct sta_info *psta)
{
	u8 *pdiag_body = (u8 *)(precv_frame->u.hdr.rx_data +
		sizeof(struct rtw_ieee80211_hdr_3addr));
	u8 *pmeas_body = &pdiag_body[3];
	u32 len = precv_frame->u.hdr.len;
	u32 rmid;
	struct rm_obj *prm;


	rmid = psta->phl_sta->aid << 16
		| pdiag_body[2] << 8
		| RM_MASTER;

	prm = rm_get_rmobj(padapter, rmid);

	if (prm == NULL) {
		/* not belong to us, report to upper */
		rtw_cfg80211_rx_rrm_action(psta->padapter, precv_frame);
		return _TRUE;
	}

	prm->p.action_code = pdiag_body[1];
	prm->p.diag_token = pdiag_body[2];
	prm->p.e_id = pmeas_body[0];

	RTW_INFO("RM: rmid=%x, bssid " MAC_FMT "\n", prm->rmid,
		MAC_ARG(prm->psta->phl_sta->mac_addr));

#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: element_id = %d\n", prm->p.e_id);
	RTW_INFO("RM: length = %d\n", (int)pmeas_body[1]);
#endif
	rm_post_event(padapter, prm->rmid, RM_EV_recv_rep);

#ifdef CONFIG_RTW_MBO
#ifdef CONFIG_LAYER2_ROAMING
	if (rtw_wnm_btm_candidates_survey(padapter
			,(pdiag_body + 3)
			,(len - sizeof(struct rtw_ieee80211_hdr_3addr))
			,_FALSE) == _FAIL)
		return _FALSE;
#endif
#endif
	rtw_cfg80211_rx_rrm_action(padapter, precv_frame);

	return _TRUE;
}

unsigned int rm_on_action(_adapter *padapter, union recv_frame *precv_frame)
{
	u32 ret = _FAIL;
	u8 *pframe = NULL;
	u8 *pframe_body = NULL;
	u8 action_code = 0;
	u8 diag_token = 0;
	struct rtw_ieee80211_hdr_3addr *whdr;
	struct sta_info *psta;


	pframe = precv_frame->u.hdr.rx_data;

	/* check RA matches or not */
	if (!_rtw_memcmp(adapter_mac_addr(padapter),
		GetAddr1Ptr(pframe), ETH_ALEN))
		goto exit;

	whdr = (struct rtw_ieee80211_hdr_3addr *)pframe;
	RTW_INFO("RM: %s bssid = " MAC_FMT "\n",
		__func__, MAC_ARG(whdr->addr2));

	psta = rtw_get_stainfo(&padapter->stapriv, whdr->addr2);

        if (!psta) {
		RTW_ERR("RM: psta not found\n");
                goto exit;
        }

	pframe_body = (unsigned char *)(pframe +
		sizeof(struct rtw_ieee80211_hdr_3addr));

	/* Figure 8-438 radio measurement request frame Action field format */
	/* Category = pframe_body[0] = 5 (Radio Measurement) */
	action_code = pframe_body[1];
	diag_token = pframe_body[2];

#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: %s radio_action=%x, diag_token=%x\n", __func__,
		action_code, diag_token);
#endif

	switch (action_code) {

	case RM_ACT_RADIO_MEAS_REQ:
		RTW_INFO("RM: RM_ACT_RADIO_MEAS_REQ\n");
		ret = rm_recv_radio_mens_req(padapter, precv_frame, psta);
		break;

	case RM_ACT_RADIO_MEAS_REP:
		RTW_INFO("RM: RM_ACT_RADIO_MEAS_REP\n");
		ret = rm_recv_radio_mens_rep(padapter, precv_frame, psta);
		break;

	case RM_ACT_LINK_MEAS_REQ:
		RTW_INFO("RM: RM_ACT_LINK_MEAS_REQ\n");
		ret = rm_recv_link_mens_req(padapter, precv_frame, psta);
		break;

	case RM_ACT_LINK_MEAS_REP:
		RTW_INFO("RM: RM_ACT_LINK_MEAS_REP\n");
		ret = rm_recv_link_mens_rep(padapter, precv_frame, psta);
		break;

	case RM_ACT_NB_REP_REQ:
		RTW_INFO("RM: RM_ACT_NB_REP_REQ\n");
		break;

	case RM_ACT_NB_REP_RESP:
		RTW_INFO("RM: RM_ACT_NB_REP_RESP\n");
		ret = rm_radio_mens_nb_rep(padapter, precv_frame, psta);
		break;

	default:
		/* TODO reply incabable */
		RTW_ERR("RM: unknown specturm management action %2x\n",
			action_code);
		break;
	}
exit:
	return ret;
}

static u8 *rm_gen_bcn_detail_2_elem(_adapter *padapter, u8 *pframe, u8 frag_id,
	struct rm_obj *prm, u8 **pie, u32 *ie_len, unsigned int *fr_len)
{
	u32 frag_max_len = 255 - *fr_len - 4; /* 4: frag_id */
	int len = *ie_len;
	u8 slen = 0, frag_len = 0, more = 0;
	u8 *ies = *pie;
	u8 id, val8;


	if (prm->q.opt.bcn.rep_last_bcn_ind)
		frag_max_len -= 3;

	/* report_detail = 2 */
	if (frag_id == 0) {
		frag_len += _FIXED_IE_LENGTH_;
		len -= _FIXED_IE_LENGTH_;
	}

	while (len >= 0) {

		id = ies[frag_len];
		slen = (unsigned int)ies[frag_len + 1] + 2;

		if ((frag_len + slen) >= frag_max_len ||
		    frag_len == *ie_len) {
			/* ID */
			val8 = 1; /* reported frame body */
			pframe = rtw_set_fixed_ie(pframe, 1, &val8, fr_len);

			/* LEN */
			pframe = rtw_set_fixed_ie(pframe, 1, &frag_len, fr_len);

			/* frame body */
			pframe = rtw_set_fixed_ie(pframe, frag_len, ies, fr_len);

			goto done;
		}

		len -= slen;
		frag_len += slen;
	}
done:
	*pie = ies + frag_len;

	if (len > 0)
		*ie_len = len; /* remain len */
	else
		*ie_len = 0;

	return pframe;
}

static u8 *rm_gen_bcn_detail_1_elem(_adapter *padapter, u8 *pframe, u8 frag_id,
	struct rm_obj *prm, u8 **ies, u32 *ie_len, unsigned int *fr_len)
{
	unsigned int my_len = 0;
	int j = 0, k, len;
	u8 *plen;
	u8 *ptr;
	u8 val8, eid;

	/* report_detail = 1 */

	/* ID */
	val8 = 1; /* 1:reported frame body */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	plen = pframe;
	val8 = 0;
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* report_detail = 1 */
	/* all fixed lenght fields */
	pframe = rtw_set_fixed_ie(pframe,
		_FIXED_IE_LENGTH_, *ies, &my_len);

	for (j = 0; j < prm->q.opt.bcn.opt_id_num; j++) {
		switch (prm->q.opt.bcn.opt_id[j]) {
		case bcn_req_ssid:
			/* SSID */
#if (RM_MORE_DBG_MSG)
			RTW_INFO("RM: bcn_req_ssid\n");
#endif
			ptr = rtw_get_ie(*ies + _FIXED_IE_LENGTH_, _SSID_IE_,
				&len, *ie_len - _FIXED_IE_LENGTH_);

			if (ptr)
				pframe = rtw_set_ie(pframe, _SSID_IE_, len, ptr, &my_len);
			break;
		case bcn_req_req:
			if (prm->q.opt.bcn.req_start == NULL)
				break;
#if (RM_MORE_DBG_MSG)
			RTW_INFO("RM: bcn_req_req");
#endif
			for (k=0; k<prm->q.opt.bcn.req_len; k++) {
				eid = prm->q.opt.bcn.req_start[k];

				val8 = *ie_len - _FIXED_IE_LENGTH_;
				ptr = rtw_get_ie(*ies + _FIXED_IE_LENGTH_,
					eid, &len, val8);

				if (!ptr)
					continue;
#if (RM_MORE_DBG_MSG)
				switch (eid) {
				case EID_SsId:
					RTW_INFO("RM: EID_SSID\n");
					break;
				case EID_QBSSLoad:
					RTW_INFO("RM: EID_QBSSLoad\n");
					break;
				case EID_HTCapability:
					RTW_INFO("RM: EID_HTCapability\n");
					break;
				case _MDIE_:
					RTW_INFO("RM: EID_MobilityDomain\n");
					break;
				case EID_Vendor:
					RTW_INFO("RM: EID_Vendor\n");
					break;
				default:
					RTW_INFO("RM: EID %d todo\n",eid);
					break;
				}
#endif
				pframe = rtw_set_ie(pframe, eid,
					len, ptr + 2, &my_len);
			} /* for() */
			break;
		case bcn_req_rep_detail:
			RTW_INFO("RM: bcn_req_rep_detail\n");
			break;
		case bcn_req_ap_ch_rep:
			RTW_INFO("RM: bcn_req_ap_ch_rep\n");
			break;
		default:
			RTW_INFO("RM: OPT %d TODO\n",prm->q.opt.bcn.opt_id[j]);
			break;
		}
	}
	/*
	 * update my length
	 * content length does NOT include ID and LEN
	 */
	val8 = my_len - 2;
	rtw_set_fixed_ie(plen, 1, &val8, &j);

	/* update length to caller */
	*fr_len += my_len;

	return pframe;
}

u8 rm_bcn_req_cond_mach(struct rm_obj *prm, struct wlan_network *pnetwork)
{
	u8 val8;


	switch(prm->q.opt.bcn.rep_cond.cond) {
	case bcn_rep_cond_immediately:
		return _SUCCESS;
	case bcn_req_cond_rcpi_greater:
		val8 = rm_get_bcn_rcpi(prm, pnetwork);
		if (val8 > prm->q.opt.bcn.rep_cond.threshold)
			return _SUCCESS;
		break;
	case bcn_req_cond_rcpi_less:
		val8 = rm_get_bcn_rcpi(prm, pnetwork);
		if (val8 < prm->q.opt.bcn.rep_cond.threshold)
			return _SUCCESS;
		break;
	case bcn_req_cond_rsni_greater:
		val8 = rm_get_bcn_rsni(prm, pnetwork);
		if (val8 != 255 && val8 > prm->q.opt.bcn.rep_cond.threshold)
			return _SUCCESS;
		break;
	case bcn_req_cond_rsni_less:
		val8 = rm_get_bcn_rsni(prm, pnetwork);
		if (val8 != 255 && val8 < prm->q.opt.bcn.rep_cond.threshold)
			return _SUCCESS;
		break;
	default:
		RTW_ERR("RM: bcn_req cond %u not support\n",
			prm->q.opt.bcn.rep_cond.cond);
		break;
	}
	return _FALSE;
}

static u8 *rm_gen_bcn_rep_ie (struct rm_obj *prm, u8 last,
	u8 *pframe, struct wlan_network *pnetwork, unsigned int *fr_len)
{
	int snr, i = 0;
	u8 val8, *plen, *ies, frag_id = 0, more;
	u16 val16;
	u32 val32, ie_len;
	u64 val64;
	unsigned int my_len;
	_adapter *padapter = prm->psta->padapter;
	u8 frag_bcn_idx[4] = {0x02, 0x2, 0x1, 0x0};
	u8 last_bcn_ind[3] = {0xa4, 0x1, 0x0};

	ies = pnetwork->network.IEs;

	ie_len = pnetwork->network.IELength;
more:
	my_len = 0;
	plen = pframe + 1;
	pframe = rtw_set_fixed_ie(pframe, 7, &prm->p.e_id, &my_len);

	/* Actual Measurement StartTime */
	val64 = cpu_to_le64(prm->meas_start_time);
	pframe = rtw_set_fixed_ie(pframe, 8, (u8 *)&val64, &my_len);

	/* Measurement Duration */
	val16 = prm->meas_end_time - prm->meas_start_time;
	val16 = cpu_to_le16(val16);
	pframe = rtw_set_fixed_ie(pframe, 2, (u8*)&val16, &my_len);

	/* TODO
	* ReportedFrameInformation:
	* 0 :beacon or probe rsp
	* 1 :pilot frame
	*/
	val8 = 0; /* report frame info */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* RCPI */
	val8 = rm_get_bcn_rcpi(prm, pnetwork);
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* RSNI */
	val8 = rm_get_bcn_rsni(prm, pnetwork);
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* BSSID */
	pframe = rtw_set_fixed_ie(pframe, 6,
		(u8 *)&pnetwork->network.MacAddress, &my_len);

	/*
	 * AntennaID
	 * 0: unknown
	 * 255: multiple antenna (Diversity)
	 */
	val8 = 0;
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* ParentTSF */
	val32 = prm->meas_start_time + pnetwork->network.PhyInfo.free_cnt;
	pframe = rtw_set_fixed_ie(pframe, 4, (u8 *)&val32, &my_len);

	/* Generate Beacon detail */

	/* Reporting Detail values
	 * 0: No fixed length fields or elements
	 * 1: All fixed length fields and any requested elements
	 *    in the Request info element if present
	 * 2: All fixed length fields and elements
	 * 3-255: Reserved
	 */
	if (prm->q.opt.bcn.rep_detail == 1) {
		pframe = rm_gen_bcn_detail_1_elem(padapter, pframe, frag_id,
			prm, &ies, &ie_len, &my_len);

	} else if (prm->q.opt.bcn.rep_detail == 2) {
		pframe = rm_gen_bcn_detail_2_elem(padapter, pframe, frag_id,
			prm, &ies, &ie_len, &my_len);

		/* fragment id num */
		more = (ie_len > 0);
		val8 = more << 7 | frag_id;
		frag_bcn_idx[3] = val8;

		pframe = rtw_set_fixed_ie(pframe, sizeof(frag_bcn_idx), frag_bcn_idx, &my_len);

		if (prm->q.opt.bcn.rep_last_bcn_ind) {
			if (last && !more)
				last_bcn_ind[2] = 1;
			pframe = rtw_set_fixed_ie(pframe,
				sizeof(last_bcn_ind), last_bcn_ind, &my_len);
		}
	}

	/*
	* update my length
	* content length does NOT include ID and LEN
	*/
	val8 = my_len - 2;
	rtw_set_fixed_ie(plen, 1, &val8, &i);

	/* update length to caller */
	*fr_len += my_len;

	if (ie_len && prm->q.opt.bcn.rep_detail == 2 && frag_id < 3) {
		frag_id++;
		goto more;
	}

	return pframe;
}

#if 1
static int rm_match_sub_elem(_adapter *padapter,
	struct rm_obj *prm, struct wlan_network *pnetwork)
{
	WLAN_BSSID_EX *pbss = &pnetwork->network;
	unsigned int my_len;
	int i, j, k, len;
	u8 *plen;
	u8 *ptr;
	u8 eid;


	my_len = 0;
	/* Reporting Detail values
	 * 0: No fixed length fields or elements
	 * 1: All fixed length fields and any requested elements
	 *    in the Request info element if present
	 * 2: All fixed length fields and elements
	 * 3-255: Reserved
	 */

	/* report_detail != 1  */
	if (prm->q.opt.bcn.rep_detail != 1)
		return _TRUE;

	/* report_detail = 1 */

	for (j = 0; j < prm->q.opt.bcn.opt_id_num; j++) {
		switch (prm->q.opt.bcn.opt_id[j]) {
		case bcn_req_ssid:
			/* SSID */
#ifdef RM_MORE_DBG_MSG
			RTW_INFO("RM: bcn_req_ssid\n");
#endif
			if (pbss->Ssid.SsidLength == 0)
				return _FALSE;
			break;
		case bcn_req_req:
			if (prm->q.opt.bcn.req_start == NULL)
				break;
#ifdef RM_MORE_DBG_MSG
			RTW_INFO("RM: bcn_req_req");
#endif
			for (k=0; k<prm->q.opt.bcn.req_len; k++) {
				eid = prm->q.opt.bcn.req_start[k];

				i = pbss->IELength - _FIXED_IE_LENGTH_;
				ptr = rtw_get_ie(pbss->IEs + _FIXED_IE_LENGTH_,
					eid, &len, i);

#ifdef RM_MORE_DBG_MSG
				switch (eid) {
				case EID_SsId:
					RTW_INFO("RM: EID_SSID\n");
					break;
				case EID_QBSSLoad:
					RTW_INFO("RM: EID_QBSSLoad\n");
					break;
				case EID_HTCapability:
					RTW_INFO("RM: EID_HTCapability\n");
					break;
				case _MDIE_:
					RTW_INFO("RM: EID_MobilityDomain\n");
					break;
				case EID_Vendor:
					RTW_INFO("RM: EID_Vendor\n");
					break;
				default:
					RTW_INFO("RM: EID %d todo\n",eid);
					break;
				}
#endif
				if (!ptr) {
					RTW_INFO("RM: EID %d not found\n",eid);
					return _FALSE;
				}
			} /* for() */
			break;
		case bcn_req_rep_detail:
			RTW_INFO("RM: bcn_req_rep_detail\n");
			break;
		case bcn_req_ap_ch_rep:
			RTW_INFO("RM: bcn_req_ap_ch_rep\n");
			break;
		default:
			RTW_INFO("RM: OPT %d TODO\n",prm->q.opt.bcn.opt_id[j]);
			break;
		}
	}
	return _TRUE;
}
#endif

static int retrieve_scan_result(struct rm_obj *prm)
{
	_list *plist, *phead;
	_queue *queue;
	_adapter *padapter = prm->psta->padapter;
	struct rtw_ieee80211_channel *pch_set;
	struct wlan_network *pnetwork = NULL;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	int i, j;
	PWLAN_BSSID_EX pbss;
	unsigned int matched_network;
	int len, my_len;
	u8 last = 0;
	u8 buf_idx, *pbuf = NULL, *tmp_buf = NULL;
	u16 xframe_ext_sz = SZ_XMITFRAME_EXT;


	tmp_buf = rtw_malloc(xframe_ext_sz);
	if (tmp_buf == NULL)
		return 0;

	matched_network = 0;
	queue = &(pmlmepriv->scanned_queue);

	_rtw_spinlock_bh(&(pmlmepriv->scanned_queue.lock));

	phead = get_list_head(queue);
	plist = get_next(phead);

	/* get requested measurement channel set */
	pch_set = prm->q.ch_set;

	/* search scan queue to find requested SSID */
	while (1) {

		if (rtw_end_of_queue_search(phead, plist) == _TRUE)
			break;

		pnetwork = LIST_CONTAINOR(plist, struct wlan_network, list);
		pbss = &pnetwork->network;

#if 0
		RTW_INFO("RM: ch %u ssid %s bssid "MAC_FMT"\n",
			pbss->Configuration.DSConfig, pbss->Ssid.Ssid,
			MAC_ARG(pbss->MacAddress));
		/*
		* report network if requested channel set contains
		* the channel matchs selected network
		*/
		if (rtw_chset_search_ch(adapter_to_chset(padapter),
			pbss->Configuration.DSConfig) < 0) /* not match */
			goto next;

		if (rtw_mlme_band_check(padapter, pbss->Configuration.DSConfig)
			== _FALSE)
			goto next;
#endif
		if (rtw_validate_ssid(&(pbss->Ssid)) == _FALSE)
			goto next;

		/* match bssid */
		if (is_wildcard_bssid(prm->q.bssid) == _FALSE)
			if (_rtw_memcmp(prm->q.bssid,
				pbss->MacAddress, 6) == _FALSE)
				goto next;
		/*
		 * default wildcard SSID. wildcard SSID:
		 * A SSID value (null) used to represent all SSIDs
		 */

		/* match ssid */
		if ((prm->q.opt.bcn.ssid.SsidLength > 0) &&
			_rtw_memcmp(prm->q.opt.bcn.ssid.Ssid,
			pbss->Ssid.Ssid,
			prm->q.opt.bcn.ssid.SsidLength) == _FALSE)
			goto next;

		/* go through measurement requested channels */
		for (i = 0; i < prm->q.ch_set_ch_amount; i++) {
			if ((pch_set[i].hw_value) ==
				(pbss->Configuration.DSConfig)) /* match ch */
				break;
		}
		if (i >= prm->q.ch_set_ch_amount) /* channel mismatch */
			goto next;

		/* match condition */
		if (rm_bcn_req_cond_mach(prm, pnetwork) == _FALSE) {
			RTW_INFO("RM: condition mismatch ch %u ssid %s bssid "MAC_FMT"\n",
				pbss->Configuration.DSConfig, pbss->Ssid.Ssid,
				MAC_ARG(pbss->MacAddress));
			RTW_INFO("RM: condition %u:%u\n",
				prm->q.opt.bcn.rep_cond.cond,
				prm->q.opt.bcn.rep_cond.threshold);
			goto next;
			//continue;
		}

		/* match subelement */
		if (rm_match_sub_elem(padapter, prm, pnetwork) == _FALSE)
			goto next;

		/* Found a matched SSID */
		matched_network++;


		RTW_INFO("RM: ch %u Found %s bssid "MAC_FMT"\n",
			pbss->Configuration.DSConfig, pbss->Ssid.Ssid,
			MAC_ARG(pbss->MacAddress));

		prm->ap[prm->ap_num++] = pnetwork;
		if (prm->ap_num >= MAX_RM_AP_NUM)
			break;
next:
		plist = get_next(plist);
	} /* while() */

	/* generate packet */
	my_len = 0;
	buf_idx = 0;
	for (i = 0; i < prm->ap_num; i++) {
		len = 0;
		last = (i == (prm->ap_num - 1));
		_rtw_memset(tmp_buf, 0, xframe_ext_sz);
		pnetwork = prm->ap[i];
		rm_gen_bcn_rep_ie(prm, last, tmp_buf, pnetwork, &len);
		prm->ap[i] = NULL;
new_packet:
		if (my_len == 0) {
			pbuf = rtw_malloc(xframe_ext_sz);
			if (pbuf == NULL)
				goto fail;
			prm->buf[buf_idx].pbuf = pbuf;
		}

		if ((xframe_ext_sz - (my_len+len+24+4)) > 0) {
			pbuf = rtw_set_fixed_ie(pbuf,
				len, tmp_buf, &my_len);
			prm->buf[buf_idx].len = my_len;
		} else {
			if (my_len == 0) /* not enough space */
				goto fail;

			my_len = 0;
			buf_idx++;

			if (buf_idx >= MAX_RM_PKT_NUM) {
				for (j = i; j < prm->ap_num; j++)
					prm->ap[i] = NULL;
				break;
			}

			goto new_packet;
		}
	}

fail:
	_rtw_spinunlock_bh(&(pmlmepriv->scanned_queue.lock));

	if (tmp_buf)
		rtw_mfree(tmp_buf, xframe_ext_sz);

	RTW_INFO("RM: Found %d matched %s (%d)\n", matched_network,
		prm->q.opt.bcn.ssid.Ssid, buf_idx+1);

	if (prm->buf[buf_idx].pbuf)
		return buf_idx + 1;

	return 0;
}

int issue_beacon_rep(struct rm_obj *prm)
{
	int i, my_len;
	u8 *pframe;
	_adapter *padapter = prm->psta->padapter;
	struct pkt_attrib *pattr;
	struct xmit_frame *pmgntframe;
	struct xmit_priv *pxmitpriv = &(padapter->xmitpriv);
	int pkt_num;
	struct dvobj_priv *dvobj = adapter_to_dvobj(padapter);
	u16 xframe_ext_sz = SZ_XMITFRAME_EXT;

	pkt_num = retrieve_scan_result(prm);

	if (pkt_num == 0) {
		issue_null_reply(prm);
		return _SUCCESS;
	}

	for (i=0;i<pkt_num;i++) {

		pmgntframe = alloc_mgtxmitframe(pxmitpriv);
		if (pmgntframe == NULL) {
			RTW_ERR("RM: %s alloc xmit_frame fail\n",__func__);
			goto fail;
		}
		pattr = &pmgntframe->attrib;
		pframe = build_wlan_hdr(padapter,
			pmgntframe, prm->psta, WIFI_ACTION);
		pframe = rtw_set_fixed_ie(pframe,
			3, &prm->p.category, &pattr->pktlen);

		my_len = 0;
		pframe = rtw_set_fixed_ie(pframe,
			prm->buf[i].len, prm->buf[i].pbuf, &my_len);

		pattr->pktlen += my_len;
		pattr->last_txcmdsz = pattr->pktlen;
		dump_mgntframe(padapter, pmgntframe);
	}
fail:
	/*GEORGIA_TODO_FIXIT*/
	for (i = 0; i < pkt_num; i++) {
		if (prm->buf[i].pbuf) {
			rtw_mfree(prm->buf[i].pbuf, xframe_ext_sz);
			prm->buf[i].pbuf = NULL;
			prm->buf[i].len = 0;
		}
	}
	return _SUCCESS;
}

/* neighbor request */
int issue_nb_req(struct rm_obj *prm)
{
	_adapter *padapter = prm->psta->padapter;
	struct sta_info *psta = prm->psta;
	struct _ADAPTER_LINK *padapter_link = psta->padapter_link;
	struct link_mlme_priv *pmlmepriv = &padapter_link->mlmepriv;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct xmit_frame *pmgntframe = NULL;
	struct pkt_attrib *pattr = NULL;
	u8 val8;
	u8 *pframe = NULL;


	RTW_INFO("RM: %s\n", __func__);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	if (pmgntframe == NULL) {
		RTW_ERR("RM: %s alloc xmit_frame fail\n",__func__);
		return _FALSE;
	}
	pattr = &pmgntframe->attrib;
	pframe = build_wlan_hdr(padapter, pmgntframe, psta, WIFI_ACTION);
	pframe = rtw_set_fixed_ie(pframe,
		3, &prm->q.category, &pattr->pktlen);

	if (prm->q.pssid) {

		u8 sub_ie[64] = {0};
		u8 *pie = &sub_ie[2];

		RTW_INFO("RM: Send NB Req to "MAC_FMT" for(SSID) %s searching\n",
			MAC_ARG(pmlmepriv->cur_network.network.MacAddress),
			pmlmepriv->cur_network.network.Ssid.Ssid);

		val8 = strlen(prm->q.pssid);
		sub_ie[0] = 0; /*SSID*/
		sub_ie[1] = val8;

		_rtw_memcpy(pie, prm->q.pssid, val8);

		pframe = rtw_set_fixed_ie(pframe, val8 + 2,
			sub_ie, &pattr->pktlen);
	} else {

		if (!pmlmepriv->cur_network.network.Ssid.SsidLength)
			RTW_INFO("RM: Send NB Req to "MAC_FMT"\n",
				MAC_ARG(pmlmepriv->cur_network.network.MacAddress));
		else {
			u8 sub_ie[64] = {0};
			u8 *pie = &sub_ie[2];

			RTW_INFO("RM: Send NB Req to "MAC_FMT" for(SSID) %s searching\n",
				MAC_ARG(pmlmepriv->cur_network.network.MacAddress),
				pmlmepriv->cur_network.network.Ssid.Ssid);

			sub_ie[0] = 0; /*SSID*/
			sub_ie[1] = pmlmepriv->cur_network.network.Ssid.SsidLength;

			_rtw_memcpy(pie, pmlmepriv->cur_network.network.Ssid.Ssid,
				pmlmepriv->cur_network.network.Ssid.SsidLength);

			pframe = rtw_set_fixed_ie(pframe,
				pmlmepriv->cur_network.network.Ssid.SsidLength + 2,
				sub_ie, &pattr->pktlen);
		}
	}

	pattr->last_txcmdsz = pattr->pktlen;
	dump_mgntframe(padapter, pmgntframe);

	return _SUCCESS;
}

/* issue link measurement request */
int issue_link_meas_req(struct rm_obj *prm)
{
	_adapter *padapter = prm->psta->padapter;
	struct sta_info *psta = prm->psta;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct xmit_frame *pmgntframe = NULL;
	struct pkt_attrib *pattr = NULL;
	u8 *pframe = NULL;
	s8 pwr_used, path_a_pwr;


	RTW_INFO("RM: %s\n", __func__);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	if (pmgntframe == NULL) {
		RTW_ERR("RM: %s alloc xmit_frame fail\n",__func__);
		return _FALSE;
	}
	pattr = &pmgntframe->attrib;
	pframe = build_wlan_hdr(padapter, pmgntframe, psta, WIFI_ACTION);

	/* Category, Action code, Dialog token */
	pframe = rtw_set_fixed_ie(pframe,
		3, &prm->q.category, &pattr->pktlen);

	/* xmit power used */
	/* we don't know actual TX power due to RA may change TX rate;
	 * But if we fix TX rate then we can get specific tx power
	 */
	pattr->rate = MGN_6M;
	rm_get_tx_power(padapter, RF_PATH_A, MGN_6M, &pwr_used);
	pframe = rtw_set_fixed_ie(pframe,
		1, &pwr_used, &pattr->pktlen);

	/* Max xmit power */
	rm_get_path_a_max_tx_power(padapter, &path_a_pwr);
	pframe = rtw_set_fixed_ie(pframe,
		1, &path_a_pwr, &pattr->pktlen);

	pattr->last_txcmdsz = pattr->pktlen;
	dump_mgntframe(padapter, pmgntframe);

	return _SUCCESS;
}

/* issue link measurement report */
int issue_link_meas_rep(struct rm_obj *prm)
{
	u8 val8;
	u8 *pframe;
	unsigned int my_len;
	_adapter *padapter = prm->psta->padapter;
	struct _ADAPTER_LINK *padapter_link = GET_PRIMARY_LINK(padapter);
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattr;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct sta_info *psta = prm->psta;
	int i;
	u8 tpc[4];
	s8 pwr_used;


	RTW_INFO("RM: %s\n", __func__);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	if (pmgntframe == NULL) {
		RTW_ERR("RM: ERR %s alloc xmit_frame fail\n",__func__);
		return _FALSE;
	}
	pattr = &pmgntframe->attrib;
	pframe = build_wlan_hdr(padapter, pmgntframe, psta, WIFI_ACTION);
	/* Category, action code, Dialog token */
	pframe = rtw_set_fixed_ie(pframe, 3,
		&prm->p.category, &pattr->pktlen);

	my_len = 0;

	/* TPC report */
	rm_get_tx_power(padapter, padapter_link->mlmeextpriv.chandef.band, MGN_6M, &pwr_used);
	tpc[0] = EID_TPC;
	tpc[1] = 2; /* length */

	/* TX power */
	tpc[2] = pwr_used;

	/* link margin */
	rm_get_rx_sensitivity(padapter, prm->q.rx_bw, prm->q.rx_rate, &pwr_used);
	tpc[3] = prm->q.rx_pwr - pwr_used; /* RX sensitivity */
	pattr->rate = MGN_6M; /* use fix rate to get fixed RX sensitivity */

#if (RM_MORE_DBG_MSG)
	RTW_INFO("RM: rx_pwr=%ddBm - rx_sensitivity=%ddBm = link_margin=%ddB\n",
		prm->q.rx_pwr, pwr_used, tpc[3]);
#endif
	pframe = rtw_set_fixed_ie(pframe, 4, tpc, &my_len);

	/* RECV antenna ID */
	val8 = 0; /* unknown antenna */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* XMIT antenna ID */
	/* Fix rate 6M(1T) always use main antenna to TX */
	val8 = 1; /* main antenna */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* RCPI */
	val8 = translate_dbm_to_rcpi(prm->q.rx_pwr);
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* RSNI */
	val8 = prm->q.rx_rsni;
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* length */
	//val8 = (u8)my_len-2;
	//rtw_set_fixed_ie(plen, 1, &val8, &i); /* use variable i to ignore it */

	pattr->pktlen += my_len;
	pattr->last_txcmdsz = pattr->pktlen;
	dump_mgntframe(padapter, pmgntframe);

	return _SUCCESS;
}

static u8 *rm_gen_bcn_req_s_elem(_adapter *padapter,
	struct rm_obj *prm, u8 *pframe, unsigned int *fr_len)
{
	u8 val8, l;
	int i;
	unsigned int my_len = 0;
	struct _RT_OPERATING_CLASS *op;


	val8 = bcn_req_active; /* measurement mode T8-64 */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* bssid */
	pframe = rtw_set_fixed_ie(pframe, 6, prm->q.bssid, &my_len);

	/*
	 * opt ssid (0)
	 */
	l = MIN(32, (int)prm->q.opt.bcn.ssid.SsidLength);

	l = (int)prm->q.opt.bcn.ssid.SsidLength;

	if (l > 32)
		RTW_ERR("RM: %s SSID len over size %d! skip it!\n",__func__, l);

	if (l > 0 && l <= 32) {
		/* Type */
		val8 = bcn_req_ssid;
		pframe = rtw_set_fixed_ie(pframe, 1,
			&val8, &my_len);
		/* Len */
		pframe = rtw_set_fixed_ie(pframe, 1,
			&l, &my_len);
		/* Value */
		pframe = rtw_set_fixed_ie(pframe, l,
			prm->q.opt.bcn.ssid.Ssid, &my_len);
	}

	/*
	 * opt reporting detail (2)
	 */
	/* Type */
	val8 = bcn_req_rep_detail;
	pframe = rtw_set_fixed_ie(pframe, 1,
		&val8, &my_len);
	/* Len */
	l = 1;
	pframe = rtw_set_fixed_ie(pframe, 1,
		&l, &my_len);
	/* Value */
	pframe = rtw_set_fixed_ie(pframe, l,
		&prm->q.opt.bcn.rep_detail, &my_len);

	/*
	 * opt request (10)
	 */

	if (prm->q.opt.bcn.req_id_num > 0) {
		/* Type */
		val8 = bcn_req_req;
		pframe = rtw_set_fixed_ie(pframe, 1,
			&val8, &my_len);
		/* Len */
		l = prm->q.opt.bcn.req_id_num;
		pframe = rtw_set_fixed_ie(pframe, 1,
			&l, &my_len);
		/* Value */
		pframe = rtw_set_fixed_ie(pframe, l,
			prm->q.opt.bcn.req_id, &my_len);
	}

	/*
	 * opt ap channel report (51)
	 */
	for (i = 0; i < prm->q.opt.bcn.ap_ch_rpt_num; i++) {
		op = prm->q.opt.bcn.ap_ch_rpt[i];
		if (op == NULL)
			break;
		/* Type */
		val8 = bcn_req_ap_ch_rep;
		pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);
		l = (u8)op->Len + 1;
		/* length */
		pframe = rtw_set_fixed_ie(pframe, 1, &l, &my_len);

		/* op class */
		val8 = op->global_op_class;
		pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);
		/* channel */
		pframe = rtw_set_fixed_ie(pframe, op->Len, op->Channel, &my_len);
	}

	/* update length to caller */
	*fr_len += my_len;

	/* optional subelements */
	return pframe;
}

static u8 *rm_gen_ch_load_req_s_elem(_adapter *padapter,
	u8 *pframe, unsigned int *fr_len)
{
	u8 val8;
	unsigned int my_len = 0;


	val8 = 1; /* 1: channel load T8-60 */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	val8 = 2; /* channel load length = 2 (extensible)  */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	val8 = 0; /* channel load condition : 0 (issue when meas done) T8-61 */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	val8 = 0; /* channel load reference value : 0 */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* update length to caller */
	*fr_len += my_len;

	return pframe;
}

static u8 *rm_gen_noise_histo_req_s_elem(_adapter *padapter,
	u8 *pframe, unsigned int *fr_len)
{
	u8 val8;
	unsigned int my_len = 0;


	val8 = 1; /* 1: noise histogram T8-62 */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	val8 = 2; /* noise histogram length = 2 (extensible)  */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	val8 = 0; /* noise histogram condition : 0 (issue when meas done) T8-63 */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	val8 = 0; /* noise histogram reference value : 0 */
	pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);

	/* update length to caller */
	*fr_len += my_len;

	return pframe;
}

int issue_radio_meas_req(struct rm_obj *prm)
{
	u8 val8;
	u8 *pframe;
	u8 *plen;
	u16 val16;
	int my_len, i;
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattr;
	_adapter *padapter = prm->psta->padapter;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;


	RTW_INFO("RM: %s - %s\n", __func__, rm_type_req_name(prm->q.m_type));

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	if (pmgntframe == NULL) {
		RTW_ERR("RM: %s alloc xmit_frame fail\n",__func__);
		return _FALSE;
	}
	pattr = &pmgntframe->attrib;
	pframe = build_wlan_hdr(padapter, pmgntframe, prm->psta, WIFI_ACTION);

	/* Category, Action code, Dialog token */
	pframe = rtw_set_fixed_ie(pframe, 3, &prm->q.category, &pattr->pktlen);

	/* repeat */
	val16 = cpu_to_le16(prm->q.rpt);
	pframe = rtw_set_fixed_ie(pframe, 2,
		(unsigned char *)&(val16), &pattr->pktlen);

	my_len = 0;
	plen = pframe + 1;

	/* Element ID, Length, Meas token, Meas Mode, Meas type, op class, ch */
	pframe = rtw_set_fixed_ie(pframe, 7, &prm->q.e_id, &my_len);

	/* random interval */
	val16 = cpu_to_le16(prm->q.rand_intvl); /* TU */
	pframe = rtw_set_fixed_ie(pframe, 2, (u8 *)&val16, &my_len);

	/* measurement duration */
	val16 = cpu_to_le16(prm->q.meas_dur);
	pframe = rtw_set_fixed_ie(pframe, 2, (u8 *)&val16, &my_len);

	/* optional subelement */
	switch (prm->q.m_type) {
	case bcn_req:
		pframe = rm_gen_bcn_req_s_elem(padapter, prm,  pframe, &my_len);
		break;
	case ch_load_req:
		pframe = rm_gen_ch_load_req_s_elem(padapter, pframe, &my_len);
		break;
	case noise_histo_req:
		pframe = rm_gen_noise_histo_req_s_elem(padapter,
			pframe, &my_len);
		break;
	case basic_req:
	default:
		break;
	}

	/* length */
	val8 = (u8)my_len - 2;
	rtw_set_fixed_ie(plen, 1, &val8, &i);

	pattr->pktlen += my_len;

	pattr->last_txcmdsz = pattr->pktlen;
	dump_mgntframe(padapter, pmgntframe);

	return _SUCCESS;
}

int rm_radio_meas_report_cond(struct rm_obj *prm)
{
	u8 val8;
	int i, ret = _FAIL;


	switch (prm->q.m_type) {
	case ch_load_req:
		val8 = prm->p.ch_load;
		switch (prm->q.opt.clm.rep_cond.cond) {
		case ch_load_cond_immediately:
			ret = _SUCCESS;
			break;
		case ch_load_cond_anpi_equal_greater:
			if (val8 >= prm->q.opt.clm.rep_cond.threshold)
				ret = _SUCCESS;
			break;
		case ch_load_cond_anpi_equal_less:
			if (val8 <= prm->q.opt.clm.rep_cond.threshold)
				ret = _SUCCESS;
			break;
		default:
			break;
		}
		break;
	case noise_histo_req:
		val8 = prm->p.anpi;
		switch (prm->q.opt.nhm.rep_cond.cond) {
		case noise_histo_cond_immediately:
			ret = _SUCCESS;
			break;
		case noise_histo_cond_anpi_equal_greater:
			if (val8 >= prm->q.opt.nhm.rep_cond.threshold)
				ret = _SUCCESS;
			break;
		case noise_histo_cond_anpi_equal_less:
			if (val8 <= prm->q.opt.nhm.rep_cond.threshold)
				ret = _SUCCESS;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return ret;
}

int retrieve_radio_meas_result(struct rm_obj *prm)
{
#ifdef CONFIG_RTW_ACS
	struct dvobj_priv *dvobj = adapter_to_dvobj(prm->psta->padapter);
#endif
	int i, ch = -1;
	u8 val8;


	ch = rtw_chset_search_ch(adapter_to_chset(prm->psta->padapter),
		prm->q.ch_num);

	if ((ch == -1) || (ch >= MAX_CHANNEL_NUM)) {
		RTW_ERR("RM: get ch(CH:%d) fail\n", prm->q.ch_num);
		ch = 0;
	}

	switch (prm->q.m_type) {
	case ch_load_req:
#if 0 /* def CONFIG_RTW_ACS */
		val8 = hal_data->acs.clm_ratio[ch];
#else
		val8 = 0;
#endif
		prm->p.ch_load = val8;
		break;
	case noise_histo_req:
#if 0 /* def CONFIG_RTW_ACS */
		/* ANPI */
		prm->p.anpi = hal_data->acs.nhm_ratio[ch];

		/* IPI 0~10 */
		for (i=0;i<11;i++)
			prm->p.ipi[i] = hal_data->acs.nhm[ch][i];
#else
		val8 = 0;
		prm->p.anpi = val8;
		for (i=0;i<11;i++)
			prm->p.ipi[i] = val8;
#endif
		break;
	default:
		break;
	}
	return _SUCCESS;
}

int issue_radio_meas_rep(struct rm_obj *prm)
{
	u8 val8 = 0;
	u8 *pframe = NULL;
	u8 *plen = NULL;
	u16 val16 = 0;
	u64 val64 = 0;
	unsigned int my_len = 0;
	_adapter *padapter = prm->psta->padapter;
	struct xmit_frame *pmgntframe = NULL;
	struct pkt_attrib *pattr = NULL;
	struct xmit_priv *pxmitpriv = &(padapter->xmitpriv);
	struct sta_info *psta = prm->psta;
	int i = 0;


	RTW_INFO("RM: %s\n", __func__);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	if (pmgntframe == NULL) {
		RTW_ERR("RM: ERR %s alloc xmit_frame fail\n",__func__);
		return _FALSE;
	}
	pattr = &pmgntframe->attrib;
	pframe = build_wlan_hdr(padapter, pmgntframe, psta, WIFI_ACTION);
	pframe = rtw_set_fixed_ie(pframe, 3,
		&prm->p.category, &pattr->pktlen);

	my_len = 0;
	plen = pframe + 1;
	pframe = rtw_set_fixed_ie(pframe, 7, &prm->p.e_id, &my_len);

	/* Actual Meas start time - 8 bytes */
	val64 = cpu_to_le64(prm->meas_start_time);
	pframe = rtw_set_fixed_ie(pframe, 8, (u8 *)&val64, &my_len);

	/* measurement duration */
	val16 = prm->meas_end_time - prm->meas_start_time;
	val16 = cpu_to_le16(val16);
	pframe = rtw_set_fixed_ie(pframe, 2, (u8 *)&val16, &my_len);

	/* optional subelement */
	switch (prm->q.m_type) {
	case ch_load_req:
		val8 = prm->p.ch_load;
		pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);
		break;
	case noise_histo_req:
		/*
		 * AntennaID
		 * 0: unknown
		 * 255: multiple antenna (Diversity)
		 */
		val8 = 0;
		pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);
		/* ANPI */
		val8 = prm->p.anpi;
		pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);
		/* IPI 0~10 */
		for (i=0;i<11;i++) {
			val8 = prm->p.ipi[i];
			pframe = rtw_set_fixed_ie(pframe, 1, &val8, &my_len);
		}
		break;
	default:
		break;
	}
	/* length */
	val8 = (u8)my_len-2;
	rtw_set_fixed_ie(plen, 1, &val8, &i); /* use variable i to ignore it */

	pattr->pktlen += my_len;
	pattr->last_txcmdsz = pattr->pktlen;
	dump_mgntframe(padapter, pmgntframe);

	return _SUCCESS;
}

void rtw_ap_parse_sta_rm_en_cap(_adapter *padapter,
	struct sta_info *psta, struct rtw_ieee802_11_elems *elem)
{
	if (elem->rm_en_cap) {
		RTW_INFO("assoc.rm_en_cap="RM_CAP_FMT"\n",
			RM_CAP_ARG(elem->rm_en_cap));

		_rtw_memcpy(psta->rm_en_cap, (elem->rm_en_cap),
			MIN(elem->rm_en_cap_len, sizeof(psta->rm_en_cap)));
	}
}

void RM_IE_handler(_adapter *padapter, PNDIS_802_11_VARIABLE_IEs pIE)
{
	int i;

	_rtw_memcpy(&padapter->rmpriv.rm_en_cap_assoc, pIE->data,
		    MIN(pIE->Length, sizeof(padapter->rmpriv.rm_en_cap_assoc)));
	RTW_INFO("assoc.rm_en_cap="RM_CAP_FMT"\n", RM_CAP_ARG(pIE->data));
}

/* Debug command */

#if (RM_SUPPORT_IWPRIV_DBG)
static int hex2num(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return -1;
}

int hex2byte(const char *hex)
{
	int a, b;
	a = hex2num(*hex++);
	if (a < 0)
		return -1;
	b = hex2num(*hex++);
	if (b < 0)
		return -1;
	return (a << 4) | b;
}

static char * hwaddr_parse(char *txt, u8 *addr)
{
	size_t i;

	for (i = 0; i < ETH_ALEN; i++) {
		int a;

		a = hex2byte(txt);
		if (a < 0)
			return NULL;
		txt += 2;
		addr[i] = a;
		if (i < ETH_ALEN - 1 && *txt++ != ':')
			return NULL;
	}
	return txt;
}

void rm_dbg_list_sta(_adapter *padapter, char *s)
{
	int i;
	struct sta_info *psta;
	struct sta_priv *pstapriv = &padapter->stapriv;
	_list *plist, *phead;


	sprintf(pstr(s), "\n");
	_rtw_spinlock_bh(&pstapriv->sta_hash_lock);
	for (i = 0; i < NUM_STA; i++) {
		phead = &(pstapriv->sta_hash[i]);
		plist = get_next(phead);

		while ((rtw_end_of_queue_search(phead, plist)) == _FALSE) {
			psta = LIST_CONTAINOR(plist,
				struct sta_info, hash_list);

			plist = get_next(plist);

			sprintf(pstr(s), "=========================================\n");
			sprintf(pstr(s), "mac=" MAC_FMT "\n",
				MAC_ARG(psta->phl_sta->mac_addr));
			sprintf(pstr(s), "state=0x%x, aid=%d, macid=%d\n",
				psta->state, psta->phl_sta->aid, psta->phl_sta->macid);
			sprintf(pstr(s), "rm_cap="RM_CAP_FMT"\n",
				RM_CAP_ARG(psta->rm_en_cap));
		}

	}
	_rtw_spinunlock_bh(&pstapriv->sta_hash_lock);
	sprintf(pstr(s), "=========================================\n");
}

void rm_dbg_help(_adapter *padapter, char *s)
{
	int i;


	sprintf(pstr(s), "\n");
	sprintf(pstr(s), "rrm list_sta\n");
	sprintf(pstr(s), "rrm list_meas\n");

	sprintf(pstr(s), "rrm add_meas <aid=1|mac=>,m=<bcn|clm|nhm|nb|link>,rpt=\n");
	sprintf(pstr(s), "rrm run_meas <aid=1|evid=>\n");
	sprintf(pstr(s), "rrm del_meas\n");

	sprintf(pstr(s), "rrm run_meas rmid=xxxx,ev=xx\n");
	sprintf(pstr(s), "rrm activate\n");

	for (i=0;i<RM_EV_max;i++)
		sprintf(pstr(s), "\t%2d %s\n",i, rm_event_name(i) );
	sprintf(pstr(s), "\n");
}

struct sta_info *rm_get_sta(_adapter *padapter, u16 aid, u8* pbssid)
{
	int i;
	struct sta_info *psta = NULL;
	struct sta_priv *pstapriv = &padapter->stapriv;
	_list *plist, *phead;


	_rtw_spinlock_bh(&pstapriv->sta_hash_lock);

	for (i = 0; i < NUM_STA; i++) {
		phead = &(pstapriv->sta_hash[i]);
		plist = get_next(phead);

		while ((rtw_end_of_queue_search(phead, plist)) == _FALSE) {
			psta = LIST_CONTAINOR(plist,
				struct sta_info, hash_list);

			plist = get_next(plist);

			if (psta->phl_sta->aid == aid)
				goto done;

			if (pbssid && _rtw_memcmp(psta->phl_sta->mac_addr,
				pbssid, 6))
				goto done;
		}

	}
	psta = NULL;
done:
	_rtw_spinunlock_bh(&pstapriv->sta_hash_lock);
	return psta;
}

static int rm_dbg_modify_meas(_adapter *padapter, char *s)
{
	struct rm_priv *prmpriv = &padapter->rmpriv;
	struct mlme_ext_info *pmlmeinfo = &padapter->mlmeextpriv.mlmext_info;
	struct rm_obj *prm;
	struct sta_info *psta;
	char *pmac, *ptr, *paid, *prpt, *pnbp, *pclm, *pnhm, *pbcn, *plnk;
	unsigned val;
	u8 bssid[ETH_ALEN];
	int i;

	/* example :
	* rrm add_meas <aid=1|mac=>,m=<nb|clm|nhm|bcn|link>,<rept=>
	* rrm run_meas <aid=1|evid=>
	*/
	paid = strstr(s, "aid=");
	pmac = strstr(s, "mac=");
	pbcn = strstr(s, "m=bcn");
	pclm = strstr(s, "m=clm");
	pnhm = strstr(s, "m=nhm");
	pnbp = strstr(s, "m=nb");
	plnk = strstr(s, "m=link");
	prpt = strstr(s, "rpt=");

	/* set all ',' to NULL (end of line) */
	ptr = s;
	while (ptr) {
		ptr = strchr(ptr, ',');
		if (ptr) {
			*(ptr) = 0x0;
			ptr++;
		}
	}
	prm = (struct rm_obj *)prmpriv->prm_sel;
	prm->q.m_token = rm_gen_meas_token(padapter);
	psta = prm->psta;

	for (i=0;i<6;i++)
		prm->q.bssid[i] = 0xff; /* wildcard bssid */
	if (paid) { /* find sta_info according to aid */
		paid += 4; /* skip aid= */
		sscanf(paid, "%u", &val); /* aid=x */
		psta = rm_get_sta(padapter, val, NULL);

	} else if (pmac) { /* find sta_info according to bssid */
		pmac += 4; /* skip mac= */
		if (hwaddr_parse(pmac, bssid) == NULL) {
			sprintf(pstr(s), "Err: \nincorrect mac format\n");
			return _FAIL;
		}
		psta = rm_get_sta(padapter, 0xff, bssid);
	}

	if (psta) {
		prm->psta = psta;

		prm->q.diag_token = rm_gen_dialog_token(padapter);
		prm->rmid = rm_gen_rmid(padapter, prm, RM_MASTER);
	} else
		return _FAIL;

	prm->q.action_code = RM_ACT_RADIO_MEAS_REQ;
	if (pbcn) {
		prm->q.m_type = bcn_req;
		prm->q.rand_intvl = le16_to_cpu(100);
		prm->q.meas_dur = le16_to_cpu(100);
	} else if (pnhm) {
		prm->q.m_type = noise_histo_req;
	} else if (pclm) {
		prm->q.m_type = ch_load_req;
	} else if (pnbp) {
		prm->q.action_code = RM_ACT_NB_REP_REQ;
	} else if (plnk) {
		prm->q.action_code = RM_ACT_LINK_MEAS_REQ;
	} else
		return _FAIL;

	if (prpt) {
		prpt += 4; /* skip rpt= */
		sscanf(prpt, "%u", &val);
		prm->q.rpt = (u8)val;
	}

	return _SUCCESS;
}

static void rm_dbg_activate_meas(_adapter *padapter, char *s)
{
	struct rm_priv *prmpriv = &(padapter->rmpriv);
	struct rm_obj *prm;
	/* ToDo CONFIG_RTW_MLD: [currently primary link only] */
	struct _ADAPTER_LINK *padapter_link = GET_PRIMARY_LINK(padapter);


	if (prmpriv->prm_sel == NULL) {
		sprintf(pstr(s), "\nErr: No inActivate measurement\n");
		return;
	}
	prm = (struct rm_obj *)prmpriv->prm_sel;

	/* verify attributes */
	if (prm->psta == NULL) {
		sprintf(pstr(s), "\nErr: inActivate meas has no psta\n");
		return;
	}

	/* measure current channel */
	prm->q.ch_num = padapter_link->mlmeextpriv.chandef.chan;
	prm->q.op_class = rtw_get_op_class_by_bchbw(padapter_link->mlmeextpriv.chandef.band,
		prm->q.ch_num, CHANNEL_WIDTH_20, CHAN_OFFSET_NO_EXT);

	/* enquee rmobj */
	rm_enqueue_rmobj(padapter, prm, _FALSE);

	sprintf(pstr(s), "\nActivate rmid=%x, state=%s, meas_type=%s\n",
		prm->rmid, rm_state_name(prm->state),
		rm_type_req_name(prm->q.m_type));

	sprintf(pstr(s), "aid=%d, mac=" MAC_FMT "\n",
		prm->psta->phl_sta->aid, MAC_ARG(prm->psta->phl_sta->mac_addr));

	/* clearn inActivate prm info */
	prmpriv->prm_sel = NULL;
}

/* for ioctl */
int rm_send_bcn_reqs(_adapter *padapter, u8 *sta_addr, u8 op_class, u8 ch,
	u16 measure_duration, u8 measure_mode, u8 *bssid, u8 *ssid,
	u8 reporting_detail,
	u8 n_ap_ch_rpt, struct _RT_OPERATING_CLASS *rpt,
	u8 n_elem_id, u8 *elem_id_list)
{
	struct rm_obj *prm;
	char *pact;
	struct sta_info *psta;
	struct _RT_OPERATING_CLASS *prpt;
	void *ptr;
	int i,j,sz;
	u8 bcast[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};


	if (n_ap_ch_rpt > BCN_REQ_OPT_AP_CH_RPT_MAX_NUM) {
		RTW_ERR("RM: chset num %d > %d\n",
			n_ap_ch_rpt, BCN_REQ_OPT_AP_CH_RPT_MAX_NUM);
		return -1;
	}
	/* dest sta */
	psta = rtw_get_stainfo(&padapter->stapriv, sta_addr);
        if (!psta) {
		RTW_ERR("RM: psta not found\n");
		return -2;
        }
	prm = rm_alloc_rmobj(padapter);
	if (prm == NULL) {
		RTW_ERR("RM: unable to alloc rm obj for requeset\n");
		return -3;
	}

	prm->psta = psta;
	prm->q.meas_dur = measure_duration;

	/* Figure 8-104 Measurement Requested format */
	prm->q.category = RTW_WLAN_CATEGORY_RADIO_MEAS;
	prm->q.action_code = RM_ACT_RADIO_MEAS_REQ;
	prm->q.m_mode = measure_mode;
	prm->q.m_type = bcn_req;
	prm->q.diag_token = rm_gen_dialog_token(padapter);
	prm->q.m_token = rm_gen_meas_token(padapter);
	prm->rmid = rm_gen_rmid(padapter, prm, RM_MASTER);

	prm->q.e_id = _MEAS_REQ_IE_; /* 38 */
	prm->q.ch_num = ch;
	prm->q.op_class = op_class;
	prm->from_ioctl = true;

	if (bssid != NULL)
		memcpy(prm->q.bssid, bssid, ETH_ALEN);
	else
		memcpy(prm->q.bssid, bcast, ETH_ALEN);

	if (ssid != NULL) {
		i = MIN(32, strlen(ssid));
		prm->q.opt.bcn.ssid.SsidLength = i;
		memcpy(prm->q.opt.bcn.ssid.Ssid, ssid, i);
	}

	if (n_ap_ch_rpt > 0) {
		prm->q.opt.bcn.ap_ch_rpt_num = n_ap_ch_rpt;
		j = 0;
		for (i = 0; i < n_ap_ch_rpt; i++) {
			prpt = rpt++;
			if (prpt == NULL)
				break;

			sz = sizeof(struct _RT_OPERATING_CLASS) * prpt->Len;
			ptr = rtw_malloc(sz);
			_rtw_memcpy(ptr, prpt, sz);
			prm->q.opt.bcn.ap_ch_rpt[i] = (struct _RT_OPERATING_CLASS *)ptr;
		}
	}
	prm->q.opt.bcn.rep_detail = reporting_detail;

	if ((n_elem_id > 0) && (n_elem_id < BCN_REQ_REQ_OPT_MAX_NUM)) {
		prm->q.opt.bcn.req_id_num = n_elem_id;
		_rtw_memcpy(prm->q.opt.bcn.req_id, elem_id_list, n_elem_id);
	}

	/* enquee rmobj */
	rm_enqueue_rmobj(padapter, prm, _FALSE);

	RTW_INFO("\nAdd rmid=%x, meas_type=%s ok\n",
		prm->rmid, rm_type_req_name(prm->q.m_type));

	if (prm->psta)
		RTW_INFO("mac="MAC_FMT"\n", MAC_ARG(prm->psta->phl_sta->mac_addr));
	return 0;
}

void indicate_beacon_report(u8 *sta_addr,
	u8 n_measure_rpt, u32 elem_len, u8 *elem)
{
	RTW_INFO("RM: recv bcn reprot from mac="MAC_FMT"\n", MAC_ARG(sta_addr));
}

static void rm_dbg_add_meas(_adapter *padapter, char *s)
{
	struct rm_priv *prmpriv = &(padapter->rmpriv);
	struct rm_obj *prm;
	char *pact;


	/* example :
	* rrm add_meas <aid=1|mac=>,m=<nb|clm|nhm|link>
	* rrm run_meas <aid=1|evid=>
	*/
	prm = (struct rm_obj *)prmpriv->prm_sel;
	if (prm == NULL)
		prm = rm_alloc_rmobj(padapter);

	if (prm == NULL) {
		sprintf(pstr(s), "\nErr: alloc meas fail\n");
		return;
	}

        prmpriv->prm_sel = prm;

	pact = strstr(s, "act");
	if (rm_dbg_modify_meas(padapter, s) == _FAIL) {

		sprintf(pstr(s), "\nErr: add meas fail\n");
		rm_free_rmobj(prm);
		prmpriv->prm_sel = NULL;
		return;
	}
	prm->q.category = RTW_WLAN_CATEGORY_RADIO_MEAS;
	prm->q.e_id = _MEAS_REQ_IE_; /* 38 */

	sprintf(pstr(s), "\nAdd rmid=%x, meas_type=%s ok\n",
		prm->rmid, rm_type_req_name(prm->q.m_type));

	if (prm->psta)
		sprintf(pstr(s), "mac="MAC_FMT"\n",
			MAC_ARG(prm->psta->phl_sta->mac_addr));

	if (pact)
		rm_dbg_activate_meas(padapter, pstr(s));
}

static void rm_dbg_del_meas(_adapter *padapter, char *s)
{
	struct rm_priv *prmpriv = &padapter->rmpriv;
	struct rm_obj *prm = (struct rm_obj *)prmpriv->prm_sel;


	if (prm) {
		sprintf(pstr(s), "\ndelete rmid=%x\n",prm->rmid);

		/* free inActivate meas - enqueue yet  */
		prmpriv->prm_sel = NULL;
		rtw_mfree(prmpriv->prm_sel, sizeof(struct rm_obj));
	} else
		sprintf(pstr(s), "Err: no inActivate measurement\n");
}

static void rm_dbg_run_meas(_adapter *padapter, char *s)
{
	struct rm_obj *prm;
	char *pevid, *prmid;
	u32 rmid, evid;


	prmid = strstr(s, "rmid="); /* hex */
	pevid = strstr(s, "evid="); /* dec */

	if (prmid && pevid) {
		prmid += 5; /* rmid= */
		sscanf(prmid, "%x", &rmid);

		pevid += 5; /* evid= */
		sscanf(pevid, "%u", &evid);
	} else {
		sprintf(pstr(s), "\nErr: incorrect attribute\n");
		return;
	}

	prm = rm_get_rmobj(padapter, rmid);

	if (!prm) {
		sprintf(pstr(s), "\nErr: measurement not found\n");
		return;
	}

	if (evid >= RM_EV_max) {
		sprintf(pstr(s), "\nErr: wrong event id\n");
		return;
	}

	rm_post_event(padapter, prm->rmid, evid);
	sprintf(pstr(s), "\npost %s to rmid=%x\n",rm_event_name(evid), rmid);
}

static void rm_dbg_show_meas(struct rm_obj *prm, char *s)
{
	struct sta_info *psta;

	psta = prm->psta;

	if (prm->q.action_code == RM_ACT_RADIO_MEAS_REQ) {

		sprintf(pstr(s), "\nrmid=%x, meas_type=%s\n",
			prm->rmid, rm_type_req_name(prm->q.m_type));

	} else  if (prm->q.action_code == RM_ACT_NB_REP_REQ) {

		sprintf(pstr(s), "\nrmid=%x, action=neighbor_req\n",
			prm->rmid);
	} else
		sprintf(pstr(s), "\nrmid=%x, action=unknown\n",
			prm->rmid);

	if (psta)
		sprintf(pstr(s), "aid=%d, mac="MAC_FMT"\n",
			psta->phl_sta->aid, MAC_ARG(psta->phl_sta->mac_addr));

	sprintf(pstr(s), "clock=%d, state=%s, rpt=%u/%u\n",
		(int)ATOMIC_READ(&prm->pclock->counter),
		rm_state_name(prm->state), prm->p.rpt, prm->q.rpt);
}

static void rm_dbg_list_meas(_adapter *padapter, char *s)
{
	int meas_amount;
	struct rm_obj *prm;
	struct sta_info *psta;
	struct rm_priv *prmpriv = &padapter->rmpriv;
	_queue *queue = &prmpriv->rm_queue;
	_list *plist, *phead;
	unsigned long sp_flags;

	sprintf(pstr(s), "\n");
	_rtw_spinlock_irq(&queue->lock, &sp_flags);
	phead = get_list_head(queue);
	plist = get_next(phead);
	meas_amount = 0;

	while ((rtw_end_of_queue_search(phead, plist)) == _FALSE) {
		prm = LIST_CONTAINOR(plist, struct rm_obj, list);
		meas_amount++;
		plist = get_next(plist);
		psta = prm->psta;
		sprintf(pstr(s), "=========================================\n");

		rm_dbg_show_meas(prm, s);
	}
	_rtw_spinunlock_irq(&queue->lock, &sp_flags);

	sprintf(pstr(s), "=========================================\n");

	if (meas_amount==0) {
		sprintf(pstr(s), "No Activate measurement\n");
		sprintf(pstr(s), "=========================================\n");
	}

	if (prmpriv->prm_sel == NULL)
		sprintf(pstr(s), "\nNo inActivate measurement\n");
	else {
		sprintf(pstr(s), "\ninActivate measurement\n");
		rm_dbg_show_meas((struct rm_obj *)prmpriv->prm_sel, s);
	}
}
#endif /* RM_SUPPORT_IWPRIV_DBG */

int verify_bcn_req(_adapter *padapter, struct sta_info *psta)
{
	char *bssid =  NULL;
	char ssid[] = "RealKungFu";
	u8 op_class = 0;
	u8 ch = 255;
	u16 measure_duration = 100;
	u8 reporting_detaial = 0;
	u8 n_ap_ch_rpt = 6;
	u8 measure_mode = bcn_req_active;
	u8 req[] = {1,2,3};
	u8 req_len = sizeof(req);


	static RT_OPERATING_CLASS US[] = {
	/* 0, OP_CLASS_NULL */	//{  0,  0, {}},
	/* 1, OP_CLASS_1 */	{115,  4, {36, 40, 44, 48}},
	/* 2, OP_CLASS_2 */	{118,  4, {52, 56, 60, 64}},
	/* 3, OP_CLASS_3 */	{124,  4, {149, 153, 157, 161}},
	/* 4, OP_CLASS_4 */	{121, 11, {100, 104, 108, 112, 116, 120, 124,
						128, 132, 136, 140}},
	/* 5, OP_CLASS_5 */	{125,  5, {149, 153, 157, 161, 165}},
	/* 6, OP_CLASS_12 */	{ 81, 11, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}}
	};

	rm_send_bcn_reqs(padapter, psta->phl_sta->mac_addr, op_class, ch,
		measure_duration, measure_mode, bssid, ssid,
		reporting_detaial, n_ap_ch_rpt, US, req_len, req);
	return 0;
}

void rm_dbg_cmd(_adapter *padapter, char *s)
{
	unsigned val;
	char *paid;
	struct sta_info *psta=NULL;

#if (RM_SUPPORT_IWPRIV_DBG)
	if (_rtw_memcmp(s, "help", 4)) {
		rm_dbg_help(padapter, s);

	} else if (_rtw_memcmp(s, "send_bcn_req", 12)) {

		/* rtwpriv wls1 rrm send_bcn_req aid=1 */
		paid = strstr(s, "aid=");
		if (paid) { /* find sta_info according to aid */
			paid += 4; /* skip aid= */
			sscanf(paid, "%u", &val); /* aid=x */
			psta = rm_get_sta(padapter, val, NULL);

			if (psta)
				verify_bcn_req(padapter, psta);
		}

	} else if (_rtw_memcmp(s, "list_sta", 8)) {
		rm_dbg_list_sta(padapter, s);

	} else if (_rtw_memcmp(s, "list_meas", 9)) {
		rm_dbg_list_meas(padapter, s);

	} else if (_rtw_memcmp(s, "add_meas", 8)) {
		rm_dbg_add_meas(padapter, s);

	} else if (_rtw_memcmp(s, "del_meas", 8)) {
		rm_dbg_del_meas(padapter, s);

	} else if (_rtw_memcmp(s, "activate", 8)) {
		rm_dbg_activate_meas(padapter, s);

	} else if (_rtw_memcmp(s, "run_meas", 8)) {
		rm_dbg_run_meas(padapter, s);

	} else if (_rtw_memcmp(s, "nb", 2)) {

		paid = strstr(s, "aid=");

		if (paid) { /* find sta_info according to aid */
			paid += 4; /* skip aid= */
			sscanf(paid, "%u", &val); /* aid=x */
			psta = rm_get_sta(padapter, val, NULL);

			if (psta)
				rm_add_nb_req(padapter, psta);
		}
	}
#else
	sprintf(pstr(s), "\n");
	sprintf(pstr(s), "rrm debug command was disabled\n");
#endif
}
#endif /* CONFIG_RTW_80211K */

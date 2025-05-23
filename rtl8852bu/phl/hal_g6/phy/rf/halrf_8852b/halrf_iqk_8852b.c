/******************************************************************************
 *
 * Copyright(c) 2007 - 2020  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/
#include "../halrf_precomp.h"

#ifdef RF_8852B_SUPPORT

#ifndef __iram_func__
#define __iram_func__
#endif


const u32 array_set_nondbcc_path01_8852b[] = {
//02_BB_AFE_Non_DBCC_PHY0_path01
	0x20fc, 0xffff0000, 0x0303,
	0x5864, 0x18000000, 0x3,
	0x7864, 0x18000000, 0x3,
	0x12b8, 0x40000000, 0x1,
	0x32b8, 0x40000000, 0x1,
	0x030c, 0xff000000, 0x13,
	0x032c, 0xffff0000, 0x0041,
	0x12b8, 0x10000000, 0x1,
	0x58c8, 0x01000000, 0x1,
	0x78c8, 0x01000000, 0x1,
	0x5864, 0xc0000000, 0x3,
	0x7864, 0xc0000000, 0x3,
	0x2008, 0x01ffffff, 0x1ffffff,
	0x0c1c, 0x00000004, 0x1,
	0x0700, 0x08000000, 0x1,
	0x0c70, 0x000003ff, 0x3ff,
	0x0c60, 0x00000003, 0x3,
	0x0c6c, 0x00000001, 0x1,
	0x58ac, 0x08000000, 0x1,
	0x78ac, 0x08000000, 0x1,
	0x0c3c, 0x00000200, 0x1,
	0x2344, 0x80000000, 0x1,
	0x4490, 0x80000000, 0x1,
//	0x12a0, 0x00007000, 0x7,
//	0x12a0, 0x00008000, 0x1,
//	0x12a0, 0x00070000, 0x3,
//	0x12a0, 0x00080000, 0x1,
//	0x32a0, 0x00070000, 0x3,
//	0x32a0, 0x00080000, 0x1,
	0x0700, 0x01000000, 0x1,
	0x0700, 0x06000000, 0x2,
	0x20fc, 0xffff0000, 0x3333,
};

const u32 array_restore_nondbcc_path01_8852b[] = {
//99_BB_AFE_Non_DBCC_PHY0_path01_restore
	0x20fc, 0xffff0000, 0x0303,
	0x12b8, 0x40000000, 0x0,
	0x32b8, 0x40000000, 0x0,
	0x5864, 0xc0000000, 0x0,
	0x7864, 0xc0000000, 0x0,
	0x2008, 0x01ffffff, 0x0000000,
	0x0c1c, 0x00000004, 0x0,
	0x0700, 0x08000000, 0x0,
	0x0c70, 0x0000001f, 0x03,
	0x0c70, 0x000003e0, 0x03,
	0x12a0, 0x000ff000, 0x00,
	0x32a0, 0x000ff000, 0x00,
	0x0700, 0x07000000, 0x0,
	0x20fc, 0xffff0000, 0x0000,
	0x58c8, 0x01000000, 0x0,
	0x78c8, 0x01000000, 0x0,
	0x0c3c, 0x00000200, 0x0,
	0x2344, 0x80000000, 0x0,
};

__iram_func__
void iqk_backup_rf0_8852b(
	struct rf_info *rf, u8 path,
	u32 backup_rf0[rf_reg_num_8852b],
	u32 backup_rf_reg0[rf_reg_num_8852b])
{
	u8 i;

	if(path != RF_PATH_A)
		return;
	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	for (i = 0; i < rf_reg_num_8852b; i++) {
		backup_rf0[i] = halrf_rrf(rf, RF_PATH_A, backup_rf_reg0[i], MASKRF);		
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]bk rf0, %x = %x\n", backup_rf_reg0[i], backup_rf0[i]);
	}	
	return;
}

__iram_func__
void iqk_backup_rf1_8852b(
	struct rf_info *rf, u8 path,
	u32 backup_rf1[rf_reg_num_8852b],
	u32 backup_rf_reg1[rf_reg_num_8852b])
{
	u8 i;

	if(path != RF_PATH_B)
		return;

	//DBG_LOG_SERIOUS(DBGMSG_RF, DBG_WARNING, "[IQK] 06 \n");
	for (i = 0; i < rf_reg_num_8852b; i++) {
		backup_rf1[i] = halrf_rrf(rf, RF_PATH_B, backup_rf_reg1[i], MASKRF);		
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]bk rf1, %x = %x\n", backup_rf_reg1[i], backup_rf1[i]);
	}	
	return;
}

__iram_func__
void iqk_restore_rf0_8852b(
	struct rf_info *rf, u8 path,
	u32 backup_rf0[rf_reg_num_8852b],
	u32 backup_rf_reg0[rf_reg_num_8852b])
{
	u32 i = 0;
	
	if(path != RF_PATH_A)
		return;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);	
	//DBG_LOG_SERIOUS(DBGMSG_RF, DBG_WARNING, "[IQK] 13 \n");
	for (i = 0; i < rf_reg_num_8852b; i++) {
		halrf_wrf(rf, RF_PATH_A, backup_rf_reg0[i], MASKRF, backup_rf0[i]);
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]restore rf0, 0x%x = 0x%x\n", backup_rf_reg0[i], halrf_rrf(rf, 0x0, backup_rf_reg0[i], MASKRF));
	}
	return;
}

__iram_func__
void iqk_restore_rf1_8852b(
	struct rf_info *rf, u8 path,
	u32 backup_rf1[rf_reg_num_8852b],
	u32 backup_rf_reg1[rf_reg_num_8852b])
{
	u32 i;
	
	if(path != RF_PATH_B)
		return;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	for (i = 0; i < rf_reg_num_8852b; i++) {
		halrf_wrf(rf, RF_PATH_B, backup_rf_reg1[i], MASKRF, backup_rf1[i]);		
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]restore rf S%d = %x, value = %x\n", path, backup_rf_reg[path][i], halrf_rrf(rf, path, backup_rf_reg[path][i], MASKRF));
	}
	return;
}

#if 0
static void _iqk_config_8852b_reg(struct rf_info *rf, u32 *array_map)
{
	u32	i = 0;
	u32	array_len = 0x0;
	u32 *array = NULL;
	u32	addr = 0, mask = 0,  val = 0;	
	
	RF_DBG(rf, DBG_RF_INIT, "===> %s\n", __func__);
	array_len = sizeof(array_map) / sizeof(u32);
	array = (u32 *) &array_map;
	while ((i + 1) < array_len) {
		addr = array[i];
		mask = array[i + 1];
		val = array[i + 2];
		halrf_wreg(rf, addr, mask, val);		
		RF_DBG(rf, DBG_RF_IQK, "[IQK]0x%x[%x] = 0x%x\n", addr, mask, val);
		i += 3;
	}

}
#endif

__iram_func__
static void _iqk_read_fft_dbcc0_8852b(struct rf_info *rf, u8 path)
{
	u8 i = 0x0;
	u32 fft[6] = {0x0};

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x00160000);
	fft[0] = halrf_rreg(rf, 0x80fc, MASKDWORD);
	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x00170000);
	fft[1] = halrf_rreg(rf, 0x80fc, MASKDWORD);
	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x00180000);
	fft[2] = halrf_rreg(rf, 0x80fc, MASKDWORD);
	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x00190000);
	fft[3] = halrf_rreg(rf, 0x80fc, MASKDWORD);
	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x001a0000);
	fft[4] = halrf_rreg(rf, 0x80fc, MASKDWORD);
	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x001b0000);
	fft[5] = halrf_rreg(rf, 0x80fc, MASKDWORD);
	for(i =0; i< 6; i++)
		RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x,fft[%x]= %x\n", path, i, fft[i]);

	return;
}

__iram_func__
static void _iqk_read_xym_dbcc0_8852b(struct rf_info *rf, u8 path)
{
	u8 i = 0x0;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	halrf_wreg(rf, 0x8000, 0x00000006, path);
	halrf_wreg(rf, 0x801c, 0x00000003, 0x1);

	for (i = 0x0; i < 0x18; i++) {
		halrf_wreg(rf, 0x8014, MASKDWORD, 0x000000c0 + i);
		halrf_wreg(rf, 0x8014, MASKDWORD, 0x00000000);
		RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, 0x8%x38 = %x\n",
			path, 1 << path, halrf_rreg(rf, 0x8138 + (path << 8), MASKDWORD));
		halrf_delay_us(rf, 1);
	}
	halrf_wreg(rf, 0x801c, 0x00000003, 0x0);
	halrf_wreg(rf, 0x8138+ (path << 8), MASKDWORD, 0x40000000);
	halrf_wreg(rf, 0x8014, MASKDWORD, 0x80010100);
	halrf_delay_us(rf, 1);

	return;
}

__iram_func__
static void _iqk_read_txcfir_dbcc0_8852b(struct rf_info *rf, u8 path, u8 group)
{
	u8 idx = 0x0;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);


	halrf_wreg(rf, 0x81d8 + (path << 8), MASKDWORD, 0x00000001);
	if (path == 0x0) {
		switch (group) {
		case 0:
			for (idx = 0; idx < 0x0d; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK] %x = %x\n", 0x8f20 + (idx << 2), 
					halrf_rreg(rf, 0x8f20 + (idx << 2), MASKDWORD));
			}
			break;
		case 1:
			for (idx = 0; idx < 0x0d; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK] %x = %x\n", 0x8f54 + (idx << 2),
					halrf_rreg(rf, 0x8f54 + (idx << 2), MASKDWORD));
			}
			break;
		case 2:
			for (idx = 0; idx < 0x0d; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK] %x = %x\n", 0x8f88 + (idx << 2),
					halrf_rreg(rf, 0x8f88 + (idx << 2), MASKDWORD));
			}
			break;
		case 3:
			for (idx = 0; idx < 0x0d; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK] %x = %x\n", 0x8fbc + (idx << 2),
					halrf_rreg(rf, 0x8fbc + (idx << 2), MASKDWORD));
			}
			break;
		default:
			break;
		}
		RF_DBG(rf, DBG_RF_IQK, "[IQK]\n");
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x8f50 = %x\n", halrf_rreg(rf, 0x8f50, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x8f84 = %x\n", halrf_rreg(rf, 0x8f84, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x8fb8 = %x\n", halrf_rreg(rf, 0x8fb8, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x8fec = %x\n", halrf_rreg(rf, 0x8fec, MASKDWORD));
	} else {
		switch (group) {
		case 0:
			for (idx = 0; idx < 0x0d; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK] %x = %x\n", 0x9320 + (idx << 2),
					halrf_rreg(rf, 0x9320 + (idx << 2), MASKDWORD));
			}
			break;
		case 1:
			for (idx = 0; idx < 0x0d; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK] %x = %x\n", 0x9354 + (idx << 2),
					halrf_rreg(rf, 0x9354 + (idx << 2), MASKDWORD));
			}
			break;
		case 2:
			for (idx = 0; idx < 0x0d; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK] %x = %x\n", 0x9388 + (idx << 2),
					halrf_rreg(rf, 0x9388 + (idx << 2), MASKDWORD));
			}
			break;
		case 3:
			for (idx = 0; idx < 0x0d; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK] %x = %x\n", 0x93bc + (idx << 2),
					halrf_rreg(rf, 0x93bc + (idx << 2), MASKDWORD));
			}
			break;
		default:
			break;
		}
		RF_DBG(rf, DBG_RF_IQK, "[IQK]\n");
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x9350 = %x\n", halrf_rreg(rf, 0x9350, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x9384 = %x\n", halrf_rreg(rf, 0x9384, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x93b8 = %x\n", halrf_rreg(rf, 0x93b8, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x93ec = %x\n", halrf_rreg(rf, 0x93ec, MASKDWORD));
	}
	halrf_wreg(rf, 0x81d8+ (path << 8), MASKDWORD, 0x00000000);
	halrf_wreg(rf, 0x81d4 + (path << 8), 0x003f0000, 0xc);
	halrf_delay_us(rf, 1);


	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, 0x8%xfc = %x\n",
		path, 1 << path, halrf_rreg(rf, 0x81fc + (path << 8), MASKDWORD));

	return;
}

__iram_func__
static void _iqk_read_rxcfir_dbcc0_8852b(struct rf_info *rf, u8 path, u8 group)
{
	u8 idx = 0x0;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);

	halrf_wreg(rf, 0x81d8 + (path << 8), MASKDWORD, 0x00000001);

	if (path == 0x0) {
		switch (group) {
		case 0:
			for (idx = 0; idx < 0x10; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]%x = %x\n", 0x8d00 + (idx << 2),
					halrf_rreg(rf, 0x8d00 + (idx << 2), MASKDWORD));
			}
			break;
		case 1:
			for (idx = 0; idx < 0x10; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]%x = %x\n", 0x8d44 + (idx << 2),
					halrf_rreg(rf, 0x8d44 + (idx << 2), MASKDWORD));
			}
			break;
		case 2:
			for (idx = 0; idx < 0x10; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]%x = %x\n", 0x8d88 + (idx << 2),
					halrf_rreg(rf, 0x8d88 + (idx << 2), MASKDWORD));
			}
			break;
		case 3:
			for (idx = 0; idx < 0x10; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]%x = %x\n", 0x8dcc + (idx << 2),
					halrf_rreg(rf, 0x8dcc + (idx << 2), MASKDWORD));
			}
			break;
		default:
			break;
		}
		RF_DBG(rf, DBG_RF_IQK, "[IQK]\n");
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x8d40 = %x\n", halrf_rreg(rf, 0x8d40, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x8d84 = %x\n", halrf_rreg(rf, 0x8d84, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x8dc8 = %x\n", halrf_rreg(rf, 0x8dc8, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x8e0c = %x\n", halrf_rreg(rf, 0x8e0c, MASKDWORD));
	} else {
		switch (group) {
		case 0:
			for (idx = 0; idx < 0x10; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]%x = %x\n", 0x9100 + (idx << 2),
					halrf_rreg(rf, 0x9100 + (idx << 2), MASKDWORD));
			}
			break;
		case 1:
			for (idx = 0; idx < 0x10; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]%x = %x\n", 0x9144 + (idx << 2),
					halrf_rreg(rf, 0x9144 + (idx << 2), MASKDWORD));
			}
			break;
		case 2:
			for(idx = 0; idx < 0x10; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]%x = %x\n", 0x9188 + (idx << 2),
					halrf_rreg(rf, 0x9188 + (idx << 2), MASKDWORD));
			}
			break;
		case 3:
			for (idx = 0; idx < 0x10; idx++) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]%x = %x\n", 0x91cc + (idx << 2),
					halrf_rreg(rf, 0x91cc + (idx << 2), MASKDWORD));
			}
			break;
		default:
			break;
		}
		RF_DBG(rf, DBG_RF_IQK, "[IQK]\n");
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x9140 = %x\n", halrf_rreg(rf, 0x9140, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x9184 = %x\n", halrf_rreg(rf, 0x9184, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x91c8 = %x\n", halrf_rreg(rf, 0x91c8, MASKDWORD));
		RF_DBG(rf, DBG_RF_IQK, "[IQK] 0x920c = %x\n", halrf_rreg(rf, 0x920c, MASKDWORD));
	}
	halrf_wreg(rf, 0x81d8 + (path << 8), MASKDWORD, 0x00000000);
	halrf_wreg(rf, 0x81d4 + (path << 8), 0x003f0000, 0xd);

	
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, 0x8%xfc = %x\n",
		path, 1 << path, halrf_rreg(rf, 0x81fc + (path << 8), MASKDWORD));

	return;
}

__iram_func__
static void _iqk_sram_8852b(struct rf_info *rf, u8 path)
{
	u32 i = 0x0;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);

	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x00020000);
	halrf_wreg(rf, 0x80e8, MASKDWORD, 0x00000080);
	halrf_wreg(rf, 0x80d8, MASKDWORD, 0x00010000);
	halrf_wreg(rf, 0x802c, 0x00000fff, 0x009);

	for (i = 0; i <= 0x9f; i++) {
		halrf_wreg(rf, 0x80d8, MASKDWORD, 0x00010000 + i);
		RF_DBG(rf, DBG_RF_IQK, "[IQK]0x%x\n",
			halrf_rreg(rf, 0x80fc, 0x0fff0000));
	}

	for (i = 0; i <= 0x9f; i++) {
		halrf_wreg(rf, 0x80d8, MASKDWORD, 0x00010000 + i);
		RF_DBG(rf, DBG_RF_IQK, "[IQK]0x%x\n",
			halrf_rreg(rf, 0x80fc, 0x00000fff));
	}
	halrf_wreg(rf, 0x80e8, MASKDWORD, 0x00000000);
	halrf_wreg(rf, 0x80d8, MASKDWORD, 0x00000000);

	return;
}

__iram_func__
static void _iqk_rxk_setting_8852b(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u32 tmp = 0x0;
	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	
	tmp = halrf_rrf(rf, path, 0x18, MASKRF);
	
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		halrf_wrf(rf, path, 0x00, 0xf0000, 0xc);
		halrf_wrf(rf, path, 0x20, 0x00100, 0x1);
		halrf_wrf(rf, path, 0x1f, 0xfffff, tmp);
		break;
	case BAND_ON_5G:
		halrf_wrf(rf, path, 0x00, 0xf0000, 0xc);
		halrf_wrf(rf, path, 0x20, 0x00080, 0x1);
		halrf_wrf(rf, path, 0x1f, 0xfffff, tmp);
		break;
	default:
		break;
	}
	return;
}

__iram_func__
static bool _iqk_check_cal_8852b(struct rf_info *rf, u8 path, u8 ktype)
{

	//struct halrf_iqk_info *iqk_info = &rf->iqk;
	struct halrf_rfk_dz_rpt *rfk_dz = &rf->rfk_dz_rpt;
	bool notready = true, fail = true;
	u32 delay_count = 0x0;
	u32 delay_count2 = 0x0;
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	delay_count = 0x0;

#ifdef HALRF_CONFIG_FW_IO_OFLD_SUPPORT
	if (rf->phl_com->dev_cap.io_ofld) {
		if (!halrf_polling_bb(rf, 0xbff8, MASKBYTE0, 0x55, 8200)) {
			RF_DBG(rf, DBG_RF_IQK, "[IQK]NCTL1 IQK timeout!!!\n");
			fail = true;		
			rfk_dz->iqk_dz_code |= DZ_IQK_ALIMTK_TIMEOUT1<< (16 * path);
		} else
			notready = false;
	} else {
		while (notready) {
			if (halrf_rreg(rf, 0xbff8, MASKBYTE0) == 0x55) {
				halrf_delay_us(rf, 10);
				notready = false;
			} else {
				halrf_delay_us(rf, 10);
				delay_count++;
			}
			if (delay_count > 820) {
				fail = true;
				rfk_dz->iqk_dz_code |= DZ_IQK_ALIMTK_TIMEOUT2<< (16 * path);
				RF_DBG(rf, DBG_RF_IQK, "[IQK]NCTL1 IQK timeout!!!\n");
				break;
			}
		}
	}
#else
	while (notready) {
		if (halrf_rreg(rf, 0xbff8, MASKBYTE0) == 0x55) {
			halrf_delay_us(rf, 10);
			notready = false;
		} else {
			halrf_delay_us(rf, 10);
			delay_count++;
		}
		if (delay_count > 820) {
			fail = true;
			rfk_dz->iqk_dz_code |= DZ_IQK_ALIMTK_TIMEOUT2<< (16 * path);
			RF_DBG(rf, DBG_RF_IQK, "[IQK]NCTL1 IQK timeout!!!\n");
			break;
		}
	}
#endif

	notready = true;
    delay_count2 = 0;
	halrf_wreg(rf, 0x80d4, 0x003F0000, 0x03);

#ifdef HALRF_CONFIG_FW_IO_OFLD_SUPPORT
	if (rf->phl_com->dev_cap.io_ofld) {
		if (!halrf_polling_bb(rf, 0x80fc, 0x0000ffff, 0x8000, 200)) {
			RF_DBG(rf, DBG_RF_IQK, "[IQK]NCTL2 IQK timeout!!!\n");
			fail = true;
		} else
			notready = false;
	} else {
		halrf_delay_us(rf, 10);
		while (notready) {
			if (halrf_rreg(rf, 0x80fc, 0x0000ffff) == 0x8000) {
				halrf_delay_us(rf, 10);
				notready = false;
			} else {
				halrf_delay_us(rf, 10);
				delay_count2++;
			}
			if (delay_count2 > 40) {
				fail = true;
				RF_DBG(rf, DBG_RF_IQK, "[IQK]NCTL2 IQK timeout!!!\n");
				break;
			}
		}
	}
#else
	halrf_delay_us(rf, 10);
	while (notready) {
		if (halrf_rreg(rf, 0x80fc, 0x0000ffff) == 0x8000) {
			halrf_delay_us(rf, 10);
			notready = false;
		} else {
			halrf_delay_us(rf, 10);
			delay_count2++;
		}
		if (delay_count2 > 40) {
			fail = true;
			RF_DBG(rf, DBG_RF_IQK, "[IQK]NCTL2 IQK timeout!!!\n");
			break;
		}
	}
#endif

	//if (!notready)
		//fail = (bool)halrf_rreg(rf, 0x8008, BIT(26));
	halrf_wreg(rf, 0x8010, MASKBYTE0, 0x0);

	//DBG_LOG_SERIOUS(DBGMSG_RF, DBG_WARNING, "[IQK]%x\n", delay_count);

	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, cnt1 = %d, cnt2 = %d, type= %x, fail = %x\n", path, delay_count, delay_count2, ktype, notready);

	return notready;
}

__iram_func__
static bool _iqk_one_shot_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
				 u8 path, u8 ktype)
{

	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool fail = false;
	u32 iqk_cmd = 0x0;
	u8 phy_map;
	u32 addr_rfc_ctl = 0x0;

	phy_map = (BIT(phy_idx) << 4) | BIT(path);

	addr_rfc_ctl = 0x5864;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	//halrf_btc_rfk_ntfy(rf, phy_map, RF_BTC_IQK, RFK_ONESHOT_START);
	switch (ktype) {
	case ID_TXAGC:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d TXAGC ============\n", path);
		iqk_cmd = 0x008 | (1 << (4 + path)) | (path << 1);
		break;
	case ID_FLoK_coarse:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d ID_FLoK_coarse ============\n", path);
		halrf_wreg(rf, addr_rfc_ctl, 0x20000000, 0x1);
		iqk_cmd = 0x108 | (1 << (4 + path));
		break;
	case ID_FLoK_fine:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d ID_FLoK_fine ============\n", path);
		halrf_wreg(rf, addr_rfc_ctl, 0x20000000, 0x1);
		iqk_cmd = 0x208 | (1 << (4 + path));
		break;
	case ID_FLOK_vbuffer:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d ID_FLoK_fine ============\n", path);
		halrf_wreg(rf, addr_rfc_ctl, 0x20000000, 0x1);
		iqk_cmd = 0x308 | (1 << (4 + path));
		break;
	case ID_TXK:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d ID_TXK ============\n", path);
		halrf_wreg(rf, addr_rfc_ctl, 0x20000000, 0x0);
		iqk_cmd = 0x008 | (1 << (path + 4)) | (((0x8 + iqk_info->iqk_bw[path] ) & 0xf) << 8);
		break;
	case ID_RXAGC:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d ID_RXAGC ============\n", path);
		iqk_cmd = 0x508 | (1 << (4 + path)) | (path << 1);
		break;
	case ID_RXK:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d ID_RXK ============\n", path);
		halrf_wreg(rf, addr_rfc_ctl, 0x20000000, 0x1);
		iqk_cmd = 0x008 | (1 << (path + 4)) | (((0xb + iqk_info->iqk_bw[path]) & 0xf) << 8);
		break;
	case ID_NBTXK:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d ID_NBTXK ============\n", path);
		halrf_wreg(rf, addr_rfc_ctl, 0x20000000, 0x0);
		halrf_wreg(rf, 0x802c, 0x00000fff, 0x021);
		iqk_cmd = 0x408 | (1 << (4 + path));
		break;
	case ID_NBRXK:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]============ S%d ID_NBRXK ============\n", path);
		halrf_wreg(rf, addr_rfc_ctl, 0x20000000, 0x1);
		halrf_wreg(rf, 0x802c, 0x0fff0000, 0x011);
		iqk_cmd = 0x608 | (1 << (4 + path));
		break;
	default:
		return false;
		break;
	}
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x,  one-shot id = %x\n", path, iqk_cmd + 1);

	halrf_wreg(rf, 0x8000, MASKDWORD, iqk_cmd + 1);
	//halrf_delay_us(rf, 1);
	//halrf_delay_us(rf, 1);

	fail = _iqk_check_cal_8852b(rf, path, ktype);
	if (iqk_info->iqk_xym_en == true)
		_iqk_read_xym_dbcc0_8852b(rf, path);
	if (iqk_info->iqk_fft_en == true)
		_iqk_read_fft_dbcc0_8852b(rf, path);
	if (iqk_info->iqk_sram_en == true)
		if (ktype == ID_NBRXK || ktype == ID_RXK)
			_iqk_sram_8852b(rf, path);

	if (iqk_info->iqk_cfir_en == true) {
		if (ktype == ID_TXK) {
			_iqk_read_txcfir_dbcc0_8852b(rf, path, 0x0);
			_iqk_read_txcfir_dbcc0_8852b(rf, path, 0x1);
			_iqk_read_txcfir_dbcc0_8852b(rf, path, 0x2);
			_iqk_read_txcfir_dbcc0_8852b(rf, path, 0x3);
		} else {
			_iqk_read_rxcfir_dbcc0_8852b(rf, path, 0x0);
			_iqk_read_rxcfir_dbcc0_8852b(rf, path, 0x1);
			_iqk_read_rxcfir_dbcc0_8852b(rf, path, 0x2);
			_iqk_read_rxcfir_dbcc0_8852b(rf, path, 0x3);
		}
	}

	//8. IQK cotrol RFC
	halrf_wreg(rf, addr_rfc_ctl, 0x20000000, 0x0);

	//halrf_btc_rfk_ntfy(rf, phy_map, RF_BTC_IQK, RFK_ONESHOT_STOP);

	return fail;
}

__iram_func__
static bool _rxk_group_sel_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
				  u8 path)
{
	struct halrf_rfk_dz_rpt *rfk_dz = &rf->rfk_dz_rpt;
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u8 gp = 0x0;
	u32 a_idxrxgain[4] = {0x190, 0x198, 0x350, 0x352};
	u32 a_idxattc2[4] = {0x0f, 0x0f, 0x3f, 0x7f};
	u32 a_idxattc1[4] = {0x3, 0x1, 0x0, 0x0};
	
	u32 g_idxrxgain[4] = {0x212, 0x21c, 0x350, 0x360};
	u32 g_idxattc2[4] = {0x00, 0x00, 0x28, 0x5f};
	u32 g_idxattc1[4] = {0x3, 0x3, 0x2, 0x1};
	bool notready = false;
	bool kfail = false;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);

	for (gp = 0; gp < 0x4; gp++) {
		switch (iqk_info->iqk_band[path]) {
		case BAND_ON_24G:
			halrf_wrf(rf, path, 0x00, 0x03ff0, g_idxrxgain[gp]);
			halrf_wrf(rf, path, 0x20, 0x00100, 0x1);
			halrf_wrf(rf, path, 0x83, 0x1fc00, g_idxattc2[gp]);
			halrf_wrf(rf, path, 0x83, 0x00300, g_idxattc1[gp]);
			break;
		case BAND_ON_5G:
			halrf_wrf(rf, path, 0x00, 0x03ff0, a_idxrxgain[gp]);
			halrf_wrf(rf, path, 0x20, 0x00080, 0x1);
			halrf_wrf(rf, path, 0x8c, 0x0007f, a_idxattc2[gp]);
			halrf_wrf(rf, path, 0x8c, 0x00180, a_idxattc1[gp]);
			break;
		default:
			break;
		}
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000100, 0x1);
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000010, 0x0);
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000007, gp);
		notready = _iqk_one_shot_8852b(rf, phy_idx, path, ID_RXK);
		//halrf_wreg(rf, 0x9fe0, BIT(16 + gp + path * 4), notready);
	}
	halrf_wrf(rf, path, 0x20, 0x00080, 0x0);
	halrf_wrf(rf, path, 0x20, 0x00100, 0x0);
	


	if (!notready)
		kfail = (bool)halrf_rreg(rf, 0x8008, BIT(26));

	if (kfail) {
		iqk_info->nb_rxcfir[path] = 0x40000002;
		halrf_wreg(rf, 0x8124 + (path << 8), 0x0000000f, 0x0);
		iqk_info->is_wb_rxiqk[path] = false;
		rfk_dz->iqk_dz_code |= DZ_RXIQK_ALIMTK  << (16 * path) ;
	} else {
		iqk_info->nb_rxcfir[path] = 0x40000000;
		halrf_wreg(rf, 0x8124 + (path << 8), 0x0000000f, 0x5);
		iqk_info->is_wb_rxiqk[path] = true;
	}
#ifndef HALRF_CONFIG_FW_IO_OFLD_SUPPORT
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, kfail = 0x%x, 0x8%x3c = 0x%x\n", path, kfail, 1 << path, halrf_rreg(rf, 0x813c + (path << 8), MASKDWORD));
#endif
	return kfail;
}

__iram_func__
static bool _iqk_check_nbiqc_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,  u8 ktype, u8 path)
{
	u32 x = 0;
	u32 y = 0;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);

	if(ktype == ID_NBTXK) {
		x = halrf_rreg(rf, 0x8138 + (path << 8), 0xfff00000); 
		y = halrf_rreg(rf, 0x8138 + (path << 8), 0x000fff00);
	} else {
		x = halrf_rreg(rf, 0x813c + (path << 8), 0xfff00000); 
		y = halrf_rreg(rf, 0x813c + (path << 8), 0x000fff00);
	}
	
	
	x = HALRF_ABS(x, 1024);
	if (y > 0x800) 
		y = (0x1000 - y);

	RF_DBG(rf, DBG_RF_IQK, "[IQK] x = %d, y = %d\n", x, y);

	if ( (x > 0x50) ||(y > 0x100))
		return true;
	else
		return false;
}

__iram_func__
static bool _iqk_nbrxk_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
			      u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u8 gp = 0x0;
	u32 a_idxrxgain[4] = {0x190, 0x198, 0x350, 0x352};
	u32 a_idxattc2[4] = {0x0f, 0x0f, 0x3f, 0x7f};
	u32 a_idxattc1[4] = {0x3, 0x1, 0x0, 0x0};
	
	u32 g_idxrxgain[4] = {0x212, 0x21c, 0x350, 0x360};
	u32 g_idxattc2[4] = {0x00, 0x00, 0x28, 0x5f};
	u32 g_idxattc1[4] = {0x3, 0x3, 0x2, 0x1};
	bool notready = false;
	bool kfail = false;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	gp = 0x3;
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		halrf_wrf(rf, path, 0x00, 0x03ff0, g_idxrxgain[gp]);
		halrf_wrf(rf, path, 0x83, 0x1fc00, g_idxattc2[gp]);
		halrf_wrf(rf, path, 0x83, 0x00300, g_idxattc1[gp]);
	break;
	case BAND_ON_5G:
		halrf_wrf(rf, path, 0x00, 0x03ff0, a_idxrxgain[gp]);
		halrf_wrf(rf, path, 0x8c, 0x0007f, a_idxattc2[gp]);
		halrf_wrf(rf, path, 0x8c, 0x00180, a_idxattc1[gp]);
		break;
	default:
		break;
	}
	halrf_wreg(rf, 0x8154 + (path << 8), 0x00000100, 0x1);
	halrf_wreg(rf, 0x8154 + (path << 8), 0x00000010, 0x0);
	//halrf_wreg(rf, 0x8154 + (path << 8), 0x00000008, 0x0);
	halrf_wreg(rf, 0x8154 + (path << 8), 0x00000007, gp);	
	halrf_wrf(rf, path, 0x1e, MASKRF, 0x80013);
	halrf_delay_us(rf, 1);

	notready = _iqk_one_shot_8852b(rf, phy_idx, path, ID_NBRXK);
	//halrf_wreg(rf, 0x9fe0, BIT(16 + gp + path * 4), notready);

	halrf_wrf(rf, path, 0x20, 0x00080, 0x0);
	halrf_wrf(rf, path, 0x20, 0x00100, 0x0);
	
	if (!notready)
		kfail = (bool)halrf_rreg(rf, 0x8008, BIT(26));

	kfail = _iqk_check_nbiqc_8852b(rf, phy_idx, ID_NBRXK, path);

	if (!kfail) {
		iqk_info->nb_rxcfir[path] = halrf_rreg(rf, 0x813c + (path << 8), MASKDWORD) | 0x2;
	} else {
		iqk_info->nb_rxcfir[path] = 0x40000002;
	}
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, kfail = 0x%x, 0x8%x3c = 0x%x\n", path, kfail, 1 << path, iqk_info->nb_rxcfir[path]);

	return kfail;
}

__iram_func__
static void _iqk_rxclk_setting_8852b(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	if (iqk_info->iqk_bw[path] == CHANNEL_WIDTH_80) { //BW80
		//07_CLK_Setting_RxIQK_BW80M_Non_DBCC_PHY0_path01
//		halrf_wreg(rf, 0x12a0, 0x00070000, 0x2);
//		halrf_wreg(rf, 0x12a0, 0x00080000, 0x1);
		halrf_rxck_force_8852b(rf, RF_PATH_A, true, ADC_960M);
//		halrf_wreg(rf, 0x32a0, 0x00070000, 0x2);
//		halrf_wreg(rf, 0x32a0, 0x00080000, 0x1);
		halrf_rxck_force_8852b(rf, RF_PATH_B, true, ADC_960M);
		halrf_delay_us(rf, 1);
		halrf_wreg(rf, 0x12b8, 0x40000000, 0x1);
		halrf_wreg(rf, 0x32b8, 0x40000000, 0x1);
		halrf_delay_us(rf, 1);
		halrf_wreg(rf, 0x030c, 0xff000000, 0x0f);
		halrf_delay_us(rf, 1);
		halrf_wreg(rf, 0x030c, 0xff000000, 0x03);
		halrf_wreg(rf, 0x032c, 0xffff0000, 0xa001);
		halrf_delay_us(rf, 1);
		halrf_wreg(rf, 0x032c, 0xffff0000, 0xa041);
		halrf_wreg(rf, 0x0700, 0x01000000, 0x1);
		halrf_wreg(rf, 0x0700, 0x06000000, 0x1);
	} else {
		//07_CLK_Setting_RxIQK_BW40M_Non_DBCC_PHY0_path01
//		halrf_wreg(rf, 0x12a0, 0x00070000, 0x1);
//		halrf_wreg(rf, 0x12a0, 0x00080000, 0x1);
		halrf_rxck_force_8852b(rf, RF_PATH_A, true, ADC_480M);
//		halrf_wreg(rf, 0x32a0, 0x00070000, 0x1);
//		halrf_wreg(rf, 0x32a0, 0x00080000, 0x1);
		halrf_rxck_force_8852b(rf, RF_PATH_B, true, ADC_480M);
		halrf_delay_us(rf, 1);
		halrf_wreg(rf, 0x12b8, 0x40000000, 0x1);
		halrf_wreg(rf, 0x32b8, 0x40000000, 0x1);
		halrf_delay_us(rf, 1);
		halrf_wreg(rf, 0x030c, 0xff000000, 0x0f);
		halrf_delay_us(rf, 1);
		halrf_wreg(rf, 0x030c, 0xff000000, 0x03);
		halrf_wreg(rf, 0x032c, 0xffff0000, 0xa001);
		halrf_delay_us(rf, 1);
		halrf_wreg(rf, 0x032c, 0xffff0000, 0xa041);
		halrf_wreg(rf, 0x0700, 0x01000000, 0x1);
		halrf_wreg(rf, 0x0700, 0x06000000, 0x0);
	}


	return;
}

__iram_func__
static bool _txk_group_sel_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
				  u8 path)
{
	struct halrf_rfk_dz_rpt *rfk_dz = &rf->rfk_dz_rpt;
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool notready = false;
	bool kfail = false;
	u8 gp = 0x0;
	u32 a_power_range[4] = {0x0, 0x0, 0x0, 0x0};
	u32 a_track_range[4] = {0x3, 0x3, 0x6, 0x6};
	u32 a_gain_bb[4] = {0x08, 0x0e, 0x08, 0x0e};
	u32 a_itqt[4] = {0x09, 0x12, 0x1b, 0x24};
	
	u32 g_power_range[4] = {0x0, 0x0, 0x0, 0x0};
	u32 g_track_range[4] = {0x4, 0x4, 0x6, 0x6};
	u32 g_gain_bb[4] = {0x08, 0x0e, 0x08, 0x0e};
	u32 g_itqt[4] = { 0x09, 0x12, 0x1b, 0x24};

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);	
	
	for (gp = 0x0; gp < 0x4; gp++) {
		switch (iqk_info->iqk_band[path]) {
		case BAND_ON_24G:
			halrf_wrf(rf, path, 0x11, 0x00003, g_power_range[gp]);
			halrf_wrf(rf, path, 0x11, 0x00070, g_track_range[gp]);
			halrf_wrf(rf, path, 0x11, 0x1f000, g_gain_bb[gp]);
			halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, g_itqt[gp]);
			break;
		case BAND_ON_5G:
			halrf_wrf(rf, path, 0x11, 0x00003, a_power_range[gp]);
			halrf_wrf(rf, path, 0x11, 0x00070, a_track_range[gp]);
			halrf_wrf(rf, path, 0x11, 0x1f000, a_gain_bb[gp]);
			halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, a_itqt[gp]);
			break;
		default:
			break;
		}
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000100, 0x1); //man_sel_cfir_lut
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000010, 0x1); //TX=0x1 or RX=0x0
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000004, 0x0); //force to zero
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000003, gp);//remapping as {idx_rfgain, idx_txbb}	
		halrf_wreg(rf, 0x8010, 0x000000ff, 0x00);

		

		notready = _iqk_one_shot_8852b(rf, phy_idx, path, ID_TXK);
		//halrf_wreg(rf, 0x9fe0, BIT(8 + gp + path * 4), notready);
	}
	
	//halrf_write_fwofld_end(rf); 	/*FW Offload End*/

	if (!notready)
		kfail = (bool)halrf_rreg(rf, 0x8008, BIT(26));

	_iqk_read_xym_dbcc0_8852b(rf, path);

	if (kfail) {
		iqk_info->nb_txcfir[path] = 0x40000002;
		halrf_wreg(rf, 0x8124 + (path << 8), 0x00000f00, 0x0);
		iqk_info->is_wb_txiqk[path] = false;
		rfk_dz->iqk_dz_code |= DZ_TXIQK_ALIMTK << (16* path) ;
	} else {
		iqk_info->nb_txcfir[path] = 0x40000000;
		halrf_wreg(rf, 0x8124 + (path << 8), 0x00000f00, 0x5);
		iqk_info->is_wb_txiqk[path] = true;
	}
#ifndef HALRF_CONFIG_FW_IO_OFLD_SUPPORT
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, kfail = 0x%x, 0x8%x38 = 0x%x\n", path, kfail, 1 << path, halrf_rreg(rf, 0x8138 + (path << 8), MASKDWORD));
#endif
	return kfail;
}

__iram_func__
static bool _iqk_nbtxk_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
			      u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool notready = false;
	bool kfail = false;
	u8 gp = 0x0;
	u32 a_power_range[4] = {0x0, 0x0, 0x0, 0x0};
	u32 a_track_range[4] = {0x3, 0x3, 0x6, 0x6};
	u32 a_gain_bb[4] = {0x08, 0x0e, 0x08, 0x0e};
	u32 a_itqt[4] = {0x09, 0x12, 0x1b, 0x24};
	
	u32 g_power_range[4] = {0x0, 0x0, 0x0, 0x0};
	u32 g_track_range[4] = {0x4, 0x4, 0x6, 0x6};
	u32 g_gain_bb[4] = {0x08, 0x0e, 0x08, 0x0e};
	u32 g_itqt[4] = { 0x09, 0x12, 0x1b, 0x24};

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);

	gp = 0x2;
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		halrf_wrf(rf, path, 0x11, 0x00003, g_power_range[gp]);
		halrf_wrf(rf, path, 0x11, 0x00070, g_track_range[gp]);
		halrf_wrf(rf, path, 0x11, 0x1f000, g_gain_bb[gp]);
		halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, g_itqt[gp]);
		break;
	case BAND_ON_5G:
		halrf_wrf(rf, path, 0x11, 0x00003, a_power_range[gp]);
		halrf_wrf(rf, path, 0x11, 0x00070, a_track_range[gp]);
		halrf_wrf(rf, path, 0x11, 0x1f000, a_gain_bb[gp]);
		halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, a_itqt[gp]);
		break;
	default:
		break;
	}
	halrf_wreg(rf, 0x8154 + (path << 8), 0x00000100, 0x1); //man_sel_cfir_lut
	halrf_wreg(rf, 0x8154 + (path << 8), 0x00000010, 0x1); //TX=0x1 or RX=0x0
	halrf_wreg(rf, 0x8154 + (path << 8), 0x00000004, 0x0); //force to zero
	halrf_wreg(rf, 0x8154 + (path << 8), 0x00000003, gp);//remapping as {idx_rfgain, idx_txbb}	
	halrf_wreg(rf, 0x8010, 0x000000ff, 0x00);
	
	notready = _iqk_one_shot_8852b(rf, phy_idx, path, ID_NBTXK);
	//halrf_write_fwofld_end(rf); 	/*FW Offload End*/

	if (!notready) {
		kfail = (bool)halrf_rreg(rf, 0x8008, BIT(26));
		kfail = _iqk_check_nbiqc_8852b(rf, phy_idx, ID_NBTXK, path);
	}

	if (!kfail) {
		iqk_info->nb_txcfir[path] = halrf_rreg(rf, 0x8138 + (path << 8), MASKDWORD)  | 0x2;
	} else {
		iqk_info->nb_txcfir[path] = 0x40000002;
	}
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, kfail = 0x%x, 0x8%x38 = 0x%x\n", path, kfail, 1 << path, iqk_info->nb_txcfir[path]);
	return kfail;
}

__iram_func__
static void _lok_res_table_8852b(struct rf_info *rf, u8 path, u8 ibias)
{

	struct halrf_iqk_info *iqk_info = &rf->iqk;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, ibias = %x\n", path, ibias);
	halrf_wrf(rf, path, 0xef, MASKRF, 0x2);
	if (iqk_info->iqk_band[path] == BAND_ON_24G)
		halrf_wrf(rf, path, 0x33, MASKRF, 0x0);
	else
		halrf_wrf(rf, path, 0x33, MASKRF, 0x1);
	halrf_wrf(rf, path, 0x3f, MASKRF, ibias);
	halrf_wrf(rf, path, 0xef, MASKRF, 0x0);
	halrf_wrf(rf, path, 0x7c, BIT(5), 0x1);
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, 0x7c = %x\n", path, halrf_rrf(rf, path, 0x7c,MASKRF));
	
	return;
}

__iram_func__
static bool _lok_finetune_check_8852b(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool is_fail = false, is_fail1 = false,  is_fail2 = false;
	u32 temp = 0x0;
	u32 core_i = 0x0;
	u32 core_q = 0x0;
	u32 fine_i = 0x0;
	u32 fine_q = 0x0;
	u8 ch = 0x0;
	u32 vbuff_i = 0x0;
	u32 vbuff_q = 0x0;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	temp = halrf_rrf(rf, path, 0x58, MASKRF);
	core_i = (temp & 0xf8000) >> 15;
	core_q = (temp & 0x07c00) >> 10;
	fine_i = (temp & 0x003c0) >> 6;
	fine_q = (temp & 0x0003c) >> 2;
	ch = ((iqk_info->iqk_times /2) % 2) & 0x1;
	
	if (core_i  < 0x2 || core_i  > 0x1d || core_q < 0x2 || core_q > 0x1d) {
		is_fail1 = true;
	} else {	
		is_fail1 = false;
	}
	iqk_info->lok_idac[ch][path] = temp;
	
	temp = halrf_rrf(rf, path, 0x0a, MASKRF);
	vbuff_i = (temp & 0xfc000) >> 14;
	vbuff_q = (temp & 0x003f0) >> 4;

	if (vbuff_i  < 0x2 || vbuff_i  > 0x3d || vbuff_q < 0x2 || vbuff_q > 0x3d) {
		is_fail2 = true;
	} else {	
		is_fail2 = false;
	}
	iqk_info->lok_vbuf[ch][path] = temp;

	is_fail = is_fail1 |  is_fail2;
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, lok_idac[%x][%x] = 0x%x\n", path, ch, path, iqk_info->lok_idac[ch][path]);
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, lok_vbuf[%x][%x] = 0x%x\n", path, ch, path, iqk_info->lok_vbuf[ch][path]);

	return is_fail;
}

__iram_func__
static bool _iqk_lok_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
			    u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool fail = false;
	bool tmp = false;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	//Init RF gain & tone idx= 8.25Mhz
	halrf_wreg(rf, 0x802c, 0x00000fff, 0x021);
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		halrf_wrf(rf, path, 0x11, 0x00070, 0x6);
		//halrf_wrf(rf, path, 0x11, 0x1f000, 0x0);
		break;
	case BAND_ON_5G:
		halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		halrf_wrf(rf, path, 0x11, 0x00070, 0x4);
		//halrf_wrf(rf, path, 0x11, 0x1f000, 0x0);
		break;
	default:
		break;
	}

//Step 1 small mod gain
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		//halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		//halrf_wrf(rf, path, 0x11, 0x00070, 0x6);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x0);
		break;
	case BAND_ON_5G:
		//halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		//halrf_wrf(rf, path, 0x11, 0x00070, 0x4);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x0);
		break;
	default:
		break;
	}
	halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, 0x9);	
	tmp = _iqk_one_shot_8852b(rf, phy_idx, path, ID_FLoK_coarse);
	iqk_info->lok_cor_fail[0][path] = tmp;

//Step 2 large mod gain
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		//halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		//halrf_wrf(rf, path, 0x11, 0x00070, 0x6);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x12);
		break;
	case BAND_ON_5G:
		//halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		//halrf_wrf(rf, path, 0x11, 0x00070, 0x4);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x12);
		break;
	default:
		break;
	}
	
	halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, 0x24);
	tmp = _iqk_one_shot_8852b(rf, phy_idx, path, ID_FLOK_vbuffer);

//Step 3 small rf gain
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		//halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		//halrf_wrf(rf, path, 0x11, 0x00070, 0x6);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x0);
		break;
	case BAND_ON_5G:
		//halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		//halrf_wrf(rf, path, 0x11, 0x00070, 0x4);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x0);
		break;
	default:
		break;
	}
	halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, 0x9);	
	halrf_wreg(rf, 0x802c, 0x00000fff, 0x021);
	tmp = _iqk_one_shot_8852b(rf, phy_idx, path, ID_FLoK_fine);
	iqk_info->lok_fin_fail[0][path] = tmp;

//Step 4 large rf gain
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		//halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		//halrf_wrf(rf, path, 0x11, 0x00070, 0x5);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x12);
		break;
	case BAND_ON_5G:
		//halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		//halrf_wrf(rf, path, 0x11, 0x00070, 0x4);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x12);
		break;
	default:
		break;
	}
	
	halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, 0x24);
	tmp = _iqk_one_shot_8852b(rf, phy_idx, path, ID_FLOK_vbuffer);
	fail = _lok_finetune_check_8852b(rf, path);

	return fail;
}

__iram_func__
static bool _iqk_2g_lok_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
			    u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
//	struct rtw_phl_com_t *phl = rf->phl_com;
//	struct dev_cap_t *dev = &phl->dev_cap;

	bool fail = false;
	bool tmp = false;
	u8 i = 0;
	u32 i_vbuf0 = 0, q_vbuf0 = 0, i_vbuf1 = 0, q_vbuf1 = 0;
	u32 i_mod_c = 0, q_mod_c = 0;	
	u32 fail_th = 0x4;
	u8 g_track_idx[3] = {4, 5, 6};
	u8 g_txbb[3] = {0xa, 0x05, 0x00};
	u8 g_wa[3] = {0x00, 0x20, 0x60};

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	halrf_wrf(rf, path, 0x51, 0x80000, 0x0);
	halrf_wrf(rf, path, 0x51, 0x00800, 0x0);
	halrf_wrf(rf, path, 0x52, 0x00800, 0x1);
	halrf_wrf(rf, path, 0x55, 0x0001f, 0x0);
	halrf_wrf(rf, path, 0xef, 0x00004, 0x1);
	halrf_wrf(rf, path, 0x33, 0x000ff, 0x00);
	halrf_wrf(rf, path, 0x00, 0xffff0, 0x403e);
	halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
	halrf_wrf(rf, path, 0x11, 0x00070, 0x6);
	halrf_wrf(rf, path, 0x11, 0x1f000, 0x0);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x1);
	halrf_wreg(rf, 0x81cc + (path << 8), 0x0000003f, 0x09);
#if 0
	if((rf->hal_com->band[phy_idx].cur_chandef.bw == CHANNEL_WIDTH_20) && (dev->nb_config != 0))
		halrf_wreg(rf, 0x802c, 0x00000fff, 0x011);
	else
		halrf_wreg(rf, 0x802c, 0x00000fff, 0x021);
#else
	halrf_wreg(rf, 0x802c, 0x00000fff, 0x021);
#endif
	halrf_wreg(rf, 0x8000, MASKDWORD, 0x00000109 | (1 << (4 + path)));
	RF_DBG(rf, DBG_RF_IQK, "[IQK]one-shot_id : 0x%x\n", 0x00000109 | (1 << (4 + path)));
	tmp = _iqk_check_cal_8852b(rf, path, 0x1);
	halrf_wreg(rf, 0x8010, 0x000000ff, 0x00);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x0);
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, RF_0x11[16:19] = 0x%x\n", path, halrf_rrf(rf, path, 0x11, 0x1f000));
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, RF_0x08[00:19] = 0x%x\n", path, halrf_rrf(rf, path, 0x08, MASKRF));	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, RF_0x09[00:19] = 0x%x\n", path, halrf_rrf(rf, path, 0x09, MASKRF));	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, RF_0x0a[00:19] = 0x%x\n", path, halrf_rrf(rf, path, 0x0a, MASKRF));
	halrf_wrf(rf, path, 0x11, 0x1f000, 0x12);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x1);
	halrf_wreg(rf, 0x81cc + (path << 8), 0x0000003f, 0x24);
	halrf_wreg(rf, 0x8000, MASKDWORD, 0x00000309 | (1 << (4 + path)));	
	RF_DBG(rf, DBG_RF_IQK, "[IQK]one-shot_id : 0x%x\n", 0x00000309 | (1 << (4 + path)));
	tmp = _iqk_check_cal_8852b(rf, path, 0x3);
	halrf_wreg(rf, 0x8010, 0x000000ff, 0x00);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x0);
	
	i_vbuf0 = halrf_rrf(rf, path, 0x0a, 0xfe000);
	q_vbuf0 = halrf_rrf(rf, path, 0x0a, 0x003f8);
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x11[16:19] = 0x%x\n", halrf_rrf(rf, path, 0x11, 0x1f000));
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x08[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x08, MASKRF));	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x09[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x09, MASKRF));	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x0a[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x0a, MASKRF));

	halrf_wrf(rf, path, 0x11, 0x1f000, 0x0);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x1);
	halrf_wreg(rf, 0x81cc + (path << 8), 0x0000003f, 0x09);
	halrf_wreg(rf, 0x8000, MASKDWORD, 0x00000209 | (1 << (4 + path)));
	RF_DBG(rf, DBG_RF_IQK, "[IQK]one-shot_id : 0x%x\n", 0x00000209 | (1 << (4 + path)));	
	tmp = _iqk_check_cal_8852b(rf, path, 0x2);
	halrf_wreg(rf, 0x8010, 0x000000ff, 0x00);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x0);
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x11[16:19] = 0x%x\n", halrf_rrf(rf, path, 0x11, 0x1f000));
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x08[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x08, MASKRF));	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x09[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x09, MASKRF));	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x0a[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x0a, MASKRF));

	halrf_wrf(rf, path, 0x11, 0x1f000, 0x12);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x1);
	halrf_wreg(rf, 0x81cc + (path << 8), 0x0000003f, 0x24);
	halrf_wreg(rf, 0x8000, MASKDWORD, 0x00000309 | (1 << (4 + path)));
	RF_DBG(rf, DBG_RF_IQK, "[IQK]one-shot_id : 0x%x\n", 0x00000309 | (1 << (4 + path)));	
	tmp = _iqk_check_cal_8852b(rf, path, 0x3);
	halrf_wreg(rf, 0x8010, 0x000000ff, 0x00);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x0);
	
	i_vbuf1 = halrf_rrf(rf, path, 0x0a, 0xfe000);
	q_vbuf1 = halrf_rrf(rf, path, 0x0a, 0x003f8);
	i_mod_c = halrf_rrf(rf, path, 0x08, 0xf8000);
	q_mod_c = halrf_rrf(rf, path, 0x08, 0x003e0);
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x11[16:19] = 0x%x\n", halrf_rrf(rf, path, 0x11, 0x1f000));
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x08[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x08, MASKRF));	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x09[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x09, MASKRF));	
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x0a[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x0a, MASKRF));

//
	RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x55[1:2] = 0x%x\n", halrf_rrf(rf, path, 0x55, 0x00006));
	if(HALRF_ABS(i_vbuf0, i_vbuf1) >= fail_th || HALRF_ABS(q_vbuf0, q_vbuf1) >= fail_th
		||(i_vbuf0	< 0x2 || i_vbuf0  > 0x7d || q_vbuf0 < 0x2 || q_vbuf0 > 0x7d)
		||(i_vbuf1	< 0x2 || i_vbuf1  > 0x7d || q_vbuf1 < 0x2 || q_vbuf1 > 0x7d)
		||(i_mod_c	< 0x2 || i_mod_c  > 0x1d || q_mod_c < 0x2 || q_mod_c > 0x1d)){
		fail = true;
		RF_DBG(rf, DBG_RF_IQK, "[IQK]!!!!!!!!!!LOK by Pass !!!!!!!!!!!\n");
		RF_DBG(rf, DBG_RF_IQK, "[IQK]i_vbuf0 = %x, q_vbuf0 = %x\n", i_vbuf0, q_vbuf0);
		RF_DBG(rf, DBG_RF_IQK, "[IQK]i_vbuf1 = %x, q_vbuf1 = %x\n", i_vbuf1, q_vbuf1);
		RF_DBG(rf, DBG_RF_IQK, "[IQK]HALRF_ABS(i_vbuf0, i_vbuf1) = %x\n", HALRF_ABS(i_vbuf0, i_vbuf1));
		RF_DBG(rf, DBG_RF_IQK, "[IQK]HALRF_ABS(q_vbuf0, q_vbuf1) = %x\n", HALRF_ABS(q_vbuf0, q_vbuf1));
		RF_DBG(rf, DBG_RF_IQK, "[IQK]i_mod_c = %x, q_mod_c = %x\n", i_vbuf1, q_vbuf1);

		RF_DBG(rf, DBG_RF_IQK, "[IQK]\n");
		halrf_wrf(rf, path, 0x08, MASKRF, 0x80200);
		halrf_wrf(rf, path, 0x09, MASKRF, 0x80200);
		halrf_wrf(rf, path, 0x0a, MASKRF, 0x80200); 		
		RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x08[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x08, MASKRF));	
		RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x09[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x09, MASKRF));	
		RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x0a[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x0a, MASKRF));
	}

	if(!fail) {
		halrf_wrf(rf, path, 0x55, 0x00006, 0x1);
		for( i = 0; i < 3; i++) {
			halrf_wrf(rf, path, 0x11, 0x00070, g_track_idx[i]);
			halrf_wrf(rf, path, 0x11, 0x1f000, g_txbb[i]);
			halrf_wrf(rf, path, 0x33, 0x000ff, g_wa[i]);
			halrf_wreg(rf, 0x5864, 0x20000000, 0x1);
			halrf_wreg(rf, 0x81cc + (path << 8), 0x0000003f, 0x09);
			RF_DBG(rf, DBG_RF_IQK, "[IQK]idx = 0x%x, txbb =%x, wa =%x\n", g_track_idx[i], g_txbb[i], g_wa[i]);
			halrf_wreg(rf, 0x8000, MASKDWORD, 0x00000209 | (1 << (4 + path)));
			RF_DBG(rf, DBG_RF_IQK, "[IQK]i = %x, one-shot_id : 0x%x\n", i, 0x00000209 | (1 << (4 + path)));
#if 0
			if((rf->hal_com->band[phy_idx].cur_chandef.bw == CHANNEL_WIDTH_20) && (dev->nb_config != 0))
				halrf_wreg(rf, 0x802c, 0x00000fff, 0x011);
			else
				halrf_wreg(rf, 0x802c, 0x00000fff, 0x021);
#else
			halrf_wreg(rf, 0x802c, 0x00000fff, 0x021);
#endif
			tmp = _iqk_check_cal_8852b(rf, path, 0x2);
			halrf_wreg(rf, 0x8010, 0x000000ff, 0x00);
			halrf_wreg(rf, 0x5864, 0x20000000, 0x0);
			
			RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x11[16:19] = 0x%x\n", halrf_rrf(rf, path, 0x11, 0x1f000));
			RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x08[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x08, MASKRF));	
			RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x09[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x09, MASKRF));	
			RF_DBG(rf, DBG_RF_IQK, "[IQK]RF_0x0a[00:19] = 0x%x\n", halrf_rrf(rf, path, 0x0a, MASKRF));
		}
	}
	halrf_wrf(rf, path, 0x33, 0x000ff, 0x00);
	iqk_info->lok_idac[0][path] = halrf_rrf(rf, path, 0x58, MASKRF);

	return false;
}

__iram_func__
static void _iqk_txk_setting_8852b(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	//u32 tmp = 0x0;

	//TX init gain setting
	/*0/1:G/A*/

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		//05a_G_S0_TxLOK_52B_reg
		halrf_wrf(rf, path, 0x90, 0x00300, 0x00);
		halrf_wrf(rf, path, 0x51, 0x80000, 0x0);
		halrf_wrf(rf, path, 0x51, 0x00800, 0x0);
		halrf_wrf(rf, path, 0x52, 0x00800, 0x1);
		halrf_wrf(rf, path, 0x55, 0x0001f, 0x0);
		halrf_wrf(rf, path, 0xef, 0x00004, 0x1);
		halrf_wrf(rf, path, 0x33, 0x000ff, 0x00);
		halrf_wrf(rf, path, 0x00, 0xffff0, 0x403e);
		halrf_delay_us(rf, 1);
		break;
	case BAND_ON_5G:
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
		//05a_A_S0_TxLOK_52B__reg
		halrf_wrf(rf, path, 0x85, 0x00003, 0x00);
		halrf_wrf(rf, path, 0x60, 0x00007, 0x1);
		halrf_wrf(rf, path, 0x55, 0x0001f, 0x0);
		halrf_wrf(rf, path, 0xef, 0x00004, 0x1);
		halrf_wrf(rf, path, 0x33, 0x000ff, 0x80);
		halrf_wrf(rf, path, 0x00, 0xffff0, 0x403e);
		halrf_delay_us(rf, 1);
		break;
	default:
		break;
	}
/*
	tmp = halrf_rrf(rf, path, 0x00, MASKRF);
	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, rf%x = 0x%x\n", path, path, tmp);
*/
	return;
}

__iram_func__
static void _iqk_txclk_setting_8852b(struct rf_info *rf, u8 path)
{

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	//04_CLK_Setting_TxIQK_DAC960MHz_nonDBCC_PHY0_path01_reg
	halrf_wreg(rf, 0x12b8, 0x40000000, 0x1);
	halrf_wreg(rf, 0x32b8, 0x40000000, 0x1);
	halrf_delay_us(rf, 1);
	halrf_wreg(rf, 0x030c, 0xff000000, 0x1f);
	halrf_delay_us(rf, 1);
	halrf_wreg(rf, 0x030c, 0xff000000, 0x13);
	halrf_wreg(rf, 0x032c, 0xffff0000, 0x0001);
	halrf_delay_us(rf, 1);
	halrf_wreg(rf, 0x032c, 0xffff0000, 0x0041);	

#if 0
	halrf_wreg(rf, 0xc000 + (path << 8), 0x00020000, 0x0);	
	halrf_delay_us(rf, 10);	
	halrf_wreg(rf, 0xc000 + (path << 8), 0x00020000, 0x1);	
	halrf_delay_us(rf, 10);	
#endif
	return;
}

__iram_func__
static void _iqk_info_iqk_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
				 u8 path)
{
#if 0
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u32 tmp = 0x0;
	bool flag = 0x0;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	iqk_info->thermal[path] = halrf_get_thermal_8852b(rf, path);	
	iqk_info->thermal_rek_en = false;
	flag = iqk_info->lok_cor_fail[0][path];
	halrf_wreg(rf, 0x9fe0, BIT(0) << (path * 4), flag);
	flag = iqk_info->lok_fin_fail[0][path];
	halrf_wreg(rf, 0x9fe0, BIT(1) << (path * 4), flag);
	flag = iqk_info->iqk_tx_fail[0][path];
	halrf_wreg(rf, 0x9fe0, BIT(2) << (path * 4), flag);
	flag = iqk_info->iqk_rx_fail[0][path];
	halrf_wreg(rf, 0x9fe0, BIT(3) << (path * 4), flag);

	tmp = halrf_rreg(rf, 0x8124 + (path << 8), MASKDWORD);
	iqk_info->bp_iqkenable[path] = tmp;
	tmp = halrf_rreg(rf, 0x8138 + (path << 8), MASKDWORD);
	iqk_info->bp_txkresult[path] = tmp;
	tmp = halrf_rreg(rf, 0x813c + (path << 8), MASKDWORD);
	iqk_info->bp_rxkresult[path] = tmp;

	halrf_wreg(rf, 0x9fe8, 0x0000ff00, (u8)iqk_info->iqk_times);

	tmp = halrf_rreg(rf, 0x9fe0, 0x0000000f << (path * 4));
	if (tmp != 0x0)
		iqk_info->iqk_fail_cnt++;
	halrf_wreg(rf, 0x9fe8, 0x00ff0000 << (path * 4), iqk_info->iqk_fail_cnt);
	return;
#endif
}


__iram_func__
static void _iqk_by_path_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
				u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool lok_is_fail = false;
	u8 ibias = 0x1;
	u8 i = 0;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	_iqk_txclk_setting_8852b(rf, path);
	halrf_adc_fifo_rst_8852b(rf, phy_idx, path);

	//LOK
	for (i = 0; i < 3; i++) {
		_lok_res_table_8852b(rf, path, ibias++);
		_iqk_txk_setting_8852b(rf, path);

		if(iqk_info->iqk_band[path] == BAND_ON_24G) 
			lok_is_fail = _iqk_2g_lok_8852b(rf, phy_idx, path);
		else
			lok_is_fail = _iqk_lok_8852b(rf, phy_idx, path);

		if (!lok_is_fail)
			break;
	}

	if(iqk_info->iqk_band[path] == BAND_ON_24G) 
		iqk_info->is_nbiqk = true;
	else
		iqk_info->is_nbiqk = false;

	//TXK
	if (iqk_info->is_nbiqk) {
		iqk_info->iqk_tx_fail[0][path] =
			_iqk_nbtxk_8852b(rf, phy_idx, path);
	} else {
		iqk_info->iqk_tx_fail[0][path] =
			_txk_group_sel_8852b(rf, phy_idx, path);
	}
	//RX
	
	_iqk_rxclk_setting_8852b(rf, path);
	_iqk_rxk_setting_8852b(rf, path);
	halrf_adc_fifo_rst_8852b(rf, phy_idx, path);
	
	//tmp = iqk_info->is_nbiqk;
		
	if (iqk_info->is_nbiqk) {
		iqk_info->iqk_rx_fail[0][path] =
			_iqk_nbrxk_8852b(rf, phy_idx, path);
	} else {
		iqk_info->iqk_rx_fail[0][path] =
			_rxk_group_sel_8852b(rf, phy_idx, path);
	}

	return;
}

__iram_func__
void iqk_set_info_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx,
				 u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u32 tmp = 0x0;
	bool flag = 0x0;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	iqk_info->thermal[path] = halrf_get_thermal_8852b(rf, path);	
	iqk_info->thermal_rek_en = false;

	flag = (bool) halrf_rreg(rf, 0x9fe0, BIT(0) << (path * 4));
	iqk_info->lok_cor_fail[0][path] = flag;

	flag = (bool) halrf_rreg(rf, 0x9fe0, BIT(1) << (path * 4));
	iqk_info->lok_fin_fail[0][path] = flag;

	flag = (bool) halrf_rreg(rf, 0x9fe0, BIT(2) << (path * 4));
	iqk_info->iqk_tx_fail[0][path] = flag;

	flag = (bool) halrf_rreg(rf, 0x9fe0, BIT(3) << (path * 4));
	iqk_info->iqk_rx_fail[0][path] = flag;
	
	tmp = halrf_rreg(rf, 0x8124 + (path << 8), MASKDWORD);
	iqk_info->bp_iqkenable[path] = tmp;

	tmp = halrf_rreg(rf, 0x8138 + (path << 8), MASKDWORD);
	iqk_info->bp_txkresult[path] = tmp;

	tmp = halrf_rreg(rf, 0x813c + (path << 8), MASKDWORD);
	iqk_info->bp_rxkresult[path] = tmp;

	iqk_info->iqk_times = (u8) halrf_rreg(rf, 0x9fe8, 0x0000ff00);
	iqk_info->iqk_fail_cnt = halrf_rreg(rf, 0x9fe8, 0x00ff0000 << (path * 4));
	return;
}

__iram_func__
bool iqk_mcc_page_sel_8852b(struct rf_info *rf, enum phl_phy_idx phy, u8 path)
{
#if 0
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool flag = false;

	if (rf->hal_com->band[phy].cur_chandef.center_ch ==  iqk_info->iqk_mcc_ch[0][path]) {
		halrf_wreg(rf, 0x8104 + (path << 8), 0x00000001, 0x0);
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000004, 0x0);
		_iqk_mcc_load_lok_8852b(rf, phy, path, iqk_info->lok_idac[0][path]);
		flag = true;
	} else if (rf->hal_com->band[phy].cur_chandef.center_ch == iqk_info->iqk_mcc_ch[1][path]) {
		halrf_wreg(rf, 0x8104 + (path << 8), 0x00000001, 0x1);
		halrf_wreg(rf, 0x8154 + (path << 8), 0x00000004, 0x1);
		_iqk_mcc_load_lok_8852b(rf, phy, path, iqk_info->lok_idac[1][path]);
		flag = true;
	} else
		flag = false;
#endif	
	return false;
}

__iram_func__
void iqk_get_ch_info_8852b(struct rf_info *rf, enum phl_phy_idx phy, u8 path)
{
#if 1
	struct rtw_phl_com_t *phl = rf->phl_com;
	struct dev_cap_t *dev = &phl->dev_cap;
#endif
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	struct halrf_gapk_info *txgapk_info = &rf->gapk;
//	u8 ver;
	u8 idx = 0;
	u8 get_empty_table = false;

	if(!phl_is_mp_mode(rf->phl_com))  {
		for  (idx = 0;  idx < 2; idx++) {
			if (iqk_info->iqk_mcc_ch[idx][path] == 0) {
				get_empty_table = true;
				break;
			}
		}
		//RF_DBG(rf, DBG_RF_IQK, "[IQK] (1)  idx = %x\n", idx);

		if (false == get_empty_table) {
			idx = iqk_info->iqk_table_idx[path] + 1;
			if (idx > 1) {
				idx = 0;
			}		
			//RF_DBG(rf, DBG_RF_IQK, "[IQK]we will replace iqk table index(%d), !!!!! \n", idx);
		}	
	} else {
		idx = 0;
	}
	RF_DBG(rf, DBG_RF_IQK, "[IQK] version 51 \n");

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	iqk_info->iqk_band[path] = rf->hal_com->band[phy].cur_chandef.band;
	iqk_info->iqk_bw[path] = rf->hal_com->band[phy].cur_chandef.bw;
	iqk_info->iqk_ch[path] = rf->hal_com->band[phy].cur_chandef.center_ch;	
	iqk_info->iqk_mcc_ch[idx][path] = rf->hal_com->band[phy].cur_chandef.center_ch;
	iqk_info->iqk_table_idx[path] =  txgapk_info->txgapk_table_idx;
	RF_DBG(rf, DBG_RF_IQK, "[IQK]iqk_info->iqk_band[%x] = 0x%x\n", path, iqk_info->iqk_band[path]);
	RF_DBG(rf, DBG_RF_IQK, "[IQK]iqk_info->iqk_bw[%x] = 0x%x\n", path, iqk_info->iqk_bw[path]);
	RF_DBG(rf, DBG_RF_IQK, "[IQK]iqk_info->iqk_ch[%x] = 0x%x\n", path, iqk_info->iqk_ch[path]);	
	RF_DBG(rf, DBG_RF_IQK, "[IQK]iqk_info->iqk_table_idx[%x] = 0x%x\n", path, iqk_info->iqk_table_idx[path]);	
	if(rf->hal_com->band[phy].cur_chandef.bw == CHANNEL_WIDTH_20)
		if(dev->nb_config != 0){
			halrf_nbiqk_enable_8852b(rf, true);
			RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, NBIQK for BW05/10 application !!\n", path);
		}

	RF_DBG(rf, DBG_RF_IQK, "[IQK]S%d (PHY%d): / DBCC %s/ %s/ CH%d/ %s\n",
		   path, phy,  rf->hal_com->dbcc_en ? "on" : "off",
		   iqk_info->iqk_band[path]  == 0 ? "2G" : (iqk_info->iqk_band[path]  == 1 ? "5G" : "6G"),
		   iqk_info->iqk_ch[path] ,
		   iqk_info->iqk_bw[path] == 0 ? "20M" : (iqk_info->iqk_bw[path] == 1 ? "40M" : "80M"));	
	RF_DBG(rf, DBG_RF_IQK, "[IQK] times = 0x%x, ch =%x\n", iqk_info->iqk_times , idx);	
	RF_DBG(rf, DBG_RF_IQK, "[IQK] iqk_mcc_ch[%x][%x] = 0x%x\n",  (u8)idx, (u8)path, iqk_info->iqk_mcc_ch[idx][path]);

	return;
}

__iram_func__
void halrf_iqk_reload_8852b(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u32 tmp;
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	iqk_info->reload_cnt++;
	tmp = iqk_info->bp_iqkenable[path];
	halrf_wreg(rf, 0x8124 + (path << 8), MASKDWORD, tmp);
	tmp = iqk_info->bp_txkresult[path];
	halrf_wreg(rf, 0x8138 + (path << 8), MASKDWORD, tmp);
	tmp = iqk_info->bp_rxkresult[path];
	halrf_wreg(rf, 0x813c + (path << 8), MASKDWORD, tmp);
	return;
}

__iram_func__
void iqk_start_iqk_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	_iqk_by_path_8852b(rf, phy_idx, path);

	return;
}

__iram_func__
void iqk_restore_8852b(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool fail;

	RF_DBG(rf, DBG_RF_IQK, "===> %s\n", __func__);

	halrf_wreg(rf, 0x8000, MASKDWORD, 0x00000e19 + (path << 4));
	fail = _iqk_check_cal_8852b(rf, path, 0x0);
#if 1
	halrf_wreg(rf, 0x8138 + (path << 8), MASKDWORD, iqk_info->nb_txcfir[path]);
	halrf_wreg(rf, 0x813c + (path << 8), MASKDWORD, iqk_info->nb_rxcfir[path]);
#else
	if(iqk_info->is_nbiqk) {
		halrf_wreg(rf, 0x8138 + (path << 8), MASKDWORD, iqk_info->nb_txcfir[path]);
		halrf_wreg(rf, 0x813c + (path << 8), MASKDWORD, iqk_info->nb_rxcfir[path]);
	} else {
		halrf_wreg(rf, 0x8138 + (path << 8), MASKDWORD, 0x40000000);
		halrf_wreg(rf, 0x813c + (path << 8), MASKDWORD, 0x40000000);
	}
#endif	
	halrf_wreg(rf, 0x8010, 0x000000ff, 0x00);
	halrf_wreg(rf, 0x8008, MASKDWORD, 0x00000000);
	halrf_wreg(rf, 0x8088, MASKDWORD, 0x80000000);
	halrf_wreg(rf, 0x8120, 0x10000000, 0x0);
	halrf_wreg(rf, 0x8220, 0x10000000, 0x0);
	halrf_wreg(rf, 0x8220, 0x00010000, 0x0);
	halrf_wrf(rf, path, 0xef, 0x00004, 0x0);
	halrf_wrf(rf, path, 0xef, 0x00004, 0x0);
	halrf_wrf(rf, path, 0x00, 0xf0000, 0x3);
	halrf_wrf(rf, path, 0x05, 0x00001, 0x1);	
	halrf_wrf(rf, path, 0x10005, 0x00001, 0x1);

	return;	
}

__iram_func__
void iqk_afebb_restore_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
	u32	i = 0;
	u32	array_len = 0x0;
	u32 *array = NULL;
	u32	addr = 0, mask = 0,  val = 0;	

	RF_DBG(rf, DBG_RF_IQK, "===> %s\n", __func__);
	
	switch(halrf_kpath_8852b(rf, phy_idx)) {
		case RF_A:			
			break;
		case RF_B:			
			break;
		default:
			array_len = sizeof(array_restore_nondbcc_path01_8852b) / sizeof(u32);
			array = (u32 *) &array_restore_nondbcc_path01_8852b;
			break;
	}

	while ((i + 1) < array_len) {
		addr = array[i];
		mask = array[i + 1];
		val = array[i + 2];
		halrf_wreg(rf, addr, mask, val);	
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]0x%x[%x] = 0x%x\n", addr, mask, val);
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]0x%x[%x] = 0x%x\n", addr, mask, halrf_rreg(rf, addr, mask));
		i += 3;
	}

	return;
}

__iram_func__
void iqk_preset_8852b(struct rf_info *rf, u8 path)
{
	//03_IQK_Preset_Non_DBCC_PHY0_path01
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u8 idx = 0;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);

	idx = iqk_info->iqk_table_idx[path];
	//halrf_wrf(rf, path, 0x55, 0x00001, 0x1);
	//halrf_wrf(rf, path, 0x18, 0x80000, idx);
	halrf_wreg(rf, 0x8104 + (path << 8), 0x00000001, idx);
	halrf_wreg(rf, 0x8154 + (path << 8), 0x00000008, idx);
	halrf_wreg(rf, 0x8138 + (path << 8), MASKDWORD, 0x40000000);
	halrf_wreg(rf, 0x813c + (path << 8), MASKDWORD, 0x40000000);
	
	halrf_wrf(rf, path, 0x5, 0x00001, 0x0);
	halrf_wrf(rf, path, 0x10005, 0x00001, 0x0);
	halrf_wreg(rf, 0x8008, MASKDWORD, 0x00000080);
	halrf_wreg(rf, 0x8088, MASKDWORD, 0x81ff010a);
#ifndef HALRF_CONFIG_FW_IO_OFLD_SUPPORT
	RF_DBG(rf, DBG_RF_IQK, "[IQK](1)S%x, 0x8%x54 = 0x%x\n", path, 1 << path, halrf_rreg(rf, 0x8154 + (path << 8), MASKDWORD));
	RF_DBG(rf, DBG_RF_IQK, "[IQK](1)S%x, 0x8%x04 = 0x%x\n", path, 1 << path, halrf_rreg(rf, 0x8104 + (path << 8), MASKDWORD));
#endif
	

	return;
}

__iram_func__
void iqk_macbb_setting_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
	u32	i = 0;
	u32	array_len = 0x0;
	u32 *array = NULL;
	u32	addr = 0, mask = 0,  val = 0;	

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===> %s\n", __func__);
	
	switch(halrf_kpath_8852b(rf, phy_idx)) {
		case RF_A:			
			break;
		case RF_B:			
			break;
		default:
			array_len = sizeof(array_set_nondbcc_path01_8852b) / sizeof(u32);
			array = (u32 *) &array_set_nondbcc_path01_8852b;
			break;
	}
	while ((i + 1) < array_len) {
		addr = array[i];
		mask = array[i + 1];
		val = array[i + 2];
		halrf_wreg(rf, addr, mask, val);
		i += 3;
	}

	halrf_txck_force_8852b(rf, RF_PATH_A, true, DAC_960M);
	halrf_rxck_force_8852b(rf, RF_PATH_A, true, ADC_1920M);
	halrf_txck_force_8852b(rf, RF_PATH_B, true, DAC_960M);
	halrf_rxck_force_8852b(rf, RF_PATH_B, true, ADC_1920M);

	return;
}

__iram_func__
void halrf_iqk_toneleakage_8852b(struct rf_info *rf, u8 path)
{
	iqk_macbb_setting_8852b(rf, HW_PHY_0, path);	
	iqk_preset_8852b(rf, path);
	_iqk_txclk_setting_8852b(rf, path);
	// main iqk single tone process
	halrf_wrf(rf, path, 0x0, 0xf0000, 0x2);
#if 0
	switch (iqk_info->iqk_band[path]) {
	case BAND_ON_24G:
		halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		halrf_wrf(rf, path, 0x11, 0x00070, 0x6);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x0e);
		break;
	case BAND_ON_5G:
		halrf_wrf(rf, path, 0x11, 0x00003, 0x0);
		halrf_wrf(rf, path, 0x11, 0x00070, 0x6);
		halrf_wrf(rf, path, 0x11, 0x1f000, 0x0e);
		break;
	default:
		break;
	}
#endif
	halrf_wreg(rf, 0x8088, MASKDWORD, 0x81ff010a);
	halrf_wreg(rf, 0x80d0, MASKDWORD, 0x00300000);
	halrf_wreg(rf, 0x8120 + (path << 8), MASKDWORD, 0xce000a08);
	halrf_wreg(rf, 0x8000, 0x00000006, path);
	halrf_wrf(rf, path, 0x10001, 0x0003f, 0x3c);
	halrf_wreg(rf, 0x8034, 0x00000030, 0x2);
	halrf_wreg(rf, 0x8038, 0x00000100, 0x1);
	halrf_wreg(rf, 0x8034, 0xff000000, 0x11);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x1);
	halrf_wreg(rf, 0x8014, 0x10000000, 0x1);
	halrf_wreg(rf, 0x8014, 0x10000000, 0x0);
	halrf_delay_us(rf, 100);
	halrf_wreg(rf, 0x5864, 0x20000000, 0x0);
	halrf_wreg(rf, 0x8018, 0x70000000, 0x2);
	halrf_wreg(rf, 0x81cc + (path << 8), MASKDWORD, 0x12);
	halrf_wreg(rf, 0x802c, 0x00000fff, 0x009);
	halrf_wreg(rf, 0x8034, 0x00000001, 0x1);
	halrf_wreg(rf, 0x8034, 0x00000001, 0x0);
	halrf_delay_us(rf, 1);
	//halrf_wreg(rf, 0x8034, 0x00000030, 0x3);
	//halrf_wreg(rf, 0x8038, 0x00000100, 0x0);
	return;
}

__iram_func__
void halrf_iqk_dbcc_8852b(struct rf_info *rf, u8 path)
{
#if 0
	bool bkdbcc = false;	
	u8 phy_idx = 0x0;
	
	bkdbcc = rf->hal_com->dbcc_en;
	rf->hal_com->dbcc_en = true;

	if (path == 0x0)
		phy_idx = HW_PHY_0;
	else
		phy_idx = HW_PHY_1;

	//iqk_mcc_page_sel_8852b(rf,phy_idx, path);		
	iqk_get_ch_info_8852b(rf,phy_idx, path);
	iqk_macbb_setting_8852b(rf, phy_idx, path);
	iqk_preset_8852b(rf, path);
	iqk_start_iqk_8852b(rf, phy_idx, path);
	iqk_restore_8852b(rf, path);
	iqk_afebb_restore_8852b(rf, phy_idx, path);	
	rf->hal_com->dbcc_en = bkdbcc;
#endif
	return;
}

__iram_func__
void halrf_iqk_onoff_8852b(struct rf_info *rf, bool is_enable)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (is_enable) {
		halrf_wreg(rf, 0x8124, MASKDWORD, 0x00000505); /*ch0*/
		halrf_wreg(rf, 0x8224, MASKDWORD, 0x00000505); /*ch1*/
		iqk_info->is_iqk_enable = true;
	} else {
		halrf_wreg(rf, 0x8124, MASKDWORD, 0x00000000); /*ch0*/
		halrf_wreg(rf, 0x8224, MASKDWORD, 0x00000000); /*ch1*/
		iqk_info->is_iqk_enable = false;
	}
	RF_DBG(rf, DBG_RF_IQK, "[IQK] IQK enable :  %s !!!\n",
	       iqk_info->is_iqk_enable ? "enable" : "disable");
	return;
}

__iram_func__
void halrf_iqk_tx_bypass_8852b(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (path == RF_PATH_A) { //path A
		/*ch0*/
		halrf_wreg(rf, 0x8124, 0x00000f00, 0x0);
		halrf_wreg(rf, 0x8138, MASKDWORD, 0x40000002);
	} else {
		/*ch1*/
		halrf_wreg(rf, 0x8224, 0x00000f00, 0x0);
		halrf_wreg(rf, 0x8238, MASKDWORD, 0x40000002);
	}
	iqk_info->nb_txcfir[path] = 0x40000002;
	return;
}

__iram_func__
void halrf_iqk_rx_bypass_8852b(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (path == RF_PATH_A) { //path A
		/*ch0*/
		halrf_wreg(rf, 0x8124, 0x0000000f, 0x0);
		halrf_wreg(rf, 0x813c, MASKDWORD, 0x40000002);
	} else {
		/*ch1*/
		halrf_wreg(rf, 0x8224, 0x0000000f, 0x0);
		halrf_wreg(rf, 0x823c, MASKDWORD, 0x40000002);
	}
	iqk_info->nb_rxcfir[path] = 0x40000002;
	return;
}

__iram_func__
void halrf_iqk_lok_bypass_8852b(struct rf_info *rf, u8 path)
{
	halrf_wrf(rf, path, 0xdf, 0x00004, 0x1);
	halrf_wrf(rf, path, 0x58, MASKRF, 0x84220);
	return;
}

__iram_func__
void halrf_nbiqk_enable_8852b(struct rf_info *rf, bool nbiqk_en)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (nbiqk_en) {
		iqk_info->is_nbiqk = true;
	} else {
		iqk_info->is_nbiqk = false;
	}

	return;
}

__iram_func__
void halrf_iqk_xym_enable_8852b(struct rf_info *rf, bool iqk_xym_en)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (iqk_xym_en) {
		iqk_info->iqk_xym_en = true;
	} else {
		iqk_info->iqk_xym_en = false;
	}

	return;
}

__iram_func__
void halrf_iqk_fft_enable_8852b(struct rf_info *rf, bool iqk_fft_en)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (iqk_fft_en) {
		iqk_info->iqk_fft_en = true;
	} else {
		iqk_info->iqk_fft_en = false;
	}

	return;
}

__iram_func__
void halrf_iqk_sram_enable_8852b(struct rf_info *rf, bool iqk_sram_en)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (iqk_sram_en) {
		iqk_info->iqk_sram_en = true;
	} else {
		iqk_info->iqk_sram_en = false;
	}

	return;
}

__iram_func__
void halrf_iqk_cfir_enable_8852b(struct rf_info *rf, bool iqk_cfir_en)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (iqk_cfir_en) {
		iqk_info->iqk_cfir_en = true;
	} else {
		iqk_info->iqk_cfir_en = false;
	}
	return;
}

__iram_func__
void halrf_iqk_track_8852b(
	struct rf_info *rf)
{
#if 0
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u8 path =0x0, i = 0x0;
	u8 cur_ther = 0x0, ther_avg_cnt = 0;
	u32 ther_avg[2] = {0};

	/*only check path 0 */
	for (path = 0; path < 1; path++) {
		cur_ther = halrf_get_thermal_8852b(rf, path);
		iqk_info->ther_avg[path][iqk_info->ther_avg_idx] = cur_ther;		
		/*Average times */
		ther_avg_cnt = 0;
		for (i = 0; i < 0x4; i++) {
			if (iqk_info->ther_avg[path][i]) {
				ther_avg[path] += iqk_info->ther_avg[path][i];
				ther_avg_cnt++;
			}
		}
		/*Calculate Average ThermalValue after average enough times*/
		if (ther_avg_cnt) {
			cur_ther = (u8)(ther_avg[path] / ther_avg_cnt);
		}
		if (HALRF_ABS(cur_ther, iqk_info->thermal[path] ) > IQK_THR_ReK) {
			iqk_info->thermal_rek_en = true;
		}
		else {
			iqk_info->thermal_rek_en = false;
		}
		//RF_DBG(rf, DBG_RF_IQK, "[IQK]S%x, iqk_ther =%d, ther_now = %d\n", path, iqk->thermal[path], cur_ther);
	}
	iqk_info->ther_avg_idx++;
	if (iqk_info->ther_avg_idx == 0x4)
		iqk_info->ther_avg_idx = 0;
	return;
#endif
}

__iram_func__
bool halrf_iqk_get_ther_rek_8852b(struct rf_info *rf ) {
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	return iqk_info->thermal_rek_en;
}

__iram_func__
u8 halrf_iqk_get_mcc_ch0_8852b(struct rf_info *rf ) {
	
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	return iqk_info->iqk_mcc_ch[0][0];
}

__iram_func__
u8 halrf_iqk_get_mcc_ch1_8852b(struct rf_info *rf ) {
	
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	return iqk_info->iqk_mcc_ch[1][0];
}

__iram_func__
bool halrf_check_fwiqk_done_8852b(struct rf_info *rf)
{
	u32 counter = 0x0;
	bool flag = false;
	bool isfail = false;
#if 1
	while (1) {
		if (halrf_rreg(rf, 0xbff8, MASKBYTE0) == 0xaa  || counter > 3000) {
			if(halrf_rreg(rf, 0x8010, MASKBYTE0) == 0xaa) {
				flag = true;
				break;
			}
		}
		counter++;
		halrf_delay_us(rf, 10);
	};
#else
	for(counter = 0; counter < 6000; counter++)
		halrf_delay_us(rf, 10);
#endif
	if (counter < 10)
		isfail = true; 
	else
		isfail = false; 
		
	if(flag) {
		RF_DBG(rf, DBG_RF_IQK, "[IQK] Load FW Done, counter = %d!!\n", counter);
	} else {
		RF_DBG(rf, DBG_RF_IQK, "[IQK] Load FW Fail, counter = %d!!\n", counter);	
		halrf_iqk_tx_bypass_8852b(rf, RF_PATH_A);
		halrf_iqk_tx_bypass_8852b(rf, RF_PATH_B);
		halrf_iqk_rx_bypass_8852b(rf, RF_PATH_A);
		halrf_iqk_rx_bypass_8852b(rf, RF_PATH_B);
		halrf_iqk_lok_bypass_8852b(rf, RF_PATH_A);		
		halrf_iqk_lok_bypass_8852b(rf, RF_PATH_B);
	}
	halrf_wreg(rf, 0x8010, 0x000000ff,0x0);
	return isfail;
}

__iram_func__
void halrf_enable_fw_iqk_8852b(struct rf_info *rf, bool is_fw_iqk)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	if (is_fw_iqk) {
		iqk_info->is_fw_iqk = true;
	} else {
		iqk_info->is_fw_iqk = false;
	}
	return;
}

__iram_func__ 
u8 halrf_get_iqk_times_8852b(struct rf_info *rf) {
	u8 times  = 0x0;

	times = (u8) halrf_rreg(rf, 0x9fe8, 0x0000ff00);
	return times;
}

__iram_func__ 
u32 halrf_get_iqk_ver_8852b(void)
{
	return iqk_version_8852b;
}

__iram_func__
void iqk_init_8852b(struct rf_info *rf)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u8 idx, path;
	halrf_wreg(rf, 0x9fe0, MASKDWORD, 0x0);	
	if (!iqk_info->is_iqk_init) {		
		RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
		iqk_info->is_iqk_init = true;
		iqk_info->is_nbiqk = false;
		iqk_info->iqk_fft_en = false;
		iqk_info->iqk_sram_en = false;
		iqk_info->iqk_cfir_en = false;
		iqk_info->iqk_xym_en = false;
		iqk_info->thermal_rek_en = false;
		iqk_info->ther_avg_idx = 0x0;
		iqk_info->iqk_times = 0x0;
		/*channel/path/TRX(TX:0, RX:1) */
		iqk_info->iqk_times = 0x0;
		iqk_info->is_fw_iqk = false;
		for (idx = 0; idx < 2; idx++) { //channel		
			iqk_info->iqk_channel[idx] = 0x0;
			for (path = 0; path < ss_8852b; path++) {//path
				iqk_info->lok_cor_fail[idx][path] = false;
				iqk_info->lok_fin_fail[idx][path] = false;
				iqk_info->iqk_tx_fail[idx][path] = false;
				iqk_info->iqk_rx_fail[idx][path] = false;
				iqk_info->iqk_mcc_ch[idx][path] = 0x0;
				iqk_info->iqk_table_idx[path] = 0x0;
			}
		}
	}
	return;
}
u8 halrf_iqk_get_rxevm_8852b(struct rf_info *rf)
{
	u8 rxevm =0x0;
#if 1
	halrf_wreg(rf, 0x738, 0x00000010, 0x1);
	halrf_wreg(rf, 0x738, 0x000000c0, 0x1);
	halrf_wreg(rf, 0x738, 0x70000000, 0x2);
	halrf_wreg(rf, 0x738, 0x00000020, 0x0);
	halrf_delay_us(rf, 100);
	halrf_wreg(rf, 0x20f4, 0x01000000, 0x0);
	halrf_wreg(rf, 0x20f8, 0x80000000, 0x1);
	halrf_wreg(rf, 0x20f0, 0x00ff0000, 0x1);
	halrf_wreg(rf, 0x20f0, 0x00000f00, 0x7);
	halrf_wreg(rf, 0x20f0, 0x000000ff, 0x0);
	halrf_wreg(rf, 0x738, 0x00000020, 0x1);
	halrf_wreg(rf, 0x738, 0x0000ff00, 0x5);
	rxevm = (u8) (halrf_rreg(rf, 0x1af0, 0x00ff0000) /4) ;
#else 
	rxevm = rtw_hal_bb_get_rxevm_single_user(rf->hal_com, HW_PHY_0, 0, 1);
#endif
	return rxevm;
}

u32 halrf_iqk_get_rximr_8852b(struct rf_info *rf, u8 path, u32 idx)
{
	u32 rximr =0x0;
	u32 tone_idx = 0x0;
	u32 main_idx = 0x0;
	u32 rf0 = 0x0;
	u32 pwr_sig = 0x0, pwr_img = 0x0;
	u32 reg_0x800c = 0x0, reg_0x8018 = 0x0, reg_0x801c = 0x0, reg_0x81cc = 0x0, reg_0x82cc = 0x0;

	reg_0x800c = halrf_rreg(rf, 0x800c, MASKDWORD);
	reg_0x8018 = halrf_rreg(rf, 0x8018, MASKDWORD);
	reg_0x801c = halrf_rreg(rf, 0x801c, MASKDWORD); 
	reg_0x81cc = halrf_rreg(rf, 0x81cc, MASKDWORD); 
	reg_0x82cc = halrf_rreg(rf, 0x82cc, MASKDWORD); 

	//tone_idx = idx * 320MHz/80MHz
	if (idx <100) {		
		tone_idx = idx * 4 * 2;
		main_idx = tone_idx & 0xfff;
	} else {
		tone_idx = (idx -100) *4 * 2;
		main_idx = (0x1000-tone_idx) & 0xfff;
	}
	RF_DBG(rf, DBG_RF_IQK, "[IQK][IMR]S%x, idx = 0x%x, tone_idx = 0x%x, main_idx = 0x%x\n", path, idx, tone_idx, main_idx);

	iqk_macbb_setting_8852b(rf, HW_PHY_0, path);	

	iqk_preset_8852b(rf, path);	
	_iqk_rxclk_setting_8852b(rf, path);
	halrf_wreg(rf, 0x8088, MASKDWORD, 0x81ff0109);
	halrf_wreg(rf, 0x8000, 0x00000006, path);
	halrf_wreg(rf, 0x800c, MASKDWORD, 0x00000c00);
	halrf_wreg(rf, 0x8018, 0x70000000, 0x4);
	halrf_wreg(rf, 0x801c, 0x000e0000, 0x0);
	halrf_wreg(rf, 0x80d0, MASKDWORD, 0x00300000);
	halrf_wreg(rf, 0x81cc + (path << 8), 0x0000003f, 0x3f);
	halrf_wreg(rf, 0x8140 + (path << 8), 0x00000100, 0x1);
	rf0 = halrf_rrf(rf, path, 0x00, 0x03800);
	halrf_wreg(rf, 0x8144 + (path << 8), 0x00070000, rf0);
	rf0  = halrf_rrf(rf, path, 0x00, 0x003e0);
	halrf_wreg(rf, 0x8144 + (path << 8), 0x1f000000, rf0);
	halrf_wreg(rf, 0x81dc + (path << 8), MASKDWORD, 0x00000001);
	halrf_wreg(rf, 0x81dc + (path << 8), MASKDWORD, 0x00000000);

	halrf_wreg(rf, 0x802c, 0x0fff0000, main_idx);
	halrf_wreg(rf, 0x8034, 0x00000001, 0x1);
	halrf_wreg(rf, 0x8034, 0x00000001, 0x0);
	halrf_delay_us(rf, 100);

	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x002d0000);
	pwr_sig = halrf_rreg(rf, 0x80fc, 0x007f0000);
	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x002e0000);
	pwr_sig = (pwr_sig << 25) + (halrf_rreg(rf, 0x80fc, MASKDWORD) >> 7);

	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x002d0000);
	pwr_img = halrf_rreg(rf, 0x80fc, 0x0000007f);	
	halrf_wreg(rf, 0x80d4, MASKDWORD, 0x002f0000);
	pwr_img = (pwr_img << 25) + (halrf_rreg(rf, 0x80fc, MASKDWORD) >> 7);	

	rximr = (u32) (pwr_sig / pwr_img);
	RF_DBG(rf, DBG_RF_IQK, "[IQK][IMR]S%x, %x, %d,%d, %d\n", path, halrf_rrf(rf, path, 0x0, MASKRF),pwr_sig, pwr_img, rximr);

	halrf_wreg(rf, 0x800c, MASKDWORD, reg_0x800c);
	halrf_wreg(rf, 0x8018, MASKDWORD, reg_0x8018);
	halrf_wreg(rf, 0x801c, MASKDWORD, reg_0x801c);
	halrf_wreg(rf, 0x81cc, MASKDWORD, reg_0x81cc);
	halrf_wreg(rf, 0x82cc, MASKDWORD, reg_0x82cc);

	return rximr;
}

#if 0
__iram_func__
void halrf_doiqk_8852b(struct rf_info *rf, bool force, enum phl_phy_idx phy_idx, u8 path)
{


	u32 backup_mac[2] = {0x0};
	u32 backup_bb[2] = {0x0};
	u32 backup_rf0[6] = {0x0};
	u32 backup_rf1[6] = {0x0};
	u32 backup_mac_reg[1] = {0x0};
	u32 backup_bb_reg[1] = {0x2344};
	u32 backup_rf_reg0[6] = {0xef, 0xde, 0x0, 0x1e, 0x2, 0x5};
	u32 backup_rf_reg1[6] =	{0xef, 0xde, 0x0, 0x1e, 0x2, 0x5};

	struct halrf_iqk_info *iqk_info = &rf->iqk;

	//halrf_btc_rfk_ntfy(rf, ((BIT(phy_idx) << 4) | RF_AB), RF_BTC_IQK, RFK_ONESHOT_START);
	RF_DBG(rf, DBG_RF_IQK, "[IQK]==========IQK strat!!!!!==========\n");
	iqk_info->version = iqk_version_8852b;
	iqk_info->iqk_step = 0;
	iqk_info->rxiqk_step = 0;
	iqk_info->reload_cnt = 0;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]Test Ver 0x%x\n", iqk_version);
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]Test Ver 0x%x\n", 0x2);
	//u32 addr = 0x0;
	//for (addr = 0x8000; addr < 0x8300; addr += 0x4)
	//	RF_DBG(rf, DBG_RF_IQK, "[IQK]  %8x,  %8x \n", addr, halrf_rreg(rf, addr + 0x4, MASKDWORD));

	if (iqk_mcc_page_sel_8852b(rf,phy_idx, path))
		return;
	iqk_get_ch_info_8852b(rf,phy_idx, path);
	iqk_backup_mac_bb_8852b(rf, path, backup_mac, backup_bb, backup_mac_reg, backup_bb_reg);
	iqk_backup_rf0_8852b(rf, path, backup_rf0, backup_rf_reg0);
	iqk_backup_rf1_8852b(rf, path, backup_rf1, backup_rf_reg1);
	iqk_macbb_setting_8852b(rf, phy_idx, path);
	iqk_preset_8852b(rf, path);
	iqk_start_iqk_8852b(rf, phy_idx, path);
	iqk_restore_8852b(rf, path);
	iqk_afebb_restore_8852b(rf, phy_idx, path);	
	iqk_restore_mac_bb_8852b(rf, path, backup_mac, backup_bb, backup_mac_reg, backup_bb_reg);
	iqk_restore_rf0_8852b(rf, path, backup_rf0, backup_rf_reg0);
	iqk_restore_rf1_8852b(rf, path, backup_rf1, backup_rf_reg1);
	iqk_info->iqk_times++;
	//halrf_btc_rfk_ntfy(rf, ((BIT(phy_idx) << 4) | RF_AB), RF_BTC_IQK, RFK_ONESHOT_STOP);	
	RF_DBG(rf, DBG_RF_IQK, "[IQK]==========IQK End!!!!!==========\n");
	return;
}

__iram_func__
void halrf_iqk_8852b(struct rf_info *rf, enum phl_phy_idx phy_idx, bool force)
{
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===>%s\n", __func__);
	iqk_init_8852b(rf);
	switch(halrf_kpath_8852b(rf, phy_idx)) {
	case RF_A:
		halrf_doiqk_8852b(rf, force, phy_idx, RF_PATH_A);
		break;
	case RF_B:		
		halrf_doiqk_8852b(rf, force, phy_idx, RF_PATH_B);
		break;
	case RF_AB:		
		halrf_doiqk_8852b(rf, force, phy_idx, RF_PATH_A);
		halrf_doiqk_8852b(rf, force, phy_idx, RF_PATH_B);
		break;
	default:
		break;
	}
	return;
}
#endif

#endif



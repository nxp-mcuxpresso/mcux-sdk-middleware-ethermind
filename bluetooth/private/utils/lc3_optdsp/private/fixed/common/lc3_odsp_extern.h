
/**
 *  \file lc3_extern.h
 *
 *  \brief This file contains external data stuctures of LC3 encoder, decoder.
 */

/*
 *  Copyright (C) 2021. Mindtree Ltd.
 *  All rights reserved.
 */
#if defined(LC3_DSP) && (LC3_DSP == 2)
#ifndef _H_LC3_ODSP_EXTERN_
#define _H_LC3_ODSP_EXTERN_

/* --------------------------------------------- Header File Inclusion */


/* --------------------------------------------- Global Definitions */
extern DATA_ALIGN const INT16 odsp_mdct_window_N80[130];
extern DATA_ALIGN const INT16 odsp_mdct_window_N160[260];
extern DATA_ALIGN const INT16 odsp_mdct_window_N240[390];
extern DATA_ALIGN const INT16 odsp_mdct_window_N320[520];
extern DATA_ALIGN const INT16 odsp_mdct_window_N480[780];

#ifdef LC3_ENABLE_7_5MS_MODE
extern DATA_ALIGN const INT16 odsp_mdct_window_N60_7_5ms[106];
extern DATA_ALIGN const INT16 odsp_mdct_window_N120_7_5ms[212];
extern DATA_ALIGN const INT16 odsp_mdct_window_N180_7_5ms[318];
extern DATA_ALIGN const INT16 odsp_mdct_window_N240_7_5ms[424];
extern DATA_ALIGN const INT16 odsp_mdct_window_N360_7_5ms[636];
#endif /* LC3_ENABLE_7_5MS_MODE */

extern DATA_ALIGN const INT32 odsp_tns_acf_lagwindow[8];
//extern DATA_ALIGN const INT32 odsp_tns_acf_lagwindow[9];
extern DATA_ALIGN const INT16 odsp_tns_de_quant_lut[17];

extern DATA_ALIGN const INT8   odsp_ac_spec_lookup[4096];
extern DATA_ALIGN const UINT16 odsp_ac_spec_cumfreq[64][17];
extern DATA_ALIGN const UINT16 odsp_ac_spec_freq[64][17];
extern DATA_ALIGN const UINT16 odsp_ari_spec_bits[64][17];

extern DATA_ALIGN const INT16 odsp_ac_tns_order_bits[2][8];
extern DATA_ALIGN const INT16 odsp_ac_tns_order_freq[2][8];
extern DATA_ALIGN const INT16 odsp_ac_tns_order_cumfreq[2][8];
extern DATA_ALIGN const INT16 odsp_ac_tns_coef_bits[8][17];
extern DATA_ALIGN const INT16 odsp_ac_tns_coef_freq[8][17];
extern DATA_ALIGN const INT16 odsp_ac_tns_coef_cumfreq[8][17];

extern DATA_ALIGN const INT16 *const odsp_sns_pre_emphasis[5];
extern DATA_ALIGN const INT16 *const odsp_sns_pre_emphasis_exp[5];

extern DATA_ALIGN const INT16 *const odsp_bands_indices_10ms[5];
#ifdef LC3_ENABLE_7_5MS_MODE
extern DATA_ALIGN const INT16 *const odsp_bands_indices_7_5ms[5];
#endif /* LC3_ENABLE_7_5MS_MODE */

/* TODO : dynamic  if not full profile */
extern DATA_ALIGN const INT16 odsp_ltpf_resample_filter_8khz[240];
extern DATA_ALIGN const INT16 odsp_ltpf_resample_filter_16khz[240];
extern DATA_ALIGN const INT16 odsp_ltpf_resample_filter_24khz[240];
extern DATA_ALIGN const INT16 odsp_ltpf_resample_filter_32khz[240];
extern DATA_ALIGN const INT16 odsp_ltpf_resample_filter_48khz[240];

extern DATA_ALIGN const INT16 odsp_ltpf_ac_weighting[98];
extern DATA_ALIGN const INT16 odsp_ltpf_pitch_interp_filter[7][9];

extern DATA_ALIGN const INT16 odsp_ltpf_synth_filter_den_8_16khz[4][4];
extern DATA_ALIGN const INT16 odsp_ltpf_synth_filter_den_24khz[4][6];
extern DATA_ALIGN const INT16 odsp_ltpf_synth_filter_den_32khz[4][8];
extern DATA_ALIGN const INT16 odsp_ltpf_synth_filter_den_48khz[4][12];
extern DATA_ALIGN const INT16 odsp_ltpf_synth_filter_num_8_16khz[4][3];
extern DATA_ALIGN const INT16 odsp_ltpf_synth_filter_num_24khz[4][5];
extern DATA_ALIGN const INT16 odsp_ltpf_synth_filter_num_32khz[4][7];
extern DATA_ALIGN const INT16 odsp_ltpf_synth_filter_num_48khz[4][11];

extern DATA_ALIGN const INT16 odsp_ltpf_gain_scale[4];

extern DATA_ALIGN const INT16 odsp_sns_vq_reg_adj_gains[2];
extern DATA_ALIGN const INT16 odsp_sns_vq_reg_lf_adj_gains[4];
extern DATA_ALIGN const INT16 odsp_sns_vq_near_adj_gains[4];
extern DATA_ALIGN const INT16 odsp_sns_vq_far_adj_gains[8];

extern DATA_ALIGN const INT16 odsp_sns_gainMSBbits[4];
extern DATA_ALIGN const INT16 odsp_sns_gainLSBbits[4];

extern DATA_ALIGN const INT16 odsp_sns_LFCB[256];
extern DATA_ALIGN const INT16 odsp_sns_HFCB[256];

extern DATA_ALIGN const UINT32 odsp_MPVQ_offsets_N6_K1[1 + 2];
extern DATA_ALIGN const UINT32 odsp_MPVQ_offsets_N10_K10[10 + 2];
extern DATA_ALIGN const UINT32 odsp_MPVQ_offsets_N16_K10[10 + 2];

extern DATA_ALIGN const INT16 odsp_global_gain_adjust_tables[5][5];

/* TODO : Check DATA_ALIGN */
extern const INT16 odsp_twid_fact_sine_cos_lut_post_fft_480[482];
extern const INT16 odsp_twid_fact_sine_cos_lut_post_fft_360[362];
extern const INT16 odsp_twid_fact_sine_cos_lut_post_fft_320[322];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_60[60];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_80[80];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_120[120];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_160[160];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_180[180];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_240[240];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_320[320];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_360[360];
extern const INT16 odsp_twid_fact_sine_cos_lut_pre_fft_480[480];

extern const INT32 odsp_rotation_vector_40_32[2 * 28];
extern const INT16 odsp_rotation_vector_320[2 * (320 - 20)];
extern const INT16 odsp_rotation_vector_360[2 * (360 - 30)];
extern const INT16 odsp_rotation_vector_480[2 * (480 - 30)];
extern const INT16 odsp_rotation_vector_15_6[2 * (90 - 15)];

extern const UINT32 odsp_pow2_lut1[32];
extern const UINT32 odsp_pow2_lut2[32];
extern const UINT32 odsp_pow2_lut3[32];
extern const INT16 odsp_inverse_integer_lut[32];

extern const INT32 odsp_inverse_sqrt_lut[128 + 2];

extern const INT32 odsp_log2_lut1[16];
extern const INT16 odsp_log2_lut2[16];

extern const INT32 odsp_pow2_s_lut1[64];
extern const INT16 odsp_pow2_s_lut2[64];

extern const INT32 odsp_inverse_sqrt_lut1[32];
extern const INT16 odsp_inverse_sqrt_lut2[32];

extern const INT32 odsp_inverse_lut1[32];
extern const INT16 odsp_inverse_lut2[32];

extern DATA_ALIGN const INT16 odsp_inverse_sqrt_s_lut[1 + 64];

#endif /* _H_LC3_ODSP_EXTERN_ */
#endif /*defined(LC3_DSP) && (LC3_DSP == 2)*/


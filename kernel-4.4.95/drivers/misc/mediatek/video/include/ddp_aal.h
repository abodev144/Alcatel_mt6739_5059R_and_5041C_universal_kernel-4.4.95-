
#ifndef __DDP_AAL_H__
#define __DDP_AAL_H__

#if defined(CONFIG_MACH_MT6799)
#define AAL_HAS_DRE3            (1)
#endif

#if defined(CONFIG_MACH_MT6799) || defined(CONFIG_MACH_MT6763) || \
	defined(CONFIG_MACH_MT6771) || defined(CONFIG_MACH_MT6775)
#define AAL_SUPPORT_KERNEL_API            (1)
#endif

#define AAL_HIST_BIN            33	/* [0..32] */
#define AAL_DRE_POINT_NUM       29

#define AAL_DRE3_HIST_NUM       17
#define AAL_DRE3_POINT_NUM      17
#define AAL_DRE3_LAST_POINT     (AAL_DRE3_POINT_NUM-1)
#define AAL_DRE_BLK_NUM         16
#define AAL_BLK_MAX_ALLOWED_NUM         128

#define AAL_SERVICE_FORCE_UPDATE 0x1

/* Custom "wide" pointer type for 64-bit compatibility. Always cast from uint32_t*. */
/* typedef unsigned long long aal_u32_ptr_t; */
#define aal_u32_handle_t unsigned long long

#define AAL_U32_PTR(x) ((void *)(unsigned long)x)

enum disp_aal_id_t {
	DISP_AAL0 = 0,
	DISP_AAL1,
	DISP_AAL_TOTAL
};

enum AAL_ESS_UD_MODE {
	CONFIG_BY_CUSTOM_LIB = 0,
	CONFIG_TO_LCD = 1,
	CONFIG_TO_AMOLED = 2
};

enum AAL_DRE_MODE {
	DRE_EN_BY_CUSTOM_LIB = 0xFFFF,
	DRE_OFF = 0,
	DRE_ON = 1
};

enum AAL_ESS_MODE {
	ESS_EN_BY_CUSTOM_LIB = 0xFFFF,
	ESS_OFF = 0,
	ESS_ON = 1
};

enum AAL_ESS_LEVEL {
	ESS_LEVEL_BY_CUSTOM_LIB = 0xFFFF
};

#define AAL_CONTROL_CMD(ID, CONTROL) (ID << 16 | CONTROL)

struct DISP_AAL_INITREG {
	/* DRE */
	int dre_map_bypass;
	/* ESS */
	int cabc_gainlmt[33];
#ifdef AAL_HAS_DRE3
	/* DRE 3.0 Reg. */
	int dre_s_lower;
	int dre_s_upper;
	int dre_y_lower;
	int dre_y_upper;
	int dre_h_lower;
	int dre_h_upper;
	int dre_x_alpha_base;
	int dre_x_alpha_shift_bit;
	int dre_y_alpha_base;
	int dre_y_alpha_shift_bit;
	int act_win_x_end;
	int dre_blk_x_num;
	int dre_blk_y_num;
	int dre_blk_height;
	int dre_blk_width;
	int dre_blk_area;
	int dre_blk_area_min;
	int hist_bin_type;
	int dre_flat_length_slope;
#endif
};

struct DISP_DRE30_INIT {
	/* DRE 3.0 SW */
	aal_u32_handle_t dre30_hist_addr;
};

struct DISP_AAL_DISPLAY_SIZE {
	int width;
	int height;
};

struct DISP_DRE30_HIST {
	int dre_max_hist[AAL_DRE_BLK_NUM][AAL_DRE_BLK_NUM][AAL_DRE3_HIST_NUM];
	int dre_rgb_max_sum[AAL_DRE_BLK_NUM][AAL_DRE_BLK_NUM];
	int dre_large_diff_count_set[AAL_DRE_BLK_NUM][AAL_DRE_BLK_NUM];
	int dre_max_diff_set[AAL_DRE_BLK_NUM][AAL_DRE_BLK_NUM];
	int dre_chroma_hist[AAL_DRE_BLK_NUM][AAL_DRE_BLK_NUM];
	int dre_flat_line_count_set[AAL_DRE_BLK_NUM][AAL_DRE_BLK_NUM];
	int dre_blk_x_num;
	int dre_blk_y_num;
};

struct DISP_AAL_HIST {
	unsigned int serviceFlags;
	int backlight;
	int colorHist;
	unsigned int maxHist[AAL_HIST_BIN];
	int requestPartial;
#ifdef AAL_HAS_DRE3
	aal_u32_handle_t dre30_hist;
#endif
#ifdef AAL_SUPPORT_KERNEL_API
	unsigned int panel_type;
	int essStrengthIndex;
	int ess_enable;
	int dre_enable;
#endif
};

struct DISP_AAL_HIST_MODULE {
	int colorHist;
	unsigned int maxHist[AAL_HIST_BIN];
	unsigned int count;
};

enum DISP_AAL_REFRESH_LATENCY {
	AAL_REFRESH_17MS = 17,
	AAL_REFRESH_33MS = 33
};

struct DISP_DRE30_PARAM {
	int dre3_gain[AAL_DRE_BLK_NUM][AAL_DRE_BLK_NUM][AAL_DRE3_POINT_NUM];
};

struct DISP_AAL_PARAM {
	int DREGainFltStatus[AAL_DRE_POINT_NUM];
	int cabc_fltgain_force;	/* 10-bit ; [0,1023] */
	int cabc_gainlmt[33];
	int FinalBacklight;	/* 10-bit ; [0,1023] */
	int allowPartial;
	int refreshLatency;	/* DISP_AAL_REFRESH_LATENCY */
#ifdef AAL_HAS_DRE3
	aal_u32_handle_t dre30_gain;
#endif
};

void disp_aal_on_end_of_frame(void);
void disp_aal_on_end_of_frame_by_module(enum disp_aal_id_t id);

extern int aal_dbg_en;
void aal_test(const char *cmd, char *debug_output);
bool disp_aal_is_support(void);
int aal_is_partial_support(void);
int aal_request_partial_support(int partial);

void disp_aal_notify_backlight_changed(int bl_1024);

void disp_aal_set_lcm_type(unsigned int panel_type);
void disp_aal_set_ess_level(int level);
void disp_aal_set_ess_en(int enable);
void disp_aal_set_dre_en(int enable);

#endif
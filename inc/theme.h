#ifndef THEME_H_
#define THEME_H_

#define THEME_MAGIC "SKYTHEME0.98"

#ifdef CONFIG_GP730_MONO
#define THEME_LEFT 3
#define THEME_RIGHT 5

#define PROGRESSBAR_LEFT 3
#define PROGRESSBAR_MID	 2
#define PROGRESSBAR_RIGHT 3
#define PROGRESSBAR_MIN_H	(PROGRESSBAR_LEFT+PROGRESSBAR_MID+PROGRESSBAR_RIGHT)

#define DEF_EDGE 3

#define BUTTON_MIN_HEIGHT	14
#define BUTTON_MID_HEIGHT	10	

#define TITLE_BEGIN_INTER 5
#define TITLE_END_INTER 7
#define TITLE_CENTER_INTER 2

#define EDITBOX_EDGE 2
#define EDITBOX_DEF_LINE_MAX	5
#define EDITBOX_INNER	2

#define SCROLLBAR_V_WIDTH	4
#define SCROLLBAR_H_HIGHT	SCROLLBAR_V_WIDTH
#define SCROLLBARLEFT	3
#define SCROLLBARRIGHT	3
#define SCROLLBARUP	SCROLLBARLEFT
#define SCROLLBARDOWN	SCROLLBARRIGHT

#define COMBO_MIN_HEIGHT 18
#define COMBO_LIST_EDGE  10
#define COMBO_INNER		 2
#define COMBO_EDGE	     1

#define STRING_IMAGE_INTER 2

#define STATUSBAR_HEIGHT	12

#define STATUSBAR_WLM_TYPE_X	0
#define STATUSBAR_WLM_TYPE_Y	0
#define STATUSBAR_WLM_TYPE_W	8
#define STATUSBAR_WLM_TYPE_H	8

#define STATUSBAR_WLM_SIGNAL_X	2
#define STATUSBAR_WLM_SIGNAL_Y	2
#define STATUSBAR_WLM_SIGNAL_W	(STATUSBAR_WLM_TYPE_W+12)
#define STATUSBAR_WLM_SIGNAL_H	10


#define STATUSBAR_TIME_X		48	
#define STATUSBAR_TIME_Y		0
#define STATUSBAR_TIME_W		30	
#define STATUSBAR_TIME_H		12

#define STATUSBAR_BATTERY_X		110
#define STATUSBAR_BATTERY_Y		2
#define STATUSBAR_BATTERY_W		16
#define STATUSBAR_BATTERY_H		8
#define STATUSBAR_BATTERYBG_X	3
#define STATUSBAR_BATTERYBG_Y	3
#define STATUSBAR_BATTERYBG_WIDTH	3

#define STATUSBAR_WIFI_SIGNAL_X	(STATUSBAR_WLM_SIGNAL_W+STATUSBAR_WLM_SIGNAL_X)
#define STATUSBAR_WIFI_SIGNAL_Y	0
#define STATUSBAR_WIFI_SIGNAL_W	12
#define STATUSBAR_WIFI_SIGNAL_H	10

#define DRAG_LENG 12
#define STATUS_IMAGE "mono_status.png"

#else

#define THEME_LEFT 4
#define THEME_RIGHT 4

//#define PROGRESSBAR_LEFT 6
//#define PROGRESSBAR_RIGHT 6

#define PROGRESSBAR_LEFT 4
#define PROGRESSBAR_MID 4
#define PROGRESSBAR_RIGHT 4
#define PROGRESSBAR_MIN_H	(PROGRESSBAR_LEFT+PROGRESSBAR_MID+PROGRESSBAR_RIGHT)

#define DEF_EDGE 6

#define BUTTON_MIN_HEIGHT	24
#define BUTTON_MID_HEIGHT	16	

#define TITLE_BEGIN_INTER 10
#define TITLE_END_INTER 10
#define TITLE_CENTER_INTER 7

#define EDITBOX_EDGE 2
#define EDITBOX_DEF_LINE_MAX	5
#define EDITBOX_INNER	5

#define SCROLLBAR_V_WIDTH	8
#define SCROLLBAR_H_HIGHT	SCROLLBAR_V_WIDTH
#define SCROLLBARLEFT	3
#define SCROLLBARRIGHT	3
#define SCROLLBARUP	SCROLLBARLEFT
#define SCROLLBARDOWN	SCROLLBARRIGHT

#define COMBO_MIN_HEIGHT 24
#define COMBO_LIST_EDGE  30
#define COMBO_INNER		 5
#define COMBO_EDGE	     2

#define STRING_IMAGE_INTER 5
#define STATUSBAR_HEIGHT	22

#define STATUSBAR_WLM_TYPE_X	0
#define STATUSBAR_WLM_TYPE_Y	0
#define STATUSBAR_WLM_TYPE_W	20
#define STATUSBAR_WLM_TYPE_H	20

#define STATUSBAR_WLM_SIGNAL_X	10
#define STATUSBAR_WLM_SIGNAL_Y	3
#define STATUSBAR_WLM_SIGNAL_W	(STATUSBAR_WLM_TYPE_W+19)
#define STATUSBAR_WLM_SIGNAL_H	20

#define STATUSBAR_TIME_X	100
#define STATUSBAR_TIME_Y	3
#define STATUSBAR_TIME_W	40	
#define STATUSBAR_TIME_H	16

#define STATUSBAR_BATTERY_X	(sys.video->sur->width-30)//210
#define STATUSBAR_BATTERY_Y	3
#define STATUSBAR_BATTERY_W	22
#define STATUSBAR_BATTERY_H	12
#define STATUSBAR_BATTERYBG_X	1
#define STATUSBAR_BATTERYBG_Y	1
#define STATUSBAR_BATTERYBG_WIDTH	6

#define STATUSBAR_WIFI_SIGNAL_X	(STATUSBAR_WLM_SIGNAL_W+STATUSBAR_WLM_SIGNAL_X)
#define STATUSBAR_WIFI_SIGNAL_Y	3
#define STATUSBAR_WIFI_SIGNAL_W	20
#define STATUSBAR_WIFI_SIGNAL_H	20

#define DRAG_LENG 16
#define STATUS_IMAGE "color_status.png"
#endif


typedef enum {
    DEFAULT = 0,
    DISABLE = 1,
    PRESSED = 2,
    NUM_STA = 3
}ctrl_status_t;

typedef struct {
    char version[20];
    color_t default_bg;
    color_t default_fg;
    color_t disable_fg;
    image_t btn[NUM_STA];
    image_t chk_off[NUM_STA];
    image_t chk_on[NUM_STA];
    image_t rdi_off[NUM_STA];
    image_t rdi_on[NUM_STA];
    image_t lst[NUM_STA];
    image_t tit_cls[NUM_STA];
	image_t progress_bar[2];
	image_t combobox;
	image_t editbox;
	image_t messagebox;
	image_t scrollbar_bg_h;
	image_t scrollbar_bg_v;
	image_t scrollbar_h;
	image_t scrollbar_v;
	image_t battery_empty;
	image_t battery_adapter;
	image_t battery_charge;
	image_t battery_red;
	image_t battery_green;
	image_t wlsignal[6];
	image_t wifisignal[4];
	image_t nettype[3];
    image_t tit_bar;
	image_t text_def;

}theme_t;

#endif

/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 * Quadstone Ltd.             Tel: +44 131 220 4491
 * 16 Chester Street          Fax: +44 131 220 4492
 * Edinburgh, EH3 7RA, UK     WWW: http://www.paramics-online.com
 *
 * This file defines the constants required for a plugin.
 * ----------------------------------------------------------------------- */ 

#ifndef _API_CONSTANTS_H_
#define _API_CONSTANTS_H_

/* -------- Constants ---------------------------------------------------- */

/* -------- Hazard values returned by link_hazard() */

#define APIHAZ_NONE             0  
#define APIHAZ_FORK             1
#define APIHAZ_DIVERGE          2
#define APIHAZ_SPLIT            3       
#define APIHAZ_CONFLUENCE       4  
#define APIHAZ_RAMP	        5  
#define APIHAZ_YIELD            6
#define APIHAZ_CLOSURE          7
#define APIHAZ_WIDEN            8
#define APIHAZ_TJUNCTION        9
#define APIHAZ_CROSSROADS      10
#define APIHAZ_LEFTTURN        11
#define APIHAZ_RIGHTTURN       12
#define APIHAZ_SIGNALS	       13

/* --------- Types for vehicle_tracer_set() */

#define TRACER_HEADWAY  1
#define TRACER_DISTANCE 2  

/* --------- Parameter types for loop_set() / loop_state() */

#define APILOOP_INCOMPLETE  1
#define APILOOP_COMPLETE    2
#define APILOOP_SMOOTHED    3
#define APILOOP_TOTAL       4
#define APILOOP_FALLING     5
#define APILOOP_RISING      6
#define APILOOP_FAULTY      7
#define APILOOP_SUSPECT     8
#define APILOOP_RESET       9

#define APILOOP_UPSTREAM    11
#define APILOOP_DOWNSTREAM  12

/* --------- Action Types for signal_action() */

#define API_ACTION_HOLD 		1
#define API_ACTION_FREE			2
#define API_ACTION_VARIABLE		3
#define API_ACTION_FIXED		4
#define API_ACTION_CURRENT_GREEN	5
#define API_ACTION_NEXT_GREEN		6
#define API_ACTION_MINIMUM_GREEN	7
#define API_ACTION_MAXIMUM_GREEN	8
#define API_ACTION_STORED_GREEN		9
#define API_ACTION_STORED_RED		10
#define API_ACTION_OFFSET		11

/* -------- Action Modes for signal_action() */

#define API_ACTIONMODE_NONE		 0
#define API_ACTIONMODE_SET 		 1
#define API_ACTIONMODE_INCREMENT	 2
#define API_ACTIONMODE_DECREMENT	 3

/* --------- Inquiry types for signal_enquiry() */

#define API_INQUIRY_RUNNING		1
#define API_INQUIRY_CYCLE_TIME		2
#define API_INQUIRY_EXPIRED_TIME	3
#define API_INQUIRY_STORED_GREEN	4
#define API_INQUIRY_CURRENT_GREEN	5
#define API_INQUIRY_NEXT_GREEN		6
#define API_INQUIRY_MAXIMUM_GREEN	7
#define API_INQUIRY_MINIMUM_GREEN	8
#define API_INQUIRY_STORED_RED		9
#define API_INQUIRY_PHASE		10
#define API_INQUIRY_OFFSET		11

/* --------- Priority settings for link_priority_set() */

#define APIPRI_MAJOR           0
#define APIPRI_MEDIUM          1
#define APIPRI_MINOR           2
#define APIPRI_BARRED          3

/* --------- Graphics settings including signal head styles */

#define APISIGSTYLE_DEFAULT             0
#define APISIGSTYLE_BULB_LEFT           1
#define APISIGSTYLE_BULB_RIGHT          2
#define APISIGSTYLE_BULB_LEFTANDRIGHT   3
#define APISIGSTYLE_BULB_BYLANE         4

#define APISIGIDX_BULB_TOP    0
#define APISIGIDX_BULB_MIDDLE 1
#define APISIGIDX_BULB_BOTTEM 2
#define APISIGIDX_BULB_ALL    3
#define APISIGIDX_BULB_NONE   4 

#define APIFILL_DEFAULT         0
#define APIFILL_SHADOW          1
#define APIFILL_SPARE           3
#define APIFILL_SHADOW2         4
#define APIFILL_CLOSED          5
#define APIFILL_CLOSED_ALT      6
#define APIFILL_CLOSED_LEFT     7
#define APIFILL_CLOSED_LEFT_ALT 8
#define APIFILL_CUT             9

#define APIARROW_HEAD	    1
#define APIARROW_TAIL	    2
#define APIARROW_MID	    3

#define APITAG_TRANGLE	    1
#define APITAG_CIRCLE	    2
#define APITAG_SQUARE	    3
#define APITAG_CROSS	    4
#define APITAG_IBAR	    5
#define APITAG_TBAR	    6
#define APITAG_HOOP	    7
#define APITAG_NONE         8

#define APIKEY_EVENT        1
#define APIKEY_BANDED       2

#define API_MODELVIEW       0x1700
#define API_PROJECTION      0x1701
#define API_TEXTURE         0x1702

#define API_LINE	    0x0003
#define API_LOOP	    0x0002
#define API_POLYGON	    0x0009
#define API_TRIANGLE        0x0004

#define APILINE_DEFAULT     0
#define APILINE_SIM         1 
#define APILINE_MID         2    
#define APILINE_MAP         3

#define APISTART_NODEA      1
#define APISTART_NODEB      2


/* arguments for qpg_DRW_layerVisible() */ 
#define APIOBJ_ROADS	         0
#define APIOBJ_ZONECON     	     1
#define APIOBJ_TEXT	             3
#define APIOBJ_DENSITY	         4
#define APIOBJ_LINK_TEXT		 5
#define APIOBJ_VEHICLES			 6
#define APIOBJ_FLOWS	         8
#define APIOBJ_ANNOT	        10 
#define APIOBJ_LIGHTS	        11 
#define APIOBJ_RESTRICTIONS    	13
#define APIOBJ_STOPLINES    	17
#define APIOBJ_BUSSTOPS       	18 
#define APIOBJ_CURR_ZONE      	19
#define APIOBJ_HAZARDS        	20
#define APIOBJ_GRID          	21
#define APIOBJ_HOTSPOTS       	22
#define APIOBJ_MIDLINES         23
#define APIOBJ_EVENTS         	24
#define APIOBJ_CURR_REGION     	25
#define APIOBJ_LOOPS          	26
#define APIOBJ_RULES          	27
#define APIOBJ_BEACONS        	28
#define APIOBJ_RESPONSE       	29 
#define APIOBJ_RFLOWS         	30
#define APIOBJ_CLOSURES       	31
#define APIOBJ_ARROWS         	32
#define APIOBJ_CARPARKS      	33
#define APIOBJ_BARREDTURNS    	35
#define APIOBJ_OVERLAY       	36
#define APIOBJ_FASTNAV       	37
#define APIOBJ_BUSROUTE         38
#define APIOBJ_NEXTLANES        39
#define APIOBJ_SPEED            65
#define APIOBJ_CURR_CRPK		66
#define APIOBJ_INCIDENTS        67
#define APIOBJ_DEMAND           68
#define APIOBJ_TARMAC           71
#define APIOBJ_LANECHOICES		72
#define APIOBJ_LINKVISIBILITY	73
#define APIOBJ_NETWORK_SKELETON	75
#define APIOBJ_SIGNPOSTS		76
#define APIOBJ_ZONE_BOUNDARIES	77
#define APIOBJ_ZONE_SECTORS		78
#define APIOBJ_CAMERA_POSITIONS	79
#define APIOBJ_ENVIRONMENT		80
#define APIOBJ_OVERLAYS			81
#define APIOBJ_PSG_WAIT_TIMES	82
#define APIOBJ_PMX_MODELS		83
#define APIOBJ_PRESET_VIEWS_POS	84
#define APIOBJ_RELEASE_QUOTAS	85
#define APIOBJ_ROADSTYLE		86
#define APIOBJ_STOPLINEREROUTE	87
#define APIOBJ_CARPARK_NAMES	88
#define APIOBJ_CARPARK_STATS	89
#define APIOBJ_LOOP_NAMES		90
#define APIOBJ_LOOP_STATS		91
#define APIOBJ_INCIDENT_DESC	92
#define APIOBJ_RELBLOCK_VALUES  93
#define APIOBJ_BEACON_NAMES	    94
#define APIOBJ_ZONE_NAMES	    95
#define APIOBJ_NODE_COORDS	    96
#define APIOBJ_ACTIVATIONAREAS	97
#define APIOBJ_WAYPOINTROUTING  98
#define APIOBJ_WAYPOINTZONES	99
#define APIOBJ_BINGMAPS			100

// Removed in 6.2
/* arguments for qpg_DRW_layerColour() & qps_DRW_layerColour() */
//#define  APICOL_ARROW	         0
//#define  APICOL_BUSSTOP 	 1 
//#define  APICOL_GRID    	 2 
//#define  APICOL_HOTSPOT 	 3 
//#define  APICOL_LANECL  	 4 
//#define  APICOL_STOPLINE    	 5 
//#define  APICOL_ROADS   	 6 
//#define  APICOL_NODES   	 7 
//#define  APICOL_LINKS   	 8 
//#define  APICOL_TC  	  	 9
//#define  APICOL_OVERLAY         10
//#define  APICOL_BACKGROUND      11
//#define  APICOL_TARMAC          12
//#define  APICOL_OD              13
//#define  APICOL_BLOCKING        14
//#define  APICOL_ZONES_OBJ       27
//#define  APICOL_CONNECTORS_OBJ  28
//#define  APICOL_SIGHEADS_OBJ    29
//#define  APICOL_MIDLINES_OBJ    30 
//#define  APICOL_NEXTLANES_OBJ   31
//#define  APICOL_BARREDTURNS_OBJ 32
//#define  APICOL_LOOPS_OBJ       33
//#define  APICOL_VMS_OBJ         34
//#define  APICOL_MINORLINKS_OBJ  35
//#define  APICOL_MAJORLINKS_OBJ  36
//#define  APICOL_BUSLANES_OBJ  37
//
//#define  APICOL_API1_OBJ        15
//#define  APICOL_API2_OBJ        16
//#define  APICOL_API3_OBJ        17
//#define  APICOL_API4_OBJ        18
//#define  APICOL_API5_OBJ        19
//#define  APICOL_API6_OBJ        20
//#define  APICOL_API7_OBJ        21
//#define  APICOL_API8_OBJ        22
//#define  APICOL_API9_OBJ        23
//#define  APICOL_API10_OBJ       24
//#define  APICOL_API11_OBJ       25
//#define  APICOL_API12_OBJ       26


/* --------- Position data --------------------------------- */
#define	APIKERB_OUTSIDE_START	1
#define	APIKERB_OUTSIDE_END	2
#define	APIKERB_INSIDE_START	3
#define	APIKERB_INSIDE_END	4

#define	APISTOPLINE_ENTRY	5
#define	APISTOPLINE_EXIT	6

#define APICURVE_CENTRE		7
#define APICURVE_OUTSIDE	8


/* --------- Random Numbers  ------------------------------- */
#define APIRNG_MISC			0
#define APIRNG_RELEASE		1
#define APIRNG_VTYPE		2
#define APIRNG_ROUTE		3
#define APIRNG_DYNAMIC		4
#define APIRNG_TOLL			5
#define APIRNG_INCIDENT		6
#define APIRNG_LANECHOICE		7
#define APIRNG_FREEWAYLANES		8
#define APIRNG_BLOCKEDRELEASE	9

/* --------- Zone Types ------------------------------------ */

#define APIZONE_SINK	        0 
#define APIZONE_INZONE          1		   
#define APIZONE_ANYCRPK         2
#define APIZONE_SPECCRPK        3 

/* bus dwell times */
#define API_DEWLL_TIME_PASSENGER 1
#define API_DWELL_TIME_SPECIFIC  2
#define API_DWELL_TIME_MEAN      3

/* test menu options */
#define API_TESTMODE_NO_TRAFFIC		0
#define API_TESTMODE_CONT_OCC		1
#define API_TESTMODE_FORCE_OCC		2
#define API_TESTMODE_NORMAL			3

// Text size indices for qps_DRW_stringRotated 
#define APITEXTSIZE_NODE		1
#define APITEXTSIZE_LINK		2
#define APITEXTSIZE_ZONE		3
#define APITEXTSIZE_BUS 		4
#define APITEXTSIZE_HAZARD	5
#define APITEXTSIZE_DEMAND	6
#define APITEXTSIZE_TURNCOUNTS   7
#define APITEXTSIZE_ODPATHS      8
#define APITEXTSIZE_SPARE1       9
#define APITEXTSIZE_SPARE2       10
#define APITEXTSIZE_LOOPS        11
#define APITEXTSIZE_CARPARK      12
#define APITEXTSIZE_UNRELEASED   13
#define APITEXTSIZE_VMS          14

/* Units mode constants for functions: qpg_UTL_qpg_UTL_toExternal_*_NGM etc. */
#define APIUNITS_UK_MODE		0
#define APIUNITS_US_MODE		1
#define APIUNITS_METRIC_MODE	2

/* product type */
#define APIPRODUCT_MODELLER   0
#define APIPRODUCT_ANALYSER   1
#define APIPRODUCT_BATCH      2
#define APIPRODUCT_REDUCER    3
#define APIPRODUCT_PARALLEL   4
#define APIPRODUCT_PROGRAMMER 5
#define APIPRODUCT_MONITOR    6
#define APIPRODUCT_PROCESSOR  7
#define APIPRODUCT_NETVIEWER  8 
#define APIPRODUCT_CONVERTER  9 
#define APIPRODUCT_ESTIMATOR  10 
#define APIPRODUCT_PNODE	  11

// key presses for qpx_GUI_keyPress and qpx_GUI_keyRelease
#define APIKEY_Escape 0x01000000
#define APIKEY_Tab 0x01000001
#define APIKEY_Backtab 0x01000002
#define APIKEY_Backspace 0x01000003
#define APIKEY_Return 0x01000004
#define APIKEY_Enter 0x01000005
#define APIKEY_Insert 0x01000006
#define APIKEY_Delete 0x01000007
#define APIKEY_Pause 0x01000008
#define APIKEY_Print 0x01000009
#define APIKEY_SysReq 0x0100000a
#define APIKEY_Clear 0x0100000b
#define APIKEY_Home 0x01000010
#define APIKEY_End 0x01000011
#define APIKEY_Left 0x01000012
#define APIKEY_Up 0x01000013
#define APIKEY_Right 0x01000014
#define APIKEY_Down 0x01000015
#define APIKEY_PageUp 0x01000016
#define APIKEY_PageDown 0x01000017
#define APIKEY_Shift 0x01000020
#define APIKEY_Control 0x01000021
#define APIKEY_Meta 0x01000022
#define APIKEY_Alt 0x01000023
#define APIKEY_AltGr 0x01001103
#define APIKEY_CapsLock 0x01000024
#define APIKEY_NumLock 0x01000025
#define APIKEY_ScrollLock 0x01000026
#define APIKEY_F1 0x01000030
#define APIKEY_F2 0x01000031
#define APIKEY_F3 0x01000032
#define APIKEY_F4 0x01000033
#define APIKEY_F5 0x01000034
#define APIKEY_F6 0x01000035
#define APIKEY_F7 0x01000036
#define APIKEY_F8 0x01000037
#define APIKEY_F9 0x01000038
#define APIKEY_F10 0x01000039
#define APIKEY_F11 0x0100003a
#define APIKEY_F12 0x0100003b
#define APIKEY_F13 0x0100003c
#define APIKEY_F14 0x0100003d
#define APIKEY_F15 0x0100003e
#define APIKEY_F16 0x0100003f
#define APIKEY_F17 0x01000040
#define APIKEY_F18 0x01000041
#define APIKEY_F19 0x01000042
#define APIKEY_F20 0x01000043
#define APIKEY_F21 0x01000044
#define APIKEY_F22 0x01000045
#define APIKEY_F23 0x01000046
#define APIKEY_F24 0x01000047
#define APIKEY_F25 0x01000048
#define APIKEY_F26 0x01000049
#define APIKEY_F27 0x0100004a
#define APIKEY_F28 0x0100004b
#define APIKEY_F29 0x0100004c
#define APIKEY_F30 0x0100004d
#define APIKEY_F31 0x0100004e
#define APIKEY_F32 0x0100004f
#define APIKEY_F33 0x01000050
#define APIKEY_F34 0x01000051
#define APIKEY_F35 0x01000052
#define APIKEY_Super_L 0x01000053
#define APIKEY_Super_R 0x01000054
#define APIKEY_Menu 0x01000055
#define APIKEY_Hyper_L 0x01000056
#define APIKEY_Hyper_R 0x01000057
#define APIKEY_Help 0x01000058
#define APIKEY_Direction_L 0x01000059
#define APIKEY_Direction_R 0x01000060
#define APIKEY_Space 0x20
#define APIKEY_Any Key_Space
#define APIKEY_Exclam 0x21
#define APIKEY_QuoteDbl 0x22
#define APIKEY_NumberSign 0x23
#define APIKEY_Dollar 0x24
#define APIKEY_Percent 0x25
#define APIKEY_Ampersand 0x26
#define APIKEY_Apostrophe 0x27
#define APIKEY_ParenLeft 0x28
#define APIKEY_ParenRight 0x29
#define APIKEY_Asterisk 0x2a
#define APIKEY_Plus 0x2b
#define APIKEY_Comma 0x2c
#define APIKEY_Minus 0x2d
#define APIKEY_Period 0x2e
#define APIKEY_Slash 0x2f
#define APIKEY_0 0x30
#define APIKEY_1 0x31
#define APIKEY_2 0x32
#define APIKEY_3 0x33
#define APIKEY_4 0x34
#define APIKEY_5 0x35
#define APIKEY_6 0x36
#define APIKEY_7 0x37
#define APIKEY_8 0x38
#define APIKEY_9 0x39
#define APIKEY_Colon 0x3a
#define APIKEY_Semicolon 0x3b
#define APIKEY_Less 0x3c
#define APIKEY_Equal 0x3d
#define APIKEY_Greater 0x3e
#define APIKEY_Question 0x3f
#define APIKEY_At 0x40
#define APIKEY_A 0x41
#define APIKEY_B 0x42
#define APIKEY_C 0x43
#define APIKEY_D 0x44
#define APIKEY_E 0x45
#define APIKEY_F 0x46
#define APIKEY_G 0x47
#define APIKEY_H 0x48
#define APIKEY_I 0x49
#define APIKEY_J 0x4a
#define APIKEY_K 0x4b
#define APIKEY_L 0x4c
#define APIKEY_M 0x4d
#define APIKEY_N 0x4e
#define APIKEY_O 0x4f
#define APIKEY_P 0x50
#define APIKEY_Q 0x51
#define APIKEY_R 0x52
#define APIKEY_S 0x53
#define APIKEY_T 0x54
#define APIKEY_U 0x55
#define APIKEY_V 0x56
#define APIKEY_W 0x57
#define APIKEY_X 0x58
#define APIKEY_Y 0x59
#define APIKEY_Z 0x5a
#define APIKEY_BracketLeft 0x5b
#define APIKEY_Backslash 0x5c
#define APIKEY_BracketRight 0x5d
#define APIKEY_AsciiCircum 0x5e
#define APIKEY_Underscore 0x5f
#define APIKEY_QuoteLeft 0x60
#define APIKEY_BraceLeft 0x7b
#define APIKEY_Bar 0x7c
#define APIKEY_BraceRight 0x7d
#define APIKEY_AsciiTilde 0x7e
#define APIKEY_nobreakspace 0x0a0
#define APIKEY_exclamdown 0x0a1
#define APIKEY_cent 0x0a2
#define APIKEY_sterling 0x0a3
#define APIKEY_currency 0x0a4
#define APIKEY_yen 0x0a5
#define APIKEY_brokenbar 0x0a6
#define APIKEY_section 0x0a7
#define APIKEY_diaeresis 0x0a8
#define APIKEY_copyright 0x0a9
#define APIKEY_ordfeminine 0x0aa
#define APIKEY_guillemotleft 0x0ab
#define APIKEY_notsign 0x0ac
#define APIKEY_hyphen 0x0ad
#define APIKEY_registered 0x0ae
#define APIKEY_macron 0x0af
#define APIKEY_degree 0x0b0
#define APIKEY_plusminus 0x0b1
#define APIKEY_twosuperior 0x0b2
#define APIKEY_threesuperior 0x0b3
#define APIKEY_acute 0x0b4
#define APIKEY_mu 0x0b5
#define APIKEY_paragraph 0x0b6
#define APIKEY_periodcentered 0x0b7
#define APIKEY_cedilla 0x0b8
#define APIKEY_onesuperior 0x0b9
#define APIKEY_masculine 0x0ba
#define APIKEY_guillemotright 0x0bb
#define APIKEY_onequarter 0x0bc
#define APIKEY_onehalf 0x0bd
#define APIKEY_threequarters 0x0be
#define APIKEY_questiondown 0x0bf
#define APIKEY_Agrave 0x0c0
#define APIKEY_Aacute 0x0c1
#define APIKEY_Acircumflex 0x0c2
#define APIKEY_Atilde 0x0c3
#define APIKEY_Adiaeresis 0x0c4
#define APIKEY_Aring 0x0c5
#define APIKEY_AE 0x0c6
#define APIKEY_Ccedilla 0x0c7
#define APIKEY_Egrave 0x0c8
#define APIKEY_Eacute 0x0c9
#define APIKEY_Ecircumflex 0x0ca
#define APIKEY_Ediaeresis 0x0cb
#define APIKEY_Igrave 0x0cc
#define APIKEY_Iacute 0x0cd
#define APIKEY_Icircumflex 0x0ce
#define APIKEY_Idiaeresis 0x0cf
#define APIKEY_ETH 0x0d0
#define APIKEY_Ntilde 0x0d1
#define APIKEY_Ograve 0x0d2
#define APIKEY_Oacute 0x0d3
#define APIKEY_Ocircumflex 0x0d4
#define APIKEY_Otilde 0x0d5
#define APIKEY_Odiaeresis 0x0d6
#define APIKEY_multiply 0x0d7
#define APIKEY_Ooblique 0x0d8
#define APIKEY_Ugrave 0x0d9
#define APIKEY_Uacute 0x0da
#define APIKEY_Ucircumflex 0x0db
#define APIKEY_Udiaeresis 0x0dc
#define APIKEY_Yacute 0x0dd
#define APIKEY_THORN 0x0de
#define APIKEY_ssharp 0x0df
#define APIKEY_division 0x0f7
#define APIKEY_ydiaeresis 0x0ff
#define APIKEY_Multi_key 0x01001120
#define APIKEY_Codeinput 0x01001137
#define APIKEY_SingleCandidate 0x0100113c
#define APIKEY_MultipleCandidate 0x0100113d
#define APIKEY_PreviousCandidate 0x0100113e
#define APIKEY_Mode_switch 0x0100117e
#define APIKEY_Kanji 0x01001121
#define APIKEY_Muhenkan 0x01001122
#define APIKEY_Henkan 0x01001123
#define APIKEY_Romaji 0x01001124
#define APIKEY_Hiragana 0x01001125
#define APIKEY_Katakana 0x01001126
#define APIKEY_Hiragana_Katakana 0x01001127
#define APIKEY_Zenkaku 0x01001128
#define APIKEY_Hankaku 0x01001129
#define APIKEY_Zenkaku_Hankaku 0x0100112a
#define APIKEY_Touroku 0x0100112b
#define APIKEY_Massyo 0x0100112c
#define APIKEY_Kana_Lock 0x0100112d
#define APIKEY_Kana_Shift 0x0100112e
#define APIKEY_Eisu_Shift 0x0100112f
#define APIKEY_Eisu_toggle 0x01001130
#define APIKEY_Hangul 0x01001131
#define APIKEY_Hangul_Start 0x01001132
#define APIKEY_Hangul_End 0x01001133
#define APIKEY_Hangul_Hanja 0x01001134
#define APIKEY_Hangul_Jamo 0x01001135
#define APIKEY_Hangul_Romaja 0x01001136
#define APIKEY_Hangul_Jeonja 0x01001138
#define APIKEY_Hangul_Banja 0x01001139
#define APIKEY_Hangul_PreHanja 0x0100113a
#define APIKEY_Hangul_PostHanja 0x0100113b
#define APIKEY_Hangul_Special 0x0100113f
#define APIKEY_Dead_Grave 0x01001250
#define APIKEY_Dead_Acute 0x01001251
#define APIKEY_Dead_Circumflex 0x01001252
#define APIKEY_Dead_Tilde 0x01001253
#define APIKEY_Dead_Macron 0x01001254
#define APIKEY_Dead_Breve 0x01001255
#define APIKEY_Dead_Abovedot 0x01001256
#define APIKEY_Dead_Diaeresis 0x01001257
#define APIKEY_Dead_Abovering 0x01001258
#define APIKEY_Dead_Doubleacute 0x01001259
#define APIKEY_Dead_Caron 0x0100125a
#define APIKEY_Dead_Cedilla 0x0100125b
#define APIKEY_Dead_Ogonek 0x0100125c
#define APIKEY_Dead_Iota 0x0100125d
#define APIKEY_Dead_Voiced_Sound 0x0100125e
#define APIKEY_Dead_Semivoiced_Sound 0x0100125f
#define APIKEY_Dead_Belowdot 0x01001260
#define APIKEY_Dead_Hook 0x01001261
#define APIKEY_Dead_Horn 0x01001262
#define APIKEY_Back 0x01000061
#define APIKEY_Forward 0x01000062
#define APIKEY_Stop 0x01000063
#define APIKEY_Refresh 0x01000064
#define APIKEY_VolumeDown 0x01000070
#define APIKEY_VolumeMute 0x01000071
#define APIKEY_VolumeUp 0x01000072
#define APIKEY_BassBoost 0x01000073
#define APIKEY_BassUp 0x01000074
#define APIKEY_BassDown 0x01000075
#define APIKEY_TrebleUp 0x01000076
#define APIKEY_TrebleDown 0x01000077
#define APIKEY_MediaPlay 0x01000080
#define APIKEY_MediaStop 0x01000081
#define APIKEY_MediaPrevious 0x01000082
#define APIKEY_MediaNext 0x01000083
#define APIKEY_MediaRecord 0x01000084
#define APIKEY_HomePage 0x01000090
#define APIKEY_Favorites 0x01000091
#define APIKEY_Search 0x01000092
#define APIKEY_Standby 0x01000093
#define APIKEY_OpenUrl 0x01000094
#define APIKEY_LaunchMail 0x010000a0
#define APIKEY_LaunchMedia 0x010000a1
#define APIKEY_Launch0 0x010000a2
#define APIKEY_Launch1 0x010000a3
#define APIKEY_Launch2 0x010000a4
#define APIKEY_Launch3 0x010000a5
#define APIKEY_Launch4 0x010000a6
#define APIKEY_Launch5 0x010000a7
#define APIKEY_Launch6 0x010000a8
#define APIKEY_Launch7 0x010000a9
#define APIKEY_Launch8 0x010000aa
#define APIKEY_Launch9 0x010000ab
#define APIKEY_LaunchA 0x010000ac
#define APIKEY_LaunchB 0x010000ad
#define APIKEY_LaunchC 0x010000ae
#define APIKEY_LaunchD 0x010000af
#define APIKEY_LaunchE 0x010000b0
#define APIKEY_LaunchF 0x010000b1
#define APIKEY_MediaLast 0x0100ffff
#define APIKEY_unknown 0x01ffffff
#define APIKEY_Call 0x01100004
#define APIKEY_Context1 0x01100000
#define APIKEY_Context2 0x01100001
#define APIKEY_Context3 0x01100002
#define APIKEY_Context4 0x01100003
#define APIKEY_Flip 0x01100006
#define APIKEY_Hangup 0x01100005
#define APIKEY_No 0x01010002
#define APIKEY_Select 0x01010000
#define APIKEY_Yes 0x01010001
#define APIKEY_Execute 0x01020003
#define APIKEY_Printer 0x01020002
#define APIKEY_Play 0x01020005
#define APIKEY_Sleep 0x01020004
#define APIKEY_Zoom 0x01020006
#define APIKEY_Cancel 0x01020001

#endif

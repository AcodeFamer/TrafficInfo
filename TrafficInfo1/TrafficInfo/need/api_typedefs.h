#ifndef _API_TYPEDEFS_
#define _API_TYPEDEFS_

typedef unsigned char  Uchar;
typedef unsigned short Ushrt;
typedef unsigned int   Uint;

#ifdef PFALSE
#undef PFALSE
#endif

#ifdef PTRUE
#undef PTRUE
#endif

#ifdef Bool
#undef Bool
#endif

#ifdef WIN32
typedef enum { PFALSE = 0, PTRUE } Bool;
#else
#define Bool int
#define PTRUE 1
#define PFALSE 0
#endif

#ifdef QPV3_TYPES
#define NODE void
#define LINK void
#define ZONE void
#define VEHICLE void
#else
typedef struct NODE_s NODE;
typedef struct LINK_s LINK;
typedef struct ZONE_s ZONE;
typedef struct VEHICLE_s VEHICLE;
#endif

typedef struct BUSSTOP_s BUSSTOP;
typedef struct BUSROUTE_s BUSROUTE;
typedef struct DETECTOR_s DETECTOR;
typedef struct CARPARK_s CARPARK;
typedef struct BEACON_s BEACON;
typedef struct LOOP_s LOOP;
typedef struct SLIP_s SLIP;
typedef struct RAMP_s RAMP;
typedef struct SECTOR_s SECTOR;
typedef struct BLOCKINGREGION_s BLOCKINGREGION;

typedef struct NET_USERDATA_s NET_USERDATA;
typedef struct NDE_USERDATA_s NDE_USERDATA;
typedef struct LNK_USERDATA_s LNK_USERDATA;
typedef struct ZNE_USERDATA_s ZNE_USERDATA;
typedef struct VHC_USERDATA_s VHC_USERDATA;
typedef struct DTC_USERDATA_s DTC_USERDATA;
typedef struct DTL_USERDATA_s DTL_USERDATA;
typedef struct BCN_USERDATA_s BCN_USERDATA;
typedef struct BST_USERDATA_s BST_USERDATA;
typedef struct BSR_USERDATA_s BSR_USERDATA;
typedef struct CPK_USERDATA_s CPK_USERDATA;
typedef struct RMP_USERDATA_s RMP_USERDATA;
typedef struct SLP_USERDATA_s SLP_USERDATA;

#ifdef WIN32
#ifdef BSMIMPORT
#define BSMDECLSPEC _declspec(dllimport)
#else
#define BSMDECLSPEC _declspec(dllexport)
#endif
#else
#define BSMDECLSPEC
#endif

#endif

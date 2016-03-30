/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 * Quadstone Ltd.             Tel: +44 131 220 4491
 * 16 Chester Street          Fax: +44 131 220 4492
 * Edinburgh,EH3 7RA,UK     WWW: http://www.paramics-online.com
 * ----------------------------------------------------------------------- */ 
/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 *
 * This header defines all the functions that are defined in the plugin
 * and called by Paramics.
 * 
 * ----------------------------------------------------------------------- */ 
#include "api_constants.h"
#include "api_typedefs.h"

/* ----------------------------------------------------------------------- */
/* ------ OVERLOADS ------------------------------------------------------ */
/* ----------------------------------------------------------------------- */

/* ------ Vehicles ------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

PLUGIN_EXPORT_OL(void,qpx_VHC_timeStep,(VEHICLE* vehicle),(vehicle)) 
PLUGIN_EXPORT_OL(void,qpx_LNK_vehicleTimeStep,(LINK* link, VEHICLE* vehicle),(link, vehicle)) 
PLUGIN_EXPORT_OL(void,qpx_VHC_release,(VEHICLE* vehicle),(vehicle))

PLUGIN_EXPORT_OL(void,qpx_VHC_arriveByIndex,(VEHICLE* vehicle, LINK* link, int zone),(vehicle,link,zone))
PLUGIN_EXPORT_OL(void,qpx_VHC_beaconByIndex,(VEHICLE* vehicle, LINK* link, int beacon),(vehicle,link,beacon))
PLUGIN_EXPORT_OL(void,qpx_VHC_detectorByIndex,(VEHICLE* vehicle, LINK* link, int detector),(vehicle,link,detector))
PLUGIN_EXPORT_OL(void,qpx_VHC_arrive,(VEHICLE* vehicle, LINK* link, ZONE* zone),(vehicle,link,zone))
PLUGIN_EXPORT_OL(void,qpx_VHC_beacon,(VEHICLE* vehicle, LINK* link, BEACON* beacon),(vehicle,link,beacon))
PLUGIN_EXPORT_OL(void,qpx_VHC_detector,(VEHICLE* vehicle, LINK* link, DETECTOR* detector),(vehicle,link,detector))
PLUGIN_EXPORT_OL(void,qpx_VHC_laneChange,(VEHICLE* vehicle, LINK* link,int lane1,int lane2),(vehicle,link,lane1,lane2))
PLUGIN_EXPORT_OL(void,qpx_VHC_move,(VEHICLE* vehicle, LINK* link,float distance,float speed),(vehicle,link,distance,speed))
PLUGIN_EXPORT_OL(void,qpx_VHC_targetHeadway,(VEHICLE* vehicle, LINK* link),(vehicle,link))
PLUGIN_EXPORT_OL(void,qpx_VHC_targetSpeed,(VEHICLE* vehicle, LINK* link),(vehicle,link))
PLUGIN_EXPORT_OL(void,qpx_VHC_transfer,(VEHICLE* vehicle, LINK* link1, LINK* link2),(vehicle,link1,link2))
// 6.3.1
PLUGIN_EXPORT_OL(void,qpx_VHC_preRemove,(VEHICLE* vehicle),(vehicle))


PLUGIN_EXPORT_OL(void,qpx_TGV_timeStep,(VEHICLE* vehicle),(vehicle)) 
PLUGIN_EXPORT_OL(void,qpx_TGV_arrive,(VEHICLE* vehicle, LINK* link, ZONE* zone),(vehicle,link,zone))
PLUGIN_EXPORT_OL(void,qpx_TGV_beacon,(VEHICLE* vehicle, LINK* link, BEACON* beacon),(vehicle,link,beacon))
PLUGIN_EXPORT_OL(void,qpx_TGV_detector,(VEHICLE* vehicle, LINK* link, DETECTOR* detector),(vehicle,link,detector))
PLUGIN_EXPORT_OL(void,qpx_TGV_arriveByIndex,(VEHICLE* vehicle, LINK* link, int zone),(vehicle,link,zone))
PLUGIN_EXPORT_OL(void,qpx_TGV_beaconByIndex,(VEHICLE* vehicle, LINK* link, int beacon),(vehicle,link,beacon))
PLUGIN_EXPORT_OL(void,qpx_TGV_detectorByIndex,(VEHICLE* vehicle, LINK* link, int detector),(vehicle,link,detector))
PLUGIN_EXPORT_OL(void,qpx_TGV_laneChange,(VEHICLE* vehicle, LINK* link,int lane1,int lane2),(vehicle,link,lane1,lane2))
PLUGIN_EXPORT_OL(void,qpx_TGV_move,(VEHICLE* vehicle, LINK* link,float distance,float speed),(vehicle,link,distance,speed))
PLUGIN_EXPORT_OL(void,qpx_TGV_targetHeadway,(VEHICLE* vehicle, LINK* link),(vehicle,link))
PLUGIN_EXPORT_OL(void,qpx_TGV_targetSpeed,(VEHICLE* vehicle, LINK* link),(vehicle,link))
PLUGIN_EXPORT_OL(void,qpx_TGV_transfer,(VEHICLE* vehicle, LINK* link1, LINK* link2),(vehicle,link1,link2))

/* ------ FRV's --------------------------------------------------------- */

/* to do */

/* ------ Car Parks ----------------------------------------------------- */

/* to do */

/* ------ Parameter Files ------------------------------------------------ */

PLUGIN_EXPORT_OL(void,qpx_CFG_parameterFile,(char *filename,int count),(filename,count)) 
PLUGIN_EXPORT_OL(void,qpx_GUI_parameterValue,(char *filename,int index,char *label,float value),(filename,index,label,value)) 
PLUGIN_EXPORT_OL(void,qpx_GUI_parameterToggle,(char *filename,int index,char *label,Bool value),(filename,index,label,value)) 

/* ------ Network -------------------------------------------------------- */

PLUGIN_EXPORT_OL(void,qpx_NET_start,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_preOpen,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_postOpen,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_timeStep,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_timeStepPostLink,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_feedback,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_preFeedback,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_close,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_complete,(void),())
PLUGIN_EXPORT_OL(void,qpx_LNK_timeStep,(LINK* link),(link)) 
PLUGIN_EXPORT_OL(void,qpx_ZNE_timeStep,(ZONE* zone),(zone))
PLUGIN_EXPORT_OL(void,qpx_NET_preSave,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_postSave,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_refresh,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_reload,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_period,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_second,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_minute,(void),())
PLUGIN_EXPORT_OL(void,qpx_NET_hour,(void),())

/* ------ SIM/CLOCK ----------------------------------------------------- */

PLUGIN_EXPORT_OL(void,qpx_SIM_start,(void),())
PLUGIN_EXPORT_OL(void,qpx_SIM_stop,(void),())

PLUGIN_EXPORT_OL(void,qpx_CLK_startOfSimLoop,(void),())
PLUGIN_EXPORT_OL(void,qpx_CLK_endOfSimLoop,(void),())


/* ------ Statistics ----------------------------------------------------- */

PLUGIN_EXPORT_OL(Bool,qpx_STA_enable,(void),())

/* ------ Graphics ------------------------------------------------------- */

PLUGIN_EXPORT_OL(void,qpx_DRW_modelView,(void),())
PLUGIN_EXPORT_OL(void,qpx_DRW_instrumentView,(void),())


/* ------ Menu Items ------------------------------------------------------ */

PLUGIN_EXPORT_OL(void,qpx_GUI_layer,(char *name,Bool on),(name,on))
PLUGIN_EXPORT_OL(void,qpx_GUI_tool,(char *name, Bool on),(name, on))

/* ------ Logging ---------------------------------------------------------- */

PLUGIN_EXPORT_OL(void,qpx_UTL_report,(char *message),(message))

/* ------------------------------------------------------------------------ */
/* ------ OVERRIDES ------------------------------------------------------- */
/* ------------------------------------------------------------------------ */

/* ------ Car Following --------------------------------------------------- */

PLUGIN_EXPORT_OR(float,qpo_CFM_followingAcceleration,(VEHICLE* vehicle, VEHICLE* aheadvehicle,float gap, LINK* link))
PLUGIN_EXPORT_OR(float,qpo_CFM_constrainedAcceleration,(VEHICLE* vehicle, LINK* link,float speed,float dist))
PLUGIN_EXPORT_OR(float,qpo_CFM_gradientAcceleration,(int type,int age,float speed,float gradient,float acc))
PLUGIN_EXPORT_OR(float,qpo_CFM_minimumGap,(void)) 
PLUGIN_EXPORT_OR(int,qpo_CFM_lookAheadCount,(int awareness))
PLUGIN_EXPORT_OR(void,qpo_CFM_behaviour,(VEHICLE* vehicle))
PLUGIN_EXPORT_OR(float,qpo_CFM_linkSpeed,(LINK* link, VEHICLE* vehicle))
PLUGIN_EXPORT_OR(float,qpo_CFM_curveSpeed,(float r, LINK* link))
PLUGIN_EXPORT_OR(float,qpo_CFM_rampRevertDistance,(VEHICLE* vehicle))
PLUGIN_EXPORT_OR(float,qpo_CFM_rampMergeHeadway,(VEHICLE* vehicle))
PLUGIN_EXPORT_OR(float,qpo_CFM_headwayFactor,(VEHICLE* vehicle, LINK* link))
PLUGIN_EXPORT_OR(float,qpo_CFM_reactionFactor,(VEHICLE* vehicle, LINK* link))
PLUGIN_EXPORT_OR(float,qpo_CFM_safeDistance,(VEHICLE* vehicle,float speed))
PLUGIN_EXPORT_OR(float,qpo_CFM_stoppingDistance,(VEHICLE* vehicle))
PLUGIN_EXPORT_OR(float,qpo_CFM_thresholdDistance,(VEHICLE* vehicle))

PLUGIN_EXPORT_OR(float,qpo_CFM_leadSpeed,(LINK* link, VEHICLE* vehicle, VEHICLE* infrontvehicle[]))
PLUGIN_EXPORT_OR(float,qpo_CFM_followSpeed,(LINK* link, VEHICLE* vehicle, VEHICLE* infrontvehicle[]))

/* ------ Lane Changing -------------------------------------------------- */

PLUGIN_EXPORT_OR(Bool,qpo_LCM_gapExists,(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link,Bool urgent))
PLUGIN_EXPORT_OR(Bool,qpo_LCM_moveIn,(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link))
PLUGIN_EXPORT_OR(Bool,qpo_LCM_moveOut,(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link))
PLUGIN_EXPORT_OR(int,qpo_LCM_passTime  ,(VEHICLE* vehicle)) 
PLUGIN_EXPORT_OR(int,qpo_LCM_overtakeTime,(VEHICLE* vehicle)) 
PLUGIN_EXPORT_OR(int,qpo_LCM_resetTime   ,(VEHICLE* vehicle)) 
PLUGIN_EXPORT_OR(void,qpo_LCM_laneUsage,(VEHICLE* vehicle, LINK* link,int *loLane,int *hiLane))
PLUGIN_EXPORT_OR(float,qpo_LCM_forceMergeDistance,(VEHICLE* vehicle, VEHICLE* remvehicle))
PLUGIN_EXPORT_OR(float,qpo_LCM_signpostMergeDistance,(VEHICLE* vehicle,float signposting,Bool urgent))
PLUGIN_EXPORT_OR(float,qpo_LCM_signpostAllowDistance,(VEHICLE* vehicle,float signposting))


/* ------ Routing -------------------------------------------------------- */

PLUGIN_EXPORT_OR(Bool,qpo_RTM_enable,(void)) 
PLUGIN_EXPORT_OR(int,qpo_RTM_decision,(LINK* link, VEHICLE* vehicle)) 
PLUGIN_EXPORT_OR(void,qpo_RTM_nextLink,(LINK* link, VEHICLE* vehicle,int nextout, LINK* *nextlink,int *newdestp))
PLUGIN_EXPORT_OR(Bool,qpo_RTM_arrival,(LINK* link, VEHICLE* vehicle)) 
PLUGIN_EXPORT_OR(Bool,qpo_RTM_arrival2,(LINK* link, VEHICLE* vehicle, Bool arrival)) 

/* ------ SCO ------------------------------------------------------------ */

PLUGIN_EXPORT_OR(Bool,qpo_SCO_pullIn,(LINK* link, VEHICLE* vehicle))
PLUGIN_EXPORT_OR(Bool,qpo_SCO_pullOut,(LINK* link, VEHICLE* vehicle))
PLUGIN_EXPORT_OR(Bool,qpo_SCO_gapExists,(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link,Bool u))


/* 4.2 */
PLUGIN_EXPORT_OL(void,qpx_BUS_stopping,(VEHICLE* vehicle, BUSSTOP* stop),(vehicle, stop))

/* ------------------ Key press ----------------------------------------- */

PLUGIN_EXPORT_OL(void,qpx_GUI_keyPress,(int key, int ctrl, int shift, int left, int middle, int right),
				 (key, ctrl, shift, left, middle, right))

PLUGIN_EXPORT_OL(void,qpx_GUI_keyRelease,(int key, int ctrl, int shift, int left, int middle, int right),
				 (key, ctrl, shift, left, middle, right))


//re added in 6.6
PLUGIN_EXPORT_OL(void,qpx_GUI_editorSelection,(void),())
PLUGIN_EXPORT_OL(void,qpx_GUI_viewSelection,(void),())

// not in v6 PLUGIN_EXPORT_OL(void,qpx_GUI_testMenu,(int type),(type))

/* Added to v6.7.0.6*/
PLUGIN_EXPORT_OR(Bool,qpo_BST_skipStop,(VEHICLE* vehicle, BUSSTOP* busstop)) 

#ifdef __cplusplus
}
#endif


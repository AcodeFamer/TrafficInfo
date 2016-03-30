/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 * Quadstone Ltd.             Tel: +44 131 220 4491
 * 16 Chester Street          Fax: +44 131 220 4492
 * Edinburgh,EH3 7RA,UK     WWW: http://www.paramics-online.com
 * ----------------------------------------------------------------------- */ 
/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 *
 * This file defines all the functions that are defined in paramics,and 
 * called by the plugin
 *
 * this file does not have
 *
 * #ifndef _API_IMPORTS_H_
 * #define _API_IMPORTS_H_
 *
 * as it is included by other files that will handle this.
 * ----------------------------------------------------------------------- */ 

#include <stdio.h>
#include "api_constants.h"
#include "api_typedefs.h"

/* ------ Loop-Back ------------------------------------------------------ */

PLUGIN_IMPORT(float,qpg_CFM_followingAcceleration,(VEHICLE* vehicle, VEHICLE* aheadvehicle,float gap, LINK* link))
PLUGIN_IMPORT(int,qpg_CFM_lookAheadCount,(int awareness)) 
PLUGIN_IMPORT(float,qpg_CFM_constrainedAcceleration,(VEHICLE* vehicle, LINK* link,float speed,float dist))
PLUGIN_IMPORT(float,qpg_CFM_gradientAcceleration,(int type,int age,float speed,float grad,float acc))
PLUGIN_IMPORT(float, qpg_CFM_gradientAccelerationTruck,(VEHICLE *V, LINK *link, Bool Accel))
PLUGIN_IMPORT(Bool,qpg_LCM_moveOut,(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link))
PLUGIN_IMPORT(Bool,qpg_LCM_moveIn,(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link))
PLUGIN_IMPORT(Bool,qpg_LCM_gapExists,(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link,Bool urgent))
PLUGIN_IMPORT(void,qpg_LCM_laneUsage,(VEHICLE* vehicle, LINK* link,int *loLane,int *hiLane))
PLUGIN_IMPORT(float, qpg_LCM_forceMergeDistance,(VEHICLE* vehicle, VEHICLE* remvehicle))
PLUGIN_IMPORT(int,   qpg_LCM_overtakeTime,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,   qpg_LCM_passTime,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,   qpg_LCM_resetTime,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,   qpg_LCM_transitionTime,(VEHICLE* vehicle))
PLUGIN_IMPORT(float, qpg_LCM_signpostMergeDistance,(VEHICLE* vehicle, float signposting, Bool urgent))
PLUGIN_IMPORT(float, qpg_LCM_signpostAllowDistance,(VEHICLE* vehicle, float signposting))

PLUGIN_IMPORT(void,qpg_CFM_behaviour,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_CFM_linkSpeed,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_CFM_stoppingDistance,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_CFM_thresholdDistance,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_CFM_safeDistance,(VEHICLE* vehicle,float speed))
PLUGIN_IMPORT(float, qpg_CFM_curveSpeed,(float r, LINK* link))
PLUGIN_IMPORT(float, qpg_CFM_headwayFactor,(VEHICLE* vehicle, LINK* link))
PLUGIN_IMPORT(float, qpg_CFM_reactionFactor,(VEHICLE* vehicle, LINK* link))
PLUGIN_IMPORT(float, qpg_CFM_minimumGap,(void))
PLUGIN_IMPORT(float, qpg_CFM_rampMergeHeadway,(VEHICLE* vehicle))
PLUGIN_IMPORT(float, qpg_CFM_rampRevertDistance,(VEHICLE* vehicle))

/* ------- Timing -------------------------------------------------------- */

PLUGIN_IMPORT(float,qpg_CFM_meanHeadway,(void))       
PLUGIN_IMPORT(float,qpg_CFM_meanReactionTime,(void)) 
PLUGIN_IMPORT(float,qpg_CFG_timeStep,(void))
PLUGIN_IMPORT(void,qps_CFG_timeStep,(float val))  
PLUGIN_IMPORT(float,qpg_CFG_simulationTime,(void))

/* ------- Config -------------------------------------------------------- */

PLUGIN_IMPORT(int,qpg_CFG_speedMemory,(void))
PLUGIN_IMPORT(int,qpg_CFG_startTime,(void))
PLUGIN_IMPORT(int,qpg_CFG_duration,(void))
PLUGIN_IMPORT(float,qpg_CFG_demandWeight,(void))
PLUGIN_IMPORT(float,qpg_CFG_timeStepDetail,(void))
PLUGIN_IMPORT(int,qpg_CFG_seed,(void))
PLUGIN_IMPORT(Bool,qpg_CFG_splitSeed,(void))
PLUGIN_IMPORT(float,qpg_CFG_costCoefficientA,(void))
PLUGIN_IMPORT(float,qpg_CFG_costCoefficientB,(void))
PLUGIN_IMPORT(float,qpg_CFG_costCoefficientC,(void))
PLUGIN_IMPORT(float,qpg_CFG_queueSpeed,(void))
PLUGIN_IMPORT(float,qpg_CFG_queueGap,(void))
PLUGIN_IMPORT(float,qpg_CFG_heavyWeight,(void))
PLUGIN_IMPORT(float,qpg_CFG_loopSize,(void))
PLUGIN_IMPORT(int,qpg_CFG_feedbackPeriod,(void))
PLUGIN_IMPORT(Bool,qpg_CFG_perturbation,(void))
PLUGIN_IMPORT(Bool,qpg_CFG_squareRootEnabled,(void))
PLUGIN_IMPORT(float,qpg_CFG_feedbackSmoothing,(void))
PLUGIN_IMPORT(float,qpg_CFG_feedbackDecay,(void))
PLUGIN_IMPORT(Bool,qpg_CFG_turningPenaltiesVisible,(void))
PLUGIN_IMPORT(float,qpg_CFG_amberTime,(void))
PLUGIN_IMPORT(Bool,qpg_CFG_closestOrigin,(void))
PLUGIN_IMPORT(Bool,qpg_CFG_closestDestination,(void))
PLUGIN_IMPORT(char,qpg_CFG_filetimeDelimiter,(void))
PLUGIN_IMPORT(float,qpg_CFG_curveSpeedFactor,(void))

/* ------- Stats -------------------------------------------------------- */

PLUGIN_IMPORT(float,qpg_STA_vehicleTotalDelay,(void))
PLUGIN_IMPORT(double,qpg_STA_vehicleTotalDistance,(void))
PLUGIN_IMPORT(int,qpg_STA_vehicleTotalCount,(void))
PLUGIN_IMPORT(int,qpg_STA_vehicleTotalStopTime,(void))
PLUGIN_IMPORT(float,qpg_STA_vehicleMeanSpeed,(void))
PLUGIN_IMPORT(float,qpg_STA_vehicleMeanDelay,(void))
PLUGIN_IMPORT(float,qpg_STA_vehicleLastSpeed,(void))
PLUGIN_IMPORT(int,qpg_STA_vehicleLastCount,(void))
PLUGIN_IMPORT(float,qpg_STA_busTotalDelay,(void))
PLUGIN_IMPORT(double,qpg_STA_busTotalDistance,(void))
PLUGIN_IMPORT(int,qpg_STA_busTotalCount,(void))
PLUGIN_IMPORT(float,qpg_STA_busMeanSpeed,(void))
PLUGIN_IMPORT(float,qpg_STA_busMeanDelay,(void))
PLUGIN_IMPORT(int,qpg_STA_busTotalStops,(void))
PLUGIN_IMPORT(int,qpg_STA_busTotalStopTime,(void))
PLUGIN_IMPORT(int,qpg_STA_busGetOn,(void))
PLUGIN_IMPORT(int,qpg_STA_busGetOff,(void))
PLUGIN_IMPORT(float,qpg_STA_busLastSpeed,(void))
PLUGIN_IMPORT(int,qpg_STA_busLastCount,(void))
PLUGIN_IMPORT(float,qpg_STA_allTotalDelay,(void))
PLUGIN_IMPORT(double,qpg_STA_allTotalDistance,(void))
PLUGIN_IMPORT(int,qpg_STA_allTotalCount,(void))
PLUGIN_IMPORT(float,qpg_STA_allMeanSpeed,(void))
PLUGIN_IMPORT(float,qpg_STA_allMeanDelay,(void))
PLUGIN_IMPORT(float,qpg_STA_allLastSpeed,(void))
PLUGIN_IMPORT(int,qpg_STA_allLastCount,(void))
PLUGIN_IMPORT(float,qpg_STA_speed,(LINK* link,int lane))
PLUGIN_IMPORT(float,qpg_STA_flow,(LINK* link,int lane))	      
PLUGIN_IMPORT(float,qpg_STA_count,(LINK* link,int lane))
PLUGIN_IMPORT(float,qpg_STA_density,(LINK* link,int lane))
PLUGIN_IMPORT(float,qpg_STA_percentDelay,(LINK* link,int lane))
PLUGIN_IMPORT(float,qpg_STA_delay,(LINK* link,int lane))
PLUGIN_IMPORT(float,qpg_STA_stoplineQueueLength,(LINK* link,int lane))
PLUGIN_IMPORT(int,qpg_STA_stoplineQueueCount,(LINK* link,int lane))
PLUGIN_IMPORT(float,qpg_STA_stoplineQueuePCUs,(LINK* link,int lane))

/* ------- Network ------------------------------------------------------- */

PLUGIN_IMPORT(char*,qpg_NET_datapath,(void))
PLUGIN_IMPORT(int,qpg_NET_nodes,(void))
PLUGIN_IMPORT(int,qpg_NET_links,(void))
PLUGIN_IMPORT(int,qpg_NET_zones,(void))
PLUGIN_IMPORT(int,qpg_NET_vehicleTypes,(void))
PLUGIN_IMPORT(int,qpg_NET_vehiclesSimulating,(void))
PLUGIN_IMPORT(int,qpg_NET_vehiclesSimulated,(void))
PLUGIN_IMPORT(int,qpg_NET_vehiclesDemanded,(void))
PLUGIN_IMPORT(float,qpg_NET_speedUp,(void))
PLUGIN_IMPORT(int,qpg_NET_lastNv,(void))
PLUGIN_IMPORT(NODE*,qpg_NET_nodeByIndex,(int id))
PLUGIN_IMPORT(LINK*,qpg_NET_linkByIndex,(int id))
PLUGIN_IMPORT(int,qpg_NDE_index,(NODE* node))
PLUGIN_IMPORT(int,qpg_LNK_index,(LINK* link))
PLUGIN_IMPORT(int,qpg_NET_numBlockingRegions,(void))
PLUGIN_IMPORT(char**,qpg_NET_blockingRegionNames,(void))
PLUGIN_IMPORT(Bool,qpg_NET_blockingRegionOpen,(char* name))
PLUGIN_IMPORT(Bool,qpg_NET_blockingRegionAgentsWaiting,(char* name))
PLUGIN_IMPORT(void,qps_NET_blockingRegionOpen,(char* name, Bool set))
PLUGIN_IMPORT(void,qps_NET_blockingRegionAgentsWaiting,(char* name, Bool set))
PLUGIN_IMPORT(int,qpg_NET_numStudyAreas,(void))
PLUGIN_IMPORT(char**,qpg_NET_studyAreaNames,(void))
PLUGIN_IMPORT(int,qpg_NET_wholeSeconds,(void))

/* ------- Nodes --------------------------------------------------------- */

PLUGIN_IMPORT(char*,qpg_NDE_name,(NODE* node))
PLUGIN_IMPORT(NODE*,qpg_NET_node,(char *name))
PLUGIN_IMPORT(int,qpg_NDE_links,(NODE* node))
PLUGIN_IMPORT(LINK*,qpg_NDE_link,(NODE* node,int index))
PLUGIN_IMPORT(LINK*, qpg_NDE_linkEntry,(NODE* node, int index))
PLUGIN_IMPORT(int,qpg_NDE_phases,(NODE* node))
PLUGIN_IMPORT(Bool,qpg_NDE_variable,(NODE* node))
PLUGIN_IMPORT(void,qps_NDE_variable,(NODE* node,Bool value))
PLUGIN_IMPORT(Bool,qpg_NDE_hold,(NODE* node))
PLUGIN_IMPORT(void,qps_NDE_hold,(NODE* node,Bool value))
PLUGIN_IMPORT(Bool,qpg_NDE_connected,(NODE* node1, NODE* node2))
PLUGIN_IMPORT(Bool,qpg_NDE_ghostIsland,(NODE* node))
PLUGIN_IMPORT(Bool,qpg_NDE_roundabout,(NODE* node))
PLUGIN_IMPORT(Bool,qpg_NDE_signalised,(NODE* node))
PLUGIN_IMPORT(int,qpg_NDE_entryLinks,(NODE* node))
PLUGIN_IMPORT(int,qpg_NDE_exitLinks,(NODE* node))


/* ------- Links --------------------------------------------------------- */

PLUGIN_IMPORT(char*,qpg_LNK_name,(LINK* link))
PLUGIN_IMPORT(LINK*,qpg_NET_link,(char *name))
PLUGIN_IMPORT(int,qpg_LNK_links,(LINK* link))
PLUGIN_IMPORT(LINK*,qpg_LNK_link,(LINK* link,int index))
PLUGIN_IMPORT(int,qpg_LNK_exitLinks,(LINK* link))
PLUGIN_IMPORT(LINK*,qpg_LNK_exit,(LINK* link,int index)) 
PLUGIN_IMPORT(int,qpg_LNK_entryLinks,(LINK* link))
PLUGIN_IMPORT(LINK*,qpg_LNK_entry,(LINK* link,int index)) 
PLUGIN_IMPORT(float,qpg_LNK_length,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_gradient,(LINK* link))
PLUGIN_IMPORT(int,qpg_LNK_lanes,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_urban,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_speedlimit,(LINK* link))
PLUGIN_IMPORT(void,qps_LNK_speedlimit,(LINK* link,float value))
PLUGIN_IMPORT(float,qpg_LNK_toHazard,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_LNK_signposting,(LINK* link))
PLUGIN_IMPORT(int,qpg_LNK_hazard,(LINK* link))  /* see APIHAZ_ values */
PLUGIN_IMPORT(void,qps_LNK_priority,(LINK* link1, LINK* link2,int pri))
PLUGIN_IMPORT(int, qpg_LNK_priority,(LINK* inlink, LINK* outlink))
PLUGIN_IMPORT(Bool,qpg_LNK_signalsAhead,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_LNK_signalsNearside,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_LNK_detectors,(LINK* link))
PLUGIN_IMPORT(int,qpg_LNK_detectorIndexByIndex,(LINK* link,int index))
PLUGIN_IMPORT(float,qpg_LNK_detectorPositionByIndex,(LINK* link,int index))
PLUGIN_IMPORT(int,qpg_LNK_beacons,(LINK* link))
PLUGIN_IMPORT(int,qpg_LNK_beaconIndexByIndex,(LINK* link,int index))
PLUGIN_IMPORT(int,qpg_LNK_zone,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_zoneConnector,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_stayInLane,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_headwayMod,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_reactionMod,(LINK* link))
PLUGIN_IMPORT(int,qpg_LNK_turncount,(LINK* link,int exit))
PLUGIN_IMPORT(void,qps_LNK_turncountClear,(LINK* link,int exit))
PLUGIN_IMPORT(Bool,qpg_LNK_special,(LINK* link))
PLUGIN_IMPORT(void,qps_LNK_special,(LINK* link,Bool value))
PLUGIN_IMPORT(int,qpg_LNK_cost,(LINK* link,int table)) 
PLUGIN_IMPORT(int,qpg_LNK_exitCost,(LINK* link1, LINK* link2,int table))
PLUGIN_IMPORT(int,qpg_LNK_destinationCost,(LINK* link,int destination,int table))
PLUGIN_IMPORT(void,qps_LNK_destinationCost,(LINK* link,int destination,int table,int cost))
PLUGIN_IMPORT(void,qps_LNK_destinationCostVector,(LINK* link,int table,int nzones,int *zone,int *icost))
PLUGIN_IMPORT(float,qpg_LNK_turnspeed,(LINK* link,int exit)) 
PLUGIN_IMPORT(void,qps_LNK_turnspeed,(LINK* link,int exit,float value)) 
PLUGIN_IMPORT(NODE*,qpg_LNK_nodeStart,(LINK* link))
PLUGIN_IMPORT(NODE*,qpg_LNK_nodeEnd,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_restrictedType,(LINK* link,int v_type))
PLUGIN_IMPORT(int,qpg_LNK_laneRestriction,(LINK* link,int lane))
PLUGIN_IMPORT(int,qpg_LNK_exitRestriction,(LINK* link,int exit))
PLUGIN_IMPORT(void, qpg_LNK_exitLanes,(LINK* link, int exit, int *lo, int *hi))
PLUGIN_IMPORT(void, qps_LNK_exitLanes,(LINK* link, int exit, int lo, int hi))

PLUGIN_IMPORT(float,qpg_LNK_width,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_medianWidth,(LINK* link))
PLUGIN_IMPORT(int,qpg_LNK_category,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_angle,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_startAngle,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_endAngle,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_stackingStopline,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_barred,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_arc,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_radius,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_arcLeft,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_toRamp,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_ratelocked,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_slipLane,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_wideStart,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_wideEnd,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_costFactor,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_onRoundabout,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_forceMerge,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_forceAcross,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_shareLanes,(LINK* link))
PLUGIN_IMPORT(int,qpg_LNK_linktype,(LINK* link))
PLUGIN_IMPORT(LINK*,qpg_LNK_nearside,(LINK* link))
PLUGIN_IMPORT(LINK*,qpg_LNK_offside,(LINK* link))
PLUGIN_IMPORT(LINK*,qpg_LNK_backside,(LINK* link))
PLUGIN_IMPORT(LINK*,qpg_LNK_match,(LINK* link))
PLUGIN_IMPORT(float,qpg_LNK_endspeed,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_LNK_tolls,(LINK* link))

PLUGIN_IMPORT(int  , qpg_LNK_ramps,(LINK* link))
PLUGIN_IMPORT(RAMP*, qpg_LNK_ramp,(LINK* link, int index))
PLUGIN_IMPORT(SLIP*, qpg_LNK_slip,(LINK* link))
PLUGIN_IMPORT(int  , qpg_RMP_vehicles,(RAMP* ramp, int lane))
PLUGIN_IMPORT(void , qpg_RMP_vehicleList,(RAMP* ramp, int lane, int count, VEHICLE* vehicle[]))
PLUGIN_IMPORT(VEHICLE* , qpg_RMP_vehicleTail,(RAMP* ramp, int lane))
PLUGIN_IMPORT(VEHICLE* , qpg_RMP_vehicleHead,(RAMP* ramp, int lane))
PLUGIN_IMPORT(int  , qpg_SLP_vehicles,(SLIP* slip))
PLUGIN_IMPORT(void , qpg_SLP_vehicleList,(SLIP* slip, int count, VEHICLE* vehicle[]))
PLUGIN_IMPORT(VEHICLE* , qpg_SLP_vehicleTail,(SLIP* slip))
PLUGIN_IMPORT(VEHICLE* , qpg_SLP_vehicleHead,(SLIP* slip))

/* ------- Categories ----------------------------------------------------- */

PLUGIN_IMPORT(Bool,  qpg_CAT_isMajor,(int category))
PLUGIN_IMPORT(Bool,  qpg_CAT_isUrban,(int category))
PLUGIN_IMPORT(int,   qpg_CAT_colour,(int category))
PLUGIN_IMPORT(float, qpg_CAT_toll,(int category))
PLUGIN_IMPORT(float, qpg_CAT_costFactor,(int category))
PLUGIN_IMPORT(Bool,  qpg_CAT_busOnly,(int category))
PLUGIN_IMPORT(Bool,  qpg_CAT_closures,(int category))
PLUGIN_IMPORT(float, qpg_CAT_curveFactor,(int category))
PLUGIN_IMPORT(float, qpg_CAT_headwayFactor,(int category))
PLUGIN_IMPORT(Bool,  qpg_CAT_forceMerge,(int category))
PLUGIN_IMPORT(Bool,  qpg_CAT_forceAcross,(int category))
PLUGIN_IMPORT(Bool,  qpg_CAT_stayInLane,(int category))
PLUGIN_IMPORT(Bool,  qpg_CAT_freewayLaneModel,(int category))
PLUGIN_IMPORT(float, qpg_CAT_signpost,(int category))
PLUGIN_IMPORT(float, qpg_CAT_range,(int category))
PLUGIN_IMPORT(float, qpg_CAT_width,(int category))
PLUGIN_IMPORT(float, qpg_CAT_median,(int category))
PLUGIN_IMPORT(float, qpg_CAT_speed,(int category))
PLUGIN_IMPORT(int,   qpg_CAT_lanes,(int category))
PLUGIN_IMPORT(int,   qpg_NET_categories,(void))

/* ------- Demands ------------------------------------------------------- */

PLUGIN_IMPORT(Bool,qpg_DMD_isPeriodic,(void))
PLUGIN_IMPORT(int,qpg_DMD_profiles,(void))
PLUGIN_IMPORT(int,qpg_DMD_periods,(void))
PLUGIN_IMPORT(int,qpg_DMD_currentPeriod,(void))
PLUGIN_IMPORT(int,qpg_DMD_matrixCount,(void))
PLUGIN_IMPORT(int,qpg_DMD_randomVehicleType,(int matrix))

/* ------- Zones --------------------------------------------------------- */

PLUGIN_IMPORT(int,qpg_ZNE_index,(ZONE* zone))            
PLUGIN_IMPORT(ZONE*,qpg_NET_zone,(int index))            
PLUGIN_IMPORT(int,qpg_ZNE_externalIndex,(int index))            
PLUGIN_IMPORT(int,qpg_ZNE_unreleased,(ZONE* zone))     
PLUGIN_IMPORT(int,qpg_ZNE_links,(ZONE* zone))          
PLUGIN_IMPORT(LINK*,qpg_ZNE_link,(ZONE* zone,int index))     
PLUGIN_IMPORT(int,qpg_ZNE_released,(ZONE* zone))
PLUGIN_IMPORT(int,qpg_ZNE_carparks,(ZONE* zone))
PLUGIN_IMPORT(int,qpg_ZNE_type,(ZONE* zone))
PLUGIN_IMPORT(int,qpg_ZNE_targetDemand,(int orig,int dest,int matrix))
PLUGIN_IMPORT(int,qpg_ZNE_vertices,(ZONE* zone))          
PLUGIN_IMPORT(void,qps_ZNE_vehicleRecall,(Bool value))       
PLUGIN_IMPORT(void,qps_ZNE_vehicleType,(int value))       
PLUGIN_IMPORT(void,qps_ZNE_vehicleDestination,(int value)) 
PLUGIN_IMPORT(void,qps_ZNE_vehicleProfile,(int value))      
PLUGIN_IMPORT(void,qps_ZNE_vehicleAwareness,(int value))     
PLUGIN_IMPORT(void,qps_ZNE_vehicleAggression,(int value))     
PLUGIN_IMPORT(void,qps_ZNE_vehicleFamiliarity,(Bool value))   
PLUGIN_IMPORT(void,qps_ZNE_vehicleLane,(int value))           
PLUGIN_IMPORT(void,qps_ZNE_vehicleSpeed,(float value))        
PLUGIN_IMPORT(void,qps_ZNE_vehicleDistance,(float value))     

/* ------- Car Parks  ---------------------------------------------------- */



/* ------- Vehicles ------------------------------------------------------ */

PLUGIN_IMPORT(LINK*,qpg_VHC_link,(VEHICLE* vehicle))  
PLUGIN_IMPORT(int,qpg_VHC_lane,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_distance,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_distance,(VEHICLE* vehicle,float value))
PLUGIN_IMPORT(float,qpg_VHC_speed,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_speed,(VEHICLE* vehicle,float value))
PLUGIN_IMPORT(float,qpg_VHC_speedHistoric,(VEHICLE* vehicle,float time))
PLUGIN_IMPORT(float,qpg_VHC_linkAcceleration,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_linkDeceleration,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_accelerating,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_accelerating,(VEHICLE* vehicle,Bool value))
PLUGIN_IMPORT(Bool,qpg_VHC_braking,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_braking,(VEHICLE* vehicle,Bool value))
PLUGIN_IMPORT(int,qpg_VHC_aggression,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_aggression,(VEHICLE* vehicle,int value))
PLUGIN_IMPORT(int,qpg_VHC_awareness,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_awareness,(VEHICLE* vehicle,int value))
PLUGIN_IMPORT(int,qpg_VHC_type,(VEHICLE* vehicle))
PLUGIN_IMPORT(VEHICLE*,qpg_VHC_ahead,(VEHICLE* vehicle))
PLUGIN_IMPORT(VEHICLE*,qpg_VHC_behind,(VEHICLE* vehicle))
PLUGIN_IMPORT(VEHICLE*,qpg_VHC_original,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_tracer,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_report,(VEHICLE* vehicle,char *format,...))
PLUGIN_IMPORT(void,qps_VHC_tracer,(VEHICLE* vehicle,int index,float value))
PLUGIN_IMPORT(void,qps_VHC_dashboard,(VEHICLE* vehicle,int index,char *format,...)) 
PLUGIN_IMPORT(Bool,qpg_VHC_special,(VEHICLE* vehicle,int index))
PLUGIN_IMPORT(void,qps_VHC_special,(VEHICLE* vehicle,int index,Bool value))
PLUGIN_IMPORT(Bool,qpg_VHC_usertag,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_usertag,(VEHICLE* vehicle,Bool value))
PLUGIN_IMPORT(float,qpg_VHC_length,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_width,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_height,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_weight,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_acceleration,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_deceleration,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_demand,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_familiar,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_perturbation,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_VHC_pcus,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_matrix,(VEHICLE* vehicle))
PLUGIN_IMPORT(float, qpg_VHC_maxSpeed,(VEHICLE* V)) 
PLUGIN_IMPORT(int,qpg_VHC_origin,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_originTrip,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_destination,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_destinationTrip,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_laneLow,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_laneHigh,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_nextLane,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_nextExit,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_nextNextExit,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_age,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_startTime,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_existTime,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_VHC_routeTable,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_letIn,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_onNode,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_notMajor,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_movingIn,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_movingOut,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_stopped,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_incident,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_recycle,(Bool val))
PLUGIN_IMPORT(Bool,qpg_BUS_atStop,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_busAvoid,(VEHICLE* vehicle,float to_hazard))
PLUGIN_IMPORT(Bool,qpg_VHC_isHeavy,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_VHC_isBus,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_VHC_shareLanes,(VEHICLE* vehicle, Bool nearside, Bool v))
PLUGIN_IMPORT(Bool,qpg_VHC_shareLanes,(VEHICLE* vehicle, Bool nearside))
PLUGIN_IMPORT(float,qpg_VTP_length,(int t))
PLUGIN_IMPORT(float,qpg_VTP_width,(int t))
PLUGIN_IMPORT(float,qpg_VTP_height,(int t))
PLUGIN_IMPORT(float,qpg_VTP_weight,(int t))
PLUGIN_IMPORT(float,qpg_VTP_acceleration,(int t))
PLUGIN_IMPORT(float,qpg_VTP_deceleration,(int t))
PLUGIN_IMPORT(float,qpg_VTP_demand,(int t))
PLUGIN_IMPORT(float,qpg_VTP_familiar,(int t))
PLUGIN_IMPORT(float,qpg_VTP_perturbation,(int t))
PLUGIN_IMPORT(float,qpg_VTP_pcus,(int t))
PLUGIN_IMPORT(int,qpg_VTP_matrix,(int t))
PLUGIN_IMPORT(float, qpg_VTP_maxSpeed, (int t))
PLUGIN_IMPORT(int,qpg_VTP_routeTable,(int t))
PLUGIN_IMPORT(Bool,qpg_VTP_restricted,(int t,int restriction))
PLUGIN_IMPORT(float,qpg_VTP_minGapFactor,(int t))
PLUGIN_IMPORT(float,qpg_VTP_meanDriverReactionFactor,(int t))
PLUGIN_IMPORT(float,qpg_VTP_meanTargetHeadwayFactor,(int t))

PLUGIN_IMPORT(void, qps_VTP_maxSpeed, (int t, float speed))
PLUGIN_IMPORT(void, qps_VHC_maxSpeed,(VEHICLE* V, float speed)) 

/* ------- Buses / FRV's ------------------------------------------------- */




/* -------- Detectors ---------------------------------------------------- */

PLUGIN_IMPORT(int,qpg_NET_detectors,(void))


/* -------- ITS ---------------------------------------------------------- */

PLUGIN_IMPORT(int,qpg_NET_beacons,(void))
PLUGIN_IMPORT(BEACON*,qpg_NET_beacon,(char* name))
PLUGIN_IMPORT(BEACON*,qpg_NET_beaconByIndex,(int index))

PLUGIN_IMPORT(char*,qpg_BCN_name,(BEACON* beacon))
PLUGIN_IMPORT(LINK*,qpg_BCN_link,(BEACON* beacon))
PLUGIN_IMPORT(char*,qpg_BCN_message,(BEACON* beacon))
PLUGIN_IMPORT(float,qpg_BCN_distance,(BEACON* beacon))
PLUGIN_IMPORT(void,qps_BCN_message,(BEACON* beacon,char *format,...))
PLUGIN_IMPORT(void,qps_BCN_colour,(BEACON* beacon,int colour))
PLUGIN_IMPORT(float,qpg_BCN_visibility,(BEACON* beacon))
PLUGIN_IMPORT(void,qps_BCN_visibility,(BEACON* beacon,float value))
PLUGIN_IMPORT(int,qpg_BCN_colour,(BEACON* beacon))
PLUGIN_IMPORT(void,qps_BCN_colourClear,(BEACON* beacon))
PLUGIN_IMPORT(void,qps_BCN_binsGraph,(BEACON* beacon,Bool state))
PLUGIN_IMPORT(void,qps_BCN_binsFormat,(BEACON* beacon,Bool state))
PLUGIN_IMPORT(void,qps_BCN_binValue,(BEACON* beacon,int index,float value))
PLUGIN_IMPORT(float,qpg_BCN_binValue,(BEACON* beacon,int index))
PLUGIN_IMPORT(void,qps_BCN_binColour,(BEACON* beacon,int index,int colour))
PLUGIN_IMPORT(int,qpg_BCN_binColour,(BEACON* beacon,int index))
PLUGIN_IMPORT(void,qps_BCN_maxBinValue,(BEACON* beacon,float value))
PLUGIN_IMPORT(float,qpg_BCN_maxBinValue,(BEACON* beacon))
PLUGIN_IMPORT(char*,qpg_BCN_graphName,(BEACON* beacon))
PLUGIN_IMPORT(void,qps_BCN_graphName,(BEACON* beacon,char *format,...))


/* -------- Units -------------------------------------------------------- */

PLUGIN_IMPORT(char*,qpg_UTL_distanceUnitLabel,(void))
PLUGIN_IMPORT(char*,qpg_UTL_speedUnitLabel,(void))
PLUGIN_IMPORT(char*,qpg_UTL_accelerationUnitLabel,(void))
PLUGIN_IMPORT(char*,qpg_UTL_densityUnitLabel,(void))
PLUGIN_IMPORT(char*,qpg_UTL_eventDensityUnitLabel,(void))
PLUGIN_IMPORT(char*,qpg_UTL_weightUnitLabel,(void))

PLUGIN_IMPORT(float,qpg_UTL_toExternalDistance,(void))
PLUGIN_IMPORT(float,qpg_UTL_toExternalSpeed,(void))
PLUGIN_IMPORT(float,qpg_UTL_toExternalAcceleration,(void))
PLUGIN_IMPORT(float,qpg_UTL_toExternalDensity,(void))
PLUGIN_IMPORT(float,qpg_UTL_toExternalWeight,(void))

PLUGIN_IMPORT(float,qpg_UTL_toInternalDistance,(void))
PLUGIN_IMPORT(float,qpg_UTL_toInternalSpeed,(void))
PLUGIN_IMPORT(float,qpg_UTL_toInternalAcceleration,(void))
PLUGIN_IMPORT(float,qpg_UTL_toInternalDensity,(void))
PLUGIN_IMPORT(float,qpg_UTL_toInternalWeight,(void))

PLUGIN_IMPORT(char*,qpg_UTL_distanceUnitLabelNGM,(int))
PLUGIN_IMPORT(char*,qpg_UTL_speedUnitLabelNGM,(int))
PLUGIN_IMPORT(char*,qpg_UTL_accelerationUnitLabelNGM,(int))
PLUGIN_IMPORT(char*,qpg_UTL_densityUnitLabelNGM,(int))
PLUGIN_IMPORT(char*,qpg_UTL_densityDistUnitLabelNGM,(int))
PLUGIN_IMPORT(char*,qpg_UTL_eventDensityUnitLabelNGM,(int))
PLUGIN_IMPORT(char*,qpg_UTL_weightUnitLabelNGM,(int))

PLUGIN_IMPORT(float,qpg_UTL_toExternalDistanceNGM,(int))
PLUGIN_IMPORT(float,qpg_UTL_toExternalSpeedNGM,(int))
PLUGIN_IMPORT(float,qpg_UTL_toExternalAccelerationNGM,(int))
PLUGIN_IMPORT(float,qpg_UTL_toExternalDensityNGM,(int))
PLUGIN_IMPORT(float,qpg_UTL_toExternalWeightNGM,(int))

PLUGIN_IMPORT(float,qpg_UTL_toInternalDistanceNGM,(int))
PLUGIN_IMPORT(float,qpg_UTL_toInternalSpeedNGM,(int))
PLUGIN_IMPORT(float,qpg_UTL_toInternalAccelerationNGM,(int))
PLUGIN_IMPORT(float,qpg_UTL_toInternalDensityNGM,(int))
PLUGIN_IMPORT(float,qpg_UTL_toInternalWeightNGM,(int))

/* ------------------- utility functions  -------------------------------- */

PLUGIN_IMPORT(double,qpg_UTL_randomDouble,(int stream,double range))
PLUGIN_IMPORT(float,qpg_UTL_randomFloat,(int stream,float  range))
PLUGIN_IMPORT(int,qpg_UTL_randomInteger,(int stream,int range))
PLUGIN_IMPORT(Bool,qpg_UTL_randomBoolean,(int stream,int ctrue))
PLUGIN_IMPORT(int,qpg_UTL_randomNormalInteger,(int stream,int mean,int max_abs_dev))
PLUGIN_IMPORT(int,qpg_UTL_randomPoissonInteger,(int stream,float mean))
PLUGIN_IMPORT(float,qpg_UTL_linearSpread,(int p1,int p2,float value,float delta))
PLUGIN_IMPORT(float,qpg_UTL_skewSpread,(int p1,int p2,float value,float delta,float skew))

PLUGIN_IMPORT(long,qpg_UTL_startTimer,(void))
PLUGIN_IMPORT(int,qpg_UTL_lapTimer,(long ref,char scale))
PLUGIN_IMPORT(void,qps_UTL_resetTimer,(long ref))
PLUGIN_IMPORT(int,qpg_UTL_readTimer,(long ref,char scale))
PLUGIN_IMPORT(void,qpg_UTL_integerToTime,(int t,int *dy,int *hr,int *mn,int *sc))
PLUGIN_IMPORT(char*,qpg_UTL_integerToTimeString,(int t))
PLUGIN_IMPORT(char*,qpg_UTL_integerToTimeFileName,(int t))
PLUGIN_IMPORT(void,qps_UTL_fileTimeSeparator,(char c))
PLUGIN_IMPORT(Bool,qpg_UTL_makeDirectory,(char *path))
PLUGIN_IMPORT(Bool,qpg_UTL_fileExists,(char *path))
PLUGIN_IMPORT(Bool,qpg_UTL_directoryExists,(char *path))
PLUGIN_IMPORT(int,qpg_UTL_linesInFile,(char *path))
PLUGIN_IMPORT(char*,qpg_UTL_paramicsHome,(void))
PLUGIN_IMPORT(char*,qpg_UTL_paramicsDataHome,(void))
PLUGIN_IMPORT(int,qpg_UTL_openFiles,(void))
PLUGIN_IMPORT(char*,qpg_UTL_appendExtension,(char *filename,char *extension))
PLUGIN_IMPORT(Bool,qpg_UTL_permissionCheck,(void))
PLUGIN_IMPORT(char*,qpg_NET_statsPath,(void))
PLUGIN_IMPORT(char*,qpg_NET_dataPath,(void))

PLUGIN_IMPORT(Bool, qpg_UTL_pluginExcluded, (char* basename,char* name))
PLUGIN_IMPORT(void, qps_UTL_pluginExcluded, (char* filename,char* name, Bool e))

/* ---------------------- Graphics --------------------------------------- */

PLUGIN_IMPORT(void,qps_DRW_arrow,(float x,float y,float z,float bearing,float gradient,float size,int pos))
PLUGIN_IMPORT(void,qps_DRW_colour,(int c))
PLUGIN_IMPORT(void,qps_DRW_colourRGB,(float r,float g,float b))
PLUGIN_IMPORT(void,qps_DRW_linkBand,(LINK* link,int colour,float proportion,float percent, int start))
PLUGIN_IMPORT(void,qps_DRW_filledCircle,(float x,float y,float z,float r))
PLUGIN_IMPORT(void,qps_DRW_filledCircleXY,(float x,float y,float r))
PLUGIN_IMPORT(void,qps_DRW_filledRectangle,(float bl_x,float bl_y,float bl_z,float tr_x,float tr_y,float tr_z))
PLUGIN_IMPORT(void,qps_DRW_filledRectangleXY,(float bl_x,float bl_y,float tr_x,float tr_y))
PLUGIN_IMPORT(void,qps_DRW_forceTimeStepRedraw,(Bool state))
PLUGIN_IMPORT(void,qps_DRW_highlightLink,(LINK* link,int colour))
PLUGIN_IMPORT(void,qps_DRW_hollowCircle,(float x,float y,float z,float r))
PLUGIN_IMPORT(void,qps_DRW_hollowCircleXY,(float x,float y,float r))
PLUGIN_IMPORT(void,qps_DRW_hollowRectangle,(float bl_x,float bl_y,float bl_z,float tr_x,float tr_y,float tr_z))
PLUGIN_IMPORT(void,qps_DRW_hollowRectangleXY,(float bl_x,float bl_y,float tr_x,float tr_y))
PLUGIN_IMPORT(void,qps_DRW_laneClosure,(LINK* link,int lane, int colour, int style))
PLUGIN_IMPORT(void,qps_DRW_laneOutline,(LINK* link,int lane,int colour))
PLUGIN_IMPORT(void,qps_DRW_lineStyle,(int style))
PLUGIN_IMPORT(void,qps_DRW_linewidth,(float width))
PLUGIN_IMPORT(void,qps_DRW_loadDrawingMatrix,(void))
PLUGIN_IMPORT(void,qps_DRW_loadIdentityMatrix,(void))
PLUGIN_IMPORT(void,qps_DRW_matrixMode,(int mode))
PLUGIN_IMPORT(void,qps_DRW_moveToBeaconHome,(BEACON* beacon))
PLUGIN_IMPORT(void,qps_DRW_moveToDetectorHome,(DETECTOR* detector))
PLUGIN_IMPORT(void,qps_DRW_moveToDetectorHomeByIndex,(int detector))
PLUGIN_IMPORT(void,qps_DRW_moveToBeaconHomeByIndex,(int beacon))
PLUGIN_IMPORT(void,qps_DRW_moveToKerbHome,(LINK* link,int kerb))
PLUGIN_IMPORT(void,qps_DRW_moveToNodeHome,(NODE* node))
PLUGIN_IMPORT(void,qps_DRW_moveToStoplineHome,(LINK* link,int lane,int stopline))
PLUGIN_IMPORT(void,qps_DRW_moveToVehicleHome,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_DRW_moveToZoneHome,(ZONE* zone))
PLUGIN_IMPORT(void,qps_DRW_objectBegin,(int object))
PLUGIN_IMPORT(void,qps_DRW_objectEnd,(void))
PLUGIN_IMPORT(void,qps_DRW_rotate,(float angle,char axis))
PLUGIN_IMPORT(void,qps_DRW_scale,(float x,float y,float z))
PLUGIN_IMPORT(void,qps_DRW_shadeLane,(LINK* link,int lane,int colour))
PLUGIN_IMPORT(void,qps_DRW_shadeLanePartial,(LINK* link,int lane,int colour,float percent, int start))
PLUGIN_IMPORT(void,qps_DRW_shadeLink,(LINK* link,int colour))
PLUGIN_IMPORT(void,qps_DRW_shadeLinkPartial,(LINK* link,int colour,float percent, int start))
PLUGIN_IMPORT(void,qps_DRW_shadeLink3D,(LINK *link, float height, int colour, int edgecolour))
PLUGIN_IMPORT(void,qps_DRW_signalColour,(NODE* node,int colour,int index))
PLUGIN_IMPORT(void,qps_DRW_signalCustom,(NODE* node,Bool state))
PLUGIN_IMPORT(void,qps_DRW_signalFace,(NODE* node,int colour))
PLUGIN_IMPORT(void,qps_DRW_signalStyle,(NODE* node,int style))
PLUGIN_IMPORT(void,qps_DRW_solid,(void))
PLUGIN_IMPORT(void,qps_DRW_storeDrawingMatrix,(void))
PLUGIN_IMPORT(void,qps_DRW_string,(char *s,float x,float y,float z,float h))
PLUGIN_IMPORT(void,qps_DRW_stringRotated,(char *s,float x,float y,float z,float rot,int n))
PLUGIN_IMPORT(void,qps_DRW_stringRotatedXY,(char *s,float x,float y,float rot,int n))
PLUGIN_IMPORT(void,qps_DRW_stringXY,(char *s,float x,float y,float h))
PLUGIN_IMPORT(void,qps_DRW_translate,(float x,float y,float z))
PLUGIN_IMPORT(void,qps_DRW_transparent,(void))
PLUGIN_IMPORT(void,qps_DRW_vehicleColour,(VEHICLE* vehicle,int colour))
PLUGIN_IMPORT(void,qps_DRW_vehicleGhost,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_DRW_vehicleHide,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_DRW_vehicleReset,(VEHICLE* vehicle))
PLUGIN_IMPORT(void,qps_DRW_vehicleTag,(VEHICLE* vehicle,int colour,int type, float size, char *format,...))
PLUGIN_IMPORT(void,qps_DRW_vertex,(float x,float y,float z))
PLUGIN_IMPORT(void,qps_DRW_vertexXY,(float x,float y))
PLUGIN_IMPORT(void,qps_DRW_zoneFilled,(ZONE* zone,int colour,float height, int highlight))
PLUGIN_IMPORT(void,qps_DRW_zoneOutline,(ZONE* zone,int colour,float height))
PLUGIN_IMPORT(void,qps_DRW_zoneShaded,(ZONE* zone,int colour,float height, int highlight, int shade_colour, int face))

PLUGIN_IMPORT(int,qpg_DRW_colourScale,(float value))
PLUGIN_IMPORT(Bool,qpg_DRW_cubeVisible,(float x, float y, float z, float size ))
PLUGIN_IMPORT(Bool,qpg_DRW_cullingEnabled,(void))
PLUGIN_IMPORT(float,qpg_DRW_defaultLinewidth,(void))
PLUGIN_IMPORT(float,qpg_DRW_distanceToVisibleObject,(float x, float y, float z, float radius))
PLUGIN_IMPORT(Bool,qpg_DRW_forceTimestepRedraw,(void))
PLUGIN_IMPORT(void,qps_DRW_forceVisibleObjectsRebuild,(Bool state))
PLUGIN_IMPORT(Bool,qpg_DRW_is3D,(void))
PLUGIN_IMPORT(Bool,qpg_DRW_layerVisible,(int object))
PLUGIN_IMPORT(Bool,qpg_DRW_lineVisible,(float sx, float sy,float sz,float ex, float ey,float ez))
PLUGIN_IMPORT(float,qpg_DRW_linewidth,(void))
PLUGIN_IMPORT(Bool,qpg_DRW_linkVisible,(LINK* link))
PLUGIN_IMPORT(Bool,qpg_DRW_pointVisible,(float x, float y, float z ))
PLUGIN_IMPORT(Bool,qpg_DRW_polygonVisible,(int count, float x[], float y[], float z[]))
PLUGIN_IMPORT(Bool,qpg_DRW_sphereVisible,(float x, float y, float z, float radius ))
PLUGIN_IMPORT(int,qpg_DRW_signalColour,(NODE* node))
PLUGIN_IMPORT(float,qpg_DRW_vehicleDistanceFromViewPoint,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_DRW_vehicleVisible,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_DRW_windowHeight,(void))
PLUGIN_IMPORT(int,qpg_DRW_windowWidth,(void))

/* ----------------------- Positional Data ------------------------------- */

PLUGIN_IMPORT(void,qpg_POS_vehicle,(VEHICLE* vehicle, LINK* link,float *x,float *y,float *z,float *bearing,float *gradient))
PLUGIN_IMPORT(void,qpg_POS_vehicleNoAdjust,(VEHICLE* vehicle, LINK* link,float *x,float *y,float *z,float *bearing,float *gradient))
PLUGIN_IMPORT(void,qpg_POS_vehicleExternal,(VEHICLE* vehicle, LINK* link,float *x,float *y,float *z,float *bearing,float *gradient))
PLUGIN_IMPORT(void,qpg_POS_zone,(ZONE* zone,float *x,float *y,float *z))
PLUGIN_IMPORT(void,qpg_POS_zoneVertex,(ZONE* zone,int index,float *x,float *y, float *z))
PLUGIN_IMPORT(void,qpg_POS_node,(NODE* node,float *x,float *y,float *z))
PLUGIN_IMPORT(void,qpg_POS_kerb,(LINK* link,int kerb,float *x,float *y,float *z))
PLUGIN_IMPORT(void,qpg_POS_stopline,(LINK* link,int lane,int stopline,float *x,float *y,float *z,float *bearing,float *gradient))
PLUGIN_IMPORT(void,qpg_POS_detector,(DETECTOR* detector,float *x,float *y,float *z,float *bearing,float *gradient))
PLUGIN_IMPORT(void,qpg_POS_beacon,(BEACON* beacon,float *x,float *y,float *z,float *bearing,float *gradient))
PLUGIN_IMPORT(void,qpg_POS_link,(LINK* link,int lane,float dist,float *x,float *y,float *z,float *bearing,float *gradient))


/* ------ Nearest Positions ----------------------------------------------- */

PLUGIN_IMPORT(void,qpg_POS_nearestNode,(NODE** node, float *x, float *y, float *z))
PLUGIN_IMPORT(void,qpg_POS_nearestLink,(LINK** link, float *x, float *y, float *z))
PLUGIN_IMPORT(void,qpg_POS_nearestZone,(ZONE** zone, float *x, float *y, float *z))
PLUGIN_IMPORT(void,qpg_POS_nearestCarpark,(CARPARK** carpark, float *x, float *y, float *z))
PLUGIN_IMPORT(void,qpg_POS_nearestSector,(SECTOR** sector, float *x, float *y, float *z))
PLUGIN_IMPORT(void,qpg_POS_nearestVehicle,(VEHICLE** vehicle, float *x, float *y, float *z))


/* ----------------------- Link vehicle data ----------------------------- */

PLUGIN_IMPORT(int,qpg_LNK_vehicles,(LINK* link,int lane))
PLUGIN_IMPORT(void,qpg_LNK_vehicleList,(LINK* link,int lane, int count, VEHICLE* vehicle[]))
PLUGIN_IMPORT(VEHICLE*,qpg_LNK_vehicleTail,(LINK* link,int lane))
PLUGIN_IMPORT(VEHICLE*,qpg_LNK_vehicleHead,(LINK* link,int lane))
PLUGIN_IMPORT(void,qpg_LNK_vehiclesAtPosition,(LINK* link,int lane,float dist, VEHICLE** infrontvehicle, VEHICLE** behindvehicle))


/* -------- Signals ------------------------------------------------------ */

PLUGIN_IMPORT(void,qps_SIG_action,(NODE* node,int phase_index,int balance_index,int action_type,int action_mode,float value))

PLUGIN_IMPORT(Bool,qpg_SIG_inquiry,(NODE* node,int phase_index,int inquiry,
                                         float *value))



/* ------------------ Lex/Yacc wrappers  -------------------------------- */

PLUGIN_IMPORT(void,qps_UTL_yaccClose,(void *fp)) /* can be FILE* or char* */
PLUGIN_IMPORT(Bool,qpg_UTL_yaccParser,(char *path,char *file,FILE **datafilein,FILE **datafileout,int *count,int(*parseFn)(void),int(*wrapFn)(void)))


PLUGIN_IMPORT(void,qps_GUI_printf,(char *format,...))

/* ------------------ SC Overtaking ------------------------------------- */

PLUGIN_IMPORT(float,qpg_CFM_thresholdDistance,(VEHICLE* vehicle))
PLUGIN_IMPORT(float,qpg_SCO_matchDistance,(VEHICLE* vehicle, LINK* link))

PLUGIN_IMPORT(VEHICLE*,qpg_SCO_overtaken,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_SCO_overtaking,(VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_SCO_overtakingLink,(LINK* link))
PLUGIN_IMPORT(void,qps_SCO_overtakingLink,(LINK* link,Bool state))

PLUGIN_IMPORT(Bool,  qpg_SCO_gapExists,(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link, Bool urgent))
PLUGIN_IMPORT(Bool,  qpg_SCO_pullIn,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,  qpg_SCO_pullOut,(LINK* link, VEHICLE* vehicle))


/* Single-lane detectors */

PLUGIN_IMPORT(DETECTOR*,qpg_NET_detector,(char *name))
PLUGIN_IMPORT(DETECTOR*,qpg_NET_detectorByIndex,(int index))
PLUGIN_IMPORT(char*,qpg_DTC_name,(DETECTOR* detector))
PLUGIN_IMPORT(LINK*,qpg_DTC_link,(DETECTOR* detector))
PLUGIN_IMPORT(int,qpg_DTC_index,(DETECTOR* detector))
PLUGIN_IMPORT(Bool,qpg_DTC_isLoopType,(DETECTOR* detector))
PLUGIN_IMPORT(Bool,qpg_DTC_isMultiple,(DETECTOR* detector))
PLUGIN_IMPORT(Bool,qpg_DTC_selected,(DETECTOR* detector))
PLUGIN_IMPORT(int,qpg_DTC_lane,(DETECTOR* detector))
PLUGIN_IMPORT(int,qpg_DTC_end_lane,(DETECTOR* detector))

PLUGIN_IMPORT(LOOP*,qpg_DTC_multipleLoop,(DETECTOR* detector, int lane))
PLUGIN_IMPORT(LOOP*,qpg_DTC_singleLoop,(DETECTOR* detector))

PLUGIN_IMPORT(float,qpg_DTL_downstreamDistance,(LOOP*))
PLUGIN_IMPORT(float,qpg_DTL_upstreamDistance,(LOOP*))
PLUGIN_IMPORT(float,qpg_DTL_flow,(LOOP*,int type))
PLUGIN_IMPORT(float,qpg_DTL_speed,(LOOP*,int type))
PLUGIN_IMPORT(float,qpg_DTL_gap,(LOOP*,int type))
PLUGIN_IMPORT(float,qpg_DTL_occupancy,(LOOP*,int type))
PLUGIN_IMPORT(float,qpg_DTL_state,(LOOP*,int edge,int type))
PLUGIN_IMPORT(int  ,qpg_DTL_lanechangeRight,(LOOP*))
PLUGIN_IMPORT(int  ,qpg_DTL_lanechangeLeft,(LOOP*))
PLUGIN_IMPORT(int  ,qpg_DTL_count,(LOOP*,int type))
PLUGIN_IMPORT(Bool,qpg_DTL_faulty,(LOOP*))
PLUGIN_IMPORT(Bool,qpg_DTL_suspect,(LOOP*))
PLUGIN_IMPORT(void,qps_DTL_state,(LOOP*,int parameter,float value))

PLUGIN_IMPORT(Bool,qpg_RTM_arrival,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_RTM_decision,(LINK* link, VEHICLE* vehicle))
PLUGIN_IMPORT(Bool,qpg_RTM_enable,(void))
PLUGIN_IMPORT(void,qpg_RTM_nextLink,(LINK* link, VEHICLE* vehicle, int nextout, LINK* *nextlink, int *newdestp))
PLUGIN_IMPORT(void,  qpg_SCO_vehicles,(LINK* link, int lane, float dist, VEHICLE** infrontvehicle, VEHICLE** behindvehicle))

/* DC  11/12/08  Fixed Route Control API */
PLUGIN_IMPORT(LINK*, qpg_RTM_fixedRouteFirstLink,(int routeId))
PLUGIN_IMPORT(LINK*, qpg_RTM_fixedRouteNextLink,(int routeId, LINK* link))
PLUGIN_IMPORT(Bool, qpg_RTM_vehicleOnFixedRoute,(VEHICLE* V))
PLUGIN_IMPORT(int, qpg_RTM_vehicleFixedRouteId,(VEHICLE* V))
PLUGIN_IMPORT(VEHICLE*, qpg_RTM_firstVehicleOnFixedRoute,(int routeId))
PLUGIN_IMPORT(VEHICLE*, qpg_RTM_nextVehicleOnFixedRoute,(int routeId, VEHICLE* V))
PLUGIN_IMPORT(void, qps_RTM_vehicleFixedRoute,(VEHICLE* V, int routeId))

/**
 * "set" functions for user data
 * 
 **/ 
PLUGIN_IMPORT(void,qps_NET_userdata,(                    NET_USERDATA* data))
PLUGIN_IMPORT(void,qps_NDE_userdata,(NODE* node,         NDE_USERDATA* data))
PLUGIN_IMPORT(void,qps_LNK_userdata,(LINK* link,         LNK_USERDATA* data))
PLUGIN_IMPORT(void,qps_ZNE_userdata,(ZONE* zone,         ZNE_USERDATA* data))
PLUGIN_IMPORT(void,qps_VHC_userdata,(VEHICLE* vehicle,   VHC_USERDATA* data))
PLUGIN_IMPORT(void,qps_DTC_userdata,(DETECTOR* detector, DTC_USERDATA* data))
PLUGIN_IMPORT(void,qps_DTL_userdata,(LOOP* loop,         DTL_USERDATA* data))
PLUGIN_IMPORT(void,qps_BCN_userdata,(BEACON* beacon,     BCN_USERDATA* data))
PLUGIN_IMPORT(void,qps_BST_userdata,(BUSSTOP* busstop,   BST_USERDATA* data))
PLUGIN_IMPORT(void,qps_BUS_passengers,(VEHICLE* V, int count))
PLUGIN_IMPORT(void,qps_BUS_departTime,(VEHICLE* V, int time))
PLUGIN_IMPORT(void,qps_BSR_busCount,(BUSROUTE* busroute, int count))
PLUGIN_IMPORT(void,qps_BSR_releaseGap,(BUSROUTE* busroute, int gap))
PLUGIN_IMPORT(void,qps_BSR_nextReleaseTime,(BUSROUTE* busroute, int time))
PLUGIN_IMPORT(void,qps_BST_boardingTime,(BUSSTOP* busstop, int time))
PLUGIN_IMPORT(void,qps_BST_arrivalRate,(BUSSTOP* busstop, int rate))
PLUGIN_IMPORT(void,qps_BST_queueLength,(BUSSTOP* busstop, int people))
PLUGIN_IMPORT(void,qps_BST_debusRate,(BUSSTOP* busstop, int rate))
PLUGIN_IMPORT(void,qps_BST_debusRate_usePerc,(BUSSTOP* busstop, Bool  use_perc))
PLUGIN_IMPORT(void,qps_BST_dwellTimeMode,(BUSSTOP* busstop, int mode))
PLUGIN_IMPORT(void,qps_BST_dwellTime,(BUSSTOP* busstop, int time))
PLUGIN_IMPORT(void,qps_BST_dwellTimeMean,(BUSSTOP* busstop, int mean))
PLUGIN_IMPORT(void,qps_BST_dwellTimeDeviation,(BUSSTOP* busstop, int deviation))
PLUGIN_IMPORT(void,qps_BSR_userdata,(BUSROUTE* busroute, BSR_USERDATA* data))
PLUGIN_IMPORT(void,qps_CPK_userdata,(CARPARK* carpark,   CPK_USERDATA* data))
PLUGIN_IMPORT(void,qps_RMP_userdata,(RAMP* ramp,         RMP_USERDATA* data))
PLUGIN_IMPORT(void,qps_SLP_userdata,(SLIP* slip,         SLP_USERDATA* data))

/**
 * "get" functions for user data
 *  
 **/
PLUGIN_IMPORT(NET_USERDATA*,qpg_NET_userdata,())
PLUGIN_IMPORT(NDE_USERDATA*,qpg_NDE_userdata,(NODE* node))
PLUGIN_IMPORT(LNK_USERDATA*,qpg_LNK_userdata,(LINK* link))
PLUGIN_IMPORT(ZNE_USERDATA*,qpg_ZNE_userdata,(ZONE* zone))
PLUGIN_IMPORT(VHC_USERDATA*,qpg_VHC_userdata,(VEHICLE* vehicle))
PLUGIN_IMPORT(DTC_USERDATA*,qpg_DTC_userdata,(DETECTOR* detector))
PLUGIN_IMPORT(DTL_USERDATA*,qpg_DTL_userdata,(LOOP* loop))
PLUGIN_IMPORT(BCN_USERDATA*,qpg_BCN_userdata,(BEACON* beacon))
PLUGIN_IMPORT(BST_USERDATA*,qpg_BST_userdata,(BUSSTOP* busstop))
PLUGIN_IMPORT(BSR_USERDATA*,qpg_BSR_userdata,(BUSROUTE* busroute))
PLUGIN_IMPORT(CPK_USERDATA*,qpg_CPK_userdata,(CARPARK* carpark))
PLUGIN_IMPORT(RMP_USERDATA*,qpg_RMP_userdata,(RAMP* ramp))
PLUGIN_IMPORT(SLP_USERDATA*,qpg_SLP_userdata,(SLIP* slip))

/**
 * Callbacks to add items to menus on the main window. These
 * user-defined menu items would allow the user to add controls for
 * raising tool windows or toggling the display of user-defined "layers"
 * within the main view window,drawn by the user code.
 * 
 **/ 

/* add an item to the Objects Menu */
PLUGIN_IMPORT(void,qps_GUI_addViewLayer,(char *name)) 
/* add an item to the Tools Menu */
PLUGIN_IMPORT(void,qps_GUI_addTool,(char *name)) 


/**
 * Callbacks to ascertain the position of objects within the
 * simulation,in order to add to the drawn scene,and also for
 * transfer of positional information to any external program.
 **/ 
PLUGIN_IMPORT(void,qpg_POS_network,(float *llx,float *lly,float *urx,float *ury))
PLUGIN_IMPORT(void,qpg_POS_crossHair,(float *x,float *y,float *z))
PLUGIN_IMPORT(void,qpg_POS_viewPoint,(float *x,float *y,float *z))

/** Set the crosshair / viewpoint */
PLUGIN_IMPORT(void,qps_POS_crossHair,(float x,float y,float z))
PLUGIN_IMPORT(void,qps_POS_viewPoint,(float x,float y,float z))

/**
 * Callbacks for fixed route vehicles (buses). 
 * 
 * Use qpg_VHC_isBus to determine if vehicle is a bus.
 **/ 


PLUGIN_IMPORT(int,qpg_BUS_passengers,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_BUS_stopTime,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_BUS_stopCount,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_BUS_linkTime,(VEHICLE* vehicle))
PLUGIN_IMPORT(int,qpg_BUS_departTime,(VEHICLE* V))
PLUGIN_IMPORT(BUSROUTE*,qpg_BUS_route,(VEHICLE* vehicle))      
PLUGIN_IMPORT(BUSSTOP*,qpg_BUS_nextStop,(VEHICLE* vehicle))   

PLUGIN_IMPORT(char*,qpg_BSR_number,(BUSROUTE* busroute))
PLUGIN_IMPORT(char*,qpg_BSR_name,(BUSROUTE* busroute))
PLUGIN_IMPORT(int,qpg_BSR_busCount,(BUSROUTE* busroute))
PLUGIN_IMPORT(int,qpg_BSR_releaseGap,(BUSROUTE* busroute))
PLUGIN_IMPORT(int,qpg_BSR_firstReleaseTime,(BUSROUTE* busroute))
PLUGIN_IMPORT(int,qpg_BSR_nextReleaseTime,(BUSROUTE* busroute))
PLUGIN_IMPORT(LINK*,qpg_BSR_firstLink,(BUSROUTE* busroute))
PLUGIN_IMPORT(LINK*,qpg_BSR_nextLink,(BUSROUTE* busroute, LINK* link))

PLUGIN_IMPORT(int,qpg_BST_boardingTime,(BUSSTOP* busstop))
PLUGIN_IMPORT(int,qpg_BST_arrivalRate,(BUSSTOP* busstop))
PLUGIN_IMPORT(int,qpg_BST_queueLength,(BUSSTOP* busstop))
PLUGIN_IMPORT(int,qpg_BST_debusRate,(BUSSTOP* busstop))
PLUGIN_IMPORT(Bool,qpg_BST_debusRate_usePerc,(BUSSTOP* busstop))
PLUGIN_IMPORT(int,qpg_BST_identifier,(BUSSTOP* busstop))


PLUGIN_IMPORT(float,qpg_RTR_distanceRemaining,(LINK* link,VEHICLE* vehicle))
PLUGIN_IMPORT(int, qpg_RTR_nextLinkIndex,(LINK *link, int d, int t, int p))
PLUGIN_IMPORT(int, qpg_RTR_tables,(void))

/**
 * The following callbacks are required to control single step mode
 */

PLUGIN_IMPORT(void,qps_CLK_singleStep,(Bool flag))
PLUGIN_IMPORT(void,qps_CLK_makeSingleStep,())
PLUGIN_IMPORT(Bool,qpg_CLK_singleStep,())

/**
 * Read & write access to simulation date
 */
PLUGIN_IMPORT(void,qps_CLK_date,(int yyyymmdd))
PLUGIN_IMPORT(int,qpg_CLK_date,())

/**
 * The following callbacks are required to directly modify turn
 * priorities on a node,to allow control of signalised intersections
 * by an external controller. The NODE* has an extra flag ext_control
 * which signals that it is a signalised node,controlled from
 * outside.
 **/ 
PLUGIN_IMPORT(void,qps_NDE_externalController,(NODE* node, Bool on))

/**
 * The node can also store an external id for it's self and an id for each
 * movement (inlink,outlink) at the node to aid translation between paramics 
 * and a hardware controler or software controler. Also a number of loop
 * detectors can be assigned to each movement (up to 4) at the node. This 
 * data can be coded from the signals GUI in 4.0.4 onwards, a new datafile 
 * is also avaliabel called "externalsignals"
 **/
PLUGIN_IMPORT(Bool,	qpg_NDE_externalController,(NODE *node))
PLUGIN_IMPORT(int,	qpg_NDE_externalControllerID,(NODE *node))
PLUGIN_IMPORT(void,	qps_NDE_externalControllerID,(NODE *node, int id))
PLUGIN_IMPORT(int,	qpg_NDE_externalControllerMovementID,(NODE *node, LINK* inlink, LINK* outlink))
PLUGIN_IMPORT(void,	qps_NDE_externalControllerMovementID,(NODE *node, LINK* inlink, LINK* outlink, int id))
PLUGIN_IMPORT(int,	qpg_NDE_externalControllerDetectorCount,(NODE *node, LINK* inlink, LINK* outlink))
PLUGIN_IMPORT(void,	qps_NDE_externalControllerDetectorCount,(NODE *node, LINK* inlink, LINK* outlink, int count))
PLUGIN_IMPORT(DETECTOR*,qpg_NDE_externalControllerDetector,(NODE *node, LINK* inlink, LINK* outlink, int index))
PLUGIN_IMPORT(void,	qps_NDE_externalControllerDetector,(NODE *node, LINK* inlink, LINK* outlink, int index, DETECTOR* detector))
PLUGIN_IMPORT(float, qpg_NDE_externalControllerNParameter,(NODE *node, int index))
PLUGIN_IMPORT(char,	*qpg_NDE_externalControllerFParameter,(NODE *node, int index))
PLUGIN_IMPORT(void,	qps_NDE_externalControllerNParameter,(NODE *node, int index, float value))
PLUGIN_IMPORT(void,	qps_NDE_externalControllerFParameter,(NODE *node, int index, char *file))
PLUGIN_IMPORT(void,	qps_NDE_externalControllerTCNode,(NODE* node, Bool on))
PLUGIN_IMPORT(Bool,	qpg_NDE_externalControllerTCNode,(NODE *node))
PLUGIN_IMPORT(int,	qpg_NDE_externalControllerTCNodeID,(NODE *node))
PLUGIN_IMPORT(void,	qps_NDE_externalControllerTCNodeID,(NODE *node, int id))


/**
 * If an external controller provides light colours for signal groups
 * and there is a mapping between turns and signal groups,then a
 * translation in the plugin can cause the correct priorities to be
 * displayed.
 * 
 **/ 

/* 
 * APIPRI_MAJOR                 Green,no opposition 
 * APIPRI_MEDIUM                Green,opposing traffic stream 
 * APIPRI_MINOR                 Yellow,Flashing Yellow 
 * APIPRI_BARRED                Red 

 Each turn gets its turn state from its primary signal group,unless
 that signal group is in the "Off" state. In this case the turn
 priority state is taken from to the secondary signal group. If this
 is also in the Off state,or is not defined,then the turn reverts to
 MINOR priority (rather like an all-way STOP intersection,or a
 flashing yellow intersection). 
*/

PLUGIN_IMPORT(float, qpg_DMD_demand, (int mx, int orig, int dest))
PLUGIN_IMPORT(void, qps_DMD_demand, (int mx, int orig, int dest, float value))
PLUGIN_IMPORT(void, qps_VHC_destination, (VEHICLE* v, int dest, int ultimate))
PLUGIN_IMPORT(void, qps_VHC_remove, (VEHICLE* v))
PLUGIN_IMPORT(int,qpg_BST_dwellTimeMode,(BUSSTOP* busstop))
PLUGIN_IMPORT(int,qpg_BST_dwellTime,(BUSSTOP* busstop))
PLUGIN_IMPORT(int,qpg_BST_dwellTimeMean,(BUSSTOP* busstop))
PLUGIN_IMPORT(int,qpg_BST_dwellTimeDeviation,(BUSSTOP* busstop))

PLUGIN_IMPORT(char*, qpg_UTL_licenseID,(void))

PLUGIN_IMPORT(void, qps_CFG_simulationTime, (int wholeSeconds))
PLUGIN_IMPORT(void, qps_CFG_periodRestart,(void))
PLUGIN_IMPORT(int, qpg_CFG_periodStartTime,(int period))
PLUGIN_IMPORT(Bool, qpg_CFG_driveOnRight, (void))

PLUGIN_IMPORT(Bool, qpg_LIC_granted, (int type, int count))



/**************************************************************************/
/* These are deprecated */

PLUGIN_IMPORT(Bool,qpg_DTI_isLoop,(int detector))
PLUGIN_IMPORT(char*,qpg_DTI_name,(int detector))
PLUGIN_IMPORT(int,qpg_DTI_lanes,(int detector))
PLUGIN_IMPORT(float,qpg_DTI_flow,(int detector,int lane,int type))
PLUGIN_IMPORT(float,qpg_DTI_speed,(int detector,int lane,int type))
PLUGIN_IMPORT(float,qpg_DTI_gap,(int detector,int lane,int type))
PLUGIN_IMPORT(float,qpg_DTI_occupancy,(int detector,int lane,int type))
PLUGIN_IMPORT(int,qpg_DTI_count,(int detector,int lane,int vehicleType))
PLUGIN_IMPORT(Bool,qpg_DTI_faulty,(int detector,int lane))
PLUGIN_IMPORT(Bool,qpg_DTI_suspect,(int detector,int lane))
PLUGIN_IMPORT(void,qps_DTI_state,(int detector,int lane,int parameter,float value))

PLUGIN_IMPORT(char*,qpg_BCI_name,(int beacon))
PLUGIN_IMPORT(LINK*,qpg_BCI_link,(int beacon))
PLUGIN_IMPORT(char*,qpg_BCI_message,(int beacon))
PLUGIN_IMPORT(float,qpg_BCI_distance,(int beacon))
PLUGIN_IMPORT(void,qps_BCI_message,(int beacon,char *format,...))
PLUGIN_IMPORT(void,qps_BCI_colour,(int beacon,int colour))
PLUGIN_IMPORT(float,qpg_BCI_visibility,(int beacon))
PLUGIN_IMPORT(void,qps_BCI_visibility,(int beacon,float value))
PLUGIN_IMPORT(int,qpg_BCI_colour,(int beacon))
PLUGIN_IMPORT(void,qps_BCI_colourClear,(int beacon))
PLUGIN_IMPORT(void,qps_BCI_binsGraph,(int beacon,Bool state))
PLUGIN_IMPORT(void,qps_BCI_binsFormat,(int beacon,Bool state))
PLUGIN_IMPORT(void,qps_BCI_binValue,(int beacon,int index,float value))
PLUGIN_IMPORT(float,qpg_BCI_binValue,(int beacon,int index))
PLUGIN_IMPORT(void,qps_BCI_binColour,(int beacon,int index,int colour))
PLUGIN_IMPORT(int,qpg_BCI_binColour,(int beacon,int index))
PLUGIN_IMPORT(void,qps_BCI_maxBinValue,(int beacon,float value))
PLUGIN_IMPORT(float,qpg_BCI_maxBinValue,(int beacon))
PLUGIN_IMPORT(char*,qpg_BCI_graphName,(int beacon))
PLUGIN_IMPORT(void,qps_BCI_graphName,(int beacon,char *format,...))

PLUGIN_IMPORT(void,qps_GUI_redraw,(void))


/* open simcore access */
PLUGIN_IMPORT(void,  qps_SIM_init,(int argc, char **argv))
PLUGIN_IMPORT(void,  qps_SIM_open,(char *datapath))
PLUGIN_IMPORT(int,   qpg_SIM_simulate,(int countdown))
PLUGIN_IMPORT(void,  qps_SIM_close,(void))
PLUGIN_IMPORT(void,  qps_SIM_tidy,(void))
PLUGIN_IMPORT(Bool,  qpg_SIM_licensed,(void))

/* 4.2 */
PLUGIN_IMPORT(void, qpg_POS_busStop,(BUSSTOP* busstop, float *x, float *y, float *z))
PLUGIN_IMPORT(LINK*, qpg_BST_link,(BUSSTOP* busstop))
PLUGIN_IMPORT(float, qpg_BST_linkDistance,(BUSSTOP* busstop))
PLUGIN_IMPORT(char*, qpg_BST_name,(BUSSTOP* busstop))
PLUGIN_IMPORT(int, qpg_RMP_lanes,(RAMP* ramp))
PLUGIN_IMPORT(LINK, *qpg_RMP_mainlineLink,(RAMP* ramp))
PLUGIN_IMPORT(int, qpg_NET_busroutes,(void))
PLUGIN_IMPORT(BUSROUTE*, qpg_NET_busrouteByIndex,(int id))
PLUGIN_IMPORT(int, qpg_BSR_links,(BUSROUTE *busroute))
PLUGIN_IMPORT(Bool,qpg_DTC_testOccupied,(DETECTOR* d))
PLUGIN_IMPORT(void,qps_DTC_testOccupied,(DETECTOR* d, Bool state))
PLUGIN_IMPORT(void,qps_CFG_demandWeight,(float weight))
PLUGIN_IMPORT(void,qps_NET_clearVehicles,(void))
PLUGIN_IMPORT(LINK*, qpg_BSR_link,(BUSROUTE *busroute, int index))


/* 5.0 */

PLUGIN_IMPORT(void, qps_VHC_stopped,(VEHICLE* V, Bool v))
PLUGIN_IMPORT(void, qps_VHC_laneRange, (VEHICLE* V, int low, int high))
PLUGIN_IMPORT(void, qps_VHC_laneLow,(VEHICLE* V, int lane))
PLUGIN_IMPORT(void, qps_VHC_laneHigh,(VEHICLE* V, int lane))
PLUGIN_IMPORT(void, qps_VHC_nextlane,(VEHICLE* V, int lane))
PLUGIN_IMPORT(void, qps_VHC_laneChange,(VEHICLE* V, int direction))
PLUGIN_IMPORT(void, qps_LNK_turnCost,(LINK* link, int exit, int cost))
PLUGIN_IMPORT(void, qps_LNK_nextlane,(LINK *link, int lane, int exit, int next, int range))
PLUGIN_IMPORT(void, qps_LNK_closure,(LINK* link, int lane, Bool open))
PLUGIN_IMPORT(void, qps_LNK_restriction,(LINK* link, int lane, int restriction))
PLUGIN_IMPORT(void, qps_LNK_speedcontrol,(LINK* link, int lane, int rule))

PLUGIN_IMPORT(int, qpg_LNK_nextlane,(LINK *link, int lane, int exit,int* range))

PLUGIN_IMPORT(int  , qpg_VTP_colour,(int t))
PLUGIN_IMPORT(char*, qpg_VTP_name,(int t))
PLUGIN_IMPORT(int  , qpg_VTP_trailers,(int t))
PLUGIN_IMPORT(float, qpg_VTP_cabLength,(int t))
PLUGIN_IMPORT(Bool , qpg_VTP_fixedRoute,(int t))
PLUGIN_IMPORT(LINK*, qpg_RMP_inlink,(RAMP* ramp))
PLUGIN_IMPORT(float, qpg_RMP_length,(RAMP* ramp))
PLUGIN_IMPORT(float, qpg_RMP_tailpoint,(RAMP* ramp))

PLUGIN_IMPORT(void, qps_RTR_buildTables, (Bool on))


PLUGIN_IMPORT(void,  qps_VHC_holdTransfer,(VEHICLE* vehicle, Bool hold)) 
PLUGIN_IMPORT(void,  qps_ZNE_vehicleLink, (LINK* link)) 

PLUGIN_IMPORT(float, qpg_CFM_leadSpeed, (LINK* link, VEHICLE* vehicle,  
                                         VEHICLE* infrontvehicle[]))
PLUGIN_IMPORT(float, qpg_CFM_followSpeed, (LINK* link, VEHICLE* vehicle,  
                                           VEHICLE* infrontvehicle[]))
PLUGIN_IMPORT(void, qps_VHC_usertagInc, (VEHICLE* vehicle))
PLUGIN_IMPORT(void, qps_VHC_usertagDec, (VEHICLE* vehicle))

PLUGIN_IMPORT(void, qps_VHC_changeLane, (VEHICLE* V, int change))

PLUGIN_IMPORT(void, qps_NDE_externalControllerTCNode, (NODE *node, Bool on))
PLUGIN_IMPORT(void, qps_NDE_externalControllerTCNodeID, (NODE *node, int id))

PLUGIN_IMPORT(Bool, qpg_NDE_externalControllerTCNode, (NODE *node))
PLUGIN_IMPORT(int, qpg_NDE_externalControllerTCNodeID, (NODE *node))


PLUGIN_IMPORT(void, qps_VHC_incident, (VEHICLE* V, int type, char* name, int colour, int lane, float dist, float wait,  float pass, float oppo))

PLUGIN_IMPORT(int, qpg_VHC_uniqueID, (VEHICLE* V))
PLUGIN_IMPORT(VEHICLE*, qpg_VHC_lookupVByLane,(LINK* link, int lane, int vID))
PLUGIN_IMPORT(VEHICLE*, qpg_VHC_lookupV,(LINK* link, int vID))

PLUGIN_IMPORT(int, qpg_LNK_turnCost,(LINK* link, int exit))
PLUGIN_IMPORT(float, qpg_LNK_DFTurnSumTime,(LINK* link, int exit))
PLUGIN_IMPORT(int, qpg_LNK_DFTurnCount,(LINK* link, int exit))
PLUGIN_IMPORT(void, qps_LNK_DFTurnSumTime,(LINK* link, int exit, float time))
PLUGIN_IMPORT(void, qps_LNK_DFTurnCount,(LINK* link, int exit, int count))

PLUGIN_IMPORT(int, qpg_SIG_priority,(NODE *node, int phase_index, LINK* inlink, LINK* outlink))

PLUGIN_IMPORT(Bool, qpg_SIM_running,(void))
PLUGIN_IMPORT(void, qps_SIM_running,(Bool state))
PLUGIN_IMPORT(void, qps_SIM_restart,(void))

PLUGIN_IMPORT(Bool, qpg_GUI_simRunning,(void))
PLUGIN_IMPORT(void, qps_GUI_simRunning,(Bool state))
PLUGIN_IMPORT(void, qps_GUI_simRestart,(void))

PLUGIN_IMPORT(Bool, qpg_GUI_singleStep,(void))
PLUGIN_IMPORT(void, qps_GUI_singleStep,(Bool))
PLUGIN_IMPORT(void, qps_GUI_runSimulation,(void))

PLUGIN_IMPORT(int, qpg_NDE_AllLinksIn,(NODE* node))
PLUGIN_IMPORT(int, qpg_NDE_AllLinksOut,(NODE* node))

/* 5.1 */
PLUGIN_IMPORT(int,	 qpg_UTL_parentProduct,(void))
PLUGIN_IMPORT(Bool,  qpg_UTL_parentHasGUI,(void))
PLUGIN_IMPORT(float, qpg_UTL_parentProductVersion,(void))

PLUGIN_IMPORT(int,	 qpg_UTL_pluginCount,(void))
PLUGIN_IMPORT(char*, qpg_UTL_pluginFile,(int index))

PLUGIN_IMPORT(void, qps_VHC_nextlink,(VEHICLE* V, int newExit))

// /5.1.2
PLUGIN_IMPORT(void, qpg_UTL_loadSnapshot,(char *path,char *filename))
PLUGIN_IMPORT(void, qps_UTL_saveSnapshot,(char *path,char *filename))

PLUGIN_IMPORT(FILE*,qpg_UTL_fileOpen,(char *md,char *path))
PLUGIN_IMPORT(Bool,qpg_UTL_fileClose,(FILE *fp))

// re-added in 6.6
PLUGIN_IMPORT(BEACON*,qpg_EDT_selectedBeacon,(void))
PLUGIN_IMPORT(BUSROUTE*,qpg_EDT_selectedBusRoute,(void))
PLUGIN_IMPORT(BUSSTOP*,qpg_EDT_selectedBusStop,(void))
PLUGIN_IMPORT(CARPARK*,qpg_EDT_selectedCarpark,(void))
PLUGIN_IMPORT(DETECTOR*,qpg_EDT_selectedDetector,(void))
PLUGIN_IMPORT(LINK*,qpg_EDT_selectedInwardLink,(void))
PLUGIN_IMPORT(LINK*,qpg_EDT_selectedLink,(void))
PLUGIN_IMPORT(NODE*,qpg_EDT_selectedNode,(void))
PLUGIN_IMPORT(NODE*,qpg_EDT_selectedNodeSecondary,(void))
PLUGIN_IMPORT(int,qpg_EDT_selectedOutwardIndex,(void))
PLUGIN_IMPORT(LINK*,qpg_EDT_selectedOutwardLink,(void))
PLUGIN_IMPORT(ZONE*,qpg_EDT_selectedZone,(void))

PLUGIN_IMPORT(BEACON*,qpg_GUI_selectedBeacon,(void))
PLUGIN_IMPORT(CARPARK*,qpg_GUI_selectedCarpark,(void))
PLUGIN_IMPORT(DETECTOR*,qpg_GUI_selectedDetector,(void))
PLUGIN_IMPORT(LINK*,qpg_GUI_selectedLink,(void))
PLUGIN_IMPORT(NODE*,qpg_GUI_selectedNode,(void))
PLUGIN_IMPORT(VEHICLE*,qpg_GUI_selectedVehicle,(void))
PLUGIN_IMPORT(ZONE*,qpg_GUI_selectedZone,(void))



/** Functions below here were removed in v6: */

// not in v6 PLUGIN_IMPORT(int, qpg_DRW_layerColour,(int object))
// not in v6 PLUGIN_IMPORT(Bool,qpg_DRW_layerVisable,(int object))

// not in v6 PLUGIN_IMPORT(void,qps_DRW_bandedTable,(int count,char *labels[],int colours[],int fill[],int edge[], int yshift))
// not in v6 PLUGIN_IMPORT(void,qps_DRW_colourkey,(char *min,char *max,char *title,float needle,int yshift))
// not in v6 PLUGIN_IMPORT(void, qps_DRW_displayList, (int object, Bool use))
// not in v6 PLUGIN_IMPORT(void,qps_DRW_eventTable,(int count,char *labels[],int colours[],int tri1[],int tri2[], int yshift))
// not in v6 PLUGIN_IMPORT(void,qps_DRW_layerColour, (int object,int colour))
// not in v6 PLUGIN_IMPORT(void, qps_DRW_textHeight, (int index, float height))

// not in v6 PLUGIN_IMPORT(int, qpg_GUI_activeCamera,(void))
// not in v6 PLUGIN_IMPORT(int, qpg_GUI_cameraID,(int index))
// not in v6 PLUGIN_IMPORT(int*, qpg_GUI_cameraIDs,(void))
// not in v6 PLUGIN_IMPORT(Bool,qpg_GUI_numberApiFiles,(void))
// not in v6 PLUGIN_IMPORT(int, qpg_GUI_numCameras,(void))


// not in v6 PLUGIN_IMPORT(void,qps_GUI_apiLabel,(int fileIndex, int index, char *text, float value))
// not in v6 PLUGIN_IMPORT(void,qps_GUI_apiPanel,(char *filename, int fileIndex, int num))
// not in v6 PLUGIN_IMPORT(void,qps_GUI_apiScale,(int fileIndex, int index, char *text, float value,float lo, float hi, int p))
// not in v6 PLUGIN_IMPORT(void,qps_GUI_apiToggle,(int fileIndex, int index, char *text, Bool state))
// not in v6 PLUGIN_IMPORT(void,qps_GUI_apiToolname,(char *label))
// not in v6 PLUGIN_IMPORT(void, qps_GUI_enableTestMenu,(Bool state))
// not in v6 PLUGIN_IMPORT(void,qps_GUI_range,(char *filename, int index, float low, float high))
// not in v6 PLUGIN_IMPORT(void,qps_GUI_seperator,(char *filename, char *name, int index))
// not in v6 PLUGIN_IMPORT(void,qps_GUI_toggle,(char *filename,int index,Bool state))
// not in v6 PLUGIN_IMPORT(void,qps_GUI_value,(char *filename,int index,float value))

// not in v6 PLUGIN_IMPORT(int, qpg_NET_cameras,(void))

// not in v6 PLUGIN_IMPORT(void, qpg_POS_cameraPosition,(int index, float *vpx, float *vpy, float *vpz, float *chx, float *chy, float *chz))






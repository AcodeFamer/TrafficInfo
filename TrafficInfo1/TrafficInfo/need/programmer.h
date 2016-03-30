
/* -----------------------------------------------------------------------
 * Paramics Programmer API	(paramics-support@quadstone.com)
 * Quadstone Ltd.		Tel: +44 131 220 4491
 * 16 Chester Stree		Fax: +44 131 220 4492
 * Edinburgh, EH3 7RA, UK	WWW: http://www.paramics-online.com
 *
 *
 *
 * This header file is part of the user distribution for Paramics Programmer
 * ----------------------------------------------------------------------- */ 

#ifndef _PROGRAMMER_H_
#define _PROGRAMMER_H_


/*
 * There are four types of API calls:
 * 
 * QPO: Override Standard Code - define a function in the plugin that
 * overrides the standard default behaviour inside Paramics. Each of
 * the key parts of the model can be replaced by your own logic.
 * 
 * QPX: Extend Standard Code - define a function in the plugin that
 * adds to the functionality in Paramics. It can be triggered by one
 * of a large number of events i.e. when the network is loaded, saved
 * refreshed, or at the start/end of each timestep etc. etc.
 *
 * QPG: Get a value from the Standard Code: retrieve data from within
 * either the simulation or graphics engines inside Paramics.
 * 
 * QPS: Set a value in the Standard Code: set a data value or change
 * or add to the view displayed.
 **/

/* 
 * The QP* prefix is followed by a 3-character code dividing the
 * interface into functional groupings
 *
 * NET - network
 * CFG - configuration
 * STA - statistics
 * UTL - utility
 * POS - position
 * DMD - demand
 * NDE - node
 * LNK - link
 * CAT - link category
 * ZNE - zone
 * VHC - vehicle
 * TGV - tagged vehicle
 * BUS - bus
 * CLK - clock/timing
 * SCO - single-carriageway overtaking
 * CFM - car following model
 * LCM - lane changing model
 * RTM - routing model
 * VTP - vehicle type
 * DTC - detector
 * DTL - loop-type detector
 * DTI - detector using index
 * BCN - beacons
 * BCI - beacon using index
 * BSR - Bus Route
 * BST - Bus Stop
 * CPK - Car Park
 * RMP - Ramp
 * SLP - Slip lane
 * SIG - Traffic Signals
 * SIM - Core Simulation
 *
 **/

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef __cplusplus
#define QPO extern "C" __declspec(dllexport) /* Override Standard Code */
#define QPX extern "C" __declspec(dllexport) /* Extend Standard Code */
#define QPG extern "C" __declspec(dllimport) /* Get Value from Standard Code */
#define QPS extern "C" __declspec(dllimport) /* Set Value in Standard Code */
#else
#define QPO __declspec(dllexport) /* Override Standard Code */
#define QPX __declspec(dllexport) /* Extend Standard Code */
#define QPG __declspec(dllimport) /* Get Value from Standard Code */
#define QPS __declspec(dllimport) /* Set Value in Standard Code */
#endif
#else
#ifdef __cplusplus
#define QPO extern "C"
#define QPX extern "C"
#define QPG extern "C"
#define QPS extern "C"
#else
#define QPO 
#define QPX 
#define QPG 
#define QPS 
#endif
#endif

#include "api_constants.h"
#include "api_typedefs.h"
#include "api_user.h"
#include "api_renaming.h"
#include "api_colours.h"

/*--- cut from here to end, paste into programmer.c, replace ";" with "{}" ---*/

QPO void  qpo_CFM_behaviour(VEHICLE* vehicle);
QPO float qpo_CFM_constrainedAcceleration(VEHICLE* vehicle, LINK* link, float speed, float dist);
QPO float qpo_CFM_curveSpeed(float r, LINK* link);
QPO float qpo_CFM_followingAcceleration(VEHICLE* vehicle, VEHICLE* aheadvehicle, float gap, LINK* link);
QPO float qpo_CFM_gradientAcceleration(int type, int age, float speed, float gradient, float acc);
QPO float qpo_CFM_headwayFactor(VEHICLE* vehicle, LINK* link);
QPO float qpo_CFM_linkSpeed(LINK* link, VEHICLE* vehicle);
QPO int   qpo_CFM_lookAheadCount(int awareness);
QPO float qpo_CFM_minimumGap(void);
QPO float qpo_CFM_rampMergeHeadway(VEHICLE* vehicle);
QPO float qpo_CFM_rampRevertDistance(VEHICLE* vehicle);
QPO float qpo_CFM_safeDistance(VEHICLE* vehicle, float speed);
QPO float qpo_CFM_stoppingDistance(VEHICLE* vehicle);
QPO float qpo_CFM_thresholdDistance(VEHICLE* vehicle);
QPO float qpo_LCM_forceMergeDistance(VEHICLE* vehicle, VEHICLE* remvehicle);
QPO Bool  qpo_LCM_gapExists(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link, Bool u);
QPO void  qpo_LCM_laneUsage(VEHICLE* vehicle, LINK* link, int *loLane, int *hiLane);
QPO Bool  qpo_LCM_moveIn(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link);
QPO Bool  qpo_LCM_moveOut(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link);
QPO int   qpo_LCM_overtakeTime(VEHICLE* vehicle);
QPO int   qpo_LCM_passTime(VEHICLE* vehicle);
QPO int   qpo_LCM_resetTime(VEHICLE* vehicle);
QPO float qpo_LCM_signpostAllowDistance(VEHICLE* vehicle, float signposting);
QPO float qpo_LCM_signpostMergeDistance(VEHICLE* vehicle, float signposting, Bool urgent);
QPO Bool  qpo_RTM_enable(void);
QPO Bool  qpo_RTM_arrival(LINK* link, VEHICLE* vehicle);
QPO Bool  qpo_RTM_arrival2(LINK* link, VEHICLE* vehicle, Bool arrived);
QPO int   qpo_RTM_decision(LINK* link, VEHICLE* vehicle);
QPO void  qpo_RTM_nextLink(LINK* link, VEHICLE* vehicle, int nextout, LINK* *nextlink, int *newdestp);
QPO Bool  qpo_SCO_gapExists(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link, Bool u);
QPO Bool  qpo_SCO_pullIn(LINK* link, VEHICLE* vehicle);
QPO Bool  qpo_SCO_pullOut(LINK* link, VEHICLE* vehicle);
QPO Bool  qpo_BST_skipStop(VEHICLE* vehicle, BUSSTOP* busstop);

/*****************************************************************************/


QPX void  qpx_CFG_parameterFile(char *filename, int count);
QPX void  qpx_DRW_instrumentView(void);
QPX void  qpx_DRW_modelView(void);
QPX void  qpx_GUI_layer(char *name, Bool on); /* called when the user entry on the layer menu is pushed */
QPX void  qpx_GUI_parameterToggle(char *filename, int index, char *label, Bool value);
QPX void  qpx_GUI_parameterValue(char *filename, int index, char *label, float value);
QPX void  qpx_GUI_tool(char *name, Bool on); /* called when the user entry on the tools menu is pushed */
QPX void  qpx_UTL_report(char *message);
QPX void  qpx_LNK_timeStep(LINK* link);
QPX void  qpx_NET_close(void);
QPX void  qpx_NET_complete(void);
QPX void  qpx_NET_feedback(void);
QPX void  qpx_NET_preFeedback(void);
QPX void  qpx_NET_hour(void);
QPX void  qpx_NET_minute(void);
QPX void  qpx_NET_period(void);
QPX void  qpx_NET_postOpen(void);
QPX void  qpx_NET_postSave(void);
QPX void  qpx_NET_preOpen(void);
QPX void  qpx_NET_preSave(void);
QPX void  qpx_NET_refresh(void);
QPX void  qpx_NET_reload(void);
QPX void  qpx_NET_second(void);
QPX void  qpx_NET_start(void);
QPX void  qpx_NET_timeStep(void);
QPX void  qpx_NET_timeStepPostLink(void);

QPX void  qpx_SIM_start(void);
QPX void  qpx_SIM_stop(void);

QPX Bool  qpx_STA_enable(void);

QPX void  qpx_TGV_arrive(VEHICLE* vehicle, LINK* link, ZONE* zone);
QPX void  qpx_TGV_beacon(VEHICLE* vehicle, LINK* link, BEACON* beacon);
QPX void  qpx_TGV_detector(VEHICLE* vehicle, LINK* link, DETECTOR* detector);
QPX void  qpx_TGV_laneChange(VEHICLE* vehicle, LINK* link, int lane1, int lane2);
QPX void  qpx_TGV_move(VEHICLE* vehicle, LINK* link, float distance, float speed);
QPX void  qpx_TGV_targetHeadway(VEHICLE* vehicle, LINK* link);
QPX void  qpx_TGV_targetSpeed(VEHICLE* vehicle, LINK* link);
QPX void  qpx_TGV_transfer(VEHICLE* vehicle, LINK* link1, LINK* link2);
QPX void  qpx_TGV_timeStep(VEHICLE* vehicle);

QPX void  qpx_VHC_arrive(VEHICLE* vehicle, LINK* link, ZONE* zone);
QPX void  qpx_VHC_beacon(VEHICLE* vehicle, LINK* link, BEACON* beacon);
QPX void  qpx_VHC_detector(VEHICLE* vehicle, LINK* link, DETECTOR* detector);
QPX void  qpx_VHC_laneChange(VEHICLE* vehicle, LINK* link, int lane1, int lane2);
QPX void  qpx_VHC_move(VEHICLE* vehicle, LINK* link, float distance, float speed);
QPX void  qpx_VHC_release(VEHICLE* vehicle);
QPX void  qpx_VHC_targetHeadway(VEHICLE* vehicle, LINK* link);
QPX void  qpx_VHC_targetSpeed(VEHICLE* vehicle, LINK* link);
QPX void  qpx_VHC_timeStep(VEHICLE* vehicle);
QPX void  qpx_LNK_vehicleTimeStep(LINK* link, VEHICLE* vehicle);
QPX void  qpx_VHC_transfer(VEHICLE* vehicle, LINK* link1, LINK* link2);
QPX void  qpx_ZNE_timeStep(ZONE* zone);

QPX void qpx_VHC_preRemove(VEHICLE* vehicle);

/*****************************************************************************/

QPS void  qps_BCN_binColour(BEACON* beacon, int index, int colour);
QPS void  qps_BCN_binValue(BEACON* beacon, int index, float value);
QPS void  qps_BCN_binsFormat(BEACON* beacon, Bool state);
QPS void  qps_BCN_binsGraph(BEACON* beacon, Bool state);
QPS void  qps_BCN_colour(BEACON* beacon, int colour);
QPS void  qps_BCN_colourClear(BEACON* beacon);
QPS void  qps_BCN_graphName(BEACON* beacon, char *format, ...);
QPS void  qps_BCN_maxBinValue(BEACON* beacon, float value);
QPS void  qps_BCN_message(BEACON* beacon, char *format, ...);
QPS void  qps_BCN_visibility(BEACON* beacon, float value);
QPS void  qps_BCN_userdata(BEACON* beacon, BCN_USERDATA* data);
QPS void  qps_BSR_userdata(BUSROUTE* busroute, BSR_USERDATA* data);
QPS void  qps_BST_userdata(BUSSTOP* busstop, BST_USERDATA* data);
QPS void  qps_BUS_passengers(VEHICLE* V, int count);
QPS void  qps_BUS_departTime(VEHICLE* V, int time);
QPS void  qps_BSR_busCount(BUSROUTE* busroute, int count);
QPS void  qps_BSR_releaseGap(BUSROUTE* busroute, int gap);
QPS void  qps_BSR_nextReleaseTime(BUSROUTE* busroute, int time);
QPS void  qps_BST_boardingTime(BUSSTOP* busstop, int time);
QPS void  qps_BST_arrivalRate(BUSSTOP* busstop, int rate);
QPS void  qps_BST_queueLength(BUSSTOP* busstop, int people);
QPS void  qps_BST_debusRate(BUSSTOP* busstop, int rate);
QPS void  qps_BST_debusRate_usePerc(BUSSTOP* busstop,  Bool use_perc);
QPS void  qps_BST_dwellTimeMode(BUSSTOP* busstop, int mode);
QPS void  qps_BST_dwellTime(BUSSTOP* busstop, int time);
QPS void  qps_BST_dwellTimeMean(BUSSTOP* busstop, int mean);
QPS void  qps_BST_dwellTimeDeviation(BUSSTOP* busstop, int deviation);
QPS void  qps_CFG_timeStep(float val); 
QPS void  qps_CFG_periodRestart(void);
QPS void  qps_CFG_simulationTime(int wholeSeconds); 
QPS void  qps_CLK_singleStep(Bool flag); 
QPS void  qps_CLK_date(int yyyymmdd); 
QPS void  qps_CLK_makeSingleStep(void); 
QPS void  qps_CPK_userdata(CARPARK* carpark, CPK_USERDATA* data);
QPS void  qps_DMD_demand (int matrix, int origin, int destination, float value);


QPS void  qps_DRW_arrow(float x, float y, float z, float bearing, float gradient, float size, int pos);
QPS void  qps_DRW_colour(int c);
QPS void  qps_DRW_colourRGB(float r, float g, float b);
QPS void  qps_DRW_filledCircle(float x, float y, float z, float r);
QPS void  qps_DRW_filledCircleXY(float x, float y, float r);
QPS void  qps_DRW_filledRectangle(float bl_x, float bl_y, float bl_z, float tr_x, float tr_y, float tr_z);
QPS void  qps_DRW_filledRectangleXY(float bl_x, float bl_y, float tr_x, float tr_y);
QPS void  qps_DRW_forceTimeStepRedraw(Bool state);
QPS void  qps_DRW_forceVisibleObjectsRebuild(Bool state);
QPS void  qps_DRW_highlightLink(LINK* link, int colour);
QPS void  qps_DRW_hollowCircle(float x, float y, float z, float r);
QPS void  qps_DRW_hollowCircleXY(float x, float y, float r);
QPS void  qps_DRW_hollowRectangle(float bl_x, float bl_y, float bl_z, float tr_x, float tr_y, float tr_z);
QPS void  qps_DRW_hollowRectangleXY(float bl_x, float bl_y, float tr_x, float tr_y);
QPS void  qps_DRW_laneClosure(LINK* link,int lane, int colour, int style);
QPS void  qps_DRW_laneOutline(LINK* link, int lane, int colour);
QPS void  qps_DRW_lineStyle(int style);
QPS void  qps_DRW_linewidth(float width);
QPS void  qps_DRW_linkBand(LINK* link, int colour, float proportion, float percent, int start);
QPS void  qps_DRW_loadDrawingMatrix(void);
QPS void  qps_DRW_loadIdentityMatrix(void);
QPS void  qps_DRW_matrixMode(int mode);
QPS void  qps_DRW_moveToBeaconHome(BEACON* beacon);
QPS void  qps_DRW_moveToBeaconHomeByIndex(int beacon);
QPS void  qps_DRW_moveToDetectorHome(DETECTOR* detector);
QPS void  qps_DRW_moveToDetectorHomeByIndex(int detector);
QPS void  qps_DRW_moveToKerbHome(LINK* link, int kerb);
QPS void  qps_DRW_moveToNodeHome(NODE* node);
QPS void  qps_DRW_moveToStoplineHome(LINK* link, int lane, int stopline);
QPS void  qps_DRW_moveToVehicleHome(VEHICLE* vehicle);
QPS void  qps_DRW_moveToZoneHome(ZONE* zone);
QPS void  qps_DRW_objectBegin(int object);
QPS void  qps_DRW_objectEnd(void);
QPS void  qps_DRW_rotate(float angle, char axis);
QPS void  qps_DRW_scale(float x, float y, float z);
QPS void  qps_DRW_shadeLane(LINK* link, int lane, int colour);
QPS void  qps_DRW_shadeLanePartial(LINK* link, int lane, int colour, float percent, int start);
QPS void  qps_DRW_shadeLink(LINK* link, int colour);
QPS void  qps_DRW_shadeLinkPartial(LINK* link, int colour, float percent, int start);
QPS void  qps_DRW_shadeLink3D(LINK *link, float height, int colour, int edgecolour);
QPS void  qps_DRW_signalColour(NODE* node, int colour, int index);
QPS void  qps_DRW_signalCustom(NODE* node, Bool state);
QPS void  qps_DRW_signalFace(NODE* node, int colour);
QPS void  qps_DRW_signalStyle(NODE* node, int style);
QPS void  qps_DRW_solid(void);
QPS void  qps_DRW_storeDrawingMatrix(void);
QPS void  qps_DRW_string(char *s, float x, float y, float z, float h);
QPS void  qps_DRW_stringRotated(char *s, float x, float y, float z, float rot, int n);
QPS void  qps_DRW_stringRotatedXY(char *s, float x, float y, float rot, int n);
QPS void  qps_DRW_stringXY(char *s, float x, float y, float h);
QPS void  qps_DRW_translate(float x, float y, float z);
QPS void  qps_DRW_transparent(void);
QPS void  qps_DRW_vehicleColour(VEHICLE* vehicle, int colour);
QPS void  qps_DRW_vehicleGhost(VEHICLE* vehicle);
QPS void  qps_DRW_vehicleHide(VEHICLE* vehicle);
QPS void  qps_DRW_vehicleReset(VEHICLE* vehicle);
QPS void  qps_DRW_vehicleTag(VEHICLE* vehicle, int colour, int type,  float size, char *format, ...);
QPS void  qps_DRW_vertex(float x, float y, float z);
QPS void  qps_DRW_vertexXY(float x, float y);
QPS void  qps_DRW_zoneFilled(ZONE* zone, int colour, float height, int highlight);
QPS void  qps_DRW_zoneOutline(ZONE* zone, int colour, float height);
QPS void  qps_DRW_zoneShaded(ZONE* zone,int colour,float height, int highlight, int shade_colour, int face);

QPG int   qpg_DRW_colourScale(float value);
QPG float qpg_DRW_defaultLinewidth(void);
QPG Bool  qpg_DRW_forceTimestepRedraw(void);
QPG Bool  qpg_DRW_is3D(void);
QPG Bool  qpg_DRW_layerVisible(int object);
QPG float qpg_DRW_linewidth(void);
QPG int   qpg_DRW_signalColour(NODE* node);
QPG int   qpg_DRW_windowHeight(void);
QPG int   qpg_DRW_windowWidth(void);


QPS void  qps_DTC_userdata(DETECTOR* detector, DTC_USERDATA* data);
QPS void  qps_DTL_state(LOOP* loop, int parameter, float value);
QPS void  qps_DTL_userdata(LOOP* loop, DTL_USERDATA* data);
QPS void  qps_GUI_addTool(char *name); /* add an item to the Tools Menu */
QPS void  qps_GUI_addViewLayer(char *name); /* add an item to Layers Menu */
QPS void  qps_GUI_printf(char *format, ...);

QPS void  qps_LNK_destinationCost(LINK* link, int destination, int table, int cost);
QPS void  qps_LNK_destinationCostVector(LINK* link, int table, int nzones, int *zone, int *icost);
QPS void  qps_LNK_priority(LINK* link1, LINK* link2, int pri);
QPS void  qps_LNK_special(LINK* link, Bool value);
QPS void  qps_LNK_speedlimit(LINK* link, float value);
QPS void  qps_LNK_turncountClear(LINK* link, int exit);
QPS void  qps_LNK_turnspeed(LINK* link, int exit, float value); 
QPS void  qps_LNK_userdata(LINK* link, LNK_USERDATA* data);
QPS void  qps_NDE_externalController(NODE* node, Bool on);
QPS void  qps_NDE_externalControllerID(NODE *node, int id);
QPS void  qps_NDE_externalControllerMovementID(NODE *node, LINK* inlink, LINK* outlink, int id);
QPS void  qps_NDE_externalControllerDetectorCount(NODE *node, LINK* inlink, LINK* outlink, int count);
QPS void  qps_NDE_externalControllerDetector(NODE *node, LINK* inlink, LINK* outlink, int index, DETECTOR* detector);
QPS void  qps_NDE_externalControllerNParameter(NODE *node, int index, float value);
QPS void  qps_NDE_externalControllerFParameter(NODE *node, int index, char *file);
QPS void  qps_NDE_hold(NODE* node, Bool value);
QPS void  qps_NDE_userdata(NODE* node, NDE_USERDATA* data);
QPS void  qps_NDE_variable(NODE* node, Bool value);
QPS void  qps_NET_userdata( NET_USERDATA* data);
QPS void  qps_RMP_userdata(RAMP *ramp, RMP_USERDATA* data);
QPS void  qps_SCO_overtakingLink(LINK* link, Bool state);
QPS void  qps_SIG_action(NODE* node, int phase, int balance, int action_type, int action_mode, float value);
QPS void  qps_SLP_userdata(SLIP *slip, SLP_USERDATA* data);
QPS void  qps_UTL_fileTimeSeparator(char c);
QPS void  qps_UTL_resetTimer(long ref);
QPS void  qps_UTL_pluginExcluded(char* filename, char* name, Bool exclude);
QPS void  qps_UTL_yaccClose(void *fp); /* can be FILE* or char* */
QPS void  qps_VHC_accelerating(VEHICLE* vehicle, Bool value);
QPS void  qps_VHC_aggression(VEHICLE* vehicle, int value);
QPS void  qps_VHC_awareness(VEHICLE* vehicle, int value);
QPS void  qps_VHC_braking(VEHICLE* vehicle, Bool value);
QPS void  qps_VHC_dashboard(VEHICLE* vehicle, int index, char *format, ...); 
QPS void  qps_VHC_destination (VEHICLE* vehicle, int destination, int ultimate);
QPS void  qps_VHC_distance(VEHICLE* vehicle, float value);
QPS void  qps_VHC_recycle(Bool val);
QPS void  qps_VHC_remove (VEHICLE* vehicle);
QPS void  qps_VHC_report(VEHICLE* vehicle, char *format, ...);
QPS void  qps_VHC_shareLanes(VEHICLE* vehicle, Bool nearside, Bool value);
QPS void  qps_VHC_special(VEHICLE* vehicle, int index, Bool value);
QPS void  qps_VHC_speed(VEHICLE* vehicle, float value);
QPS void  qps_VHC_tracer(VEHICLE* vehicle, int index, float value);
QPS void  qps_VHC_userdata(VEHICLE* vehicle, VHC_USERDATA* data);
QPS void  qps_VHC_usertag(VEHICLE* vehicle, Bool value);
QPS void  qps_ZNE_userdata(ZONE* zone, ZNE_USERDATA* data);
QPS void  qps_ZNE_vehicleAggression(int value); 
QPS void  qps_ZNE_vehicleAwareness(int value); 
QPS void  qps_ZNE_vehicleDestination(int value); 
QPS void  qps_ZNE_vehicleDistance(float value); 
QPS void  qps_ZNE_vehicleFamiliarity(Bool value); 
QPS void  qps_ZNE_vehicleLane(int value); 
QPS void  qps_ZNE_vehicleProfile(int value); 
QPS void  qps_ZNE_vehicleRecall(Bool value); 
QPS void  qps_ZNE_vehicleSpeed(float value); 
QPS void  qps_ZNE_vehicleType(int value); 

QPS void  qps_SIM_init(int argc, char **argv);
QPS void  qps_SIM_open(char *datapath);
QPS void  qps_SIM_close(void);
QPS void  qps_SIM_tidy(void);

/******************************************************************************/

QPG int   qpg_BCN_binColour(BEACON* beacon, int index);
QPG float qpg_BCN_binValue(BEACON* beacon, int index);
QPG int   qpg_BCN_colour(BEACON* beacon);
QPG float qpg_BCN_distance(BEACON* beacon);
QPG char* qpg_BCN_graphName(BEACON* beacon);
QPG LINK* qpg_BCN_link(BEACON* beacon);
QPG float qpg_BCN_maxBinValue(BEACON* beacon);
QPG char* qpg_BCN_message(BEACON* beacon);
QPG char* qpg_BCN_name(BEACON* beacon);
QPG float qpg_BCN_visibility(BEACON* beacon);
QPG BCN_USERDATA* qpg_BCN_userdata(BEACON* beacon);
QPG int   qpg_BSR_busCount(BUSROUTE* busroute);
QPG LINK* qpg_BSR_firstLink(BUSROUTE* busroute);
QPG int   qpg_BSR_firstReleaseTime(BUSROUTE* busroute);
QPG char* qpg_BSR_name(BUSROUTE* busroute);
QPG LINK* qpg_BSR_nextLink(BUSROUTE* busroute, LINK* link);
QPG int   qpg_BSR_nextReleaseTime(BUSROUTE* busroute);
QPG char* qpg_BSR_number(BUSROUTE* busroute);
QPG int   qpg_BSR_releaseGap(BUSROUTE* busroute);
QPG BSR_USERDATA* qpg_BSR_userdata(BUSROUTE* busroute);
QPG int   qpg_BST_arrivalRate(BUSSTOP* busstop);
QPG int   qpg_BST_boardingTime(BUSSTOP* busstop);
QPG int   qpg_BST_debusRate(BUSSTOP* busstop);
QPG Bool  qpg_BST_debusRate_usePerc(BUSSTOP* busstop);
QPG int   qpg_BST_identifier(BUSSTOP* busstop);
QPG int   qpg_BST_queueLength(BUSSTOP* busstop);


/* DC  11/12/08  Fixed Route Control API */
QPG LINK*		qpg_RTM_fixedRouteFirstLink(int routeId);
QPG LINK*		qpg_RTM_fixedRouteNextLink(int routeId, LINK* link);
QPG Bool		qpg_RTM_vehicleOnFixedRoute(VEHICLE* V);
QPG int			qpg_RTM_vehicleFixedRouteId(VEHICLE* V);
QPG VEHICLE*	qpg_RTM_firstVehicleOnFixedRoute(int routeId);
QPG VEHICLE*	qpg_RTM_nextVehicleOnFixedRoute(int routeId, VEHICLE* V);

QPS void		qps_RTM_vehicleFixedRoute(VEHICLE* V, int routeId);


QPG int   qpg_BST_dwellTimeMode(BUSSTOP* busstop);
QPG int   qpg_BST_dwellTime(BUSSTOP* busstop);
QPG int   qpg_BST_dwellTimeMean(BUSSTOP* busstop);
QPG int   qpg_BST_dwellTimeDeviation(BUSSTOP* busstop);

QPG BST_USERDATA* qpg_BST_userdata(BUSSTOP* busstop);
QPG Bool  qpg_BUS_atStop(VEHICLE* vehicle);
QPG Bool  qpg_BUS_atStop(VEHICLE* vehicle); 
QPG int   qpg_BUS_linkTime(VEHICLE* vehicle);
QPG BUSSTOP* qpg_BUS_nextStop(VEHICLE* vehicle); 
QPG int   qpg_BUS_passengers(VEHICLE* vehicle);
QPG BUSROUTE* qpg_BUS_route(VEHICLE* vehicle); 
QPG int   qpg_BUS_stopCount(VEHICLE* vehicle);
QPG int   qpg_BUS_stopTime(VEHICLE* vehicle);
QPG int   qpg_BUS_departTime(VEHICLE* V);
QPG float qpg_CFG_amberTime(void);
QPG Bool  qpg_CFG_closestDestination(void);
QPG Bool  qpg_CFG_closestOrigin(void);
QPG float qpg_CFG_costCoefficientA(void);
QPG float qpg_CFG_costCoefficientB(void);
QPG float qpg_CFG_costCoefficientC(void);
QPG float qpg_CFG_curveSpeedFactor(void);
QPG float qpg_CFG_demandWeight(void);
QPG Bool  qpg_CFG_driveOnRight(void);
QPG int   qpg_CFG_duration(void);
QPG float qpg_CFG_feedbackDecay(void);
QPG int   qpg_CFG_feedbackPeriod(void);
QPG float qpg_CFG_feedbackSmoothing(void);
QPG char qpg_CFG_filetimeDelimiter(void);
QPG float qpg_CFG_heavyWeight(void);
QPG float qpg_CFG_loopSize(void);
QPG Bool  qpg_CFG_perturbation(void);
QPG int   qpg_CFG_periodStartTime(int period);
QPG float qpg_CFG_queueGap(void);
QPG float qpg_CFG_queueSpeed(void);
QPG int   qpg_CFG_seed(void);
QPG float qpg_CFG_simulationTime(void);
QPG int   qpg_CFG_speedMemory(void);
QPG Bool  qpg_CFG_splitSeed(void);
QPG Bool  qpg_CFG_squareRootEnabled(void);
QPG int   qpg_CFG_startTime(void);
QPG float qpg_CFG_timeStep(void);
QPG float qpg_CFG_timeStepDetail(void);
QPG Bool  qpg_CFG_turningPenaltiesVisible(void);
QPG void  qpg_CFM_behaviour(VEHICLE* vehicle);
QPG float qpg_CFM_constrainedAcceleration(VEHICLE* vehicle, LINK* link, float speed, float dist);
QPG float qpg_CFM_followingAcceleration(VEHICLE* vehicle, VEHICLE* aheadvehicle, float gap, LINK* link);
QPG float qpg_CFM_gradientAcceleration(int type, int age, float speed, float grad, float acc);
QPG float qpg_CFM_gradientAccelerationTruck(VEHICLE *V, LINK *link, Bool Accel);
QPG float qpg_CFM_linkSpeed(LINK* link, VEHICLE* vehicle);
QPG int   qpg_CFM_lookAheadCount(int awareness); 
QPG float qpg_CFM_meanHeadway(void); 
QPG float qpg_CFM_meanReactionTime(void); 
QPG float qpg_CFM_safeDistance(VEHICLE* vehicle, float speed);
QPG float qpg_CFM_stoppingDistance(VEHICLE* vehicle);
QPG float qpg_CFM_thresholdDistance(VEHICLE* vehicle);
QPG float qpg_CFM_curveSpeed(float r, LINK* link);
QPG float qpg_CFM_headwayFactor(VEHICLE* vehicle, LINK* link);
QPG float qpg_CFM_minimumGap(void);
QPG float qpg_CFM_rampMergeHeadway(VEHICLE* vehicle);
QPG float qpg_CFM_rampRevertDistance(VEHICLE* vehicle);
QPG float qpg_CFM_thresholdDistance(VEHICLE* vehicle);
QPG int   qpg_CLK_date(void); 
QPG Bool  qpg_CLK_singleStep(void); 
QPG CPK_USERDATA* qpg_CPK_userdata(CARPARK* carpark);
QPG int   qpg_DMD_currentPeriod(void);
QPG float qpg_DMD_demand(int matrix, int origin, int destination);
QPG Bool  qpg_DMD_isPeriodic(void);
QPG int   qpg_DMD_matrixCount(void);
QPG int   qpg_DMD_periods(void);
QPG int   qpg_DMD_profiles(void);
QPG int   qpg_DMD_randomVehicleType(int matrix);
QPG int   qpg_DTC_index(DETECTOR* detector);
QPG Bool  qpg_DTC_isLoopType(DETECTOR* detector);
QPG Bool  qpg_DTC_isMultiple(DETECTOR* detector);
QPG int   qpg_DTC_lane(DETECTOR* detector);
QPG int   qpg_DTC_end_lane(DETECTOR* detector);
QPG LINK* qpg_DTC_link(DETECTOR* detector);
QPG LOOP* qpg_DTC_multipleLoop(DETECTOR* detector, int lane);
QPG char* qpg_DTC_name(DETECTOR* detector);
QPG Bool  qpg_DTC_selected(DETECTOR* detector);
QPG LOOP* qpg_DTC_singleLoop(DETECTOR* detector);
QPG DTC_USERDATA* qpg_DTC_userdata(DETECTOR* detector);
QPG int   qpg_DTL_count(LOOP* loop, int type);
QPG int   qpg_DTL_count(LOOP* loop, int vehicletype);
QPG float qpg_DTL_downstreamDistance(LOOP* loop);
QPG Bool  qpg_DTL_faulty(LOOP* loop);
QPG float qpg_DTL_flow(LOOP* loop, int type);
QPG float qpg_DTL_gap(LOOP* loop, int type);
QPG int   qpg_DTL_lanechangeLeft(LOOP* loop);
QPG int   qpg_DTL_lanechangeRight(LOOP* loop);
QPG float qpg_DTL_occupancy(LOOP* loop, int type);
QPG float qpg_DTL_speed(LOOP* loop, int type);
QPG float qpg_DTL_state(LOOP* loop, int edge, int type);
QPG Bool  qpg_DTL_suspect(LOOP* loop);
QPG float qpg_DTL_upstreamDistance(LOOP* loop);
QPG DTL_USERDATA* qpg_DTL_userdata(LOOP* loop);
QPG Bool  qpg_LIC_granted(int type, int count);
QPG Bool  qpg_LCM_gapExists(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link, Bool u);
QPG void  qpg_LCM_laneUsage(VEHICLE* vehicle, LINK* link, int *loLane, int *hiLane);
QPG Bool  qpg_LCM_moveIn(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link);
QPG Bool  qpg_LCM_moveOut(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link);
QPG float qpg_LCM_forceMergeDistance(VEHICLE* vehicle, VEHICLE* remvehicle);
QPG int   qpg_LCM_overtakeTime(VEHICLE* vehicle);
QPG int   qpg_LCM_passTime(VEHICLE* vehicle);
QPG int   qpg_LCM_resetTime(VEHICLE* vehicle);
QPG float qpg_LCM_signpostAllowDistance(VEHICLE* vehicle, float signposting);
QPG float qpg_LCM_signpostMergeDistance(VEHICLE* vehicle, float signposting, Bool urgent);
QPG float qpg_LNK_angle(LINK* link);
QPG Bool  qpg_LNK_arc(LINK* link);
QPG float qpg_LNK_radius(LINK* link);
QPG Bool  qpg_LNK_arcLeft(LINK* link);
QPG LINK* qpg_LNK_backside(LINK* link);
QPG Bool  qpg_LNK_barred(LINK* link);
QPG int   qpg_LNK_beaconIndexByIndex(LINK* link, int index);
QPG int   qpg_LNK_beacons(LINK* link);
QPG int   qpg_LNK_category(LINK* link);
QPG int   qpg_LNK_cost(LINK* link, int table); 
QPG float qpg_LNK_costFactor(LINK* link);
QPG int   qpg_LNK_destinationCost(LINK* link, int destination, int table);
QPG int   qpg_LNK_detectorIndexByIndex(LINK* link, int index);
QPG float qpg_LNK_detectorPositionByIndex(LINK* link, int index);
QPG int   qpg_LNK_detectors(LINK* link);
QPG float qpg_LNK_endAngle(LINK* link);
QPG float qpg_LNK_endspeed(LINK* link);
QPG LINK* qpg_LNK_entry(LINK* link, int index); 
QPG int   qpg_LNK_entryLinks(LINK* link);
QPG LINK* qpg_LNK_exit(LINK* link, int index); 
QPG int   qpg_LNK_exitLinks(LINK* link);
QPG int   qpg_LNK_exitCost(LINK* link1, LINK* link2, int table);
QPG Bool  qpg_LNK_forceAcross(LINK* link);
QPG Bool  qpg_LNK_forceMerge(LINK* link);
QPG Bool  qpg_LNK_shareLanes(LINK* link);
QPG float qpg_LNK_gradient(LINK* link);
QPG int   qpg_LNK_hazard(LINK* link); 
QPG float qpg_LNK_headwayMod(LINK* link);
QPG float qpg_LNK_reactionMod(LINK* link);
QPG int   qpg_LNK_index(LINK* link);
QPG int   qpg_LNK_laneRestriction(LINK* link, int lane);
QPG int   qpg_LNK_exitRestriction(LINK* link, int exit);
QPG void  qpg_LNK_exitLanes(LINK* link, int exit, int *lo, int *hi);
QPG int   qpg_LNK_lanes(LINK* link);
QPG float qpg_LNK_length(LINK* link);
QPG LINK* qpg_LNK_link(LINK* link, int index);
QPG int   qpg_LNK_links(LINK* link);
QPG int   qpg_LNK_linktype(LINK* link);
QPG LINK* qpg_LNK_match(LINK* link);
QPG float qpg_LNK_medianWidth(LINK* link);
QPG char* qpg_LNK_name(LINK* link);
QPG LINK* qpg_LNK_nearside(LINK* link);
QPG NODE* qpg_LNK_nodeEnd(LINK* link);
QPG NODE* qpg_LNK_nodeStart(LINK* link);
QPG LINK* qpg_LNK_offside(LINK* link);
QPG Bool  qpg_LNK_onRoundabout(LINK* link);
QPG RAMP* qpg_LNK_ramp(LINK* link, int index);
QPG int   qpg_LNK_ramps(LINK* link);
QPG Bool  qpg_LNK_ratelocked(LINK* link);
QPG Bool  qpg_LNK_restrictedType(LINK* link, int v_type);
QPG Bool  qpg_LNK_signalsAhead(LINK* link, VEHICLE* vehicle);
QPG Bool  qpg_LNK_signalsNearside(LINK* link, VEHICLE* vehicle);
QPG float qpg_LNK_signposting(LINK* link);
QPG SLIP* qpg_LNK_slip(LINK* link);
QPG Bool  qpg_LNK_slipLane(LINK* link);
QPG Bool  qpg_LNK_special(LINK* link);
QPG float qpg_LNK_speedlimit(LINK* link);
QPG Bool  qpg_LNK_stackingStopline(LINK* link);
QPG float qpg_LNK_startAngle(LINK* link);
QPG Bool  qpg_LNK_stayInLane(LINK* link);
QPG float qpg_LNK_toHazard(LINK* link, VEHICLE* vehicle);
QPG Bool  qpg_LNK_toRamp(LINK* link);
QPG Bool  qpg_LNK_tolls(LINK* link);
QPG int   qpg_LNK_turncount(LINK* link, int exit);
QPG float qpg_LNK_turnspeed(LINK* link, int exit); 
QPG Bool  qpg_LNK_urban(LINK* link);
QPG LNK_USERDATA* qpg_LNK_userdata(LINK* link);
QPG VEHICLE* qpg_LNK_vehicleHead(LINK* link, int lane);
QPG void  qpg_LNK_vehicleList(LINK* link, int lane, int count, VEHICLE* vehicle[]);
QPG VEHICLE* qpg_LNK_vehicleTail(LINK* link, int lane);
QPG int   qpg_LNK_vehicles(LINK* link, int lane);
QPG void  qpg_LNK_vehiclesAtPosition(LINK* link, int lane, float dist, 
                                     VEHICLE** infront, VEHICLE** behind);
QPG Bool  qpg_LNK_wideEnd(LINK* link);
QPG Bool  qpg_LNK_wideStart(LINK* link);
QPG float qpg_LNK_width(LINK* link);
QPG int   qpg_LNK_zone(LINK* link);
QPG Bool  qpg_LNK_zoneConnector(LINK* link);
QPG Bool  qpg_CAT_isMajor(int category);
QPG Bool  qpg_CAT_isUrban(int category);
QPG int   qpg_CAT_colour(int category);
QPG float qpg_CAT_toll(int category) ;
QPG float qpg_CAT_costFactor(int category);
QPG Bool  qpg_CAT_busOnly(int category);
QPG Bool  qpg_CAT_closures(int category);
QPG float qpg_CAT_curveFactor(int category);
QPG float qpg_CAT_headwayFactor(int category);
QPG Bool  qpg_CAT_forceMerge(int category);
QPG Bool  qpg_CAT_forceAcross(int category);
QPG Bool  qpg_CAT_stayInLane(int category);
QPG Bool  qpg_CAT_freewayLaneModel(int category);
QPG float qpg_CAT_signpost(int category);
QPG float qpg_CAT_range(int category);
QPG float qpg_CAT_width(int category);
QPG float qpg_CAT_median(int category);
QPG float qpg_CAT_speed(int category);
QPG int   qpg_CAT_lanes(int category);
QPG Bool  qpg_NDE_connected(NODE* node1, NODE* node2);
QPG int   qpg_NDE_entryLinks(NODE* node);
QPG int   qpg_NDE_exitLinks(NODE* node);
QPG Bool  qpg_NDE_ghostIsland(NODE* node);
QPG Bool  qpg_NDE_hold(NODE* node);
QPG int   qpg_NDE_index(NODE* node);
QPG LINK* qpg_NDE_link(NODE* node, int index);
QPG LINK* qpg_NDE_linkEntry(NODE* node, int index);
QPG int   qpg_NDE_links(NODE* node);
QPG char* qpg_NDE_name(NODE* node);
QPG int   qpg_NDE_phases(NODE* node);
QPG Bool  qpg_NDE_roundabout(NODE* node);
QPG Bool  qpg_NDE_signalised(NODE* node);
QPG NDE_USERDATA* qpg_NDE_userdata(NODE* node);
QPG Bool  qpg_NDE_variable(NODE* node);
QPG Bool  qpg_NDE_externalController(NODE *node);
QPG int   qpg_NDE_externalControllerID(NODE *node);
QPG int   qpg_NDE_externalControllerDetectorCount(NODE *node, LINK* inlink, LINK* outlink);
QPG int   qpg_NDE_externalControllerMovementID(NODE *node, LINK* inlink, LINK* outlink);
QPG DETECTOR* qpg_NDE_externalControllerDetector(NODE *node, LINK* inlink, LINK* outlink, int index);
QPG float qpg_NDE_externalControllerNParameter(NODE *node, int index);
QPG char  *qpg_NDE_externalControllerFParameter(NODE *node, int index);
QPG BEACON* qpg_NET_beacon(char *name);
QPG BEACON* qpg_NET_beaconByIndex(int index);
QPG int   qpg_NET_beacons(void);
QPG int   qpg_NET_numBlockingRegions(void);
QPG char** qpg_NET_blockingRegionNames(void);
QPG Bool  qpg_NET_blockingRegionOpen(char* name);
QPG Bool  qpg_NET_blockingRegionAgentsWaiting(char* name);
QPS void  qps_NET_blockingRegionOpen(char* name, Bool set);
QPS void  qps_NET_blockingRegionAgentsWaiting(char* name, Bool set);
QPG int   qpg_NET_categories(void);
QPG char* qpg_NET_dataPath(void);
QPG char* qpg_NET_datapath(void);
QPG DETECTOR* qpg_NET_detector(char *name);
QPG DETECTOR* qpg_NET_detectorByIndex(int index);
QPG int   qpg_NET_detectors(void);
QPG LINK* qpg_NET_link(char *name);
QPG LINK* qpg_NET_linkByIndex(int id);
QPG int   qpg_NET_links(void);
QPG NODE* qpg_NET_node(char *name);
QPG NODE* qpg_NET_nodeByIndex(int id);
QPG int   qpg_NET_nodes(void);
QPG int	  qpg_NET_numStudyAreas(void);
QPG char** qpg_NET_studyAreaNames(void);
QPG float qpg_NET_speedUp(void);
QPG int   qpg_NET_lastNv(void);
QPG char* qpg_NET_statsPath(void);
QPG NET_USERDATA* qpg_NET_userdata();
QPG int   qpg_NET_vehicleTypes(void);
QPG int   qpg_NET_vehiclesDemanded(void);
QPG int   qpg_NET_vehiclesSimulated(void);
QPG int   qpg_NET_vehiclesSimulating(void);
QPG ZONE* qpg_NET_zone(int index); 
QPG int   qpg_NET_zones(void);
QPG int   qpg_NET_wholeSeconds(void);
QPG void  qpg_POS_beacon(BEACON* beacon, float *x, float *y, float *z, float *bearing, float *gradient);
QPG void  qpg_POS_crossHair(float *x, float *y, float *z);
QPG void  qpg_POS_viewPoint(float *x, float *y, float *z);
QPG void  qpg_POS_detector(DETECTOR* detector, float *x, float *y, float *z, float *b, float *g);
QPG void  qpg_POS_kerb(LINK* link, int kerb, float *x, float *y, float *z);
QPG void  qpg_POS_link(LINK* link, int lane, float dist, float *x, float *y, float *z, float *b, float *g);
QPG void  qpg_POS_network(float *llx, float *lly, float *urx, float *ury);
QPG void  qpg_POS_node(NODE* node, float *x, float *y, float *z);
QPG void  qpg_POS_stopline(LINK* link, int lane, int stopline, float *x, float *y, float *z, float *b, float *g);
QPG void  qpg_POS_vehicle(VEHICLE* vehicle, LINK* link, float *x, float *y, float *z, float *b, float *g);
QPG void  qpg_POS_vehicleNoAdjust(VEHICLE* vehicle, LINK* link, float *x, float *y, float *z, float *b, float *g);
QPG void  qpg_POS_vehicleExternal(VEHICLE* vehicle, LINK* link, float *x, float *y, float *z, float *b, float *g);
QPG void  qpg_POS_zone(ZONE* zone, float *x, float *y, float *z);
QPG void  qpg_POS_zoneVertex(ZONE* zone, int index, float *x, float *y, float *z);
QPG RMP_USERDATA* qpg_RMP_userdata(RAMP* ramp);
QPG VEHICLE* qpg_RMP_vehicleHead(RAMP* ramp, int lane);
QPG void  qpg_RMP_vehicleList(RAMP* ramp, int lane, int count, VEHICLE* vehicle[]);
QPG VEHICLE* qpg_RMP_vehicleTail(RAMP* ramp, int lane);
QPG int   qpg_RMP_vehicles(RAMP* ramp, int lane);

QPG float qpg_RTR_distanceRemaining(LINK* link, VEHICLE* vehicle);
QPG int   qpg_RTR_tables(void);
QPG int   qpg_RTR_nextLinkIndex(LINK *link, int dest, int table, int ptbn);
QPG float qpg_SCO_matchDistance(VEHICLE* vehicle, LINK* link);
QPG VEHICLE* qpg_SCO_overtaken(VEHICLE* vehicle);
QPG Bool  qpg_SCO_overtaking(VEHICLE* vehicle);
QPG Bool  qpg_SCO_overtakingLink(LINK* link);
QPG void  qpg_SCO_vehicles(LINK* link, int lane, float dist, VEHICLE** infrontvehicle, VEHICLE** behindvehicle);
QPG Bool  qpg_SCO_gapExists(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link, Bool urgent);
QPG Bool  qpg_SCO_pullIn(LINK* link, VEHICLE* vehicle);
QPG Bool  qpg_SCO_pullOut(LINK* link, VEHICLE* vehicle);

QPG Bool  qpg_SIG_inquiry(NODE* node, int phase_index, int inquiry, float *value);
QPG SLP_USERDATA* qpg_SLP_userdata(SLIP* slip);
QPG VEHICLE* qpg_SLP_vehicleHead(SLIP* slip);
QPG void  qpg_SLP_vehicleList(SLIP* slip, int count, VEHICLE* vehicle[]);
QPG VEHICLE* qpg_SLP_vehicleTail(SLIP* slip);
QPG int   qpg_SLP_vehicles(SLIP* slip);
QPG int   qpg_STA_allLastCount(void);
QPG float qpg_STA_allLastSpeed(void);
QPG float qpg_STA_allMeanDelay(void);
QPG float qpg_STA_allMeanSpeed(void);
QPG int   qpg_STA_allTotalCount(void);
QPG float qpg_STA_allTotalDelay(void);
QPG double qpg_STA_allTotalDistance(void);
QPG int   qpg_STA_busGetOff(void);
QPG int   qpg_STA_busGetOn(void);
QPG int   qpg_STA_busLastCount(void);
QPG float qpg_STA_busLastSpeed(void);
QPG float qpg_STA_busMeanDelay(void);
QPG float qpg_STA_busMeanSpeed(void);
QPG int   qpg_STA_busTotalCount(void);
QPG float qpg_STA_busTotalDelay(void);
QPG double qpg_STA_busTotalDistance(void);
QPG int   qpg_STA_busTotalStopTime(void);
QPG int   qpg_STA_busTotalStops(void);
QPG float qpg_STA_count(LINK* link, int lane);
QPG float qpg_STA_delay(LINK* link, int lane);
QPG float qpg_STA_density(LINK* link, int lane);
QPG float qpg_STA_flow(LINK* link, int lane); 
QPG float qpg_STA_percentDelay(LINK* link, int lane);
QPG float qpg_STA_speed(LINK* link, int lane);
QPG int   qpg_STA_stoplineQueueCount(LINK* link, int lane);
QPG float qpg_STA_stoplineQueueLength(LINK* link, int lane);
QPG float qpg_STA_stoplineQueuePCUs(LINK* link, int lane);
QPG int   qpg_STA_vehicleLastCount(void);
QPG float qpg_STA_vehicleLastSpeed(void);
QPG float qpg_STA_vehicleMeanDelay(void);
QPG float qpg_STA_vehicleMeanSpeed(void);
QPG int   qpg_STA_vehicleTotalCount(void);
QPG float qpg_STA_vehicleTotalDelay(void);
QPG double qpg_STA_vehicleTotalDistance(void);
QPG int   qpg_STA_vehicleTotalStopTime(void);
QPG char* qpg_UTL_accelerationUnitLabel(void);
QPG char* qpg_UTL_appendExtension(char *filename, char *extension);
QPG char* qpg_UTL_densityUnitLabel(void);
QPG Bool  qpg_UTL_directoryExists(char *path);
QPG char* qpg_UTL_distanceUnitLabel(void);
QPG char* qpg_UTL_eventDensityUnitLabel(void);
QPG Bool  qpg_UTL_fileClose(FILE *fp);
QPG FILE* qpg_UTL_fileOpen(char *md, char *path);
QPG Bool  qpg_UTL_fileExists(char *path);
QPG void  qpg_UTL_integerToTime(int t, int *dy, int *hr, int *mn, int *sc);
QPG char* qpg_UTL_integerToTimeFileName(int t);
QPG char* qpg_UTL_integerToTimeString(int t);
QPG int   qpg_UTL_lapTimer(long ref, char scale);
QPG float qpg_UTL_linearSpread(int p1, int p2, float value, float delta);
QPG float qpg_UTL_linearSpread(int p1, int p2, float value, float delta);
QPG int   qpg_UTL_linesInFile(char *path);
QPG Bool  qpg_UTL_makeDirectory(char *path);
QPG int   qpg_UTL_openFiles(void);
QPG char* qpg_UTL_paramicsDataHome(void);
QPG char* qpg_UTL_paramicsHome(void);
QPG Bool  qpg_UTL_permissionCheck(void);
QPG Bool  qpg_UTL_pluginExcluded(char* basename, char* name);
QPG Bool  qpg_UTL_randomBoolean(int stream, int ctrue);
QPG double qpg_UTL_randomDouble(int stream, double range);
QPG float qpg_UTL_randomFloat(int stream, float range);
QPG int   qpg_UTL_randomInteger(int stream, int range);
QPG int   qpg_UTL_randomNormalInteger(int stream, int mean, int std_dev);
QPG int   qpg_UTL_randomPoissonInteger(int stream, float mean);
QPG int   qpg_UTL_readTimer(long ref, char scale);
QPG float qpg_UTL_skewSpread(int p1, int p2, float value, float delta, float skew);
QPG float qpg_UTL_skewSpread(int p1, int p2, float value, float delta, float skew);
QPG char* qpg_UTL_speedUnitLabel(void);
QPG long qpg_UTL_startTimer(void);
QPG float qpg_UTL_toExternalAcceleration(void);
QPG float qpg_UTL_toExternalDensity(void);
QPG float qpg_UTL_toExternalDistance(void);
QPG float qpg_UTL_toExternalSpeed(void);
QPG float qpg_UTL_toExternalWeight(void);
QPG float qpg_UTL_toInternalAcceleration(void);
QPG float qpg_UTL_toInternalDensity(void);
QPG float qpg_UTL_toInternalDistance(void);
QPG float qpg_UTL_toInternalSpeed(void);
QPG float qpg_UTL_toInternalWeight(void);
QPG char* qpg_UTL_licenseID(void);
QPG char* qpg_UTL_weightUnitLabel(void);

QPG float qpg_UTL_toExternalDistanceNGM(int distMode);
QPG float qpg_UTL_toInternalDistanceNGM(int distMode);
QPG char *qpg_UTL_distanceUnitLabelNGM(int distMode);
QPG float qpg_UTL_toExternalSpeedNGM(int spMode);
QPG float qpg_UTL_toInternalSpeedNGM(int spMode);
QPG char *qpg_UTL_speedUnitLabelNGM(int spMode);
QPG float qpg_UTL_toExternalAccelerationNGM(int accMode);
QPG float qpg_UTL_toInternalAccelerationNGM(int accMode);
QPG char *qpg_UTL_accelerationUnitLabelNGM(int accMode);
QPG float qpg_UTL_toExternalDensityNGM(int denMode);
QPG float qpg_UTL_toInternalDensityNGM(int denMode);
QPG char *qpg_UTL_densityUnitLabelNGM(int denMode);
QPG char *qpg_UTL_densityDistUnitLabelNGM(int denMode);
QPG char *qpg_UTL_eventDensityUnitLabelNGM(int denMode);
QPG float qpg_UTL_toExternalWeightNGM(int wgtMode);
QPG float qpg_UTL_toInternalWeightNGM(int wgtMode);
QPG char *qpg_UTL_weightUnitLabelNGM(int wgtMode);

QPG Bool  qpg_UTL_yaccParser(char *path, char *file, FILE **datafilein, FILE **datafileout, 
                             int *count, int(*parseFn)(void), int(*wrapFn)(void));

QPG Bool  qpg_VHC_accelerating(VEHICLE* vehicle);
QPG float qpg_VHC_acceleration(VEHICLE* vehicle);
QPG int   qpg_VHC_age(VEHICLE* vehicle);
QPG int   qpg_VHC_aggression(VEHICLE* vehicle);
QPG VEHICLE* qpg_VHC_ahead(VEHICLE* vehicle);
QPG int   qpg_VHC_awareness(VEHICLE* vehicle);
QPG VEHICLE* qpg_VHC_behind(VEHICLE* vehicle);
QPG Bool  qpg_VHC_braking(VEHICLE* vehicle);
QPG Bool  qpg_VHC_busAvoid(VEHICLE* vehicle, float to_hazard);
QPG float qpg_VHC_deceleration(VEHICLE* vehicle);
QPG float qpg_VHC_demand(VEHICLE* vehicle);
QPG int   qpg_VHC_destination(VEHICLE* vehicle);
QPG int   qpg_VHC_destinationTrip(VEHICLE* vehicle);
QPG float qpg_VHC_distance(VEHICLE* vehicle);
QPG int   qpg_VHC_existTime(VEHICLE* vehicle);
QPG float qpg_VHC_familiar(VEHICLE* vehicle);
QPG float qpg_VHC_height(VEHICLE* vehicle);
QPG Bool  qpg_VHC_incident(VEHICLE* vehicle);
QPG Bool  qpg_VHC_isBus(VEHICLE* vehicle);
QPG Bool  qpg_VHC_isHeavy(VEHICLE* vehicle);
QPG int   qpg_VHC_lane(VEHICLE* vehicle);
QPG int   qpg_VHC_laneHigh(VEHICLE* vehicle);
QPG int   qpg_VHC_laneLow(VEHICLE* vehicle);
QPG float qpg_VHC_length(VEHICLE* vehicle);
QPG Bool  qpg_VHC_letIn(VEHICLE* vehicle);
QPG LINK* qpg_VHC_link(VEHICLE* vehicle); 
QPG float qpg_VHC_linkAcceleration(LINK* link, VEHICLE* vehicle);
QPG float qpg_VHC_linkDeceleration(LINK* link, VEHICLE* vehicle);
QPG int   qpg_VHC_matrix(VEHICLE* vehicle);
QPG float qpg_VHC_maxSpeed(VEHICLE* V);
QPG Bool  qpg_VHC_movingIn(VEHICLE* vehicle);
QPG Bool  qpg_VHC_movingOut(VEHICLE* vehicle);
QPG int   qpg_VHC_nextExit(VEHICLE* vehicle);
QPG int   qpg_VHC_nextNextExit(VEHICLE* vehicle);
QPG int   qpg_VHC_nextLane(VEHICLE* vehicle);
QPG Bool  qpg_VHC_notMajor(LINK* link, VEHICLE* vehicle);
QPG Bool  qpg_VHC_onNode(VEHICLE* vehicle);
QPG int   qpg_VHC_origin(VEHICLE* vehicle);
QPG int   qpg_VHC_originTrip(VEHICLE* vehicle);
QPG VEHICLE* qpg_VHC_original(VEHICLE* vehicle);
QPG float qpg_VHC_pcus(VEHICLE* vehicle);
QPG float qpg_VHC_perturbation(VEHICLE* vehicle);
QPG int   qpg_VHC_routeTable(VEHICLE* vehicle);
QPG Bool  qpg_VHC_shareLanes(VEHICLE* vehicle, Bool nearside);
QPG Bool  qpg_VHC_special(VEHICLE* vehicle, int index);
QPG float qpg_VHC_speed(VEHICLE* vehicle);
QPG float qpg_VHC_speedHistoric(VEHICLE* vehicle, float time);
QPG int   qpg_VHC_startTime(VEHICLE* vehicle);
QPG Bool  qpg_VHC_stopped(VEHICLE* vehicle);
QPG int   qpg_VHC_tracer(VEHICLE* vehicle);
QPG int   qpg_VHC_type(VEHICLE* vehicle);
QPG VHC_USERDATA* qpg_VHC_userdata(VEHICLE* vehicle);
QPG Bool  qpg_VHC_usertag(VEHICLE* vehicle);
QPG float qpg_VHC_weight(VEHICLE* vehicle);
QPG float qpg_VHC_width(VEHICLE* vehicle);
QPG float qpg_VTP_acceleration(int t);
QPG float qpg_VTP_deceleration(int t);
QPG float qpg_VTP_demand(int t);
QPG float qpg_VTP_familiar(int t);
QPG float qpg_VTP_height(int t);
QPG float qpg_VTP_length(int t);
QPG int   qpg_VTP_matrix(int t);
QPG float qpg_VTP_maxSpeed(int t);
QPG float qpg_VTP_pcus(int t);
QPG float qpg_VTP_perturbation(int t);
QPG int   qpg_VTP_routeTable(int t);
QPG Bool  qpg_VTP_restricted(int t, int restriction);
QPG float qpg_VTP_weight(int t);
QPG float qpg_VTP_width(int t);
QPG int   qpg_ZNE_carparks(ZONE* zone);
QPG int   qpg_ZNE_externalIndex(int index); 
QPG int   qpg_ZNE_index(ZONE* zone); 
QPG LINK* qpg_ZNE_link(ZONE* zone, int index); 
QPG int   qpg_ZNE_links(ZONE* zone); 
QPG int   qpg_ZNE_released(ZONE* zone);
QPG int   qpg_ZNE_targetDemand(int orig, int dest, int matrix);
QPG int   qpg_ZNE_type(ZONE* zone);
QPG int   qpg_ZNE_unreleased(ZONE* zone); 
QPG ZNE_USERDATA* qpg_ZNE_userdata(ZONE* zone);
QPG int   qpg_ZNE_vertices(ZONE* zone); 
QPS void  qps_GUI_redraw(void);

QPX void qpx_GUI_keyPress(int key, int ctrl, int shift, int left, int middle, int right);
QPX void qpx_GUI_keyRelease(int key, int ctrl, int shift, int left, int middle, int right);

QPG Bool  qpg_DRW_cullingEnabled(void);
QPG Bool  qpg_DRW_vehicleVisible(VEHICLE* vehicle);
QPG Bool  qpg_DRW_linkVisible(LINK* link);
QPG Bool  qpg_DRW_lineVisible(float sx, float sy,float sz,float ex, float ey,float ez);
QPG Bool  qpg_DRW_polygonVisible(int count, float x[], float y[], float z[]);
QPG Bool  qpg_DRW_pointVisible(float x, float y, float z );
QPG Bool  qpg_DRW_sphereVisible(float x, float y, float z, float radius );
QPG Bool  qpg_DRW_cubeVisible(float x, float y, float z, float size );
QPG float qpg_DRW_distanceToVisibleObject(float x, float y, float z, float radius);
QPG float qpg_DRW_vehicleDistanceFromViewPoint(VEHICLE* vehicle);

QPG Bool  qpg_SIM_licensed(void);
QPG int   qpg_SIM_simulate(int countdown);

/* 4.2 */
QPG void qpg_POS_busStop(BUSSTOP* busstop, float *x, float *y, float *z);
QPG LINK* qpg_BST_link(BUSSTOP* busstop);
QPG float qpg_BST_linkDistance(BUSSTOP* busstop);
QPG char *qpg_BST_name(BUSSTOP* busstop);
QPG int qpg_RMP_lanes(RAMP* ramp);
QPX void  qpx_BUS_stopping(VEHICLE* vehicle, BUSSTOP* stop);
QPG int qpg_NET_busroutes(void);
QPG BUSROUTE* qpg_NET_busrouteByIndex(int id);
QPG int qpg_BSR_links(BUSROUTE *busroute);
QPG LINK* qpg_BSR_link(BUSROUTE *busroute, int index);
QPG Bool qpg_DTC_testOccupied(DETECTOR* d);
QPS void qps_DTC_testOccupied(DETECTOR* d, Bool state);
QPS void qps_CFG_demandWeight(float weight);
QPS void qps_NET_clearVehicles(void);
QPG int  qpg_LNK_priority(LINK* link1, LINK* link2);

/* 5.0 */
QPS void qps_VHC_stopped(VEHICLE* V, Bool v);
QPS void qps_VHC_laneRange(VEHICLE* V, int low, int high);
QPS void qps_VHC_laneLow(VEHICLE* V, int lane);
QPS void qps_VHC_laneHigh(VEHICLE* V, int lane);
QPS void qps_VHC_nextlane(VEHICLE* V, int lane);
QPS void qps_VHC_laneChange(VEHICLE* V, int direction);
QPS void qps_LNK_closure(LINK* link, int lane, Bool open);
QPS void qps_LNK_restriction(LINK* link, int lane, int restriction);
QPS void qps_LNK_speedcontrol(LINK* link, int lane, int rule);
QPS void qps_LNK_turnCost(LINK* link, int exit, int cost);
QPS void qps_LNK_nextlane(LINK *link, int lane, int exit, int next, int range);

QPG int   qpg_LNK_nextlane(LINK *link, int lane, int exit, int* range);
QPS void  qps_LNK_exitLanes(LINK* link, int exit, int lo, int hi);

QPG int   qpg_VTP_colour(int t);
QPG char* qpg_VTP_name(int t);
QPG int   qpg_VTP_trailers(int t);
QPG float qpg_VTP_cabLength(int t);
QPG Bool  qpg_VTP_fixedRoute(int t);
QPG LINK* qpg_RMP_inlink(RAMP* ramp);
QPG float qpg_RMP_length(RAMP* ramp);
QPG float qpg_RMP_tailpoint(RAMP* ramp);

QPS void qps_RTR_buildTables(Bool on);

QPS void  qps_VHC_holdTransfer(VEHICLE* V, Bool hold); 

QPS void  qps_ZNE_vehicleLink(LINK* link); 


QPO Bool qpo_RTM_arrival2(LINK* link, VEHICLE* vehicle, Bool arrival);

QPO float qpo_CFM_leadSpeed(LINK* link, VEHICLE* vehicle,  
                            VEHICLE* infrontvehicle[]);

QPO float qpo_CFM_followSpeed(LINK* link, VEHICLE* vehicle,  
                              VEHICLE* infrontvehicle[]);

QPG float qpg_CFM_leadSpeed(LINK* link, VEHICLE* vehicle,  
                            VEHICLE* infrontvehicle[]);

QPG float qpg_CFM_followSpeed(LINK* link, VEHICLE* vehicle,  
                              VEHICLE* infrontvehicle[]);

QPS void  qps_POS_crossHair(float x, float y, float z);
QPS void  qps_POS_viewPoint(float x, float y, float z);

QPS void qps_VHC_usertagInc(VEHICLE* vehicle);
QPS void qps_VHC_usertagDec(VEHICLE* vehicle);
QPS void qps_VHC_changeLane(VEHICLE* vehicle, int direction);

QPG LINK *qpg_RMP_mainlineLink(RAMP* ramp);

QPS void qps_NDE_externalControllerTCNode(NODE *node, Bool on);
QPS void qps_NDE_externalControllerTCNodeID(NODE *node, int id);

QPG Bool qpg_NDE_externalControllerTCNode(NODE *node);
QPG int qpg_NDE_externalControllerTCNodeID(NODE *node);


QPG int qpg_LNK_turnCost(LINK* link, int exit);
QPG float qpg_LNK_DFTurnSumTime(LINK* link, int exit);
QPG int qpg_LNK_DFTurnCount(LINK* link, int exit);
QPS void qps_LNK_DFTurnSumTime(LINK* link, int exit, float time);
QPS void qps_LNK_DFTurnCount(LINK* link, int exit, int count);


QPS int qpg_SIG_priority(NODE *node, int phase_index, LINK* inlink, LINK* outlink);


QPG Bool qpg_SIM_running(void);
QPS void qps_SIM_running(Bool state);
QPS void qps_SIM_restart(void);

QPG Bool qpg_GUI_simRunning(void);
QPS void qps_GUI_simRunning(Bool state);
QPS void qps_GUI_simRestart(void);

QPG Bool qpg_GUI_singleStep(void);
QPS void qps_GUI_singleStep(Bool);
QPS void qps_GUI_runSimulation(void);

QPG int qpg_NDE_AllLinksIn(NODE* node);
QPG int qpg_NDE_AllLinksOut(NODE* node);


/* 5.1 */
QPG int	  qpg_UTL_parentProduct(void);
QPG Bool  qpg_UTL_parentHasGUI(void);
QPG float qpg_UTL_parentProductVersion(void);

QPG int	  qpg_UTL_pluginCount(void);
QPG char* qpg_UTL_pluginFile(int index);

QPX void  qpx_CLK_startOfSimLoop(void);
QPX void  qpx_CLK_endOfSimLoop(void);

QPS void  qps_VHC_incident(VEHICLE* V, int type, char* name, int colour, int lane, float dist, float wait,  float pass, float oppo);

QPG int	  qpg_VHC_uniqueID(VEHICLE* V);
QPG VEHICLE* qpg_VHC_lookupVByLane(LINK* link, int lane, int vID);
QPG VEHICLE* qpg_VHC_lookupV(LINK* link, int vID);
QPS void qps_VHC_nextlink(VEHICLE* V, int newExit);

// 5.1.1
QPG void qpg_UTL_loadSnapshot(char *path,char *filename);
QPS void qps_UTL_saveSnapshot(char *path,char *filename);

// New in 6.2.0
QPG void qpg_POS_nearestNode(NODE** node, float *x, float *y, float *z);
QPG void qpg_POS_nearestLink(LINK** link, float *x, float *y, float *z);
QPG void qpg_POS_nearestZone(ZONE** zone, float *x, float *y, float *z);
QPG void qpg_POS_nearestCarpark(CARPARK** carpark, float *x, float *y, float *z);
QPG void qpg_POS_nearestSector(SECTOR** sector, float *x, float *y, float *z);
QPG void qpg_POS_nearestVehicle(VEHICLE** vehicle, float *x, float *y, float *z);

QPX void qpx_VHC_preRemove(VEHICLE* vehicle);

// v5 fucntions re-added in 6.6.0
QPX void  qpx_GUI_editorSelection(void);
QPX void  qpx_GUI_viewSelection(void);

QPG BEACON* qpg_EDT_selectedBeacon(void);
QPG BUSROUTE* qpg_EDT_selectedBusRoute(void);
QPG BUSSTOP* qpg_EDT_selectedBusStop(void);
QPG CARPARK* qpg_EDT_selectedCarpark(void);
QPG DETECTOR* qpg_EDT_selectedDetector(void);
QPG LINK* qpg_EDT_selectedInwardLink(void);
QPG LINK* qpg_EDT_selectedLink(void);
QPG NODE* qpg_EDT_selectedNode(void);
QPG NODE* qpg_EDT_selectedNodeSecondary(void);
QPG int   qpg_EDT_selectedOutwardIndex(void);
QPG LINK* qpg_EDT_selectedOutwardLink(void);
QPG ZONE* qpg_EDT_selectedZone(void);

QPG BEACON* qpg_GUI_selectedBeacon(void);
QPG CARPARK* qpg_GUI_selectedCarpark(void);
QPG DETECTOR* qpg_GUI_selectedDetector(void);
QPG LINK* qpg_GUI_selectedLink(void);
QPG NODE* qpg_GUI_selectedNode(void);
QPG VEHICLE* qpg_GUI_selectedVehicle(void);
QPG ZONE* qpg_GUI_selectedZone(void);

// 6.7
QPS void qps_VTP_maxSpeed(int t, float speed);
QPS void qps_VHC_maxSpeed(VEHICLE* V, float speed); 


/** Functions below here were removed in v6: */

// not in v6 QPG int   qpg_DRW_layerColour(int object);
// not in v6 QPG Bool  qpg_DRW_layerVisable(int object); 
// not in v6 QPS void  qps_DRW_bandedTable(int count, char *labels[], int colours[], int fill[], int edge[], int yshift);
// not in v6 QPS void  qps_DRW_colourkey(char *min, char *max, char *title, float needle, int yshift);
// not in v6 QPS void qps_DRW_displayList(int object, Bool use);
// not in v6 QPS void  qps_DRW_eventTable(int count, char *labels[], int colours[], int tri1[], int tri2[], int shift);
// not in v6 QPS void  qps_DRW_layerColour(int object, int colour);
// not in v6 QPS void qps_DRW_textHeight(int index, float height);
// not in v6 QPG int   qpg_GUI_activeCamera(void);
// not in v6 QPG int   qpg_GUI_cameraID(int index);
// not in v6 QPG int*  qpg_GUI_cameraIDs(void);
// not in v6 QPG Bool  qpg_GUI_numberApiFiles(void);
// not in v6 QPG int   qpg_GUI_numCameras(void);
// not in v6 QPS void  qps_GUI_apiLabel(int fileIndex, int index, char *text, float value);
// not in v6 QPS void  qps_GUI_apiPanel(char *filename, int fileIndex, int num);
// not in v6 QPS void  qps_GUI_apiScale(int fileIndex, int index, char *text, float value,float lo, float hi, int p);
// not in v6 QPS void  qps_GUI_apiToggle(int fileIndex, int index, char *text, Bool state);
// not in v6 QPS void  qps_GUI_apiToolname(char *label);
// not in v6 QPS void  qps_GUI_enableTestMenu(Bool state);
// not in v6 QPS void  qps_GUI_range(char *filename, int index, float low, float high);
// not in v6 QPS void  qps_GUI_seperator(char *filename, char *name, int index);
// not in v6 QPS void  qps_GUI_toggle(char *filename, int index, Bool state);
// not in v6 QPS void  qps_GUI_value(char *filename, int index, float value);
// not in v6 QPX void qpx_GUI_testMenu(int type);
// not in v6 QPG int   qpg_NET_cameras(void);
// not in v6 QPG void  qpg_POS_cameraPosition(int index, float *vpx, float *vpy, float *vpz, float *chx, float *chy, float *chz);



#endif

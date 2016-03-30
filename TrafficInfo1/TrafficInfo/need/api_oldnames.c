/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 * Quadstone Ltd.             Tel: +44 131 220 4491
 * 16 Chester Street          Fax: +44 131 220 4492
 * Edinburgh,EH3 7RA,UK     WWW: http://www.paramics-online.com
 * ----------------------------------------------------------------------- */ 
/* -----------------------------------------------------------------------
 *
 * This file is an adapter for the pre-v4 names for the Paramics
 * Programmer functions. It is required only in the case where a
 * pre-v4 plugin is to be linked against a v4 library.
 * ----------------------------------------------------------------------- */ 

#include <stdarg.h>
#include "api_typedefs.h"
#include "api_user.h"

#define VSTRLEN 2048
static char str[VSTRLEN];

#ifdef WIN32
#define VSNPRINTF _vsnprintf
#else
#define VSNPRINTF vsnprintf
#endif


/* ------ Loop-Back ------------------------------------------------------ */

float std_follow_acc(VEHICLE* vehicle, VEHICLE* aheadvehicle,float gap, LINK* link) 
{
    return  qpg_CFM_followingAcceleration(vehicle,aheadvehicle,gap,link);
}

int std_lookahead_vehicles(int awareness) 
{
    return  qpg_CFM_lookAheadCount(awareness);
}

float std_constrained_acc(VEHICLE* vehicle, LINK* link,float speed,float dist)
{
    return  qpg_CFM_constrainedAcceleration(vehicle,link,speed,dist);
}

float std_gradient_acc(int type,int age,float speed,float grad,float acc)
{
    return  qpg_CFM_gradientAcceleration(type,age,speed,grad,acc);
}

Bool std_move_out(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link)
{
    return  qpg_LCM_moveOut(vehicle,infrontvehicle,behindvehicle,link);
}

Bool std_move_in(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link)
{
    return  qpg_LCM_moveIn(vehicle,infrontvehicle,behindvehicle,link);
}

Bool std_gap_exists(VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link,Bool urgent)
{
    return  qpg_LCM_gapExists(vehicle,aheadvehicle,behindvehicle,link,urgent);
}

void std_lane_usage(VEHICLE* vehicle, LINK* link,int *loLane,int *hiLane)
{
    qpg_LCM_laneUsage(vehicle,link,loLane,hiLane);
}

void std_behaviour(VEHICLE* vehicle)
{
    qpg_CFM_behaviour(vehicle);
}

float std_link_maxspeed(LINK* link, VEHICLE* vehicle)
{
    return  qpg_CFM_linkSpeed(link,vehicle);
}

float std_stopping_distance(VEHICLE* vehicle)
{
    return  qpg_CFM_stoppingDistance(vehicle);
}

float std_activate_distance(VEHICLE* vehicle)
{
    return  qpg_CFM_thresholdDistance(vehicle);
}

float std_safe_distance(VEHICLE* vehicle,float speed)
{
    return  qpg_CFM_safeDistance(vehicle,speed);
}



/* ------- Timing -------------------------------------------------------- */

float mean_headway(void)
{
    return  qpg_CFM_meanHeadway();
}

float mean_reaction(void)
{
    return  qpg_CFM_meanReactionTime();
}

/* ------- Config -------------------------------------------------------- */

float cfg_timestep(void)
{
    return  qpg_CFG_timeStep();
}

float timestep(void)
{
    return  qpg_CFG_timeStep();
}

void timestep_set(float val)
{
    qps_CFG_timeStep(val);
}


float simulation_time(void)
{
    return  qpg_CFG_simulationTime();
}

int cfg_speed_memory(void)
{
    return  qpg_CFG_speedMemory();
}

int cfg_start_time(void)
{
    return  qpg_CFG_startTime();
}

int cfg_duration(void)
{
    return  qpg_CFG_duration();
}

float cfg_demand_weight(void)
{
    return  qpg_CFG_demandWeight();
}

float cfg_timestepDetail(void)
{
    return qpg_CFG_timeStepDetail();
}


int cfg_seed(void)
{
    return  qpg_CFG_seed();
}

Bool cfg_split_seed(void)
{
    return  qpg_CFG_splitSeed();
}

float cfg_cost_a(void)
{
    return  qpg_CFG_costCoefficientA();
}

float cfg_cost_b(void)
{
    return  qpg_CFG_costCoefficientB();
}

float cfg_cost_c(void)
{
    return  qpg_CFG_costCoefficientC();
}

float cfg_q_speed(void)
{
    return  qpg_CFG_queueSpeed();
}

float cfg_q_gap(void)
{
    return  qpg_CFG_queueGap();
}

float cfg_heavy_weight(void)
{
    return  qpg_CFG_heavyWeight();
}

float cfg_loop_size(void)
{
    return  qpg_CFG_loopSize();
}

int cfg_feedback_period(void)
{
    return  qpg_CFG_feedbackPeriod();
}

Bool cfg_perturbation(void)
{
    return  qpg_CFG_perturbation();
}

Bool cfg_sqr_root(void)
{
    return  qpg_CFG_squareRootEnabled();
}

float cfg_feedback_smoothing(void)
{
    return  qpg_CFG_feedbackSmoothing();
}

float cfg_feedback_decay(void)
{
    return  qpg_CFG_feedbackDecay();
}

Bool cfg_turning_penalties_visible(void)
{
    return  qpg_CFG_turningPenaltiesVisible();
}

float cfg_amber_time(void)
{
    return  qpg_CFG_amberTime();
}

Bool cfg_closest_origin(void)
{
    return  qpg_CFG_closestOrigin();
}

Bool cfg_closest_detination(void)
{
    return  qpg_CFG_closestDestination();
}

char cfg_filetime_deliminator(void)
{
    return  qpg_CFG_filetimeDelimiter();
}

float cfg_curve_speed_factor(void)
{
    return  qpg_CFG_curveSpeedFactor();
}


/* ------- Stats -------------------------------------------------------- */

float sta_vehicle_total_delay(void)
{
    return  qpg_STA_vehicleTotalDelay();
}

double sta_vehicle_total_distance(void)
{
    return  qpg_STA_vehicleTotalDistance();
}

int sta_vehicle_total_count(void)
{
    return  qpg_STA_vehicleTotalCount();
}

int sta_vehicle_total_stop_time(void)
{
    return  qpg_STA_vehicleTotalStopTime();
}

float sta_vehicle_mean_speed(void)
{
    return  qpg_STA_vehicleMeanSpeed();
}

float sta_vehicle_mean_delay(void)
{
    return  qpg_STA_vehicleMeanDelay();
}

float sta_vehicle_last_speed(void)
{
    return  qpg_STA_vehicleLastSpeed();
}

int sta_vehicle_last_count(void)
{
    return  qpg_STA_vehicleLastCount();
}

float sta_bus_total_delay(void)
{
    return  qpg_STA_busTotalDelay();
}

double sta_bus_total_distance(void)
{
    return  qpg_STA_busTotalDistance();
}

int sta_bus_total_count(void)
{
    return  qpg_STA_busTotalCount();
}

float sta_bus_mean_speed(void)
{
    return  qpg_STA_busMeanSpeed();
}

float sta_bus_mean_delay(void)
{
    return  qpg_STA_busMeanDelay();
}

int sta_bus_total_stops(void)
{
    return  qpg_STA_busTotalStops();
}

int sta_bus_total_stop_time(void)
{
    return  qpg_STA_busTotalStopTime();
}

int sta_bus_get_on(void)
{
    return  qpg_STA_busGetOn();
}

int sta_bus_get_off(void)
{
    return  qpg_STA_busGetOff();
}

float sta_bus_last_speed(void)
{
    return  qpg_STA_busLastSpeed();
}

int sta_bus_last_count(void)
{
    return  qpg_STA_busLastCount();
}

float sta_all_total_delay(void)
{
    return  qpg_STA_allTotalDelay();
}

double sta_all_total_distance(void)
{
    return  qpg_STA_allTotalDistance();
}

int sta_all_total_count(void)
{
    return  qpg_STA_allTotalCount();
}

float sta_all_mean_speed(void)
{
    return  qpg_STA_allMeanSpeed();
}

float sta_all_mean_delay(void)
{
    return  qpg_STA_allMeanDelay();
}

float sta_all_last_speed(void)
{
    return  qpg_STA_allLastSpeed();
}

int sta_all_last_count(void)
{
    return  qpg_STA_allLastCount();
}

float sta_speed(LINK* link,int lane)
{
    return  qpg_STA_speed(link,lane);
}

float sta_flow(LINK* link,int lane) 
{
    return  qpg_STA_flow(link,lane) ;
}

float sta_count(LINK* link,int lane)
{
    return  qpg_STA_count(link,lane);
}

float sta_density(LINK* link,int lane)
{
    return  qpg_STA_density(link,lane);
}

float sta_percent_delay(LINK* link,int lane)
{
    return  qpg_STA_percentDelay(link,lane);
}

float sta_delay(LINK* link,int lane)
{
    return  qpg_STA_delay(link,lane);
}

float sta_stopline_q_length(LINK* link,int lane)
{
    return  qpg_STA_stoplineQueueLength(link,lane);
}

int sta_stopline_q_count(LINK* link,int lane)
{
    return  qpg_STA_stoplineQueueCount(link,lane);
}

float sta_stopline_q_pcus(LINK* link,int lane)
{
    return  qpg_STA_stoplineQueuePCUs(link,lane);
}


/* ------- Network ------------------------------------------------------- */

char* net_datapath()
{
    return qpg_NET_datapath();
}

int net_n_nodes(void)
{
    return  qpg_NET_nodes();
}

int net_n_links(void)
{
    return  qpg_NET_links();
}

int net_n_zones(void)
{
    return  qpg_NET_zones();
}

int net_n_vehicle_types(void)
{
    return  qpg_NET_vehicleTypes();
}

int net_n_vehicles_simulating(void)
{
    return  qpg_NET_vehiclesSimulating();
}

int net_n_vehicles_simulated(void)
{
    return  qpg_NET_vehiclesSimulated();
}

int net_n_vehicles_demanded(void)
{
    return  qpg_NET_vehiclesDemanded();
}

float net_speed_up(void)
{
    return  qpg_NET_speedUp();
}

NODE* id_node(int id)
{
    return  qpg_NET_nodeByIndex(id);
}

LINK* id_link(int id)
{
    return  qpg_NET_linkByIndex(id);
}

int node_id(NODE* node)
{
    return  qpg_NDE_index(node);
}

int link_id(LINK* link)
{
    return  qpg_LNK_index(link);
}


/* ------- Nodes --------------------------------------------------------- */

char* node_name(NODE* node )
{
    return qpg_NDE_name(node);
}

NODE* node_ref(char *name)
{
    return  qpg_NET_node(name);
}

int node_n_links(NODE* node)
{
    return  qpg_NDE_links(node);
}

LINK* node_link(NODE* node,int index)
{
    return  qpg_NDE_link(node,index);
}

int node_n_phases(NODE* node)
{
    return  qpg_NDE_phases(node);
}

Bool node_variable(NODE* node)
{
    return  qpg_NDE_variable(node);
}

void node_variable_set(NODE* node,Bool value)
{
    qps_NDE_variable(node,value);
}

Bool node_hold(NODE* node)
{
    return  qpg_NDE_hold(node);
}

void node_hold_set(NODE* node,Bool value)
{
    qps_NDE_hold(node,value);
}

Bool nodes_connected (NODE* node1, NODE* node2)
{
    return  qpg_NDE_connected (node1,node2);
}

Bool node_ghost_island(NODE* node)
{
    return  qpg_NDE_ghostIsland(node);
}

Bool node_roundabout(NODE* node)
{
    return  qpg_NDE_roundabout(node);
}

Bool node_signalised(NODE* node)
{
    return  qpg_NDE_signalised(node);
}

int node_n_entry_links(NODE* node)
{
    return  qpg_NDE_entryLinks(node);
}

int node_n_exit_links(NODE* node)
{
    return  qpg_NDE_exitLinks(node);
}



/* ------- Links --------------------------------------------------------- */

char* link_name(LINK* link )
{
    return qpg_LNK_name(link);
}

LINK* link_ref(char *name)
{
    return  qpg_NET_link(name);
}

int link_n_links(LINK* link)
{
    return  qpg_LNK_links(link);
}

LINK* link_link(LINK* link,int index)
{
    return  qpg_LNK_link(link,index);
}

int link_n_exit_links(LINK* link)
{
    return  qpg_LNK_exitLinks(link);
}

LINK* link_exit(LINK* link,int index)
{
    return  qpg_LNK_exit(link,index);
}

int link_n_entry_links(LINK* link)
{
    return  qpg_LNK_entryLinks(link);
}

LINK* link_entry(LINK* link,int index)
{
    return  qpg_LNK_entry(link,index);
}

float link_length(LINK* link)
{
    return  qpg_LNK_length(link);
}

float link_gradient(LINK* link)
{
    return  qpg_LNK_gradient(link);
}

int link_n_lanes(LINK* link)
{
    return  qpg_LNK_lanes(link);
}

Bool link_urban(LINK* link)
{
    return  qpg_LNK_urban(link);
}

float link_speedlimit(LINK* link)
{
    return  qpg_LNK_speedlimit(link);
}

void link_speedlimit_set(LINK* link,float value)
{
    qps_LNK_speedlimit(link,value);
}

float link_to_hazard(LINK* link, VEHICLE* vehicle)
{
    return  qpg_LNK_toHazard(link,vehicle);
}

float link_signposting(LINK* link)
{
    return  qpg_LNK_signposting(link);
}

int link_hazard(LINK* link)
{
    return qpg_LNK_hazard(link );
}

void link_priority_set(LINK* link1, LINK* link2,int pri)
{
    qps_LNK_priority(link1,link2,pri);
}

Bool link_signals_ahead(LINK* link, VEHICLE* vehicle)
{
    return  qpg_LNK_signalsAhead(link,vehicle);
}

Bool link_signals_nearside(LINK* link, VEHICLE* vehicle)
{
    return  qpg_LNK_signalsNearside(link,vehicle);
}

int link_n_detectors(LINK* link)
{
    return  qpg_LNK_detectors(link);
}

int link_detector(LINK* link,int index)
{
    return  qpg_LNK_detectorIndexByIndex(link,index);
}

float link_detector_dist(LINK* link,int index)
{
    return  qpg_LNK_detectorPositionByIndex(link, index);
}

int link_n_beacons(LINK* link)
{
    return  qpg_LNK_beacons(link);
}

int link_beacon(LINK* link,int index)
{
    return  qpg_LNK_beaconIndexByIndex(link,index);
}

int link_zone(LINK* link)
{
    return  qpg_LNK_zone(link);
}

Bool link_zone_connector(LINK* link)
{
    return  qpg_LNK_zoneConnector(link);
}

Bool link_stay_in_lane(LINK* link)
{
    return  qpg_LNK_stayInLane(link);
}

float link_headway_mod(LINK* link)
{
    return  qpg_LNK_headwayMod(link);
}

int link_turncount(LINK* link,int exit)
{
    return  qpg_LNK_turncount(link,exit);
}

void link_turncount_clear(LINK* link,int exit)
{
    qps_LNK_turncountClear(link,exit);
}

Bool link_special(LINK* link)
{
    return  qpg_LNK_special(link);
}

void link_special_set(LINK* link,Bool value)
{
    qps_LNK_special(link,value);
}

int link_cost(LINK* link,int table)
{
    return  qpg_LNK_cost(link,table);
}

int link_exit_cost(LINK* link1, LINK* link2,int table)
{
    return  qpg_LNK_exitCost(link1,link2,table);
}

int link_destination_cost(LINK* link,int destination,int table)
{
    return  qpg_LNK_destinationCost(link,destination,table);
}

void link_destination_cost_set(LINK* link,int destination,int table,int cost)
{
    qps_LNK_destinationCost(link,destination,table,cost);
}

void link_destination_cost_vector_set(LINK* link,int table,int nzones,int *zone,int *icost)
{
    qps_LNK_destinationCostVector(link,table,nzones,zone,icost);
}

float link_turnspeed(LINK* link,int exit)
{
    return  qpg_LNK_turnspeed(link,exit);
}

void link_turnspeed_set(LINK* link,int exit,float value)
{
    qps_LNK_turnspeed(link,exit,value);
}

NODE* link_node_start (LINK* link)
{
    return  qpg_LNK_nodeStart (link);
}

NODE* link_node_end (LINK* link)
{
    return  qpg_LNK_nodeEnd (link);
}

Bool link_restricted_type(LINK* link,int v_type)
{
    return  qpg_LNK_restrictedType(link,v_type);
}

int link_lane_restriction(LINK* link,int lane)
{
    return  qpg_LNK_laneRestriction(link,lane);
}

float link_width(LINK* link)
{
    return  qpg_LNK_width(link);
}

float link_median_width(LINK* link)
{
    return  qpg_LNK_medianWidth(link);
}

int link_category(LINK* link)
{
    return  qpg_LNK_category(link);
}

float link_angle(LINK* link)
{
    return  qpg_LNK_angle(link);
}

float link_start_angle(LINK* link)
{
    return  qpg_LNK_startAngle(link);
}

float link_end_angle(LINK* link)
{
    return  qpg_LNK_endAngle(link);
}

Bool link_stacking_stopline(LINK* link)
{
    return  qpg_LNK_stackingStopline(link);
}

Bool link_barred(LINK* link)
{
    return  qpg_LNK_barred(link);
}

Bool link_arc(LINK* link)
{
    return  qpg_LNK_arc(link);
}

Bool link_arc_left(LINK* link)
{
    return  qpg_LNK_arcLeft(link);
}

Bool link_to_ramp(LINK* link)
{
    return  qpg_LNK_toRamp(link);
}

Bool link_ratelocked(LINK* link)
{
    return  qpg_LNK_ratelocked(link);
}

Bool link_slip_lane(LINK* link)
{
    return  qpg_LNK_slipLane(link);
}

Bool link_wide_start(LINK* link)
{
    return  qpg_LNK_wideStart(link);
}

Bool link_wide_end(LINK* link)
{
    return  qpg_LNK_wideEnd(link);
}

float link_cost_factor(LINK* link)
{
    return  qpg_LNK_costFactor(link);
}

Bool link_on_roundabout(LINK* link)
{
    return  qpg_LNK_onRoundabout(link);
}

Bool link_force_merge(LINK* link)
{
    return  qpg_LNK_forceMerge(link);
}

Bool link_force_across(LINK* link)
{
    return  qpg_LNK_forceAcross(link);
}

int link_linktype(LINK* link)
{
    return  qpg_LNK_linktype(link);
}

LINK* link_nearside(LINK* link)
{
    return  qpg_LNK_nearside(link);
}

LINK* link_offside(LINK* link)
{
    return  qpg_LNK_offside(link);
}

LINK* link_backside(LINK* link)
{
    return  qpg_LNK_backside(link);
}

LINK* link_match(LINK* link)
{
    return  qpg_LNK_match(link);
}

float link_endspeed(LINK* link)
{
    return  qpg_LNK_endspeed(link);
}

Bool link_tolls(LINK* link)
{
    return  qpg_LNK_tolls(link);
}



/* ------- Demands ------------------------------------------------------- */

Bool dmd_periods(void)
{
    return  qpg_DMD_isPeriodic();
}

int dmd_profile_count(void)
{
    return  qpg_DMD_profiles();
}

int dmd_period_count(void)
{
    return  qpg_DMD_periods();
}

int dmd_current_period(void)
{
    return  qpg_DMD_currentPeriod();
}

int dmd_matrix_count(void)
{
    return  qpg_DMD_matrixCount();
}


/* ------- Zones --------------------------------------------------------- */

int zone_index(ZONE* zone)
{
    return  qpg_ZNE_index(zone);
}

ZONE* index_zone(int index)
{
    return  qpg_NET_zone(index);
}

int zone_external_index(int index)
{
    return  qpg_ZNE_externalIndex(index);
}

int zone_n_unreleased(ZONE* zone)
{
    return  qpg_ZNE_unreleased(zone);
}

int zone_n_links(ZONE* zone)
{
    return  qpg_ZNE_links(zone);
}

LINK* zone_link(ZONE* zone,int index)
{
    return  qpg_ZNE_link(zone,index);
}

int zone_n_released(ZONE* zone)
{
    return  qpg_ZNE_released(zone);
}

int zone_n_carparks(ZONE* zone)
{
    return  qpg_ZNE_carparks(zone);
}

int zone_type(ZONE* zone)
{
    return  qpg_ZNE_type(zone);
}

int zone_target_demand(int orig,int dest,int matrix)
{
    return  qpg_ZNE_targetDemand(orig,dest,matrix);
}

void zone_vehicle_recall_set(Bool value)
{
    qps_ZNE_vehicleRecall(value);
}

void zone_vehicle_type_set(int value)
{
    qps_ZNE_vehicleType(value);
}

void zone_vehicle_destination_set(int value)
{
    qps_ZNE_vehicleDestination(value);
}

void zone_vehicle_profile_set(int value)
{
    qps_ZNE_vehicleProfile(value);
}

void zone_vehicle_awareness_set(int value)
{
    qps_ZNE_vehicleAwareness(value);
}

void zone_vehicle_aggression_set(int value)
{
    qps_ZNE_vehicleAggression(value);
}

void zone_vehicle_familiarity_set(Bool value)
{
    qps_ZNE_vehicleFamiliarity(value);
}

void zone_vehicle_lane_set(int value)
{
    qps_ZNE_vehicleLane(value);
}

void zone_vehicle_speed_set(float value)
{
    qps_ZNE_vehicleSpeed(value);
}

void zone_vehicle_distance_set(float value)
{
    qps_ZNE_vehicleDistance(value);
}


/* ------- Car Parks ---------------------------------------------------- */



/* ------- Vehicles ------------------------------------------------------ */

LINK* vehicle_link(VEHICLE* vehicle)
{
    return  qpg_VHC_link(vehicle);
}

int vehicle_lane(VEHICLE* vehicle)
{
    return  qpg_VHC_lane(vehicle);
}

float vehicle_distance(VEHICLE* vehicle)
{
    return  qpg_VHC_distance(vehicle);
}

void vehicle_distance_set(VEHICLE* vehicle,float value)
{
    qps_VHC_distance(vehicle,value);
}

float vehicle_speed(VEHICLE* vehicle)
{
    return  qpg_VHC_speed(vehicle);
}

void vehicle_speed_set(VEHICLE* vehicle,float value)
{
    qps_VHC_speed(vehicle,value);
}

float vehicle_speed_historic(VEHICLE* vehicle,float time)
{
    return  qpg_VHC_speedHistoric(vehicle,time);
}

float vehicle_acc(LINK* link, VEHICLE* vehicle)
{
    return  qpg_VHC_linkAcceleration(link,vehicle);
}

float vehicle_dec(LINK* link, VEHICLE* vehicle)
{
    return  qpg_VHC_linkDeceleration(link,vehicle);
}

Bool vehicle_accelerating(VEHICLE* vehicle)
{
    return  qpg_VHC_accelerating(vehicle);
}

void vehicle_accelerating_set(VEHICLE* vehicle,Bool value)
{
    qps_VHC_accelerating(vehicle,value);
}

Bool vehicle_braking(VEHICLE* vehicle)
{
    return  qpg_VHC_braking(vehicle);
}

void vehicle_braking_set(VEHICLE* vehicle,Bool value)
{
    qps_VHC_braking(vehicle,value);
}

int vehicle_aggression(VEHICLE* vehicle)
{
    return  qpg_VHC_aggression(vehicle);
}

void vehicle_aggression_set(VEHICLE* vehicle,int value)
{
    qps_VHC_aggression(vehicle,value);
}

int vehicle_awareness(VEHICLE* vehicle)
{
    return  qpg_VHC_awareness(vehicle);
}

void vehicle_awareness_set(VEHICLE* vehicle,int value)
{
    qps_VHC_awareness(vehicle,value);
}

int vehicle_type(VEHICLE* vehicle)
{
    return  qpg_VHC_type(vehicle);
}

VEHICLE* vehicle_ahead(VEHICLE* vehicle)
{
    return  qpg_VHC_ahead(vehicle);
}

VEHICLE* vehicle_behind(VEHICLE* vehicle)
{
    return  qpg_VHC_behind(vehicle);
}

VEHICLE* vehicle_original(VEHICLE* vehicle)
{
    return  qpg_VHC_original(vehicle);
}

int vehicle_tracer(VEHICLE* vehicle)
{
    return  qpg_VHC_tracer(vehicle);
}

void vehicle_report(VEHICLE* vehicle,char *format,...)
{
    va_list arg;
    va_start (arg,format);
    
    VSNPRINTF(str,VSTRLEN,format,arg);
    qps_VHC_report(vehicle,str);

    va_end (arg);
}

void vehicle_tracer_set(VEHICLE* vehicle,int index,float value)
{
    qps_VHC_tracer(vehicle,index,value);
}


Bool vehicle_special(VEHICLE* vehicle,int index)
{
    return  qpg_VHC_special(vehicle,index);
}

void vehicle_special_set(VEHICLE* vehicle,int index,Bool value)
{
    qps_VHC_special(vehicle,index,value);
}

Bool vehicle_usertag(VEHICLE* vehicle)
{
    return  qpg_VHC_usertag(vehicle);
}

void vehicle_usertag_set(VEHICLE* vehicle,Bool value)
{
    qps_VHC_usertag(vehicle,value);
}

float vehicle_length (VEHICLE* vehicle)
{
    return  qpg_VHC_length (vehicle);
}

float vehicle_width (VEHICLE* vehicle)
{
    return  qpg_VHC_width (vehicle);
}

float vehicle_height (VEHICLE* vehicle)
{
    return  qpg_VHC_height (vehicle);
}

float vehicle_weight (VEHICLE* vehicle)
{
    return  qpg_VHC_weight (vehicle);
}

float vehicle_accel (VEHICLE* vehicle)
{
    return  qpg_VHC_acceleration (vehicle);
}

float vehicle_decel (VEHICLE* vehicle)
{
    return  qpg_VHC_deceleration(vehicle);
}

float vehicle_demand (VEHICLE* vehicle)
{
    return  qpg_VHC_demand (vehicle);
}

float vehicle_familiar (VEHICLE* vehicle)
{
    return  qpg_VHC_familiar (vehicle);
}

float vehicle_perturbation (VEHICLE* vehicle)
{
    return  qpg_VHC_perturbation (vehicle);
}

float vehicle_pcus (VEHICLE* vehicle)
{
    return  qpg_VHC_pcus (vehicle);
}

int vehicle_matrix (VEHICLE* vehicle)
{
    return  qpg_VHC_matrix (vehicle);
}

int vehicle_origin(VEHICLE* vehicle)
{
    return  qpg_VHC_origin(vehicle);
}

int vehicle_origin_trip(VEHICLE* vehicle)
{
    return  qpg_VHC_originTrip(vehicle);
}

int vehicle_destination(VEHICLE* vehicle)
{
    return  qpg_VHC_destination(vehicle);
}

int vehicle_destination_trip(VEHICLE* vehicle)
{
    return  qpg_VHC_destinationTrip(vehicle);
}

int vehicle_lane_low(VEHICLE* vehicle)
{
    return  qpg_VHC_laneLow(vehicle);
}

int vehicle_lane_high(VEHICLE* vehicle)
{
    return  qpg_VHC_laneHigh(vehicle);
}

int vehicle_next_lane(VEHICLE* vehicle)
{
    return  qpg_VHC_nextLane(vehicle);
}

int vehicle_next_exit(VEHICLE* vehicle)
{
    return  qpg_VHC_nextExit(vehicle);
}

int vehicle_age(VEHICLE* vehicle)
{
    return  qpg_VHC_age(vehicle);
}

int vehicle_start_time(VEHICLE* vehicle)
{
    return  qpg_VHC_startTime(vehicle);
}

int vehicle_exist_time(VEHICLE* vehicle)
{
    return  qpg_VHC_existTime(vehicle);
}

int vehicle_route_table(VEHICLE* vehicle)
{
    return  qpg_VHC_routeTable(vehicle);
}

Bool vehicle_let_in(VEHICLE* vehicle)
{
    return  qpg_VHC_letIn(vehicle);
}

Bool vehicle_on_node(VEHICLE* vehicle)
{
    return  qpg_VHC_onNode(vehicle);
}

Bool vehicle_not_major(LINK* link, VEHICLE* vehicle)
{
    return  qpg_VHC_notMajor(link,vehicle);
}

Bool vehicle_moving_in(VEHICLE* vehicle)
{
    return  qpg_VHC_movingIn(vehicle);
}

Bool vehicle_stopped(VEHICLE* vehicle)
{
    return  qpg_VHC_stopped(vehicle);
}

Bool vehicle_incident(VEHICLE* vehicle)
{
    return  qpg_VHC_incident(vehicle);
}

void vehicle_recycle_set(Bool val)
{
    qps_VHC_recycle(val);
}

Bool vehicle_bus_at_stop(VEHICLE* vehicle)
{
    return  qpg_BUS_atStop(vehicle);
}

Bool vehicle_bus_avoid(VEHICLE* vehicle,float to_hazard)
{
    return  qpg_VHC_busAvoid(vehicle,to_hazard);
}

Bool vehicle_is_heavy(VEHICLE* vehicle)
{
    return  qpg_VHC_isHeavy(vehicle);
}

Bool vehicle_is_bus(VEHICLE* vehicle)
{
    return  qpg_VHC_isBus(vehicle);
}

float type_length (int t)
{
    return  qpg_VTP_length (t);
}

float type_width (int t)
{
    return  qpg_VTP_width (t);
}

float type_height (int t)
{
    return  qpg_VTP_height (t);
}

float type_weight (int t)
{
    return  qpg_VTP_weight (t);
}

float type_acceleration (int t)
{
    return  qpg_VTP_acceleration (t);
}

float type_deceleration (int t)
{
    return  qpg_VTP_deceleration (t);
}

float type_demand (int t)
{
    return  qpg_VTP_demand (t);
}

float type_familiar (int t)
{
    return  qpg_VTP_familiar (t);
}

float type_perturbation (int t)
{
    return  qpg_VTP_perturbation (t);
}

float type_pcus (int t)
{
    return  qpg_VTP_pcus (t);
}

int type_matrix (int t)
{
    return  qpg_VTP_matrix (t);
}

Bool type_restricted(int t,int restriction)
{
    return  qpg_VTP_restricted(t,restriction);
}



/* -------- Detectors ---------------------------------------------------- */

int n_detectors(void)
{
    return  qpg_NET_detectors();
}

Bool is_detector_loop (int detector)
{
    return  qpg_DTI_isLoop(detector);
}

char* detector_id(int detector )
{
    return qpg_DTI_name(detector);
}

int loop_n_lanes(int detector)
{
    return  qpg_DTI_lanes(detector);
}

float loop_flow(int detector,int lane,int type)
{
    return  qpg_DTI_flow(detector,lane,type);
}

float loop_speed(int detector,int lane,int type)
{
    return  qpg_DTI_speed(detector,lane,type);
}

float loop_gap(int detector,int lane,int type)
{
    return  qpg_DTI_gap(detector,lane,type);
}

float loop_occupancy(int detector,int lane,int type)
{
    return  qpg_DTI_occupancy(detector,lane,type);
}

int loop_count(int detector,int lane,int vehicleType)
{
    return  qpg_DTI_count(detector,lane,vehicleType);
}

Bool loop_faulty (int detector,int lane)
{
    return  qpg_DTI_faulty (detector,lane);
}

Bool loop_suspect (int detector,int lane)
{
    return  qpg_DTI_suspect (detector,lane);
}

void loop_set(int detector,int lane,int parameter,float value)
{
    qps_DTI_state(detector,lane,parameter,value);
}


/* -------- ITS ---------------------------------------------------------- */

int n_beacons(void)
{
    return  qpg_NET_beacons();
}

char* beacon_ident(int beacon )
{
    return qpg_BCI_name(beacon);
}

LINK* beacon_link(int beacon)
{
    return  qpg_BCI_link(beacon);
}

char* vms_message(int beacon )
{
    return qpg_BCI_message(beacon);
}

float vms_dist(int beacon)
{
    return  qpg_BCI_distance(beacon);
}

void vms_message_set(int beacon,char *format,...)
{
    va_list arg;
    va_start (arg,format);
    
    VSNPRINTF(str,VSTRLEN,format,arg);
    qps_BCI_message(beacon,str);

    va_end (arg);
}

void vms_colour_set(int beacon,int colour)
{
    qps_BCI_colour(beacon,colour);
}

float vms_visibility(int beacon)
{
    return  qpg_BCI_visibility(beacon);
}

void vms_visibility_set(int beacon,float value)
{
    qps_BCI_visibility(beacon,value);
}

int vms_colour(int beacon)
{
    return  qpg_BCI_colour(beacon);
}

void vms_colour_clear(int beacon)
{
    qps_BCI_colourClear(beacon);
}

void vms_toggel_bins_graph(int beacon,Bool state)
{
    qps_BCI_binsGraph(beacon,state);
}

void vms_set_bins_format(int beacon,Bool state)
{
    qps_BCI_binsFormat(beacon,state);
}

void vms_set_bin_value(int beacon,int index,float value)
{
    qps_BCI_binValue(beacon,index,value);
}

float vms_get_bin_value(int beacon,int index)
{
    return  qpg_BCI_binValue(beacon,index);
}

void vms_set_bin_colour(int beacon,int index,int colour)
{
    qps_BCI_binColour(beacon,index,colour);
}

int vms_get_bin_colour(int beacon,int index)
{
    return  qpg_BCI_binColour(beacon,index);
}

void vms_set_max_bin_value(int beacon,float value)
{
    qps_BCI_maxBinValue(beacon,value);
}

float vms_get_max_bin_value(int beacon)
{
    return qpg_BCI_maxBinValue(beacon);
}

char *vms_get_graph_name(int beacon)
{
    return qpg_BCI_graphName(beacon);
}

void vms_set_graph_name(int beacon,char *format,...)
{
    va_list arg;
    va_start (arg,format);
    
    VSNPRINTF(str,VSTRLEN,format,arg);
    qps_BCI_graphName(beacon,str);

    va_end (arg);
}



/* -------- Units -------------------------------------------------------- */

char* external_distance_unit_label(void)
{
    return qpg_UTL_distanceUnitLabel();
}

char* external_speed_unit_label(void)
{
    return qpg_UTL_speedUnitLabel();
}

char* external_acceleration_unit_label(void)
{
    return qpg_UTL_accelerationUnitLabel();
}

char* external_density_unit_label(void)
{
    return qpg_UTL_densityUnitLabel();
}

char* external_event_density_unit_label(void)
{
    return qpg_UTL_eventDensityUnitLabel();
}

char* external_weight_unit_label(void)
{
    return qpg_UTL_weightUnitLabel();
}


float from_internal_distance_unit(void)
{
    return  qpg_UTL_toExternalDistance();
}

float from_internal_speed_unit(void)
{
    return  qpg_UTL_toExternalSpeed();
}

float from_internal_acceleration_unit(void)
{
    return  qpg_UTL_toExternalAcceleration();
}

float from_internal_density_unit(void)
{
    return  qpg_UTL_toExternalDensity();
}

float from_internal_weight_unit(void)
{
    return  qpg_UTL_toExternalWeight();
}


float to_internal_distance_unit(void)
{
    return  qpg_UTL_toInternalDistance();
}

float to_internal_speed_unit(void)
{
    return  qpg_UTL_toInternalSpeed();
}

float to_internal_acceleration_unit(void)
{
    return  qpg_UTL_toInternalAcceleration();
}

float to_internal_density_unit(void)
{
    return  qpg_UTL_toInternalDensity();
}

float to_internal_weight_unit(void)
{
    return  qpg_UTL_toInternalWeight();
}


/* ------------------- utility functions -------------------------------- */

double utl_d_random(int stream,double range)
{
    return  qpg_UTL_randomDouble(stream,range);
}

float utl_f_random(int stream,float range)
{
    return  qpg_UTL_randomFloat(stream,range);
}

int utl_i_random(int stream,int range)
{
    return  qpg_UTL_randomInteger(stream,range);
}

Bool utl_tf_random(int stream,int ctrue)
{
    return  qpg_UTL_randomBoolean(stream,ctrue);
}

int utl_i_normal_random(int stream,int mean,int std_dev)
{
    return  qpg_UTL_randomNormalInteger(stream,mean,std_dev);
}

int utl_i_poisson_random(int stream,float mean)
{
    return  qpg_UTL_randomPoissonInteger(stream,mean);
}

float utl_linear_spread(int p1,int p2,float value,float delta)
{
    return  qpg_UTL_linearSpread(p1,p2,value,delta);
}

float utl_skew_spread(int p1,int p2,float value,float delta,float skew)
{
    return  qpg_UTL_skewSpread(p1,p2,value,delta,skew);
}

float linear_spread(int p1,int p2,float value,float delta)
{
    return  qpg_UTL_linearSpread(p1,p2,value,delta);
}

float skew_spread(int p1,int p2,float value,float delta,float skew)
{
    return  qpg_UTL_skewSpread(p1,p2,value,delta,skew);
}


long utl_start_timer(void)
{
    return  qpg_UTL_startTimer();
}

int utl_lap_timer(long ref,char scale)
{
    return  qpg_UTL_lapTimer(ref,scale);
}

void utl_reset_timer(long ref)
{
    qps_UTL_resetTimer(ref);
}

int utl_read_timer(long ref,char scale)
{
    return  qpg_UTL_readTimer(ref,scale);
}

void utl_int2HMS(int t,int *dy,int *hr,int *mn,int *sc)
{
    qpg_UTL_integerToTime(t,dy,hr,mn,sc);
}

char* utl_int2HMSstr(int t )
{
    return qpg_UTL_integerToTimeString(t);
}

char* utl_int2HMSstrF(int t )
{
    return qpg_UTL_integerToTimeFileName(t);
}

void int2HMS(int t,int *dy,int *hr,int *mn,int *sc)
{
    qpg_UTL_integerToTime(t,dy,hr,mn,sc);
}

char* int2HMSstr(int t )
{
    return qpg_UTL_integerToTimeString(t);
}

char* int2HMSstrF(int t )
{
    return qpg_UTL_integerToTimeFileName(t);
}

void file_time_separator_set(char c)
{
    qps_UTL_fileTimeSeparator(c);
}

void utl_file_time_separator_set(char c)
{
    qps_UTL_fileTimeSeparator(c);
}

Bool utl_makedir(char *path)
{
    return  qpg_UTL_makeDirectory(path);
}

Bool utl_file_exists(char *path)
{
    return  qpg_UTL_fileExists(path);
}

Bool utl_dir_exists(char *path)
{
    return qpg_UTL_directoryExists(path);
}

int utl_lines_in_file(char *path)
{
    return qpg_UTL_linesInFile(path);
}

char *utl_paramics_home(void)
{
    return  qpg_UTL_paramicsHome();
}

char *utl_paramics_data_home(void)
{
    return qpg_UTL_paramicsDataHome();
}

char *utl_net_datapath(void)
{
    return qpg_NET_dataPath();
}

char* utl_net_statpath(void)
{
    return qpg_NET_statsPath();
}

//FILE *utl_pf_open(char *md,char *path)
//{
//    return qpg_UTL_fileOpen(md,path);
//}

//Bool utl_pf_close(FILE *fp)
//{
//    return  qpg_UTL_fileClose(fp);
//}

int utl_num_open_files(void)
{
    return qpg_UTL_openFiles();
}

char *utl_append_extension(char *filename,char *extension)
{
    return qpg_UTL_appendExtension(filename,extension);
}

Bool utl_permission_check(void)
{
    return  qpg_UTL_permissionCheck();
}

char* net_get_statpath(void)
{
    return qpg_NET_statsPath();
}

char* net_get_datapath(void)
{
    return qpg_NET_dataPath();
}


#ifdef API_GRAFIX

/* ---------------------- Graphics --------------------------------------- */

// not in v6 

void drw_hollow_circle(float x,float y,float r)
{
    qps_DRW_hollowCircleXY(x,y,r);
}

void drw_hollow_circle_z(float x,float y,float z,float r)
{
    qps_DRW_hollowCircle(x,y,z,r);
}

void drw_filled_circle_(float x,float y,float r)
{
    qps_DRW_filledCircleXY(x,y,r);
}

void drw_filled_circle_z(float x,float y,float z,float r)
{
    qps_DRW_filledCircle(x,y,z,r);
}

void drw_hollow_rectangle(float bl_x,float bl_y,float tr_x,float tr_y)
{
    qps_DRW_hollowRectangleXY(bl_x,bl_y,tr_x,tr_y);
}

void drw_filled_rectangle(float bl_x,float bl_y,float tr_x,float tr_y)
{
    qps_DRW_filledRectangleXY(bl_x,bl_y,tr_x,tr_y);
}

void drw_hollow_rectangle_z(float bl_x,float bl_y,float bl_z,float tr_x,float tr_y,float tr_z)
{
    qps_DRW_hollowRectangle(bl_x,bl_y,bl_z,tr_x,tr_y,tr_z);
}

void drw_filled_rectangle_z(float bl_x,float bl_y,float bl_z,float tr_x,float tr_y,float tr_z)
{
    qps_DRW_filledRectangle(bl_x,bl_y,bl_z,tr_x,tr_y,tr_z);
}

void drw_string(char *s,float x,float y,float h)
{
    qps_DRW_stringXY(s,x,y,h);
}

void drw_string_z(char *s,float x,float y,float z,float h)
{
    qps_DRW_string(s,x,y,z,h);
}

void drw_string_facncy(char *s,float x,float y,float rot,int n)
{
    qps_DRW_stringRotatedXY(s,x,y,rot,n);
}

void drw_string_facncy_z(char *s,float x,float y,float z,float rot,int n)
{
    qps_DRW_stringRotated(s,x,y,z,rot,n);
}

void drw_arrow_z(float x,float y,float z,float bearing,float gradient,float size,int pos)
{
    qps_DRW_arrow(x,y,z,bearing,gradient,size,pos);
}

void drw_colourkey(char *min,char *max,char *title,float needle,int yshift)
{
    qps_DRW_colourkey(min,max,title,needle,yshift);
}

int drw_colour_scale(float value)
{
    return qpg_DRW_colourScale(value);
}

void drw_banded_table(int count,char *labels[],int colours[],int fill[],int edge[], int yshift)
{
    qps_DRW_bandedTable(count,labels,colours,fill,edge,yshift);
}

void drw_event_table(int count,char *labels[],int colours[],int tri1[],int tri2[], int yshift)
{
    qps_DRW_eventTable(count,labels,colours,tri1,tri2,yshift);
}


void drw_move_to_vehicle_home(VEHICLE* vehicle)
{
    qps_DRW_moveToVehicleHome(vehicle);
}

void drw_move_to_zone_home(ZONE* zone)
{
    qps_DRW_moveToZoneHome(zone);
}

void drw_move_to_node_home(NODE* node)
{
    qps_DRW_moveToNodeHome(node);
}

void drw_move_to_kerb_home(LINK* link,int kerb)
{
    qps_DRW_moveToKerbHome(link,kerb);
}

void drw_move_to_stopline_home(LINK* link,int lane,int stopline)
{
    qps_DRW_moveToStoplineHome(link,lane,stopline);
}

void drw_move_to_detector_home(int detector)
{
    qps_DRW_moveToDetectorHomeByIndex(detector);
}

void drw_move_to_beacon_home(int beacon)
{
    qps_DRW_moveToBeaconHomeByIndex(beacon);
}


void drw_store_drawing_matrix(void)
{
    qps_DRW_storeDrawingMatrix();
}

void drw_load_drawing_matrix(void)
{
    qps_DRW_loadDrawingMatrix();
}

void drw_object_begin(int object)
{
    qps_DRW_objectBegin(object);
}

void drw_object_end(void)
{
    qps_DRW_objectEnd();
}

void drw_colour(int c)
{
    qps_DRW_colour(c);
}

void drw_colour_rgb(float r,float g,float b)
{
    qps_DRW_colourRGB(r,g,b);
}

void drw_vertex(float x,float y)
{
    qps_DRW_vertexXY(x,y);
}

void drw_vertex_z(float x,float y,float z)
{
    qps_DRW_vertex(x,y,z);
}

void drw_set_matrix_mode(int mode)
{
    qps_DRW_matrixMode(mode);
}

void drw_load_identity_matrix(void)
{
    qps_DRW_loadIdentityMatrix();
}

void drw_linewidth(float width)
{
    qps_DRW_linewidth(width);
}

float drw_get_linewidth(void)
{
    return  qpg_DRW_linewidth();
}

void drw_line_style(int style)
{
    qps_DRW_lineStyle(style);
}

float drw_get_default_linewidth(void)
{
    return  qpg_DRW_defaultLinewidth();
}

void drw_translate(float x,float y,float z)
{
    qps_DRW_translate(x,y,z);
}

void drw_scale(float x,float y,float z)
{
    qps_DRW_scale(x,y,z);
}

void drw_rotate(float angle,char axis)
{
    qps_DRW_rotate(angle,axis);
}

void drw_solid(void)
{
    qps_DRW_solid();
}

void drw_transparent(void)
{
    qps_DRW_transparent();
}

Bool drw_3d(void)
{
    return  qpg_DRW_is3D();
}


void draw_link_band(LINK* link,int colour,float proportion,float percent)
{
    qps_DRW_linkBand(link,colour,proportion,percent, (percent < 0.0 ? 1 : 2));
}

void drw_link_band(LINK* link,int colour,float proportion,float percent, int start)
{
    qps_DRW_linkBand(link,colour,proportion,percent,start);
}

void drw_shade_link(LINK* link,int colour)
{
    qps_DRW_shadeLink(link,colour);
}

void drw_shade_link_partial(LINK* link,int colour,float percent, int start)
{
    qps_DRW_shadeLinkPartial(link,colour,percent,start);
}

void drw_highlight_link(LINK* link,int colour)
{
    qps_DRW_highlightLink(link,colour);
}

void drw_lane_closure(LINK* link,int type,int lane)
{
    qps_DRW_laneClosure(link,lane, 0,type);
}

void drw_lane_outline(LINK* link,int lane,int colour)
{
    qps_DRW_laneOutline(link,lane,colour);
}

void drw_shade_lane(LINK* link,int lane,int colour)
{
    qps_DRW_shadeLane(link,lane,colour);
}

void drw_shade_lane_partial(LINK* link,int lane,int colour,float percent, int start)
{
    qps_DRW_shadeLanePartial(link,lane,colour,percent,start);
}


void drw_zone_outline(ZONE* zone,int colour,float height)
{
    qps_DRW_zoneOutline(zone,colour,height);
}

void drw_zone_filled(ZONE* zone,int colour,float height)
{
    qps_DRW_zoneFilled(zone,colour,height);
}


void drw_vehicle_colour(VEHICLE* vehicle,int colour)
{
    qps_DRW_vehicleColour(vehicle,colour);
}

void drw_vehicle_hide(VEHICLE* vehicle)
{
    qps_DRW_vehicleHide(vehicle);
}

void drw_vehicle_ghost(VEHICLE* vehicle)
{
    qps_DRW_vehicleGhost(vehicle);
}

void drw_vehicle_reset(VEHICLE* vehicle)
{
    qps_DRW_vehicleReset(vehicle);
}

void drw_vehicle_tag(VEHICLE* vehicle,int colour,int type,char *format,...)
{
    va_list arg;
    va_start (arg,format);
    
    VSNPRINTF(str,VSTRLEN,format,arg);
    qps_DRW_vehicleTag(vehicle,colour,type, 1.2, str);

    va_end (arg);
}


void drw_set_signal_custom(NODE* node,Bool state)
{
    qps_DRW_signalCustom(node,state);
}

void drw_set_signal_style(NODE* node,int style)
{
    qps_DRW_signalStyle(node,style);
}

void drw_set_signal_colour(NODE* node,int colour,int index)
{
    qps_DRW_signalColour(node,colour,index);
}

int drw_get_signal_colour(NODE* node)
{
    return  qpg_DRW_signalColour(node);
}

void drw_set_signal_face(NODE* node,int colour)
{
    qps_DRW_signalFace(node,colour);
}

void vehicle_dashboard_set(VEHICLE* vehicle,int index,char *format,...)
{
    va_list arg;
    va_start (arg,format);
    
    VSNPRINTF(str,VSTRLEN,format,arg);
    qps_VHC_dashboard(vehicle,index,str);

    va_end (arg);
}
void api_coefficient_set(char *filename,int index,float value)
{
    qps_GUI_value(filename,index,value);
}

void api_toggle_set(char *filename,int index,Bool state)
{
    qps_GUI_toggle(filename,index,state);
}

#endif

/* ----------------------- Positional Data ------------------------------- */

void pos_vehicle(VEHICLE* vehicle, LINK* link,float *x,float *y,float *z,float *bearing,float *gradient)
{
    qpg_POS_vehicle(vehicle,link,x,y,z,bearing,gradient);
}

void pos_zone(ZONE* zone,float *x,float *y,float *z)
{
    qpg_POS_zone(zone,x,y,z);
}

void pos_node(NODE* node,float *x,float *y,float *z)
{
    qpg_POS_node(node,x,y,z);
}

void pos_kerb(LINK* link,int kerb,float *x,float *y,float *z)
{
    qpg_POS_kerb(link,kerb,x,y,z);
}

void pos_stopline(LINK* link,int lane,int stopline,float *x,float *y,float *z,float *bearing,float *gradient)
{
    qpg_POS_stopline(link,lane,stopline,x,y,z,bearing,gradient);
}

void pos_detector(int detector,float *x,float *y,float *z,float *bearing,float *gradient)
{
    qpg_POS_detector(qpg_NET_detectorByIndex(detector),x,y,z,bearing,gradient);
}

void pos_beacon(int beacon,float *x,float *y,float *z,float *bearing,float *gradient)
{
    qpg_POS_beacon(qpg_NET_beaconByIndex(beacon),x,y,z,bearing,gradient);
}

void pos_link(LINK* link,int lane,float dist,float *x,float *y,float *z,float *bearing,float *gradient)
{
    qpg_POS_link(link,lane,dist,x,y,z,bearing,gradient);
}



/* ----------------------- Link vehicle data ----------------------------- */

int link_vehicle_count(LINK* link,int lane)
{
    return  qpg_LNK_vehicles(link,lane);
}

void link_vehicle_data(LINK* link,int lane, VEHICLE* vehicle[],int *count)
{
    /* this has been replaced by qpg_LNK_vehicleList which takes count
       as an input parameter and assumes that an array of size [count]
       has already been allocated for the vehicle pointers */
}

VEHICLE* link_vehicle_tail(LINK* link,int lane)
{
    return qpg_LNK_vehicleTail(link,lane);
}

VEHICLE* link_vehicle_head(LINK* link,int lane)
{
    return qpg_LNK_vehicleHead(link,lane);
}



/* -------- Signals ------------------------------------------------------ */

void signal_action(NODE* node,int phase_index,int balance_index,int action_type,int action_mode,float value)
{
    qps_SIG_action(node,phase_index,balance_index,action_type,action_mode,value);
}

Bool signal_inquiry(NODE* node,int phase_index,int inquiry,float *value)
{
    return qpg_SIG_inquiry(node,phase_index,inquiry,value);
}




/* ------------------ Lex/Yacc wrappers -------------------------------- */

void yacc_close(void *fp)
{
    qps_UTL_yaccClose(fp);
}

Bool yacc_parser(char *path,char *file,FILE **datafilein,FILE **datafileout,int *count,int(*parseFn)(void),int(*wrapFn)(void))
{
    return qpg_UTL_yaccParser(path,file,datafilein,datafileout,count,
                              parseFn,wrapFn);
}


/* ------------------ API interface ------------------------------------- */



void api_printf(char *format,...)
{
    va_list arg;
    va_start (arg,format);
    
    VSNPRINTF(str,VSTRLEN,format,arg);
    qps_GUI_printf(str);

    va_end (arg);
}


/* ------------------ SC Overtaking ------------------------------------- */

float vehicle_act_dist(VEHICLE* vehicle)
{
    return  qpg_CFM_thresholdDistance(vehicle);
}

float link_match_dist(VEHICLE* vehicle, LINK* link)
{
    return  qpg_SCO_matchDistance(vehicle,link);
}

void vehicles_at(LINK* link,int lane,float distance,
                 VEHICLE** infront, VEHICLE** behind)
{
    qpg_LNK_vehiclesAtPosition(link,lane,distance,infront,behind);
}

VEHICLE* get_overtakenV(VEHICLE* vehicle)
{
    return qpg_SCO_overtaken(vehicle);
}

Bool vehicle_overtaking(VEHICLE* vehicle)
{
    return  qpg_SCO_overtaking(vehicle);
}

Bool link_overtaking(LINK* link)
{
    return  qpg_SCO_overtakingLink(link);
}

void link_overtaking_set(LINK* link,Bool state)
{
    qps_SCO_overtakingLink(link,state);
}


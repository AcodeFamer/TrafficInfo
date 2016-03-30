/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 * Quadstone Ltd.             Tel: +44 131 220 4491
 * 16 Chester Street          Fax: +44 131 220 4492
 * Edinburgh, EH3 7RA, UK     WWW: http://www.paramics-online.com
 *
 *
 *
 * This file can be included in the user's file to allow conversion from the
 * old naming scheme to the new
 * ----------------------------------------------------------------------- */ 

#ifndef _API_RENAMING_H_
#define _API_RENAMING_H_

#define follow_acc                              qpo_CFM_followingAcceleration
#define constrained_acc                         qpo_CFM_constrainedAcceleration
#define gradient_acc                            qpo_CFM_gradientAcceleration
#define minimum_gap                             qpo_CFM_minimumGap
#define lookahead_vehicles                      qpo_CFM_lookAheadCount
#define behaviour                               qpo_CFM_behaviour
#define link_maxspeed                           qpo_CFM_linkSpeed
#define curve_speed                             qpo_CFM_curveSpeed
#define ramp_merge_headway                      qpo_CFM_rampMergeHeadway
#define vehicle_headway_factor                  qpo_CFM_headwayFactor
#define safe_distance                           qpo_CFM_safeDistance
#define stopping_distance                       qpo_CFM_stoppingDistance
#define activate_distance                       qpo_CFM_thresholdDistance
#define ramp_headway_resume_distance            qpo_CFM_rampRevertDistance
#define gap_exists                              qpo_LCM_gapExists
#define move_in                                 qpo_LCM_moveIn
#define move_out                                qpo_LCM_moveOut
#define lc_accept_time                          qpo_LCM_passTime
#define lc_overtake_time                        qpo_LCM_overtakeTime
#define lc_reset_time                           qpo_LCM_resetTime
#define lane_usage                              qpo_LCM_laneUsage
#define force_get_in_distance                   qpo_LCM_forceMergeDistance
#define signposting_get_in                      qpo_LCM_signpostMergeDistance
#define signposting_let_in                      qpo_LCM_signpostAllowDistance
#define routing_enable                          qpo_RTM_enable
#define routing_decision                        qpo_RTM_decision
#define routing_next_link                       qpo_RTM_nextLink
#define vehicle_arrival                         qpo_RTM_arrival
#define pull_in                                 qpo_SCO_pullIn
#define pull_out                                qpo_SCO_pullOut
#define match_gap_exists                        qpo_SCO_gapExists

#define vehicle_action                          qpx_VHC_timeStep
#define vehicle_link_action                     qpx_LNK_vehicleTimeStep
#define vehicle_release                         qpx_VHC_release
#define vehicle_arrive                          qpx_VHC_arriveByIndex
#define vehicle_beacon                          qpx_VHC_beaconByIndex
#define vehicle_detector                        qpx_VHC_detectorByIndex
#define vehicle_lanechange                      qpx_VHC_laneChange
#define vehicle_move                            qpx_VHC_move
#define vehicle_target_headway                  qpx_VHC_targetHeadway
#define vehicle_target_speed                    qpx_VHC_targetSpeed
#define vehicle_transfer                        qpx_VHC_transfer
#define vehicle_tagged_arrive                   qpx_TGV_arriveByIndex
#define vehicle_tagged_beacon                   qpx_TGV_beaconByIndex
#define vehicle_tagged_detector                 qpx_TGV_detectorByIndex
#define vehicle_tagged_lanechange               qpx_TGV_laneChange
#define vehicle_tagged_move                     qpx_TGV_move
#define vehicle_tagged_target_headway           qpx_TGV_targetHeadway
#define vehicle_tagged_target_speed             qpx_TGV_targetSpeed
#define vehicle_tagged_transfer                 qpx_TGV_transfer
#define api_coefficient_file                    qpx_CFG_parameterFile
#define api_coefficient_value                   qpx_GUI_parameterValue
#define api_toggle_value                        qpx_GUI_parameterToggle
#define api_pre_netload                         qpx_NET_preOpen
#define api_setup                               qpx_NET_postOpen
#define net_action                              qpx_NET_timeStep
#define net_post_action                         qpx_NET_timeStepPostLink
#define feedback_action                         qpx_NET_feedback
#define end_action                              qpx_NET_close
#define pre_save_action                         qpx_NET_preSave
#define post_save_action                        qpx_NET_postSave
#define refresh_action                          qpx_NET_refresh
#define reload_action                           qpx_NET_reload
#define period_action                           qpx_NET_period
#define every_second_action                     qpx_NET_second
#define every_minute_action                     qpx_NET_minute
#define every_hour_action                       qpx_NET_hour
#define link_action                             qpx_LNK_timeStep
#define zone_action                             qpx_ZNE_timeStep
#define plugin_stats                            qpx_STA_enable
#define plugin_draw_ortho                       qpx_DRW_instrumentView
#define plugin_draw                             qpx_DRW_modelView

/* The following is a list of imports. These do not need to be changed
by "#define", as conversion routines exist in api_oldnames.c

OLD CALLBACK                       NEW CALLBACK

std_follow_acc                     qpg_CFM_followingAcceleration
std_constrained_acc                qpg_CFM_constrainedAcceleration
std_gradient_acc                   qpg_CFM_gradientAcceleration
std_lookahead_vehicles             qpg_CFM_lookAheadCount
std_behaviour                      qpg_CFM_behaviour
std_link_maxspeed                  qpg_CFM_linkSpeed
std_safe_distance                  qpg_CFM_safeDistance
std_stopping_distance              qpg_CFM_stoppingDistance
std_activate_distance              qpg_CFM_thresholdDistance
std_gap_exists                     qpg_LCM_gapExists
std_move_in                        qpg_LCM_moveIn
std_move_out                       qpg_LCM_moveOut
std_lane_usage                     qpg_LCM_laneUsage
mean_headway                       qpg_CFM_meanHeadway
mean_reaction                      qpg_CFM_meanReactionTime
timestep                           qpg_CFG_timeStep
timestep_set                       qps_CFG_timeStep
simulation_time                    qpg_CFG_simulationTime
cfg_speed_memory                   qpg_CFG_speedMemory
cfg_start_time                     qpg_CFG_startTime
cfg_duration                       qpg_CFG_duration
cfg_demand_weight                  qpg_CFG_demandWeight
cfg_timestep_detail                qpg_CFG_timestepDetail
cfg_timestep                       qpg_CFG_timeStep
cfg_seed                           qpg_CFG_seed
cfg_split_seed                     qpg_CFG_splitSeed
cfg_cost_a                         qpg_CFG_costCoefficientA
cfg_cost_b                         qpg_CFG_costCoefficientB
cfg_cost_c                         qpg_CFG_costCoefficientC
cfg_q_speed                        qpg_CFG_queueSpeed
cfg_q_gap                          qpg_CFG_queueGap
cfg_heavy_weight                   qpg_CFG_heavyWeight
cfg_loop_size                      qpg_CFG_loopSize
cfg_feedback_period                qpg_CFG_feedbackPeriod
cfg_perturbation                   qpg_CFG_perturbation
cfg_sqr_root                       qpg_CFG_squareRootEnabled
cfg_feedback_smoothing             qpg_CFG_feedbackSmoothing
cfg_feedback_decay                 qpg_CFG_feedbackDecay
cfg_turning_penalties_visible      qpg_CFG_turningPenaltiesVisible
cfg_amber_time                     qpg_CFG_amberTime
cfg_closest_origin                 qpg_CFG_closestOrigin
cfg_closest_detination             qpg_CFG_closestDetination
cfg_filetime_deliminator           qpg_CFG_filetimeDelimiter
cfg_curve_speed_factor             qpg_CFG_curveSpeedFactor
sta_vehicle_total_delay            qpg_STA_vehicleTotalDelay
sta_vehicle_total_distance         qpg_STA_vehicleTotalDistance
sta_vehicle_total_count            qpg_STA_vehicleTotalCount
sta_vehicle_total_stop_time        qpg_STA_vehicleTotalStopTime
sta_vehicle_mean_speed             qpg_STA_vehicleMeanSpeed
sta_vehicle_mean_delay             qpg_STA_vehicleMeanDelay
sta_vehicle_last_speed             qpg_STA_vehicleLastSpeed
sta_vehicle_last_count             qpg_STA_vehicleLastCount
sta_bus_total_delay                qpg_STA_busTotalDelay
sta_bus_total_distance             qpg_STA_busTotalDistance
sta_bus_total_count                qpg_STA_busTotalCount
sta_bus_mean_speed                 qpg_STA_busMeanSpeed
sta_bus_mean_delay                 qpg_STA_busMeanDelay
sta_bus_total_stops                qpg_STA_busTotalStops
sta_bus_total_stop_time            qpg_STA_busTotalStopTime
sta_bus_get_on                     qpg_STA_busGetOn
sta_bus_get_off                    qpg_STA_busGetOff
sta_bus_last_speed                 qpg_STA_busLastSpeed
sta_bus_last_count                 qpg_STA_busLastCount
sta_all_total_delay                qpg_STA_allTotalDelay
sta_all_total_distance             qpg_STA_allTotalDistance
sta_all_total_count                qpg_STA_allTotalCount
sta_all_mean_speed                 qpg_STA_allMeanSpeed
sta_all_mean_delay                 qpg_STA_allMeanDelay
sta_all_last_speed                 qpg_STA_allLastSpeed
sta_all_last_count                 qpg_STA_allLastCount
sta_speed                          qpg_STA_speed
sta_flow                           qpg_STA_flow
sta_count                          qpg_STA_count
sta_density                        qpg_STA_density
sta_percent_delay                  qpg_STA_percentDelay
sta_delay                          qpg_STA_delay
sta_stopline_q_length              qpg_STA_stoplineQueueLength
sta_stopline_q_count               qpg_STA_stoplineQueueCount
sta_stopline_q_pcus                qpg_STA_stoplineQueuePCUs
net_datapath                       qpg_NET_datapath
net_n_nodes                        qpg_NET_nodes
net_n_links                        qpg_NET_links
net_n_zones                        qpg_NET_zones
net_n_vehicle_types                qpg_NET_vehicleTypes
net_n_vehicles_simulating          qpg_NET_vehiclesSimulating
net_n_vehicles_simulated           qpg_NET_vehiclesSimulated
net_n_vehicles_demanded            qpg_NET_vehiclesDemanded
net_speed_up                       qpg_NET_speedUp
id_node                            qpg_NET_nodeByIndex
id_link                            qpg_NET_linkByIndex
node_id                            qpg_NDE_index
link_id                            qpg_LNK_index
node_name                          qpg_NDE_name
node_ref                           qpg_NET_node
node_n_links                       qpg_NDE_links
node_link                          qpg_NDE_link
node_n_phases                      qpg_NDE_phases
node_variable                      qpg_NDE_variable
node_variable_set                  qps_NDE_variable
node_hold                          qpg_NDE_hold
node_hold_set                      qps_NDE_hold
nodes_connected                    qpg_NDE_connected
node_ghost_island                  qpg_NDE_ghostIsland
node_roundabout                    qpg_NDE_roundabout
node_signalised                    qpg_NDE_signalised
node_n_entry_links                 qpg_NDE_entryLinks
node_n_exit_links                  qpg_NDE_exitLinks
link_name                          qpg_LNK_name
link_ref                           qpg_NET_link
link_n_links                       qpg_LNK_links
link_link                          qpg_LNK_link
link_n_exit_links                  qpg_LNK_exitLinks
link_exit                          qpg_LNK_exit
link_n_entry_links                 qpg_LNK_entryLinks
link_entry                         qpg_LNK_entry
link_length                        qpg_LNK_length
link_gradient                      qpg_LNK_gradient
link_n_lanes                       qpg_LNK_lanes
link_urban                         qpg_LNK_urban
link_speedlimit                    qpg_LNK_speedlimit
link_speedlimit_set                qps_LNK_speedlimit
link_to_hazard                     qpg_LNK_toHazard
link_signposting                   qpg_LNK_signposting
link_hazard                        qpg_LNK_hazard
link_priority_set                  qps_LNK_priority
link_signals_ahead                 qpg_LNK_signalsAhead
link_signals_nearside              qpg_LNK_signalsNearside
link_n_detectors                   qpg_LNK_detectors
link_detector                      qpg_LNK_detectorIndexByIndex
link_detector_dist                 qpg_LNK_detectorDistance
link_n_beacons                     qpg_LNK_beacons
link_beacon                        qpg_LNK_beaconIndexByIndex
link_zone                          qpg_LNK_zone
link_zone_connector                qpg_LNK_zoneConnector
link_stay_in_lane                  qpg_LNK_stayInLane
link_headway_mod                   qpg_LNK_headwayMod
link_turncount                     qpg_LNK_turncount
link_turncount_clear               qps_LNK_turncount
link_special                       qpg_LNK_special
link_special_set                   qps_LNK_special
link_cost                          qpg_LNK_cost
link_exit_cost                     qpg_LNK_exitCost
link_destination_cost              qpg_LNK_destinationCost
link_destination_cost_set          qps_LNK_destinationCost
link_destination_cost_vector_set   qps_LNK_destinationCostVector
link_turnspeed                     qpg_LNK_turnspeed
link_turnspeed_set                 qps_LNK_turnspeed
link_node_start                    qpg_LNK_nodeStart
link_node_end                      qpg_LNK_nodeEnd
link_restricted_type               qpg_LNK_restrictedType
link_lane_restriction              qpg_LNK_laneRestriction
link_width                         qpg_LNK_width
link_median_width                  qpg_LNK_medianWidth
link_category                      qpg_LNK_category
link_angle                         qpg_LNK_angle
link_start_angle                   qpg_LNK_startAngle
link_end_angle                     qpg_LNK_endAngle
link_stacking_stopline             qpg_LNK_stackingStopline
link_barred                        qpg_LNK_barred
link_arc                           qpg_LNK_arc
link_arc_left                      qpg_LNK_arcLeft
link_to_ramp                       qpg_LNK_toRamp
link_ratelocked                    qpg_LNK_ratelocked
link_slip_lane                     qpg_LNK_slipLane
link_wide_start                    qpg_LNK_wideStart
link_wide_end                      qpg_LNK_wideEnd
link_cost_factor                   qpg_LNK_costFactor
link_on_roundabout                 qpg_LNK_onRoundabout
link_force_merge                   qpg_LNK_forceMerge
link_force_across                  qpg_LNK_forceAcross
link_linktype                      qpg_LNK_linktype
link_nearside                      qpg_LNK_nearside
link_offside                       qpg_LNK_offside
link_backside                      qpg_LNK_backside
link_match                         qpg_LNK_match
link_endspeed                      qpg_LNK_endspeed
link_tolls                         qpg_LNK_tolls
dmd_periods                        qpg_DMD_isPeriodic
dmd_profile_count                  qpg_DMD_profiles
dmd_period_count                   qpg_DMD_periods
dmd_current_period                 qpg_DMD_currentPeriod
dmd_matrix_count                   qpg_DMD_matrixCount
zone_index                         qpg_ZNE_index
index_zone                         qpg_NET_zone
zone_external_index                qpg_ZNE_externalIndex
zone_n_unreleased                  qpg_ZNE_unreleased
zone_n_links                       qpg_ZNE_links
zone_link                          qpg_ZNE_link
zone_n_released                    qpg_ZNE_released
zone_n_carparks                    qpg_ZNE_carparks
zone_type                          qpg_ZNE_type
zone_target_demand                 qpg_ZNE_targetDemand
zone_vehicle_recall_set            qps_ZNE_vehicleRecall
zone_vehicle_type_set              qps_ZNE_vehicleType
zone_vehicle_destination_set       qps_ZNE_vehicleDestination
zone_vehicle_profile_set           qps_ZNE_vehicleProfile
zone_vehicle_awareness_set         qps_ZNE_vehicleAwareness
zone_vehicle_aggression_set        qps_ZNE_vehicleAggression
zone_vehicle_familiarity_set       qps_ZNE_vehicleFamiliarity
zone_vehicle_lane_set              qps_ZNE_vehicleLane
zone_vehicle_speed_set             qps_ZNE_vehicleSpeed
zone_vehicle_distance_set          qps_ZNE_vehicleDistance
vehicle_link                       qpg_VHC_link
vehicle_lane                       qpg_VHC_lane
vehicle_distance                   qpg_VHC_distance
vehicle_distance_set               qps_VHC_distance
vehicle_speed                      qpg_VHC_speed
vehicle_speed_set                  qps_VHC_speed
vehicle_speed_historic             qpg_VHC_speedHistoric
vehicle_acc                        qpg_VHC_acceleration
vehicle_dec                        qpg_VHC_deceleration
vehicle_accelerating               qpg_VHC_accelerating
vehicle_accelerating_set           qps_VHC_accelerating
vehicle_braking                    qpg_VHC_braking
vehicle_braking_set                qps_VHC_braking
vehicle_aggression                 qpg_VHC_aggression
vehicle_aggression_set             qps_VHC_aggression
vehicle_awareness                  qpg_VHC_awareness
vehicle_awareness_set              qps_VHC_awareness
vehicle_type                       qpg_VHC_type
vehicle_ahead                      qpg_VHC_ahead
vehicle_behind                     qpg_VHC_behind
vehicle_original                   qpg_VHC_original
vehicle_tracer                     qpg_VHC_tracer
vehicle_report                     qps_VHC_report
vehicle_tracer_set                 qps_VHC_tracer
vehicle_dashboard_set              qps_VHC_dashboard
vehicle_special                    qpg_VHC_special
vehicle_special_set                qps_VHC_special
vehicle_usertag                    qpg_VHC_usertag
vehicle_usertag_set                qps_VHC_usertag
vehicle_length                     qpg_VHC_length
vehicle_width                      qpg_VHC_width
vehicle_height                     qpg_VHC_height
vehicle_weight                     qpg_VHC_weight
vehicle_accel                      qpg_VHC_accel
vehicle_decel                      qpg_VHC_decel
vehicle_demand                     qpg_VHC_demand
vehicle_familiar                   qpg_VHC_familiar
vehicle_perturbation               qpg_VHC_perturbation
vehicle_pcus                       qpg_VHC_pcus
vehicle_matrix                     qpg_VHC_matrix
vehicle_origin                     qpg_VHC_origin
vehicle_origin_trip                qpg_VHC_originTrip
vehicle_destination                qpg_VHC_destination
vehicle_destination_trip           qpg_VHC_destinationTrip
vehicle_lane_low                   qpg_VHC_laneLow
vehicle_lane_high                  qpg_VHC_laneHigh
vehicle_next_lane                  qpg_VHC_nextLane
vehicle_next_exit                  qpg_VHC_nextExit
vehicle_age                        qpg_VHC_age
vehicle_start_time                 qpg_VHC_startTime
vehicle_exist_time                 qpg_VHC_existTime
vehicle_route_table                qpg_VHC_routeTable
vehicle_let_in                     qpg_VHC_letIn
vehicle_on_node                    qpg_VHC_onNode
vehicle_not_major                  qpg_VHC_notMajor
vehicle_moving_in                  qpg_VHC_movingIn
vehicle_stopped                    qpg_VHC_stopped
vehicle_incident                   qpg_VHC_incident
vehicle_recycle_set                qps_VHC_recycle
vehicle_bus_avoid                  qpg_VHC_busAvoid
vehicle_is_heavy                   qpg_VHC_isHeavy
vehicle_is_bus                     qpg_VHC_isBus
vehicle_bus_at_stop                qpg_BUS_atStop
type_length                        qpg_VTP_length
type_width                         qpg_VTP_width
type_height                        qpg_VTP_height
type_weight                        qpg_VTP_weight
type_accel                         qpg_VTP_acceleration
type_decel                         qpg_VTP_deceleration
type_demand                        qpg_VTP_demand
type_familiar                      qpg_VTP_familiar
type_perturbation                  qpg_VTP_perturbation
type_pcus                          qpg_VTP_pcus
type_matrix                        qpg_VTP_matrix
type_restricted                    qpg_VTP_restricted
n_detectors                        qpg_NET_detectors
name_detector                      qpg_NET_detector
is_detector_loop                   qpg_DTI_isLoop
detector_id                        qpg_DTI_name
loop_n_lanes                       qpg_DTI_lanes
loop_flow                          qpg_DTI_flow
loop_speed                         qpg_DTI_speed
loop_gap                           qpg_DTI_gap
loop_occupancy                     qpg_DTI_occupancy
loop_count                         qpg_DTI_count
loop_faulty                        qpg_DTI_faulty
loop_suspect                       qpg_DTI_suspect
loop_set                           qps_DTI_state
detector_loop_set                  qps_DTL_state
n_beacons                          qpg_NET_beacons
beacon_ident                       qpg_BCI_name
beacon_link                        qpg_BCI_link
vms_message                        qpg_BCI_message
vms_dist                           qpg_BCI_distance
vms_message_set                    qps_BCI_message
vms_colour_set                     qps_BCI_colour
vms_visibility                     qpg_BCI_visibility
vms_visibility_set                 qps_BCI_visibility
vms_colour                         qpg_BCI_colour
vms_colour_clear                   qps_BCI_colourClear
vms_toggel_bins_graph              qps_BCI_binsGraph
vms_set_bins_format                qps_BCI_binsFormat
vms_set_bin_value                  qps_BCI_binValue
vms_get_bin_value                  qpg_BCI_binValue
vms_set_bin_colour                 qps_BCI_binColour
vms_get_bin_colour                 qpg_BCI_binColour
vms_set_max_bin_value              qps_BCI_maxBinValue
vms_get_max_bin_value              qpg_BCI_maxBinValue
vms_get_graph_name                 qpg_BCI_graphName
vms_set_graph_name                 qps_BCI_graphName
external_distance_unit_label       qpg_UTL_distanceUnitLabel
external_speed_unit_label          qpg_UTL_speedUnitLabel
external_acceleration_unit_label   qpg_UTL_accelerationUnitLabel
external_density_unit_label        qpg_UTL_densityUnitLabel
external_event_density_unit_label  qpg_UTL_eventDensityUnitLabel
external_weight_unit_label         qpg_UTL_weightUnitLabel
from_internal_distance_unit        qpg_UTL_toExternalDistance
from_internal_speed_unit           qpg_UTL_toExternalSpeed
from_internal_acceleration_unit    qpg_UTL_toExternalAcceleration
from_internal_density_unit         qpg_UTL_toExternalDensity
from_internal_weight_unit          qpg_UTL_toExternalWeight
to_internal_distance_unit          qpg_UTL_toInternalDistance
to_internal_speed_unit             qpg_UTL_toInternalSpeed
to_internal_acceleration_unit      qpg_UTL_toInternalAcceleration
to_internal_density_unit           qpg_UTL_toInternalDensity
to_internal_weight_unit            qpg_UTL_toInternalWeight
utl_d_random                       qpg_UTL_randomDouble
utl_f_random                       qpg_UTL_randomFloat
utl_i_random                       qpg_UTL_randomInteger
utl_tf_random                      qpg_UTL_randomBoolean
utl_i_normal_random                qpg_UTL_randomNormalInteger
utl_i_poisson_random               qpg_UTL_randomPoissonInteger
utl_linear_spread                  qpg_UTL_linearSpread
utl_skew_spread                    qpg_UTL_skewSpread
linear_spread                      qpg_UTL_linearSpread
skew_spread                        qpg_UTL_skewSpread
utl_start_timer                    qpg_UTL_startTimer
utl_lap_timer                      qpg_UTL_lapTimer
utl_reset_timer                    qpg_UTL_resetTimer
utl_read_timer                     qpg_UTL_readTimer
utl_int2HMS                        qpg_UTL_integerToTime
utl_int2HMSstr                     qpg_UTL_integerToTimeString
utl_int2HMSstrF                    qpg_UTL_integerToTimeFileName
int2HMS                            qpg_UTL_integerToTime
int2HMSstr                         qpg_UTL_integerToTimeString
int2HMSstrF                        qpg_UTL_integerToTimeFileName
utl_file_time_separator_set        qps_UTL_fileTimeSeparator
file_time_separator_set            qps_UTL_fileTimeSeparator
utl_makedir                        qpg_UTL_makeDirectory
utl_file_exists                    qpg_UTL_fileExists
utl_dir_exists                     qpg_UTL_directoryExists
utl_lines_in_file                  qpg_UTL_linesInFile
utl_paramics_home                  qpg_UTL_paramicsHome
utl_paramics_data_home             qpg_UTL_paramicsDataHome
utl_pf_open                        qpg_UTL_fileOpen
utl_pf_close                       qpg_UTL_fileClose
utl_num_open_files                 qpg_UTL_openFiles
utl_append_extension               qpg_UTL_appendExtension
utl_permission_check               qpg_UTL_permissionCheck
utl_net_datapath                   qpg_NET_statsPath
utl_net_statpath                   qpg_NET_dataPath
net_get_statpath                   qpg_NET_statsPath
net_get_datapath                   qpg_NET_dataPath
drw_hollow_circle_z                qps_DRW_hollowCircle
drw_filled_circle_z                qps_DRW_filledCircle
drw_hollow_circle                  qps_DRW_hollowCircleXY
drw_filled_circle                  qps_DRW_filledCircleXY
drw_hollow_rectangle               qps_DRW_hollowRectangleXY
drw_filled_rectangle               qps_DRW_filledRectangleXY
drw_hollow_rectangle_z             qps_DRW_hollowRectangle
drw_filled_rectangle_z             qps_DRW_filledRectangle
drw_string_facncy_z                qps_DRW_stringRotated
drw_string_facncy                  qps_DRW_stringXYRotated
drw_string_z                       qps_DRW_string
drw_string                         qps_DRW_stringXY
drw_arrow_z                        qps_DRW_arrow
drw_colourkey                      qps_DRW_colourkey
drw_colour_scale                   qps_DRW_colourScale
drw_banded_table                   qps_DRW_bandedTable
drw_event_table                    qps_DRW_eventTable
drw_move_to_vehicle_home           qps_DRW_moveToVehicleHome
drw_move_to_zone_home              qps_DRW_moveToZoneHome
drw_move_to_node_home              qps_DRW_moveToNodeHome
drw_move_to_kerb_home              qps_DRW_moveToKerbHome
drw_move_to_stopline_home          qps_DRW_moveToStoplineHome
drw_move_to_detector_home          qps_DRW_moveToDetectorHome
drw_move_to_beacon_home            qps_DRW_moveToBeaconHome
drw_store_drawing_matrix           qps_DRW_storeDrawingMatrix
drw_load_drawing_matrix            qps_DRW_loadDrawingMatrix
drw_object_begin                   qps_DRW_objectBegin
drw_object_end                     qps_DRW_objectEnd
drw_colour                         qps_DRW_colour
drw_colour_rgb                     qps_DRW_colourRGB
drw_vertex                         qps_DRW_vertexXY
drw_vertex_z                       qps_DRW_vertex
drw_set_matrix_mode                qps_DRW_matrixMode
drw_load_identity_matrix           qps_DRW_loadIdentityMatrix
drw_linewidth                      qps_DRW_linewidth
drw_get_linewidth                  qpg_DRW_linewidth
drw_line_style                     qps_DRW_lineStyle
drw_get_default_linewidth          qpg_DRW_defaultLinewidth
drw_translate                      qps_DRW_translate
drw_scale                          qps_DRW_scale
drw_rotate                         qps_DRW_rotate
drw_solid                          qps_DRW_solid
drw_transparent                    qps_DRW_transparent
drw_3d                             qpg_DRW_is3D
draw_link_band                     qps_DRAW_linkBand
drw_link_band                      qps_DRW_linkBand
drw_shade_link                     qps_DRW_shadeLink
drw_shade_link_partial             qps_DRW_shadeLinkPartial
drw_highlight_link                 qps_DRW_highlightLink
drw_lane_closure                   qps_DRW_laneClosure
drw_lane_outline                   qps_DRW_laneOutline
drw_shade_lane                     qps_DRW_shadeLane
drw_shade_lane_partial             qps_DRW_shadeLanePartial
drw_zone_outline                   qps_DRW_zoneOutline
drw_zone_filled                    qps_DRW_zoneFilled
drw_vehicle_colour                 qps_DRW_vehicleColour
drw_vehicle_hide                   qps_DRW_vehicleHide
drw_vehicle_ghost                  qps_DRW_vehicleGhost
drw_vehicle_reset                  qps_DRW_vehicleReset
drw_vehicle_tag                    qps_DRW_vehicleTag
drw_set_signal_custom              qps_DRW_signalCustom
drw_set_signal_style               qps_DRW_signalStyle
drw_set_signal_colour              qps_DRW_signalColour
drw_get_signal_colour              qpg_DRW_signalColour
drw_set_signal_face                qps_DRW_signalFace
pos_vehicle                        qpg_POS_vehicle
pos_zone                           qpg_POS_zone
pos_node                           qpg_POS_node
pos_kerb                           qpg_POS_kerb
pos_stopline                       qpg_POS_stopline
pos_detector                       qpg_POS_detector
pos_beacon                         qpg_POS_beacon
pos_link                           qpg_POS_link
link_vehicle_count                 qpg_LNK_vehicles
link_vehicle_data                  qpg_LNK_vehicleData
link_vehicle_tail                  qpg_LNK_vehicleTail
link_vehicle_head                  qpg_LNK_vehicleHead
signal_action                      qps_SIG_action
signal_inquiry                     qpg_SIG_inquiry
node_external_controller_set       qps_NDE_externalController
yacc_parser                        qpg_UTL_yaccParser
yacc_close                         qpg_UTL_yaccClose
api_coefficient_set                qps_GUI_value
api_toggle_set                     qps_GUI_toggle
api_printf                         qps_GUI_printf
vehicle_act_dist                   qpg_CFM_thresholdDistance
link_match_dist                    qpg_SCO_matchDistance
vehicles_at                        qpg_SCO_vehicles
get_overtakenvehicle               qpg_SCO_overtaken
vehicle_overtaking                 qpg_SCO_overtaking
link_overtaking_set                qps_SCO_overtakingLink
link_overtaking			   qpg_SCO_overtakingLink */

#endif

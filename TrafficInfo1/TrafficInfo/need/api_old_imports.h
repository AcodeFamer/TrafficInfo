/* -----------------------------------------------------------------------
 * Paramics Programmer API   (paramics-support@quadstone.com)
 * Quadstone Ltd.             Tel: +44 131 220 4491
 * 16 Chester Street          Fax: +44 131 220 4492
 * Edinburgh,EH3 7RA,UK     WWW: http://www.paramics-online.com
 *
 *
 *
 * This file can be included in the user's file to allow conversion from the
 * old naming scheme to the new
 * ----------------------------------------------------------------------- */ 

#ifndef _API_OLD_IMPORTS_H_
#define _API_OLD_IMPORTS_H_

#include <stdio.h>

#include "api_constants.h"
#include "api_typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------ Loop-Back ------------------------------------------------------ */

float std_follow_acc(VEHICLE* vehicle, VEHICLE* aheadvehicle,float gap, LINK* link);
int   std_lookahead_vehicles(int awareness); 
float std_constrained_acc(VEHICLE* vehicle, LINK* link,float speed,float dist);
float std_gradient_acc(int type,int age,float speed,float grad,float acc);
Bool  std_move_out(VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link);
Bool  std_move_in (VEHICLE* vehicle, VEHICLE* infrontvehicle[], VEHICLE* behindvehicle[], LINK* link);
Bool  std_gap_exists (VEHICLE* vehicle, VEHICLE* aheadvehicle, VEHICLE* behindvehicle, LINK* link,Bool urgent);
void  std_lane_usage (VEHICLE* vehicle, LINK* link,int *loLane,int *hiLane);
void  std_behaviour (VEHICLE* vehicle);
float std_link_maxspeed (LINK* link, VEHICLE* vehicle);
float std_stopping_distance(VEHICLE* vehicle);
float std_activate_distance(VEHICLE* vehicle);
float std_safe_distance(VEHICLE* vehicle,float speed);


/* ------- Timing -------------------------------------------------------- */

float mean_headway (void);       
float mean_reaction (void); 
float timestep (void);
void  timestep_set (float val);  
float simulation_time (void);

/* ------- Config -------------------------------------------------------- */

int   cfg_speed_memory(void);
int   cfg_start_time(void);
int   cfg_duration(void);
float cfg_demand_weight(void);
float cfg_timestep_detail(void);
float cfg_timestep(void);
int   cfg_seed(void);
Bool  cfg_split_seed(void);
float cfg_cost_a(void);
float cfg_cost_b(void);
float cfg_cost_c(void);
float cfg_q_speed(void);
float cfg_q_gap(void);
float cfg_heavy_weight(void);
float cfg_loop_size(void);
int   cfg_feedback_period(void);
Bool  cfg_perturbation(void);
Bool  cfg_sqr_root(void);
float cfg_feedback_smoothing(void);
float cfg_feedback_decay(void);
Bool  cfg_turning_penalties_visible(void);
float cfg_amber_time(void);
Bool  cfg_closest_origin(void);
Bool  cfg_closest_detination(void);
char  cfg_filetime_deliminator(void);
float cfg_curve_speed_factor(void);

/* ------- Stats -------------------------------------------------------- */

float  sta_vehicle_total_delay(void);
double sta_vehicle_total_distance(void);
int    sta_vehicle_total_count(void);
int    sta_vehicle_total_stop_time(void);
float  sta_vehicle_mean_speed(void);
float  sta_vehicle_mean_delay(void);
float  sta_vehicle_last_speed(void);
int    sta_vehicle_last_count(void);
float  sta_bus_total_delay(void);
double sta_bus_total_distance(void);
int    sta_bus_total_count(void);
float  sta_bus_mean_speed(void);
float  sta_bus_mean_delay(void);
int    sta_bus_total_stops(void);
int    sta_bus_total_stop_time(void);
int    sta_bus_get_on(void);
int    sta_bus_get_off(void);
float  sta_bus_last_speed(void);
int    sta_bus_last_count(void);
float  sta_all_total_delay(void);
double sta_all_total_distance(void);
int    sta_all_total_count(void);
float  sta_all_mean_speed(void);
float  sta_all_mean_delay(void);
float  sta_all_last_speed(void);
int    sta_all_last_count(void);
float  sta_speed(LINK* link,int lane);
float  sta_flow(LINK* link,int lane);	      
float  sta_count(LINK* link,int lane);
float  sta_density(LINK* link,int lane);
float  sta_percent_delay(LINK* link,int lane);
float  sta_delay(LINK* link,int lane);
float  sta_stopline_q_length(LINK* link,int lane);
int    sta_stopline_q_count(LINK* link,int lane);
float  sta_stopline_q_pcus(LINK* link,int lane);

/* ------- Network ------------------------------------------------------- */

char* net_datapath (void);
int   net_n_nodes (void);
int   net_n_links (void);
int   net_n_zones (void);
int   net_n_vehicle_types (void);
int   net_n_vehicles_simulating (void);
int   net_n_vehicles_simulated (void);
int   net_n_vehicles_demanded (void);
float net_speed_up(void);
NODE* id_node (int id);
LINK* id_link (int id);
int   node_id (NODE* node);
int   link_id (LINK* link);

/* ------- Nodes --------------------------------------------------------- */

char* node_name (NODE* node);
NODE* node_ref (char *name);
int   node_n_links (NODE* node);
LINK* node_link (NODE* node,int index);
int   node_n_phases (NODE* node);
Bool  node_variable (NODE* node);
void  node_variable_set (NODE* node,Bool value);
Bool  node_hold (NODE* node);
void  node_hold_set (NODE* node,Bool value);
Bool  nodes_connected  (NODE* node1, NODE* node2);
Bool  node_ghost_island(NODE* node);
Bool  node_roundabout(NODE* node);
Bool  node_signalised(NODE* node);
int   node_n_entry_links(NODE* node);
int   node_n_exit_links(NODE* node);


/* ------- Links --------------------------------------------------------- */

char* link_name (LINK* link);
LINK* link_ref (char *name);
int   link_n_links (LINK* link);
LINK* link_link (LINK* link,int index);
int   link_n_exit_links (LINK* link);
LINK* link_exit (LINK* link,int index); 
int   link_n_entry_links (LINK* link);
LINK* link_entry (LINK* link,int index); 
float link_length (LINK* link);
float link_gradient (LINK* link);
int   link_n_lanes (LINK* link);
Bool  link_urban (LINK* link);
float link_speedlimit (LINK* link);
void  link_speedlimit_set (LINK* link,float value);
float link_to_hazard (LINK* link, VEHICLE* vehicle);
float link_signposting (LINK* link);
int   link_hazard (LINK* link);  /* see APIHAZ_ values */
void  link_priority_set (LINK* link1, LINK* link2,int pri);
Bool  link_signals_ahead (LINK* link, VEHICLE* vehicle);
Bool  link_signals_nearside (LINK* link, VEHICLE* vehicle);
int   link_n_detectors (LINK* link);
int   link_detector (LINK* link,int index);
float link_detector_dist (LINK* link,int index);
int   link_n_beacons (LINK* link);
int   link_beacon (LINK* link,int index);
int   link_zone (LINK* link);
Bool  link_zone_connector (LINK* link);
Bool  link_stay_in_lane (LINK* link);
float link_headway_mod (LINK* link);
int   link_turncount (LINK* link,int exit);
void  link_turncount_clear (LINK* link,int exit);
Bool  link_special (LINK* link);
void  link_special_set (LINK* link,Bool value);
int   link_cost (LINK* link,int table); 
int   link_exit_cost (LINK* link1, LINK* link2,int table);
int   link_destination_cost (LINK* link,int destination,int table);
void  link_destination_cost_set(LINK* link,int destination,int table,int cost);
void  link_destination_cost_vector_set(LINK* link,int table,int nzones,int *zone,int *icost);
float link_turnspeed (LINK* link,int exit); 
void  link_turnspeed_set (LINK* link,int exit,float value); 
NODE* link_node_start  (LINK* link);
NODE* link_node_end  (LINK* link);
Bool  link_restricted_type (LINK* link,int v_type);
int   link_lane_restriction (LINK* link,int lane);
float link_width(LINK* link);
float link_median_width(LINK* link);
int   link_category(LINK* link);
float link_angle(LINK* link);
float link_start_angle(LINK* link);
float link_end_angle(LINK* link);
Bool  link_stacking_stopline(LINK* link);
Bool  link_barred(LINK* link);
Bool  link_arc(LINK* link);
Bool  link_arc_left(LINK* link);
Bool  link_to_ramp(LINK* link);
Bool  link_ratelocked(LINK* link);
Bool  link_slip_lane(LINK* link);
Bool  link_wide_start(LINK* link);
Bool  link_wide_end(LINK* link);
float link_cost_factor(LINK* link);
Bool  link_on_roundabout(LINK* link);
Bool  link_force_merge(LINK* link);
Bool  link_force_across(LINK* link);
int   link_linktype(LINK* link);
LINK* link_nearside(LINK* link);
LINK* link_offside(LINK* link);
LINK* link_backside(LINK* link);
LINK* link_match(LINK* link);
float link_endspeed(LINK* link);
Bool  link_tolls(LINK* link);


/* ------- Demands ------------------------------------------------------- */

Bool  dmd_periods(void);
int   dmd_profile_count(void);
int   dmd_period_count(void);
int   dmd_current_period(void);
int   dmd_matrix_count(void);

/* ------- Zones --------------------------------------------------------- */

int   zone_index (ZONE* zone);            
ZONE* index_zone (int index);            
int   zone_external_index (int index);            
int   zone_n_unreleased (ZONE* zone);     
int   zone_n_links (ZONE* zone);          
LINK* zone_link (ZONE* zone,int index);     
int   zone_n_released(ZONE* zone);
int   zone_n_carparks(ZONE* zone);
int   zone_type(ZONE* zone);
int   zone_target_demand(int orig,int dest,int matrix);
void  zone_vehicle_recall_set (Bool value);       
void  zone_vehicle_type_set (int value);       
void  zone_vehicle_destination_set (int value); 
void  zone_vehicle_profile_set (int value);      
void  zone_vehicle_awareness_set (int value);     
void  zone_vehicle_aggression_set (int value);     
void  zone_vehicle_familiarity_set (Bool value);   
void  zone_vehicle_lane_set (int value);           
void  zone_vehicle_speed_set (float value);        
void  zone_vehicle_distance_set (float value);     

/* ------- Car Parks  ---------------------------------------------------- */



/* ------- Vehicles ------------------------------------------------------ */

LINK* vehicle_link (VEHICLE* vehicle);  
int   vehicle_lane (VEHICLE* vehicle);
float vehicle_distance (VEHICLE* vehicle);
void  vehicle_distance_set (VEHICLE* vehicle,float value);
float vehicle_speed (VEHICLE* vehicle);
void  vehicle_speed_set (VEHICLE* vehicle,float value);
float vehicle_speed_historic (VEHICLE* vehicle,float time);
BSMDECLSPEC float vehicle_acc (LINK* link, VEHICLE* vehicle);
BSMDECLSPEC float vehicle_dec (LINK* link, VEHICLE* vehicle);
Bool  vehicle_accelerating (VEHICLE* vehicle);
void  vehicle_accelerating_set (VEHICLE* vehicle,Bool value);
Bool  vehicle_braking (VEHICLE* vehicle);
void  vehicle_braking_set (VEHICLE* vehicle,Bool value);
int   vehicle_aggression (VEHICLE* vehicle);
void  vehicle_aggression_set (VEHICLE* vehicle,int value);
int   vehicle_awareness (VEHICLE* vehicle);
void  vehicle_awareness_set (VEHICLE* vehicle,int value);
int   vehicle_type (VEHICLE* vehicle);
VEHICLE* vehicle_ahead (VEHICLE* vehicle);
VEHICLE* vehicle_behind (VEHICLE* vehicle);
VEHICLE* vehicle_original (VEHICLE* vehicle);
int   vehicle_tracer (VEHICLE* vehicle);
void  vehicle_report (VEHICLE* vehicle,char *format,...);
void  vehicle_tracer_set (VEHICLE* vehicle,int index,float value);
void  vehicle_dashboard_set (VEHICLE* vehicle,int index,char *format,...); 
Bool  vehicle_special (VEHICLE* vehicle,int index);
void  vehicle_special_set (VEHICLE* vehicle,int index,Bool value);
Bool  vehicle_usertag (VEHICLE* vehicle);
void  vehicle_usertag_set (VEHICLE* vehicle,Bool value);
float vehicle_length  (VEHICLE* vehicle);
float vehicle_width  (VEHICLE* vehicle);
float vehicle_height  (VEHICLE* vehicle);
float vehicle_weight  (VEHICLE* vehicle);
float vehicle_accel  (VEHICLE* vehicle);
float vehicle_decel  (VEHICLE* vehicle);
float vehicle_demand  (VEHICLE* vehicle);
float vehicle_familiar  (VEHICLE* vehicle);
float vehicle_perturbation  (VEHICLE* vehicle);
float vehicle_pcus  (VEHICLE* vehicle);
int   vehicle_matrix  (VEHICLE* vehicle);
int   vehicle_origin (VEHICLE* vehicle);
int   vehicle_origin_trip (VEHICLE* vehicle);
int   vehicle_destination (VEHICLE* vehicle);
int   vehicle_destination_trip (VEHICLE* vehicle);
int   vehicle_lane_low (VEHICLE* vehicle);
int   vehicle_lane_high (VEHICLE* vehicle);
int   vehicle_next_lane (VEHICLE* vehicle);
int   vehicle_next_exit (VEHICLE* vehicle);
int   vehicle_age (VEHICLE* vehicle);
int   vehicle_start_time (VEHICLE* vehicle);
int   vehicle_exist_time (VEHICLE* vehicle);
int   vehicle_route_table (VEHICLE* vehicle);
Bool  vehicle_let_in (VEHICLE* vehicle);
Bool  vehicle_on_node (VEHICLE* vehicle);
Bool  vehicle_not_major (LINK* link, VEHICLE* vehicle);
Bool  vehicle_moving_in (VEHICLE* vehicle);
Bool  vehicle_stopped (VEHICLE* vehicle);
Bool  vehicle_incident (VEHICLE* vehicle);
void  vehicle_recycle_set (Bool val);
Bool  vehicle_bus_at_stop (VEHICLE* vehicle);
Bool  vehicle_bus_avoid (VEHICLE* vehicle,float to_hazard);
Bool  vehicle_is_heavy (VEHICLE* vehicle);
Bool  vehicle_is_bus (VEHICLE* vehicle);
float type_length  (int t);
float type_width  (int t);
float type_height  (int t);
float type_weight  (int t);
float type_accel  (int t);
float type_decel  (int t);
float type_demand  (int t);
float type_familiar  (int t);
float type_perturbation  (int t);
float type_pcus  (int t);
int   type_matrix  (int t);
Bool  type_restricted (int t,int restriction);


/* ------- Buses / FRV's ------------------------------------------------- */




/* -------- Detectors ---------------------------------------------------- */

int   n_detectors (void);
Bool  is_detector_loop  (int detector);
char* detector_id (int detector);
int   loop_n_lanes (int detector);
float loop_flow (int detector,int lane,int type);
float loop_speed (int detector,int lane,int type);
float loop_gap (int detector,int lane,int type);
float loop_occupancy (int detector,int lane,int type);
int   loop_count (int detector,int lane,int vehicleType);
Bool  loop_faulty  (int detector,int lane);
Bool  loop_suspect  (int detector,int lane);
void  loop_set (int detector,int lane,int parameter,float value);

/* -------- ITS ---------------------------------------------------------- */

int   n_beacons (void);
char* beacon_ident (int beacon);
LINK* beacon_link (int beacon);
char* vms_message (int beacon);
float vms_dist (int beacon);
BSMDECLSPEC void  vms_message_set (int beacon,char *format,...);
void  vms_colour_set (int beacon,int colour);
float vms_visibility (int beacon);
void  vms_visibility_set (int beacon,float value);
int   vms_colour (int beacon);
void  vms_colour_clear (int beacon);
void  vms_toggel_bins_graph (int beacon,Bool state);
void  vms_set_bins_format (int beacon,Bool state);
void  vms_set_bin_value (int beacon,int index,float value);
float vms_get_bin_value (int beacon,int index);
void  vms_set_bin_colour (int beacon,int index,int colour);
int   vms_get_bin_colour (int beacon,int index);
void  vms_set_max_bin_value (int beacon,float value);
float vms_get_max_bin_value (int beacon);
char  *vms_get_graph_name (int beacon);
void  vms_set_graph_name (int beacon,char *format,...);


/* -------- Units -------------------------------------------------------- */

BSMDECLSPEC char* external_distance_unit_label (void);
BSMDECLSPEC char* external_speed_unit_label (void);
BSMDECLSPEC char* external_acceleration_unit_label (void);
BSMDECLSPEC char* external_density_unit_label (void);
BSMDECLSPEC char* external_event_density_unit_label (void);
BSMDECLSPEC char* external_weight_unit_label (void);

BSMDECLSPEC float from_internal_distance_unit (void);
BSMDECLSPEC float from_internal_speed_unit (void);
BSMDECLSPEC float from_internal_acceleration_unit (void);
BSMDECLSPEC float from_internal_density_unit (void);
BSMDECLSPEC float from_internal_weight_unit (void);

BSMDECLSPEC float to_internal_distance_unit (void);
BSMDECLSPEC float to_internal_speed_unit (void);
BSMDECLSPEC float to_internal_acceleration_unit (void);
BSMDECLSPEC float to_internal_density_unit (void);
BSMDECLSPEC float to_internal_weight_unit (void);

/* ------------------- utility functions  -------------------------------- */

double utl_d_random(int stream,double range);
float  utl_f_random(int stream,float  range);
int    utl_i_random(int stream,int range);
Bool   utl_tf_random(int stream,int ctrue);
int    utl_i_normal_random(int stream,int mean,int std_dev);
int    utl_i_poisson_random(int stream,float mean);
float  utl_linear_spread (int p1,int p2,float value,float delta);
float  utl_skew_spread (int p1,int p2,float value,float delta,float skew);
float  linear_spread (int p1,int p2,float value,float delta);
float  skew_spread (int p1,int p2,float value,float delta,float skew);

long  utl_start_timer(void);
int   utl_lap_timer(long ref,char scale);
void  utl_reset_timer(long ref);
int   utl_read_timer(long ref,char scale);
void  utl_int2HMS (int t,int *dy,int *hr,int *mn,int *sc);
char* utl_int2HMSstr (int t);
char* utl_int2HMSstrF (int t);
void  int2HMS (int t,int *dy,int *hr,int *mn,int *sc);
char* int2HMSstr (int t);
char* int2HMSstrF (int t);

void  utl_file_time_separator_set(char c);
Bool  utl_makedir(char *path);
Bool  utl_file_exists(char *path);
Bool  utl_dir_exists(char *path);
int   utl_lines_in_file(char *path);
char *utl_paramics_home(void);
char *utl_paramics_data_home(void);
char *utl_net_datapath(void);
char* utl_net_statpath(void);
FILE *utl_pf_open(char *md,char *path);
Bool  utl_pf_close(FILE *fp);
int   utl_num_open_files(void);
char *utl_append_extension(char *filename,char *extension);
Bool  utl_permission_check(void);
char* net_get_statpath (void);
char* net_get_datapath (void);
void  file_time_separator_set(char c);

/* ---------------------- Graphics --------------------------------------- */

void  drw_hollow_circle(float x,float y,float r);
void  drw_hollow_circle_z (float x,float y,float z,float r);
void  drw_filled_circle_z(float x,float y,float z,float r);
void  drw_filled_circle (float x,float y,float r);
void  drw_hollow_rectangle(float bl_x,float bl_y,float tr_x,float tr_y);
void  drw_filled_rectangle(float bl_x,float bl_y,float tr_x,float tr_y);
void  drw_hollow_rectangle_z(float bl_x,float bl_y,float bl_z,float tr_x,float tr_y,float tr_z);
void  drw_filled_rectangle_z(float bl_x,float bl_y,float bl_z,float tr_x,float tr_y,float tr_z);
void  drw_string(char *s,float x,float y,float h);
void  drw_string_z(char *s,float x,float y,float z,float h);
void  drw_string_facncy(char *s,float x,float y,float rot,int n);
void  drw_string_facncy_z(char *s,float x,float y,float z,float rot,int n);
void  drw_arrow_z(float x,float y,float z,float bearing,float gradient,float size,int pos);
void  drw_colourkey(char *min,char *max,char *title,float needle,int yshift);
int   drw_colour_scale(float vlaue);
void  drw_banded_table(int count,char *labels[],int colours[],int fill[],int edge[], int yshift);
void  drw_event_table(int count,char *labels[],int colours[],int tri1[],int tri2[], int yshift);

void  drw_move_to_vehicle_home(VEHICLE* vehicle);
void  drw_move_to_zone_home(ZONE* zone);
void  drw_move_to_node_home(NODE* node);
void  drw_move_to_kerb_home(LINK* link,int kerb);
void  drw_move_to_stopline_home(LINK* link,int lane,int stopline);
void  drw_move_to_detector_home(int detector);
void  drw_move_to_beacon_home(int beacon);

void  drw_store_drawing_matrix(void);
void  drw_load_drawing_matrix(void);
void  drw_object_begin(int object);
void  drw_object_end(void);
void  drw_colour(int c);
void  drw_colour_rgb(float r,float g,float b);
void  drw_vertex(float x,float y);
void  drw_vertex_z(float x,float y,float z);
void  drw_set_matrix_mode(int mode);
void  drw_load_identity_matrix(void);
void  drw_linewidth(float width);
float drw_get_linewidth(void);
void  drw_line_style(int style);
float drw_get_default_linewidth(void);
void  drw_translate(float x,float y,float z);
void  drw_scale(float x,float y,float z);
void  drw_rotate(float angle,char axis);
void  drw_solid(void);
void  drw_transparent(void);
Bool  drw_3d(void);

void  draw_link_band (LINK* link,int colour,float proportion,float percent);
void  drw_link_band (LINK* link,int colour,float proportion,float percent, int start);
void  drw_shade_link(LINK* link,int colour);
void  drw_shade_link_partial(LINK* link,int colour,float percent, int start);
void  drw_highlight_link(LINK* link,int colour);
void  drw_lane_closure(LINK* link,int type,int lane);
void  drw_lane_outline(LINK* link,int lane,int colour);
void  drw_shade_lane(LINK* link,int lane,int colour);
void  drw_shade_lane_partial(LINK* link,int lane,int colour,float percent, int start);

void  drw_zone_outline(ZONE* zone,int colour,float height);
void  drw_zone_filled(ZONE* zone,int colour,float height);

void  drw_vehicle_colour(VEHICLE* vehicle,int colour);
void  drw_vehicle_hide(VEHICLE* vehicle);
void  drw_vehicle_ghost(VEHICLE* vehicle);
void  drw_vehicle_reset(VEHICLE* vehicle);
void  drw_vehicle_tag(VEHICLE* vehicle,int colour,int type,char *format,...);

void  drw_set_signal_custom(NODE* node,Bool state);
void  drw_set_signal_style(NODE* node,int style);
void  drw_set_signal_colour(NODE* node,int colour,int index);
int   drw_get_signal_colour(NODE* node);
void  drw_set_signal_face(NODE* node,int colour);

/* ----------------------- Positional Data ------------------------------- */

void  pos_vehicle (VEHICLE* vehicle, LINK* link,float *x,float *y,float *z,float *bearing,float *gradient);
void  pos_zone(ZONE* zone,float *x,float *y,float *z);
void  pos_node(NODE* node,float *x,float *y,float *z);
void  pos_kerb(LINK* link,int kerb,float *x,float *y,float *z);
void  pos_stopline(LINK* link,int lane,int stopline,float *x,float *y,float *z,float *bearing,float *gradient);
BSMDECLSPEC void  pos_detector(int detector,float *x,float *y,float *z,float *bearing,float *gradient);
BSMDECLSPEC void  pos_beacon(int beacon,float *x,float *y,float *z,float *bearing,float *gradient);
void  pos_link(LINK* link,int lane,float dist,float *x,float *y,float *z,float *bearing,float *gradient);


/* ----------------------- Link vehicle data ----------------------------- */

int   link_vehicle_count(LINK* link,int lane);
/* must give count as parameter to show how much memory is allocated */
void  link_vehicle_list(LINK* link,int lane, int count, VEHICLE* vehicle[]);
VEHICLE *link_vehicle_tail(LINK* link,int lane);
VEHICLE *link_vehicle_head(LINK* link,int lane);


/* -------- Signals ------------------------------------------------------ */

void  signal_action(NODE* node,int phase_index,int balance_index, int action_type, int action_mode, float value);
Bool  signal_inquiry (NODE* node,int phase_index,int inquiry,float *value);



/* ------------------ Lex/Yacc wrappers  -------------------------------- */

void  yacc_close(void *fp); /* can be FILE* or char* */
Bool  yacc_parser (char *path,char *file,FILE **datafilein,FILE **datafileout,int *count,int(*parseFn)(void),int(*wrapFn)(void));


/* ------------------ API interface ------------------------------------- */

void  api_coefficient_set(char *filename,int index,float value);
void  api_toggle_set (char *filename,int index,Bool state);
void  api_printf (char *format,...);

/* ------------------ SC Overtaking ------------------------------------- */

float vehicle_act_dist(VEHICLE* vehicle);
float link_match_dist(VEHICLE* vehicle, LINK* link);
void  vehicles_at(LINK* link,int lane,float dist, VEHICLE** infrontvehicle, VEHICLE** behindvehicle);
VEHICLE*  get_overtakenV       (VEHICLE* vehicle);
Bool  vehicle_overtaking    (VEHICLE* vehicle);
Bool  link_overtaking       (LINK* link);
void  link_overtaking_set   (LINK* link,Bool state);


#ifdef __cplusplus
}
#endif

#endif


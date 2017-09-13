DROP TABLE IF EXISTS scheduler_sequencePropConfig_items;
CREATE TABLE scheduler_sequencePropConfig_items (
  ItemId	  smallint unsigned,
  EFDB_Name	  varchar(32),
  IDL_Type        varchar(32),
  Count           smallint unsigned,
  Units           varchar(32),
  Frequency       float,
  Range           varchar(32),
  Sensor_location varchar(32),
  Description     varchar(128),
  PRIMARY KEY (num)
);
INSERT INTO scheduler_sequencePropConfig_items VALUES (1,"name","string",32,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (2,"prop_id","long",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (3,"twilight_boundary","double",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (4,"delta_lst","double",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (5,"dec_window","double",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (6,"max_airmass","double",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (7,"max_cloud","double",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (8,"min_distance_moon","double",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (9,"exclude_planets","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (10,"num_user_regions","long",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (11,"user_region_ids","long",20,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (12,"num_sub_sequences","long",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (13,"sub_sequence_names","string",32,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (14,"num_sub_sequence_filters","long",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (15,"sub_sequence_filters","string",32,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (16,"num_sub_sequence_filter_visits","long",60,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (17,"num_sub_sequence_events","long",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (18,"num_sub_sequence_max_missed","long",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (19,"sub_sequence_time_intervals","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (20,"sub_sequence_time_window_starts","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (21,"sub_sequence_time_window_maximums","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (22,"sub_sequence_time_window_ends","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (23,"sub_sequence_time_weights","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (24,"num_master_sub_sequences","long",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (25,"master_sub_sequence_names","string",32,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (26,"num_nested_sub_sequences","long",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (27,"nested_sub_sequence_names","string",32,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (28,"num_master_sub_sequence_events","long",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (29,"num_master_sub_sequence_max_missed","long",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (30,"master_sub_sequence_time_intervals","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (31,"master_sub_sequence_time_window_starts","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (32,"master_sub_sequence_time_window_maximums","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (33,"master_sub_sequence_time_window_ends","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (34,"master_sub_sequence_time_weights","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (35,"num_nested_sub_sequence_filters","long",100,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (36,"nested_sub_sequence_filters","string",32,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (37,"num_nested_sub_sequence_filter_visits","long",600,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (38,"num_nested_sub_sequence_events","long",100,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (39,"num_nested_sub_sequence_max_missed","long",100,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (40,"nested_sub_sequence_time_intervals","double",100,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (41,"nested_sub_sequence_time_window_starts","double",100,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (42,"nested_sub_sequence_time_window_maximums","double",100,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (43,"nested_sub_sequence_time_window_ends","double",100,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (44,"nested_sub_sequence_time_weights","double",100,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (45,"num_filters","long",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (46,"filter_names","string",32,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (47,"bright_limit","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (48,"dark_limit","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (49,"max_seeing","double",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (50,"num_filter_exposures","long",10,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (51,"exposures","double",50,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (52,"max_num_targets","long",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (53,"accept_serendipity","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (54,"accept_consecutive_visits","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (55,"restart_lost_sequences","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (56,"restart_complete_sequences","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (57,"airmass_bonus","double",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (58,"hour_angle_bonus","double",1,"",0.054,"","","");
INSERT INTO scheduler_sequencePropConfig_items VALUES (59,"hour_angle_max","double",1,"",0.054,"","","");

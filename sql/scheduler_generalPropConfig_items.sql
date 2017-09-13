DROP TABLE IF EXISTS scheduler_generalPropConfig_items;
CREATE TABLE scheduler_generalPropConfig_items (
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
INSERT INTO scheduler_generalPropConfig_items VALUES (1,"name","string",32,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (2,"prop_id","long",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (3,"twilight_boundary","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (4,"delta_lst","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (5,"dec_window","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (6,"max_airmass","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (7,"max_cloud","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (8,"min_distance_moon","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (9,"exclude_planets","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (10,"num_region_selections","long",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (11,"region_types","string",32,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (12,"region_minimums","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (13,"region_maximums","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (14,"region_bounds","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (15,"region_combiners","string",32,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (16,"num_time_ranges","long",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (17,"time_range_starts","long",20,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (18,"time_range_ends","long",20,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (19,"num_selection_mappings","long",20,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (20,"selection_mappings","long",100,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (21,"num_exclusion_selections","long",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (22,"exclusion_types","string",32,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (23,"exclusion_minimums","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (24,"exclusion_maximums","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (25,"exclusion_bounds","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (26,"num_filters","long",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (27,"filter_names","string",32,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (28,"num_visits","long",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (29,"num_grouped_visits","long",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (30,"bright_limit","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (31,"dark_limit","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (32,"max_seeing","double",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (33,"num_filter_exposures","long",10,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (34,"exposures","double",50,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (35,"max_num_targets","long",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (36,"accept_serendipity","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (37,"accept_consecutive_visits","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (38,"airmass_bonus","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (39,"hour_angle_bonus","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (40,"hour_angle_max","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (41,"restrict_grouped_visits","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (42,"time_interval","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (43,"time_window_start","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (44,"time_window_max","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (45,"time_window_end","double",1,"",0.054,"","","");
INSERT INTO scheduler_generalPropConfig_items VALUES (46,"time_weight","double",1,"",0.054,"","","");

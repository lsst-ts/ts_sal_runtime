DROP TABLE IF EXISTS scheduler_target_items;
CREATE TABLE scheduler_target_items (
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
INSERT INTO scheduler_target_items VALUES (1,"targetId","long",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (2,"fieldId","long",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (3,"groupId","long",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (4,"filter","string",32,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (5,"request_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (6,"request_mjd","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (7,"ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (8,"dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (9,"angle","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (10,"num_exposures","long",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (11,"exposure_times","long",10,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (12,"airmass","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (13,"sky_brightness","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (14,"cloud","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (15,"seeing","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (16,"slew_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (17,"cost","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (18,"prop_boost","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (19,"rank","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (20,"num_proposals","long",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (21,"proposal_Ids","long",10,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (22,"proposal_values","double",10,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (23,"proposal_needs","double",10,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (24,"proposal_bonuses","double",10,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (25,"proposal_boosts","double",10,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (26,"moon_ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (27,"moon_dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (28,"moon_alt","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (29,"moon_az","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (30,"moon_phase","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (31,"moon_distance","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (32,"sun_alt","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (33,"sun_az","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (34,"sun_ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (35,"sun_dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_target_items VALUES (36,"solar_elong","double",1,"",0.054,"","","");

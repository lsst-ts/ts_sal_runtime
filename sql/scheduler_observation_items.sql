DROP TABLE IF EXISTS scheduler_observation_items;
CREATE TABLE scheduler_observation_items (
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
INSERT INTO scheduler_observation_items VALUES (1,"observationId","long",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (2,"observation_start_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (3,"observation_start_mjd","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (4,"observation_start_lst","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (5,"night","long",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (6,"targetId","long",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (7,"fieldId","long",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (8,"groupId","long",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (9,"filter","string",32,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (10,"num_proposals","long",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (11,"proposal_Ids","long",10,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (12,"ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (13,"dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (14,"angle","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (15,"altitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (16,"azimuth","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (17,"num_exposures","long",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (18,"exposure_times","long",10,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (19,"visit_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (20,"sky_brightness","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (21,"airmass","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (22,"cloud","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (23,"seeing_fwhm_500","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (24,"seeing_fwhm_geom","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (25,"seeing_fwhm_eff","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (26,"five_sigma_depth","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (27,"moon_ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (28,"moon_dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (29,"moon_alt","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (30,"moon_az","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (31,"moon_phase","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (32,"moon_distance","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (33,"sun_alt","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (34,"sun_az","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (35,"sun_ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (36,"sun_dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_observation_items VALUES (37,"solar_elong","double",1,"",0.054,"","","");

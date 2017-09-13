DROP TABLE IF EXISTS scheduler_driverConfig_items;
CREATE TABLE scheduler_driverConfig_items (
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
INSERT INTO scheduler_driverConfig_items VALUES (1,"coadd_values","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (2,"time_balancing","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (3,"timecost_time_max","double",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (4,"timecost_time_ref","double",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (5,"timecost_cost_ref","double",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (6,"timecost_weight","double",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (7,"filtercost_weight","double",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (8,"night_boundary","double",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (9,"new_moon_phase_threshold","double",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (10,"ignore_sky_brightness","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (11,"ignore_airmass","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (12,"ignore_clouds","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_driverConfig_items VALUES (13,"ignore_seeing","boolean",1,"",0.054,"","","");

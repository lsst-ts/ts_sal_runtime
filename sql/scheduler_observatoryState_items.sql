DROP TABLE IF EXISTS scheduler_observatoryState_items;
CREATE TABLE scheduler_observatoryState_items (
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
INSERT INTO scheduler_observatoryState_items VALUES (1,"timestamp","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (2,"pointing_ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (3,"pointing_dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (4,"pointing_angle","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (5,"pointing_altitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (6,"pointing_azimuth","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (7,"pointing_pa","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (8,"pointing_rot","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (9,"tracking","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (10,"telescope_altitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (11,"telescope_azimuth","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (12,"telescope_rotator","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (13,"dome_altitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (14,"dome_azimuth","double",1,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (15,"filter_position","string",32,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (16,"filter_mounted","string",32,"",0.054,"","","");
INSERT INTO scheduler_observatoryState_items VALUES (17,"filter_unmounted","string",32,"",0.054,"","","");

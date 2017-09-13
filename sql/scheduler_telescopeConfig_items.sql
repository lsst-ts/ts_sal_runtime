DROP TABLE IF EXISTS scheduler_telescopeConfig_items;
CREATE TABLE scheduler_telescopeConfig_items (
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
INSERT INTO scheduler_telescopeConfig_items VALUES (1,"altitude_minpos","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (2,"altitude_maxpos","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (3,"azimuth_minpos","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (4,"azimuth_maxpos","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (5,"altitude_maxspeed","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (6,"altitude_accel","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (7,"altitude_decel","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (8,"azimuth_maxspeed","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (9,"azimuth_accel","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (10,"azimuth_decel","double",1,"",0.054,"","","");
INSERT INTO scheduler_telescopeConfig_items VALUES (11,"settle_time","double",1,"",0.054,"","","");

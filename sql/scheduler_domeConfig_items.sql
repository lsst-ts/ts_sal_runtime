DROP TABLE IF EXISTS scheduler_domeConfig_items;
CREATE TABLE scheduler_domeConfig_items (
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
INSERT INTO scheduler_domeConfig_items VALUES (1,"altitude_maxspeed","double",1,"",0.054,"","","");
INSERT INTO scheduler_domeConfig_items VALUES (2,"altitude_accel","double",1,"",0.054,"","","");
INSERT INTO scheduler_domeConfig_items VALUES (3,"altitude_decel","double",1,"",0.054,"","","");
INSERT INTO scheduler_domeConfig_items VALUES (4,"azimuth_maxspeed","double",1,"",0.054,"","","");
INSERT INTO scheduler_domeConfig_items VALUES (5,"azimuth_accel","double",1,"",0.054,"","","");
INSERT INTO scheduler_domeConfig_items VALUES (6,"azimuth_decel","double",1,"",0.054,"","","");
INSERT INTO scheduler_domeConfig_items VALUES (7,"settle_time","double",1,"",0.054,"","","");

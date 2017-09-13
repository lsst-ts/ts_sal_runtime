DROP TABLE IF EXISTS scheduler_rotatorConfig_items;
CREATE TABLE scheduler_rotatorConfig_items (
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
INSERT INTO scheduler_rotatorConfig_items VALUES (1,"minpos","double",1,"",0.054,"","","");
INSERT INTO scheduler_rotatorConfig_items VALUES (2,"maxpos","double",1,"",0.054,"","","");
INSERT INTO scheduler_rotatorConfig_items VALUES (3,"filter_change_pos","double",1,"",0.054,"","","");
INSERT INTO scheduler_rotatorConfig_items VALUES (4,"maxspeed","double",1,"",0.054,"","","");
INSERT INTO scheduler_rotatorConfig_items VALUES (5,"accel","double",1,"",0.054,"","","");
INSERT INTO scheduler_rotatorConfig_items VALUES (6,"decel","double",1,"",0.054,"","","");
INSERT INTO scheduler_rotatorConfig_items VALUES (7,"followsky","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_rotatorConfig_items VALUES (8,"resume_angle","boolean",1,"",0.054,"","","");

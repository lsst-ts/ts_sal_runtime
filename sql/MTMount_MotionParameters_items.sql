DROP TABLE IF EXISTS MTMount_MotionParameters_items;
CREATE TABLE MTMount_MotionParameters_items (
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
INSERT INTO MTMount_MotionParameters_items VALUES (1,"Azimuth_Position","double",1,"",0.054,"","","");
INSERT INTO MTMount_MotionParameters_items VALUES (2,"Azimuth_Velocity","double",1,"",0.054,"","","");
INSERT INTO MTMount_MotionParameters_items VALUES (3,"Azimuth_Acceleration","double",1,"",0.054,"","","");
INSERT INTO MTMount_MotionParameters_items VALUES (4,"Azimuth_Jerk","double",1,"",0.054,"","","");
INSERT INTO MTMount_MotionParameters_items VALUES (5,"Elevation_Position","double",1,"",0.054,"","","");
INSERT INTO MTMount_MotionParameters_items VALUES (6,"Elevation_Velocity","double",1,"",0.054,"","","");
INSERT INTO MTMount_MotionParameters_items VALUES (7,"Elevation_Acceleration","double",1,"",0.054,"","","");
INSERT INTO MTMount_MotionParameters_items VALUES (8,"ElevationJerk","double",1,"",0.054,"","","");

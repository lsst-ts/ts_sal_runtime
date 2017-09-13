DROP TABLE IF EXISTS scheduler_parkConfig_items;
CREATE TABLE scheduler_parkConfig_items (
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
INSERT INTO scheduler_parkConfig_items VALUES (1,"telescope_altitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_parkConfig_items VALUES (2,"telescope_azimuth","double",1,"",0.054,"","","");
INSERT INTO scheduler_parkConfig_items VALUES (3,"telescope_rotator","double",1,"",0.054,"","","");
INSERT INTO scheduler_parkConfig_items VALUES (4,"dome_altitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_parkConfig_items VALUES (5,"dome_azimuth","double",1,"",0.054,"","","");
INSERT INTO scheduler_parkConfig_items VALUES (6,"filter_position","string",32,"",0.054,"","","");

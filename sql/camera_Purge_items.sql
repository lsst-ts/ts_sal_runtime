DROP TABLE IF EXISTS camera_Purge_items;
CREATE TABLE camera_Purge_items (
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
INSERT INTO camera_Purge_items VALUES (1,"Accelerometer","float",6,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (2,"Blower_setting","float",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (3,"Blower_speed","float",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (4,"Body_Flow_meter","float",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (5,"Body_Temp","float",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (6,"Heater_current","float",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (7,"Heaters","float",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (8,"Microphone","long",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (9,"Trunk_Flow_meter","float",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (10,"Trunk_Temp","float",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (11,"Valve_setting","long",1,"",0.054,"","","");
INSERT INTO camera_Purge_items VALUES (12,"Valves","long",1,"",0.054,"","","");

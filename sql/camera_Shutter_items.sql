DROP TABLE IF EXISTS camera_Shutter_items;
CREATE TABLE camera_Shutter_items (
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
INSERT INTO camera_Shutter_items VALUES (1,"Blade_home","short",2,"",0.054,"","","");
INSERT INTO camera_Shutter_items VALUES (2,"Close_profile","float",24,"",0.054,"","","");
INSERT INTO camera_Shutter_items VALUES (3,"Motor_current","float",2,"",0.054,"","","");
INSERT INTO camera_Shutter_items VALUES (4,"Motor_temp","float",2,"",0.054,"","","");
INSERT INTO camera_Shutter_items VALUES (5,"Open_direction","short",1,"",0.054,"","","");
INSERT INTO camera_Shutter_items VALUES (6,"Open_profile","float",24,"",0.054,"","","");
INSERT INTO camera_Shutter_items VALUES (7,"Profile_function","string",32,"",0.054,"","","");

DROP TABLE IF EXISTS camera_Cold_items;
CREATE TABLE camera_Cold_items (
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
INSERT INTO camera_Cold_items VALUES (1,"Compressor_load","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (2,"Compressor_speed","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (3,"Discharge_pressure","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (4,"Discharge_temp","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (5,"Flow_interlock","short",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (6,"Heater_current","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (7,"Heater_voltage","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (8,"Intake_flow","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (9,"Intake_pressure","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (10,"Intake_temp","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (11,"Ion_pump","float",4,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (12,"Mech_pump","short",4,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (13,"Post_expansion_pressure","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (14,"Post_expansion_temp","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (15,"Pre_expansion_pressure","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (16,"Pre_expansion_temp","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (17,"RGA","long",10,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (18,"Return_temp","float",6,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (19,"UtilityRoom_temperature","float",1,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (20,"Vacuum_gauge","float",5,"",0.054,"","","");
INSERT INTO camera_Cold_items VALUES (21,"Valve_status","short",6,"",0.054,"","","");

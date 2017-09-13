DROP TABLE IF EXISTS camera_Cryo_items;
CREATE TABLE camera_Cryo_items (
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
INSERT INTO camera_Cryo_items VALUES (1,"Cold_temperature","float",3,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (2,"Compressor","float",1,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (3,"Compressor_speed","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (4,"Cryo_temperature","float",12,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (5,"Discharge_pressure","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (6,"Discharge_temp","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (7,"Flow_interlock","short",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (8,"Heater_current","float",6,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (9,"Heater_voltage","float",6,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (10,"Intake_flow","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (11,"Intake_pressure","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (12,"Intake_temp","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (13,"Post_expansion_pressure","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (14,"Post_expansion_temp","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (15,"Pre_expansion_pressure","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (16,"Pre_expansion_temp","float",2,"",0.054,"","","");
INSERT INTO camera_Cryo_items VALUES (17,"Return_temp","float",2,"",0.054,"","","");

DROP TABLE IF EXISTS camera_SAS_items;
CREATE TABLE camera_SAS_items (
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
INSERT INTO camera_SAS_items VALUES (1,"Board_ID","short",1,"",0.054,"","","");
INSERT INTO camera_SAS_items VALUES (2,"Board_current","float",4,"",0.054,"","","");
INSERT INTO camera_SAS_items VALUES (3,"Board_temp","float",12,"",0.054,"","","");
INSERT INTO camera_SAS_items VALUES (4,"Board_voltage","float",4,"",0.054,"","","");
INSERT INTO camera_SAS_items VALUES (5,"CABAC_MUX","long",12,"",0.054,"","","");
INSERT INTO camera_SAS_items VALUES (6,"CCD_ID","short",3,"",0.054,"","","");
INSERT INTO camera_SAS_items VALUES (7,"CCD_temp","long",3,"",0.054,"","","");
INSERT INTO camera_SAS_items VALUES (8,"FPGACheckSum","long",6,"",0.054,"","","");
INSERT INTO camera_SAS_items VALUES (9,"REB_ID","short",1,"",0.054,"","","");

DROP TABLE IF EXISTS camera_PCMS_items;
CREATE TABLE camera_PCMS_items (
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
INSERT INTO camera_PCMS_items VALUES (1,"Bias_Status","short",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (2,"Bias_current","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (3,"Bias_voltage","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (4,"Clock_Status","short",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (5,"Clock_current","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (6,"Clock_voltage","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (7,"FPGA_Status","short",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (8,"FPGA_current","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (9,"FPGA_voltage","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (10,"Low_Status","short",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (11,"Low_current","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (12,"Low_voltage","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (13,"OD_Status","short",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (14,"OD_current","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (15,"OD_voltage","float",1,"",0.054,"","","");
INSERT INTO camera_PCMS_items VALUES (16,"REB_ID","short",1,"",0.054,"","","");

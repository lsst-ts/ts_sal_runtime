DROP TABLE IF EXISTS tcs_kernel_Target_items;
CREATE TABLE tcs_kernel_Target_items (
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
INSERT INTO tcs_kernel_Target_items VALUES (1,"Humid","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (2,"Press","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (3,"TLR","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (4,"Tai","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (5,"Temp","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (6,"Wavel","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (7,"XOffset","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (8,"YOffset","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (9,"az","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (10,"azdot","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (11,"el","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (12,"eldot","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (13,"focalplaneX","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (14,"focalplaneY","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Target_items VALUES (15,"t0","float",1,"",0.054,"","","");

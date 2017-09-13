DROP TABLE IF EXISTS tcs_kernel_PointingLog_items;
CREATE TABLE tcs_kernel_PointingLog_items (
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
INSERT INTO tcs_kernel_PointingLog_items VALUES (1,"Aux","float",3,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (2,"Casspa","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (3,"Dec","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (4,"Fl","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (5,"Humid","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (6,"Marked","long",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (7,"Pitch","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (8,"Press","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (9,"Ra","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (10,"Rcorr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (11,"Roll","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (12,"Temp","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (13,"Tlr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (14,"Wavel","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (15,"Xr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingLog_items VALUES (16,"Yr","float",1,"",0.054,"","","");

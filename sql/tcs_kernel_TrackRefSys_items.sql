DROP TABLE IF EXISTS tcs_kernel_TrackRefSys_items;
CREATE TABLE tcs_kernel_TrackRefSys_items (
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
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (1,"ae2mt","float",9,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (2,"amprms","float",21,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (3,"cst","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (4,"diurab","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (5,"hm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (6,"humid","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (7,"press","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (8,"refa","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (9,"refb","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (10,"sst","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (11,"tdbj","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (12,"temp","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (13,"tlat","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (14,"tlr","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackRefSys_items VALUES (15,"wavel","float",1,"",0.054,"","","");

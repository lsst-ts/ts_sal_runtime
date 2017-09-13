DROP TABLE IF EXISTS tcs_kernel_PointingControl_items;
CREATE TABLE tcs_kernel_PointingControl_items (
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
INSERT INTO tcs_kernel_PointingControl_items VALUES (1,"AGuide","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingControl_items VALUES (2,"ALocal","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingControl_items VALUES (3,"BGuide","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingControl_items VALUES (4,"BLocal","float",1,"",0.054,"","","");

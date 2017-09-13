DROP TABLE IF EXISTS tcs_kernel_FK5Target_items;
CREATE TABLE tcs_kernel_FK5Target_items (
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
INSERT INTO tcs_kernel_FK5Target_items VALUES (1,"dec","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (2,"epoc","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (3,"equinox","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (4,"parallax","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (5,"pmDec","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (6,"pmRA","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (7,"ra","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_FK5Target_items VALUES (8,"rv","float",1,"",0.054,"","","");

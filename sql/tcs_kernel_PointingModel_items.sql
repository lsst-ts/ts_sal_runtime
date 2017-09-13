DROP TABLE IF EXISTS tcs_kernel_PointingModel_items;
CREATE TABLE tcs_kernel_PointingModel_items (
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
INSERT INTO tcs_kernel_PointingModel_items VALUES (1,"Coeffv","float",100,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (2,"Model","long",30,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (3,"Nterml","long",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (4,"Nterms","long",1,"",0.054,"","","");
INSERT INTO tcs_kernel_PointingModel_items VALUES (5,"Ntermx","long",1,"",0.054,"","","");

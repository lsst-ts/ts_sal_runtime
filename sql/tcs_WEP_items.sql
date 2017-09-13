DROP TABLE IF EXISTS tcs_WEP_items;
CREATE TABLE tcs_WEP_items (
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
INSERT INTO tcs_WEP_items VALUES (1,"basis_set_name","string",32,"",0.054,"","","");
INSERT INTO tcs_WEP_items VALUES (2,"number_of_terms","long",1,"",0.054,"","","");
INSERT INTO tcs_WEP_items VALUES (3,"z_arr1","double",64,"",0.054,"","","");
INSERT INTO tcs_WEP_items VALUES (4,"z_arr2","double",64,"",0.054,"","","");
INSERT INTO tcs_WEP_items VALUES (5,"z_arr3","double",64,"",0.054,"","","");
INSERT INTO tcs_WEP_items VALUES (6,"z_arr4","double",64,"",0.054,"","","");

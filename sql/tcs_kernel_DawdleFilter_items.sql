DROP TABLE IF EXISTS tcs_kernel_DawdleFilter_items;
CREATE TABLE tcs_kernel_DawdleFilter_items (
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
INSERT INTO tcs_kernel_DawdleFilter_items VALUES (1,"Bypass","long",1,"",0.054,"","","");
INSERT INTO tcs_kernel_DawdleFilter_items VALUES (2,"T","float",1,"",0.054,"","","");

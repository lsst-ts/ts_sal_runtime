DROP TABLE IF EXISTS tcs_AOCS_items;
CREATE TABLE tcs_AOCS_items (
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
INSERT INTO tcs_AOCS_items VALUES (1,"result","string",32,"",0.054,"","","");

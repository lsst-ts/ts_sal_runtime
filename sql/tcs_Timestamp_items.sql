DROP TABLE IF EXISTS tcs_Timestamp_items;
CREATE TABLE tcs_Timestamp_items (
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
INSERT INTO tcs_Timestamp_items VALUES (1,"Timestamp","string",32,"",0.054,"","","");

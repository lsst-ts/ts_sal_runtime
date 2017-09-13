DROP TABLE IF EXISTS m1m3_LUT_items;
CREATE TABLE m1m3_LUT_items (
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
INSERT INTO m1m3_LUT_items VALUES (1,"param","float",32,"",0.054,"","","");

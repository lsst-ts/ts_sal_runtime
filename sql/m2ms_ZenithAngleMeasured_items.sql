DROP TABLE IF EXISTS m2ms_ZenithAngleMeasured_items;
CREATE TABLE m2ms_ZenithAngleMeasured_items (
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
INSERT INTO m2ms_ZenithAngleMeasured_items VALUES (1,"ZenithAngleMeasured","double",1,"",0.054,"","","");

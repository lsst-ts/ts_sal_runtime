DROP TABLE IF EXISTS scheduler_iconstraints_items;
CREATE TABLE scheduler_iconstraints_items (
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
INSERT INTO scheduler_iconstraints_items VALUES (1,"codes","long",32,"",0.054,"","","");

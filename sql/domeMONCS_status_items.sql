DROP TABLE IF EXISTS domeMONCS_status_items;
CREATE TABLE domeMONCS_status_items (
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
INSERT INTO domeMONCS_status_items VALUES (1,"data","float",16,"",0.054,"","","");

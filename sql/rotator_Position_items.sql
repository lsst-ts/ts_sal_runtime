DROP TABLE IF EXISTS rotator_Position_items;
CREATE TABLE rotator_Position_items (
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
INSERT INTO rotator_Position_items VALUES (1,"Calibrated","float",32,"",0.054,"","","");
INSERT INTO rotator_Position_items VALUES (2,"Raw","long",16,"",0.054,"","","");
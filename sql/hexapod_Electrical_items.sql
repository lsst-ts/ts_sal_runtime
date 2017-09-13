DROP TABLE IF EXISTS hexapod_Electrical_items;
CREATE TABLE hexapod_Electrical_items (
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
INSERT INTO hexapod_Electrical_items VALUES (1,"error","long",16,"",0.054,"","","");
INSERT INTO hexapod_Electrical_items VALUES (2,"status","short",16,"",0.054,"","","");
INSERT INTO hexapod_Electrical_items VALUES (3,"voltage","long",16,"",0.054,"","","");
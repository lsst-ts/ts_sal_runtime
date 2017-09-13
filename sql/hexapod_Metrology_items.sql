DROP TABLE IF EXISTS hexapod_Metrology_items;
CREATE TABLE hexapod_Metrology_items (
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
INSERT INTO hexapod_Metrology_items VALUES (1,"distance","long",18,"",0.054,"","","");
INSERT INTO hexapod_Metrology_items VALUES (2,"error","long",18,"",0.054,"","","");
INSERT INTO hexapod_Metrology_items VALUES (3,"status","short",18,"",0.054,"","","");

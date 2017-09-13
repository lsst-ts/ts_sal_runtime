DROP TABLE IF EXISTS m1m3_Application_items;
CREATE TABLE m1m3_Application_items (
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
INSERT INTO m1m3_Application_items VALUES (1,"demand","float",6,"",0.054,"","","");
INSERT INTO m1m3_Application_items VALUES (2,"error","float",6,"",0.054,"","","");
INSERT INTO m1m3_Application_items VALUES (3,"position","float",6,"",0.054,"","","");
INSERT INTO m1m3_Application_items VALUES (4,"status","short",16,"",0.054,"","","");

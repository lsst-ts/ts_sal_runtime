DROP TABLE IF EXISTS rotator_TC_items;
CREATE TABLE rotator_TC_items (
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
INSERT INTO rotator_TC_items VALUES (1,"error","float",16,"",0.054,"","","");
INSERT INTO rotator_TC_items VALUES (2,"setpoint","float",16,"",0.054,"","","");
INSERT INTO rotator_TC_items VALUES (3,"status","short",16,"",0.054,"","","");
INSERT INTO rotator_TC_items VALUES (4,"temperature","float",16,"",0.054,"","","");

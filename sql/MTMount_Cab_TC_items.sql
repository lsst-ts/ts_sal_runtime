DROP TABLE IF EXISTS MTMount_Cab_TC_items;
CREATE TABLE MTMount_Cab_TC_items (
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
INSERT INTO MTMount_Cab_TC_items VALUES (1,"Cabinet_Internal_Temperature_1","double",1,"",0.054,"","","");
INSERT INTO MTMount_Cab_TC_items VALUES (2,"Cabinet_Internal_Temperature_2","double",1,"",0.054,"","","");
INSERT INTO MTMount_Cab_TC_items VALUES (3,"Cabinet_External_Temperature_1","double",1,"",0.054,"","","");
INSERT INTO MTMount_Cab_TC_items VALUES (4,"Cabinet_External_Temperature_2","double",1,"",0.054,"","","");

DROP TABLE IF EXISTS scheduler_obsSiteConfig_items;
CREATE TABLE scheduler_obsSiteConfig_items (
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
INSERT INTO scheduler_obsSiteConfig_items VALUES (1,"name","string",32,"",0.054,"","","");
INSERT INTO scheduler_obsSiteConfig_items VALUES (2,"latitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_obsSiteConfig_items VALUES (3,"longitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_obsSiteConfig_items VALUES (4,"height","double",1,"",0.054,"","","");
INSERT INTO scheduler_obsSiteConfig_items VALUES (5,"pressure","double",1,"",0.054,"","","");
INSERT INTO scheduler_obsSiteConfig_items VALUES (6,"temperature","double",1,"",0.054,"","","");
INSERT INTO scheduler_obsSiteConfig_items VALUES (7,"relative_humidity","double",1,"",0.054,"","","");

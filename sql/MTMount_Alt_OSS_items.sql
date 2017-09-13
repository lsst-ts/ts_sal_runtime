DROP TABLE IF EXISTS MTMount_Alt_OSS_items;
CREATE TABLE MTMount_Alt_OSS_items (
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
INSERT INTO MTMount_Alt_OSS_items VALUES (1,"Local_Remote","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (2,"Floating","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (3,"Cooling","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (4,"Oil","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (5,"Pump","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (6,"Oil_Flow","double",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (7,"Oil_Pressure","double",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (8,"Oil_Temperature","double",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (9,"Oil_Film","double",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (10,"Oil_Filter_Pressure","double",1,"",0.054,"","","");
INSERT INTO MTMount_Alt_OSS_items VALUES (11,"Status"," unsignedlong",1,"",0.054,"","","");

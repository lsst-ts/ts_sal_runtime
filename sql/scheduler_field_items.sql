DROP TABLE IF EXISTS scheduler_field_items;
CREATE TABLE scheduler_field_items (
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
INSERT INTO scheduler_field_items VALUES (1,"ID","long",1,"",0.054,"","","");
INSERT INTO scheduler_field_items VALUES (2,"fov","double",1,"",0.054,"","","");
INSERT INTO scheduler_field_items VALUES (3,"ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_field_items VALUES (4,"dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_field_items VALUES (5,"gl","double",1,"",0.054,"","","");
INSERT INTO scheduler_field_items VALUES (6,"gb","double",1,"",0.054,"","","");
INSERT INTO scheduler_field_items VALUES (7,"el","double",1,"",0.054,"","","");
INSERT INTO scheduler_field_items VALUES (8,"eb","double",1,"",0.054,"","","");

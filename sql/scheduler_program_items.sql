DROP TABLE IF EXISTS scheduler_program_items;
CREATE TABLE scheduler_program_items (
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
INSERT INTO scheduler_program_items VALUES (1,"completion","float",1,"",0.054,"","","");
INSERT INTO scheduler_program_items VALUES (2,"id","long",1,"",0.054,"","","");
INSERT INTO scheduler_program_items VALUES (3,"priority","long",1,"",0.054,"","","");
INSERT INTO scheduler_program_items VALUES (4,"status","long",1,"",0.054,"","","");

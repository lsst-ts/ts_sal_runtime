DROP TABLE IF EXISTS scheduler_progress_items;
CREATE TABLE scheduler_progress_items (
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
INSERT INTO scheduler_progress_items VALUES (1,"completion","double",32,"",0.054,"","","");
INSERT INTO scheduler_progress_items VALUES (2,"priority","long",32,"",0.054,"","","");
INSERT INTO scheduler_progress_items VALUES (3,"projection","long",32,"",0.054,"","","");
INSERT INTO scheduler_progress_items VALUES (4,"taskid","long",32,"",0.054,"","","");

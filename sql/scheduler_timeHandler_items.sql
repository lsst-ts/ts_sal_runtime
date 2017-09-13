DROP TABLE IF EXISTS scheduler_timeHandler_items;
CREATE TABLE scheduler_timeHandler_items (
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
INSERT INTO scheduler_timeHandler_items VALUES (1,"timestamp","double",1,"",0.054,"","","");
INSERT INTO scheduler_timeHandler_items VALUES (2,"night","long",1,"",0.054,"","","");
INSERT INTO scheduler_timeHandler_items VALUES (3,"is_down","boolean",1,"",0.054,"","","");
INSERT INTO scheduler_timeHandler_items VALUES (4,"down_duration","double",1,"",0.054,"","","");

DROP TABLE IF EXISTS scheduler_blockPusher_items;
CREATE TABLE scheduler_blockPusher_items (
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
INSERT INTO scheduler_blockPusher_items VALUES (1,"timestamp","long",1,"",0.054,"","","");
INSERT INTO scheduler_blockPusher_items VALUES (2,"block","double",200000,"",0.054,"","","");

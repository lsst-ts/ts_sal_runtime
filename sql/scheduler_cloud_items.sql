DROP TABLE IF EXISTS scheduler_cloud_items;
CREATE TABLE scheduler_cloud_items (
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
INSERT INTO scheduler_cloud_items VALUES (1,"timestamp","double",1,"",0.054,"","","");
INSERT INTO scheduler_cloud_items VALUES (2,"cloud","double",1,"",0.054,"","","");

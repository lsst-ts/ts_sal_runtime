DROP TABLE IF EXISTS EXA_Summary_items;
CREATE TABLE EXA_Summary_items (
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
INSERT INTO EXA_Summary_items VALUES (1,"EXAmple","boolean",16,"",0.054,"","","");
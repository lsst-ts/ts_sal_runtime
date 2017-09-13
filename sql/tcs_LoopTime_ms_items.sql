DROP TABLE IF EXISTS tcs_LoopTime_ms_items;
CREATE TABLE tcs_LoopTime_ms_items (
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
INSERT INTO tcs_LoopTime_ms_items VALUES (1,"LoopTime_ms","double",1,"",0.054,"","","");

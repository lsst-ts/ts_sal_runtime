DROP TABLE IF EXISTS m2ms_StepVectorUpdate_items;
CREATE TABLE m2ms_StepVectorUpdate_items (
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
INSERT INTO m2ms_StepVectorUpdate_items VALUES (1,"steps","long",72,"",0.054,"","","");

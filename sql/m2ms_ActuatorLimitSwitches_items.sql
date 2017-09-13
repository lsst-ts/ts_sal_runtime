DROP TABLE IF EXISTS m2ms_ActuatorLimitSwitches_items;
CREATE TABLE m2ms_ActuatorLimitSwitches_items (
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
INSERT INTO m2ms_ActuatorLimitSwitches_items VALUES (1,"forward","boolean",72,"",0.054,"","","");
INSERT INTO m2ms_ActuatorLimitSwitches_items VALUES (2,"reverse","boolean",72,"",0.054,"","","");

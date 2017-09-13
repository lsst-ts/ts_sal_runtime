DROP TABLE IF EXISTS m1m3_Actuators_items;
CREATE TABLE m1m3_Actuators_items (
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
INSERT INTO m1m3_Actuators_items VALUES (1,"cyltemp","float",120,"",0.054,"","","");
INSERT INTO m1m3_Actuators_items VALUES (2,"envtemp","float",120,"",0.054,"","","");
INSERT INTO m1m3_Actuators_items VALUES (3,"error","long",120,"",0.054,"","","");
INSERT INTO m1m3_Actuators_items VALUES (4,"lvdtcorr","float",120,"",0.054,"","","");
INSERT INTO m1m3_Actuators_items VALUES (5,"position","long",120,"",0.054,"","","");
INSERT INTO m1m3_Actuators_items VALUES (6,"pressure","float",120,"",0.054,"","","");
INSERT INTO m1m3_Actuators_items VALUES (7,"setpoint","long",120,"",0.054,"","","");
INSERT INTO m1m3_Actuators_items VALUES (8,"status","long",120,"",0.054,"","","");

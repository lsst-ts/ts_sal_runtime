DROP TABLE IF EXISTS environment_weather_items;
CREATE TABLE environment_weather_items (
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
INSERT INTO environment_weather_items VALUES (1,"ambient_temp","double",1,"",0.054,"","","");
INSERT INTO environment_weather_items VALUES (2,"humidity","double",1,"",0.054,"","","");
INSERT INTO environment_weather_items VALUES (3,"pressure","double",1,"",0.054,"","","");

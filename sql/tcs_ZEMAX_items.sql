DROP TABLE IF EXISTS tcs_ZEMAX_items;
CREATE TABLE tcs_ZEMAX_items (
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
INSERT INTO tcs_ZEMAX_items VALUES (1,"bg_algorithm","string",32,"",0.054,"","","");
INSERT INTO tcs_ZEMAX_items VALUES (2,"exposure","double",1,"",0.054,"","","");
INSERT INTO tcs_ZEMAX_items VALUES (3,"iterations","long",1,"",0.054,"","","");

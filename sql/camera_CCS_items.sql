DROP TABLE IF EXISTS camera_CCS_items;
CREATE TABLE camera_CCS_items (
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
INSERT INTO camera_CCS_items VALUES (1,"CCS_Status","long",20,"",0.054,"","","");
INSERT INTO camera_CCS_items VALUES (2,"Image_Status","long",20,"",0.054,"","","");

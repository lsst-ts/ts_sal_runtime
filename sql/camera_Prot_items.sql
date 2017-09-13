DROP TABLE IF EXISTS camera_Prot_items;
CREATE TABLE camera_Prot_items (
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
INSERT INTO camera_Prot_items VALUES (1,"Status","long",2,"",0.054,"","","");

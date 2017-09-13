DROP TABLE IF EXISTS camera_GDS_items;
CREATE TABLE camera_GDS_items (
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
INSERT INTO camera_GDS_items VALUES (1,"REB_ID","short",1,"",0.054,"","","");
INSERT INTO camera_GDS_items VALUES (2,"Timing_parameter","long",10,"",0.054,"","","");
INSERT INTO camera_GDS_items VALUES (3,"flag","long",20,"",0.054,"","","");

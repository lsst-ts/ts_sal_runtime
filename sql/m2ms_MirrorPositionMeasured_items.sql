DROP TABLE IF EXISTS m2ms_MirrorPositionMeasured_items;
CREATE TABLE m2ms_MirrorPositionMeasured_items (
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
INSERT INTO m2ms_MirrorPositionMeasured_items VALUES (1,"xTilt","double",1,"",0.054,"","","");
INSERT INTO m2ms_MirrorPositionMeasured_items VALUES (2,"yTilt","double",1,"",0.054,"","","");
INSERT INTO m2ms_MirrorPositionMeasured_items VALUES (3,"piston","double",1,"",0.054,"","","");
INSERT INTO m2ms_MirrorPositionMeasured_items VALUES (4,"xPosition","double",1,"",0.054,"","","");
INSERT INTO m2ms_MirrorPositionMeasured_items VALUES (5,"yPosition","double",1,"",0.054,"","","");
INSERT INTO m2ms_MirrorPositionMeasured_items VALUES (6,"theta_z_position","double",1,"",0.054,"","","");

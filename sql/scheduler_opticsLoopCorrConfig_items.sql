DROP TABLE IF EXISTS scheduler_opticsLoopCorrConfig_items;
CREATE TABLE scheduler_opticsLoopCorrConfig_items (
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
INSERT INTO scheduler_opticsLoopCorrConfig_items VALUES (1,"tel_optics_ol_slope","double",1,"",0.054,"","","");
INSERT INTO scheduler_opticsLoopCorrConfig_items VALUES (2,"tel_optics_cl_alt_limit","double",3,"",0.054,"","","");
INSERT INTO scheduler_opticsLoopCorrConfig_items VALUES (3,"tel_optics_cl_delay","double",2,"",0.054,"","","");

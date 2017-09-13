DROP TABLE IF EXISTS scheduler_cameraConfig_items;
CREATE TABLE scheduler_cameraConfig_items (
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
INSERT INTO scheduler_cameraConfig_items VALUES (1,"readout_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (2,"shutter_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (3,"filter_mount_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (4,"filter_change_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (5,"filter_max_changes_burst_num","long",1,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (6,"filter_max_changes_burst_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (7,"filter_max_changes_avg_num","long",1,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (8,"filter_max_changes_avg_time","double",1,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (9,"filter_mounted","string",32,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (10,"filter_pos","string",32,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (11,"filter_removable","string",32,"",0.054,"","","");
INSERT INTO scheduler_cameraConfig_items VALUES (12,"filter_unmounted","string",32,"",0.054,"","","");

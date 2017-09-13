DROP TABLE IF EXISTS domeLouvers_status_items;
CREATE TABLE domeLouvers_status_items (
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
INSERT INTO domeLouvers_status_items VALUES (1,"position_error","float",34,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (2,"position_actual","float",34,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (3,"position_cmd","float",34,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (4,"drive_torque_actual","float",68,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (5,"drive_torque_error","float",68,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (6,"drive_torque_cmd","float",68,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (7,"drive_current_actual","float",68,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (8,"drive_temp_actual","float",68,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (9,"encoder_head_raw","float",68,"",0.054,"","","");
INSERT INTO domeLouvers_status_items VALUES (10,"encoder_head_calibrated","float",68,"",0.054,"","","");

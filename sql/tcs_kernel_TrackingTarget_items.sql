DROP TABLE IF EXISTS tcs_kernel_TrackingTarget_items;
CREATE TABLE tcs_kernel_TrackingTarget_items (
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
INSERT INTO tcs_kernel_TrackingTarget_items VALUES (1,"PositionX","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackingTarget_items VALUES (2,"PositionY","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackingTarget_items VALUES (3,"T0","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackingTarget_items VALUES (4,"VelocityX","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_TrackingTarget_items VALUES (5,"VelocityY","float",1,"",0.054,"","","");

DROP TABLE IF EXISTS MTMount_Az_CW_items;
CREATE TABLE MTMount_Az_CW_items (
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
INSERT INTO MTMount_Az_CW_items VALUES (1,"AngleDif_Actual","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_CW_items VALUES (2,"AngleDif_ActualLVDT","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_CW_items VALUES (3,"Positive_Power_Off_Switch","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_CW_items VALUES (4,"Negative_Power_Off_Switch","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_CW_items VALUES (5,"Axis_Status"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_Az_CW_items VALUES (6,"Curr_Actual_1","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_CW_items VALUES (7,"Curr_Actual_2","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_CW_items VALUES (8,"Drive_Status_1"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_Az_CW_items VALUES (9,"Drive_Status_2"," unsignedlong",1,"",0.054,"","","");

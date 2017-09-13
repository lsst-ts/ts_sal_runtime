DROP TABLE IF EXISTS MTMount_Az_items;
CREATE TABLE MTMount_Az_items (
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
INSERT INTO MTMount_Az_items VALUES (1,"Angle_Set","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (2,"Angle_Actual","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (3,"EncHead_Actual_1"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (4,"EncHead_Actual_2"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (5,"EncHead_Actual_3"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (6,"EncHead_Actual_4"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (7,"Vel_Set","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (8,"Vel_Actual","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (9,"Acc_Actual","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (10,"Torque_Set","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (11,"Axis_Status"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (12,"Positive_Adjustable_Software_Limit","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (13,"Negative_Adjustable_Software_Limit","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (14,"Positive_Software_Limit","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (15,"Negative_Software_Limit","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (16,"Positive_Directional_Limit_Switch","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (17,"Negative_Directional_Limit_Switch","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (18,"Positive_Power_Off_Switch","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (19,"Negative_Power_Off_Switch","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (20,"Curr_Actual","double",1,"",0.054,"","","");
INSERT INTO MTMount_Az_items VALUES (21,"Drive_Status"," unsignedlong",1,"",0.054,"","","");

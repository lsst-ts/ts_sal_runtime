DROP TABLE IF EXISTS MTMount_MC_items;
CREATE TABLE MTMount_MC_items (
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
INSERT INTO MTMount_MC_items VALUES (1,"Pos_Set","double",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (2,"Pos_Actual","double",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (3,"Positive_Directional_Limit_Switch","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (4,"Negative_Directional_Limit_Switch","boolean",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (5,"Axis_Status"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (6,"Curr_Actual_1","double",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (7,"Curr_Actual_2","double",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (8,"Curr_Actual_3","double",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (9,"Curr_Actual_4","double",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (10,"Drive_Status_1"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (11,"Drive_Status_2"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (12,"Drive_Status_3"," unsignedlong",1,"",0.054,"","","");
INSERT INTO MTMount_MC_items VALUES (13,"Drive_Status_4"," unsignedlong",1,"",0.054,"","","");

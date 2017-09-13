DROP TABLE IF EXISTS scheduler_rankingData_items;
CREATE TABLE scheduler_rankingData_items (
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
INSERT INTO scheduler_rankingData_items VALUES (1,"LST","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (2,"MJD","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (3,"date","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (4,"dec","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (5,"exposureTime","double",10,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (6,"fieldId","long",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (7,"filter","string",32,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (8,"moonAlt","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (9,"moonAz","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (10,"moonDec","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (11,"moonDistance","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (12,"moonIllumination","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (13,"moonRa","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (14,"mountAltitude","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (15,"mountAzimuth","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (16,"observationNight","long",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (17,"ra","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (18,"rotatorAngle","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (19,"seeing","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (20,"skyAngle","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (21,"skyBrightnessFilter","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (22,"skyBrightnessV","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (23,"slewTime","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (24,"sunAlt","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (25,"sunAz","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (26,"sunElongation","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (27,"transparency","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (28,"visitTime","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (29,"weatherHumidity","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (30,"weatherWindDirection","double",1,"",0.054,"","","");
INSERT INTO scheduler_rankingData_items VALUES (31,"weatherWindSpeed","double",1,"",0.054,"","","");

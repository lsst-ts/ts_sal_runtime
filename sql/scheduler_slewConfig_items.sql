DROP TABLE IF EXISTS scheduler_slewConfig_items;
CREATE TABLE scheduler_slewConfig_items (
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
INSERT INTO scheduler_slewConfig_items VALUES (1,"prereq_domalt","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (2,"prereq_domaz","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (3,"prereq_domazsettle","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (4,"prereq_telalt","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (5,"prereq_telaz","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (6,"prereq_telopticsopenloop","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (7,"prereq_telopticsclosedloop","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (8,"prereq_telsettle","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (9,"prereq_telrot","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (10,"prereq_filter","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (11,"prereq_exposures","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (12,"prereq_readout","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (13,"prereq_adc","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (14,"prereq_ins_optics","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (15,"prereq_guider_pos","string",32,"",0.054,"","","");
INSERT INTO scheduler_slewConfig_items VALUES (16,"prereq_guider_adq","string",32,"",0.054,"","","");

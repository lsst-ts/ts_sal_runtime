DROP TABLE IF EXISTS tcs_kernel_Site_items;
CREATE TABLE tcs_kernel_Site_items (
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
INSERT INTO tcs_kernel_Site_items VALUES (1,"Amprms","float",21,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (2,"Aoprms","float",15,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (3,"Daz","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (4,"Diurab","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (5,"Elong","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (6,"Lat","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (7,"Refa","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (8,"Refb","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (9,"St0","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (10,"T0","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (11,"Tt0","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (12,"Ttj","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (13,"Ttmtai","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (14,"Uau","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (15,"Ukm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (16,"Vau","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (17,"Vkm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (18,"delat","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (19,"delut","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (20,"elongm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (21,"hm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (22,"latm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (23,"tai","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (24,"ttmtat","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (25,"xpm","float",1,"",0.054,"","","");
INSERT INTO tcs_kernel_Site_items VALUES (26,"ypm","float",1,"",0.054,"","","");

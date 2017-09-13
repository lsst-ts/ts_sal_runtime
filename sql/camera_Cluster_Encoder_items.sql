DROP TABLE IF EXISTS camera_Cluster_Encoder_items;
CREATE TABLE camera_Cluster_Encoder_items (
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
INSERT INTO camera_Cluster_Encoder_items VALUES (1,"Image_SD","float",3216,"",0.054,"","","");
INSERT INTO camera_Cluster_Encoder_items VALUES (2,"Image_mean","float",3216,"",0.054,"","","");
INSERT INTO camera_Cluster_Encoder_items VALUES (3,"Overscan_SD","float",3216,"",0.054,"","","");
INSERT INTO camera_Cluster_Encoder_items VALUES (4,"Overscan_mean","float",3216,"",0.054,"","","");
INSERT INTO camera_Cluster_Encoder_items VALUES (5,"PSF","float",9648,"",0.054,"","","");

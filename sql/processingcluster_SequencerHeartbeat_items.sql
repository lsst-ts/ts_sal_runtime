DROP TABLE IF EXISTS processingcluster_SequencerHeartbeat_items;
CREATE TABLE processingcluster_SequencerHeartbeat_items (
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
INSERT INTO processingcluster_SequencerHeartbeat_items VALUES (1,"Name","string",32,"",0.054,"","","");
INSERT INTO processingcluster_SequencerHeartbeat_items VALUES (2,"Identifier","float",1,"",0.054,"","","");
INSERT INTO processingcluster_SequencerHeartbeat_items VALUES (3,"Timestamp","string",32,"",0.054,"","","");

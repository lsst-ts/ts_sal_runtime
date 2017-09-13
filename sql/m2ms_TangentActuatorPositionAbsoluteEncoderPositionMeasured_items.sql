DROP TABLE IF EXISTS m2ms_TangentActuatorPositionAbsoluteEncoderPositionMeasured_items;
CREATE TABLE m2ms_TangentActuatorPositionAbsoluteEncoderPositionMeasured_items (
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
INSERT INTO m2ms_TangentActuatorPositionAbsoluteEncoderPositionMeasured_items VALUES (1,"tangentLink_0deg_absoluteEncoderPositionMeasured","double",1,"",0.054,"","","");
INSERT INTO m2ms_TangentActuatorPositionAbsoluteEncoderPositionMeasured_items VALUES (2,"tangentLink_60deg_absoluteEncoderPositionMeasured","double",1,"",0.054,"","","");
INSERT INTO m2ms_TangentActuatorPositionAbsoluteEncoderPositionMeasured_items VALUES (3,"tangentLink_120deg_absoluteEncoderPositionMeasured","double",1,"",0.054,"","","");
INSERT INTO m2ms_TangentActuatorPositionAbsoluteEncoderPositionMeasured_items VALUES (4,"tangentLink_180deg_absoluteEncoderPositionMeasured","double",1,"",0.054,"","","");
INSERT INTO m2ms_TangentActuatorPositionAbsoluteEncoderPositionMeasured_items VALUES (5,"tangentLink_240deg_absoluteEncoderPositionMeasured","double",1,"",0.054,"","","");
INSERT INTO m2ms_TangentActuatorPositionAbsoluteEncoderPositionMeasured_items VALUES (6,"tangentLink_300deg_absoluteEncoderPositionMeasured","double",1,"",0.054,"","","");

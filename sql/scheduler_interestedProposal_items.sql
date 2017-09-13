DROP TABLE IF EXISTS scheduler_interestedProposal_items;
CREATE TABLE scheduler_interestedProposal_items (
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
INSERT INTO scheduler_interestedProposal_items VALUES (1,"observationId","long",1,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (2,"num_proposals","long",1,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (3,"proposal_Ids","long",10,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (4,"proposal_values","double",10,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (5,"proposal_needs","double",10,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (6,"proposal_bonuses","double",10,"",0.054,"","","");
INSERT INTO scheduler_interestedProposal_items VALUES (7,"proposal_boosts","double",10,"",0.054,"","","");

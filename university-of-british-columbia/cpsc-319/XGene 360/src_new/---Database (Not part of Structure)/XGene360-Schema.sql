-- March 19 
-- fixed the lengths 
-- fixed stuff in various tables
-- changed to InnoDB with INDEX and FOREIGN KEY
-- added on update/delete cascade
-- INDEX changed to keys and constraints
-- added solution table
-- still need to check how large genotype is
-- is plantid larege enough
-- adding parent table for plants
-- potential bug with generation number
-- generation question
-- fixed index problem

-- 
-- Table structure for table `Course`
-- 

CREATE TABLE `Course` (
  `CourseId` int(10) unsigned NOT NULL auto_increment,
  `Name` varchar(30) NOT NULL default '',
  `Description` varchar(250) default NULL,
  PRIMARY KEY  (`CourseId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `Cross`
-- 

CREATE TABLE `Cross` (
  `CrossNum` int(10) unsigned NOT NULL default '0',
  `UserId` varchar(10) NOT NULL default '',
  `PollenCrossNum` int(10) unsigned NOT NULL default '0',
  `PollenPlantNum` int(10) NOT NULL default '0',
  `PollenGene` varchar(4) NOT NULL default '',
  `SeedCrossNum` int(10) unsigned NOT NULL default '0',
  `SeedPlantNum` int(10) NOT NULL default '0',
  `SeedGene` varchar(4) NOT NULL default '',
  `GeneSequences` varchar(200) default NULL,
  `CreationDate` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`CrossNum`,`UserId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `LongerGeneSequences`
-- 

CREATE TABLE `LongerGeneSequences` (
  `SequencesId` int(10) unsigned NOT NULL auto_increment,
  `UserId` varchar(10) NOT NULL default '',
  `CrossNum` int(10) unsigned NOT NULL default '0',
  `GeneSequences` varchar(200) NOT NULL default '',
  PRIMARY KEY  (`SequencesId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `MasterProblem`
-- 

CREATE TABLE `MasterProblem` (
  `ProblemId` int(10) NOT NULL auto_increment,
  `Description` varchar(250) default NULL,
  `Name` varchar(30) NOT NULL default '',
  `GMU1_2` float unsigned NOT NULL default '50',
  `GMU2_3` float unsigned NOT NULL default '50',
  `TraitOrder` char(3) NOT NULL default '123',
  `CourseId` int(10) NOT NULL default '0',
  `ModificationDate` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `EpistasisCode` tinyint(3) unsigned default NULL,
  `Trait1Name` varchar(20) NOT NULL default '',
  `Trait1AAPhenoName` varchar(20) NOT NULL default '',
  `Trait1AbPhenoName` varchar(20) NOT NULL default '',
  `Trait1bAPhenoName` varchar(20) NOT NULL default '',
  `Trait1bbPhenoName` varchar(20) NOT NULL default '',
  `Trait2Name` varchar(20) NOT NULL default '',
  `Trait2AAPhenoName` varchar(20) NOT NULL default '',
  `Trait2AbPhenoName` varchar(20) NOT NULL default '',
  `Trait2bAPhenoName` varchar(20) NOT NULL default '',
  `Trait2bbPhenoName` varchar(20) NOT NULL default '',
  `Trait3Name` varchar(20) NOT NULL default '',
  `Trait3AAPhenoName` varchar(20) NOT NULL default '',
  `Trait3AbPhenoName` varchar(20) NOT NULL default '',
  `Trait3bAPhenoName` varchar(20) NOT NULL default '',
  `Trait3bbPhenoName` varchar(20) NOT NULL default '',
  `ProgenyPerMating` int(10) unsigned NOT NULL default '50',
  `MaxProgeny` int(10) unsigned NOT NULL default '1000',
  PRIMARY KEY  (`ProblemId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `Phenotype`
-- 

CREATE TABLE `Phenotype` (
  `PhenotypeId` int(10) unsigned NOT NULL auto_increment,
  `TraitId` int(10) unsigned NOT NULL default '0',
  `Name` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`PhenotypeId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `StudentProblem`
-- 

CREATE TABLE `StudentProblem` (
  `UserId` varchar(10) NOT NULL default '',
  `MasterProblemId` int(10) NOT NULL default '0',
  `Modified` tinyint(1) NOT NULL default '0',
  `Description` varchar(250) default NULL,
  `Name` varchar(30) NOT NULL default '',
  `GMU1_2` float unsigned NOT NULL default '50',
  `GMU2_3` float unsigned NOT NULL default '50',
  `TraitOrder` char(3) NOT NULL default '123',
  `ModificationDate` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `EpistasisCode` tinyint(3) unsigned default NULL,
  `Trait1Name` varchar(20) NOT NULL default '',
  `Trait1AAPhenoName` varchar(20) NOT NULL default '',
  `Trait1AbPhenoName` varchar(20) NOT NULL default '',
  `Trait1bAPhenoName` varchar(20) NOT NULL default '',
  `Trait1bbPhenoName` varchar(20) NOT NULL default '',
  `Trait2Name` varchar(20) NOT NULL default '',
  `Trait2AAPhenoName` varchar(20) NOT NULL default '',
  `Trait2AbPhenoName` varchar(20) NOT NULL default '',
  `Trait2bAPhenoName` varchar(20) NOT NULL default '',
  `Trait2bbPhenoName` varchar(20) NOT NULL default '',
  `Trait3Name` varchar(20) NOT NULL default '',
  `Trait3AAPhenoName` varchar(20) NOT NULL default '',
  `Trait3AbPhenoName` varchar(20) NOT NULL default '',
  `Trait3bAPhenoName` varchar(20) NOT NULL default '',
  `Trait3bbPhenoName` varchar(20) NOT NULL default '',
  `ProgenyPerMating` int(10) unsigned NOT NULL default '50',
  `MaxProgeny` int(10) unsigned NOT NULL default '1000',
  `ProgenyGenerated` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`UserId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `Trait`
-- 

CREATE TABLE `Trait` (
  `TraitId` int(10) unsigned NOT NULL auto_increment,
  `CourseId` int(10) unsigned NOT NULL default '0',
  `Name` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`TraitId`),
  FULLTEXT KEY `Name` (`Name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `User`
-- 

CREATE TABLE `User` (
  `UserId` varchar(10) NOT NULL default '',
  `CourseId` int(10) NOT NULL default '0',
  `PrivilegeLvl` tinyint(3) unsigned NOT NULL default '3',
  `FirstName` varchar(20) NOT NULL default '',
  `LastName` varchar(20) NOT NULL default '',
  `Pwd` varchar(50) NOT NULL default '',
  `StudentNum` int(8) unsigned default NULL,
  PRIMARY KEY  (`UserId`),
  KEY `LastName` (`LastName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `XG_ProblemTraitMadeFor`
-- 

CREATE TABLE `XG_ProblemTraitMadeFor` (
  `problem_id` int(10) unsigned NOT NULL auto_increment,
  `problem_name` varchar(250) NOT NULL default '',
  `problem_desc` varchar(250) NOT NULL default '',
  `professor_id` varchar(10) NOT NULL default '',
  `course_id` int(10) unsigned NOT NULL default '0',
  `trait_A_name` varchar(250) NOT NULL default '',
  `trait_B_name` varchar(250) NOT NULL default '',
  `trait_A_unit` varchar(250) NOT NULL default '',
  `trait_B_unit` varchar(250) NOT NULL default '',  
  `trait_A_number_of_genes` int(10) NOT NULL default '0',
  `trait_B_number_of_genes` int(10) NOT NULL default '0',
  `trait_A_h2` double NOT NULL default '0',
  `trait_B_h2` double NOT NULL default '0',
  `trait_A_var` double NOT NULL default '0',
  `trait_B_var` double NOT NULL default '0',
  `trait_A_parent_A_mean` double NOT NULL default '0',
  `trait_A_parent_B_mean` double NOT NULL default '0',
  `trait_B_parent_A_mean` double NOT NULL default '0',
  `trait_B_parent_B_mean` double NOT NULL default '0',
  `number_of_progeny_per_cross` int(10) unsigned NOT NULL default '0',
  `max_cross` int(10) unsigned NOT NULL default '0',
  `number_of_displayed_plants` int(10) unsigned NOT NULL default '0',
  `range_of_acceptance` double NOT NULL default '5',
  `start_date` datetime NOT NULL default '0000-00-00 00:00:00',
  `due_date` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY ( problem_id ), 
  KEY problem_professor_id_index ( professor_id ),
  KEY problem_course_id_index ( course_id ),
  CONSTRAINT problem_professor_id_index  FOREIGN KEY ( professor_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE, 
  CONSTRAINT problem_course_id_index FOREIGN KEY ( course_id ) REFERENCES Course( CourseId )
    ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `XG_Assigns`
-- 

CREATE TABLE `XG_Assigns` (
  `problem_id` int(10) unsigned NOT NULL default '0',
  `student_id` varchar(10) NOT NULL default '',
  PRIMARY KEY (problem_id, student_id),
  KEY assign_problem_id_index ( problem_id ),
  CONSTRAINT assign_problem_id_index FOREIGN KEY ( problem_id ) REFERENCES XG_ProblemTraitMadeFor( problem_id )
    ON UPDATE CASCADE ON DELETE CASCADE, 
  KEY assign_student_id_index ( student_id ), 
  CONSTRAINT assign_student_id_index FOREIGN KEY ( student_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE 
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `XG_Assists`
-- 

CREATE TABLE `XG_Assists` (
  `course_id` int(10) unsigned NOT NULL default '0',
  `ta_id` varchar(10) NOT NULL default '',
  PRIMARY KEY ( course_id, ta_id ),
  KEY assist_course_id_index ( course_id ),
  CONSTRAINT assist_course_id_index FOREIGN KEY ( course_id ) REFERENCES Course( CourseId )
    ON UPDATE CASCADE ON DELETE CASCADE,
  KEY assist_ta_id_index ( ta_id ),
  CONSTRAINT assist_ta_id_index FOREIGN KEY ( ta_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `XG_FeedbackLeftFor`
-- 

CREATE TABLE `XG_FeedbackLeftFor` (
  `feedback_id` int(10) unsigned NOT NULL auto_increment,
  `feedback` text NOT NULL,
  `left_from_id` varchar(10) NOT NULL default '',
  `left_for_id` varchar(10) NOT NULL default '',
  `problem_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  ( feedback_id ),
  KEY left_from_id_index ( left_from_id ),
  CONSTRAINT left_from_id_index FOREIGN KEY ( left_from_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE,
  KEY left_for_id_index ( left_for_id ),
  CONSTRAINT left_for_id_index FOREIGN KEY ( left_for_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE,
  KEY problem_id_index ( problem_id ),
  CONSTRAINT problem_id_index FOREIGN KEY (`problem_id`) REFERENCES XG_ProblemTraitMadeFor( problem_id )
    ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `XG_ProblemSolution` (
  `problem_id` int(10) unsigned NOT NULL default '0',
  `student_id` varchar(10) NOT NULL default '',
  `hand_in_timestamp` datetime NOT NULL default '0000-00-00 00:00:00',
  `solution_desc` blob NOT NULL,
  `trait_A_number_of_genes` int(10) NOT NULL default '0',
  `trait_B_number_of_genes` int(10) NOT NULL default '0',
  `trait_A_h2` double NOT NULL default '0',
  `trait_B_h2` double NOT NULL default '0',
  `trait_A_SD` double NOT NULL default '0',
  `trait_B_SD` double NOT NULL default '0',
  `trait_A_parent_A_mean` double NOT NULL default '0',
  `trait_A_parent_B_mean` double NOT NULL default '0',
  `trait_B_parent_A_mean` double NOT NULL default '0',
  `trait_B_parent_B_mean` double NOT NULL default '0',
  KEY solution_problem_id_index ( problem_id ),
  CONSTRAINT solution_problem_id_index FOREIGN KEY ( problem_id ) REFERENCES XG_ProblemTraitMadeFor( problem_id )
    ON UPDATE CASCADE ON DELETE CASCADE, 
  KEY solution_student_id_index ( student_id ), 
  CONSTRAINT solution_student_id_index FOREIGN KEY ( student_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE 
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- 
-- Table structure for table `XG_PlantGenerates`
-- 

CREATE TABLE `XG_PlantGenerates` (
  `plant_id` int(10) unsigned NOT NULL auto_increment,
  `user_id` varchar(10) NOT NULL default '',
  `problem_id` int(10) unsigned NOT NULL default '0',
  `generation_num` int(10) unsigned NOT NULL default '0',
  `value_trait_A` double NOT NULL default '0',
  `value_trait_B` double NOT NULL default '0',
  `genotype_trait_A` varchar(50) NOT NULL,
  `genotype_trait_B` varchar(50) NOT NULL,
  PRIMARY KEY ( plant_id, user_id, problem_id ), 
  KEY plant_user_id_index ( user_id ),
  CONSTRAINT plant_user_id_index FOREIGN KEY ( user_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE,
  KEY plant_problem_id_index ( problem_id ),
  CONSTRAINT plant_problem_id_index FOREIGN KEY ( problem_id ) REFERENCES XG_ProblemTraitMadeFor( problem_id )
    ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `XG_PlantParents` (
  `plant_id` int(10) unsigned NOT NULL auto_increment,
  `user_id` varchar(10) NOT NULL default '',
  `problem_id` int(10) unsigned NOT NULL default '0',
  `generation_num` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY ( plant_id, user_id, problem_id, generation_num ), 
  KEY parent_plant_id_index ( plant_id ),
  CONSTRAINT parent_plant_id_index FOREIGN KEY ( plant_id ) REFERENCES XG_PlantGenerates( plant_id )
    ON UPDATE CASCADE ON DELETE CASCADE,  
  KEY parent_user_id_index ( user_id ),
  CONSTRAINT parent_user_id_index FOREIGN KEY ( user_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE,
  KEY parent_problem_id_index ( problem_id ),
  CONSTRAINT parent_problem_id_index FOREIGN KEY ( problem_id ) REFERENCES XG_ProblemTraitMadeFor( problem_id )
    ON UPDATE CASCADE ON DELETE CASCADE
    ) ENGINE=InnoDB DEFAULT CHARSET=latin1;
 
-- 
-- Table structure for table `XG_Teaches`
-- 

CREATE TABLE `XG_Teaches` (
  `professor_id` varchar(10) NOT NULL default '',
  `course_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY ( professor_id, course_id ),
  KEY teach_professor_id_index ( professor_id ),
  CONSTRAINT teach_professor_id_index FOREIGN KEY ( professor_id ) REFERENCES User( UserId )
    ON UPDATE CASCADE ON DELETE CASCADE, 
  KEY teach_course_id_index ( course_id ),
  CONSTRAINT teach_course_id_index FOREIGN KEY ( course_id ) REFERENCES Course( CourseId )
    ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

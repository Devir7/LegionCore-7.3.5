DROP TABLE IF EXISTS `creature_template_movement`;
CREATE TABLE `creature_template_movement` (
  `CreatureId` int(10) unsigned NOT NULL DEFAULT '0',
  `Ground` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `Swim` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `Flight` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Rooted` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`CreatureId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `creature_movement_override`;
CREATE TABLE `creature_movement_override` (
  `SpawnId` bigint(20) unsigned NOT NULL DEFAULT '0',
  `Ground` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `Swim` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `Flight` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Rooted` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`SpawnId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `creature_template_movement` SELECT `entry`,0,0,0,0 FROM `creature_template` WHERE `InhabitType`!=3;
UPDATE `creature_template_movement` SET `Ground`=1 WHERE `CreatureId` IN (SELECT `entry` FROM `creature_template` WHERE `InhabitType` & 1);
UPDATE `creature_template_movement` SET `Swim`=1 WHERE `CreatureId` IN (SELECT `entry` FROM `creature_template` WHERE `InhabitType` & 2);
UPDATE `creature_template_movement` SET `Flight`=1 WHERE `CreatureId` IN (SELECT `entry` FROM `creature_template` WHERE (`InhabitType` & 5) = 4);
UPDATE `creature_template_movement` SET `Flight`=2 WHERE `CreatureId` IN (SELECT `entry` FROM `creature_template` WHERE (`InhabitType` & 5) = 5);
UPDATE `creature_template_movement` SET `Rooted`=1 WHERE `CreatureId` IN (SELECT `entry` FROM `creature_template` WHERE `InhabitType` & 8);

ALTER TABLE `creature_template` DROP `InhabitType`;

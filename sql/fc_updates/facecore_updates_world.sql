-- Desolation procs only with BS fix.
DELETE FROM `spell_proc_event` WHERE `entry` IN ('66799','66814','66815','66816','66817');
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
('66799','0','15','4194304','0','0','0','0','0','0','0'), -- Desolation (Rank 1)
('66814','0','15','4194304','0','0','0','0','0','0','0'), -- Desolation (Rank 2)
('66815','0','15','4194304','0','0','0','0','0','0','0'), -- Desolation (Rank 3)
('66816','0','15','4194304','0','0','0','0','0','0','0'), -- Desolation (Rank 4)
('66817','0','15','4194304','0','0','0','0','0','0','0'); -- Desolation (Rank 5)

-- Vampiric Touch dispel fix
DELETE FROM `spell_bonus_data` WHERE `entry` IN ('34914', '64085');
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('34914','0','0.4','0','0','Priest - Vampiric Touch'),
('64085','1.2','0','0','0','Priest - Vampiric Touch');

-- Fix Summon Infernal spell. Thanks inordon fod idea
UPDATE `creature_template` SET flags_extra = 0 WHERE `entry` = 89; 

-- DKs Blood Tap spell fix
DELETE FROM `spell_script_names` WHERE `spell_id`=45529;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (45529, 'spell_dk_blood_tap');

-- Leeeeeeeeroy! achievement fix
UPDATE `instance_template` SET `script`='instance_blackrock_spire' WHERE `map`=229;
UPDATE `creature_template` SET `ScriptName`='npc_rookey_whelp' WHERE entry=10161;
UPDATE `gameobject_template` SET `ScriptName`='go_rookey_egg' WHERE entry=175124;

-- Nature's Grasp fix
DELETE FROM `spell_proc_event` WHERE `entry` IN (16689,16810,16811,16812,16813,17329,27009,53312);
INSERT INTO `spell_proc_event` (`entry`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`procFlags`,`procEx`,`ppmRate`,`CustomChance`,`Cooldown`) VALUES
(16689,0,0,0,0,0,0,0,0,100,1), -- Nature's Grasp (Rank 1)
(16810,0,0,0,0,0,0,0,0,100,1), -- Nature's Grasp (Rank 2)
(16811,0,0,0,0,0,0,0,0,100,1), -- Nature's Grasp (Rank 3)
(16812,0,0,0,0,0,0,0,0,100,1), -- Nature's Grasp (Rank 4)
(16813,0,0,0,0,0,0,0,0,100,1), -- Nature's Grasp (Rank 5)
(17329,0,0,0,0,0,0,0,0,100,1), -- Nature's Grasp (Rank 6)
(27009,0,0,0,0,0,0,0,0,100,1), -- Nature's Grasp (Rank 7)
(53312,0,0,0,0,0,0,0,0,100,1);-- Nature's Grasp (Rank 8)

-- Seals of the Pure fix
DELETE FROM spell_bonus_data WHERE entry IN (25742);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('25742','0','0','0','0','Paladin - Seal of Righteousness Dummy Proc');

-- fix Reign of the Unliving (normal and heroic) proc only from crit
DELETE FROM `spell_proc_event` WHERE entry IN (67712, 67758);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
('67712','0','0','0','0','0','0','2','0','0','2'),
('67758','0','0','0','0','0','0','2','0','0','2');

-- ICC weapons procs
-- (71845) Item - Icecrown 25 Normal Caster Weapon Proc 
DELETE FROM `spell_proc_event` WHERE `entry` IN (71845); 
INSERT INTO `spell_proc_event` VALUES (71845, 0x01, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 2, 40); 
-- (71845) Item - Icecrown 25 Normal Caster Weapon Proc 
DELETE FROM `spell_proc_event` WHERE `entry` IN (71845); 
INSERT INTO `spell_proc_event` VALUES (71845, 0x01, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 2, 45);
-- (71865) Item - Icecrown 25 Normal Healer Weapon Proc 
DELETE FROM `spell_proc_event` WHERE `entry` IN (71865); 
INSERT INTO `spell_proc_event` VALUES (71865, 0x01, 0x0A, 0x00000000, 0x00000000, 0x00000000, 0x00044000, 0x00000018, 0, 1, 0); 
-- (71868) Item - Icecrown 25 Heroic Healer Weapon Proc 
DELETE FROM `spell_proc_event` WHERE `entry` IN (71868); 
INSERT INTO `spell_proc_event` VALUES (71868, 0x01, 0x0A, 0x00000000, 0x00000000, 0x00000000, 0x00044000, 0x00000018, 0, 1, 0); 
-- (71871) Item - Icecrown 25 Normal Tank Weapon Proc 
DELETE FROM `spell_proc_event` WHERE `entry` IN (71871); 
INSERT INTO `spell_proc_event` VALUES (71871, 0x01, 0x0A, 0x00000000, 0x00000000, 0x00000000, 0x00000014, 0x00000018, 0, 37, 30); 
-- (71873) Item - Icecrown 25 Heroic Tank Weapon Proc 
DELETE FROM `spell_proc_event` WHERE `entry` IN (71873); 
INSERT INTO `spell_proc_event` VALUES (71873, 0x01, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x00000014, 0x00000018, 0, 37, 35);

-- Divine Storm heal effect fix
DELETE FROM `spell_bonus_data` WHERE `entry` IN ('54172');
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('54172','0','0','0','0','Paladin - Divine Storm');

DELETE FROM `spell_dbc` WHERE `Id` IN ('199997');
INSERT INTO `spell_dbc` (`Id`, `Dispel`, `Mechanic`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `Stances`, `StancesNot`, `Targets`, `CastingTimeIndex`, `AuraInterruptFlags`, `ProcFlags`, `ProcChance`, `ProcCharges`, `MaxLevel`, `BaseLevel`, `SpellLevel`, `DurationIndex`, `RangeIndex`, `StackAmount`, `EquippedItemClass`, `EquippedItemSubClassMask`, `EquippedItemInventoryTypeMask`, `Effect1`, `Effect2`, `Effect3`, `EffectDieSides1`, `EffectDieSides2`, `EffectDieSides3`, `EffectRealPointsPerLevel1`, `EffectRealPointsPerLevel2`, `EffectRealPointsPerLevel3`, `EffectBasePoints1`, `EffectBasePoints2`, `EffectBasePoints3`, `EffectMechanic1`, `EffectMechanic2`, `EffectMechanic3`, `EffectImplicitTargetA1`, `EffectImplicitTargetA2`, `EffectImplicitTargetA3`, `EffectImplicitTargetB1`, `EffectImplicitTargetB2`, `EffectImplicitTargetB3`, `EffectRadiusIndex1`, `EffectRadiusIndex2`, `EffectRadiusIndex3`, `EffectApplyAuraName1`, `EffectApplyAuraName2`, `EffectApplyAuraName3`, `EffectAmplitude1`, `EffectAmplitude2`, `EffectAmplitude3`, `EffectMultipleValue1`, `EffectMultipleValue2`, `EffectMultipleValue3`, `EffectMiscValue1`, `EffectMiscValue2`, `EffectMiscValue3`, `EffectMiscValueB1`, `EffectMiscValueB2`, `EffectMiscValueB3`, `EffectTriggerSpell1`, `EffectTriggerSpell2`, `EffectTriggerSpell3`, `EffectSpellClassMaskA1`, `EffectSpellClassMaskA2`, `EffectSpellClassMaskA3`, `EffectSpellClassMaskB1`, `EffectSpellClassMaskB2`, `EffectSpellClassMaskB3`, `EffectSpellClassMaskC1`, `EffectSpellClassMaskC2`, `EffectSpellClassMaskC3`, `MaxTargetLevel`, `SpellFamilyName`, `SpellFamilyFlags1`, `SpellFamilyFlags2`, `SpellFamilyFlags3`, `MaxAffectedTargets`, `DmgClass`, `PreventionType`, `DmgMultiplier1`, `DmgMultiplier2`, `DmgMultiplier3`, `AreaGroupId`, `SchoolMask`, `Comment`) VALUES
('199997','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','1','0','-1','0','0','6','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','Divine Storm Helper (SERVERSIDE)');

DELETE FROM `spell_proc_event` WHERE `entry` IN ('199997');
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
('199997','0','10','0','131072','0','16','0','0','100','0');

-- The Valiant's Challenge
UPDATE `creature_template` SET `ScriptName` = 'npc_squire_danny' WHERE `entry` = 33518;
UPDATE `creature_template` SET `KillCredit1` = 33708 WHERE `entry` = 33707;
UPDATE `creature_template` SET `ScriptName` = 'npc_argent_champion' WHERE `entry` = 33707;
DELETE FROM `creature_template_addon` WHERE `entry` = 33707;
INSERT INTO `creature_template_addon` (`entry`, `mount`) VALUES ('33707', '14337');

-- prevent bagouse varlock's summon spell on battlegrounds
DELETE FROM `disables` WHERE `sourceType`=0 and `entry` = 698;
INSERT INTO `disables` VALUES (0, 698, (1+16+32), "489,529,529,566", "4572,4571,3417,3418,3820", "Ritual of Summoning spell on BG");

-- Fizzcrank Recon Pilot
DELETE FROM `creature_ai_scripts` WHERE creature_id = 25841;
UPDATE `creature_template` SET IconName = 'Speak', npcflag = 1, gossip_menu_id = 0, AIName = '', ScriptName = 'npc_recon_pilot', unit_flags = 0x00000000, flags_extra = 2, dynamicflags = 36  WHERE entry = 25841;
DELETE FROM `creature_template_addon` WHERE entry = 25841;
INSERT INTO `creature_template_addon` VALUES (25841, 0, 0, 7, 0, 65, '');
UPDATE `creature` SET DeathState = 0 WHERE id = 25841;

-- Open Halls of Reflection without quest
UPDATE `access_requirement` set `quest_done_A`=0, `quest_done_H`=0 where `mapId` = 668;

-- Item - Hunter T10 Survival 2P Bonus
DELETE FROM `spell_proc_event` WHERE `entry` = 70727;
INSERT INTO `spell_proc_event` VALUES (70727, 0, 9, 0, 0, 0, 64, 0, 0, 5, 0); 
-- Item - Hunter T10 Survival 4P Bonus
DELETE FROM `spell_proc_event` WHERE `entry` = 70730;
INSERT INTO `spell_proc_event` VALUES (70730, 0, 9, 16384, 4096, 0, 262144, 0, 0, 5, 0);  

-- fix Magister Hathorel and Arcanist Tybalin scriptname
UPDATE `creature_template` SET `ScriptName` = 'npc_magister_hathorel' WHERE `entry` = 36670;
UPDATE `creature_template` SET `ScriptName` = 'npc_arcanist_tybalin' WHERE `entry` = 36669;

-- set visible intendants of The Sons of Hodir and Knights of the Ebon Blade
UPDATE `creature` SET phaseMask=65535 WHERE `id` in (32538,32540);

-- Open access to heroic ICC without achievement
UPDATE `access_requirement` SET `completed_achievement`=0 WHERE `mapId`=631 and `difficulty` in (2,3);

-- [Dungeon Finder] Fix Drak'Tharon Keep reward for DF
UPDATE `instance_encounters` SET `creditType` = '0', `creditEntry` = '26632' WHERE `entry` IN ('376', '375');
-- [Dungeon Finder] Fix reward for Utgarde Keep.
UPDATE `instance_encounters` SET `creditEntry` = '23980' WHERE `entry` IN ('575', '576');
-- [Dungeon Finder] Fix CoS reward
UPDATE `instance_encounters` SET `creditType`=0, `creditEntry`=26533 WHERE `entry` IN (296, 300);

-- Master Poisoner fix
DELETE FROM `spell_dbc` WHERE `Id` IN ('45176');
INSERT INTO `spell_dbc` (`Id`, `Dispel`, `Mechanic`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `Stances`, `StancesNot`, `Targets`, `CastingTimeIndex`, `AuraInterruptFlags`, `ProcFlags`, `ProcChance`, `ProcCharges`, `MaxLevel`, `BaseLevel`, `SpellLevel`, `DurationIndex`, `RangeIndex`, `StackAmount`, `EquippedItemClass`, `EquippedItemSubClassMask`, `EquippedItemInventoryTypeMask`, `Effect1`, `Effect2`, `Effect3`, `EffectDieSides1`, `EffectDieSides2`, `EffectDieSides3`, `EffectRealPointsPerLevel1`, `EffectRealPointsPerLevel2`, `EffectRealPointsPerLevel3`, `EffectBasePoints1`, `EffectBasePoints2`, `EffectBasePoints3`, `EffectMechanic1`, `EffectMechanic2`, `EffectMechanic3`, `EffectImplicitTargetA1`, `EffectImplicitTargetA2`, `EffectImplicitTargetA3`, `EffectImplicitTargetB1`, `EffectImplicitTargetB2`, `EffectImplicitTargetB3`, `EffectRadiusIndex1`, `EffectRadiusIndex2`, `EffectRadiusIndex3`, `EffectApplyAuraName1`, `EffectApplyAuraName2`, `EffectApplyAuraName3`, `EffectAmplitude1`, `EffectAmplitude2`, `EffectAmplitude3`, `EffectMultipleValue1`, `EffectMultipleValue2`, `EffectMultipleValue3`, `EffectMiscValue1`, `EffectMiscValue2`, `EffectMiscValue3`, `EffectMiscValueB1`, `EffectMiscValueB2`, `EffectMiscValueB3`, `EffectTriggerSpell1`, `EffectTriggerSpell2`, `EffectTriggerSpell3`, `EffectSpellClassMaskA1`, `EffectSpellClassMaskA2`, `EffectSpellClassMaskA3`, `EffectSpellClassMaskB1`, `EffectSpellClassMaskB2`, `EffectSpellClassMaskB3`, `EffectSpellClassMaskC1`, `EffectSpellClassMaskC2`, `EffectSpellClassMaskC3`, `MaxTargetLevel`, `SpellFamilyName`, `SpellFamilyFlags1`, `SpellFamilyFlags2`, `SpellFamilyFlags3`, `MaxAffectedTargets`, `DmgClass`, `PreventionType`, `DmgMultiplier1`, `DmgMultiplier2`, `DmgMultiplier3`, `AreaGroupId`, `SchoolMask`, `Comment`) VALUES
('45176','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','1','1','1','0','1','0','-1','0','0','3','0','0','0','0','0','0','0','0','0','0','0','0','0','0','6','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','8','0','0','0','0','0','0','0','0','0','0','1','Master Poisoner Trigger (SERVERSIDE)');
DELETE FROM `spell_proc_event` WHERE `entry` IN ('31226', '31227', '58410');
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
('31226','0','8','0','524288','0','0','0','0','0','0'), -- Master Poisoner (Rank 1)
('31227','0','8','0','524288','0','0','0','0','0','0'), -- Master Poisoner (Rank 2)
('58410','0','8','0','524288','0','0','0','0','0','0'); -- Master Poisoner (Rank 3)

-- Deadly Poison fix
DELETE FROM `spell_bonus_data` WHERE `entry` IN ('2818');
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('2818','0','0','0','0.03','Rogue - Deadly Poison Rank 1($AP*0.12 / number of ticks)');
DELETE FROM `spell_script_names` WHERE `spell_id` IN ('-2818');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('-2818','spell_rog_deadly_poison');

-- Envenom fix
DELETE FROM `spell_bonus_data` WHERE `entry` IN ('32645');
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('32645','0','0','0','0','Rogue - Envenom');

-- Threat of Thassarian fix
DELETE FROM `spell_proc_event` WHERE `entry` IN (65661,66191,66192);
INSERT INTO `spell_proc_event` (`entry`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`procFlags`,`procEx`,`ppmRate`,`CustomChance`,`Cooldown`) VALUES
(65661,0,15,0x00400011,0x20020004,0x00000000,16,0,0,100,0), -- Threat of Thassarian - Rank1
(66191,0,15,0x00400011,0x20020004,0x00000000,16,0,0,100,0), -- Threat of Thassarian - Rank2
(66192,0,15,0x00400011,0x20020004,0x00000000,16,0,0,100,0); -- Threat of Thassarian - Rank3

-- fix for YTDB after "guards don't evade..." commit
UPDATE `creature_template` SET `Unit_flags` = 36864 WHERE `entry` = 3296;

-- Isle of Conquest bosses aggro through wall fix
UPDATE `creature_template` SET `unit_flags` = 256 WHERE `entry` = 34924;
UPDATE `creature_template` SET `unit_flags` = 256 WHERE `entry` = 34922;
UPDATE `creature_template` SET `unit_flags` = 256 WHERE `entry` = 34918;
UPDATE `creature_template` SET `unit_flags` = 256 WHERE `entry` = 34919;

-- another fix for YTDB for unit_flags 
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 16844;
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 16857;
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 16968;
UPDATE `creature_template` SET `unit_flags` = 32768 WHERE `entry` = 25760;
UPDATE `creature_template` SET `Unit_flags` = 36864 WHERE `entry` = 3296;
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 26076;
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 26073;

-- fix flag for Sunreaver Agent NPC.
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 36776;

-- fix flag for Silver Covenant Agent
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 36774; 

-- DB/Achievements: Fix achievement "Lonely?"
UPDATE `gameobject_template` SET `data10`=45123 WHERE `entry`=187267;

-- Dangerous Love achievement
-- Alliance
UPDATE quest_template SET prevQuestID = 0 where ExclusiveGroup = 24638;
-- Horde
UPDATE quest_template SET prevQuestID = 0 where ExclusiveGroup = 24658;
-- Alliance
UPDATE quest_template SET prevQuestID = 24576 where ExclusiveGroup = 24638;
-- Horde
UPDATE quest_template SET prevQuestID = 24657 where ExclusiveGroup = 24658;

-- Cinderglacier
UPDATE `spell_proc_event` SET `SpellFamilyName` = '15', `SpellFamilyMask0` = 0x42002, `SpellFamilyMask1` = 0x6, `SpellFamilyMask2` = 0x80 WHERE `entry` = 53386;

-- Druid Berserk fix
DELETE FROM `spell_script_names` WHERE `spell_id`=50334 AND `ScriptName`='spell_dru_berserk';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(50334, 'spell_dru_berserk');

-- Fix spell 66926 for quest "They Grow Up So Fast"
DELETE FROM `spell_script_names` WHERE `spell_id`=66926;
INSERT INTO `spell_script_names` VALUES
(66926, 'spell_gen_venomhide_check');

-- Lifebloom final bloom fix
UPDATE `spell_bonus_data` SET `direct_bonus`=0.3857 WHERE `entry`=33778 ;
UPDATE `spell_bonus_data` SET `dot_bonus`=0.0653 WHERE `entry` IN (48450, 48451, 48628);

-- Ashbringer sound effect fix
DELETE FROM `spell_script_names` WHERE `spell_id`=28441;
INSERT INTO `spell_script_names` VALUES
(28441, 'spell_ashbringer_sound_effect');

-- fix some quests in Borean Tundra
UPDATE creature_template SET scriptname = 'vehicle_wyrmrest_skytalon' WHERE entry = 32535;

-- Add script for Archmage Vargoth NPC(19481)
UPDATE creature_template SET scriptname = 'npc_archmage_vargoth' WHERE entry = 19481;

-- Add scripts for some NPC in Dragon Blight
UPDATE creature_template SET scriptname = 'vehicle_forsaken_blight_spreader' WHERE entry = 26523;
UPDATE creature_template SET scriptname = 'npc_warsong_battle_standard' WHERE entry = 26678;
UPDATE creature_template SET scriptname = 'npc_emissary_brighthoof' WHERE entry = 26181;
UPDATE creature_template SET scriptname = 'npc_wintergarde_mine_bomb' WHERE entry = 27435;
UPDATE creature_template SET scriptname = 'npc_devout_bodyguard' WHERE entry = 27247;
UPDATE creature_template SET scriptname = 'npc_high_abbot_landgren' WHERE entry = 27245;
UPDATE creature_template SET scriptname = 'npc_agent_skully' WHERE entry = 27350;
UPDATE creature_template SET scriptname = 'npc_7th_legion_siege_engineer' WHERE entry = 27163;
UPDATE creature_template SET scriptname = 'vehicle_alliance_steamtank' WHERE entry = 27587;
UPDATE creature_template SET scriptname = 'mob_woodlands_walker' WHERE entry = 26421;

-- Bone Shield Charges Cooldown
DELETE FROM `spell_dbc` WHERE `Id`=250000;
INSERT INTO `spell_dbc` (`Id`, `Dispel`, `Mechanic`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `Stances`, `StancesNot`, `Targets`, `CastingTimeIndex`, `AuraInterruptFlags`, `ProcFlags`, `ProcChance`, `ProcCharges`, `MaxLevel`, `BaseLevel`, `SpellLevel`, `DurationIndex`, `RangeIndex`, `StackAmount`, `EquippedItemClass`, `EquippedItemSubClassMask`, `EquippedItemInventoryTypeMask`, `Effect1`, `Effect2`, `Effect3`, `EffectDieSides1`, `EffectDieSides2`, `EffectDieSides3`, `EffectRealPointsPerLevel1`, `EffectRealPointsPerLevel2`, `EffectRealPointsPerLevel3`, `EffectBasePoints1`, `EffectBasePoints2`, `EffectBasePoints3`, `EffectMechanic1`, `EffectMechanic2`, `EffectMechanic3`, `EffectImplicitTargetA1`, `EffectImplicitTargetA2`, `EffectImplicitTargetA3`, `EffectImplicitTargetB1`, `EffectImplicitTargetB2`, `EffectImplicitTargetB3`, `EffectRadiusIndex1`, `EffectRadiusIndex2`, `EffectRadiusIndex3`, `EffectApplyAuraName1`, `EffectApplyAuraName2`, `EffectApplyAuraName3`, `EffectAmplitude1`, `EffectAmplitude2`, `EffectAmplitude3`, `EffectMultipleValue1`, `EffectMultipleValue2`, `EffectMultipleValue3`, `EffectMiscValue1`, `EffectMiscValue2`, `EffectMiscValue3`, `EffectMiscValueB1`, `EffectMiscValueB2`, `EffectMiscValueB3`, `EffectTriggerSpell1`, `EffectTriggerSpell2`, `EffectTriggerSpell3`, `EffectSpellClassMaskA1`, `EffectSpellClassMaskA2`, `EffectSpellClassMaskA3`, `EffectSpellClassMaskB1`, `EffectSpellClassMaskB2`, `EffectSpellClassMaskB3`, `EffectSpellClassMaskC1`, `EffectSpellClassMaskC2`, `EffectSpellClassMaskC3`, `MaxTargetLevel`, `SpellFamilyName`, `SpellFamilyFlags1`, `SpellFamilyFlags2`, `SpellFamilyFlags3`, `MaxAffectedTargets`, `DmgClass`, `PreventionType`, `DmgMultiplier1`, `DmgMultiplier2`, `DmgMultiplier3`, `AreaGroupId`, `SchoolMask`, `Comment`) VALUES
(250000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 8, 1, 0, -1, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 'Bone Shield Charges Cooldown');

-- Fix Koralon's Meteor Fists
DELETE FROM spell_script_names WHERE spell_id = 66765;
INSERT INTO spell_script_names VALUES 
(66765, "spell_koralon_meteor_fists");

DELETE FROM `creature_model_info` WHERE (`modelid`=29524);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`) VALUES (29524, 0.45, 8, 2, 0);

-- Fix Battleground Demolisher (http://www.wowhead.com/npc=28781) HP
UPDATE `creature_template` SET `exp` = 0 WHERE `entry` = 32796;

-- Fix Explosive shot from spd scaling
DELETE FROM `spell_bonus_data` WHERE `entry`='53352';
INSERT INTO `spell_bonus_data`(`entry`,`direct_bonus`,`dot_bonus`,`ap_bonus`,`ap_dot_bonus`,`comments`) VALUES ( '53352','0','0','0.14','0','Hunter - Explosive Shot (triggered)');

-- Fix Isle of Conquest
DELETE FROM npc_spellclick_spells WHERE npc_entry IN (35413, 35419, 35431, 35433);
INSERT INTO npc_spellclick_spells (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`, `aura_required`, `aura_forbidden`, `user_type`) VALUES
(35413, 60968, 0, 0, 0, 1, 0, 0, 0),
(35419, 68503, 0, 0, 0, 1, 0, 0, 0),
(35431, 46598, 0, 0, 0, 1, 0, 0, 0),
(35433, 46598, 0, 0, 0, 1, 0, 0, 0); 

-- Bloodworm AI
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 28017;
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
(2801700, 28017, 4, 0, 100, 0, 0, 0, 0, 0, 11, 50453, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Bloodworm - Health Leech');

-- Lorvo and aysa guid is wrong. In our db Aysa(entry 54567) has 3 guids 563511,563545,571938   , Lorvo(entry 54943) has 2 guids 563517,571937.You must check the quest in game which guids should apply these auras.
-- DELETE FROM `creature_addon` WHERE `guid`=224522;
-- INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
-- (224522, '80797');
--
-- DELETE FROM `creature_addon` WHERE `guid`=224519; 
-- INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
-- (224519, '80797');
--
-- DELETE FROM `creature_addon` WHERE `guid`=224593;
-- INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
-- (224593, '82358');
--
-- DELETE FROM `creature_addon` WHERE `guid`=224592; 
-- INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
--(224592, '82358');

DELETE FROM `spell_area` WHERE `spell`=102393;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(102393, 5846, 0, 29419, 0, 0, 2, 1, 64, 9),
(102393, 5825, 0, 29419, 0, 0, 2, 1, 64, 9);

DELETE FROM `spell_area` WHERE `spell`=102395;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(102395, 5846, 0, 29419, 0, 0, 2, 1, 64, 2),
(102395, 5825, 0, 29419, 0, 0, 2, 1, 64, 2);

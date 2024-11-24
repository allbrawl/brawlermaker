#include "brawler.h"
#include "brawlermaker.h"
#include <csv.h>
#include <stdexcept>
#include <iostream>
#include <csv.h>

int toint(std::string s, int fallback)
{
    try
    {
        return stoi(s);
    }
    catch (const std::exception &e)
    {
        return fallback;
    }
}

std::vector<Brawler> BrawlerMaker::getBrawlers(const std::string charactersCSVPath, const std::string cardsCSVPath, const std::string skillsCSVPath, const std::string textsCSVPath, bool ignoreNonHeros) const
{
    CSVHandler handle;
    std::vector<Brawler> brawlers;
    auto rows = handle.getRows(charactersCSVPath);
    auto cardsRows = handle.getRows(cardsCSVPath);
    auto skillsRows = handle.getRows(skillsCSVPath);
    auto textsRows = handle.getRows(textsCSVPath);
    auto charactersColumns = handle.getColumns(charactersCSVPath);
    auto cardsColumns = handle.getColumns(cardsCSVPath);
    auto skillsColumns = handle.getColumns(skillsCSVPath);

    bool datatypes = true;

    for (auto &row : rows)
    {
        if (datatypes)
        {
            datatypes = false;
            continue;
        }
        Brawler brawler;
        std::string type = row[20];
        if (type != "Hero" && ignoreNonHeros == true)
        {
            continue;
        }
        brawler.codename = row[0];
        brawler.tid = row[77];

        brawler.weaponSkill = row[4];
        brawler.ultimateSkill = row[5];

        brawler.speed = toint(row[7], UNDEFINED);
        brawler.health = toint(row[8], UNDEFINED);

        brawler.iconSWF = row[80];
        brawler.icon = row[81];
        brawler.pet = row[6];

        brawler.scale = toint(row[61], UNDEFINED);

        brawler.attackRechargeUltimateAmount = toint(row[18], UNDEFINED);

        brawler.ultimateRechargeUltimateAmount = toint(row[19], UNDEFINED);

        for (auto &skillsRow : skillsRows)
        {
            if (skillsRow[0] == brawler.weaponSkill)
            {
                try
                {
                    brawler.ultimateReloadTime = toint(skillsRow[14], UNDEFINED);

                    brawler.weaponReloadTime = toint(skillsRow[14], UNDEFINED);
                    brawler.weaponAmmoCount = toint(skillsRow[15], UNDEFINED);
                    brawler.weaponDamage = toint(skillsRow[16], UNDEFINED);
                    brawler.attackSpread = toint(skillsRow[19], UNDEFINED);
                    brawler.attackProjectileCount = toint(skillsRow[21], UNDEFINED);
                    brawler.weaponTimeBetweenAttacks = toint(skillsRow[18], UNDEFINED);
                    brawler.attackDuration = toint(skillsRow[7], UNDEFINED);
                    brawler.weaponRange = toint(skillsRow[9], UNDEFINED);
                    brawler.attackProjectile = toint(skillsRow[handle.getColumnIndex(skillsColumns, "AttackProjectile")], UNDEFINED);
                }

                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << " at line " << __LINE__ << " indentifier " << skillsRow[0] << std::endl;
                    throw;
                }
            }
            if (skillsRow[0] == brawler.ultimateSkill)
            {
                try
                {

                    brawler.ultimateDamage = toint(skillsRow[16], UNDEFINED);

                    brawler.ultimateSpread = toint(skillsRow[19], UNDEFINED);

                    brawler.ultimateProjectileCount = 0;

                    brawler.ultimateProjectileCount = toint(skillsRow[21], UNDEFINED);

                    brawler.ultimateAttackDuration = toint(skillsRow[7], UNDEFINED);

                    brawler.summonedCharacter == skillsRow[handle.getColumnIndex(skillsColumns, "SummonedCharacter")];

                    brawler.ultimateRange = toint(skillsRow[9], UNDEFINED);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << " at line " << __LINE__ << " identifier " << skillsRow[0] << std::endl;
                    throw;
                }
            }
        }

        std::string weaponTID;
        std::string ultimateTID;
        for (auto &cardsRow : cardsRows)
        {
            if (cardsRow[3] == brawler.codename)
            {
                if (cardsRow[8] == "unlock")
                {
                    brawler.number = toint(cardsRow[handle.getColumnIndex(cardsColumns, "SortOrder")], UNDEFINED);
                    const std::string csvRarity = cardsRow[13];
                    if (csvRarity == "common")
                        brawler.rarity = Rarity::TrophyRoad;
                    else if (csvRarity == "rare")
                        brawler.rarity = Rarity::Rare;
                    else if (csvRarity == "super_rare")
                        brawler.rarity = Rarity::SuperRare;
                    else if (csvRarity == "epic")
                        brawler.rarity = Rarity::Epic;
                    else if (csvRarity == "mega_epic")
                        brawler.rarity = Rarity::Mythic;
                    else if (csvRarity == "legendary")
                        brawler.rarity = Rarity::Legendary;
                    break;
                }
                else if (cardsRow[9] == brawler.weaponSkill)
                {
                    weaponTID = cardsRow[14];
                }
                else if (cardsRow[9] == brawler.ultimateSkill)
                {
                    ultimateTID = cardsRow[14];
                }
            }
        }

        for (auto &textsRow : textsRows)
        {
            if (textsRow[0] == brawler.tid)
            {
                brawler.codename = textsRow[1];
            }
            if (textsRow[0] == brawler.tid + "_DESC")
            {
                brawler.description = textsRow[1];
                break;
            }
            else if (textsRow[0] == weaponTID)
            {
                brawler.weaponName = textsRow[1];
                break;
            }
            else if (textsRow[0] == ultimateTID)
            {
                brawler.ultimateName = textsRow[1];
                break;
            }
            else if (textsRow[0] == weaponTID + "_DESC")
            {
                brawler.weaponDescription = textsRow[1];
                break;
            }
            else if (textsRow[0] == ultimateTID + "_DESC")
            {
                brawler.ultimateDescription = textsRow[1];
                break;
            }
        }
        brawlers.push_back(brawler);
    }
    return brawlers;
}

int addBrawler(const Brawler &brawler, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath)
{
    CSVHandler csv;
    CSV characters = csv.readCSV(charactersCSVPath);
    std::vector<std::string> newCharacter = {brawler.codename, "", "", "bull", brawler.codename + "Weapon", brawler.codename + "Ulti", "",
                                             std::to_string(brawler.speed), std::to_string(brawler.health), "", "", "", "",
                                             "", "", "", "12", "", std::to_string(brawler.attackRechargeUltimateAmount), std::to_string(brawler.ultimateRechargeUltimateAmount), "Hero", "", brawler.codename + "Default", "",
                                             "", "",
                                             "", "", "", "takedamage_gen", "death_shotgun_girl", "Gen_move_fx", "reload_shotgun_girl",
                                             "No_ammo_shotgungirl", "Dry_fire_shotgungirl", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                             "", "", "30", "", "80", "80", "", "", "35", std::to_string(brawler.scale), "210", "284", "90", "175", "260", "", "", "", "-25",
                                             "40", "120", "Medium", "-48", "", "450", "", "", brawler.tid, "", "sc/ui.sc",
                                             "hero_icon_" + brawler.icon, "0", "human", "footstep", "25", "250", "200", "", "", "1", "3", "2", "", "", "", "",
                                             "", "", "", "", "", "ShellyTutorial", "", "", "", "", "", "3", "3", "3"};
    characters.rows.push_back(newCharacter);
    csv.writeCSV(charactersCSVPath, characters);

    CSV cards = csv.readCSV(cardsCSVPath);
    std::string rarity;
    if (brawler.rarity == Rarity::Rare)
    {
        rarity = "rare";
    }
    else if (brawler.rarity == Rarity::SuperRare)
    {
        rarity = "super_rare";
    }
    else if (brawler.rarity == Rarity::Epic)
    {
        rarity = "epic";
    }
    else if (brawler.rarity == Rarity::Mythic)
    {
        rarity = "mega_epic";
    }
    else if (brawler.rarity == Rarity::Legendary)
    {
        rarity = "legendary";
    }
    else
    {
        rarity = "common";
    }

    std::vector<std::string> card_unlock = {brawler.codename + "_unlock", "sc/ui.sc", "", brawler.codename, "", "", "0", "", "unlock", "", "",
                                            "", "", rarity,
                                            "", "", "", "", "", "", std::to_string(brawler.number), ""};

    cards.rows.push_back(card_unlock);

    std::vector<std::string> card_hp = {brawler.codename + "_hp", "sc/ui.sc", "health_icon", brawler.codename, "", "", "1", "", "hp", "", "",
                                        "", "",
                                        "common", "TID_ARMOR", "TID_ARMOR", "", "", "genicon_health", "", "", ""};

    cards.rows.push_back(card_hp);

    std::vector<std::string> card_weapon = {brawler.codename + "_abi", "sc/ui.sc", "attack_icon", brawler.codename, "", "", "2", "", "skill",
                                            brawler.codename + "Weapon", "", "", "", "common", brawler.tid + "_WEAPON",
                                            "TID_STAT_DAMAGE", "", "", "genicon_damage", "", "", ""};

    cards.rows.push_back(card_weapon);

    std::vector<std::string> card_ulti = {brawler.codename + "_ulti", "sc/ui.sc", "ulti_icon", brawler.codename, "", "", "3", "", "skill",
                                          brawler.codename + "Ulti", "", "", "", "common", brawler.tid + "_ULTI",
                                          "TID_STAT_DAMAGE", "", "", "genicon_damage", "", "", ""};

    cards.rows.push_back(card_ulti);

    csv.writeCSV(cardsCSVPath, cards);

    auto skills = csv.readCSV(skillsCSVPath);

    std::vector<std::string> weapon_skill = {brawler.codename + "Weapon", "Attack", "true", "true", "true", "", "50", std::to_string(brawler.attackDuration), "",
                                             std::to_string(brawler.weaponRange), "", "",
                                             "", "", std::to_string(brawler.weaponReloadTime), std::to_string(brawler.weaponAmmoCount), std::to_string(brawler.weaponDamage), "", std::to_string(brawler.weaponTimeBetweenAttacks),
                                             std::to_string(brawler.attackSpread), "", std::to_string(brawler.attackProjectileCount), "",
                                             "true", "", "", "", "", "", "", "", "", brawler.attackProjectile, "", "", "", "", "", "", "", "",
                                             "sc/ui.sc", "rapid_fire_button", "rico_def_atk", "", "", "", "", "", "", "", "", "", "", "", ""};

    std::vector<std::string> ultimate_skill = {brawler.codename + "Ulti", "Attack", "true", "true", "true", "", "50", std::to_string(brawler.ultimateAttackDuration), "",
                                               std::to_string(brawler.ultimateRange), "", "",
                                               "", "", "", "", std::to_string(brawler.ultimateDamage), "", std::to_string(brawler.ultimateTimeBetweenAttacks), std::to_string(brawler.ultimateSpread), "",
                                               std::to_string(brawler.ultimateProjectileCount), "",
                                               "true", "", "", "", "", "", "", "", "", brawler.ultimateProjectile, "", "", "", "", "", "", "", "",
                                               "sc/ui.sc", "rapid_fire_button", "rico_def_atk", "", "", "", "", "", "", "", "", "", "", "", ""};
}
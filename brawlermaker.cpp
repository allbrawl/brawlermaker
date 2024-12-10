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

Brawler BrawlerMaker::getBrawler(const std::string tid, const std::string charactersCSVPath, const std::string cardsCSVPath, const std::string skillsCSVPath, const std::string textsCSVPath) const
{
    CSVHandler csv;
    Brawler brawler;
    auto characters = csv.readCSV(charactersCSVPath);
    auto cards = csv.readCSV(cardsCSVPath);
    auto skills = csv.readCSV(skillsCSVPath);
    auto texts = csv.readCSV(textsCSVPath);

    for (auto &row : characters.rows)
    {
        if (row[characters.getColumnIndex("TID")] != tid)
        {
            continue;
        }
        std::string type = row["Type"];
        brawler.codename = row["Name"];

        brawler.tid = row["TID"];

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

        for (auto &skillsRow : skills.rows)
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
                    brawler.attackProjectile = skillsRow[skills.getColumnIndex("Projectile")];
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
                    brawler.summonedCharacter == skillsRow[skills.getColumnIndex("SummonedCharacter")];
                    brawler.ultimateRange = toint(skillsRow[9], UNDEFINED);
                    brawler.ultimateProjectile = skillsRow[skills.getColumnIndex("Projectile")];
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << " at line " << __LINE__ << " identifier " << skillsRow[0] << std::endl;
                    throw;
                }
            }
        }

        for (auto &cardsRow : cards.rows)
        {
            if (cardsRow[3] == brawler.codename)
            {
                if (cardsRow[cards.getColumnIndex("Type")] == "unlock")
                {
                    brawler.number = toint(cardsRow[cards.getColumnIndex("SortOrder")], UNDEFINED);
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
                }
                else if (cardsRow[cards.getColumnIndex("Type")] == "skill")
                {
                    if (cardsRow[cards.getColumnIndex("Skill")] == brawler.weaponSkill)
                    {
                        brawler.weaponTID = cardsRow[cards.getColumnIndex("TID")];
                    }
                    else if (cardsRow[cards.getColumnIndex("Skill")] == brawler.ultimateSkill)
                    {
                        brawler.ultimateTID = cardsRow[cards.getColumnIndex("TID")];
                    }
                }
            }
        }

        for (auto &textsRow : texts.rows)
        {
            if (textsRow[0] == brawler.tid)
            {
                brawler.name = textsRow[1];
            }
            else if (textsRow[0] == brawler.tid + "_DESC")
            {
                brawler.description = textsRow[1];
            }
            else if (textsRow[0] == brawler.tid + "_SHORT_DESC")
            {
                brawler.shortDescription = textsRow[1];
            }
            else if (textsRow[0] == brawler.weaponTID)
            {
                brawler.weaponName = textsRow[1];
            }
            else if (textsRow[0] == brawler.ultimateTID)
            {
                brawler.ultimateName = textsRow[1];
            }
            else if (textsRow[0] == brawler.weaponTID + "_DESC")
            {
                brawler.weaponDescription = textsRow[1];
            }
            else if (textsRow[0] == brawler.ultimateTID + "_DESC")
            {
                brawler.ultimateDescription = textsRow[1];
            }
        }
        break;
    }
    return brawler;
}

std::vector<Brawler> BrawlerMaker::getBrawlers(std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath, bool ignoreNonHeros)
{
    CSVHandler csv;
    auto characters = csv.readCSV(charactersCSVPath);
    std::vector<Brawler> brawlers;
    bool datatypes = true;
    for (auto row : characters.rows)
    {
        if (datatypes)
        {
            datatypes = false;
            continue;
        }
        if (ignoreNonHeros && row[characters.getColumnIndex("Type")] != "Hero")
        {
            continue;
        }
        Brawler brawler;
        brawler = getBrawler(row[characters.getColumnIndex("TID")], charactersCSVPath, cardsCSVPath, skillsCSVPath, textsCSVPath);
        brawlers.push_back(brawler);
    }
    return brawlers;
}

int BrawlerMaker::addBrawler(const Brawler &brawler, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath)
{
    CSVHandler csv;
    CSV characters = csv.readCSV(charactersCSVPath);
    Row newCharacter = {brawler.codename, "", "", "bull", brawler.codename + "Weapon", brawler.codename + "Ulti", "",
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
    characters.writeCSV();

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

    std::vector<std::string> cardUnlock = {brawler.codename + "_unlock", "sc/ui.sc", "", brawler.codename, "", "", "0", "", "unlock", "", "",
                                           "", "", rarity,
                                           "", "", "", "", "", "", std::to_string(brawler.number), ""};

    cards.rows.push_back(cardUnlock);

    std::vector<std::string> cardHP = {brawler.codename + "_hp", "sc/ui.sc", "health_icon", brawler.codename, "", "", "1", "", "hp", "", "",
                                       "", "",
                                       "common", "TID_ARMOR", "TID_ARMOR", "", "", "genicon_health", "", "", ""};

    cards.rows.push_back(cardHP);

    std::vector<std::string> cardWeapon = {brawler.codename + "_abi", "sc/ui.sc", "attack_icon", brawler.codename, "", "", "2", "", "skill",
                                           brawler.codename + "Weapon", "", "", "", "common", brawler.tid + "_WEAPON",
                                           "TID_STAT_DAMAGE", "", "", "genicon_damage", "", "", ""};

    cards.rows.push_back(cardWeapon);

    std::vector<std::string> cardUlti = {brawler.codename + "_ulti", "sc/ui.sc", "ulti_icon", brawler.codename, "", "", "3", "", "skill",
                                         brawler.codename + "Ulti", "", "", "", "common", brawler.tid + "_ULTI",
                                         "TID_STAT_DAMAGE", "", "", "genicon_damage", "", "", ""};

    cards.rows.push_back(cardUlti);

    cards.writeCSV();

    auto skills = csv.readCSV(skillsCSVPath);

    std::vector<std::string> weaponSkill = {brawler.codename + "Weapon", "Attack", "true", "true", "true", "", "50", std::to_string(brawler.attackDuration), "",
                                            std::to_string(brawler.weaponRange), "", "",
                                            "", "", std::to_string(brawler.weaponReloadTime), std::to_string(brawler.weaponAmmoCount), std::to_string(brawler.weaponDamage), "", std::to_string(brawler.weaponTimeBetweenAttacks),
                                            std::to_string(brawler.attackSpread), "", std::to_string(brawler.attackProjectileCount), "",
                                            "true", "", "", "", "", "", "", "", "", brawler.attackProjectile, "", "", "", "", "", "", "", "",
                                            "sc/ui.sc", "rapid_fire_button", "rico_def_atk", "", "", "", "", "", "", "", "", "", "", "", ""};

    skills.rows.push_back(weaponSkill);

    std::vector<std::string> ultimateSkill = {brawler.codename + "Ulti", "Attack", "true", "true", "true", "", "50", std::to_string(brawler.ultimateAttackDuration), "",
                                              std::to_string(brawler.ultimateRange), "", "",
                                              "", "", "", "", std::to_string(brawler.ultimateDamage), "", std::to_string(brawler.ultimateTimeBetweenAttacks), std::to_string(brawler.ultimateSpread), "",
                                              std::to_string(brawler.ultimateProjectileCount), "",
                                              "true", "", "", "", "", "", "", "", "", brawler.ultimateProjectile, "", "", "", "", "", "", "", "",
                                              "sc/ui.sc", "rapid_fire_button", "rico_def_atk", "", "", "", "", "", "", "", "", "", "", "", ""};

    skills.rows.push_back(ultimateSkill);

    skills.writeCSV();

    auto texts = csv.readCSV(textsCSVPath);

    std::vector<std::string> brawlerName = {brawler.tid, brawler.name};

    texts.rows.push_back(brawlerName);

    std::vector<std::string> brawlerDescription = {brawler.tid + "_DESC", brawler.description};

    texts.rows.push_back(brawlerDescription);

    std::vector<std::string> brawlerShortDescription = {brawler.tid + "_SHORT_DESC", brawler.shortDescription};

    texts.rows.push_back(brawlerShortDescription);

    std::vector<std::string> brawlerWeaponName = {brawler.weaponTID, brawler.weaponName};

    texts.rows.push_back(brawlerWeaponName);

    std::vector<std::string> brawlerWeaponDescription = {brawler.weaponTID + "_DESC", brawler.weaponDescription};

    texts.rows.push_back(brawlerWeaponDescription);

    std::vector<std::string> brawlerUltimateName = {brawler.ultimateTID, brawler.ultimateName};

    texts.rows.push_back(brawlerUltimateName);

    std::vector<std::string> brawlerUltimateDescription = {brawler.ultimateTID + "_DESC", brawler.ultimateDescription};

    texts.rows.push_back(brawlerUltimateDescription);

    texts.writeCSV();

    return 0;
}

int BrawlerMaker::removeBrawler(std::string tid, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath)
{
    CSVHandler csv;
    auto characters = csv.readCSV(charactersCSVPath);
    auto cards = csv.readCSV(cardsCSVPath);
    auto skills = csv.readCSV(skillsCSVPath);
    auto texts = csv.readCSV(textsCSVPath);

    // Store weapon and ultimate skill as it is used when removing the brawler from texts.csv and skills.csv
    std::string weaponSkill;
    std::string ultimateSkill;
    // Codename is needed later for cards
    std::string name;
    // Remove character from characters.csv
    for (auto it = characters.rows.begin(); it != characters.rows.end();)
    {
        if ((*it)[characters.getColumnIndex("TID")] == tid)
        {
            name = (*it)[0];
            weaponSkill = (*it)[characters.getColumnIndex("WeaponSkill")];
            ultimateSkill = (*it)[characters.getColumnIndex("UltimateSKill")];
            it = texts.rows.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Write changes to characters.csv
    characters.writeCSV();

    // Remove from skills.csv
    for (auto it = skills.rows.begin(); it != skills.rows.end();)
    {
        if ((*it)[skills.getColumnIndex("Name")] == weaponSkill)
        {
            it = texts.rows.erase(it);
        }
        else if ((*it)[skills.getColumnIndex("Name")] == ultimateSkill)
        {
            it = texts.rows.erase(it);
        }
        else
        {
            ++it;
        }
    }

    skills.writeCSV();

    std::string weaponTID;
    std::string ultimateTID;

    // Remove all mentions of brawler from cards.csv
    for (auto it = cards.rows.begin(); it != cards.rows.end();)
    {
        if ((*it)["Target"] == name)
        {
            if ((*it)[cards.getColumnIndex("Skill")] == weaponSkill)
            {
                weaponTID = (*it)[cards.getColumnIndex("TID")];
            }
            else if ((*it)[cards.getColumnIndex("Skill")] == ultimateSkill)
            {
                ultimateTID = (*it)[cards.getColumnIndex("TID")];
            }
            it = texts.rows.erase(it);
        }
        else
        {
            ++it;
        }
    }

    cards.writeCSV();

    // Remove all mentions of brawler from texts.csv
    for (auto it = texts.rows.begin(); it != texts.rows.end();)
    {
        if ((*it)[0] == tid)
        {
            it = texts.rows.erase(it);
        }
        else if ((*it)[0] == tid + "_DESC")
        {
            it = texts.rows.erase(it);
        }
        else if ((*it)[0] == tid + "_SHORT_DESC")
        {
            it = texts.rows.erase(it);
        }
        else if ((*it)[0] == weaponTID)
        {
            it = texts.rows.erase(it);
        }
        else if ((*it)[0] == weaponTID + "_DESC")
        {
            it = texts.rows.erase(it);
        }
        else if ((*it)[0] == ultimateTID)
        {
            it = texts.rows.erase(it);
        }
        else if ((*it)[0] == ultimateTID + "_DESC")
        {
            it = texts.rows.erase(it);
        }
        else
        {
            ++it;
        }
    }

    texts.writeCSV();
}

int BrawlerMaker::editBrawler(std::string tid, const Brawler &brawler, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath)
{
    CSVHandler csv;
    auto characters = csv.readCSV(charactersCSVPath);
    auto cards = csv.readCSV(cardsCSVPath);
    auto skills = csv.readCSV(skillsCSVPath);
    auto texts = csv.readCSV(textsCSVPath);
    int i = 0;

    for (auto row : characters.rows)
    {
        if (row["TID"] == tid)
        {

        }
        i++;
    }

    return i;
}
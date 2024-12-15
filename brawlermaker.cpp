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
    CSV characters(charactersCSVPath);
    CSV cards(cardsCSVPath);
    CSV skills(skillsCSVPath);
    CSV texts(textsCSVPath);
    Brawler brawler;

    for (auto &row : characters.rows)
    {
        if (row[characters.getColumnIndex("TID")] != tid)
        {
            continue;
        }

        std::string type = row["Type"];
        brawler.codename = row["Name"];
        brawler.tid = row["TID"];
        brawler.weaponSkill = row["WeaponSkill"];
        brawler.ultimateSkill = row["UltimateSkill"];
        brawler.speed = toint(row["Speed"], UNDEFINED);
        brawler.health = toint(row["Hitpoints"], UNDEFINED);
        brawler.iconSWF = row["IconSWF"];
        brawler.icon = row["IconExportName"];
        brawler.pet = row["Pet"];
        brawler.scale = toint(row["Scale"], UNDEFINED);
        brawler.attackRechargeUltimateAmount = toint(row["UltiChargeMul"], UNDEFINED);
        brawler.ultimateRechargeUltimateAmount = toint(row["UltiChargeUltiMul"], UNDEFINED);

        for (auto &skillsRow : skills.rows)
        {
            if (skillsRow["Name"] == brawler.weaponSkill)
            {
                try
                {
                    brawler.weaponReloadTime = toint(skillsRow["RechargeTime"], UNDEFINED);
                    brawler.weaponAmmoCount = toint(skillsRow["MaxCharge"], UNDEFINED);
                    brawler.weaponDamage = toint(skillsRow["Damage"], UNDEFINED);
                    brawler.attackSpread = toint(skillsRow["Spread"], UNDEFINED);
                    brawler.attackProjectileCount = toint(skillsRow["NumBulletsInOneAttack"], UNDEFINED);
                    brawler.weaponTimeBetweenAttacks = toint(skillsRow["MsBetweenAttacks"], UNDEFINED);
                    brawler.attackDuration = toint(skillsRow["ActiveTime"], UNDEFINED);
                    brawler.weaponRange = toint(skillsRow["CastingRange"], UNDEFINED);
                    brawler.attackProjectile = skillsRow["Projectile"];
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

                    brawler.ultimateDamage = toint(skillsRow["Damage"], UNDEFINED);
                    brawler.ultimateSpread = toint(skillsRow["Spread"], UNDEFINED);
                    brawler.ultimateProjectileCount = toint(skillsRow["NumBulletsInOneAttack"], UNDEFINED);
                    brawler.ultimateAttackDuration = toint(skillsRow["ActiveTime"], UNDEFINED);
                    brawler.summonedCharacter == skillsRow[skills.getColumnIndex("SummonedCharacter")];
                    brawler.ultimateRange = toint(skillsRow["CastingRange"], UNDEFINED);
                    brawler.ultimateProjectile = skillsRow[skills.getColumnIndex("Projectile")];
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << " at line " << __LINE__ << " identifier " << skillsRow[0] << std::endl;
                    throw;
                }
            }
        }

        for (Row &cardsRow : cards.rows)
        {
            if (cardsRow["Target"] == brawler.codename)
            {
                if (cardsRow["Type"] == "unlock")
                {
                    brawler.number = toint(cardsRow["SortOrder"], UNDEFINED);
                    const std::string csvRarity = cardsRow["Rarity"];
                }
                else if (cardsRow["Type"] == "skill")
                {
                    if (cardsRow["Skill"] == brawler.weaponSkill)
                    {
                        brawler.weaponTID = cardsRow["TID"];
                    }
                    else if (cardsRow["Skill"] == brawler.ultimateSkill)
                    {
                        brawler.ultimateTID = cardsRow["TID"];
                    }
                }
            }
        }

        for (Row &textsRow : texts.rows)
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
    CSV characters(charactersCSVPath);
    std::vector<Brawler> brawlers;
    bool datatypes = true;
    for (Row row : characters.rows)
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
    CSV csv;
    CSV characters(charactersCSVPath);
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

    CSV cards(cardsCSVPath);
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

    CSV skills(skillsCSVPath);

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

    CSV texts(textsCSVPath);

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
    CSV characters(charactersCSVPath);
    CSV cards(cardsCSVPath);
    CSV skills(skillsCSVPath);
    CSV texts(textsCSVPath);

    // Store weapon and ultimate skill as it is used when removing the brawler from texts.csv and skills.csv
    std::string weaponSkill;
    std::string ultimateSkill;
    // Codename is needed later for cards
    std::string name;
    // Remove character from characters.csv
    for (auto it = characters.rows.begin(); it != characters.rows.end();)
    {
        if ((*it)["TID"] == tid)
        {
            name = (*it)[0];
            weaponSkill = (*it)["WeaponSkill"];
            ultimateSkill = (*it)["UltimateSkill"];
            it = characters.rows.erase(it);
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
        if ((*it)["Name"] == weaponSkill)
        {
            it = skills.rows.erase(it);
        }
        else if ((*it)["Name"] == ultimateSkill)
        {
            it = skills.rows.erase(it);
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
            if ((*it)["Skill"] == weaponSkill)
            {
                weaponTID = (*it)["TID"];
            }
            else if ((*it)["Skill"] == ultimateSkill)
            {
                ultimateTID = (*it)["TID"];
            }
            it = cards.rows.erase(it);
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

    return 0;
}

int BrawlerMaker::editBrawler(std::string tid, const Brawler &brawler, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath)
{
    CSV characters(charactersCSVPath);
    CSV cards(cardsCSVPath);
    CSV skills(skillsCSVPath);
    CSV texts(textsCSVPath);

    for (Row row : characters.rows)
    {
        if (row["TID"] == tid)
        {
            row["Name"] = brawler.codename;
            row["TID"] = brawler.tid;
            row["WeaponSkill"] = brawler.weaponSkill;
            row["UltimateSkill"] = brawler.ultimateSkill;
            row["Speed"] = brawler.speed;
            row["Hitpoints"] = brawler.health;
            row["IconSWF"] = brawler.iconSWF;
            row["IconExportName"] = brawler.icon;
            row["Pet"] = brawler.pet;
            row["Scale"] = brawler.scale;
            row["UltiChargeMul"] = brawler.attackRechargeUltimateAmount;
            row["UltiChargeUltiMul"] = brawler.ultimateRechargeUltimateAmount;
        }
    }

    characters.writeCSV();

    for (Row row : skills.rows)
    {
        if (row["Name"] == brawler.weaponSkill)
        {
            row["RechargeTime"] = (brawler.weaponReloadTime == UNDEFINED) ? "" : std::to_string(brawler.weaponReloadTime);
            row["MaxCharge"] = (brawler.weaponAmmoCount == UNDEFINED) ? "" : std::to_string(brawler.weaponAmmoCount);
            row["Damage"] = (brawler.weaponDamage == UNDEFINED) ? "" : std::to_string(brawler.weaponDamage);
            row["Spread"] = (brawler.attackSpread == UNDEFINED) ? "" : std::to_string(brawler.attackSpread);
            row["NumBulletsInOneAttack"] = (brawler.attackProjectileCount == UNDEFINED) ? "" : std::to_string(brawler.attackProjectileCount);
            row["MsBetweenAttacks"] = (brawler.weaponTimeBetweenAttacks == UNDEFINED) ? "" : std::to_string(brawler.weaponTimeBetweenAttacks);
            row["ActiveTime"] = (brawler.attackDuration == UNDEFINED) ? "" : std::to_string(brawler.attackDuration);
            row["CastingRange"] = (brawler.weaponRange == UNDEFINED) ? "" : std::to_string(brawler.weaponRange);
            row["Projectile"] = brawler.attackProjectile;
        }
        else if (row["Name"] == brawler.ultimateSkill)
        {
            row["Damage"] = (brawler.weaponDamage == UNDEFINED) ? "" : std::to_string(brawler.weaponDamage);
            row["Spread"] = (brawler.attackSpread == UNDEFINED) ? "" : std::to_string(brawler.attackSpread);
            row["NumBulletsInOneAttack"] = (brawler.attackProjectileCount == UNDEFINED) ? "" : std::to_string(brawler.attackProjectileCount);
            row["MsBetweenAttacks"] = (brawler.weaponTimeBetweenAttacks == UNDEFINED) ? "" : std::to_string(brawler.weaponTimeBetweenAttacks);
            row["ActiveTime"] = (brawler.attackDuration == UNDEFINED) ? "" : std::to_string(brawler.attackDuration);
            row["CastingRange"] = (brawler.weaponRange == UNDEFINED) ? "" : std::to_string(brawler.weaponRange);
            row["Projectile"] = brawler.attackProjectile;
        }
    }

    for (Row row : cards.rows)
    {
        if (row["Target"] == brawler.codename)
        {
            if (row["Type"] == "unlock")
            {
                row["SortOrder"] = brawler.number;
                std::string rarityStr;
                switch (brawler.rarity)
                {
                case Rarity::TrophyRoad:
                    rarityStr = "common";
                case Rarity::Rare:
                    rarityStr = "rare";
                case Rarity::SuperRare:
                    rarityStr = "super_rare";
                case Rarity::Epic:
                    rarityStr = "epic";
                case Rarity::Mythic:
                    rarityStr = "mega_epic";
                case Rarity::Legendary:
                    rarityStr = "legendary";
                }
                row["Rarity"] == rarityStr;
            }
            else if (row["Type"] == "skill")
            {
                if (row["Skill"] == brawler.weaponSkill)
                {
                    row["TID"] == brawler.weaponTID;
                }
                else if (row["Skill"] == brawler.ultimateSkill)
                {
                    row["TID"] == brawler.ultimateTID;
                }
            }
        }
    }

    for (Row row : texts.rows)
    {
        if (row[0] == brawler.tid)
        {
            row[1] = brawler.name;
        }
        else if (row[0] == brawler.tid + "_DESC")
        {
            row[1] = brawler.description;
        }
        else if (row[0] == brawler.tid + "_SHORT_DESC")
        {
            row[1] = brawler.shortDescription;
        }
        else if (row[0] == brawler.weaponTID)
        {
            row[1] = brawler.weaponName;
        }
        else if (row[0] == brawler.ultimateTID)
        {
            row[1] = brawler.ultimateName;
        }
        else if (row[0] == brawler.weaponTID + "_DESC")
        {
            row[1] = brawler.weaponDescription;
        }
        else if (row[0] == brawler.ultimateTID + "_DESC")
        {
            row[1] = brawler.ultimateDescription;
        }
    }

    return 0;
}
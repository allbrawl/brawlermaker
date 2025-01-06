#include <csv.h>
#include <stdexcept>
#include <iostream>

#include "brawler.h"
#include "brawlermaker.h"

Brawler BrawlerMaker::getBrawler(const std::string tid, const std::string charactersCSVPath, const std::string cardsCSVPath, const std::string skillsCSVPath, const std::string textsCSVPath) const
{
    CSV characters(charactersCSVPath);
    CSV cards(cardsCSVPath);
    CSV skills(skillsCSVPath);
    CSV texts(textsCSVPath);
    Brawler brawler;
    bool found;

    for (auto &row : characters.rows)
    {
        if (row["TID"] != tid)
        {
            continue;
        }

        found = true;
        std::string type = row["Type"];
        brawler.codename = row["Name"];
        brawler.tid = row["TID"];
        brawler.weaponSkill = row["WeaponSkill"];
        brawler.ultimateSkill = row["UltimateSkill"];
        brawler.speed = row["Speed"];
        brawler.health = row["Hitpoints"];
        brawler.iconSWF = row["IconSWF"];
        brawler.icon = row["IconExportName"];
        brawler.pet = row["Pet"];
        brawler.scale = row["Scale"];
        brawler.attackRechargeUltimateAmount = row["UltiChargeMul"];
        brawler.ultimateRechargeUltimateAmount = row["UltiChargeUltiMul"];
        brawler.defaultSkin = row["DefaultSkin"];
        break;
    }

    if (!found)
    {
        throw std::runtime_error("Brawler with TID " + tid + " not found.");
    }

    for (auto &skillsRow : skills.rows)
    {
        if (skillsRow["Name"] == brawler.weaponSkill)
        {
            try
            {
                brawler.weaponReloadTime = skillsRow["RechargeTime"];
                brawler.weaponAmmoCount = skillsRow["MaxCharge"];
                brawler.weaponDamage = skillsRow["Damage"];
                brawler.attackSpread = skillsRow["Spread"];
                brawler.attackProjectileCount = skillsRow["NumBulletsInOneAttack"];
                brawler.weaponTimeBetweenAttacks = skillsRow["MsBetweenAttacks"];
                brawler.attackDuration = skillsRow["ActiveTime"];
                brawler.weaponRange = skillsRow["CastingRange"];
                brawler.attackProjectile = skillsRow["Projectile"];
                brawler.attackCooldown = skillsRow["Cooldown"];
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
                brawler.ultimateDamage = skillsRow["Damage"];
                brawler.ultimateSpread = skillsRow["Spread"];
                brawler.ultimateProjectileCount = skillsRow["NumBulletsInOneAttack"];
                brawler.ultimateAttackDuration = skillsRow["ActiveTime"];
                brawler.summonedCharacter == skillsRow["SummonedCharacter"];
                brawler.ultimateRange = skillsRow["CastingRange"];
                brawler.ultimateProjectile = skillsRow["Projectile"];
                brawler.ultimateCooldown = skillsRow["Cooldown"];
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
                brawler.number = cardsRow["SortOrder"];
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
    return brawler;
}

std::vector<Brawler> BrawlerMaker::getBrawlers(std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath, bool ignoreNonHeros)
{
    CSV characters(charactersCSVPath);
    std::vector<Brawler> brawlers;
    bool datatypes = true;
    for (Row &row : characters.rows)
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
                        brawler.speed, brawler.health, "", "", "", "",
                        "", "", "", "12", "", brawler.attackRechargeUltimateAmount, brawler.ultimateRechargeUltimateAmount, "Hero", "", brawler.codename + "Default", "",
                        "", "",
                        "", "", "", "takedamage_gen", "death_shotgun_girl", "Gen_move_fx", "reload_shotgun_girl",
                        "No_ammo_shotgungirl", "Dry_fire_shotgungirl", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                        "", "", "30", "", "80", "80", "", "", "35", brawler.scale, "210", "284", "90", "175", "260", "", "", "", "-25",
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
                                           "", "", "", "", "", "", brawler.number, ""};

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

    std::vector<std::string> weaponSkill = {brawler.codename + "Weapon", "Attack", "true", "true", "true", "", brawler.attackCooldown, brawler.attackDuration, "",
                                            brawler.weaponRange, "", "",
                                            "", "", brawler.weaponReloadTime, brawler.weaponAmmoCount, brawler.weaponDamage, "", brawler.weaponTimeBetweenAttacks,
                                            brawler.attackSpread, "", brawler.attackProjectileCount, "",
                                            "true", "", "", "", "", "", "", "", "", brawler.attackProjectile, "", "", "", "", "", "", "", "",
                                            "sc/ui.sc", "rapid_fire_button", "rico_def_atk", "", "", "", "", "", "", "", "", "", "", "", ""};

    skills.rows.push_back(weaponSkill);

    std::vector<std::string> ultimateSkill = {brawler.codename + "Ulti", "Attack", "true", "true", "true", "", brawler.ultimateCooldown, brawler.ultimateAttackDuration, "",
                                              brawler.ultimateRange, "", "",
                                              "", "", "", "", brawler.ultimateDamage, "", brawler.ultimateTimeBetweenAttacks, brawler.ultimateSpread, "",
                                              brawler.ultimateProjectileCount, "",
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

    for (Row &row : characters.rows)
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
            row["DefaultSkin"] = brawler.defaultSkin;
        }
    }

    characters.writeCSV();

    for (Row &row : skills.rows)
    {
        if (row["Name"] == brawler.weaponSkill)
        {
            row["RechargeTime"] = brawler.weaponReloadTime;
            row["MaxCharge"] = brawler.weaponAmmoCount;
            row["Damage"] = brawler.weaponDamage;
            row["Spread"] = brawler.attackSpread;
            row["NumBulletsInOneAttack"] = brawler.attackProjectileCount;
            row["MsBetweenAttacks"] = brawler.weaponTimeBetweenAttacks;
            row["ActiveTime"] = brawler.attackDuration;
            row["CastingRange"] = brawler.weaponRange;
            row["Projectile"] = brawler.attackProjectile;
            row["Cooldown"] = brawler.attackCooldown;
        }
        else if (row["Name"] == brawler.ultimateSkill)
        {
            row["Damage"] = brawler.weaponDamage;
            row["Spread"] = brawler.attackSpread;
            row["NumBulletsInOneAttack"] = brawler.attackProjectileCount;
            row["MsBetweenAttacks"] = brawler.weaponTimeBetweenAttacks;
            row["ActiveTime"] = brawler.attackDuration;
            row["CastingRange"] = brawler.weaponRange;
            row["Projectile"] = brawler.attackProjectile;
            row["Cooldown"] = brawler.ultimateCooldown;
        }
    }

    skills.writeCSV();

    for (Row &row : cards.rows)
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

    cards.writeCSV();

    for (Row &row : texts.rows)
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

    texts.writeCSV();

    return 0;
}

int BrawlerMaker::cloneBrawler(std::string tid, std::string newTID, std::string newName, std::string newWeaponName, std::string newUltimateName, std::string charactersCSVPath, std::string cardsCSVPath, std::string skillsCSVPath, std::string textsCSVPath)
{
    CSV characters(charactersCSVPath);
    CSV cards(cardsCSVPath);
    CSV skills(skillsCSVPath);
    CSV texts(textsCSVPath);

    for (Row &row : characters.rows)
    {
        if (row["TID"] == tid)
        {
            Row newRow = row;
            newRow["TID"] = newTID;
            newRow["Name"] = newName;
            newRow["ItemName"] = newName;
            characters.rows.push_back(newRow);
            break;
        }
    }

    characters.writeCSV();

    for (Row &row : cards.rows)
    {
        if (row["Target"] == newName)
        {
            if (row["Type"] == "unlock")
            {
                Row newRow = row;
                newRow["Target"] = newName;
                newRow["Name"] = newName + "_unlock";
                cards.rows.push_back(newRow);
            }
            else if (row["Type"] == "hp")
            {
                Row newRow = row;
                newRow["Target"] = newName;
                newRow["Name"] = newName + "_hp";
                cards.rows.push_back(newRow);
            }
            else if (row["Type"] == "skill")
            {
                if (row["Skill"] == newWeaponName)
                {
                    Row newRow = row;
                    newRow["Target"] = newName;
                    newRow["Name"] = newName + "_abi";
                    newRow["Skill"] = newWeaponName;
                    cards.rows.push_back(newRow);
                }
                else if (row["Skill"] == newUltimateName)
                {
                    Row newRow = row;
                    newRow["Target"] = newName;
                    newRow["Name"] = newName + "_ulti";
                    newRow["Skill"] = newUltimateName;
                    cards.rows.push_back(newRow);
                }
            }
        }
    }

    cards.writeCSV();

    for (Row &row : skills.rows)
    {
        if (row["Name"] == newWeaponName)
        {
            Row newRow = row;
            newRow["Name"] = newWeaponName;
        }
        else if (row["Name"] == newUltimateName)
        {
            Row newRow = row;
            newRow["Name"] = newUltimateName;
        }
    }

    skills.writeCSV();

    for (Row &row : texts.rows)
    {
        if (row["TID"] == tid)
        {
            Row newRow = row;
            newRow[0] = newTID;
            texts.rows.push_back(newRow);
        }
        else if (row["TID"] == tid + "_DESC")
        {
            Row newRow = row;
            newRow[0] = newTID + "_DESC";
            texts.rows.push_back(newRow);
        }
        else if (row["TID"] == tid + "_SHORT_DESC")
        {
            Row newRow = row;
            newRow[0] = newTID + "_SHORT_DESC";
            texts.rows.push_back(newRow);
        }
        else if (row["TID"] == newWeaponName)
        {
            Row newRow = row;
            newRow[0] = newWeaponName;
            texts.rows.push_back(newRow);
        }
        else if (row["TID"] == newWeaponName + "_DESC")
        {
            Row newRow = row;
            newRow[0] = newWeaponName + "_DESC";
            texts.rows.push_back(newRow);
        }
        else if (row["TID"] == newUltimateName)
        {
            Row newRow = row;
            newRow[0] = newUltimateName;
            texts.rows.push_back(newRow);
        }
        else if (row["TID"] == newUltimateName + "_DESC")
        {
            Row newRow = row;
            newRow[0] = newUltimateName + "_DESC";
            texts.rows.push_back(newRow);
        }
    }

    texts.writeCSV();

    return 0;
}

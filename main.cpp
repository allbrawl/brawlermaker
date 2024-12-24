#include "brawlermaker.h"
#include <iostream>
#include <csv.h>
#include <cstring>

void help()
{
    std::cout << "Brawlermaker Utility\n";
    std::cout << "Usage: brawlermaker <csv path> <mode> [arguments]\n\n";
    std::cout << "Modes:\n";
    std::cout << "  list [TID]                                  Lists all brawlers or details of a specific brawler if TID is provided.\n";
    std::cout << "  add                                         Adds a new brawler to the CSV files.\n";
    std::cout << "  remove <TID>                                Removes a brawler by TID from the CSV files.\n";
    std::cout << "  edit <TID> <field>=<value>                  Modifies the details of an existing brawler by TID.\n";
    std::cout << "  clone <original TID> <copy tid> <new name>  Creates a duplicate of an existing brawler with a new TID.\n";
}

void printBrawler(const Brawler &brawler)
{
    std::cout << "*************************" << "\n";
    std::cout << "codename: " << brawler.codename << "\n";
    std::cout << "name: " << brawler.name << "\n";
    std::cout << "tid: " << brawler.tid << "\n";
    std::cout << "description: " << brawler.description << "\n";
    std::cout << "weaponName: " << brawler.weaponName << "\n";
    std::cout << "ultimateName: " << brawler.ultimateName << "\n";
    std::cout << "weaponDescription: " << brawler.weaponDescription << "\n";
    std::cout << "ultimateDescription: " << brawler.ultimateDescription << "\n";
    if (brawler.rarity == Rarity::TrophyRoad)
        std::cout << "rarity: Trophy Road" << "\n";
    else if (brawler.rarity == Rarity::Rare)
        std::cout << "rarity: Rare" << "\n";
    else if (brawler.rarity == Rarity::SuperRare)
        std::cout << "rarity: Super Rare" << "\n";
    else if (brawler.rarity == Rarity::Epic)
        std::cout << "rarity: Epic" << "\n";
    else if (brawler.rarity == Rarity::Mythic)
        std::cout << "rarity: Mythic " << "\n";
    else if (brawler.rarity == Rarity::Legendary)
        std::cout << "rarity: Legendary" << "\n";

    std::cout << "weaponSkill: " << brawler.weaponSkill << "\n";
    std::cout << "ultimateSkill: " << brawler.ultimateSkill << "\n";
    std::cout << "speed: " << brawler.speed << "\n";
    std::cout << "health: " << brawler.health << "\n";
    std::cout << "iconSWF: " << brawler.iconSWF << "\n";
    std::cout << "icon: " << brawler.icon << "\n";
    std::cout << "pet: " << brawler.pet << "\n";
    std::cout << "summonedCharacter: " << brawler.summonedCharacter << "\n";
    std::cout << "scale: " << brawler.scale << "\n";
    std::cout << "weaponRange: " << brawler.weaponRange << "\n";
    std::cout << "ultimateRange: " << brawler.ultimateRange << "\n";
    std::cout << "weaponReloadTime: " << brawler.weaponReloadTime << "\n";
    std::cout << "weaponAmmoCount: " << brawler.weaponAmmoCount << "\n";
    std::cout << "ultimateAmmoCount: " << brawler.ultimateAmmoCount << "\n";
    std::cout << "weaponDamage: " << brawler.weaponDamage << "\n";
    std::cout << "ultimateDamage: " << brawler.ultimateDamage << "\n";
    std::cout << "attackSpread: " << brawler.attackSpread << "\n";
    std::cout << "ultimateSpread: " << brawler.ultimateSpread << "\n";
    std::cout << "attackProjectileCount: " << brawler.attackProjectileCount << "\n";
    std::cout << "ultimateProjectileCount: " << brawler.ultimateProjectileCount << "\n";
    std::cout << "weaponTimeBetweenAttacks: " << brawler.weaponTimeBetweenAttacks << "\n";
    std::cout << "ultimateTimeBetweenAttacks: " << brawler.ultimateTimeBetweenAttacks << "\n";
    std::cout << "attackDuration: " << brawler.attackDuration << "\n";
    std::cout << "ultimateAttackDuration: " << brawler.ultimateAttackDuration << "\n";
    std::cout << "attackRechargeUltimateAmount: " << brawler.attackRechargeUltimateAmount << "\n";
    std::cout << "ultimateRechargeUltimateAmount: " << brawler.ultimateRechargeUltimateAmount << "\n";
    std::cout << "number: " << brawler.number << "\n";
    std::cout << "attackCooldown: " << brawler.attackCooldown << "\n";
    std::cout << "ultimateCooldown:" << brawler.ultimateCooldown << "\n";
    std::cout << "attackProjectile: " << brawler.attackProjectile << "\n";
    std::cout << "ultimateProjectile: " << brawler.ultimateProjectile << "\n";
    std::cout << "weaponTID: " << brawler.weaponTID << "\n";
    std::cout << "ultimateTID: " << brawler.ultimateTID << "\n";
    std::cout << "defaultSkin: " << brawler.defaultSkin << "\n";
}

std::string tolower(std::string text)
{
    std::string result = text;
    for (char &c : result)
    {
        c = std::tolower(c);
    }
    return result;
}

int main(int argc, char **argv)
{
    if (argc <= 2)
    {
        help();
    }
    else if (!strcmp("list", argv[2]))
    {
        BrawlerMaker bm;

        if (argc > 3)
        {
            Brawler brawler;
            try
            {
                brawler = bm.getBrawler(argv[3], std::string(argv[1]) + "/csv_logic/characters.csv", std::string(argv[1]) + "/csv_logic/cards.csv", std::string(argv[1]) + "/csv_logic/skills.csv", std::string(argv[1]) + "/localization/texts.csv");
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                exit(1);
            }
            printBrawler(brawler);
            std::cout << "*************************" << "\n";
        }
        else
        {
            std::vector<Brawler> brawlers = bm.getBrawlers(std::string(argv[1]) + "/csv_logic/characters.csv", std::string(argv[1]) + "/csv_logic/cards.csv", std::string(argv[1]) + "/csv_logic/skills.csv", std::string(argv[1]) + "/localization/texts.csv", true);
            for (const auto &brawler : brawlers)
            {
                printBrawler(brawler);
            }
            std::cout << "*************************" << "\n";
        }
    }
    else if (!strcmp("remove", argv[1]) && argc > 2)
    {
        BrawlerMaker bm;

        bm.removeBrawler(argv[2], std::string(argv[1]) + "/csv_logic/characters.csv", std::string(argv[1]) + "/csv_logic/cards.csv", std::string(argv[1]) + "/csv_logic/skills.csv", std::string(argv[1]) + "/localization/texts.csv");
    }
    else if (!strcmp("edit", argv[2]) && argc == 5)
    {
        BrawlerMaker bm;

        std::string tid = argv[3];
        std::string fieldValuePair = argv[4];

        size_t separatorPos = fieldValuePair.find('=');
        if (separatorPos == std::string::npos)
        {
            std::cerr << "Invalid field=value format." << std::endl;
            return 1;
        }

        std::string field = fieldValuePair.substr(0, separatorPos);
        std::string value = fieldValuePair.substr(separatorPos + 1);
        field = tolower(field);
        Brawler brawler;
        try
        {
            brawler = bm.getBrawler(tid, std::string(argv[1]) + "/csv_logic/characters.csv", std::string(argv[1]) + "/csv_logic/cards.csv", std::string(argv[1]) + "/csv_logic/skills.csv", std::string(argv[1]) + "/localization/texts.csv");
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            exit(1);
        }

        if (field == "tid")
            brawler.tid = value;
        else if (field == "name")
            brawler.name = value;
        else if (field == "codename")
            brawler.codename = value;
        else if (field == "description")
            brawler.description = value;
        else if (field == "shortdescription")
            brawler.shortDescription = value;
        else if (field == "weaponname")
            brawler.weaponName = value;
        else if (field == "ultimatename")
            brawler.ultimateName = value;
        else if (field == "weapondescription")
            brawler.weaponDescription = value;
        else if (field == "ultimatedescription")
            brawler.ultimateDescription = value;
        else if (field == "rarity")
        {
            if (tolower(value) == "trophyroad")
                brawler.rarity = Rarity::TrophyRoad;
            else if (tolower(value) == "rare")
                brawler.rarity = Rarity::Rare;
            else if (tolower(value) == "superrare")
                brawler.rarity = Rarity::SuperRare;
            else if (tolower(value) == "epic")
                brawler.rarity = Rarity::Epic;
            else if (tolower(value) == "mythic")
                brawler.rarity = Rarity::Mythic;
            else if (tolower(tolower(value)) == "legendary")
                brawler.rarity = Rarity::Legendary;
            else
            {
                std::cerr << "Invalid rarity value." << std::endl;
                return 1;
            }
        }

        else if (field == "weaponskill")
            brawler.weaponSkill = value;
        else if (field == "ultimateskill")
            brawler.ultimateSkill = value;
        else if (field == "speed")
            brawler.speed = value;
        else if (field == "health")
            brawler.health = value;
        else if (field == "iconswf")
            brawler.iconSWF = value;
        else if (field == "icon")
            brawler.icon = value;
        else if (field == "pet")
            brawler.pet = value;
        else if (field == "summonedcharacter")
            brawler.summonedCharacter = value;
        else if (field == "scale")
            brawler.scale = value;
        else if (field == "weaponrange")
            brawler.weaponRange = value;
        else if (field == "ultimaterange")
            brawler.ultimateRange = value;
        else if (field == "weaponreloadtime")
            brawler.weaponReloadTime = value;
        else if (field == "weaponammocount")
            brawler.weaponAmmoCount = value;
        else if (field == "ultimateammocount")
            brawler.ultimateAmmoCount = value;
        else if (field == "weapondamage")
            brawler.weaponDamage = value;
        else if (field == "ultimatedamage")
            brawler.ultimateDamage = value;
        else if (field == "attackspread")
            brawler.attackSpread = value;
        else if (field == "ultimatespread")
            brawler.ultimateSpread = value;
        else if (field == "attackprojectilecount")
            brawler.attackProjectileCount = value;
        else if (field == "ultimateprojectilecount")
            brawler.ultimateProjectileCount = value;
        else if (field == "weapontimebetweenattacks")
            brawler.weaponTimeBetweenAttacks = value;
        else if (field == "ultimatetimeBetweenattacks")
            brawler.ultimateTimeBetweenAttacks = value;
        else if (field == "attackduration")
            brawler.attackDuration = value;
        else if (field == "ultimateattackduration")
            brawler.ultimateAttackDuration = value;
        else if (field == "attackrechargeultimateamount")
            brawler.attackRechargeUltimateAmount = value;
        else if (field == "ultimaterechargeultimateamount")
            brawler.ultimateRechargeUltimateAmount = value;
        else if (field == "number")
            brawler.number = value;
        else if (field == "attackcooldown")
            brawler.attackCooldown = value;
        else if (field == "ultimatecooldown")
            brawler.ultimateCooldown = value;
        else if (field == "attackprojectile")
            brawler.attackProjectile = value;
        else if (field == "ultimateprojectile")
            brawler.ultimateProjectile = value;
        else if (field == "weapontid")
            brawler.weaponTID = value;
        else if (field == "ultimatetid")
            brawler.ultimateTID = value;
        else if (field == "defaultskin")
            brawler.defaultSkin = value;
        else
        {
            std::cerr << "Field not recognized." << std::endl;
            return 1;
        }
        int result = bm.editBrawler(tid, brawler, std::string(argv[1]) + "/csv_logic/characters.csv", std::string(argv[1]) + "/csv_logic/cards.csv", std::string(argv[1]) + "/csv_logic/skills.csv", std::string(argv[1]) + "/localization/texts.csv");

        if (result == 0)
            std::cout << "Brawler successfully updated." << std::endl;
        else
            std::cerr << "Failed to update brawler." << std::endl;
    }
    else if (!strcmp("clone", argv[2]) && argc == 6)
    {
        BrawlerMaker bm;

        int result = bm.cloneBrawler(argv[3], argv[4], argv[5], std::string(argv[4]) + "Weapon", std::string(argv[4]) + "Ulti", std::string(argv[1]) + "/csv_logic/characters.csv", std::string(argv[1]) + "/csv_logic/cards.csv", std::string(argv[1]) + "/csv_logic/skills.csv", std::string(argv[1]) + "/localization/texts.csv");

        if (result == 0)
            std::cout << "Brawler successfully cloned." << std::endl;
        else
            std::cerr << "Failed to clone brawler." << std::endl;
        }
        else
        {
        help();
        }

    return 0;
}

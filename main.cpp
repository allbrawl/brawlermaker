#include <brawlermaker.h>
#include <iostream>
#include <csv.h>

int main()
{
    BrawlerMaker handle;
    auto brawlers = handle.getBrawlers("baseCSVs/csv_logic/characters.csv", "baseCSVs/csv_logic/cards.csv", "baseCSVs/csv_logic/skills.csv", "baseCSVs/localization/texts.csv", true);
    for (auto brawler : brawlers)
    {
        std::cout << "*************************" << std::endl;
        std::cout << "codename: " << brawler.codename << std::endl;
        std::cout << "name: " << brawler.name << std::endl;
        std::cout << "tid: " << brawler.tid << std::endl;
        std::cout << "description: " << brawler.description << std::endl;
        std::cout << "weaponName: " << brawler.weaponName << std::endl;
        std::cout << "ultimateName: " << brawler.ultimateName << std::endl;
        std::cout << "weaponDescription: " << brawler.weaponDescription << std::endl;
        std::cout << "ultimateDescription: " << brawler.ultimateDescription << std::endl;
        std::cout << "rarity: " << static_cast<int>(brawler.rarity) << std::endl;
        std::cout << "weaponSkill: " << brawler.weaponSkill << std::endl;
        std::cout << "ultimateSkill: " << brawler.ultimateSkill << std::endl;
        std::cout << "speed: " << (brawler.speed == UNDEFINED ? "undefined" : std::to_string(brawler.speed)) << std::endl;
        std::cout << "health: " << (brawler.health == UNDEFINED ? "undefined" : std::to_string(brawler.health)) << std::endl;
        std::cout << "iconSWF: " << brawler.iconSWF << std::endl;
        std::cout << "icon: " << brawler.icon << std::endl;
        std::cout << "pet: " << brawler.pet << std::endl;
        std::cout << "summonedCharacter: " << brawler.summonedCharacter << std::endl;
        std::cout << "scale: " << (brawler.scale == UNDEFINED ? "undefined" : std::to_string(brawler.scale)) << std::endl;
        std::cout << "weaponRange: " << (brawler.weaponRange == UNDEFINED ? "undefined" : std::to_string(brawler.weaponRange)) << std::endl;
        std::cout << "ultimateRange: " << (brawler.ultimateRange == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateRange)) << std::endl;
        std::cout << "weaponReloadTime: " << (brawler.weaponReloadTime == UNDEFINED ? "undefined" : std::to_string(brawler.weaponReloadTime)) << std::endl;
        std::cout << "ultimateReloadTime: " << (brawler.ultimateReloadTime == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateReloadTime)) << std::endl;
        std::cout << "weaponAmmoCount: " << (brawler.weaponAmmoCount == UNDEFINED ? "undefined" : std::to_string(brawler.weaponAmmoCount)) << std::endl;
        std::cout << "ultimateAmmoCount: " << (brawler.ultimateAmmoCount == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateAmmoCount)) << std::endl;
        std::cout << "weaponDamage: " << (brawler.weaponDamage == UNDEFINED ? "undefined" : std::to_string(brawler.weaponDamage)) << std::endl;
        std::cout << "ultimateDamage: " << (brawler.ultimateDamage == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateDamage)) << std::endl;
        std::cout << "attackSpread: " << (brawler.attackSpread == UNDEFINED ? "undefined" : std::to_string(brawler.attackSpread)) << std::endl;
        std::cout << "ultimateSpread: " << (brawler.ultimateSpread == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateSpread)) << std::endl;
        std::cout << "attackProjectileCount: " << (brawler.attackProjectileCount == UNDEFINED ? "undefined" : std::to_string(brawler.attackProjectileCount)) << std::endl;
        std::cout << "ultimateProjectileCount: " << (brawler.ultimateProjectileCount == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateProjectileCount)) << std::endl;
        std::cout << "weaponTimeBetweenAttacks: " << (brawler.weaponTimeBetweenAttacks == UNDEFINED ? "undefined" : std::to_string(brawler.weaponTimeBetweenAttacks)) << std::endl;
        std::cout << "ultimateTimeBetweenAttacks: " << (brawler.ultimateTimeBetweenAttacks == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateTimeBetweenAttacks)) << std::endl;
        std::cout << "attackDuration: " << (brawler.attackDuration == UNDEFINED ? "undefined" : std::to_string(brawler.attackDuration)) << std::endl;
        std::cout << "ultimateAttackDuration: " << (brawler.ultimateAttackDuration == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateAttackDuration)) << std::endl;
        std::cout << "attackRechargeUltimateAmount: " << (brawler.attackRechargeUltimateAmount == UNDEFINED ? "undefined" : std::to_string(brawler.attackRechargeUltimateAmount)) << std::endl;
        std::cout << "ultimateRechargeUltimateAmount: " << (brawler.ultimateRechargeUltimateAmount == UNDEFINED ? "undefined" : std::to_string(brawler.ultimateRechargeUltimateAmount)) << std::endl;
        std::cout << "number: " << (brawler.number == UNDEFINED ? "undefined" : std::to_string(brawler.number)) << std::endl;
        std::cout << "attackProjectile: " << brawler.attackProjectile << std::endl;
        std::cout << "ultimateProjectile: " << brawler.ultimateProjectile << std::endl;
        std::cout << "weaponTID: " << brawler.weaponTID << std::endl;
        std::cout << "ultimateTID: " << brawler.ultimateTID << std::endl;
    }

    return 0;
}
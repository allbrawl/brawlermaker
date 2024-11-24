#ifndef BRAWLER_H
#define BRAWLER_H

#include <vector>
#include <string>

enum class Rarity
{
    TrophyRoad, // common
    Rare,       // rare
    SuperRare,  // super_rare
    Epic,       // epic
    Mythic,     // mega_epic
    Legendary   // legendary
};

/*
enum class Speed
{
    VerySlow, // 0
    Slow, // 1
    Normal, // 2
    Fast, // 3
    VeryFast // 4
};
*/

class Brawler
{
public:
    std::string tid;
    std::string name;
    std::string codename;
    std::string description;
    std::string weaponName;
    std::string ultimateName;
    std::string weaponDescription;
    std::string ultimateDescription;
    Rarity rarity;
    std::string weaponSkill;
    std::string ultimateSkill;
    int speed;
    int health;
    std::string iconSWF;
    std::string icon;
    std::string pet;
    std::string summonedCharacter;
    int scale;
    int weaponRange;
    int ultimateRange;
    int weaponReloadTime;
    int ultimateReloadTime;
    int weaponAmmoCount;
    int ultimateAmmoCount;
    int weaponDamage;
    int ultimateDamage;
    int attackSpread;
    int ultimateSpread;
    int attackProjectileCount;
    int ultimateProjectileCount;
    int weaponTimeBetweenAttacks;
    int ultimateTimeBetweenAttacks;
    int attackDuration;
    int ultimateAttackDuration;
    int attackRechargeUltimateAmount;
    int ultimateRechargeUltimateAmount;
    int number;
    std::string attackProjectile;
    std::string ultimateProjectile;
    std::string weaponTID;
    std::string ultimateTID; 


    Brawler(const std::string &tid, const std::string &name, const std::string &codename, const std::string &description, std::string &weaponTID, std::string &ultimateTID,
            const std::string &weaponName, const std::string &ultimateName,
            const Rarity rarity,
            const std::string &weaponSkill, const std::string &weaponDescription, const std::string &ultimateDescription,
            const std::string &ultimateSkill,
            const int speed, const int health, const std::string &iconSWF, const std::string &icon, const std::string &pet, std::string &summonedCharacter,
            const int scale, const int range, const int weaponReloadTime, const int ultimateReloadTime, const int weaponAmmoCount, const int ultimateAmmoCount,
            const int weaponDamage, const int ultimateDamage, const int attackSpread, const int ultimateSpread, const int ultimateRange,
            const int attackProjectileCount, const int ultimateProjectileCount, const int weaponTimeBetweenAttacks, const int ultimateTimeBetweenAttacks,
            const int attackDuration, const int ultimateAttackDuration, const int attackRechargeUltimateAmount, const int ultimateRechargeUltimateAmount, const int number, const std::string &attackProjectile, const std::string &ultimateProjectile)
        : tid(tid), name(name), codename(codename), description(description), weaponTID(weaponTID), ultimateTID(ultimateTID),
          weaponName(weaponName), ultimateName(ultimateName), weaponSkill(weaponSkill), ultimateSkill(ultimateSkill),
          speed(speed), health(health), iconSWF(iconSWF), icon(icon), pet(pet), summonedCharacter(summonedCharacter),
          scale(scale), weaponRange(range), ultimateRange(ultimateRange), weaponReloadTime(weaponReloadTime), ultimateReloadTime(ultimateReloadTime),
          weaponAmmoCount(weaponAmmoCount), ultimateAmmoCount(ultimateAmmoCount), weaponDamage(weaponDamage), ultimateDamage(ultimateDamage), attackSpread(attackSpread),
          ultimateSpread(ultimateSpread), attackProjectileCount(attackProjectileCount), ultimateProjectileCount(ultimateProjectileCount), weaponTimeBetweenAttacks(weaponTimeBetweenAttacks), ultimateTimeBetweenAttacks(ultimateTimeBetweenAttacks), attackDuration(attackDuration), ultimateAttackDuration(ultimateAttackDuration), attackRechargeUltimateAmount(attackRechargeUltimateAmount), ultimateRechargeUltimateAmount(ultimateRechargeUltimateAmount), number(number), attackProjectile(attackProjectile), ultimateProjectile(ultimateProjectile), rarity(rarity), weaponDescription(weaponDescription), ultimateDescription(ultimateDescription) {};
    Brawler() : tid(""), name(""), codename(""), description(""), weaponTID(""), ultimateTID(""), weaponName(""), ultimateName(""), rarity(Rarity::TrophyRoad), weaponDescription(""), ultimateDescription(""), weaponSkill(""), ultimateSkill(""), speed(0), health(0), iconSWF(""), icon(""), pet(""), summonedCharacter(""), scale(0), weaponRange(0), ultimateRange(0), weaponReloadTime(0), ultimateReloadTime(0), weaponAmmoCount(0), ultimateAmmoCount(0), weaponDamage(0), ultimateDamage(0), attackSpread(0), ultimateSpread(0), attackProjectileCount(0), ultimateProjectileCount(0), weaponTimeBetweenAttacks(0), ultimateTimeBetweenAttacks(0), attackDuration(0), ultimateAttackDuration(0), attackRechargeUltimateAmount(0), ultimateRechargeUltimateAmount(0), number(0), attackProjectile(""), ultimateProjectile("") {}
};
#endif

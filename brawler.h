#pragma once

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
    std::string shortDescription;
    std::string weaponName;
    std::string ultimateName;
    std::string weaponDescription;
    std::string ultimateDescription;
    Rarity rarity;
    std::string weaponSkill;
    std::string ultimateSkill;
    std::string speed;
    std::string health;
    std::string iconSWF;
    std::string icon;
    std::string pet;
    std::string summonedCharacter;
    std::string scale;
    std::string weaponRange;
    std::string ultimateRange;
    std::string weaponReloadTime;
    std::string weaponAmmoCount;
    std::string ultimateAmmoCount;
    std::string weaponDamage;
    std::string ultimateDamage;
    std::string attackSpread;
    std::string ultimateSpread;
    std::string attackProjectileCount;
    std::string ultimateProjectileCount;
    std::string weaponTimeBetweenAttacks;
    std::string ultimateTimeBetweenAttacks;
    std::string attackDuration;
    std::string ultimateAttackDuration;
    std::string attackRechargeUltimateAmount;
    std::string ultimateRechargeUltimateAmount;
    std::string number;
    std::string attackCooldown;
    std::string ultimateCooldown;
    std::string attackProjectile;
    std::string ultimateProjectile;
    std::string weaponTID;
    std::string ultimateTID;
    std::string defaultSkin;

    Brawler(std::string &tid, std::string &name, std::string &codename, std::string &description, std::string &shortDescription, std::string &weaponTID, std::string &ultimateTID,
            std::string &weaponName, std::string &ultimateName,
            Rarity rarity,
            std::string &weaponSkill, std::string &weaponDescription, std::string &ultimateDescription,
            std::string &ultimateSkill,
            std::string speed, std::string health, std::string &iconSWF, std::string &icon, std::string &pet, std::string &summonedCharacter,
            std::string scale, std::string range, std::string weaponReloadTime, std::string ultimateReloadTime, std::string weaponAmmoCount, std::string ultimateAmmoCount,
            std::string weaponDamage, std::string ultimateDamage, std::string attackSpread, std::string ultimateSpread, std::string ultimateRange,
            std::string attackProjectileCount, std::string ultimateProjectileCount, std::string weaponTimeBetweenAttacks, std::string ultimateTimeBetweenAttacks,
            std::string attackDuration, std::string ultimateAttackDuration, std::string attackRechargeUltimateAmount, std::string ultimateRechargeUltimateAmount, std::string number, std::string attackCooldown, std::string ultimateCooldown, std::string &attackProjectile, std::string &ultimateProjectile,
            std::string &defaultSkin)
        : tid(tid), name(name), codename(codename), description(description), shortDescription(shortDescription), weaponTID(weaponTID), ultimateTID(ultimateTID),
          weaponName(weaponName), ultimateName(ultimateName), weaponSkill(weaponSkill), ultimateSkill(ultimateSkill),
          speed(speed), health(health), iconSWF(iconSWF), icon(icon), pet(pet), summonedCharacter(summonedCharacter),
          scale(scale), weaponRange(range), ultimateRange(ultimateRange), weaponReloadTime(weaponReloadTime),
          weaponAmmoCount(weaponAmmoCount), ultimateAmmoCount(ultimateAmmoCount), weaponDamage(weaponDamage), ultimateDamage(ultimateDamage), attackSpread(attackSpread),
          ultimateSpread(ultimateSpread), attackProjectileCount(attackProjectileCount), ultimateProjectileCount(ultimateProjectileCount), weaponTimeBetweenAttacks(weaponTimeBetweenAttacks),
          ultimateTimeBetweenAttacks(ultimateTimeBetweenAttacks), attackDuration(attackDuration), ultimateAttackDuration(ultimateAttackDuration), attackRechargeUltimateAmount(attackRechargeUltimateAmount), 
          ultimateRechargeUltimateAmount(ultimateRechargeUltimateAmount), number(number), attackCooldown(attackCooldown), ultimateCooldown(ultimateCooldown), attackProjectile(attackProjectile), 
          ultimateProjectile(ultimateProjectile), rarity(rarity), weaponDescription(weaponDescription), ultimateDescription(ultimateDescription), defaultSkin(defaultSkin) {};
    Brawler() : tid(""), name(""), codename(""), description(""), shortDescription(""), weaponTID(""), ultimateTID(""), weaponName(""), ultimateName(""), rarity(Rarity::TrophyRoad), weaponDescription(""), ultimateDescription(""), weaponSkill(""), ultimateSkill(""), speed(""), health(""), iconSWF(""), icon(""), pet(""), summonedCharacter(""), scale(""), weaponRange(""), ultimateRange(""), weaponReloadTime(""), weaponAmmoCount(""), ultimateAmmoCount(""), weaponDamage(""), ultimateDamage(""), attackSpread(""), ultimateSpread(""), attackProjectileCount(""), ultimateProjectileCount(""), weaponTimeBetweenAttacks(""), ultimateTimeBetweenAttacks(""), attackDuration(""), ultimateAttackDuration(""), attackRechargeUltimateAmount(""), ultimateRechargeUltimateAmount(""), number(""), attackCooldown(""), ultimateCooldown(""), attackProjectile(""), ultimateProjectile(""), defaultSkin("") {}
};

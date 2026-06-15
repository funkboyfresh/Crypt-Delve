# CryptDelve Phase 1 Data Reference

Create the following DataAssets in the Unreal Editor under Content/Data/.

## Races (URaceDefinition)

| Asset | Race | Bonus |
|-------|------|-------|
| DA_Race_Human | Human | +10% XP |
| DA_Race_Elf | Elf | +5 evasion |
| DA_Race_Dwarf | Dwarf | +5 armor |

## Classes (UClassDefinition)

| Asset | Class | Skill Tree | Starting Weapon Tag |
|-------|-------|------------|---------------------|
| DA_Class_Fighter | Fighter | Tree_Fighter | Weapon.Sword |
| DA_Class_Wizard | Wizard | Tree_Wizard | Weapon.Staff |
| DA_Class_Cleric | Cleric | Tree_Cleric | Weapon.Mace |

## Zone (UZoneDefinition)

| Asset | ZoneId | Floors | Boss |
|-------|--------|--------|------|
| DA_Zone_CryptOfAsh | CryptOfAsh | 3 | AshLord |

## Skill Trees (USkillTreeDefinition)

Each tree should have 8-12 nodes with prerequisites. Example Fighter nodes:
- fighter_power_1: +2 STR
- fighter_toughness_1: +2 CON (requires fighter_power_1)
- fighter_melee_mastery: Ability.Primary upgrade + Weapon.Sword proficiency
- fighter_shield_wall: +5 armor

## Items (UItemDefinition)

| ItemId | Slot | BaseDamage | ArmorBonus |
|--------|------|------------|------------|
| IronSword | MainHand | 12 | 0 |
| ClothRobe | Chest | 0 | 3 |
| LeatherHelm | Helmet | 0 | 2 |

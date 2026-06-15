# Project Concept: CryptDelve

## 1. Executive Summary
**CryptDelve** is an online multiplayer, top-down roguelike dungeon crawler built on Unreal Engine for up to 8 players. The title seamlessly merges the high-stakes, session-based variability of roguelikes with the deep, permanent character progression and customization found in traditional fantasy role-playing systems (D&D). 

CryptDelve features universal cross-play and cross-progression across PC (Steam), Nintendo Switch 2, Xbox, and PlayStation 5, utilizing a centralized account matrix to preserve player data across all hardware.

---

## 2. Core Pillars
* **Universal Cross-Platform Flow:** Seamless multiplayer matchmaking and instant cross-progression across PC and next-gen consoles.
* **Persistent Roguelike Progression:** Individual runs feature unpredictable layouts and hazardous conditions, but character levels, skill trees, and items permanently persist.
* **Tactical 8-Player Scale:** Deep multi-character cooperative combat balancing that dynamically scales challenges according to party size.

---

## 3. Platform & Technical Specifications
* **Engine:** Unreal Engine 5+
* **Target Platforms:** PC (Steam), Nintendo Switch 2, Xbox Series X/S, PlayStation 5.
* **Network Topology:** Authoritative Client-Server model with dedicated servers or robust listen-server capabilities. 
* **Identity Infrastructure:** Cross-platform backend integration (e.g., Epic Online Services) for centralized account management, cross-play matchmaking, and remote cloud data storage.

---

## 4. Core Gameplay Systems

### 4.1 Perspective & Input
* **Camera:** Fixed top-down perspective optimized for tactical overview and tracking fast combat.
* **Controls:** Twin-stick/Action combat configuration with native controller map presets for consoles/handhelds, alongside Keyboard/Mouse support for PC.

### 4.2 Races, Classes, & Skill Trees
* **Racial & Class Identities:** Directly inspired by classic d20 fantasy systems. Players select a Race (providing passive traits and attribute distributions) and a Class (dictating their active role, base mechanics, and combat style).
* **Branching Skill Trees:** Each class features a dedicated, persistent tree. Players permanently invest earned experience to unlock nodes that govern active abilities, core spellbooks, and direct weapon performance metrics.

### 4.3 Progression Mechanics & Inventory
* **Character Persistence:** Characters do not wipe upon a failed run. They retain accumulated power, choices, and gear across distinct gameplay areas and individual sessions.
* **Equipment Framework:** Characters feature permanent equippable slots:
  * Helmet
  * Armor
  * Leggings
  * Weapon (Main-hand / Off-hand / Two-handed)
* **The Progression Divide:**
  * **Permanent Elements:** Level data, allocated skill points, unlocked abilities, and baseline equipped gear profiles are securely committed to the player's network account.
  * **Roguelike Elements:** In-map localized modifiers (e.g., temporary resource modifiers, elemental damage multipliers, and area-specific hazard perks) are acquired mid-run and reset completely upon extraction or party defeat.

---

## 5. Loop & Level Generation

### 5.1 Game Loop
1. **The Sanctuary (Hub):** Players party up (up to 8), adjust persistent skill tree nodes, swap out gear, and vote on the overarching zone theme to assault.
2. **The Descent (Levels):** A gauntlet of dynamically generated levels matching the aesthetic and hazard ruleset of the overarching zone theme.
3. **The Boss Lair:** Every level group concludes with an intricate, multi-phase boss fight. Victory unlocks subsequent progression regions and rewards high-tier permanent gear, while run failure returns players to the Hub.

### 5.2 Procedural Level Systems
* **Tile-Based Architecture:** Levels are procedurally built using prefabricated visual/structural tile modules. 
* Rulesets defining spatial branching, room density, encounter spawning, and tile stitching parameters will be formalized during prototyping phases.

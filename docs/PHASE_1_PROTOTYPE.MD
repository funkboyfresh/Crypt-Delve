---
name: UE Roguelike Prototype
overview: Bootstrap an Unreal Engine 5 PC prototype (2-4 player co-op, 1 zone, basic races/classes, persistent gear + skill trees) with cloud-linked account saves, using architecture that extends cleanly to 8-player cross-play on Steam, Switch 2, Xbox, and PS5.
todos:
  - id: create-project
    content: Create UE 5.5 C++ project at ~/Projects/<GameName> with git, module structure, and .gitignore
    status: pending
  - id: topdown-multiplayer
    content: Implement top-down movement, Enhanced Input, and 2-4 player dedicated-server replication
    status: pending
  - id: gas-combat
    content: Set up GAS with attribute sets, 1 prototype class, and server-authoritative combat
    status: pending
  - id: character-equipment
    content: Build persistent CharacterProfile, equipment slots, and stat aggregation pipeline
    status: pending
  - id: skill-trees
    content: Data-driven skill trees with server-validated unlocks tied to GAS abilities
    status: pending
  - id: roguelike-run
    content: Implement RunState (seed, modifiers, floor index) separate from persistent character data
    status: pending
  - id: levelgen-boss
    content: Stub room-graph level generator for 1 zone theme, 3 floors, and 1 boss encounter
    status: pending
  - id: eos-playfab
    content: Wire EOS auth/sessions and PlayFab character save/load with disconnect checkpoints
    status: pending
  - id: lobby-ui
    content: Build Main Menu → Login → Character Select → Host/Join lobby flow with CommonUI
    status: pending
isProject: false
---

# Unreal Roguelike — Phase 1 Prototype Plan

## Goal
[cite_start]Build a **PC-only vertical prototype** that proves the core loop[cite: 25]:
> [cite_start]Log in → pick persistent character → join 2-4 player run → procedurally generated zone levels → boss → keep gear/skills/progression → log out and resume on another PC session[cite: 25].

[cite_start]Everything in Phase 1 is chosen so you **do not throw away work** when adding consoles, cross-play, and 8-player scale later[cite: 26].

## Recommended Stack (solo-indie friendly)

| Layer | Phase 1 choice | Why | Future extension |
|---|---|---|---|
| Engine | **UE 5.5+** (C++ core, Blueprint for content) | [cite_start]Best top-down + multiplayer tooling [cite: 29] | [cite_start]Same project, add platform SDKs [cite: 30] |
| Online identity | **Epic Online Services (EOS)** | [cite_start]Free, native UE plugin, account ID survives platform changes [cite: 30, 31] | [cite_start]Link Steam/Xbox/PS/Nintendo IDs later [cite: 31] |
| Persistent data | **PlayFab** (or EOS Player Data Storage) | [cite_start]Fast solo-dev path for characters, inventory, skill unlocks [cite: 31, 32] | [cite_start]Same API across all platforms [cite: 33] |
| Multiplayer model | **Dedicated server** (local dev server first) | [cite_start]Roguelike fairness + run state authority [cite: 33, 34] | [cite_start]Deploy to AWS/GCP/Hathora/Edgegap [cite: 34] |
| Abilities/combat | **Gameplay Ability System (GAS)** | [cite_start]Industry standard for skill-tree-driven abilities [cite: 34, 35] | [cite_start]Scales to complex builds [cite: 35] |
| Content authoring | **DataAssets + DataTables** | [cite_start]Races, classes, items, skills without recompiles [cite: 35, 36] | [cite_start]Designers can expand later [cite: 36] |

[cite_start]**Do not use Steam Cloud as primary save** — it locks persistence to Steam and blocks Switch/Xbox/PS cross-device sync[cite: 37]. [cite_start]Use EOS/PlayFab from day one; add Steam as a login provider in Phase 2[cite: 38].

## High-Level Architecture & Authority Rules

* [cite_start]**Authority Rule (Critical):** The dedicated server owns combat, loot rolls, run modifiers, and level generation seeds[cite: 38]. [cite_start]Clients only predict movement/animations[cite: 39]. [cite_start]Persistent character data is written **server-side → PlayFab** at run end and safe checkpoints[cite: 39].
* [cite_start]**Platform Abstraction Guardrail:** Wrap all login and subsystem identity requests behind abstract C++ interfaces (e.g., `IPlatformAuth` / `IPlatformSession`)[cite: 72]. [cite_start]This guarantees that the Switch 2 or console SDKs can plug in later without requiring a rewrite of core game code[cite: 72].

## Project Structure

[cite_start]Create project at `~/Projects/<GameName>/` with this module layout:
```text
Source/
  <GameName>/
    Core/           # GameInstance, GameMode, PlayerController 
    Characters/     # Race/class components, stat calculation 
    Abilities/      # GAS abilities, effects, attribute sets 
    Equipment/      # Slots, item definitions, stat modifiers 
    Progression/    # Skill trees, unlock validation 
    Roguelike/      # Run modifiers, floor seeds, zone config 
    LevelGen/       # Tile grid, room graph, spawn points (stub rules) 
    Network/        # EOS login, session create/join, PlayFab sync 
    UI/             # Character select, HUD, skill tree, inventory 
Content/
  Data/             # DataTables: Races, Classes, Items, Skills, Zones 
  Maps/             # MainMenu, Lobby, Zone01_Prototype 
  Blueprints/       # Designer-facing wrappers only


***

### Section 4: Gameplay Systems (Part 1)
```markdown
## Core Gameplay Systems (Phase 1 Scope) [cite: 41]

### 1. Top-down multiplayer foundation [cite: 41]
* Fixed or free camera; twin-stick action configuration[cite: 41, 42].
* Replicated `ACharacter` pawns with server-authoritative movement[cite: 43].
* Lobby flow: Main Menu → Login → Character Select → Host/Join Session → Load Zone[cite: 43].
* **Scaling Guardrail:** Target **2-4 players** for active Phase 1 network testing, but keep the maximum session bounds parameter configurable (`MaxPlayers = 8`)[cite: 44]. Ensure difficulty calculation formulas dynamically evaluate player-count arrays (up to 8) rather than hardcoding calculations for 4 players[cite: 103, 127].

### 2. Persistent character model (survives runs) [cite: 45]
Define a serializable `FCharacterProfile`[cite: 45]:
* Identity: `CharacterId`, `AccountId`, name, race, class[cite: 45].
* Base stats: STR/DEX/CON/INT/WIS/CHA (or simplified 4-stat variant)[cite: 45, 129].
* Progression: level, XP, unspent skill points, unlocked skill node IDs[cite: 45].
* Equipment: helmet, chest, legs, boots, gloves, main-hand, off-hand, accessory slots[cite: 45].
* Inventory: item instance IDs + stack counts[cite: 45].

*Persistence triggers:* character creation, end of run, boss defeat, manual rest checkpoint, disconnect grace window[cite: 45].

### 3. Races and classes (D&D-inspired, data-driven) [cite: 46]
* Phase 1 content target: **3 races, 3 classes**[cite: 46].
* Example set: Human (+XP), Elf (+evasion), Dwarf (+armor) / Fighter, Wizard, Cleric[cite: 47].
* Each race/class is a `UDataAsset` referencing starting stats, allowed weapon tags, and skill tree root nodes[cite: 47].

### [cite_start]4. Skill trees tied to abilities [cite: 47]
* [cite_start]One tree per class (+ optional racial passive node)[cite: 47]. [cite_start]Nodes grant stat bonuses, GAS ability unlocks, upgrades, and weapon proficiency tags[cite: 48].
* [cite_start]Server validates unlock requests against points and prerequisites[cite: 49].
* [cite_start]**Weapon performance** = base item stats × proficiency tags from skill tree × run modifiers[cite: 50]. [cite_start]Keep Phase 1 trees small (~8-12 nodes)[cite: 51].

### [cite_start]5. Equipment system [cite: 51]
* [cite_start]`UEquipmentComponent` on character; replicated for visuals/stats[cite: 51, 52].
* [cite_start]Items are `UItemDefinition` (static) + `FItemInstance`[cite: 52]. [cite_start]Equip rules enforced server-side[cite: 53].
* [cite_start]Visuals: modular skeletal mesh parts or simple mesh swaps per slot[cite: 54].

### [cite_start]6. Roguelike vs persistent split (Core Design Rule) [cite: 55]

| [cite_start]Persistent (between runs/sessions) [cite: 55] | [cite_start]Per-run roguelike (resets each run) [cite: 55] |
|---|---|
| [cite_start]Character level/XP, skill unlocks [cite: 56] | [cite_start]Map layout seed and room graph [cite: 56] |
| [cite_start]Equipped gear and inventory [cite: 57] | [cite_start]Temporary run buffs/debuffs [cite: 57] |
| [cite_start]Currency / meta-progression updates [cite: 57] | [cite_start]Damage/resource/drop rate modifiers [cite: 57] |
| [cite_start]Account-wide cosmetics (later) [cite: 58] | [cite_start]Floor affixes, shrines, hazard density [cite: 58] |

[cite_start]Implement `URunStateComponent` on GameState holding run seed, floor index, active modifiers, and party wipe rules[cite: 59].

### [cite_start]7. Zone / level / boss loop (1 zone in prototype) [cite: 60]
* [cite_start]Phase 1 zone: **"Crypt of Ash"**[cite: 60]. [cite_start]Loop: Generate floor → clear objectives → spawn floor exit → after **3 floors**, spawn zone boss[cite: 61].
* [cite_start]**Console Resource Guardrail:** When writing the room-graph generator (`FRoomGraph`), stub generation rules using basic tile placeholders[cite: 61, 62]. [cite_start]Keep the algorithm optimized for low memory usage and tracking limits early, anticipating the physical hardware ceilings of platforms like the Switch 2[cite: 100, 101, 154].

### [cite_start]8. Online services wiring [cite: 63]
* [cite_start]**EOS:** Handle Product ID/dev sandbox setup, Dev Auth login, and lobby session creation/joining[cite: 63].
* [cite_start]**PlayFab:** Keep Title ID and secret key on the dedicated server only[cite: 64]. [cite_start]Store `CharacterProfile` JSON keyed by the EOS `ProductUserId` using `LoginWithCustomId`, `GetUserData`, and `UpdateUserData` calls[cite: 64].


## [cite_start]Suggested Development Order (solo, ~4-6 months part-time) [cite: 73]

1. [cite_start]**Weeks 1-2:** UE project setup, source control, Enhanced Input, top-down single-player movement[cite: 73].
2. [cite_start]**Weeks 3-4:** Dedicated server + 2-player replication foundation, basic network hit registration[cite: 73].
3. [cite_start]**Weeks 5-6:** GAS integration, 1 class setup with 3 active abilities, simple placeholder AI[cite: 73].
4. [cite_start]**Weeks 7-8:** Character profile construction, equipment components, stat aggregation[cite: 73].
5. [cite_start]**Weeks 9-10:** Skill tree UI creation + server-authoritative node validation[cite: 73].
6. [cite_start]**Weeks 11-12:** Procedural room graph generation + 3-floor loop tracking + 1 boss encounter[cite: 73].
7. [cite_start]**Weeks 13-14:** EOS login execution + matchmaking lobby joins[cite: 73].
8. [cite_start]**Weeks 15-16:** PlayFab client payload read/write + disconnect state checkpoints + bug polish[cite: 73].

## [cite_start]Structural Guardrails for Future Implementation [cite: 167]
1. [cite_start]**Network Performance Strategy:** Keep actor replication counts tight[cite: 167]. [cite_start]Profile network data allocation early during the 2-4 player prototype so that pivoting to an Unreal Engine **Replication Graph** configuration in Phase 2 requires no architectural overhauls[cite: 168].
2. [cite_start]**Abstract Platform Interfaces:** Maintain full isolation of store platforms behind generic C++ wrapper structures[cite: 169].
3. [cite_start]**Data-Driven Pipelines:** Ensure all balancing targets exist strictly inside DataAssets and DataTables[cite: 170].

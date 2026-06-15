# CryptDelve

Phase 1 prototype for an online multiplayer roguelike dungeon crawler built in Unreal Engine 5.7.

## Features (Phase 1)

- Top-down twin-stick movement with 2-4 player dedicated-server replication
- GAS-based combat with Fighter, Wizard, and Cleric prototype abilities
- Persistent character profiles with races, classes, equipment, and skill trees
- Roguelike run state (seeds, floor modifiers) separate from persistent progression
- Stub room-graph level generation for the Crypt of Ash zone (3 floors + boss)
- EOS auth/session scaffolding with PlayFab-compatible persistence layer
- Main Menu → Login → Character Select → Lobby UI flow (CommonUI)

## Requirements

- Unreal Engine 5.7
- Visual Studio 2022 with C++ game development workload
- Epic Online Services developer product (optional for local dev fallback)
- PlayFab title (optional; local JSON saves used when unconfigured)

## Setup

1. Open `CryptDelve.uproject` in Unreal Engine 5.7.
2. Allow the editor to compile C++ modules on first launch.
3. Copy `Config/EOS/EOSDevConfig.template.json` values into `Config/DefaultEngine.ini` EOS settings (or use dev auth fallback).
4. Copy `Config/PlayFabConfig.template.ini` to `Config/PlayFabConfig.ini` when ready for cloud saves.
5. Create Blueprint subclasses in `Content/Blueprints/` for:
   - `WBP_MainMenu` (parent: `MainMenuWidget`)
   - `WBP_CharacterSelect` (parent: `CharacterSelectWidget`)
   - `WBP_Lobby` (parent: `LobbyWidget`)
   - `WBP_SkillTree` (parent: `SkillTreeWidget`)
6. Create Enhanced Input assets in `Content/Input/`:
   - `IMC_Default`, `IA_Move`, `IA_Look`, `IA_PrimaryAbility`, `IA_SecondaryAbility`
7. Assign widget classes and input assets on `BP_CryptDelvePlayerController`.

## Running multiplayer locally

**Dedicated server:**
```
CryptDelveServer.exe /Game/Maps/Zone01_Prototype -log
```

**Client:**
```
CryptDelve.exe 127.0.0.1 -log
```

Or use the editor Play dropdown with Net Mode = Play As Client and Number of Players = 2-4.

## Architecture

```
Source/CryptDelve/
  Core/           GameInstance, GameMode, Character, PlayerController
  Characters/     Profile, races, classes, stat calculation
  Abilities/      GAS attributes, melee/fireball/heal abilities
  Equipment/      Slots, item definitions, stat aggregation
  Progression/    Skill trees with server-validated unlocks
  Roguelike/      RunState (seed, modifiers, floor index)
  LevelGen/       Room graph generator, boss encounter stub
  Network/        EOS auth/sessions, PlayFab persistence
  UI/             Main menu, character select, lobby, skill tree
```

## Cross-platform roadmap

Phase 1 is PC-only. EOS account linking and PlayFab persistence are structured for future Steam, Xbox, PS5, and Switch 2 integration without rewriting game systems.

## Content TODO

- Author `Content/Data/` DataAssets for 3 races, 3 classes, starter items, skill trees
- Build `MainMenu`, `Lobby`, and `Zone01_Prototype` maps in editor
- Replace placeholder meshes and VFX

# CryptDelve: Technical Execution & Implementation Plan

Developing an 8-player cross-play roguelike with structural persistence requires a highly coordinated, backend-first approach. This document maps out the architectural layout and phases required to execute the vision.

---

## Phase 1: Identity Backbone & Unified Cross-Progression
*Objective: Secure cross-play matchmaking and persistent remote accounts before freezing gameplay modules.*

### 1.1 Backend Identity Architecture
* **Platform Provider Selection:** Implement **Epic Online Services (EOS)** or an equivalent unified backend engine (e.g., PlayFab). This manages accounts across Steam, Xbox, PlayStation, and Nintendo.
* **Cross-Progression Matrix:** Setup cloud storage profiles linked to a master identity token. When a player boots on a Nintendo Switch 2, the game sends authentication tokens matching their master profile, pulling back their persistent character schema, gear arrays, and tree configs.
* **Security & Data Ownership:** Inventory and level-state changes must be validated exclusively server-side to prevent memory injection attacks and local client file manipulation.

### 1.2 Authoritative 8-Player Networking
* Standardize on an authoritative Client-Server model using Unreal Engine's native networking pipelines.
* Integrate Unreal's **Replication Graph** early on to efficiently distribute network replication data for 8 players and heavy AI clusters across varying console bandwidth capabilities.

---

## Phase 2: Core Progression Data Splitting
*Objective: Separate permanent profile states from volatile, session-based roguelike mechanics.*

### 2.1 The Gear Serialization System
* Establish a database-friendly item schema. All equippable slots (`Helmet`, `Armor`, `Leggings`, `Weapons`) must represent structured JSON payloads or Data Assets that easily translate into network-friendly data states during runtime.

### 2.2 Skill Trees and Weapon Linking
* Build character attributes using Unreal Engine’s **Gameplay Ability System (GAS)**.
* **Weapon Dependency Mapping:** Ensure weapons rely on external skill tree factors. Instead of hard-coding weapon swing damage or fire rates directly onto an item, weapon calculations must poll the player's current persistent GAS attributes and skill tree flags.

### 2.3 Run-Specific Modifier Layer
* Create an isolated runtime Component (`URoguelikeRunComponent`) attached to the game state. 
* This subsystem applies temporary buffs (e.g., `+15% Critical Chance against Undead for current run`, `Double Gold multipliers`). Upon return to the lobby hub or connection closure, this component destroys itself without affecting the persistent profile data.

---

## Phase 3: Co-op Combat & Scaling Architecture
*Objective: Build out the playable grey-box prototype and scale encounter mechanics to support 8 players.*

### 3.1 Class & Race Base Architecture
* Write expandable base C++ templates for characters:
  * `ACryptDelveCharacterBase` -> Native hooks for attributes, movement, and GAS.
  * Racial adjustments apply baseline multipliers to attributes upon generation.
  * Class parameters determine active abilities and branch structures for the Skill Tree UI.

### 3.2 Dynamic Multiplayer Balancing
* Design a dynamic parsing system that listens to active network players ($1 \rightarrow 8$).
* Scale enemy spawn algorithms, elite enemy frequency, health coefficients, and boss damage mechanics dynamically on the fly as players join or drop from sessions.

---

## Phase 4: Procedural Generation Pipelines
*Objective: Formulate the mathematical logic for random dungeon layouts.*

### 4.1 Modular Tile Manager
* Write a dedicated custom C++ generator actor (`AProceduralGenerationManager`).
* Implement a graph-based room assembly algorithm that picks up prefabricated level geometry "tiles" and attaches them via designated connector sockets.
* Decouple the structure rules from the cosmetics, allowing a single dungeon generator code component to run a "Crypt" tileset, a "Magma Cave" tileset, or a "Castle" tileset seamlessly.

---

## Phase 5: Optimization, Next-Gen Porting, & Compliance
*Objective: Maintain target framerates across all platforms and clear technical console certifications.*

### 5.1 Platform Scalability (Targeting Switch 2 / PC)
* Set explicit runtime memory boundaries early to make room for the handheld constraints of the Nintendo Switch 2 alongside high-fidelity modes on Xbox Series X/S and PS5.
* Optimize asset polygonal configurations specifically for top-down visibility (removing unviewed backfaces) and enforce Dynamic Resolution Scaling.

### 5.2 Technical Requirements Checklist (TRC/XR Compliance)
* Plan around explicit platform requirements for cross-network connectivity. Manage separate privacy permissions, cross-network chat configurations, and user profile blockings mandated by Microsoft, Sony, and Nintendo.

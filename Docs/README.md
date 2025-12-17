# FPInteractMoveComp

**Modular First-Person Interaction & Movement System (Unreal Engine 5.7)**

`FPInteractMoveComp` is a modular, component-based interaction system built in C++ for Unreal Engine, designed to demonstrate **clean APIs, decoupled architecture, and extensibility**.

The project focuses on reusable gameplay systems, not actor-specific logic, and is fully interoperable with Blueprints.

---

## Overview

The system provides reusable components to:

- Handle first-person interaction via raycasting
- Provide visual feedback (highlighting) for interactable objects
- Move objects smoothly using interpolation and animation curves

All communication is done through **interfaces**, ensuring **zero coupling** between systems and actors.

---

## Features

- **Modular component-based design**
- **Interface-driven interaction**
    - `IImInteractable`
    - `IImHighlightable`
- **Clean C++ APIs with Blueprint integration**
- **Centralized highlight system**
- **Smooth object movement with configurable curves**
- Designed for **extensibility and testing**

---

## Demo Map

The project includes a **dedicated demo level** designed to validate architectural decisions and showcase system behavior in isolation.

This level is intentionally minimal and structured as a **technical showcase**, not a gameplay scenario.

---

## Usage Notes (Important)

To enable interaction, **the player character must own an `InteractComponent`**.

- `InteractComponent` is responsible for:
    - Performing the raycast
    - Discovering interactable / highlightable components via interfaces
    - Executing interaction and highlight logic

Any custom character (FPS, TPS, pawn, etc.) can use the system **as long as it includes `InteractComponent`** and provide
a valid `USceneComponent` (e.g. camera) as the interaction origin.
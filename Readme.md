# SuperTetris3D

A 3D Tetris-style game built with Unreal Engine (C++). This repository contains the game code, assets and integration for UE5.6.

## Key points

- Engine: Unreal Engine 5.6
- Language: C++
- Project root: `SuperTetris3D.uproject`
- FMOD integration: `Plugins/FMODStudio` (optional — see FMOD section)

## Prerequisites

- Unreal Engine 5.6 installed
- Visual Studio 2022 (Windows) with C++ toolset or Xcode on macOS if targeting mac
- (Optional) FMOD Studio if you want to access the FMOD project inside `FMOD_Project`.

## Getting started (Windows)

1. Clone the repository:

  `git clone <repo-url>`

2. Generate project files (if needed):

   - Right-click the `SuperTetris3D.uproject` file and select "Generate Visual Studio project files"
   - Or run the provided GenerateProjectFiles script for your platform.

3. Build and open:

   - Open `SuperTetris3D.sln` in Visual Studio.
   - Set configuration to `Development Editor` and platform to `Win64`.
   - Build the solution.
   - Double-click `SuperTetris3D.uproject` to open the Editor (or launch from Visual Studio).

4. In Editor: open "MainMenu" level and click Play to test the game.

## FMOD notes

This project includes the FMOD plugin in `Plugins/FMODStudio`. To use FMOD audio in-game:

- Install FMOD Studio (matching supported integration version).
- Place built `.bank` files in `Content/FMOD` (or configure the plugin settings to the bank output directory).
- Use the FMOD Studio plugin `Validate FMOD` option in Editor if available.

Even if you don't use FMOD, the plugin files must be in place or audio features that depend on banks will not function.

## Project structure (high level)

- `Source/SuperTetris3D/Private` - implementation (.cpp)
- `Source/SuperTetris3D/Public` - public headers (.h)
- `Content/` - game assets
- `Plugins/FMODStudio/` - FMOD plugin

Notable source files:
- `ABoard.*` - board/game loop and piece management
- `AGrid.*` - grid logic and piece placement
- `ABlock.*` - block actor logic
- `ASpawner.*` - piece spawner logic
- `ATetrisGameMode.*` - game mode and state management
- `USuperTetris3DGameInstance.*` - savegame and highscore handling
- `FPieceTemplate.*` - struct defining piece shapes


## Controls

- Movement:
  - `A` or `←` — Move left
  - `D` or `→` — Move right
- Rotation:
  - `Q` — Rotate left
  - `E`, `↑` or `Space` — Rotate right
- Soft drop:
  - `S` or `↓` — Accelerate (hold)
- Pause:
  - `P` or `Esc` — Pause

Recommended: use `A` and `D` (rotate with your left hand) and `←`, `↓`, `→` (move and accelerate with your right hand).


## Author

- Name: `Brais García Brenlla (MrBrenlla)`
- Email: `bgbrenlla@gmail.com`

# Max Payne 2 – Unreal Engine 5 C++ skeleton

Ez a repository egy **Unreal Engine 5.4 C++ projektváz** a Max Payne 2 újraírásához. Nem tartalmaz a teljes játékot, és jogvédett Max Payne 2 assetokat sem.

## Fájlok

```text
MaxPayne2Unreal.uproject
Source/
  MaxPayne2Unreal.Target.cs
  MaxPayne2UnrealEditor.Target.cs
  MaxPayne2Unreal/
    MaxPayne2Unreal.Build.cs
    MaxPayne2Unreal.cpp
    Public/
      MaxPayne2GameMode.h
      MaxPayne2Character.h
      MaxPayne2PlayerController.h
      BulletTimeComponent.h
    Private/
      MaxPayne2GameMode.cpp
      MaxPayne2Character.cpp
      MaxPayne2PlayerController.cpp
      BulletTimeComponent.cpp
Content/
  Maps/.gitkeep
Config/
  DefaultEngine.ini
  DefaultGame.ini
  DefaultInput.ini
README.md
```

## Mit tartalmaz a váz?

- **GameMode**: alap pawn és player controller beállítás.
- **Character**: mozgás, default walk/jump sebesség, bullet-time komponens.
- **PlayerController**: WASD + egér nézés, `Fire` action, skeleton szintű shooting.
- **BulletTimeComponent**: time dilation alapú, időzített bullet time.
- **Input config**: `W`, `A`, `S`, `D`, `MouseX`, `MouseY`, bal egér `Fire`.

## Futtatás

1. Telepíts **Unreal Engine 5.4**.
2. Nyisd meg `MaxPayne2Unreal.uproject`-et.
3. Generálj projektfájlokat, majd buildelj.
4. A `Content/Maps/MaxPayne2Sandbox` map csak placeholder; a tényleges mapot és assetokat külön kell létrehozni.

Ez a váz nem alkalmas teljes Max Payne 2 remake-re önmagában; a következő lépések a map, karakter mesh, fegyverrendszer, AI és bullet-time vizuális effekt.


## Smoke test

The smoke test builds a small procedural scene with a stick figure. It uses only Unreal Engine basic shapes (`Cylinder`, `Sphere`, `Cube`) and no assets or textures.

- `ASmokeTestGameMode` spawns a floor and two blocks.
- `AStickFigurePawn` is the player pawn: a stick figure made from engine basic meshes, with a spring-arm camera. Mouse input (`Turn`, `LookUp`) lets the player look around the scene.

## Standalone compile check

There is also a dependency-free C++ smoke test that compiles without Unreal:

```bash
g++ -std=c++17 -O2 tests/smoke_test.cpp -o tests/smoke_test
printf 'a\nq\n' | ./tests/smoke_test
```

It renders a small ASCII scene with a stick figure and lets you rotate the view with `a`/`d`, tilt with `w`/`s`, and quit with `q`.

## Unreal run

Open `MaxPayne2Unreal.uproject` in Unreal Engine 5.4, generate project files, and run. If `/Engine/Maps/Entry` is not available in your engine build, create an empty level named `SmokeTest` and set `GameDefaultMap` to `/Game/Maps/SmokeTest`.

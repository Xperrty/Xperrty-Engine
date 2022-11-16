# Xperrty-Engine
Custom made engine for 2d games that attempts to utilize the cpu and gpu as much as possible in an effective way.
At the moment the project is in an early stage and most of the intended functionalities are just in concept phase.
It may also contain a lot of debug and prototype code.

To generate the project (Visual Studio 2022) use ./genProjects.bat. It will use premake5 to generate the projects(implementation in ./premake5.lua).
For older versions of Visual Studio use "call vendor\bin\premake\premake5.exe vs20xx" in a command prompt.

There are quite a few warnings related to casting, they should be safe for now but they will get fixed in a later push.

The important functionalities implemented for now are Batched Thread Pool, Object Pool and Batches (rendering).

Sandbox contains a demo project with a game.
It showcases creation/deletion of objects, updating, collisions between arrows and zombies. Implementation is single & multithreaded (toggled by Space at runtime) 
Text rendering is not yet implemented in the engine so all the communication is done via console so check it at runtime.

Demo keybinds:

W,A,S,D -> move

Space -> Enable/Disable multithreading

Esc -> Delete all zombies and arrows (Single threaded, game might hang)

1-6 (alphanum keys) -> changes the number of spawned arrows and enemies

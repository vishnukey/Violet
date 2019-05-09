# An SFML Test project

My first time playing around with SFML or any graphics library in C++.
As such, depends on SFML.
Looking at turning this into more of a game engine, starting with 2D but may move to 3D with openGL

Build system uses CMake and brings in SFML as a submodule. Pull with `git clone --recurse-submodules <REPO>` to get the submodules 

## TODO
- [ ] Move map from `std:array<std::string>` to a map of `Tile`s, for sane indexing an reasonable collisions
- [ ] Collisions detection with coins and other collidables
- [ ] Enemies 
- [ ] ???
- [ ] profit

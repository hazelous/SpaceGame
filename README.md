# SpaceGame
Small mini game in C++ using SplashKit library.

## Gameplay
- Left & Right arrow keys to move the ship
- Catch coins (+1), cash (+2), diamonds (+3)
- Avoid asteroids (−5)
- The game ends when your bank balance goes negative

## Running it
This project depends on SplashKit, which must be installed separately.

1. Install SplashKit by following the guide: https://splashkit.io/installation/
2. Add the sprite resources which are not included (see note below).
3. Build with CMake. The included CMakeLists.txt sets the C++ standard and links SplashKit (may need to point it at the library explicitly if CMake can't find SplashKit).
4. Run the executable from a location where it can reach the resources folder

To run the game you'll need a Resources folder containing the sprites the code references which includes: aquarii (the ship), the planet images (mercury, venus, earth, mars, jupiter, saturn, uranus, neptune, pluto), and the falling objects (coin, cash, diamond). These are loaded via a SplashKit resource bundle named lost_in_space.txt.

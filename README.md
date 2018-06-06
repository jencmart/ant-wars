# ANT WARS

School project.


C++ terminal game running on ncurses library.


Game is similiar to Tentacle Wars.

## Getting Started

### Prerequisites
*   gcc
*   ncurses
*   make
*   doxygen


### Installing

```
git clone https://github.com/jencmart/ant-wars.git
```

```
make compile
```

## Usage
  
```
make run
```

![From main menu you can play new game / load game](https://raw.githubusercontent.com/jencmart/ant-wars/master/data/screenshots/ant0.gif)

### How to play
  
   Round starts by selecting your (green) anthills.
   
   Select one of them by LMB(Left mouse button).
   
   Then select an enemy's anthill to attack it or your anthill to support it.

   Next it is opponent's turn to do the same.
   
   Then the simulation of the turn takes place.
   
   Finally round ends and next one starts.
   
   ![Antwars in action](https://raw.githubusercontent.com/jencmart/ant-wars/master/data/screenshots/ant2.gif)

   You'll win when you capture all of the enemy's anthills.
   
   You'll loose when you lost all of your anthills.
   
   ---------------
   
   Ants in anthills are regenerating durign turn simulation.
   
   Ants'll kill each other on the road, when they are on the same path between two anthills during simulation.
   
#### ANT HILL TYPES:
   GREEN ANTHILL            - yours
   
   WHITE ANTHILL            - neutral, must be conquered, but they don't attack
   
   RED   ANTHHILL           - ultraBogo AI enemy ants
   
   BLUE  && PURPLE ANTHILL  - bogo AI


#### OTHER INFO:
   Game is paused by 'p'
   
   In menu you can go back by 'q'


![scalability](https://raw.githubusercontent.com/jencmart/ant-wars/master/data/screenshots/ant3.gif)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

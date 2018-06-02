//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_MENU_H
#define ANTWARS_MENU_H

#include <dirent.h>
#include <vector>
#include <list>
#include "inOut.h"

const std::vector<std::string> PAUSE_MENU = {"CONTINUE", "SAVE GAME", "QUIT GAME", "NEW GAME",
                                             "LOAD GAME", "EXIT"};
const std::vector<std::string> MAIN_MENU = {"NEW GAME", "LOAD GAME", "EXIT"};

class Menu
{
private:
   InputOutput *m_IN_OUT;
   eGameState *m_gameState;
   const std::string & m_mapsDir;
   const std::string & m_savesDir;
public:
   std::string mapName;
   std::string savedGameName;
   std::string loadGameName;

   /*! Constructor for the menu
    * @param x
    * @param gameState
    * @param mapsDir - directory where maps are stored
    * @param savesDir  - directory where save files are stored
    */
   Menu(InputOutput *x,
        eGameState *gameState,
        const std::string & mapsDir ,
        const std::string & savesDir) :
           m_IN_OUT(x),
           m_gameState(gameState),
           m_mapsDir(mapsDir),
           m_savesDir(savesDir)

   {}

   /*! Read file names in specified directory, returns it's names as list of strings
    * @param listOfMaps
    * @param pathToDir
    */
   void ReadDirectory(std::list<std::string> &listOfMaps, std::string pathToDir) const;

   /*! Load name of file of map which user want to playe
    * @return true - file selected
    * @return false - user quit without selecting file name
    */
   bool ChooseMap();

   /*! Load name of file from which user want to load game
    * @return true - file selected
    * @return false - user quit without selecting file name
    */
   bool ChooseLoadGame();

   /*! Display option co name the file of to which user want so save the game
    * and stores it
    * @return true - if user confirm save
    * @return false - if user reject to save the game
    */
   bool LoadSaveName();

   /*! Display menu options or content of directories
    *
    */
   int DisplayMenuItems(const std::vector<std::string> &menu) const;

   /*! Main menu loop
    *  Used to choose menu options
    */
   void Loop();

};

#endif //ANTWARS_MENU_H

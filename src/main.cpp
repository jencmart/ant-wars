#include "gameWrapper.h"



/*! STARTS THE GAME.....
 * @param argv
 * @param argc
 * @return
 */

#define CONFIG_FILE "antwars.conf"

int main(int argv, char **argc)
{

   ///Load configuration file
   std::ifstream f(CONFIG_FILE, std::ios::in);
   std::string mapsDirectory, savesDirectory;

   std::getline(f, mapsDirectory);
   std::getline(f, savesDirectory);

   ///If something wrong, return 1
   if (f.fail() || f.bad())
   {
      std::cout << "Could not load " CONFIG_FILE << std::endl;
      std::cout << "Exiting now..." << std::endl;
      return 1;
   }

   ///run the game
   GameWrapper newGame(mapsDirectory, savesDirectory);
   newGame.run();
   return 0;
}

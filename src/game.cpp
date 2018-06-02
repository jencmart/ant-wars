//
// Created by jencmart on 5/27/17.
//

#include "game.h"


void Game::Loop()
{
   StartDisplay();

   nodelay(m_IN_OUT-> m_window, true); //no delay

   while (1)
   {
      if (!m_pausedInSimulation)
      {
         ///Collect moves from all the players
         for (auto &player : m_players)
         {
            /// If game was paused, skip all players who allready choosed....
            if (m_pausedPayer && player != m_pausedPayer)
               continue;
            if (m_pausedPayer && player == m_pausedPayer)
               m_pausedPayer = NULL;

            /// Print HUD
            PrintHud(player);

            /// If game paused between some moves....
            int in_char = wgetch(m_IN_OUT->m_window);
            if (in_char == 'p' || in_char == KEY_EXIT)
            {
               m_pausedPayer = player;
               m_gameState = GAME_PAUSE;
               return;
            }

            /// try collect command, catch game paused....
            try
            {
               m_commandList.push_back(player->GetCommand());
            }
            catch (Pause &x)
            {
               m_pausedPayer = player;
               m_gameState = GAME_PAUSE;
               return;
            }
            PrintHud(player);
         }
      }

      if (m_pausedInSimulation)
         m_pausedInSimulation = false;

      PrintHud(NULL);
      refresh();
      attron(COLOR_PAIR(1));

      mvprintw(10, m_map.GetWidth() + 5, "All attacks confirmed.");
      usleep(100000);
      refresh();
      refresh();
      mvprintw(11, m_map.GetWidth() + 5, "Running attack simulation.");
      refresh();

      ///Process all commands till no of them are left...
      while (m_commandList.size())
      {
         // TODO if  real time game would be implemented, checking of existing command need to be
         // TODO implemented and if so, only increase num of waiting ants
         /// If game was paused, set paused in simulation....
         nodelay(m_IN_OUT-> m_window, true); //no delay
         int in_char = wgetch(m_IN_OUT->m_window);
         /// If game paused between some moves....
         if (in_char == 'p' || in_char == KEY_EXIT)
         {
            m_pausedInSimulation = true;
            m_gameState = GAME_PAUSE;
            return;
         }

         ProcessCommandsByOneStep();
         m_map.Display(m_IN_OUT);
         refresh();
         usleep(ANT_SPEED);
         ++m_antRiser;
         if (!(m_antRiser %= 10))
            m_map.RiseAntNumbers();
      }

      mvprintw(12, m_map.GetWidth() + 5, "Simulation finished.");
      refresh();
      usleep(100000);
      mvprintw(13, m_map.GetWidth() + 5, "End of %d. round.", m_roundNum++);
      refresh();
      usleep(800000);
      refresh();

      if (CheckEnd())
         break;


      ///All players without AntHills will be removed....
      RemoveDeadPlayers();

      mvprintw(5, m_map.GetWidth() + 5, "                          ");
      mvprintw(6, m_map.GetWidth() + 5, "                          ");
      mvprintw(7, m_map.GetWidth() + 5, "                          ");
      mvprintw(8, m_map.GetWidth() + 5, "                          ");

      mvprintw(10, m_map.GetWidth() + 5, "                           ");
      mvprintw(11, m_map.GetWidth() + 5, "                           ");
      mvprintw(12, m_map.GetWidth() + 5, "                           ");
      mvprintw(13, m_map.GetWidth() + 5, "                           ");

   }

   ///If main loop finished, game is over.....
   for (int i = 5; i < 20; ++i)
      mvprintw(i, m_map.GetWidth() + 1, "                                                 ");

   RemoveDeadPlayers();
   mvprintw(7, m_map.GetWidth() + 5, "***********************");
   mvprintw(8, m_map.GetWidth() + 5, "*                     *");
   mvprintw(9, m_map.GetWidth() + 5, "*                     *");
   if(  (*m_players.begin())->GetID() != 'p')
   {
      attron(COLOR_PAIR(7));
      mvprintw(9, m_map.GetWidth() + 8, "G A M E   O V E R");
      attron(COLOR_PAIR(1));
   }
   else
   {
      attron(COLOR_PAIR(6));
      mvprintw(9, m_map.GetWidth() + 8,    ">>>  YOU WON  <<<");
      attron(COLOR_PAIR(1));
   }

   mvprintw(10, m_map.GetWidth() + 5, "*                     *");
   mvprintw(11, m_map.GetWidth() + 5, "***********************");
   mvprintw(13, m_map.GetWidth() + 5, "Press 'q' to exit game.");
   mvprintw(14, m_map.GetWidth() + 5, "Press 'm' to return to main menu.");
//   mvprintw(15, m_map.GetWidth() + 5, "Press 'RETURN' to play this map again.");
   refresh();

   /// Wait for user input...
   nodelay(m_IN_OUT->m_window, false);
   int in_char = wgetch(m_IN_OUT->m_window);
   switch (in_char)
   {
      case 'q':
         m_gameState = GAME_QUIT;
         return;

      case 'm':
         m_gameState = GAME_MENU;
         return;

      default:
         m_gameState = GAME_MENU;
         return;
   }
}

void Game::ProcessCommandsByOneStep()
{

   for (auto comdIt = m_commandList.begin(); comdIt != m_commandList.end();)
   {
      (*comdIt)->Process();
      if ((*comdIt)->Done())
      {
         delete *comdIt;
         comdIt = m_commandList.erase(comdIt);
      } else
         ++comdIt;

   }
   --m_score;
   return;
}

void Game::PrintHud(AbstractPlayer *player) const
{
   mvprintw(1, m_map.GetWidth() + 5, "                ");
   mvprintw(2, m_map.GetWidth() + 5, "                ");
   mvprintw(3, m_map.GetWidth() + 5, "                               ");
   refresh();


   attron(COLOR_PAIR(12));
   mvprintw(1, m_map.GetWidth() + 5, "       %d", m_roundNum);
   attron(COLOR_PAIR(1));
   mvprintw(1, m_map.GetWidth() + 5, "ROUND:");
   attron(COLOR_PAIR(12));
   mvprintw(2, m_map.GetWidth() + 5, "       %d", m_score);
   attron(COLOR_PAIR(1));
   mvprintw(2, m_map.GetWidth() + 5, "SCORE:");

   mvprintw(3, m_map.GetWidth() + 5, "TURN: ");
   if (player)
   {
      const char *name = (player->GetRealName()).c_str();
      attron(COLOR_PAIR( (short) player->GetID()));

      mvprintw(3, m_map.GetWidth() + 12, name);
      attron(COLOR_PAIR(1));

   } else
      mvprintw(3, m_map.GetWidth() + 12, "-------");
   refresh();

   attron(COLOR_PAIR(1));
   m_map.Display(m_IN_OUT);


}

bool Game::CheckEnd() const
{
   for (auto player : m_players)
   {
      if (m_numOfAntHills == m_map.getNumOfAntHillsByOwner(player->GetID()))
      {
         /// potom je game over
         return true;
      }
   }
   return false;
}


void Game::RemoveDeadPlayers()
{
   for (auto player = m_players.begin(); player != m_players.end();)
   {
      if (m_map.getNumOfAntHillsByOwner((*player)->GetID()) == 0)
      {
         delete *player;
         player = m_players.erase(player);
      } else
         ++player;
   }
}

void Game::Save(const std::string saveDir, const std::string saveFileName) const
{
   /// open file for writing
   std::string fileName = saveDir + '/' + saveFileName;

   std::ofstream f(fileName);
   if (f.bad())
      throw ErrorWhileSaving();

   ///write filemap name
   f << m_map.GetMapName() << std::endl;
   if (f.bad())
      throw ErrorWhileSaving();

   ///write score
   f << m_score << std::endl;
   if (f.bad())
      throw ErrorWhileSaving();


   ///write round number
   f << m_roundNum << std::endl;
   if (f.bad())
      throw ErrorWhileSaving();

   ///write ant riser
   f << m_antRiser << std::endl;
   if (f.bad())
      throw ErrorWhileSaving();

   ///write number of antHills
   f << m_numOfAntHills << std::endl;
   if (f.bad())
      throw ErrorWhileSaving();

   ///write state for eachAntHill
   for (auto x : m_map.GetAntHillStates())
   {
      f << x.first << ' ' << x.second << std::endl;
      if (f.bad())
         throw ErrorWhileSaving();
   }


   /// WRITE SAVE STATE
   /// if saved during choose command state...
   if (m_pausedPayer)
      f << m_pausedPayer->GetID() << std::endl;

      ///else must be saved during simulation state...
   else
      f << 1 << std::endl;


   /// write data from which commands should be retrieved.....

   /// write number of commands....
   f << m_commandList.size() << std::endl;
   if (f.bad())
      throw ErrorWhileSaving();

   ///write data from commands
   for (auto x : m_commandList)
   {
      f << *x << std::endl;
      if (f.bad())
         throw ErrorWhileSaving();
   }

   f.close();
   return;
}

void Game::StartDisplay()
{
   m_IN_OUT->ClearAll();
   m_map.Display(m_IN_OUT);
   m_IN_OUT->Refresh();

   for (int i = 1; i < 18; ++i)
      mvprintw(i, m_map.GetWidth() + 3, "|                                  |");

   mvprintw(0, m_map.GetWidth() + 3, "+----------------------------------+");
   mvprintw(9, m_map.GetWidth() + 3, "+----------------------------------+");
   mvprintw(4, m_map.GetWidth() + 3, "+----------------------------------+");
   mvprintw(15, m_map.GetWidth() + 3, "+----------------------------------+");
   mvprintw(18, m_map.GetWidth() + 3, "+----------------------------------+");
   attron(COLOR_PAIR(12));
   mvprintw(16, m_map.GetWidth() + 5, "             LMB");
   mvprintw(17, m_map.GetWidth() + 5, "             p");
   attron(COLOR_PAIR(1));
   mvprintw(16, m_map.GetWidth() + 5, "Select hill:");
   mvprintw(17, m_map.GetWidth() + 5, "Pause game:");


   if (m_pausedPayer)
      PrintHud(m_pausedPayer);

   refresh();

}

void Game::InitPlayers()
{
   ///Initialize players - this should be done with playerFactory....
   if (m_map.HavePlayer('p'))
      m_players.push_back(new HumanPlayer(&m_map, 'p', "YOU", m_IN_OUT));
   if (m_map.HavePlayer('e'))
      m_players.push_back(new BotPlayer(&m_map, 'e'));
   if (m_map.HavePlayer('f'))
      m_players.push_back(new BotPlayer(&m_map, 'f'));
   if (m_map.HavePlayer('g'))
      m_players.push_back(new BotPlayer(&m_map, 'g'));



   for( int i = 'h' ; i < 'z' ; ++i)
   {
      if (m_map.HavePlayer(i) && i != 'n'  && i != 'p')
         m_players.push_back(new BotPlayer(&m_map, i));


   }
}

void Game::LoadGame(std::string saveFileName, std::string pathToSaves)
{
   std::string fileName = pathToSaves + '/' + saveFileName;

   std::ifstream f(fileName);
   std::string tmpString;
   std::getline(f, tmpString); // load file map name....

   /// load member variables
   f >> m_score;
   f >> m_roundNum;
   f >> m_antRiser;


   f >> m_numOfAntHills;
   /// load ant hill data
   std::list<std::pair<int, int>> antHillData;
   char c;
   int num;
   for (int i = 0; i < m_numOfAntHills; ++i)
   {
      f >> c; // anthillName
      f >> num; // num of ants
      antHillData.push_back(std::pair<int, int>(c, num));
   }

   ///UPDATE ANTHILL DATA
   m_map.UpdateAntHills(antHillData);

   ///INITIALIZE PLAYERS AND REMOVE DEAD ONES
   InitPlayers();
   RemoveDeadPlayers();


   ///LOAD PAUSE STATE
   int pauseState;
   f >> pauseState;
   if (pauseState == 1)
   {
      m_pausedInSimulation = true;
      m_pausedPayer = NULL;
   } else
   {
      for (auto player : m_players)
      {
         if (player->GetID() == pauseState)
         {
            m_pausedPayer = player;
            m_pausedInSimulation = false;
            break;
         }
      }
   }

   StartDisplay();

   ///LOAD COMMAND DATA TODO here some bullshit is happening >>total wtf<<
   int numOfCommands;
   f >> numOfCommands;

   for (int i = 0; i < numOfCommands; ++i)
   {
      int row, col, fromId, toId, numWainting, numWalking;

      f >> row >> col;
      Coords from(row, col);

      f >> row >> col;
      Coords to(row, col);

      f >> fromId >> toId >> numWainting >> numWalking;
      std::list<Coords> antsCoords;

      for (int j = 0; j < numWalking; ++j)
      {
         f >> row >> col;
         antsCoords.push_back(Coords(row, col));
      }

      /// push back that damn bad initializable command !
      m_commandList.push_back(new Command(numWainting,
                                          (AntHill *) m_map.GetElement(from),
                                          (AntHill *) m_map.GetElement(to),
                                          fromId,
                                          toId,
                                          &m_map,
                                          antsCoords));

   }
}

std::string Game::LoadMapName(std::string saveFileName, std::string pathToSaves) const
{
   std::string fileName = pathToSaves + '/' + saveFileName;
   std::ifstream f(fileName);

   std::string mapName;

   if (f.bad())
      throw ErrorWhileReadingFile(fileName);

   std::getline(f, mapName);
   if (f.bad())
      throw ErrorWhileReadingFile(fileName);

   return mapName;
}

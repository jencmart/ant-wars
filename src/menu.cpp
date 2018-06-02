//
// Created by jencmart on 5/27/17.
//

#include "menu.h"

void Menu::Loop()
{
   m_IN_OUT->ClearAll();

   m_IN_OUT->Refresh();

   ///MAIN_MENU = {"NEW GAME", "LOAD GAME", "QUIT GAME"}
   if (*m_gameState == GAME_MENU)
   {
      int rv = DisplayMenuItems(MAIN_MENU);
      switch (rv)
      {
         ///NEW GAME
         case 0:
            if (ChooseMap())
            {
               *m_gameState = GAME_NEW;
               return;
            }
            break;

            ///LOAD GAME
         case 1:
            if (ChooseLoadGame())
            {
               *m_gameState = GAME_LOAD;
               return;
            }
            break;

            ///QUIT GAME
         case 2:
            *m_gameState = GAME_QUIT;
            return;

         default:
            break;

      }
   }

   ///  PAUSE_MENU = {"CONTINUE", "SAVE GAME", "END THIS GAME", "NEW GAME",
   ///                "LOAD GAME", "QUIT GAME"};
   if (*m_gameState == GAME_PAUSE)
   {
      int rv = DisplayMenuItems(PAUSE_MENU);
      switch (rv)
      {
         ///CONTINUE
         case 0:
            *m_gameState = GAME_CONTINUE;
            return;

            ///SAVE GAME
         case 1:
            /// NAPIS ZE SE HRA ULOZILA
            if (LoadSaveName())
               *m_gameState = GAME_SAVE;
            else
               *m_gameState = GAME_PAUSE;
            return;

            ///END THIS GAME
         case 2:
            *m_gameState = GAME_MENU;
            return;

            ///NEW GAME
         case 3:
            if (ChooseMap())
            {
               *m_gameState = GAME_NEW;
               return;
            }
            break;

            ///LOAD GAME
         case 4:
            if (ChooseLoadGame())
            {
               *m_gameState = GAME_LOAD;
               return;
            }
            break;

            ///QUIT GAME
         case 5:
            *m_gameState = GAME_QUIT;
            return;

         default:
            break;

      }
   }
   m_IN_OUT->ClearAll();
}

int Menu::DisplayMenuItems(const std::vector<std::string> &menu) const
{

   int offset = 7;
   int lastPos = 0;
   unsigned position = 0;

   for (unsigned i = 0; i < menu.size(); ++i)
      mvprintw(i + offset, offset, menu[i].c_str());

   while (1)
   {
      mvprintw(offset + lastPos, offset - 1, " ");
      mvprintw(offset + position, offset - 1, "*");
      refresh();

      int in_char = wgetch(m_IN_OUT->m_window);

      switch (in_char)
      {
         case KEY_ENTER:
         case 10:
         case 13:
            return position;

         case KEY_UP:
            lastPos = position;
            if (position == 0)
               position = (unsigned) menu.size() - 1;
            else
               position--;
            break;

         case KEY_DOWN:
            lastPos = position;
            if (position == menu.size() - 1)
               position = 0;
            else
               position++;
         default:
            break;
      }

   }
}

bool Menu::LoadSaveName()
{
   m_IN_OUT->ClearAll();
   refresh();

   int offset = 5;
   mvprintw(offset, offset, "Enter save file name [A-Za-z]:");
   mvprintw(offset + 1, offset, "Press 'RETURN' to save.");
   mvprintw(offset + 2, offset, "Press 'KEY LEFT' to go back to menu.");
   refresh();

   int position = offset + 31;
   std::string saveName;

   while (1)
   {
      int in_char = wgetch(m_IN_OUT->m_window);

      switch (in_char)
      {

         /// KEY ENTER
         case KEY_ENTER:
         case 10:
         case 13:
            if (saveName.size())
            {
               savedGameName = saveName;
               return true;
            } else
            {
               attron(COLOR_PAIR(7));
               mvprintw(offset + 3, offset, "Save name must be at least 1 characer long !!! ");
               attron(COLOR_PAIR(1));
               refresh();
               break;
            }

            ///KEY LEFT
         case KEY_LEFT:
            return false;

            ///KEY LEFT
         case KEY_BACKSPACE:
         case 127:
            if (saveName.size())
            {
               saveName.resize(saveName.size() - 1);
               mvprintw(offset, position, "                    ");
               mvprintw(offset + 3, offset, "                                               ");
               mvprintw(offset, position, saveName.c_str());
            }
            break;
            /// OTHER KEY
         default:
            if (saveName.size() == 15)
            {
               mvprintw(offset + 3, offset, "                                               ");
               attron(COLOR_PAIR(7));
               mvprintw(offset + 3, offset, "Max length reached !!! ");
               attron(COLOR_PAIR(1));
               break;
            } else if ((in_char >= 'A' && in_char <= 'Z') || (in_char >= 'a' && in_char <= 'z'))
            {
               saveName += in_char;
               mvprintw(offset, position, saveName.c_str());
               mvprintw(offset + 3, offset, "                                               ");
               break;
            }

            break;
      }
   }

}

bool Menu::ChooseLoadGame()
{
   unsigned current = 0;
   unsigned last = 0;
   int offset = 5;

   std::list<std::string> listSaves;
   ReadDirectory(listSaves, m_savesDir);

   m_IN_OUT->ClearAll();
   refresh();

   if (listSaves.size() == 0)
   {
      attron(COLOR_PAIR(7));
      mvprintw(offset, offset, "No saved games!");
      attron(COLOR_PAIR(1));
      refresh();
      usleep(800000);
      return false;
   }


   std::vector<std::string> listOfSaves{ std::begin(listSaves), std::end(listSaves) };

   for (unsigned i = 0; i < listOfSaves.size(); ++i)
      m_IN_OUT->Display(Coords(i + offset, offset), listOfSaves[i]);

   m_IN_OUT->Display(Coords(current + offset, offset - 1), "*");
   m_IN_OUT->Refresh();

   bool quit = false;

   while (1)
   {

      int in_char = wgetch(m_IN_OUT->m_window);

      switch (in_char)
      {
         case KEY_ENTER:
         case 10:
         case 13:
            loadGameName = listOfSaves[current];
            return true;
         case 'q':
            quit = true;
            break;

         case KEY_UP:
         case 'w':
            if (!current)
            {
               last = current;
               current = (unsigned) (listOfSaves.size() - 1);
            } else
            {
               last = current;
               current--;
            }
            break;
         case KEY_DOWN:
         case 's':
            last = current;
            current++;
            current %= listOfSaves.size();

         default:
            break;
      }

      mvaddch(offset + last, offset - 1, ' ');
      mvaddch(offset + current, offset - 1, '*');
      refresh();

      if (quit)
         return false;

   }
}

bool Menu::ChooseMap()
{
   unsigned current = 0;
   unsigned last = 0;
   int offset = 5;

   std::list<std::string> listMaps;
   ReadDirectory(listMaps, m_mapsDir);

   m_IN_OUT->ClearAll();
   refresh();


   if (listMaps.size() == 0)
   {
      attron(COLOR_PAIR(7));
      mvprintw(offset, offset, "No maps to load !");
      attron(COLOR_PAIR(1));
      refresh();
      usleep(800000);
      return false;
   }

   std::vector<std::string> listOfMaps{ std::begin(listMaps), std::end(listMaps) };

   m_IN_OUT->ClearAll();

   for (unsigned i = 0; i < listOfMaps.size(); ++i)
      m_IN_OUT->Display(Coords(i + offset, offset), listOfMaps[i]);

   m_IN_OUT->Display(Coords(current + offset, offset - 1), "*");
   m_IN_OUT->Refresh();

   bool quit = false;

   while (1)
   {
      int in_char = wgetch(m_IN_OUT->m_window);

      switch (in_char)
      {
         case KEY_ENTER:
         case 10:
         case 13:
            mapName = listOfMaps[current];
            return true;
         case 'q':
            quit = true;
            break;

         case KEY_UP:
         case 'w':
            if (!current)
            {
               last = current;
               current = (unsigned) (listOfMaps.size() - 1);
            } else
            {
               last = current;
               current--;
            }
            break;
         case KEY_DOWN:
         case 's':
            last = current;
            current++;
            current %= listOfMaps.size();

         default:
            break;
      }

      mvaddch(offset + last, offset - 1, ' ');
      mvaddch(offset + current, offset - 1, '*');
      refresh();

      if (quit)
         return false;

   }
}

void Menu::ReadDirectory(std::list<std::string> &listToLoad, std::string pathToDir) const
{
   DIR *directory;
   struct dirent *f = NULL;
   directory = opendir(pathToDir.c_str());
   while (directory)
   {
      f = readdir(directory);
      if (!f)
         break;

      if (f->d_type != DT_REG)
         continue;
      listToLoad.push_back(std::string(f->d_name));
   }

   free(directory);
   delete f;

   listToLoad.sort();

}

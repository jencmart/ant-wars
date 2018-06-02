//
// Created by jencmart on 5/27/17.
//

#include "humanPlayer.h"

Command *HumanPlayer::GetCommand() const
{
   AntHill *from;
   AntHill *to;
   /// i know that everybody says that goto is bullshit, but i kinda like it here
   Here:

   mvprintw(5, m_map->GetWidth() + 5, "[  ] SELECT YOUR ANTHILL");
   refresh();

   while (1)
   {

      /// If game was paused, skip all players who allready choosed....
      int in_char = wgetch(m_inOut->m_window);
      /// If game paused between some moves....
      if (in_char == 'p' || in_char == KEY_EXIT)
         throw Pause();

      Coords crds = GetMouseClickCoords();

      if (m_map->GetElement(crds) != NULL && m_map->GetElement(crds)->OwnerId() == 'p')
      {
         from = (AntHill *) m_map->GetElement(crds);
         break;
      }
   }

   attron(COLOR_PAIR(6));
   attron(WA_BOLD);
   mvprintw(5, m_map->GetWidth() + 6, "OK");
   attron(COLOR_PAIR(1));
   mvprintw(6, m_map->GetWidth() + 5, "[  ] SELECT OTHER ANTHILL");
   refresh();

   while (1)
   {

      /// If game was paused, skip all players who allready choosed....
      int in_char = wgetch(m_inOut->m_window);
      /// If game paused between some moves....
      if (in_char == 'p' || in_char == KEY_EXIT)
         throw Pause();

      Coords crds = GetMouseClickCoords();
      if (m_map->GetElement(crds) != NULL &&
          m_map->GetElement(crds) != from &&
          (m_map->GetElement(crds)->OwnerId() >= 'a' &&
           m_map->GetElement(crds)->OwnerId() <= 'z')
              )
      {
         to = (AntHill *) m_map->GetElement(crds);
         break;
      }
   }


   ///CIL UTOKU ZADAN
   attron(COLOR_PAIR(6));
   attron(WA_BOLD);
   mvprintw(6, m_map->GetWidth() + 6, "OK");
   attron(COLOR_PAIR(1));
   mvprintw(7, m_map->GetWidth() + 5, "[  ] COMPUTING PATH");
   refresh();

   Command *command;
   try
   { command = new Command(from, to, m_map); }
   catch (...)
   {
      mvprintw(8, m_map->GetWidth() + 5, "Path don't exist !");
      usleep(100000);
      mvprintw(5, m_map->GetWidth() + 5, "                                  ");
      mvprintw(6, m_map->GetWidth() + 5, "                                  ");
      mvprintw(7, m_map->GetWidth() + 5, "                                  ");
      mvprintw(8, m_map->GetWidth() + 5, "                                  ");
      refresh();
      goto Here;
   }

   ///Attack destination gathered
   attron(COLOR_PAIR(6));
   attron(WA_BOLD);
   mvprintw(7, m_map->GetWidth() + 6, "OK");

   mvprintw(8, m_map->GetWidth() + 5, "COMMAND ACCEPTED");
   attron(COLOR_PAIR(1));
   refresh();

  // usleep(900000);

   return command;
}

Coords HumanPlayer::GetMouseClickCoords() const
{
   int ch = 0;
   while (1)
   {
      ch = getch();
      if (ch == 'p' || ch == KEY_EXIT)
         throw Pause();
      if (ch == KEY_MOUSE)
      {
         assert(getmouse(&m_inOut->event) == OK);
         if (m_inOut->event.bstate == BUTTON1_CLICKED || BUTTON1_DOUBLE_CLICKED)
         {
            return Coords(m_inOut->event.y, m_inOut->event.x);
         }
      }

   }
}

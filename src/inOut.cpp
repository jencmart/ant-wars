//
// Created by jencmart on 5/27/17.
//

#include "inOut.h"

void InputOutput::Animate(const Coords &coords, const std::string str, int ms) const
{
   ////  wattron(m_window, COLOR_PAIR(3));
   //  mvwaddch(m_window, player.pos.y + 1, player.pos.x, ACS_UARROW);
   //  wattroff(m_window, COLOR_PAIR( 4));

   move(coords.m_row, coords.m_col);
   for (const auto c : str)
   {
      addch((const chtype)c);
      refresh();
      usleep((__useconds_t)ms);
   }
}

void InputOutput::Display(const Coords &coords, const std::string str, int ms) const
{

   ////  wattron(m_window, COLOR_PAIR(3));
   //  mvwaddch(m_window, player.pos.y + 1, player.pos.x, ACS_UARROW);
   //  wattroff(m_window, COLOR_PAIR( 4));

   move(coords.m_row, coords.m_col);
   for (const auto c : str)
   {
      addch((const chtype)c);
      refresh();
   }
}
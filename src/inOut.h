//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_INOUT_H
#define ANTWARS_INOUT_H

#include <ncurses.h>
#include <string>
#include <unistd.h>
#include "common.h"

class InputOutput
{
public:
   WINDOW *m_window;
   MEVENT event;

   InputOutput()
   {
      m_window = initscr();
      raw(); //mouse
      keypad(m_window, true);
      noecho();
      clear();
      cbreak();
      nodelay(m_window, true); //no delay
      refresh();
      curs_set(0);
      mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL); //mouse
      start_color();
      init_pair((short)'n', COLOR_WHITE, COLOR_WHITE); // NEUTRAL HILL
      init_pair( (short)'p' , COLOR_GREEN, COLOR_GREEN);  //GREEN HILL
      init_pair((short)'e', COLOR_RED, COLOR_RED);    // RED HILL
      init_pair((short)'f', COLOR_BLUE, COLOR_BLUE);  // BLUE HILL
      init_pair((short)'g', COLOR_MAGENTA, COLOR_MAGENTA);  // MAGENTA HILL
      init_pair((short)'h', COLOR_CYAN, COLOR_CYAN);  // MAGENTA HILL
      init_pair(1, COLOR_WHITE, COLOR_BLACK);        //DEFAULT
      init_pair(4, COLOR_BLACK, COLOR_YELLOW); //WALL
      init_pair(5, COLOR_CYAN, COLOR_BLACK);    //PATH COLOR
      init_pair(6, COLOR_GREEN, COLOR_BLACK);   //GREEN TEXT
      init_pair(7, COLOR_RED, COLOR_BLACK);     //RED TEXT
      init_pair(11, COLOR_BLUE, COLOR_BLACK);   //BLUE TEXT
      init_pair(12, COLOR_YELLOW, COLOR_BLACK); //YELLOW TEXT
      init_pair(13, COLOR_MAGENTA, COLOR_BLACK);   //MAGENTA TEXT
      attron(A_BOLD);
      box(m_window, 0, 0);
   };

   ~InputOutput()
   {
      ///destroy window
      endwin();
      delwin(m_window);
   }

   void ClearAll()
   {
      clear();
      refresh();
   }

   ///coords represent position
   inline void Display(const Coords &coords, const char c) const
   {
      move(coords.m_row, coords.m_col);
      addch((const chtype)c);
   };

   ///coords represent starting position
   void Display(const Coords &coords, const std::string str, int ms = 0) const;

   ///coords represent starting position
   void Animate(const Coords &coords, const std::string str, int ms = 0) const;

   void Refresh()
   { refresh(); }
};


#endif //ANTWARS_INOUT_H

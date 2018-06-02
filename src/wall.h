//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_WALL_H
#define ANTWARS_WALL_H

#include "mapElement.h"

#define WALL_COLOR 4
#define DEFAULT_COLOR 1

class Wall : public MapElement
{
public:
   Wall(Coords coords, int ID) : MapElement(coords, ID)
   {}

   /*! Display wall block(currently set to hashtag with orange BG) space....
    * @param inOut
    */
   void Display(InputOutput *inOut) const override
   {
      attron(COLOR_PAIR(WALL_COLOR));
      inOut->Display(m_origin, '#');
      attron(COLOR_PAIR(DEFAULT_COLOR));
   }

};

#endif //ANTWARS_WALL_H

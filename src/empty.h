//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_EMPTY_H
#define ANTWARS_EMPTY_H

#include "mapElement.h"

class Empty : public MapElement
{
public:
   Empty(Coords coords, int ID) : MapElement(coords, ID)
   {}

   /*! Display empty space....
    * @param inOut
    */
   inline void Display(InputOutput *inOut) const override
   { inOut->Display(m_origin, ' '); }

   /*! Empty Map element is empty, so it returns true...
    * @return
    */
   inline virtual bool IsEmpty() const override
   { return true; }
};

#endif //ANTWARS_EMPTY_H

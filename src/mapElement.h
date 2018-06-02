//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_MAPELEMENT_H
#define ANTWARS_MAPELEMENT_H


#include "inOut.h"

class DifferentOwnerException
{};

class NotEnoughAntsException
{};

class AntHill;


/*! Abstract displayable class
 */
class Displayabe
{
public:
   virtual ~Displayabe() = default;

   /*! All inherited classes must implement display method
    */
   virtual void Display(InputOutput *) const = 0;
};

class MapElement : public Displayabe
{

protected:
   Coords m_origin;
   int m_ownerID;
   int m_color;


public:
   MapElement(Coords coords, int IDowner) : m_origin(coords.m_row, coords.m_col),
                                            m_ownerID(IDowner)
   {}

   virtual ~MapElement() = default;

   /*! Return true if object is empty
    * @return
    */
   inline virtual bool IsEmpty() const
   { return false; }

   /*! Returns ownerID of the object
    * @return
    */
   inline int OwnerId() const
   { return m_ownerID; }

   /*! Returns origin coords of the object
    * @return
    */
   inline Coords GetOrigin() const
   { return m_origin; }

};

#endif //ANTWARS_MAPELEMENT_H

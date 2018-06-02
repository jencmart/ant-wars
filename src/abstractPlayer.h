//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_ABSTRACTPLAYER_H
#define ANTWARS_ABSTRACTPLAYER_H

#include "command.h"

class AbstractPlayer
{
protected:
   Map *m_map;
   int m_typeID;
   std::string m_playerName;

public:
   AbstractPlayer(Map *map,
                  int typeID,
                  std::string realName = "") : m_map(map),
                                               m_typeID(typeID),
                                               m_playerName(realName)
   {
      AssignName();
   };

   virtual ~AbstractPlayer() = default;

   /*! Based on the ownerID, assign real name to the antHill
    *  the good and creative names are assign only to the e,f,g,h ownerID
    *  although ownerID can be used from 'e' to 'z'
    *  */
   void AssignName();

   /*! ownerID getter
    * @return
    */
   inline virtual int GetID() const
   { return m_typeID; }

   /*! Return string representing real name of ant hill e.g. name of the player who represent
    * antHill with this ownerID
    * @return
    */
   inline virtual std::string GetRealName() const
   { return m_playerName; }


   /*! Every player must implement this method, to be able to return commands and play the game...
    * @return
    */
   virtual Command *GetCommand() const = 0;

};

#endif //ANTWARS_ABSTRACTPLAYER_H


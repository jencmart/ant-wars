//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_HUMANPLAYER_H
#define ANTWARS_HUMANPLAYER_H

#include <assert.h>
#include "abstractPlayer.h"

#include "inOut.h"
#include "game.h"

class HumanPlayer : public AbstractPlayer
{
private:
   InputOutput *m_inOut;
   /*! Listen to mouse clicking and return mouse state...
    * @return
    */
   Coords GetMouseClickCoords() const;

public:
   HumanPlayer(Map *map,
               int playerType,
               const std::string playerName,
               InputOutput *inOut) : AbstractPlayer(map, playerType, playerName),
                                     m_inOut(inOut)
   {};

   /*! Returns command created by humanPlayer
    * @return
    */
   Command *GetCommand() const override;

};


#endif //ANTWARS_HUMANPLAYER_H

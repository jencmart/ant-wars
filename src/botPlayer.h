//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_BOTPLAYER_H
#define ANTWARS_BOTPLAYER_H

#include "abstractPlayer.h"
#define CONSIDER_TIME  200000

class BotPlayer : public AbstractPlayer
{
private:
public:
   BotPlayer(Map *map, int playerType) : AbstractPlayer(map, playerType)
   {}

   /*! Collect command from BOT player
    * Bsed on ownerID ( 'e' 'f'  [g,z]\{p} ) different AI strategies are promoted
    * @return
    */
   Command *GetCommand() const override;

   /*! Constantly select first enemy in the enemy list
    * @param myHills
    * @param otherHills
    * @return
    */
   Command *UltraBogoAI(std::list<AntHill *> myHills,std::list<AntHill *> otherHills) const;

   /*! Randomly select my hill, Randomly select other hill. Try create command
    * @param myHills
    * @param otherHills
    * @return
    */
   Command *BogoAI(std::list<AntHill *> myHills,std::list<AntHill *> otherHills) const;

};

#endif //ANTWARS_BOTPLAYER_H

//
// Created by jencmart on 5/27/17.
//

#include "botPlayer.h"

/// Pokud ti nejde vytvorit cesta, vem nahodne nejake mraveniste nepritele a zautoc

Command *BotPlayer::GetCommand() const
{
   usleep(CONSIDER_TIME);

   while (1)
   {
      std::list<AntHill *> myAntHills;
      std::list<AntHill *> enemyAntHills;

      myAntHills = m_map->GetAntHillsByOwner(m_typeID);

      for (int i = 'e'; i < 'z'; ++i)
      {
         if (m_typeID != i)
         {
            std::list<AntHill *> tmp = m_map->GetAntHillsByOwner(i);
            enemyAntHills.insert(enemyAntHills.end(), tmp.begin(), tmp.end());
         }
      }

      /// ULTRA BOGO BOT PLAYER
      if (m_typeID == 'e')
         return UltraBogoAI(myAntHills, enemyAntHills);

      /// BOGO BOT PLAYERS
      else
         return BogoAI(myAntHills, enemyAntHills);

   }

   return NULL;
}

Command *BotPlayer::BogoAI(std::list<AntHill *> myHills, std::list<AntHill *> otherHills) const
{
   Command *command;

   while (1)
   {
      ///set iterators
      std::list<AntHill *>::iterator randItOther = otherHills.begin();
      std::list<AntHill *>::iterator randItMine = myHills.begin();

      ///get randIterators
      std::advance(randItOther, std::rand() % otherHills.size());
      std::advance(randItMine, std::rand() % myHills.size());

      ///try to create command
      try
      { command = new Command(*randItMine, *randItOther, m_map); }
      catch (...)
      { continue; }

      return command;
   }
}

Command *BotPlayer::UltraBogoAI(std::list<AntHill *> myHills, std::list<AntHill *> otherHills) const
{
   Command * command;

   for( auto myHill : myHills)
   {
      try
      { command = new Command(myHill, * (otherHills.begin()), m_map); }
      catch (...)
      { continue; }

      return command;
   }

   return  NULL;
}

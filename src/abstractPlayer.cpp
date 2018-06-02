//
// Created by jencmart on 6/3/17.
//

#include "abstractPlayer.h"

void AbstractPlayer::AssignName()
{
   for (int i = 'e'; i <= 'z'; ++i)
      {
         if (m_typeID == 'e')
         {
            m_playerName = "RedHill ants";
            break;
         } else if (m_typeID == 'f')
         {
            m_playerName = "BlueHill ants";
            break;
         } else if (m_typeID == 'g')
         {
            m_playerName = "PurpleHill ants";
            break;
         } else if (m_typeID != 'p')
         {
            m_playerName = m_typeID + "Hill ants";
            break;
         }
      }
}

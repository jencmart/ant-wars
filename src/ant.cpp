//
// Created by jencmart on 5/27/17.
//

#include "ant.h"

void Ant::Move()
{
   ///Ask path for the next coords
   Coords nextCoords = m_path->GetNextCoords(m_sourceAntHill, m_origin);

   /// If next coords are destination AntHill coords, let AntHill deal with myself
   if (m_path->IsDestination(m_sourceAntHill, nextCoords))
      (m_path->GetTargetAntHill(m_sourceAntHill))->DealWithAnt(this);

   ///If there is an enemy Ant fight with him for life and death in merciless bloody duel
   if (m_path->IsEnemeyAnt(m_sourceAntHill, nextCoords) != NULL)
      (m_path->IsEnemeyAnt(m_sourceAntHill, nextCoords))->FightInDuel(this);

   ///And move to the next coord....
   m_origin = nextCoords;
}


void Ant::Display(InputOutput *) const
{
   attron(COLOR_PAIR((short)m_ownerID));


   if(m_ownerID >= 'h' &&  m_ownerID != 'p' )
   {
      std::list<int> myList{'e', 'f', 'g', 'h', 'p'};
      std::list<int>::iterator rand = myList.begin();
      ///get randIterators
      std::advance(rand, std::rand() % myList.size());
      attron(COLOR_PAIR((short)(*rand)));
   }


   mvprintw(m_origin.m_row, m_origin.m_col, "O");
   refresh();
   attron(COLOR_PAIR(1));

   refresh();
}

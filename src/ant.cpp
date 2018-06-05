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

      int color = m_ownerID;
   if(color >= 'h' && color != 'n' &&  color != 'p' )
   {
      std::list<int> myList{'e', 'f', 'g', 'h', 'p'};
      std::list<int>::iterator rand = myList.begin();
      std::advance(rand, std::rand() % myList.size());
      color = (*rand);
   }

   if(color == 'n')
      attron(COLOR_PAIR(2));
   else if(color == 'p')
      attron(COLOR_PAIR(3));
   else if(color == 'e')
      attron(COLOR_PAIR(8));
   else if(color == 'f')
      attron(COLOR_PAIR(9));
   else if(color == 'g')
      attron(COLOR_PAIR(10));
   else
      attron(COLOR_PAIR(14));



   mvprintw(m_origin.m_row, m_origin.m_col, "O");
   refresh();
   attron(COLOR_PAIR(1));

   refresh();
}

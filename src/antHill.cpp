//
// Created by jencmart on 5/27/17.
//

#include "antHill.h"
#include "ant.h"

Ant *AntHill::GetAnt(int ownerID, Path *path)
{
   if (ownerID != m_ownerID)
      throw DifferentOwnerException();

   if (m_numOfAnts == 1)
      throw NotEnoughAntsException();

   m_numOfAnts--;
   return new Ant(this, path);
}

void AntHill::Display(InputOutput *inOut) const
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
   
   attron(WA_BOLD);


   /// dipslay border
   mvprintw(m_origin.m_row, m_origin.m_col, "+---+");
   mvprintw(m_origin.m_row + 2, m_origin.m_col, "+---+");
   mvprintw(m_origin.m_row + 1, m_origin.m_col, "|");
   mvprintw(m_origin.m_row + 1, m_origin.m_col + 3, " |");
   attron(COLOR_PAIR(1));

   /// display info
   move(m_origin.m_row + 1, m_origin.m_col + 1);
   addch((const chtype) m_name);
   mvprintw(m_origin.m_row + 1, m_origin.m_col + 2, "%d", m_numOfAnts);

}

void AntHill::DealWithAnt(Ant *incomingAnt)
{
   if (incomingAnt->OwnerId() == m_ownerID || m_ownerID == 'n')
      RiseAntNumber(incomingAnt);
   else
      DecreaseAntNumber();

   incomingAnt->Kill();
}

void AntHill::RiseAntNumber(MapElement *ant)
{
   if (m_ownerID == 'n' && m_numOfAnts)
   {
      DecreaseAntNumber();
      return;
   }
   if (m_numOfAnts == 0)
   {
      m_ownerID = ant->OwnerId();
      m_numOfAnts++;
   } else if (m_numOfAnts < MAX_LOAD)
      m_numOfAnts++;
}

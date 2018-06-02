//
// Created by jencmart on 5/27/17.
//

#include "path.h"

//TODO TADY SE TO POSERE POPICUJE ZACIKLI A UMRE
/*!
 * for all edge coordinates of "From" AntHill find shortest path to all edge coordinates of Anthill "To".
 * @param from
 * @param to
 * @throws PathNotExistException if path dont exists
 */
void Path::GeneratePathCoords(AntHill *fromAntHill, AntHill *toAntHill, bool animate)
{
   Coords fromCrds = fromAntHill->GetMiddle();
   Coords toCrds = toAntHill->GetMiddle();

   refresh();

   try
   { m_coords = BreadthFirstSearch(fromCrds, toCrds, animate); }
   catch (...)
   { throw PathNotExistException(); }
}


Coords Path::GetNextCoords(AntHill *antSourceAntHill, Coords currentCoords)
{
   refresh();

   for (unsigned i = 0; i < m_coords.size(); ++i)
   {
      if (m_coords[i] == currentCoords)
      {
         /// meaning that ant would like to go right...
         if (antSourceAntHill == m_from)
         {
            refresh();
            return m_coords[i + 1];

         }

            /// else ant must would like to from direction...
         else
         {
            refresh();
            //  usleep(100000); //TODO this sleep slows down ants nicely
            return m_coords[i - 1];
         }
      }
   }

   ///for happy non void return; but coords are always found...
   return Coords(0, 0);
}


bool Path::IsDestination(AntHill *antSourceAntHill, Coords antNextCoords)
{
   if (m_from == antSourceAntHill)
      return m_map->GetElement(antNextCoords) == m_to;
   else
      return m_map->GetElement(antNextCoords) == m_from;
}

AntHill *Path::GetTargetAntHill(AntHill *antSourceAntHill)
{
   if (m_from == antSourceAntHill)
      return m_to;
   else
      return m_from;
}

Ant *Path::IsEnemeyAnt(AntHill *antSourceAntHill, Coords antNextCoords)
{
   std::list<Ant *>::iterator antIter;


   ///ant goes from FROM to TO and the path is shared with other direction ant...
   if (antSourceAntHill == m_from && m_usedByTo)
   {
      for (antIter = m_toAnts.begin(); antIter != m_toAnts.end(); ++antIter)
      {
         if (((MapElement *) (*antIter))->GetOrigin() == antNextCoords &&
             antSourceAntHill->OwnerId() != ((MapElement *) (*antIter))->OwnerId())
         {
            return *antIter;
         }
      }
   } else if (antSourceAntHill == m_to && m_usedByFrom)
   {
      for (antIter = m_fromAnts.begin(); antIter != m_fromAnts.end(); ++antIter)
      {
         if (((MapElement *) (*antIter))->GetOrigin() == antNextCoords &&
             antSourceAntHill->OwnerId() != ((MapElement *) (*antIter))->OwnerId())
         {
            return *antIter;
         }
      }
   }
   return NULL;
}

void Path::AddAntOnPath(AntHill *sourceAntHill, Ant *newAntToAdd)
{
   if (sourceAntHill == m_from)
      m_fromAnts.push_back(newAntToAdd);
   else
      m_toAnts.push_back(newAntToAdd);
}

void Path::RemoveAntOnPath(AntHill *sourceAntHill, Ant *deadAntToRemove)
{
   /// if the ant if from antHill which firstly created the path....
   if (sourceAntHill == m_from)
   {
      for (auto x = m_fromAnts.begin(); x != m_fromAnts.end();)
      {
         if (*x == deadAntToRemove)
         {
            x = m_fromAnts.erase(x);
            break;
         } else
            ++x;
      }
   } else
   {

      for (auto x = m_toAnts.begin(); x != m_toAnts.end();)
      {
         if (*x == deadAntToRemove)
         {
            x = m_toAnts.erase(x);
            break;
         } else
            ++x;
      }
   }

}

std::vector<Coords, std::allocator<Coords>>
Path::BreadthFirstSearch(const Coords start, const Coords finish, bool animate) const
{
   std::list<Coords> queue; // .front() .pop_front() .push_back()
   std::set<Coords> open; // .insert(coords)
   std::set<Coords> closed; // .insert(coords) .count(coords) ... not => 0
   std::map<Coords, Coords> predacessor; // .insert(Pair<>()

   ///add start element to queue
   queue.push_back(start);
   open.insert(start);

   while (queue.size() != 0)
   {
      ///if expanded is our final node
      if (queue.front() == finish)
      {
         attron(COLOR_PAIR(1));
         return ReconstructPath(start, finish, predacessor, animate);
      }

      /// expand first element in queue
      for (auto &expanded : m_map->expandCoord(queue.front(), m_from, m_to))
      {
         /// if expanded element was not used yet
         if (!open.count(expanded) && !closed.count(expanded))
         {
            if (animate)
            {
               attron(COLOR_PAIR('p'));
               mvprintw(expanded.m_row, expanded.m_col, "+");
               refresh();
            }

            ///  add it to back of queue and mark it open
            queue.push_back(expanded);
            open.insert(expanded);
            /// and mark predacessor
            predacessor.insert(std::pair<Coords, Coords>(expanded, Coords(queue.front().m_row,
                                                                          queue.front().m_col)));
         }

      }

      ///finally add elmenet from top of queue to closed and pop him from queue
      closed.insert(Coords(queue.front().m_row, queue.front().m_col));
      queue.pop_front();
   }

   /// in this case path do not exist
   throw PathNotExistException();
}

std::vector<Coords>
Path::ReconstructPath(Coords start, Coords finish, std::map<Coords, Coords> predacessors,
                      bool animate)
{
   std::vector<Coords> finalPath;
   finalPath.insert(finalPath.begin(), finish);
   Coords tmp = finish;
   while (tmp != start)
   {
      finalPath.insert(finalPath.begin(), predacessors.find(tmp)->second);
      tmp = predacessors.find(tmp)->second;
   }


   if (animate)
   {
      attron(COLOR_PAIR(6));
      for (auto x : finalPath)
      {
         mvprintw(x.m_row, x.m_col, "*");
         refresh();
      }

      usleep(ANIMATE_SLEEP);
   }

   return finalPath;
}

void Path::Display(InputOutput *) const
{
   attron(COLOR_PAIR(5));
   attron(WA_BOLD);

   for (auto x : m_coords)
      mvprintw(x.m_row, x.m_col, "*");

   attron(COLOR_PAIR(1));
}

void Path::DisplayAnts(InputOutput *a) const
{
   for (auto &ant :  m_fromAnts)
      ((MapElement *) ant)->Display(a);

   for (auto &ant :  m_toAnts)
      ((MapElement *) ant)->Display(a);

   refresh();
}



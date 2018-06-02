//
// Created by jencmart on 5/27/17.
//

#include "command.h"

void Command::InitializeAnts(std::list<Coords> listOfAntsCoords)
{
   for (auto antCoords : listOfAntsCoords)
   {
      Ant *newAnt = new Ant(m_from, m_path, m_fromOwner, antCoords);
      m_antList.push_back(newAnt);
      m_path->AddAntOnPath(m_from, newAnt);
   }
}

void Command::Process()
{
   /// In case of ant's death delete his instance and remove pointer to him from list of ants
   for (auto antIt = m_antList.begin(); antIt != m_antList.end();)
   {
      if ((*antIt)->IsDead())
      {
         m_path->RemoveAntOnPath(m_from, *antIt);
         delete *antIt;
         antIt = m_antList.erase(antIt);
      } else
         ++antIt;
   }

   for (auto ant : m_antList)
      ant->Move();

   /// If there are still same ants awaiting to be born and send to path of glory.....
   if (m_waitingAnts)
   {
      /// ...ask AntHill to born new innoncent little one...
      Ant *newAnt = NULL;
      try
      {
         newAnt = m_from->GetAnt(m_fromOwner, m_path);
         ///.... if so, start his journery by putting him to the beggining of the path....
         m_antList.push_back(newAnt);
         m_path->AddAntOnPath(m_from, newAnt);
         //// ...and decrease number of waiting ones....
         m_waitingAnts--;
      }
         /// But if there is exception.... KILL ALL ANTS BY THE HAND OF GOD !
      catch (DifferentOwnerException &x)
      {
         m_waitingAnts = 0;
      }
      catch (NotEnoughAntsException &x)
      {
         m_waitingAnts = 0;
      }
   }

   /// In case of ant's death delete his instance and remove pointer to him from list of ants
   for (auto antIt = m_antList.begin(); antIt != m_antList.end();)
   {
      if ((*antIt)->IsDead())
      {
         m_path->RemoveAntOnPath(m_from, *antIt);
         delete *antIt;
         antIt = m_antList.erase(antIt);
      } else
         ++antIt;
   }
}

void Command::CreateOrConnectPath(bool animate)
{
   /// if from destination hill leads path to source anthil..
   if (m_to->GetPath(m_from) != NULL)
   {
      /// we ask for this path .. priradime cestu commandu
      m_path = m_to->GetPath(m_from);

      ///  we inform path that it's used by another coommand
      m_path->AddUser(m_from, m_to);

      /// we inform anthyhill that path leads from it
      m_from->AddPathWhichLeadsTo(m_to, m_path);
   }

      /// if there is no path yet.....
   else
   {
      try
      {
         m_path = new Path(m_from, m_to, m_map, animate);
      } /// create new path for the command
      catch (PathNotExistException &x)          /// path set itselves that it is used by this command
      { throw x; }


      m_from->AddPathWhichLeadsTo(m_to, m_path); /// we inform anthill that path leads from him
      m_map->AddPath(m_path); ///adds path to map's list of elements....
   }
}

std::ostream &operator<<(std::ostream &os, Command &x)
{
   os << x.m_from->GetOrigin().m_row << ' ' << x.m_from->GetOrigin().m_col << ' ' << ///from coords
      x.m_to->GetOrigin().m_row << ' ' << x.m_to->GetOrigin().m_col << ' '             ///to coords
      << x.m_fromOwner << ' ' << x.m_toOwner
      << ' '                                                       /// fromID, toID
      << x.m_waitingAnts << ' ' << x.m_antList.size();            ///num waiting, num walking

   /// print ant ant positions
   unsigned i = 0;
   for (auto ant : x.m_antList)
   {
      if (!i)
         os << ' ';
      os << ant->GetOrigin().m_row << ' ' << ant->GetOrigin().m_col;

      if (++i < x.m_antList.size())
         os << ' ';
   }

   return os;
}

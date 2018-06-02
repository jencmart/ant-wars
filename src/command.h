//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_COMMAND_H
#define ANTWARS_COMMAND_H

#include <list>
#include "path.h"
#include "ant.h"

#define  ANTS_PER_CMD 5
#define  ANIMATION true

class Command
{
private:
   int m_waitingAnts;
   std::list<Ant *> m_antList;
   AntHill *m_from;
   AntHill *m_to;
   int m_fromOwner;
   int m_toOwner;
   Map *m_map;
   Path *m_path;
public:

   /*! Constructor used when loading commands from saved game
    * @param waitingAnts
    * @param from
    * @param to
    * @param fromOwner
    * @param toOwner
    * @param map
    * @param antCoords
    */
   Command(int waitingAnts,
           AntHill *from,
           AntHill *to,
           int fromOwner,
           int toOwner,
           Map *map,
           std::list<Coords> antCoords
   ) : m_waitingAnts(0),
       m_from(from),
       m_to(to),
       m_fromOwner(fromOwner),
       m_toOwner(toOwner),
       m_map(map),
       m_path(NULL)
   {

      /// optional false argument here tells path not to visully display pathfinding
      /// and suppres aesthetic animation sleeps
      CreateOrConnectPath(false);

      InitializeAnts(antCoords);
   }

   /*! Ingame command constructor used by all players.
    * Each player must be able to use this constructor
    * @param from
    * @param to
    * @param map
    */
   Command(AntHill *from, AntHill *to, Map *map) : m_waitingAnts(ANTS_PER_CMD),
                                                   m_from(from),
                                                   m_to(to),
                                                   m_fromOwner(from->OwnerId()),
                                                   m_toOwner(to->OwnerId()),
                                                   m_map(map),
                                                   m_path(NULL)
   {
      CreateOrConnectPath();
   }


   /*! Destructor removes in path and in antHill usage by this command instance.
    * If path is not used anymore, it also delete path.
    */
   ~Command()
   {
      m_path->RemoveUser(m_from);
      m_from->RemovePathWhichLeads(m_path);
      if (m_path->NoUsers())
      {
         m_map->DestructPath(m_path);
         delete m_path;
      }

      /// happens only when quitting running game with ants instances on path....
      for (auto ant : m_antList)
         delete ant;
   }

   /*! Assign path to cammand.
    * If path between two anthills allready exists, command will connect to this path
    * If path dont exist yet, command will ask to create new one
    * @param animate
    * @throws PathNotExistException if new between two antHills was not found
    */
   void CreateOrConnectPath(bool animate = ANIMATION);

   /*! Process command by one step.
    * That consists of moving existing ants by one coord
    * Constructing new ants if there are still some waiting ants
    * Finally delete all ants who died during move
    */
   void Process();

   /*! Operator << is used to print command to the save file
    * @param os
    * @param x
    * @return os
    */
   friend std::ostream &operator<<(std::ostream &os, Command &x);

   /*! Command stante getter
    * @return ture - command finished
    * @return false - command not finished
    */
   inline bool Done() const
   { return m_waitingAnts == 0 && m_antList.size() == 0; }

   /*! Used when loading game to init ants at specific positions.
    */
   void InitializeAnts(std::list<Coords>);
};

#endif //ANTWARS_COMMAND_H

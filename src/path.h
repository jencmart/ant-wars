//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_PATH_H
#define ANTWARS_PATH_H

#include <list>
#include <map>
#include "map.h"
#include "antHill.h"

#define ANIMATE_SLEEP 100000

class Map;

class Ant;

/**
 * Path is initialized and defined by list of coordinates.
 * It is guaranteed by Map::FindPath() that first and last coord that first and last
 * coordinates are part of edges of some AntHills.
 */
class Path : public Displayabe
{
private:
   std::vector<Coords> m_coords;
   AntHill *m_from;
   AntHill *m_to;
   Map *m_map;
   bool m_usedByFrom;
   bool m_usedByTo;
   std::list<Ant *> m_fromAnts;
   std::list<Ant *> m_toAnts;

   /*! Generate path coordinates between two AntHills.
   * @param from
   * @param to
   * @throws PathNotExistException if there is obstacle or other Anthill between Anthill from and Anthill to
   * @return
   */
   void GeneratePathCoords(AntHill *from, AntHill *to, bool animate);

   /*! Path reconstruction is support method for BFS
   * @param start
   * @param finish
   * @param predacessors
   * @return
   */
   static std::vector<Coords>
   ReconstructPath(Coords fromCoords, Coords toCoords, std::map<Coords, Coords> predacessors,
                   bool animate);


public:


   Path(AntHill *from, AntHill *to, Map *map) :
           m_from(from),
           m_to(to),
           m_map(map)
           {
              GeneratePathCoords(from, to, false);
           };

   /*! Constructor for used by command
    * @param from
    * @param to
    * @param map
    * @param animate
    */
   Path(AntHill *from, AntHill *to, Map *map, bool animate) :
           m_from(from),
           m_to(to),
           m_map(map),
           m_usedByFrom(true),
           m_usedByTo(false)
   {
      GeneratePathCoords(from, to, animate);
   }

   ~Path() = default;

   /*! Calculate Manhattan distance between two points
   * Can be used either in some AI of bot players or to compute path by some
    * pathfinding algorithm such as GreedySearch or A* or Dijkstra algorithm
   * @param from
   * @param to
   * @return
   */
   inline static int ManhattanDistance(Coords from, Coords to)
   { return std::max(std::abs(from.m_row - to.m_row), std::abs(from.m_col - to.m_col)); }


   /*! Very nice and simple implementation of BFS. much wow
    * Compute shortest path between two coordinates
    * it takes in account obstacles on the path
    * Path is not aesthetic, because going slantwise have same value as going straight.
    * To introduce more aesthetic shortest path, A* have to be implemented.
    * (It's not so hard i would have probably done it, if I would have one more day to
    * work on this program................)
    */
   std::vector<Coords, std::allocator<Coords>>
   BreadthFirstSearch(const Coords start, const Coords finish, bool animate) const;

   /*! return length of path
    * @return
    */
   inline int PathLength(void) const
   { return (int) m_coords.size() ; }

   /*! Display path over the map...
    * @param
    */
   void Display(InputOutput *a) const override;

   /*! Display ants, which on the path....
    * @param a
    */
   void DisplayAnts(InputOutput *a) const;

   /*! Returns initial position for the ant.
    * That means starting position of the path if  ant go from FROM to TO
    * Or last positon of the path if ant goues fro TO to FROM
    * @param antHill
    * @return
    */
   inline Coords GetAntOrigin(AntHill *sourceAntHill) const
   { return sourceAntHill == m_from ? *(m_coords.begin()) : *(--m_coords.end()); }

   /*! Adds another commad who uses this path... (e.g. direction of anthills )
    * If there allready exist path between these AntHills, but in "reversed" direction, add also path in other direction...
    * @param one
    * @param other
    */
   inline void AddUser(AntHill *one, AntHill *other)
   { m_usedByTo = true; }


   /*!
    * Remove user who had order from hist from antHill...
    * @param one
    * @param other
    */
   inline void RemoveUser(AntHill *one)
   {
      if (one == m_from)
         m_usedByFrom = false;
      else
         m_usedByTo = false;
   }


   /*! User status getter
    * @return true - if no users of this path
    * @return false - if some users of this path
    */
   inline bool NoUsers() const
   { return !m_usedByTo && !m_usedByFrom; }

   /*! Return coordinates for the ant, who asks for them
    * Source anthill of the ant must be taken to account to determine
    * if ant is going FROM->TO or TO->FRO.
    * @param pHill
    * @param currentCoords
    * @return
    */
   Coords GetNextCoords(AntHill *pHill, Coords currentCoords);

   /*! Used by ant
    * @param antSourceAntHill
    * @param antNextCoords
    * @return true - if ant reached his destination
    * @return false - if not
    */
   bool IsDestination(AntHill *antSourceAntHill, Coords antNextCoords);

   /*! Returns target anthill for the ant
    * @param antSourceAntHill
    * @return
    */
   AntHill *GetTargetAntHill(AntHill *antSourceAntHill);

   /*! Return true / false wehether enemey ant is found at given coords
   * @param antSourceAntHill
   * @param antNextCoords
   * @return
   */
   Ant *IsEnemeyAnt(AntHill *antSourceAntHill, Coords antNextCoords);

   /*! Adds ant ptr to the path when new ant is constructed
    * @param sourceAntAntHill
    * @param newAntToAdd
    */
   void AddAntOnPath(AntHill *sourceAntAntHill, Ant *newAntToAdd);

   /*! Removes (usuallu dead) ant from the path
    * @param antSourceAntHill
    * @param deadAntToRemove
    */
   void RemoveAntOnPath(AntHill *antSourceAntHill, Ant *deadAntToRemove);
};


#endif //ANTWARS_PATH_H

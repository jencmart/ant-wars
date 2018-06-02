//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_ANTHILL_H
#define ANTWARS_ANTHILL_H

#include <vector>
#include "mapElement.h"

class Ant;

class Path;

#define MAX_LOAD 20      /// Maximal and default number of ants in antHills
#define NEUTRAL_LOAD 10  /// Default number of ants in neutral antHills

class AntHill : public MapElement
{

private:
   int m_numOfAnts;
   char m_name;
   AntHill *m_pathLeadsTo;
   Path *m_path;

   /*! Riseds or decreases number of ant in antHill.
    * In case that antHill is neutral and have ants, number of ants is decreased.
    * In case that antHill is neutral and have zero ants, number of ants is increased
    * and ownerId is changed to the ant's ownerID
    * @param ptr to ant which entered antHill
    */
   void RiseAntNumber(MapElement *ant);


   /*! Decrease number of ant in antHill.
    * If number of ants became zero, owner of ant hill is set to neutral
    */
   inline void DecreaseAntNumber()
   {
      if (!--m_numOfAnts)
         m_ownerID = 'n';
   }

public:

   /*! In game constructor
    * @param coords  of origin of antHill (left to corner)
    * @param ownerID ownerID, supposed to be between 'e' and 'z'
    * @param name of antHill, supposed to be between 'A' and 'Z'
    */
   AntHill(Coords coords,
           int ownerID,
           char name) : MapElement(coords, ownerID),
                        m_numOfAnts(MAX_LOAD),
                        m_name(name),
                        m_pathLeadsTo(NULL),
                        m_path(NULL)
   {
      if (ownerID == 'n')
         m_numOfAnts = NEUTRAL_LOAD;
   }

   ~AntHill() = default;

   /*! Return ptr to path which leads to anther AntHill.
    * If there is no such a path, NULL is returned
    * TODO - if realtime game would be implemented, this must be rewritten to the list of paths...
    * @param to
    * @return ptr * - if path exists
    * @return NUL   - if path don't exists
    */
   inline Path *GetPath(AntHill *to) const
   {
      if (to == m_pathLeadsTo)
         return m_path;
      return NULL;
   }


   /*! Increase number of ants in antHill.
    * Ant hill must not be neutral (this allso covers case when there is 0 ants)
    */
   inline void GiveBirth()
   {
      if (m_ownerID != 'n' && m_numOfAnts < 20)
         m_numOfAnts++;
   }

   /*! Set owner and number of ants in antHill.
    * Used by when loading game. to set state of antHill istance, which usually
    * differ from state which was loaded from map
    * @param ownerAndNumAnts - pair<ownerID,numberOfAnts>
    */
   inline void SetState(std::pair<int, int> ownerAndNumAnts)
   {
      m_ownerID = ownerAndNumAnts.first;
      m_numOfAnts = ownerAndNumAnts.second;
   }

   /*! Adds path which leads to another antHill
    * TODO - if realtime game would be implemented, this must be rewritten to the list of paths...
    * @param to
    * @param path
    */
   inline void AddPathWhichLeadsTo(AntHill *to, Path *path)
   {
      m_pathLeadsTo = to;
      m_path = path;
   }

   /*! Removes path which leads to...
    * TODO - if realtime game would be implemented, this must be rewritten to the list of paths...
    * TODO - currently is parameter (ptr to path)unused, but in realtime version it would be needed to find the path
    */
   inline void RemovePathWhichLeads(Path *path)
   {
      m_path = NULL;
      m_pathLeadsTo = NULL;
   }

   /*! Returns coordinates of the middle of antHill.
    * This is used by pathFinding algorithm to get start(end) point of the path
    * @return
    */
   inline Coords GetMiddle() const
   {
      return Coords(m_origin.m_row + 1, m_origin.m_col + 2);
   }

   /*! Returns (char) name of antHill.
    * TODO Currently unused, but can be used by Ant::Display() to get ant's shape
    * @return
    */
   inline char GetName() const
   {
      return m_name;
   }

   /*!If possible, return's new ant instance.
    * Applicant must share ownerID of this AntHill. Else DifferentOwnerException is thrown.
    * If numbers of Ants in AntHill is greater than 1, returns pointer to new Ant instance.
    * If numer of Ants is lesser or equal to 1 NotEnoughAntsException.
    * @param ID_toCheck
    * @param path
    * @throws DifferentOwnerException if applicant have different owner
    * @throws NotEnoughAntsException if antHill have <=1 number of ants
    * @return ptr to new instance of ant
    */
   Ant *GetAnt(int ID_toCheck, Path *path);

   /*! Displays antHil
    * @param inOut
    */
   void Display(InputOutput *inOut) const;

   /*!Determines if ant have same or different owner.
    * That calls RiseAntNumbers(same ownerID or this antHill is neutral)
    * or DecreaseAntNumbers(different ownerID)
    */
   void DealWithAnt(Ant *incomingAnt);

   /*! NumberOfAnts getter
    * @return number of ants
    */
   int GetNumOfAnts() const
   {
      return m_numOfAnts;
   }
};


#endif //ANTWARS_ANTHILL_H

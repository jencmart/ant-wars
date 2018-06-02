//
// Created by jencmart on 5/25/17.
//

#ifndef ANTWARS_ANT_H
#define ANTWARS_ANT_H

#include "mapElement.h"
#include "path.h"


class Ant : public MapElement
{
private:
   bool m_isDead;
   Path *m_path;
   AntHill *m_sourceAntHill;
public:

   /*! Constructor used by game::Load() method.
    * Ant is initialized specific ownerID at specific coords.
    * @param sourceAntHill
    * @param path
    * @param ownerId
    * @param initCoords
    */
   Ant(AntHill *sourceAntHill, Path *path, int ownerId, Coords initCoords) :
           MapElement(initCoords, ownerId),
           m_isDead(false),
           m_path(path),
           m_sourceAntHill(sourceAntHill)
   {}

   /*!Constructor for creating ant during gameplay.
    * It is used by AntHill (which is in charge by Command instance) to create instance of Ant.
    * Ant ownerID is set to AntHill ownerID and position is set to the coordinates provided by path instance.
    * (that should be beginning or end of the path, based on if the path is shared with other command
    * or not.
    * @param sourceAntHill
    * @param path
    */
   Ant(AntHill *sourceAntHill,
       Path *path) :
           MapElement(path->GetAntOrigin(sourceAntHill), sourceAntHill->OwnerId()),
           m_isDead(false),
           m_path(path),
           m_sourceAntHill(sourceAntHill)
   {}


   /*! Ant display method.
  * Ant collect information about color ant shape and than display itselves.
  * ownerID which determine color must be saved, because at the time, when ant
  * is on the way, the owner of source antHill can be changed.
  */
   void Display(InputOutput *) const override;


   /*!Mark Ant as dead.
    */
   inline void Kill()
   { m_isDead = true; }

   /*! Kill attacking Ant ant kill yourselves as well.
    * @param ptr to enemyAnt
    */
   inline void FightInDuel(Ant *enemyAnt)
   {
      enemyAnt->Kill();
      this->Kill();
   }

   /*!Move ant by one coord.
    * Let ant move by one coordinate provided by path. If there will be enemy ant or if coord will be end of the path
    * deal with it appropriately. In case of enemy ant FightInDuel with him. In case of AntHill let the AntHill to determine
    * what will happend.
    */
   void Move();

   /*! m_isDead getter.
    * Renturns true if Ant is marked as dead.
    * @return
    */
   inline bool IsDead() const
   { return m_isDead; }
};


#endif //ANTWARS_ANT_H



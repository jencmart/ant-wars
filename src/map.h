//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_MAP_H
#define ANTWARS_MAP_H

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <math.h>
#include <stack>
#include <set>
#include <map>
#include <list>

#include "mapElement.h"
#include "wall.h"
#include "empty.h"
#include "antHill.h"
#include "exceptions.h"
#include "path.h"

//class Path;

class Map
{
private:
   int m_height;
   int m_width;
   std::string m_mapName;
   int m_numOfAntHills;
   std::vector<std::vector<MapElement *>> m_mapMatrix;          //2D matrix of ptrs to MapElement
   std::vector<MapElement *> m_listOfElements;     //list ptrs of MapElements
   std::vector<AntHill *> m_listOfAntHills;
   std::list<Path *> m_listOfPaths;
   std::set<int> m_players;
   std::string m_pathToMap;


   ///******* Private methods for loading map file *******************
   void CountRowsCols(const std::string &mapName);

   void LoadMapFromFile(const std::string);

   void LoadMap(const std::vector<std::vector<char>> &);

   void LoadAntHill(int, int, const std::vector<std::vector<char>> &);

   void loadWall(int, int, const std::vector<std::vector<char>> &);

   void LoadEmpty(int, int, const std::vector<std::vector<char>> &);

   void CheckAntHillFormat(int, int, const std::vector<std::vector<char>> &) const;

   inline bool PartOfExistingAntHill(int x, int y) const
   { return m_mapMatrix[x][y] != NULL; }

public:

   Map(const std::string pathToMaps,
       const std::string mapName) :

           m_mapName(mapName),
           m_numOfAntHills(0)
   {
      m_pathToMap = pathToMaps + '/' + mapName;


      try
      { LoadMapFromFile(m_pathToMap); }
      catch (UnexpectedCharacter &x)
      {
         clear();
         refresh();
         attron(COLOR_PAIR(7));
         mvprintw(1, 1, "Unexpected character row: %d col: %d", x.m_row, x.m_col);
         attron(COLOR_PAIR(1));
         refresh();
         ///delete list of elements
         for (auto mapElem : m_listOfElements)
            delete mapElem;
         usleep(3000000);
         throw x;
      }

      catch( ErrorWhileReadingFile &x)
      {
         clear();
         refresh();
         attron(COLOR_PAIR(7));
         mvprintw(1, 1, "Error while reading map file");
         attron(COLOR_PAIR(1));
         refresh();
         ///delete list of elements
         for (auto mapElem : m_listOfElements)
            delete mapElem;
         usleep(2000000);
         throw x;
      }
   }

   ~Map()
   {
      ///delete list of elements
      for (auto mapElem : m_listOfElements)
         delete mapElem;

      /// delete list of paths -- not needed all paths are deleted at this point....
   }

   /*! ...
    * @return string with map name
    */
   std::string GetMapName() const
   { return m_mapName; }

   /*! ...
    * @return int - width of the map
    */
   inline int GetWidth() const
   { return m_width; }

   /*!
    * Returns list of AntHills, which belongs to player with ceratin ID
    * @param ownerId
    * @return
    */
   std::list<AntHill *> GetAntHillsByOwner(int ownerId);

   inline int getNumOfAntHills() const
   { return (int) m_listOfAntHills.size(); }


   /*! Command all anthills to increse number of ants
    */
   void RiseAntNumbers() const;


   /*! Returns number of antHills owned by player with specified ownerID
    * @param ownerId
    * @return
    */
   int getNumOfAntHillsByOwner(int ownerId) const;


   /*!
    * Dipslay map call .Dsiplay() on all Map Elements
    */
   void Display(InputOutput *) const;

   /*!
    * Returns element at specified position
    */
   MapElement *GetElement(Coords) const;

   /*! Evaluate if coordinates are "empty" for the path
    * that means that object on succh coordinates must be empty or must be one of the anthills
    * between which path would be
    * @param coords
    * @param a
    * @param b
    * @return
    */
   bool EvaluateCoords(const Coords &coords, AntHill *a, AntHill *b) const;

   /*!
    * Return vector of coordinates which are either ompty or where desired antHill lies...
    */
   std::vector<Coords> expandCoord(Coords coords, AntHill *from, AntHill *to) const;

   /*!Adds path created by command
    * @param path
    */
   inline void AddPath(Path *path)
   { m_listOfPaths.push_back(path); }

   /*! Return true if player with specified ownerID exists
    * @param i
    * @return
    */
   inline bool HavePlayer(int i) const
   { return m_players.count(i) != 0; }


   /*! Removes path from list of paths
    * @param path
    */
   inline void DestructPath(Path *path)
   { m_listOfPaths.remove(path); }

   /*! Used when saving the game. States of all antHills are collected.
    * It is in format par<ownerID, numberOfAnts>
    * @return
    */
   std::list<std::pair<char, int>> GetAntHillStates() const;

   /*! Used when loading game. Set all antHills to specified state.
    * @param list
    */
   void UpdateAntHills(std::list<std::pair<int, int>> list);
};

#endif //ANTWARS_MAP_H

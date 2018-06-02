//
// Created by jencmart on 5/27/17.
//
#include "map.h"





///******************************* CheckAntHillFormat ****************************************************************
/*! Check characters at positions by which AntHill is supposed to be represented.
 *
 * @param row
 * @param col
 * @param charMap
 */
void Map::CheckAntHillFormat(int row, int col, const std::vector<std::vector<char>> &charMap) const
{

   /// Ant Hill must not interfer to the border or beyond...
   if (col + 6 >= m_width || row + 4 >= m_height)
      throw UnexpectedCharacter(row, col, charMap[row][col]);

   ///first and third (last) line must be "*****" ...
   for (int j = col; j < col + 5; ++j)
      if (charMap[row][j] != '*' || charMap[row + 2][j] != '*')
         throw UnexpectedCharacter(row, j, charMap[row][j]);

   ///secon line must have format "*[A-Z]{p,e,q} *" ....
   if (charMap[row + 1][col] != '*')
      throw UnexpectedCharacter(row + 1, col, charMap[row + 1][col]);
   else if ((charMap[row + 1][col + 1] < 'A') || (charMap[row + 1][col + 1] > 'Z'))
      throw UnexpectedCharacter(row + 1, col + 1, charMap[row + 1][col + 1]);

   else if ((charMap[row + 1][col + 2] < 'a') || (charMap[row + 1][col + 1] > 'z') )
      throw UnexpectedCharacter(row + 1, col + 2, charMap[row + 1][col + 2]);
   else if (charMap[row + 1][col + 3] != ' ')
      throw UnexpectedCharacter(row + 1, col + 3, charMap[row + 1][col + 3]);
   else if (charMap[row + 1][col + 4] != '*')
      throw UnexpectedCharacter(row + 1, col + 4, charMap[row + 1][col + 4]);

   return;
}


///******************************* LoadMapFromFile ****************************************************************
/**
 * AntHill is represented by 15 characters total (3 rows by 5 characters) in special format.
 * First and third (last) line are "*****"
 * Second line have "*[A-Z]{p,e,q} *" format where uppercase character represent name of AntHill and lowercase character ownership...
 * @param row
 * @param col
 * @param charMap
 */
void Map::LoadAntHill(int row, int col, const std::vector<std::vector<char>> &charMap)
{

   ///Other character than '*' must always be already part of existing AntHill
   if (charMap[row][col] != '*')
   {
      if (!PartOfExistingAntHill(row, col))
         throw UnexpectedCharacter(row, col, charMap[row][col]);
   }

   ///If '*' character is allready part of existing AntHill, don't care about it.

   if (PartOfExistingAntHill(row, col))
      return;


   ///Otherwise we have '*' character which is not part of any AntHill yet.

   ///Before creating new one, we check all area, which is supposed to be covered by AntHill
   CheckAntHillFormat(row, col, charMap);

   ///Create new AntHill...
   m_mapMatrix[row][col] = new AntHill(Coords(row, col),           // origin position
                                       charMap[row + 1][col + 2], // owner
                                       charMap[row + 1][col + 1]  // name
   );

   int i  = charMap[row + 1][col + 2];
  // if( i != 'p')
      m_players.insert( i  );

   /// ...and fill map with area covered by it.
   for (int i = row; i < row + 3; ++i)
      for (int j = col; j < col + 5; ++j)
         m_mapMatrix[i][j] = m_mapMatrix[row][col];


   m_numOfAntHills++;
   m_listOfElements.push_back(m_mapMatrix[row][col]);

   m_listOfAntHills.push_back((AntHill *) m_mapMatrix[row][col]);
   return;
}


///********************************** LoadBrick **************************************************************************
void Map::loadWall(int row, int col, const std::vector<std::vector<char>> &)
{
   m_mapMatrix[row][col] = new Wall(Coords(row, col), -1);
   m_listOfElements.push_back(m_mapMatrix[row][col]);
}


///********************************** LoadEmpty **************************************************************************
void Map::LoadEmpty(int row, int col, const std::vector<std::vector<char>> &)
{
   ///In border of the map must not be empty space
   if (row == 0 || col == 0 || row == m_height - 1 || col == m_width - 1)
      throw UnexpectedCharacter(row, col, ' ');

   /// ' ' character is also part of the AntHill. If so, it was already handled when creating new AntHill.
   if (PartOfExistingAntHill(row, col))
      return;

   m_mapMatrix[row][col] = new Empty(Coords(row, col), -1);
   m_listOfElements.push_back(m_mapMatrix[row][col]);
}


///********************************** LoadMap **************************************************************************
void Map::LoadMap(const std::vector<std::vector<char>> &charMap)
{

   ///Read char Matrix and by char value handle appropriate map element.
   for (int i = 0; i < m_height; ++i)
      for (int j = 0; j < m_width; ++j)
      {
         if (charMap[i][j] == '*' ||
                 (charMap[i][j] >= 'A' && charMap[i][j] <= 'Z') ||
                 (charMap[i][j] >= 'a' && charMap[i][j] <= 'z'))
            LoadAntHill(i, j, charMap);

         else if (charMap[i][j] == '#')
            loadWall(i, j, charMap);

         else if (charMap[i][j] == ' ')
            LoadEmpty(i, j, charMap);

         else
            throw UnexpectedCharacter(i, j, charMap[i][j]);

      }
}

///******************************* LoadMapFromFile ****************************************************************

/*! Load map file to memory.
 * LoadMapFromFile  ( LOAD FILE TO CHARACTER MATRIX)
 * First count rows and lines of the map file.
 * Next initialize 2D char matrix of desired size.
 * Next load whole map file to this matrix.
 * Main reason for loading whole file at once and parsing it after are AntHills elements in the map file.
 *      It is better to call AntHill constructor with name and ownership of the AntHill that setting the name after by setter method.
 *      But the name and ownership of the AntHill is on the +1 line from first char that represent AntHill
 *      If we have fthe ile already loaded it's easy to get the name. Otherwise we would have to wait to read 1+ line.
 * Basically it is not problem, because map files are supposed to be small (usually about 1000 Bytes)
 * @param mapName
 */
void Map::LoadMapFromFile(const std::string mapName)
{


   ///Count file width and file size...
   CountRowsCols(mapName);

   ///Resize vector matrix to size calculated by CountRowsCols....
   m_mapMatrix.resize(m_height, std::vector<MapElement *>(m_width, NULL));

   ///Initialize character matrix to store whole file in memory
   std::vector<std::vector<char>> charMatrix(m_height, std::vector<char>(m_width));

   ///Open file
   ///Read it char by char (...yup this is pretty retarded that We're now reading file for the second time... )
   std::ifstream f(mapName);

   if (f.bad() || f.fail())
      throw ErrorWhileReadingFile(mapName);

   char c;
   for (int i = 0; i < m_height; ++i)
   {
      for (int j = 0; j < m_width; ++j)
      {
         f.get(c);
         if (f.bad() || f.eof() || f.fail())
            throw ErrorWhileReadingFile(mapName);
         charMatrix[i][j] = c;
      }

      ///read the newline....
      f.get(c);
   }

   ///Close file
   f.close();

   ///Now transform chars from charMatrix the the mapMatrix
   LoadMap(charMatrix);
}


///*********************************** CoutRowsCols ********************************************************************
/*!Count number and columns of map file by reading it.
 * @throws ErrorWhileReadingFile if file can't be read or file becomes unavailible
 * @param fileMapName
 */
void Map::CountRowsCols(const std::string &mapName)
{
   m_height = 0;
   m_width = 0;
   int firstLineWidth = 0;
   char c;

   ///Open map file
   std::ifstream f(mapName, std::ios::in);
   if (f.bad() || f.fail())
      throw ErrorWhileReadingFile(mapName);

   ///Read map file char by char until EOF
   while (!f.eof())
   {
      f.get(c);

      ///inc line length without '\n'
      if (c != '\n')
      {
         ///count first line length
         if (m_height == 0)
            firstLineWidth++;

         ///rest of the lines...
         ++m_width;
      }

         /// '\n' character inc num of lines...
      else
      {
         if (!f.eof())
         {
            ++m_height;
            if (m_width != firstLineWidth)
               throw UnexpectedCharacter(m_height, m_width, c);
            m_width = 0;
         }
      }
   }

   m_width = firstLineWidth;

   f.clear();
   f.close();

}

/*! Returns ptr to MapElement at specified position.
 *
 * @return
 */
MapElement *Map::GetElement(Coords crds) const
{
   if (crds.m_row >= m_height || crds.m_col >= m_width)
      return NULL;
   else
      return m_mapMatrix[crds.m_row][crds.m_col];
}

void Map::Display(InputOutput *inOut) const
{
   /// firstly dipsplay base map
   for (const auto elem : m_listOfElements)
      elem->Display(inOut);

   /// than display paths
   for (const auto path : m_listOfPaths)
      path->Display(inOut);

   ///than ants on path
   for (const auto path : m_listOfPaths)
      path->DisplayAnts(inOut);

   /// finally display antHills again (this is not necessary, but other way, antHills can be
   /// damaged by path, which starts and ends in them...)
   for (const auto elem : m_listOfAntHills)
         elem->Display(inOut);
}

std::list<AntHill *> Map::GetAntHillsByOwner(int ownerId)
{
   std::list<AntHill *> antHills;

   for (auto x : m_listOfElements)
      if (x->OwnerId() == ownerId)
         antHills.push_back((AntHill *) x);

   return antHills;
}

std::list<std::pair<char, int>> Map::GetAntHillStates() const
{
   std::list<std::pair<char, int>> antHillData;

   for( auto x: m_listOfAntHills)
      antHillData.push_back(std::pair<char,int>(x->OwnerId(),x->GetNumOfAnts()));

   return antHillData;
}

void Map::UpdateAntHills(std::list<std::pair<int, int>> listOfUpdates)
{
   std::vector<AntHill *>::iterator antHillIter = m_listOfAntHills.begin();
   std::list<std::pair<int,int>>::iterator updateIter = listOfUpdates.begin();

   for( ; antHillIter != m_listOfAntHills.end() && updateIter != listOfUpdates.end(); ++antHillIter, ++updateIter)
   {
      (*antHillIter)->SetState(*updateIter);
   }
}

std::vector<Coords> Map::expandCoord(Coords coords, AntHill *from, AntHill *to) const
{
      std::vector<Coords> coordsExpanded;

      /// three top and three bottom coords
      for (int j = coords.m_col - 1; j < coords.m_col + 2; ++j)
      {
         if (EvaluateCoords(Coords(coords.m_row - 1, j), from, to))
            coordsExpanded.push_back(Coords(coords.m_row - 1, j));
         if (EvaluateCoords(Coords(coords.m_row + 1, j), from, to))
            coordsExpanded.push_back(Coords(coords.m_row + 1, j));
      }

      if (EvaluateCoords(Coords(coords.m_row, coords.m_col - 1), from, to))
         coordsExpanded.push_back(Coords(coords.m_row, coords.m_col - 1));
      if (EvaluateCoords(Coords(coords.m_row, coords.m_col + 1), from, to))
         coordsExpanded.push_back(Coords(coords.m_row, coords.m_col + 1));

      return coordsExpanded;
}

bool Map::EvaluateCoords(const Coords &coords, AntHill *a, AntHill *b) const
{
   if (coords.m_row >= m_height - 1 || coords.m_col >= m_width - 1)
      return false;

   return GetElement(coords)->IsEmpty() || GetElement(coords) == a || GetElement(coords) == b;
}

int Map::getNumOfAntHillsByOwner(int ownerId) const
{
   int i = 0;

   for (auto x : m_listOfElements)
      if (x->OwnerId() == ownerId)
         i++;

   return i;
}

void Map::RiseAntNumbers() const
{
   for ( auto x : m_listOfAntHills)
   {
      x->GiveBirth();
   }
}

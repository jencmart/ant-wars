//
// Created by jencmart on 5/28/17.
//

#ifndef ANTWARS_EXCEPTIONS_H
#define ANTWARS_EXCEPTIONS_H
#include <iostream>

///*************************************************************************************************
///******************************* CLASSES OF  EXCEPTION *******************************************
///*************************************************************************************************

/*! Thrown during game when user want to pause game.
 *
 */
class Pause
{};

/*! Thrown when loading files with unexpected characters.
 *  It also collects information of position of this unexpected character in the file.
 */
class UnexpectedCharacter
{
public:
   UnexpectedCharacter(int row, int col, char c) : m_row(row), m_col(col), m_c(c)
   {}
   void print()
   {
      std::cout << "[Unexpected character in map file!]: " << m_row + 1 << "," << m_col + 1 << ": '"
                << m_c << "'"
                << std::endl;
   }

   int m_row;
   int m_col;
   char m_c;
};


/*! Thrown by path when command asks to create path between two anthills which cant be connected.
 */
class PathNotExistException
{
};

/*! If there is problem durign saving the game exception is thrown. (usually wen we lost permission
 * to write to the file or when save dir is missing or inacessible
 */
class ErrorWhileSaving{};

/*! Usually thrown when desired file is missing or inacessible.
 */
class ErrorWhileReadingFile
{
public:
   ErrorWhileReadingFile(const std::string &fileName) : m_fileName(fileName)
   {}

   /*! Prints name of filename which caused error
    */
   inline void print() const
   { std::cout << "Error while reading: " << m_fileName << std::endl; }

private:
   std::string m_fileName;
};

#endif //ANTWARS_EXCEPTIONS_H

//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_COMMON_H
#define ANTWARS_COMMON_H




/*! Game states enumeration
 */
enum eGameState
{
   GAME_INIT, GAME_MENU, GAME_LOAD, GAME_PAUSE,
   GAME_NEW, GAME_QUIT, GAME_SAVE, GAME_CONTINUE
};

/*! Broadly used structure of coordinates in most classes of the game
 */
struct Coords
{
   int m_row;
   int m_col;

   Coords(int row, int col) : m_row(row), m_col(col)
   {}

   /*! ...
    * @param other
    * @return
    */
   inline bool operator==(const Coords &other) const
   { return m_row == other.m_row && m_col == other.m_col; }

   /*! ...
    * @param other
    * @return
    */
   inline bool operator!=(const Coords &other) const
   { return !(*this == other); }

   /*! ...
    * @param other
    * @return
    */
   inline bool operator<(const Coords &other) const
   { return other.m_row < m_row || (other.m_row == m_row && other.m_col < m_col); }
};


#endif //ANTWARS_COMMON_H
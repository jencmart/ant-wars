//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_GAME_H
#define ANTWARS_GAME_H

#include <vector>
#include <string>

#include "inOut.h"
#include "humanPlayer.h"
#include "botPlayer.h"

#define ANT_SPEED 50000

class Game
{
private:
   InputOutput *m_IN_OUT;
   std::list<AbstractPlayer *> m_players; /// NEED TO BE UPDATED ... AFTER UPDATING MAP
   ///vyrobi se, ale pak se musi odmazat podle stavu mapy...
   ///aka delete dead...
   Map m_map;                             /// NEED TO BE SAVED RIGHT STATE /ok
   int m_score;                           /// NEED TO BE SAVED /ok
   int m_roundNum;                        /// NEED TO BE SAVED /ok
   int m_numOfAntHills;                   /// NEED TO BE SAVED /ok
   std::list<Command *> m_commandList;    /// NEED TO BE SAVED - EG ALL COMMANDS NEED TO BE SAVED
   eGameState &m_gameState;                                      /// AND NEED TO BE CONSTRUCTED AGAIN
   AbstractPlayer *m_pausedPayer;        /// NEED TO BE SAVED /ok
   bool m_pausedInSimulation;             /// NEED TO BE SAVED /ok
   int m_antRiser;

public:

   /*!Load game constructor
    * @param inOut
    * @param saveFileName
    * @param pathToSaves
    * @param pathToMaps
    * @param gameState
    */
   Game(InputOutput *inOut,
        std::string saveFileName,
        std::string pathToSaves,
        std::string pathToMaps,
        eGameState &gameState) :
           m_IN_OUT(inOut),
           m_players(0),
           m_map(pathToMaps, LoadMapName(saveFileName, pathToSaves)), /// OK
           m_score(0),
           m_roundNum(0),
           m_numOfAntHills(0),
           m_commandList(0),
           m_gameState(gameState),
           m_pausedPayer(NULL),
           m_pausedInSimulation(false),
           m_antRiser(0)
   {
      LoadGame(saveFileName, pathToSaves);
      /// load players

      /// remove dead players
   }


   /*!
    * Default constructor
    * @param inOut
    * @param mapName
    * @param difficulty
    * @param playerName
    */
   Game(InputOutput *inOut,
        const std::string pathToMaps,
        const std::string mapName,
        eGameState &gameState)
           :
           m_IN_OUT(inOut),
           m_players(0),
           m_map(pathToMaps, mapName),
           m_score(1000),
           m_roundNum(1),
           m_numOfAntHills(m_map.getNumOfAntHills()),
           m_gameState(gameState),
           m_pausedPayer(NULL),
           m_pausedInSimulation(false),
           m_antRiser(0)
   {
      InitPlayers();
   }

   ~Game()
   {
      ///delete players
      for (auto player : m_players)
         delete player;

      ///delete command lists - deleting all commands will also delete all paths
      for (auto command : m_commandList)
         delete command;
   }

   /*!
   * Main game loop
   */
   void Loop();

   /*!
    * Iterate through current comands. Process them iteratively until no commands left.
    * If the command is finished, delele and remove it.
    */
   void ProcessCommandsByOneStep();

   /*! Initialize players, who were found in the map file
    */
   void InitPlayers();

   /*! Arranges of loading oll member variables for loading saved game state
    * @param saveFileName
    * @param pathToSaves
    */
   void LoadGame(std::string saveFileName, std::string pathToSaves);

   /*! Prints info about current player, score and round
    */
   void PrintHud(AbstractPlayer *) const;

   /*! Check if game ended.
    * That happens when some player own all the anthills
    * @return
    */
   bool CheckEnd() const;

   /*!Delete all players who own zero anthills.
    *
    */
   void RemoveDeadPlayers();

   /*! Saves game state to the file...
   * THERE IS KNOWN BUG, THAT WE DONT SAVE ON PAUSE OR SAVE GAME WHICH COMMAND WAS
   * EXECUTED LAST TIME, SO WHEN GAME IS INIT, WE START FROM FIRST COMMAND AGAIN
   * AND THAT IS WHY SOME COMMANDS COULD HAVE BEEN EXECUTED MORE TIMES THAN OTHERS....
   * @param saveDir
   * @param saveFileName
   */
   void Save(const std::string saveDir, const std::string saveFileName) const;

   /*! Load map name from save file
    * @param saveFileName
    * @param pathToSaves
    * @return
    */
   std::string LoadMapName(std::string saveFileName, std::string pathToSaves) const;

   /*! Display general HUD for the game
    */
   void StartDisplay();
};

#endif //ANTWARS_GAME_H

//
// Created by jencmart on 6/3/17.
//

#include "gameWrapper.h"

void GameWrapper::run()
{
   m_gameState = GAME_MENU;

   while (1)
   {
      /// MENU WITH NEW GAME or MENU with PAUSED GAME
      if (m_gameState == GAME_MENU || m_gameState == GAME_PAUSE)
         m_menu.Loop();


      if (m_gameState == GAME_CONTINUE)
      {
         m_game->Loop();
         if (m_gameState != GAME_PAUSE)
         {
            delete m_game;
            m_game = NULL;
         }
      } else if (m_gameState == GAME_NEW)
      {
         if (m_game)
            delete m_game;

         try
         {
            m_game = new Game(m_IN_OUT,
                              MAPS_DIR,
                              m_menu.mapName,
                              m_gameState);

            m_game->Loop();
         }
         catch (...)
         {
            m_gameState = GAME_MENU;
         }

         if (m_gameState != GAME_PAUSE && m_game)
         {
            delete m_game;
            m_game = NULL;
         }
      }


         /// GAME SAVE menu state
      else if (m_gameState == GAME_SAVE)
      {

         m_game->Save(SAVES_DIR, m_menu.savedGameName);
         /// zeptej se menu jak se ma save game jmenovat
         /// posli to m_game aby se ulozila do toho a toho souboru


         m_gameState = GAME_PAUSE;
      }


         /// GAME LOAD menu state
      else if (m_gameState == GAME_LOAD)
      {
         if (m_game)
            delete m_game;
         m_game = NULL;


         try
         {
            m_game = new Game(m_IN_OUT,
                              m_menu.loadGameName,
                              SAVES_DIR,
                              MAPS_DIR,
                              m_gameState);

            m_game->Loop();
         }
         catch (...)
         {
            m_gameState = GAME_MENU;
         }



         if (m_gameState != GAME_PAUSE)
         {
            delete m_game;
            m_game = NULL;
         }
      }

         /// GAME QUIT game state
      else if (m_gameState == GAME_QUIT)
      {
         if (m_game)
            delete m_game;

         delete m_IN_OUT;

         return;
      }

   }
}
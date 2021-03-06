#include "Console.h"
#include <iostream>
#include <string>

using namespace ::std;

const void Console::PrintBoard(GameState &GameState)
{
   board currentBoard = GameState.GoBoard();
   uint8_t sizeOfCurrentBoard = GameState.GoBoardSize();
   for (uint8_t x = 0; x < sizeOfCurrentBoard; x++)
   {
      for (uint8_t y = 0; y < sizeOfCurrentBoard; y++)
      {
         switch (currentBoard[x][y])
         {
         case stone::empty:
            cout << "+ ";
            break;
         case stone::black:
            cout << "O ";
            break;
         case stone::white:
            cout << "0 ";
            break;
         }
      }
      cout << endl;
   }
   Console::OutputDeadStones(GameState);
}

const void Console::OutputDeadStones(GameState &GameState)
{
   cout << "Dead white stones : " << GameState.PrizonerStones(stone::white) << endl;
   cout << "Dead black stones : " << GameState.PrizonerStones(stone::black) << endl;
}

void Console::ObtainValidPlayerMove(GameState &GameState)
{
   while (!GetCoordinatesAndPlay(GameState))
   {
      std::cout << "you cant go there!" << std::endl;
   }
}

bool Console::GetCoordinatesAndPlay(GameState &GameState)
{
   uint8_t size = GameState.GoBoardSize();
   int8_t x = size;
   int8_t y = size;
   while (x >= 0 && x >= size)
   {
      x = GetInput("please input an x coordinate : ");
   }
   while (y >= 0 && y >= size)
   {
      y = GetInput("please input a y coordinate : ");
   }

   return GameState.PlayStone(x, y, GameState.WhosMoveIsNext());
}

uint8_t Console::GetInput(const string &message)
{
   cout << message << endl;
   string stringInput;
   size_t* pos = 0;
   uint8_t input = 0;
   uint8_t base = 10;
   bool succesfull = false;
   while (!succesfull)
   {
      cin >> stringInput;
      try
      {
         input = stoi(stringInput, pos, base);
         succesfull = true;
      }
      catch (invalid_argument)
      {
         cout << "Invalid!" << endl;
         cout << message << endl;
         succesfull = false;
      }
      catch (out_of_range)
      {
         cout << "Out of range!" << endl;
         cout << message << endl;
         succesfull = false;
      }
   }
   return input;
}
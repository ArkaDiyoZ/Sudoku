/* Play Sudoku */
#include "Sudoku.h"


int main(int argc, char* argv[])
{
 
	// Create Sudoku game object
    Sudoku::Sudoku S;

	// Play Sudoku game

	/*	
    setlocale(LC_ALL, "Rus");
    int action = 0;

	do
    {
        game g;
        action = g.mainMenu();
        switch(action)
        {
            case 0: main_game(); action = 0; break;
            case 1: g.rules(); action = 0; break;
            case 2: SDL_Quit; action = 1; break;
        }
	} while (action == 0);

	return 0;
	*/
   	S.play();
	return 0;
}


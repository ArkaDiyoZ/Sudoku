#pragma once
#include <SDL.h> 
#include <iostream>
#include <time.h>  

#include "Button.h"
#include "SudokuCell.h"
#include "SudokuGenerator.h"


namespace Sudoku
{
	class Sudoku
	{
	private:
		// Define window dimensions
		const int mWindowHeight;
		const int mWindowWidth;

		// Define Sudoku grid dimensions
		const int mGridHeight;
		const int mGridWidth;

		// Define Sudoku max grid rows and columns (normally set to 9 x 9)
		const int mGridRows;
		const int mGridCols;

		// Define window and renderer
		SDL_Window* mWindow;
		SDL_Window* Window_3;
		SDL_Renderer* mRenderer_2;
		SDL_Renderer* mRenderer;
		SDL_Renderer* mRenderer_1;
		// Texture cache to hold preloaded textures
		int mTotalTextures;
		SDL_Texture* mTextureCache[15];
		SDL_Texture* mTextCache[10];
		SDL_Texture* mTextCache_2[10];
		SDL_Texture* mTextAbout[15];
		SDL_Texture* mTextEx[10];
		

		// Define true type font paramaters
		TTF_Font* mFont;
		int mFontSize;

		// Define total buttons
		const int mTotalCells;

		// Define grid of cells (normally set to 9 x 9 = 81)
		Cell mGrid[81];

		// Define check and new buttons
		Button mCheckButton;
		Button mNewButton;
		Button mSolveButton;
		Button mPlayButton;
		Button mAboutButton;
		Button mExitButton;
		Button mNameButton;
		Button mExButton;
		Button mResButton;

		Button Leveleasy;
		Button Levelmed;
		Button Levelhard;
		Button ChooseLevel;
		Button Exit_Btn_Win2;
		// Timer (Optional)
		Button mTimer;

		// Define colours 
		SDL_Color mClearColour;

	private:
		
		// Intialise SDL window, renderer and true type font
		bool initialiseSDL();

		// Get index of 1D array from row and col
		inline int getIndex(int row, int col) const;

		// Load textures using SDL true type fonts
		void loadTexture(SDL_Texture*& texture, const char* text, SDL_Color& fontColour);

		// Preload textures using SDL true type fonts
		void preloadTextures();

		// Create interface layout by setting button parameters
		void createInterfaceLayout();
		
		// Generate a Sudoku puzzle with a unique solution
		void generateSudoku();

		//Solve sudoku
		void solovesudoke();

		// Free textures
		void freeTextures();

	public:
		// Constructor to intialise member variables
		Sudoku();
		// Destructor to free textures
		~Sudoku();
		// Play Sudoku
		int play();

		int menu();

		int menu_result(int );
		// Close Sudoku
		void close();
	};
	class Wind: private Sudoku 
	{
	public: 
		Wind();
		~Wind();
	private:
		int WinHei = 720;
		int WinWidth = 880;
		SDL_Renderer* Ren;
		SDL_Window* Win;

	};

};
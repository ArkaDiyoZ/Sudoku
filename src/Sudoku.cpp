#include "Sudoku.h"

//----------------------------------Constructor and Destructor---------------------------------//
Sudoku::Sudoku::Sudoku()
	: mWindowHeight(880), mWindowWidth(720),
	mGridHeight(720), mGridWidth(720),
	mGridRows(9), mGridCols(9),
	mWindow(nullptr), mRenderer(nullptr),
	mTotalTextures(15), mTextureCache{ nullptr },
	mFont(nullptr), mFontSize(mGridHeight / 9),
	mTotalCells(81), mTextCache{ nullptr }, mTextEx{ nullptr },
	  mClearColour({ 0, 0, 0, SDL_ALPHA_OPAQUE })
{

}

Sudoku::Sudoku::~Sudoku()
{
	freeTextures();
	close();
}

int Sudoku::Sudoku::menu()
{
	bool measureTimeForCheckButton = false;
	time_t startTimeForCheckButton;
	bool completed = false;

	SDL_SetRenderDrawColor(mRenderer, 219, 184, 215, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(mRenderer);
	// Choose colour of font
	SDL_Color fontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // black

	// Load texture for empty space
	loadTexture(mTextCache[0], " ", fontColour);

	// Load textures for numbers from 1 to 9
	for (int num = 5; num < 10; num++)
	{
		const char temp[] = { '0' + num, '\0' };
		loadTexture(mTextCache[num], temp, fontColour);
	}

	// Load texture for "Check", "Solve", and "New" buttons
	loadTexture(mTextCache[1], "SUDOKU", fontColour);
	loadTexture(mTextCache[2], "Play", fontColour);
	loadTexture(mTextCache[3], "About", fontColour);
	loadTexture(mTextCache[4], "Exit", fontColour);

	const int numberOfOtherButtons_1 = 4;
	mPlayButton.setTexture(mTextCache[2]);
	mAboutButton.setTexture(mTextCache[3]);
	mExitButton.setTexture(mTextCache[4]);
	mNameButton.setTexture(mTextCache[1]);

	Button* otherButtons_1[numberOfOtherButtons_1] = {&mNameButton, &mPlayButton, &mAboutButton, &mExitButton  };

	int buttonStartCol = 200;
	int buttonStartRow = 200;
	int buttonHeight = 200;
	int buttonWidth = 300;
	// Set check, solve, and new buttons (last row)
	for (int button = 0; button < numberOfOtherButtons_1; button++) // colBlock is every 3 columns of cells
	{
		if (button == 0 ) {
			buttonStartCol = 200;
			buttonStartRow = 0;
			buttonHeight = 200;
			buttonWidth = 300;

		}else {
			buttonStartRow += 50;
			buttonStartRow += 150;

		}
		// Set button position and dimensions
		SDL_Rect buttonRect = { buttonStartCol, buttonStartRow, buttonWidth, buttonHeight };
		otherButtons_1[button]->setButtonRect(buttonRect);

	}
	
	// Render check button
	mPlayButton.renderButton(mRenderer);
	mPlayButton.centerTextureRect();
	mPlayButton.renderTexture(mRenderer);

	// Render new button
	mAboutButton.renderButton(mRenderer);
	mAboutButton.centerTextureRect();
	mAboutButton.renderTexture(mRenderer);

	// Render solve button
	mExitButton.renderButton(mRenderer);
	mExitButton.centerTextureRect();
	mExitButton.renderTexture(mRenderer);

	// Render solve button
	mNameButton.renderButton(mRenderer);
	mNameButton.centerTextureRect();
	mNameButton.renderTexture(mRenderer);


	SDL_Event event;
	bool stop = false;
	bool ex = false;
	bool pl = false;
	bool flag = false;

	SDL_RenderPresent(mRenderer);

	while (!stop)
	{
		// Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			
			if (mExitButton.getMouseEvent(&event) == ButtonState::BUTTON_MOUSE_DOWN)
			{
				// Set check solution flag
				ex = true;
				stop = true;
				return 1;
			}
			if (mPlayButton.getMouseEvent(&event) == ButtonState::BUTTON_MOUSE_DOWN){	
				/*  
				bool stop_1 = false;
				SDL_Event ev_1;
				SDL_Color fontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // black
				SDL_SetRenderDrawColor(mRenderer, 219, 184, 215, SDL_ALPHA_OPAQUE);
				// Load texture for empty space
				loadTexture(mTextCache_2[0], " ", fontColour);

				// Load textures for numbers from 1 to 9
				for (int num = 5; num < 10; num++)
				{
					const char temp[] = { '0' + num, '\0' };
					loadTexture(mTextCache_2[num], temp, fontColour);
				}

				// Load texture for "Check", "Solve", and "New" buttons
				loadTexture(mTextCache_2[1], "CHOOSE LEVEL", fontColour);
				loadTexture(mTextCache_2[2], "Play", fontColour);
				loadTexture(mTextCache_2[3], "About", fontColour);
				loadTexture(mTextCache_2[4], "Exit", fontColour);

				SDL_RenderClear(mRenderer);
				const int numberOfOtherButtons_2 = 4;
				Leveleasy.setTexture(mTextCache[2]);
				Levelmed.setTexture(mTextCache[3]);
				Levelhard.setTexture(mTextCache[4]);
				ChooseLevel.setTexture(mTextCache[1]);

				Button* otherButtons_2[numberOfOtherButtons_2] = { &ChooseLevel ,&Leveleasy, &Levelmed,  &Levelhard };

				int buttonStartCol = 200;
				int buttonStartRow = 200;
				int buttonHeight = 200;
				int buttonWidth = 300;
				// Set check, solve, and new buttons (last row)
				for (int button = 0; button < numberOfOtherButtons_2; button++) // colBlock is every 3 columns of cells
				{
					if (button == 0) {
						buttonStartCol = 200;
						buttonStartRow = 0;
						buttonHeight = 200;
						buttonWidth = 300;

					}
					else {
						buttonStartRow += 50;
						buttonStartRow += 150;

					}
					// Set button position and dimensions
					SDL_Rect buttonRect = { buttonStartCol, buttonStartRow, buttonWidth, buttonHeight };
					otherButtons_2[button]->setButtonRect(buttonRect);

				}

				// Render solve button
				ChooseLevel.renderButton(mRenderer);
				ChooseLevel.centerTextureRect();
				ChooseLevel.renderTexture(mRenderer);

				// Render check button
				Leveleasy.renderButton(mRenderer);
				Leveleasy.centerTextureRect();
				Leveleasy.renderTexture(mRenderer);

				// Render new button
				Levelmed.renderButton(mRenderer);
				Levelmed.centerTextureRect();
				Levelmed.renderTexture(mRenderer);

				// Render solve button
				Levelhard.renderButton(mRenderer);
				Levelhard.centerTextureRect();
				Levelhard.renderTexture(mRenderer);

				while (!stop_1) 
				{
					while (SDL_PollEvent(&ev_1) != 0) 
					{
				    
					
					}
				
				}

				*/
				
				// Set check solution flag
				pl = true;
				stop = true;
				return 0;
			} 	
			if (mAboutButton.getMouseEvent(&event) == ButtonState::BUTTON_MOUSE_DOWN)
			{

				SDL_Delay(800);
				//SDL_RenderClear(mRenderer);
				//The surface contained by the window
				SDL_Surface* mScreenSurface = NULL;
				//The image we will load and show on the screen
				SDL_Surface* mAbout = SDL_LoadBMP ("assets/su_do_ku_1_1.bmp");
				// создание второго окна (правила игры)
				SDL_Window* window2 = SDL_CreateWindow("About", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
				if (window2 == nullptr)
				{
					std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
					return -1;
				}
				else
				{
					//Get window surface
					mScreenSurface = SDL_GetWindowSurface(window2);										
				}
				mRenderer_1 = SDL_CreateRenderer(window2, -1, 0);
				if (mRenderer_1 == nullptr)
				{
					std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
				}
				SDL_RenderPresent(mRenderer_1);
				//Apply the image
				SDL_BlitSurface(mAbout, NULL, mScreenSurface, NULL);
				//Update the surface
				SDL_UpdateWindowSurface(window2);


			/*  
				bool stop_1 = false;
				SDL_Event ev_1;
				SDL_Color fontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // black
				SDL_SetRenderDrawColor(mRenderer, 219, 184, 215, SDL_ALPHA_OPAQUE);
				// Load texture for empty space
				loadTexture(mTextAbout[0], " ", fontColour);

				// Load textures for numbers from 1 to 9
				for (int num = 5; num < 10; num++)
				{
					const char temp[] = { '0' + num, '\0' };
					loadTexture(mTextAbout[num], temp, fontColour);
				}

				// Load texture for "Check", "Solve", and "New" buttons
				loadTexture(mTextCache_2[1], "Группа И596", fontColour);
				loadTexture(mTextCache_2[2], "Вирин Аркадий", fontColour);
				loadTexture(mTextCache_2[3], "About", fontColour);
				loadTexture(mTextCache_2[4], "Exit", fontColour);

				SDL_RenderClear(mRenderer);
				const int numberOfOtherButtons_2 = 4;
				Leveleasy.setTexture(mTextCache[2]);
				Levelmed.setTexture(mTextCache[3]);
				Levelhard.setTexture(mTextCache[4]);
				ChooseLevel.setTexture(mTextCache[1]);

				Button* otherButtons_2[numberOfOtherButtons_2] = { &ChooseLevel ,&Leveleasy, &Levelmed,  &Levelhard };

				int buttonStartCol = 200;
				int buttonStartRow = 200;
				int buttonHeight = 200;
				int buttonWidth = 300;
				// Set check, solve, and new buttons (last row)
				for (int button = 0; button < numberOfOtherButtons_2; button++) // colBlock is every 3 columns of cells
				{
					if (button == 0) {
						buttonStartCol = 200;
						buttonStartRow = 0;
						buttonHeight = 200;
						buttonWidth = 300;

					}
					else {
						buttonStartRow += 50;
						buttonStartRow += 150;

					}
					// Set button position and dimensions
					SDL_Rect buttonRect = { buttonStartCol, buttonStartRow, buttonWidth, buttonHeight };
					otherButtons_2[button]->setButtonRect(buttonRect);

				}

				// Render solve button
				ChooseLevel.renderButton(mRenderer);
				ChooseLevel.centerTextureRect();
				ChooseLevel.renderTexture(mRenderer);

				// Render check button
				Leveleasy.renderButton(mRenderer);
				Leveleasy.centerTextureRect();
				Leveleasy.renderTexture(mRenderer);

				// Render new button
				Levelmed.renderButton(mRenderer);
				Levelmed.centerTextureRect();
				Levelmed.renderTexture(mRenderer);

				// Render solve button
				Levelhard.renderButton(mRenderer);
				Levelhard.centerTextureRect();
				Levelhard.renderTexture(mRenderer);

				while (!stop_1)
				{
					while (SDL_PollEvent(&ev_1) != 0)
					{


					}

				}
				*/

					
				
				//SDL_RenderPresent(mRenderer);
			}  

		}

	}
	



	//SDL_Delay(5000);

}

int Sudoku::Sudoku::menu_result(int flag_1)
{
	SDL_Delay(200);
	Window_3 = SDL_CreateWindow("Win", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
	if (Window_3 == nullptr)
	{
		std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
		return 0;
	}

	mRenderer_2 = SDL_CreateRenderer(Window_3, -1, 0);
	if (mRenderer_2 == nullptr)
	{
		std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
	}



	
	SDL_SetRenderDrawColor(mRenderer_2, 219, 184, 215, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(mRenderer_2);
	// Load texture for empty space
	SDL_Color fontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // black
	loadTexture(mTextEx[0], " ", fontColour);

	// Load textures for numbers from 1 to 9
	for (int num = 5; num < 10; num++)
	{
		const char temp[] = { '0' + num, '\0' };
		loadTexture(mTextEx[num], temp, fontColour);
	}
	// Load texture for "Check", "Solve", and "New" buttons
	
	loadTexture(mTextEx[2], "Exit", fontColour);

	const int numberOfOtherButtons_3 = 1;
	
	mExButton.setTexture(mTextEx[1]);
	Button* otherButtons_3[numberOfOtherButtons_3] = { &mExButton};
	int buttonStartCol = 200;
	int buttonStartRow = 400;
	int buttonHeight = 300;
	int buttonWidth = 300;
	// Set check, solve, and new buttons (last row)
	for (int button = 0; button < numberOfOtherButtons_3; button++) // colBlock is every 3 columns of cells
	{
	
		// Set button position and dimensions
		SDL_Rect buttonRect_3 = { 200, 500, buttonWidth, buttonHeight };
		otherButtons_3[button]->setButtonRect(buttonRect_3);
	}
	
	SDL_Event event_22;
	bool stop_11 = false;
	bool flag = false;

	//SDL_Delay(500);
	//SDL_RenderClear(mRenderer_2);
	//SDL_RenderClear(mRenderer_2);
	// Render check button
	SDL_Surface* mScreenSurface = NULL;
	//The image we will load and show on the screen
	SDL_Surface* mAbout = NULL;
	if (flag_1 == 3) {
		mAbout = SDL_LoadBMP("assets/Brill_1.bmp");
	}
	else if (flag_1 == 10) {
		mAbout = SDL_LoadBMP("assets/Silver_1.bmp");
	}
	else if (flag_1 == 11) {
		mAbout = SDL_LoadBMP("assets/Bronze_1.bmp");
	}
	
	// создание второго окна (правила игры)
	
		//Get window surface
	mScreenSurface = SDL_GetWindowSurface(Window_3);

	mRenderer_1 = SDL_CreateRenderer(Window_3, -1, 0);
	if (mRenderer_1 == nullptr)
	{
		std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
	}
	SDL_RenderPresent(mRenderer_1);
	//Apply the image
	SDL_BlitSurface(mAbout, NULL, mScreenSurface, NULL);
	//Update the surface
	SDL_UpdateWindowSurface(Window_3);


	while (!stop_11)
	{

		while (SDL_PollEvent(&event_22) != 0)
		{
			if (event_22.type == SDL_QUIT)
			{
				// Set stop flag
				stop_11 = true;
				SDL_DestroyWindow(Window_3);
				SDL_QUIT;
				//return 0;
			}

			if (mExButton.getMouseEvent(&event_22) == ButtonState::BUTTON_MOUSE_DOWN)
			{
				// Set check solution flag
				stop_11 = true;
				SDL_DestroyWindow(Window_3);
				SDL_QUIT;
			}
			

		}
	}

	SDL_RenderPresent(mRenderer_2);
	mExButton.renderButton(mRenderer_2);
	mExButton.centerTextureRect();
	mExButton.renderTexture(mRenderer_2);
	SDL_RenderPresent(mRenderer_2);

	
}

//--------------------------------------Private methods----------------------------------------//
bool Sudoku::Sudoku::initialiseSDL()
{
	// Set success initialisation flag
	bool success = true;

	// Initalise SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL could not intialise! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Initialise SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialise! Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	// Create window
	mWindow = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
	if (mWindow == nullptr)
	{
		std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Create renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
	if (mRenderer == nullptr)
	{
		std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Load font for text
	mFont = TTF_OpenFont("assets/open sans.ttf", mFontSize);
	if (mFont == nullptr)
	{
		std::cout << "Failed to load lazy font! Error: " << TTF_GetError() << std::endl;
		success = false;
	}


	return success;
}

inline int Sudoku::Sudoku::getIndex(int row, int col) const
{
	return row * mGridRows + col;
}

void Sudoku::Sudoku::loadTexture(SDL_Texture*& texture, const char* text, SDL_Color& fontColour)
{
	// Create text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text, fontColour);
	if (textSurface == nullptr)
	{
		std::cout << "Could not create TTF SDL_Surface! Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		// Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (texture == nullptr)
		{
			std::cout << "Could not create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
		SDL_FreeSurface(textSurface);
	}
}

void Sudoku::Sudoku::preloadTextures()
{
	// Choose colour of font
	SDL_Color fontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // black

	// Load texture for empty space
	loadTexture(mTextureCache[0], " ", fontColour);

	// Load textures for numbers from 1 to 9
	for (int num = 1; num < 10; num++)
	{
		const char temp[] = { '0' + num, '\0' };
		loadTexture(mTextureCache[num], temp, fontColour);
	}

	// Load texture for "Check", "Solve", and "New" buttons
	loadTexture(mTextureCache[10], "Check", fontColour);
	loadTexture(mTextureCache[11], "New", fontColour);
	loadTexture(mTextureCache[12], "Wrong!", fontColour);
	loadTexture(mTextureCache[13], "Right!", fontColour);
	loadTexture(mTextureCache[14], "Solve", fontColour);
}

void Sudoku::Sudoku::createInterfaceLayout()
{
	// Define thick and thin borders
	const int thinBorder = 2;
	const int thickBorder = thinBorder + 6;

	/*----------------------------------------Display Stopwatch------------------------------------------*/
	// Treat stopwatch as a button that can't be clicked
	int buttonStartRow = 0;
	int buttonWidth = mGridWidth - 2 * thickBorder;
	// mWindowHeight = buttonHeight + 6 * thinBorder + 6 * thickBorder (rearange this equation)
	int buttonHeight = (mWindowHeight - 6 * thinBorder - 6 * thickBorder) / 11;

	buttonStartRow += thickBorder;
	int buttonStartCol = 0;
	buttonStartCol += thickBorder;
	// Set button position and dimensions
	SDL_Rect buttonRect = { buttonStartCol, buttonStartRow, buttonWidth, buttonHeight };
	mTimer.setButtonRect(buttonRect);
	/*----------------------------------Create buttons for each cell-------------------------------------*/
	// Define cell button dimensions
	// mGridWidth = 6 * thinBorder + 4 * thickBorder + 9 * buttonWidth (rearrange this equation)
	buttonWidth = (mGridWidth - 6 * thinBorder - 4 * thickBorder) / mGridCols;

	// Carry on from previous starting row
	buttonStartRow += buttonHeight;

	// Set cell button position and dimensions
	for (int gridRow = 0; gridRow < mGridRows; gridRow++)
	{
		// Add to starting row
		if (gridRow == 0) buttonStartRow += thickBorder;
		else if (gridRow % 3 == 0) buttonStartRow += buttonHeight + thickBorder;
		else buttonStartRow += buttonHeight + thinBorder;

		// Reset starting column
		int buttonStartCol = 0;

		for (int gridCol = 0; gridCol < mGridCols; gridCol++)
		{
			// Add to starting column
			if (gridCol == 0) buttonStartCol += thickBorder;
			else if (gridCol % 3 == 0) buttonStartCol += buttonWidth + thickBorder;
			else buttonStartCol += buttonWidth + thinBorder;

			// Set button position and dimensions
			SDL_Rect buttonRect = { buttonStartCol, buttonStartRow, buttonWidth, buttonHeight };
			int index = getIndex(gridRow, gridCol);
			mGrid[index].setButtonRect(buttonRect);
		}
	}

	/*----------------------------------Create check, and new buttons-------------------------------------*/
	const int numberOfOtherButtons = 3;
	mCheckButton.setTexture(mTextureCache[10]);
	mNewButton.setTexture(mTextureCache[11]);
	mSolveButton.setTexture(mTextureCache[14]);


	Button* otherButtons[numberOfOtherButtons] = {&mCheckButton, &mNewButton, &mSolveButton};

	// Redefine button width
	// mGridWidth = 3 * thickBorder + 9 * numberOfOtherButtons (rearrange this equation)
	buttonWidth = 229;

	// Carry on from previous starting row
	buttonStartRow += buttonHeight + thickBorder;

	// Reset starting column
	int borderWidthTotal = 0;

	// Set check, solve, and new buttons (last row)
	for (int button = 0; button < numberOfOtherButtons; button++) // colBlock is every 3 columns of cells
	{
		// Add border width to total
		if (button == 0) borderWidthTotal += thickBorder;
		else borderWidthTotal += thickBorder;
		int buttonStartCol = button * buttonWidth + borderWidthTotal;

		// Set button position and dimensions
		SDL_Rect buttonRect = { buttonStartCol, buttonStartRow, buttonWidth, buttonHeight };
		otherButtons[button]->setButtonRect(buttonRect);
	}

}

void Sudoku::Sudoku::generateSudoku()
{
	// Create empty an empty grid to store generated Sudoku
	int generatedGrid[81] = { };

	// Create empty an empty grid to store solution to generated Sudoku
	int solution[81] = { };

	// Instantiate a Sudoku generator object and generate Sudoku with the empty grids
	Generator G;
	G.generate(generatedGrid, solution);

	for (int i = 0; i < 81; i++)
	{
		// Set number and solution
		mGrid[i].setNumber(generatedGrid[i]);
		mGrid[i].setSolution(solution[i]); 

		// Set editability
		if (generatedGrid[i] == 0)
		{
			// This is a cell that can be editable
			mGrid[i].setEditable(true);
		}
		else
		{
			// This cell is fixed and cannot be edited
			mGrid[i].setEditable(false);
		}

		// Set texture (0 = ' ', 1 to 9 = '1' '2'... '9')
		mGrid[i].setTexture(mTextureCache[generatedGrid[i]]);

		// Center texture onto button
		mGrid[i].centerTextureRect();

	}
}

void Sudoku::Sudoku::solovesudoke()
{
	// Create empty an empty grid to store generated Sudoku
	int generatedGrid[81] = { };

	// Create empty an empty grid to store solution to generated Sudoku
	int solution[81] = { };

	// Instantiate a Sudoku generator object and generate Sudoku with the empty grids
	Generator G;
	G.generate(generatedGrid,solution);
	
	for (int i = 0; i < 81; i++)
	{
		// Set number and solution
		//mGrid[i].setNumber(solution[i]);
		mGrid[i].setSolution(solution[i]);

		// Set editability
		if (generatedGrid[i] == 0)
		{
			// This is a cell that can be editable
			mGrid[i].setEditable(true);
		}
		else
		{
			// This cell is fixed and cannot be edited
			mGrid[i].setEditable(false);
		}

		// Set texture (0 = ' ', 1 to 9 = '1' '2'... '9')
		mGrid[i].setTexture(mTextureCache[solution[i]]);

		// Center texture onto button
		mGrid[i].centerTextureRect();

	}
}

void Sudoku::Sudoku::freeTextures()
{
	for (int i = 0; i < mTotalTextures; i++)
	{
		// Free texture if it exists
		if (mTextureCache[i] != nullptr)
		{
			SDL_DestroyTexture(mTextureCache[i]);
			mTextureCache[i] = nullptr;
		}
	}
}

//--------------------------------------Public methods----------------------------------------//
int Sudoku::Sudoku::play()
{	tm formattedTime; 
	int flag;
	bool che_ck = false;
	// Initialise SDL
	if (!initialiseSDL())
	{
		close();
	}
	
	// Preload textures for Sudoku grid and buttons
	preloadTextures();

	if (menu() == 1) {
		//close();
		return 0;
	};

	// Create interface layout
	createInterfaceLayout();

	// Generate Sudoku, set textures, and editability of each cell
	generateSudoku();



	// Set first current cell selected
	Cell* currentCellSelected = &mGrid[0];
	for (int cell = 0; cell < mTotalCells; cell++)
	{
		if (mGrid[cell].isEditable())
		{
			currentCellSelected = &mGrid[cell];
			currentCellSelected->setSelected(true);
			break;
		}
	}

	// Enable text input
	SDL_StartTextInput();

	// Loop variables
	SDL_Event event;
	bool stop = false;
	bool completed = false;
	bool generateNewSudoku = false;
	bool checkSolution = false;
	bool solve = false;

	// Timing for check button
	bool measureTimeForCheckButton = false;
	time_t startTimeForCheckButton;

	// Timer
	time_t startTimer;
	time(&startTimer);

	// Game loop
	while (!stop)
	{
		// Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			// Handle quiting and completion
			if (event.type == SDL_QUIT)
			{
				// Set stop flag
				stop = true;
			}
			// Handle mouse event for "Check" button
			if (mCheckButton.getMouseEvent(&event) == ButtonState::BUTTON_MOUSE_DOWN)
			{
				// Set check solution flag
				checkSolution = true;
			}
			// Handle mouse event for "New" button
			if (mNewButton.getMouseEvent(&event) == ButtonState::BUTTON_MOUSE_DOWN)
			{
				// Set generate new Sudoku flag
				generateNewSudoku = true;
			}
			if (mSolveButton.getMouseEvent(&event) == ButtonState::BUTTON_MOUSE_DOWN)
			{
				
				solve = true;
			}
			// Handle mouse event for cells
			for (int cell = 0; cell < mTotalCells; cell++)
			{
				// If editable
				if (mGrid[cell].isEditable())
				{
					// Set button state and return if mouse pressed on cell
					if (mGrid[cell].getMouseEvent(&event) == ButtonState::BUTTON_MOUSE_DOWN)
					{
						// Set current cell selected to false
						currentCellSelected->setSelected(false);
						
						// Set new cell selected to true
						currentCellSelected = &mGrid[cell];
						currentCellSelected->setSelected(true);
					}
				}
			}
			// Handle keyboard events for current cell selected
			currentCellSelected->handleKeyboardEvent(&event, mTextureCache);
		}
		// If "New" button was clicked
		if (generateNewSudoku)
		{
			// Generate new sudoku
			generateSudoku();

			// Set current cell selected to false
			currentCellSelected->setSelected(false);

			// Find new starting cell
			for (int cell = 0; cell < mTotalCells; cell++)
			{
				if (mGrid[cell].isEditable())
				{
					currentCellSelected = &mGrid[cell];
					currentCellSelected->setSelected(true);
					break;
				}
			}

			// Reset flags
			generateNewSudoku = false;
			completed = false;

			// Reset timer
			time(&startTimer);
		}
		if (solve) 
		{
			solovesudoke();	
			//Reset flags

			//generateNewSudoku = false;
			//completed = false;

			// Reset timer
			time(&startTimer);
		}
		// If "Check" button was clicked
		if (checkSolution)
		{
			// Check if complete
			for (int cell = 0; cell < mTotalCells; cell++)
			{
				if (!mGrid[cell].isCorrect())
				{
					completed = false;
					break;
				}
				completed = true;
			}

			// Set measure time flag and starting time
			measureTimeForCheckButton = true;
			time(&startTimeForCheckButton);

			// Reset flag
			checkSolution = false;
			/* 
			SDL_Delay(800);
			
			SDL_Window* window3 = SDL_CreateWindow("Win", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
			if (window3 == nullptr)
			{
				std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
				return -1;
			}

			mRenderer_2 = SDL_CreateRenderer(window3, -1, 0);
			if (mRenderer_2 == nullptr)
			{
				std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
			}
			SDL_SetRenderDrawColor(mRenderer_2, 219, 184, 215, SDL_ALPHA_OPAQUE);
			SDL_RenderPresent(mRenderer_2);
			*/
			
		}
		// If currently measuring time
		if (measureTimeForCheckButton)
		{
			int seconds = 2;
			if (difftime(time(NULL), startTimeForCheckButton) < seconds && completed)
			{
				// Set colour to green
				SDL_Color colour = { 91, 191, 116, SDL_ALPHA_OPAQUE };

				// Set render colour to green
				SDL_SetRenderDrawColor(mRenderer, colour.r, colour.g, colour.b, SDL_ALPHA_OPAQUE);

				// Set texture to "Right!"
				mCheckButton.setTexture(mTextureCache[13]);

				// Set mouse down colour to green
				mCheckButton.setMouseDownColour(colour);

				//SDL_RenderFillRect(mRenderer, NULL);
				//SDL_Delay(800);

				che_ck = true;
				if (che_ck == 1) {

					SDL_Delay(300);
					if (formattedTime.tm_min < 3) {
						menu_result(3);
						che_ck = 0;
						close();
						return 0;
					}
					else if (formattedTime.tm_min < 10) {
						menu_result(10);
						che_ck = 0;
						close();
						return 0;
					}
					else if (formattedTime.tm_min > 11) {
						menu_result(11);
						che_ck = 0;
						close();
						return 0;
					}

					//mRenderer = NULL;
				}
				
			}
			else if (difftime(time(NULL), startTimeForCheckButton) < seconds && !completed)
			{
				// Set colour to red
				SDL_Color colour = { 200, 73, 46, SDL_ALPHA_OPAQUE };

				// Set render colour to red
				SDL_SetRenderDrawColor(mRenderer, colour.r, colour.g, colour.b, SDL_ALPHA_OPAQUE);

				// Set texture to "Wrong!"
				mCheckButton.setTexture(mTextureCache[12]);

				// Set mouse down colour to red
				mCheckButton.setMouseDownColour(colour);
			}
			else
			{
				// Reset measure time flag
				measureTimeForCheckButton = false;
			}
		}
		else
		{
			// Set texture to "Check"
			mCheckButton.setTexture(mTextureCache[10]);

			// Set render colour to black
			SDL_SetRenderDrawColor(mRenderer, mClearColour.r, mClearColour.g, mClearColour.b, mClearColour.a);
		}

		// Clear screen with rendered colour
		SDL_RenderClear(mRenderer);
		SDL_RenderClear(mRenderer_2);
		
		

		


		// Render buttons and texture of each cell to backbuffer
		for (int cell = 0; cell < mTotalCells; cell++)
		{
			// Render button
			mGrid[cell].renderButton(mRenderer);

			// Re-center since diffrerent numbers have different sized textures
			mGrid[cell].centerTextureRect();

			// Render texture
			mGrid[cell].renderTexture(mRenderer);
		}

		// Render check button
		mCheckButton.renderButton(mRenderer);
		mCheckButton.centerTextureRect();
		mCheckButton.renderTexture(mRenderer);

		// Render new button
		mNewButton.renderButton(mRenderer);
		mNewButton.centerTextureRect();
		mNewButton.renderTexture(mRenderer);
		
		// Render solve button
		mSolveButton.renderButton(mRenderer);
		mSolveButton.centerTextureRect();
		mSolveButton.renderTexture(mRenderer);

		SDL_RenderPresent(mRenderer_2);
		mExButton.renderButton(mRenderer_2);
		mExButton.centerTextureRect();
		mExButton.renderTexture(mRenderer_2);
		SDL_RenderPresent(mRenderer_2);

		mResButton.renderButton(mRenderer_2);
		mResButton.centerTextureRect();
		mResButton.renderTexture(mRenderer_2);
		SDL_RenderPresent(mRenderer_2);

		// Calculate timer
		time_t difference = time(NULL) - startTimer;
		
		localtime_s(&formattedTime, &difference);
		char timer[80];
		strftime(timer, sizeof(timer), "%H:%M:%S", &formattedTime);
		
		// Load and render timer (TO DO: use preloaded textures to render timer)
		SDL_Texture* timerTexture = nullptr;
		SDL_Color fontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // black
		loadTexture(timerTexture, timer, fontColour);
		mTimer.setTexture(timerTexture);
		mTimer.renderButton(mRenderer);
		mTimer.centerTextureRect();
		mTimer.renderTexture(mRenderer);
		SDL_DestroyTexture(timerTexture);
		timerTexture = nullptr;

		// Update screen from backbuffer and clear backbuffer
		SDL_RenderPresent(mRenderer);
		SDL_RenderPresent(mRenderer_2);
		// Slow down program becuase it doesn't need to run very fast
		SDL_Delay(10);
	}
	/* 
	if (che_ck == true) {
		SDL_RenderFillRect(mRenderer, NULL);
		SDL_Delay(800);
		//SDL_RenderClear(mRenderer);
		//SDL_SetRenderDrawColor(mRenderer, 219, 184, 215, SDL_ALPHA_OPAQUE);
		//SDL_RenderPresent(mRenderer);
		

	}*/
	
	// Disable text input
	SDL_StopTextInput();

	// Free button textures
	freeTextures();

	// Destroy and quit
	close();

}

 void Sudoku::Sudoku::close()
{
	// Destroy
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mRenderer = nullptr;
	mWindow = nullptr;

	// Free font
	TTF_CloseFont(mFont);
	mFont = nullptr;

	// Quit
	SDL_Quit();
	TTF_Quit();
}


	/*  
	// Create window
	mWindow_2 = SDL_CreateWindow("About", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
	if (mWindow_2 == nullptr)
	{
		std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
	}

	// Create renderer
	mRenderer_2 = SDL_CreateRenderer(mWindow_2, -1, 0);
	if (mRenderer_2 == nullptr)
	{
		std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
	}

	// Initalise SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL could not intialise! Error: " << SDL_GetError() << std::endl;
	}
	SDL_RenderClear(mRenderer_2);

	//bool ab = true;
	//SDL_Event ev;
	//SDL_LogDebug(SDL_LOG_CATEGORY_ERROR,"%c");
	//while (ab)
//	{
		// Handle events on queue
		//while (SDL_PollEvent(&ev) != 0)
		//{

			SDL_SetRenderDrawColor(mRenderer_2, 219, 184, 215, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(mRenderer_2);
			SDL_RenderPresent(mRenderer_2);
			SDL_Delay(800);
			//SDL_Delay(2000);
			// Handle quiting and completion
		//if (ev.type ==  SDL_QUIT)
			//{
				//ab = false;

				//SDL_DestroyRenderer(mRenderer_2);
			//	SDL_DestroyWindow(mWindow_2);
				//mRenderer_2 = nullptr;
			//	mWindow_2 = nullptr;

				//ev.type = SDL_QUIT;
				//close(mRenderer_2, mWindow_2, mFont_2);
				//break;
				//return 0;																			
			//}
		//}
	//}

	*/

 Sudoku::Wind::Wind()
 {
	 
	 
 }

 Sudoku::Wind::~Wind()
 {
	 std::cout << "dis" << std::endl;
 }

#include "MainGame.h"
#include "Errors.h"
#include "ImageLoader.h"
#include <iostream>
#include <string>


//Constructor, just initializes private member variables
MainGame::MainGame() : 
	_window(nullptr), 
	_screenHeight(768),
	_screenWidth(1024), 
	_time(0.0f), 
	_gameState(GameState::PLAY)
{
}

//Destructor
MainGame::~MainGame()
{
}

//This runs the game
void MainGame::run() {
	initSystems();

	//Initialize our sprite. (temporary)
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	_playerTexture = ImageLoader::loadPNG("Textures/JumperPack_Kenney/PNG/Players/bunny1_stand.png");
	//This only returns when the game ends
	gameLoop();
}

//Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems() {
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Open an SDL window
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("SDL Window could not be created!");
	}

	//Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}

	//Set up glew (optional but recommended)
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}

	//Tell SDL that we want a double buffered window so we dont get
	//any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Set the background color to blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	initShaders();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

//This is the main game loop for our program
void MainGame::gameLoop() {

	//Will loop until we set _gameState to EXIT
	while (_gameState != GameState::EXIT) {
		processInput();
		_time += 0.01;

		drawGame();
	}
}

//Processes input with SDL
void MainGame::processInput() {
	SDL_Event evnt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " change12 " << evnt.motion.y << std::endl;
			break;
		}
	}
}

//Draws the game using the almighty OpenGL
void MainGame::drawGame() {

	//Set the base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);


	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time); 

	//Draw our sprite!
	_sprite.draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	//Swap our buffer and draw everything to the screen!
	SDL_GL_SwapWindow(_window);
}
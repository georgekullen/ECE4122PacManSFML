/*
	Author: George Kullen
	Class: ECE4122
	Last Date Modified: 10/31/22

	Description: Pacman game using SFML.  Utilizes 2D vector array for coins and powerups and random ghost movement.

	Resources: https://www.programiz.com/cpp-programming/library-function/cmath/cos,
	https://www.sfml-dev.org/tutorials/2.5/window-events.php,
	https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php,
	https://www.sfml-dev.org/tutorials/2.5/graphics-transform.php,
	SFML tutorial Ch.5 Timber.cpp
*/

// Include important C++ libraries here
#include <sstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <random>

// Make code easier to type with "using namespace"
using namespace sf;

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 3);

bool DEBUG = false;
float GAMESPEED = 0.5;

std::vector<std::vector<char>> coinVector{
	{'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'},
	{'c', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', 'c'},
	{'P', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', 'P'},
	{'c', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', 'c'},
	{'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'},
	{'c', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', 'c'},
	{'c', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', 'c'},
	{'c', 'c', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', 'c', 'c'},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{'L', 'e', 'e', 'e', 'e', 'c', 'e', 'e', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'e', 'e', 'e', 'c', 'e', 'e', 'e', 'e', 'R'},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' '},
	{'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'},
	{'c', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', 'c'},
	{'c', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', 'c'},
	{'P', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'M', 'M', 'c', 'c', 'c', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'P'},
	{' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' '},
	{' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' '},
	{'c', 'c', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', ' ', ' ', 'c', 'c', 'c', 'c', 'c', 'c'},
	{'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c'},
	{'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c'},
	{'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'},
};

int main()
{
	// Create a video mode object
	VideoMode vm(641, 728);

	// Create and open a window for the game
	RenderWindow window(vm, "PAC-MAN", Style::Default);
	window.setFramerateLimit(120);
	std::vector<RectangleShape> invisWalls;
	invisWalls.resize(54);
	//define invisble walls
	invisWalls[0].setSize(sf::Vector2f(570, 15));
	invisWalls[0].setFillColor(sf::Color::Red);
	invisWalls[0].setPosition(32, 652);

	invisWalls[1].setSize(sf::Vector2f(570, 15));
	invisWalls[1].setFillColor(sf::Color::Red);
	invisWalls[1].setPosition(32, 22);

	invisWalls[2].setSize(sf::Vector2f(10, 210));
	invisWalls[2].setFillColor(sf::Color::Red);
	invisWalls[2].setPosition(32, 22);

	invisWalls[3].setSize(sf::Vector2f(10, 210));
	invisWalls[3].setFillColor(sf::Color::Red);
	invisWalls[3].setPosition(596, 22);

	invisWalls[4].setSize(sf::Vector2f(10, 235));
	invisWalls[4].setFillColor(sf::Color::Red);
	invisWalls[4].setPosition(596, 420);

	invisWalls[5].setSize(sf::Vector2f(10, 235));
	invisWalls[5].setFillColor(sf::Color::Red);
	invisWalls[5].setPosition(32, 420);

	invisWalls[6].setSize(sf::Vector2f(110, 10));
	invisWalls[6].setFillColor(sf::Color::Red);
	invisWalls[6].setPosition(32, 417);

	invisWalls[7].setSize(sf::Vector2f(110, 10));
	invisWalls[7].setFillColor(sf::Color::Red);
	invisWalls[7].setPosition(32, 344);

	invisWalls[8].setSize(sf::Vector2f(110, 10));
	invisWalls[8].setFillColor(sf::Color::Red);
	invisWalls[8].setPosition(494, 417);

	invisWalls[9].setSize(sf::Vector2f(110, 10));
	invisWalls[9].setFillColor(sf::Color::Red);
	invisWalls[9].setPosition(494, 344);

	invisWalls[10].setSize(sf::Vector2f(110, 10));
	invisWalls[10].setFillColor(sf::Color::Red);
	invisWalls[10].setPosition(32, 294);

	invisWalls[11].setSize(sf::Vector2f(110, 10));
	invisWalls[11].setFillColor(sf::Color::Red);
	invisWalls[11].setPosition(494, 294);

	invisWalls[12].setSize(sf::Vector2f(110, 10));
	invisWalls[12].setFillColor(sf::Color::Red);
	invisWalls[12].setPosition(32, 223);

	invisWalls[13].setSize(sf::Vector2f(110, 10));
	invisWalls[13].setFillColor(sf::Color::Red);
	invisWalls[13].setPosition(494, 223);

	invisWalls[14].setSize(sf::Vector2f(10, 80));
	invisWalls[14].setFillColor(sf::Color::Red);
	invisWalls[14].setPosition(134, 222);

	invisWalls[15].setSize(sf::Vector2f(10, 80));
	invisWalls[15].setFillColor(sf::Color::Red);
	invisWalls[15].setPosition(134, 345);

	invisWalls[16].setSize(sf::Vector2f(10, 80));
	invisWalls[16].setFillColor(sf::Color::Red);
	invisWalls[16].setPosition(494, 345);

	invisWalls[17].setSize(sf::Vector2f(35, 20));
	invisWalls[17].setFillColor(sf::Color::Red);
	invisWalls[17].setPosition(561, 530);

	invisWalls[18].setSize(sf::Vector2f(35, 20));
	invisWalls[18].setFillColor(sf::Color::Red);
	invisWalls[18].setPosition(44, 529);

	invisWalls[19].setSize(sf::Vector2f(10, 80));
	invisWalls[19].setFillColor(sf::Color::Red);
	invisWalls[19].setPosition(247, 285);

	invisWalls[20].setSize(sf::Vector2f(10, 80));
	invisWalls[20].setFillColor(sf::Color::Red);
	invisWalls[20].setPosition(380, 285);

	invisWalls[21].setSize(sf::Vector2f(120, 10));
	invisWalls[21].setFillColor(sf::Color::Red);
	invisWalls[21].setPosition(258, 355);

	invisWalls[22].setSize(sf::Vector2f(90, 10));
	invisWalls[22].setFillColor(sf::Color::Red);
	invisWalls[22].setPosition(257, 285);

	invisWalls[23].setSize(sf::Vector2f(34, 10));
	invisWalls[23].setFillColor(sf::Color::Red);
	invisWalls[23].setPosition(346, 285);

	invisWalls[24].setSize(sf::Vector2f(18, 78));
	invisWalls[24].setFillColor(sf::Color::Red);
	invisWalls[24].setPosition(310, 37);

	invisWalls[25].setSize(sf::Vector2f(56, 35));
	invisWalls[25].setFillColor(sf::Color::Red);
	invisWalls[25].setPosition(86, 81);

	invisWalls[26].setSize(sf::Vector2f(56, 35));
	invisWalls[26].setFillColor(sf::Color::Red);
	invisWalls[26].setPosition(496, 81);

	invisWalls[27].setSize(sf::Vector2f(72, 35));
	invisWalls[27].setFillColor(sf::Color::Red);
	invisWalls[27].setPosition(190, 81);

	invisWalls[28].setSize(sf::Vector2f(72, 35));
	invisWalls[28].setFillColor(sf::Color::Red);
	invisWalls[28].setPosition(375, 81);

	invisWalls[29].setSize(sf::Vector2f(48, 16));
	invisWalls[29].setFillColor(sf::Color::Red);
	invisWalls[29].setPosition(89, 162);

	invisWalls[30].setSize(sf::Vector2f(48, 16));
	invisWalls[30].setFillColor(sf::Color::Red);
	invisWalls[30].setPosition(498, 162);

	invisWalls[31].setSize(sf::Vector2f(17, 130));
	invisWalls[31].setFillColor(sf::Color::Red);
	invisWalls[31].setPosition(186, 164);

	invisWalls[32].setSize(sf::Vector2f(53, 15));
	invisWalls[32].setFillColor(sf::Color::Red);
	invisWalls[32].setPosition(206, 223);

	invisWalls[33].setSize(sf::Vector2f(17, 130));
	invisWalls[33].setFillColor(sf::Color::Red);
	invisWalls[33].setPosition(432, 164);

	invisWalls[34].setSize(sf::Vector2f(53, 15));
	invisWalls[34].setFillColor(sf::Color::Red);
	invisWalls[34].setPosition(373, 223);

	invisWalls[35].setSize(sf::Vector2f(10, 70));
	invisWalls[35].setFillColor(sf::Color::Red);
	invisWalls[35].setPosition(494, 224);

	invisWalls[36].setSize(sf::Vector2f(130, 17));
	invisWalls[36].setFillColor(sf::Color::Red);
	invisWalls[36].setPosition(252, 161);

	invisWalls[37].setSize(sf::Vector2f(17, 60));
	invisWalls[37].setFillColor(sf::Color::Red);
	invisWalls[37].setPosition(310, 177);

	invisWalls[38].setSize(sf::Vector2f(15, 70));
	invisWalls[38].setFillColor(sf::Color::Red);
	invisWalls[38].setPosition(188, 350);

	invisWalls[39].setSize(sf::Vector2f(15, 70));
	invisWalls[39].setFillColor(sf::Color::Red);
	invisWalls[39].setPosition(434, 350);

	invisWalls[40].setSize(sf::Vector2f(130, 17));
	invisWalls[40].setFillColor(sf::Color::Red);
	invisWalls[40].setPosition(254, 407);

	invisWalls[41].setSize(sf::Vector2f(17, 60));
	invisWalls[41].setFillColor(sf::Color::Red);
	invisWalls[41].setPosition(310, 423);

	invisWalls[42].setSize(sf::Vector2f(70, 17));
	invisWalls[42].setFillColor(sf::Color::Red);
	invisWalls[42].setPosition(191, 469);

	invisWalls[43].setSize(sf::Vector2f(70, 17));
	invisWalls[43].setFillColor(sf::Color::Red);
	invisWalls[43].setPosition(375, 469);

	invisWalls[44].setSize(sf::Vector2f(40, 15));
	invisWalls[44].setFillColor(sf::Color::Red);
	invisWalls[44].setPosition(88, 469);

	invisWalls[45].setSize(sf::Vector2f(15, 70));
	invisWalls[45].setFillColor(sf::Color::Red);
	invisWalls[45].setPosition(127, 469);

	invisWalls[46].setSize(sf::Vector2f(15, 70));
	invisWalls[46].setFillColor(sf::Color::Red);
	invisWalls[46].setPosition(496, 469);

	invisWalls[47].setSize(sf::Vector2f(40, 15));
	invisWalls[47].setFillColor(sf::Color::Red);
	invisWalls[47].setPosition(512, 469);

	invisWalls[48].setSize(sf::Vector2f(173, 17));
	invisWalls[48].setFillColor(sf::Color::Red);
	invisWalls[48].setPosition(88, 592);

	invisWalls[49].setSize(sf::Vector2f(17, 60));
	invisWalls[49].setFillColor(sf::Color::Red);
	invisWalls[49].setPosition(187, 534);

	invisWalls[50].setSize(sf::Vector2f(130, 17));
	invisWalls[50].setFillColor(sf::Color::Red);
	invisWalls[50].setPosition(252, 530);

	invisWalls[51].setSize(sf::Vector2f(17, 60));
	invisWalls[51].setFillColor(sf::Color::Red);
	invisWalls[51].setPosition(310, 546);

	invisWalls[52].setSize(sf::Vector2f(173, 17));
	invisWalls[52].setFillColor(sf::Color::Red);
	invisWalls[52].setPosition(375, 591);

	invisWalls[53].setSize(sf::Vector2f(17, 60));
	invisWalls[53].setFillColor(sf::Color::Red);
	invisWalls[53].setPosition(433, 532);

	//PAC-MAN Title Screen
	Texture textureTitle;
	textureTitle.loadFromFile("C:/Users/George/source/repos/Lab3-2/Beginning-Cpp-Game-Programming-Second-Edition-master/Chapter05/graphics/pac-man.bmp");
	Sprite spriteTitle;
	spriteTitle.setTexture(textureTitle);
	spriteTitle.setPosition(0, 0);

	//Define the Maze
	Texture textureMaze;
	textureMaze.loadFromFile("C:/Users/George/source/repos/Lab3-2/Beginning-Cpp-Game-Programming-Second-Edition-master/Chapter05/graphics/maze.bmp");
	Sprite spriteMaze;
	spriteMaze.setTexture(textureMaze);
	spriteMaze.setPosition(0, 0);

	//Pac-Man
	Texture texturePacMan;
	texturePacMan.loadFromFile("C:/Users/George/source/repos/Lab3-2/Beginning-Cpp-Game-Programming-Second-Edition-master/Chapter05/graphics/pacman.bmp");
	Sprite pacManSprite;
	pacManSprite.setTexture(texturePacMan);

	//Red Ghost
	Texture textureRedGhost;
	textureRedGhost.loadFromFile("C:/Users/George/source/repos/Lab3-2/Beginning-Cpp-Game-Programming-Second-Edition-master/Chapter05/graphics/red_ghosts.bmp");
	Sprite redGhostSprite;
	redGhostSprite.setTexture(textureRedGhost);
	redGhostSprite.setPosition(0, 0);

	//Blue Ghost
	Texture textureBlueGhost;
	textureBlueGhost.loadFromFile("C:/Users/George/source/repos/Lab3-2/Beginning-Cpp-Game-Programming-Second-Edition-master/Chapter05/graphics/blue_ghost.bmp");
	Sprite blueGhostSprite;
	blueGhostSprite.setTexture(textureBlueGhost);
	blueGhostSprite.setPosition(0, 0);

	//Pink Ghost
	Texture texturePinkGhost;
	texturePinkGhost.loadFromFile("C:/Users/George/source/repos/Lab3-2/Beginning-Cpp-Game-Programming-Second-Edition-master/Chapter05/graphics/pink_ghost.bmp");
	Sprite pinkGhostSprite;
	pinkGhostSprite.setTexture(texturePinkGhost);
	pinkGhostSprite.setPosition(0, 0);

	//Orange Ghost
	Texture textureOrangeGhost;
	textureOrangeGhost.loadFromFile("C:/Users/George/source/repos/Lab3-2/Beginning-Cpp-Game-Programming-Second-Edition-master/Chapter05/graphics/orange_ghost.bmp");
	Sprite orangeGhostSprite;
	orangeGhostSprite.setTexture(textureOrangeGhost);
	orangeGhostSprite.setPosition(0, 0);

	//Start Message Text
	Text startText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	startText.setFont(font);
	startText.setString("Press Enter to start!");
	startText.setCharacterSize(36);
	startText.setFillColor(Color::White);
	FloatRect startTextRect = startText.getLocalBounds();
	startText.setOrigin(startTextRect.left +
		startTextRect.width / 2.0f,
		startTextRect.top +
		startTextRect.height / 2.0f);
	startText.setPosition(641 / 2.0f, 728 / 2.0f);

	//Score Text
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("01234");
	scoreText.setCharacterSize(35);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(140,670);

	//Lives Text
	Text livesText;
	livesText.setFont(font);
	livesText.setString("01234");
	livesText.setCharacterSize(35);
	livesText.setFillColor(Color::White);
	livesText.setPosition(409, 670);

	SoundBuffer gameStartBuffer;
	gameStartBuffer.loadFromFile("C:/Users/George/source/repos/Lab3-2/Beginning-Cpp-Game-Programming-Second-Edition-master/Chapter05/sound/pacman-beginning");
	Sound pacManBeginning;
	pacManBeginning.setBuffer(gameStartBuffer);

	// Control the player input
	bool acceptInput = false;

	//game start
	bool begin = false;

	//game pause
	bool paused = true;

	int score = 0;
	int lives = 1;
	bool powerUpEaten = false;

	int xPacMan = 302;
	int yPacMan = 491;
	pacManSprite.setPosition(xPacMan, yPacMan);

	char pacManDirection = 'l';
	std::chrono::time_point<std::chrono::system_clock> m_StartTime = std::chrono::system_clock::now();
	int red[3] = { 301, 247, distribution(generator)};
	int blue[3] = { 301, 247, rand() % 4 + 1};
	int orange[3] = { 301, 247, rand() % 4 + 1 };
	int pink[3] = { 301, 247, rand() % 4 + 1 };
	int count = 0;

	while (window.isOpen()) {
		//power up timer
		if (powerUpEaten) {
			std::cout << "POWERUP!";
			if ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_StartTime).count()) / 1000.0 >= 5) {
				powerUpEaten = false;
			}
		}
		//score check
		if (score == 240) {
			window.close();
		}
		//pacman and ghost collisions
		if (pacManSprite.getGlobalBounds().intersects(redGhostSprite.getGlobalBounds())) {
			if (powerUpEaten) {
				red[0] = 1000;
				red[1] = 1000;
				red[2] = 1;
			}
			else {
				window.close();
			}
		}
		if (pacManSprite.getGlobalBounds().intersects(blueGhostSprite.getGlobalBounds())) {
			if (powerUpEaten) {
				blue[0] = 1000;
				blue[1] = 1000;
				blue[2] = 1;
			}
			else {
				window.close();
			}
		}
		if (pacManSprite.getGlobalBounds().intersects(orangeGhostSprite.getGlobalBounds())) {
			if (powerUpEaten) {
				orange[0] = 1000;
				orange[1] = 1000;
				orange[2] = 1;
			}
			else {
				window.close();
			}
		}
		if (pacManSprite.getGlobalBounds().intersects(pinkGhostSprite.getGlobalBounds())) {
			if (powerUpEaten) {
				pink[0] = 1000;
				pink[1] = 1000;
				pink[2] = 1;
			}
			else {
				window.close();
			}
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;
			}

		}

		/*
		****************************************
		Handle the players input
		****************************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			begin = true;
			acceptInput = true;
			if (DEBUG) {
				std::cout << "game start/resume";
			}
			pacManBeginning.play();
		}

		window.clear();
		if (begin) {
			// Wrap the player controls to
			// Make sure we are accepting input
			if (acceptInput)
			{
				// More code here next...
				// First handle pressing the right cursor key
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					pacManDirection = 'r';
					acceptInput = false;
				}

				// Handle the left cursor key
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					pacManDirection = 'l';
					acceptInput = false;
				}
				// Handle the down cursor key
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					pacManDirection = 'd';
					acceptInput = false;
				}
				// Handle the up cursor key
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					pacManDirection = 'u';
					acceptInput = false;
				}
			}
			
			//pacMan Movement
			if (pacManDirection == 'l') {
				xPacMan--;
				pacManSprite.setPosition(xPacMan, yPacMan);
				for (int i = 0; i < 54; i++) {
					if (pacManSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						xPacMan++;
					}
				}
			}
			else if (pacManDirection == 'r') {
				xPacMan++;
				pacManSprite.setPosition(xPacMan, yPacMan);
				for (int i = 0; i < 54; i++) {
					if (pacManSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						xPacMan--;
					}
				}
			}
			else if (pacManDirection == 'u') {
				yPacMan--;
				pacManSprite.setPosition(xPacMan, yPacMan);
				for (int i = 0; i < 54; i++) {
					if (pacManSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						yPacMan++;
					}
				}
			}
			else if (pacManDirection == 'd') {
				yPacMan++;
				pacManSprite.setPosition(xPacMan, yPacMan);
				for (int i = 0; i < 54; i++) {
					if (pacManSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						yPacMan--;
					}
				}
			}

			//red ghost movement
			redGhostSprite.setPosition(red[0], red[1]);
			if (red[2] == 0) {
				red[0]++;
				redGhostSprite.setPosition(red[0], red[1]);
				for (int i = 0; i < 54; i++) {
					if (redGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						red[2] = distribution(generator);
						red[0]--;
					}
				}
			}
			else if (red[2] == 1) {
				red[0]--;
				redGhostSprite.setPosition(red[0], red[1]);
				for (int i = 0; i < 54; i++) {
					if (redGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						red[2] = distribution(generator);
						red[0]++;
					}
				}
			}
			else if (red[2] == 2) {
				red[1]++;
				redGhostSprite.setPosition(red[0], red[1]);
				for (int i = 0; i < 54; i++) {
					if (redGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						red[2] = distribution(generator);
						red[1]--;
					}		
				}
			}
			else if (red[2] == 3) {
				red[1]--;
				redGhostSprite.setPosition(red[0], red[1]);
				for (int i = 0; i < 54; i++) {
					if (redGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						red[2] = distribution(generator);
						red[1]++;
					}	
				}
			}
			redGhostSprite.setPosition(red[0], red[1]);
			//blue ghost movement
			if (blue[2] == 1) {
				blue[0]++;
				blueGhostSprite.setPosition(blue[0], blue[1]);
				for (int i = 0; i < 54; i++) {
					if (blueGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						blue[2] = (rand() % 4) + 1;
						blue[0]--;
					}
				}
			}
			else if (blue[2] == 2) {
				blue[0]--;
				blueGhostSprite.setPosition(blue[0], blue[1]);
				for (int i = 0; i < 54; i++) {
					if (blueGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						blue[2] = (rand() % 4) + 1;
						blue[0]++;
						break;
					}
				}
			}
			else if (blue[2] == 3) {
				blue[1]++;
				blueGhostSprite.setPosition(blue[0], blue[1]);
				for (int i = 0; i < 54; i++) {
					if (blueGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						blue[2] = (rand() % 4) + 1;
						blue[1]--;
						break;
					}
				}
			}
			else if (blue[2] == 4) {
				blue[1]--;
				blueGhostSprite.setPosition(blue[0], blue[1]);
				for (int i = 0; i < 54; i++) {
					if (blueGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						blue[2] = (rand() % 4) + 1;
						blue[1]++;
						break;
					}
				}
			}
			blueGhostSprite.setPosition(blue[0], blue[1]);
			//orange ghost movement
			if (orange[2] == 1) {
				orange[0]++;
				orangeGhostSprite.setPosition(orange[0], orange[1]);
				for (int i = 0; i < 54; i++) {
					if (orangeGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						orange[2] = (rand() % 4) + 1;
						orange[0]--;
						break;
					}
				}
			}
			else if (orange[2] == 2) {
				orange[0]--;
				orangeGhostSprite.setPosition(orange[0], orange[1]);
				for (int i = 0; i < 54; i++) {
					if (orangeGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						orange[2] = (rand() % 4) + 1;
						orange[0]++;
						break;
					}
				}
			}
			else if (orange[2] == 3) {
				orange[1]++;
				orangeGhostSprite.setPosition(orange[0], orange[1]);
				for (int i = 0; i < 54; i++) {
					if (orangeGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						orange[2] = (rand() % 4) + 1;
						orange[1]--;
						break;
					}
				}
			}
			else if (orange[2] == 4) {
				orange[1]--;
				orangeGhostSprite.setPosition(orange[0], orange[1]);
				for (int i = 0; i < 54; i++) {
					if (orangeGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						orange[2] = (rand() % 4) + 1;
						orange[1]++;
						break;
					}
				}
			}
			orangeGhostSprite.setPosition(orange[0], orange[1]);
			//pink ghost movement
			if (pink[2] == 1) { 
				pink[0]++;
				pinkGhostSprite.setPosition(pink[0], pink[1]);
				for (int i = 0; i < 54; i++) {
					if (pinkGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						pink[2] = (rand() % 4) + 1;
						pink[0]--;
						break;
					}
				}
			}
			else if (pink[2] == 2) {
				pink[0]--;
				pinkGhostSprite.setPosition(pink[0], pink[1]);
				for (int i = 0; i < 54; i++) {
					if (pinkGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						pink[2] = (rand() % 4) + 1;
						pink[0]++;
						break;
					}
				}
			}
			else if (pink[2] == 3) {
				pink[1]++;
				pinkGhostSprite.setPosition(pink[0], pink[1]);
				for (int i = 0; i < 54; i++) {
					if (pinkGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						pink[2] = (rand() % 4) + 1;
						pink[1]--;
						break;
					}
				}
			}
			else if (pink[2] == 4) {
				pink[1]--;
				pinkGhostSprite.setPosition(pink[0], pink[1]);
				for (int i = 0; i < 54; i++) {
					if (pinkGhostSprite.getGlobalBounds().intersects(invisWalls[i].getGlobalBounds())) {
						pink[2] = (rand() % 4) + 1;
						pink[1]++;
						break;
					}
				}
			}
			pinkGhostSprite.setPosition(pink[0], pink[1]);
			
			pacManSprite.setPosition(xPacMan, yPacMan);
			window.draw(spriteMaze);

			//draw score and lives
			std::stringstream ss;
			ss << score;
			scoreText.setString(ss.str());
			window.draw(scoreText);
			std::stringstream ss2;
			ss2 << lives;
			livesText.setString(ss2.str());
			window.draw(livesText);
			if (DEBUG) {
				for (int i = 0; i < 54; i++) {
					window.draw(invisWalls[i]);
				}
			}
			//Draw the coins and Powerups
			int xOffset = 60;
			int yOffset = 55;
			int coinOffset = 20;
			CircleShape coin(2.5);
			CircleShape powerUp(6);
			if (DEBUG) {
				coin.setFillColor(sf::Color(255, 0, 0));
				powerUp.setFillColor(sf::Color(255, 0, 0));
			}
			for (int r = 0; r < 29; r++) {
				for (int c = 0; c < 26; c++) {
					if (coinVector[r][c] == 'c') {
						//draw coin
						coin.setPosition(xOffset + (c * 20.5), yOffset + (r * 20.5));
						if (pacManSprite.getGlobalBounds().intersects(coin.getGlobalBounds()))
						{
							if (DEBUG) {
								std::cout << "coin eaten";
							}
							coinVector[r][c] = 'e';
							score++;
							std::cout << coinVector[r][c];
						} else {
							window.draw(coin);
						}
					}
					else if (coinVector[r][c] == 'P') { //powerup draw
						powerUp.setPosition(xOffset + (c * 20.5) - 3.5, yOffset + (r * 20.5) - 3.5);
						if (pacManSprite.getGlobalBounds().intersects(powerUp.getGlobalBounds()))
						{
							coinVector[r][c] = 'e';
							std::cout << coinVector[r][c];
							powerUpEaten = true;
							m_StartTime = std::chrono::system_clock::now();
						}
						else {
							window.draw(powerUp);
						}
					}
					else if (coinVector[r][c] == 'L') { //left tunnel check
						coin.setPosition(xOffset + (c * 20.5), yOffset + (r * 20.5));
						if (pacManSprite.getGlobalBounds().intersects(coin.getGlobalBounds())) {
							xPacMan = 500;
							yPacMan = 306;
							pacManSprite.setPosition(xPacMan, yPacMan);
						}
					}
					else if (coinVector[r][c] == 'R') { //right tunnel check
						coin.setPosition(xOffset + (c * 20.5), yOffset + (r * 20.5));
						if (pacManSprite.getGlobalBounds().intersects(coin.getGlobalBounds())) {
							xPacMan = 91;
							yPacMan = 307;
							pacManSprite.setPosition(xPacMan, yPacMan);
						}
					}
				}
			}
			//Draw sprites
			window.draw(pacManSprite);
			window.draw(redGhostSprite);
			window.draw(blueGhostSprite);
			window.draw(pinkGhostSprite);
			window.draw(orangeGhostSprite);
		}
		else {
			window.draw(spriteTitle);
			window.draw(startText);
		}
		window.display();
		acceptInput = true;
	}
}
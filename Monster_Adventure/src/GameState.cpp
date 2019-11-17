#include "GameState.h"

//Initialization
void GameState::initKeybinds()
{
	std::ifstream fileconfig("src/Config/gamestate_keybinds.ini");
	if (fileconfig.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (fileconfig >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	fileconfig.close();
}

void GameState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[GAME State] >> ..ERROR.. Could't load font");
	}
}

void GameState::initTexture()
{
	//load all palyer texture
	if (!this->textures["PLAYER_SHEET_DUDE"].loadFromFile("src/Resource/Charector/Player/Dude/Dude_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["PLAYER_SHEET_PINK"].loadFromFile("src/Resource/Charector/Player/Pink/Pink_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["PLAYER_SHEET_OWLET"].loadFromFile("src/Resource/Charector/Player/Owlet/Owlet_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["ENEMY_SHEET_SKELETON"].loadFromFile("src/Resource/Charector/Enemy/Skeleton/Skeleton_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load Enemy texture");
	}
}

void GameState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("src/Resource/Background/MainMenuState/background.png")) {
		throw("[Game State] >> ..ERROR.. Could't load backgroundTexture");
	}

	for (int i = 0; i < 2; i++) {
		sf::RectangleShape buff;
		buff.setTexture(&this->backgroundTexture);
		this->background.push_back(buff);
		this->background[i].setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
		this->background[i].setPosition(static_cast<float>(this->window->getSize().x) * i, 0.0f);
	}
}

void GameState::initPlayer()
{
	if (this->playerIndex == 0) {
		this ->player = new Player(600, 0, this->textures["PLAYER_SHEET_DUDE"], this->playerName);
	}
	if (this->playerIndex == 1) {
		this->player = new Player(600, 0, this->textures["PLAYER_SHEET_PINK"], this->playerName);
	}
	if (this->playerIndex == 2) {
		this->player = new Player(600, 0, this->textures["PLAYER_SHEET_OWLET"], this->playerName);
	}
}

void GameState::initEnemy()
{
	for (short unsigned i = 1; i < 5; i++) {
		this->enemy.push_back(new Enemy(200.0f * i, 0.0f, this->textures["ENEMY_SHEET_SKELETON"], "1"));
	}
}

void GameState::initView()
{
	this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
	
	this->view.setCenter(this->player->getCenter().x, this->window->getSize().y / 2.0f);

	this->window->setView(this->view);
}

void GameState::initUI()
{
	//create nameText
	this->nameText.setFont(this->font);
	this->nameText.setCharacterSize(30);
	this->nameText.setString(this->player->getName());
	this->nameText.setPosition(
		this->view.getCenter().x + 300.0f,
		10.0f
	);
	//create HPText
	this->HPText.setFont(this->font);
	this->HPText.setCharacterSize(30);
	this->HPText.setString("HP");
	this->HPText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 20.0f,
		10.0f
	);
	//create scoreText
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(30);
	this->scoreText.setString("SCORE :");
	this->scoreText.setPosition(
		this->view.getCenter().x + 300.0f,
		50.0f
	);


	//create playerShowHPBar
	this->playerShowHPBar.setOutlineThickness(5.0f);
	this->playerShowHPBar.setOutlineColor(sf::Color::Black);
	this->playerShowHPBar.setFillColor(sf::Color::Green);
	this->playerShowHPBar.setSize(sf::Vector2f(
		(this->view.getSize().x / 2.0f)*(this->player->getCurrHP() / this->player->getMaxHP()) , 
		20.0f
	));
	this->playerShowHPBar.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 80.0f, 
		20.0f
	);
	//create playerShowScoreText
	std::stringstream int_to_string;
	int_to_string << this->player->getScore();
	this->playerShowScoreText.setFont(this->font);
	this->playerShowScoreText.setCharacterSize(30);
	this->playerShowScoreText.setString(int_to_string.str());
	this->playerShowScoreText.setPosition(
		this->view.getCenter().x + 420.0f,
		50.0f
	);
}

void GameState::initPopUpMenu()
{
	this->pauseMenu = new PopUpMenu(this->view, this->font);
	this->pauseMenu->setMenuTextString("PAUSED");
	this->pauseMenu->addButton("Resume", 4.0f, "RESUME");
	this->pauseMenu->addButton("Quit", 6.0f, "QUIT");

	this->gameOverMenu = new PopUpMenu(this->view, this->font);
	this->gameOverMenu->setMenuTextString("GAME OVER");
	this->gameOverMenu->setWidth((this->view.getSize().x / 16.0f) * 6.0f);
	this->gameOverMenu->addButton("Quit", 9.0f, "EXIT TO MENU");
}

//Constructor , Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,
	short unsigned player_index, std::string player_name)
	:State(window, supportedKeys, states), playerIndex(player_index), playerName(player_name)
{
	std::cout << "[Game State] >> On" << std::endl;
	this->initKeybinds();
	this->initFonts();

	this->initTexture();
	this->initBackground();

	this->initPlayer();
	this->initEnemy();

	this->initView();
	this->initUI();
	this->initPopUpMenu();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	delete this->player;

	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			delete this->enemy[i];
			this->enemy.pop_back();
		}
	}
}

//Function
void GameState::updateState(const float &dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);

	//gameover 
	if (this->gameover) {
		this->updateGameOverMenuButton();
	}
	//not gameover
	else {
		this->updateInput(dt);

		//Unpaused update
		if (!this->paused) {
			this->updatePlayer(dt);
			this->updateEnemy(dt);
			this->updateUI();

			//clear enemy when it died
			if (!this->enemy.empty()) {
				for (int i = 0; i < this->enemy.size(); i++) {
					if (this->enemy[i]->getDied()) {
						this->player->increaseScore(this->enemy[i]->getPoint());

						delete enemy[i];
						this->enemy.erase(this->enemy.begin() + i);
					}
				}
			}

			//clear player when died
			if (this->player->getDied()) {
				this->overState();

				//write score in score.data
				std::fstream scorefile("src/Config/Data/Score.data", std::ios::app);
				scorefile << "\n" << this->player->getName();
				scorefile << "\t\t" << this->player->getScore();
				scorefile.close();
			}
		}
		//Paused update
		else if (this->paused) {
			this->updatePauseMenuButton();
		}
	}

	this->updateView();
}

void GameState::updateInput(const float &dt)
{
	//Update paused input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()) {
		if (!this->paused) {
			this->pausedState();
		}
		else {
			this->unpausedState();
		}
	}
}

void GameState::updatePlayer(const float & dt)
{
	//Update player input
	if (!this->player->getAttacking()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
			this->player->moveEntity(-1.0f, 0.0f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
			this->player->moveEntity(1.0f, 0.0f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))) && !this->player->getJumpping()) {
			this->player->jump();
		}
	}

	if (!this->player->getJumpping() && !this->player->getHurting()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ATTACK"))) && !this->player->getAttacking()) {
			if (!this->enemy.empty()) {
				srand(int(time(NULL)));
				
				for (int i = 0; i < this->enemy.size(); i++) {
					//random attack style [chance to double is 40%]
					if (rand() % 100 <= 40) {
						this->player->attack(dt, Player::ATTACK_DOUBLE, this->enemy[i]);
					}
					else {
						this->player->attack(dt, Player::ATTACK_ONCE, this->enemy[i]);
					}
				}
			}
		}
	}

	//Update all player component
	this->player->updateEntity(dt, *this->window);
}

void GameState::updateEnemy(const float &dt)
{
	//Control enemy
	this->updateEnemyControl(dt);

	//Update all Entity component
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			this->enemy[i]->updateEntity(dt, *this->window);
		}
	}
}

void GameState::updateEnemyControl(const float& dt)
{
	if (!this->enemy.empty()) {
		srand(int(time(NULL)));
		for (int i = 0; i < this->enemy.size(); i++) {
			//control bot walk to player
			if (std::abs(this->player->getCenter().x - this->enemy[i]->getCenter().x) <= 300.0f && std::abs(this->player->getCenter().x - this->enemy[i]->getCenter().x) >=50) {
				if (this->player->getCenter().x < this->enemy[i]->getCenter().x) {
					this->enemy[i]->moveEntity(-1.0f, 0.0f, dt);
				}
				if (this->player->getCenter().x > this->enemy[i]->getCenter().x) {
					this->enemy[i]->moveEntity(1.0f, 0.0f,dt);
				}
			}

			//control bot attack player [enemy chance to attack is 80%]
			if (rand() % 100 <= 80) {
				if (std::abs(this->player->getCenter().x - this->enemy[i]->getCenter().x) <= 100.0f && !this->enemy[i]->getAttacking()) {
					this->enemy[i]->attack(dt, Enemy::ATTACK_ONCE, this->player);
				}
			}
		}
	}
}

//update
void GameState::updateView()
{
	this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
	this->view.setCenter(this->player->getCenter().x, this->window->getSize().y / 2.0f);

	this->window->setView(this->view);

	
	if (this->view.getCenter().x - this->view.getSize().x / 2.0f < 0.0f || this->getQuit()) {
		this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
		this->view.setCenter(
			this->window->getSize().x / 2.0f,
			this->window->getSize().y / 2.0f
		);
		this->window->setView(this->view);
	}
}

void GameState::updateUI()
{
	
	//update nameText
	this->nameText.setPosition(
		this->view.getCenter().x + 300.0f,
		10.0f
	);
	//update HPText
	this->HPText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 20.0f,
		10.0f
	);
	//update scoreText
	this->scoreText.setPosition(
		this->view.getCenter().x + 300.0f,
		50.0f
	);


	//update playerShowHPBar
	if ((this->player->getCurrHP() / this->player->getMaxHP()) * 100.0f <= 50.0f) {
		this->playerShowHPBar.setFillColor(sf::Color::Yellow);
	}
	if ((this->player->getCurrHP() / this->player->getMaxHP()) * 100.0f <= 20.0f) {
		this->playerShowHPBar.setFillColor(sf::Color::Red);
	}

	if (this->player->getCurrHP() <= 0.0f) {
		this->playerShowHPBar.setSize(sf::Vector2f(
			0.0f,
			20.0f
		));
	}
	else {
		this->playerShowHPBar.setSize(sf::Vector2f(
			(this->view.getSize().x / 2.0f)*(this->player->getCurrHP() / this->player->getMaxHP()),
			20.0f
		));
	}
	this->playerShowHPBar.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 80.0f,
		20.0f
	);

	//update playerShowScoreText
	std::stringstream int_to_string;
	int_to_string << this->player->getScore();
	this->playerShowScoreText.setString(int_to_string.str());
	this->playerShowScoreText.setPosition(
		this->view.getCenter().x + 420.0f,
		50.0f
	);
}

void GameState::updatePauseMenuButton()
{
	//Update all the buttons in Paused Menu
	this->pauseMenu->updatePauseMenu(this->mousePosView, this->view);

	//Action button
	if (this->pauseMenu->isButtonPreesed("Resume")) {
		this->unpausedState();
	}
	if (this->pauseMenu->isButtonPreesed("Quit")) {
		this->endState();
	}
}

void GameState::updateGameOverMenuButton()
{
	//update content
	std::stringstream int_to_string;
	int_to_string << this->player->getScore();
	this->gameOverMenu->setDescriptTextString("Score : " + int_to_string.str());

	//Update all the buttons in Game Over Menu
	this->gameOverMenu->updatePauseMenu(this->mousePosView, this->view);

	//Action button
	if (this->gameOverMenu->isButtonPreesed("Quit")) {
		this->endState();
	}
}

//render
void GameState::renderState(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	for (int i = 0; i < this->background.size(); i++) {
		target->draw(this->background[i]);
	}

	//render UI
	this->renderUI(target);

	//render all entity 
	this->renderEnemy(target);
	this->renderPlayer(target);

	//paused menu render
	if (this->paused) {		
		this->pauseMenu->renderPauseMenu(*target);
	}

	//gameover menu render
	if (this->gameover) {
		this->gameOverMenu->renderPauseMenu(*target);
	}
}

void GameState::renderPlayer(sf::RenderTarget * target)
{
	this->player->renderEntity(*target);
}

void GameState::renderEnemy(sf::RenderTarget* target)
{
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			this->enemy[i]->renderEntity(*target);
		}
	}
}

void GameState::renderUI(sf::RenderTarget * target)
{
	target->draw(this->nameText);

	target->draw(this->HPText);
	target->draw(this->scoreText);

	target->draw(this->playerShowHPBar);
	target->draw(this->playerShowScoreText);
}


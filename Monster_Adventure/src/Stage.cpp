#include "Stage.h"

//initialization
void Stage::initVariable()
{
	this->clear = false;
}

Stage::Stage(sf::RenderWindow* window, Player *player)
	: window(window), player(player)
{
	this->initVariable();
}

Stage::~Stage()
{
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			delete this->enemy[i];

			this->enemy.erase(this->enemy.begin() + i);
		}

		// fit size vector
		this->enemy.shrink_to_fit();
	}
}

//Accessor
const sf::Vector2f Stage::getStageSize()
{
	if (!this->background.empty()) {
		float size_x = 0;
		float size_y = 0;
		for (int i = 0; i < this->background.size(); i++) {
			size_x += this->background[i].getSize().x;
			size_y += this->background[i].getSize().y;
		}
		return sf::Vector2f(size_x, size_y);
	}
	else {
		return sf::Vector2f(0.0f, 0.0f);
	}
}

const bool& Stage::getClear()
{
	return this->clear;
}

std::vector<Enemy*>& Stage::getEnemy()
{
	return this->enemy;
}

//Function
void Stage::addBackground(short unsigned background_id)
{
	//select background
	if (background_id == 1) {
		if (!this->background_texture.loadFromFile("src/Resource/Background/GameState/background_1.png")) {
			throw("[Stage] >> ..ERROR.. Could't load backgroundTexture");
		}
	}
	if (background_id == 2) {
		if (!this->background_texture.loadFromFile("src/Resource/Background/GameState/background_2.png")) {
			throw("[Stage] >> ..ERROR.. Could't load backgroundTexture");
		}
	}
		
	//create background
	int start_count = (int)this->background.size();
	int end_count = start_count + 2;
	for (int i = start_count; i < end_count; i++) {
		sf::RectangleShape buff;
		buff.setTexture(&this->background_texture);

		this->background.push_back(buff);
		this->background[i].setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
		this->background[i].setPosition(static_cast<float>(this->window->getSize().x) * i, 0.0f);
	}
}

void Stage::addEnemy(const float x, const float y, sf::Texture & texture_sheet, std::string id)
{
	//push enemy into enemy vactor
	this->enemy.push_back(new Enemy(x,y,texture_sheet,id));

	// fit size vector
	this->enemy.shrink_to_fit();
}

void Stage::updateStage(const float & dt)
{
	//update enemy
	this->updateEnemy(dt);

	//cleared stage if all enemy down
	if (this->enemy.empty()) {
		this->clear = true;
	}
}

void Stage::updateEnemy(const float & dt)
{
	//Control enemy
	this->updateEnemyControl(dt);

	//Update all Entity component
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			this->enemy[i]->updateEntity(dt, *this->window);
		}
	}

	//clear enemy when it died
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			if (this->enemy[i]->getDied()) {
				this->player->increaseScore(this->enemy[i]->getPoint());

				delete enemy[i];
				this->enemy.erase(this->enemy.begin() + i);

				// fit size vector
				this->enemy.shrink_to_fit();
			}
		}
	}
}

void Stage::updateEnemyControl(const float & dt)
{
	if (!this->enemy.empty()) {
		srand(int(time(NULL)));
		for (int i = 0; i < this->enemy.size(); i++) {
			//control bot walk to player
			if (std::abs(this->player->getCenter().x - this->enemy[i]->getCenter().x) <= 300.0f && std::abs(this->player->getCenter().x - this->enemy[i]->getCenter().x) >= 50) {
				if (this->player->getCenter().x < this->enemy[i]->getCenter().x) {
					this->enemy[i]->moveEntity(-1.0f, 0.0f, dt);
				}
				if (this->player->getCenter().x > this->enemy[i]->getCenter().x) {
					this->enemy[i]->moveEntity(1.0f, 0.0f, dt);
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

void Stage::renderStage(sf::RenderTarget * target)
{
	if (!target) {
		target = this->window;
	}

	//render background
	for (int i = 0; i < this->background.size(); i++) {
		target->draw(this->background[i]);
	}

	//render enemy
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			this->enemy[i]->renderEntity(*target);
		}
	}
}

#include "Stage.h"

//initialization
void Stage::initVariable()
{
	this->clear = false;
}

Stage::Stage(sf::RenderWindow* window, sf::Font& font, Player *player)
	: window(window), font(font), player(player)
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

	if (!this->item.empty()) {
		for (int i = 0; i < this->item.size(); i++) {
			delete this->item[i];

			this->item.erase(this->item.begin() + i);
		}

		// fit size vector
		this->item.shrink_to_fit();
	}
}

//Accessor
const sf::Vector2i Stage::getStageSize()
{
	if (!this->background.empty()) {
		float size_x = 0;
		float size_y = 0;
		for (int i = 0; i < this->background.size(); i++) {
			size_x += this->background[i].getSize().x;
			size_y += this->background[i].getSize().y;
		}
		return sf::Vector2i(size_x, size_y);
	}
	else {
		return sf::Vector2i(0.0f, 0.0f);
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
void Stage::addBackground(std::string background_id)
{
	//select background
	std::string path = "src/Resource/Background/GameState/background_" + background_id + ".png";
	if (!this->background_texture.loadFromFile(path)) {
		throw("[Stage] >> ..ERROR.. Could't load backgroundTexture");
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

	//update item
	this->updateItem(dt);

	//cleared stage if all enemy down
	if (this->enemy.empty()) {
		this->clear = true;
	}
}

void Stage::updateEnemy(const float & dt)
{
	//Control enemy
	this->updateEnemyControl(dt);

	//Update all enemy component
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			this->enemy[i]->updateEntity(dt, *this->window);
		}
	}

	//clear enemy when it died
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			if (this->enemy[i]->getDied()) {
				//drop item [chance to drop 75%]
				if (rand() % 101 <= 60) {
				
					std::stringstream itemID;
					itemID << rand() % 3 + 1;
					this->item.push_back(new Item(this->enemy[i]->getCenter().x, this->enemy[i]->getPosition().y, itemID.str()));

					// fit size vector
					this->item.shrink_to_fit();
				}

				//increase player score
				this->player->increaseScore(this->enemy[i]->getPoint());
				
				delete this->enemy[i];
				this->enemy.erase(this->enemy.begin() + i);

				// fit size vector
				this->enemy.shrink_to_fit();
			}
		}
	}
}

void Stage::updateEnemyControl(const float & dt)
{
	srand(int(time(NULL)));

	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			//control bot walk to player [player is near]
			if (!this->enemy[i]->getAttacking()) {
				if (std::abs(this->player->getCenter().x - this->enemy[i]->getCenter().x) <= 300.0f  && std::abs(this->player->getCenter().x - this->enemy[i]->getCenter().x) >= 30) {
					if (this->player->getCenter().x < this->enemy[i]->getCenter().x) {
						this->enemy[i]->moveEntity(-1.0f, 0.0f, dt);
					}
					if (this->player->getCenter().x > this->enemy[i]->getCenter().x) {
						this->enemy[i]->moveEntity(1.0f, 0.0f, dt);
					}
				}
				//control bot random walk [player is far]
				else {
					//random direction bot [10% to go left , 10% to go right]
					if (rand() % 101 <= 10) {
						this->enemy[i]->moveEntity(-1.0f, 0.0f, dt);
					}
					else if (rand() % 101 >= 90) {
						this->enemy[i]->moveEntity(1.0f, 0.0f, dt);
					}
				}
			}

			//control bot attack player 
			if (!this->enemy[i]->getHurting()) {
				if (std::abs(this->player->getCenter().x - this->enemy[i]->getCenter().x) <= 100.0f && !this->enemy[i]->getAttacking()) {
					//[enemy chance to attack is 95 % ]
					if (rand() % 101 <= 95) {
						this->enemy[i]->attack(dt, Enemy::ATTACK_ONCE, this->player);
					}
				}
			}
		}
	}
}

void Stage::updateItem(const float & dt)
{
	//Control item
	this->updateItemControl(dt);

	//Update all item component
	if (!this->item.empty()) {
		for (int i = 0; i < this->item.size(); i++) {
			this->item[i]->updateEntity(dt, *this->window);
		}
	}

	//check player get item
	if (!this->item.empty()) {
		for (int i = 0; i < this->item.size(); i++) {
			if (this->item[i]->checkPlayerCollision(this->player)) {
				item[i]->buffPlayer(this->player);

				delete this->item[i];
				this->item.erase(this->item.begin() + i);

				// fit size vector
				this->item.shrink_to_fit();
			}
		}
	}
}

void Stage::updateItemControl(const float & dt)
{
	if (!this->item.empty()) {
		for (int i = 0; i < this->item.size(); i++) {
			//control item fly to player [player is near]
			if (std::abs(this->player->getCenter().x - this->item[i]->getCenter().x) <= 50) {
				if (this->player->getCenter().x < this->item[i]->getCenter().x) {
					this->item[i]->moveEntity(-1.0f, 0.0f, dt);
				}
				if (this->player->getCenter().x > this->item[i]->getCenter().x) {
					this->item[i]->moveEntity(1.0f, 0.0f, dt);
				}

				if (std::abs(this->player->getCenter().y - this->item[i]->getCenter().y) <= 50) {
					if (this->player->getCenter().y < this->item[i]->getCenter().y) {
						this->item[i]->moveEntity(0.0f, -5.0f, dt);
					}
					if (this->player->getCenter().y > this->item[i]->getCenter().y) {
						this->item[i]->moveEntity(0.0f, 5.0f, dt);
					}
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

	//render item
	if (!this->item.empty()) {
		for (int i = 0; i < this->item.size(); i++) {
			this->item[i]->renderEntity(*target);
		}
	}
}

#include "ScoreState.h"

//Initialization
void ScoreState::initKeybinds()
{
	std::ifstream ifs("src/Config/scorestate_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void ScoreState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[Score State] >> ..ERROR.. Could't load font");
	}
}

void ScoreState::initScore()
{
	std::ifstream getdata("src/Config/Data/Score.data");

	while (getdata.is_open()) {

		std::string name = "";
		std::string score = "";

		getdata >> name;
		getdata >> score;

		std::stringstream string_to_int(score);
		int buff_int;
		string_to_int >> buff_int;

		this->getScore.push_back(std::make_pair(name, buff_int));

		if (name == "") {
			getdata.close();
		}
	}

	//sorting score
	this->bubbleSortScore();
}

void ScoreState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("src/Resource/Background/ScoreState/background.png")) {
		throw("[Score State] >> ..ERROR.. Could't load backgroundTexture");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void ScoreState::initContainer()
{
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x / 8.0f * 4.0f),
			static_cast<float>(this->window->getSize().y - (this->window->getSize().y / 8.0f) * 3.9f)
		)
	);

	this->container.setFillColor(sf::Color(20, 20, 20, 180));

	this->container.setPosition(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x / 2.0f - this->container.getSize().x / 2.0f),
			static_cast<float>(this->window->getSize().y / 8.0f * 1.75f)
		)
	);
}

void ScoreState::initDescriptText()
{
	this->descriptText.setFont(this->font);
	this->descriptText.setCharacterSize(50);
	this->descriptText.setOutlineThickness(5.0f);
	this->descriptText.setOutlineColor(sf::Color::Red);

	this->descriptText.setString("Monster Ranking");

	this->descriptText.setPosition(sf::Vector2f(
		this->window->getSize().x / 2.0f - this->descriptText.getGlobalBounds().width / 2.0f,
		this->window->getSize().y / 16.0f * 1.5f
	));
}

void ScoreState::initRankText()
{
	//set loop rap
	size_t loop_size = this->getScore.size() - 1;
	if (loop_size > 5) {
		loop_size = 5;
	}

	//set name text
	std::string name = "";
	std::string name_list = "- NAME -\n\n";
	for (int i = 0; i < loop_size; i++) {
		name = this->getScore[i].first;
		name_list +=  name + "\n";
	}
	this->rankNameText.setString(name_list);
	
	//set score text
	int score;
	std::string score_list = "- SCORE -\n\n";
	for (int i = 0; i < loop_size; i++) {
		score = this->getScore[i].second;
		std::stringstream int_to_string;
		int_to_string << score;

		score_list += int_to_string.str() + "\n";
	}
	this->rankScoreText.setString(score_list);
	
	//set name,score text display
	this->rankNameText.setCharacterSize(40);
	this->rankScoreText.setCharacterSize(40);

	this->rankNameText.setFont(this->font);
	this->rankScoreText.setFont(this->font);

	this->rankNameText.setLineSpacing(1.1f);
	this->rankScoreText.setLineSpacing(1.1f);

	this->rankNameText.setPosition(
		this->window->getSize().x/16.0f * 5.0f,
		this->window->getSize().y / 16.0f * 4.0f
	);
	this->rankScoreText.setPosition(
		this->window->getSize().x / 16.0f * 9.0f, 
		this->window->getSize().y / 16.0f * 4.0f
	);
}

void ScoreState::initButtons()
{
	//create buttons
	float button_width = 150.0f;
	float button_height = 0.0f;

	this->buttons["Back"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2),
		(this->window->getSize().y / 8) * 6.50f,
		button_width, button_height,
		this->font, "BACK", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255)
	);
}

//Function
void ScoreState::bubbleSortScore()
{
	int i, j;
	for (i = 0; i < this->getScore.size() - 1; i++) {
		for (j = 0; j < this->getScore.size() - 2; j++) {
			if (this->getScore[j].second < this->getScore[j+1].second) {
				swap(&this->getScore[j], &this->getScore[j+1]);
			}
		}
	}
}

void ScoreState::swap(std::pair<std::string ,int>* pair_x, std::pair<std::string, int>* pair_y)
{
	std::pair<std::string, int> temp = *pair_x;
	*pair_x = *pair_y;
	*pair_y = temp;
}


//Constructor , Destructor
ScoreState::ScoreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	std::cout << "[Score State] >> On" << std::endl;
	this->initKeybinds();
	this->initFonts();

	this->initScore();

	this->initBackground();
	this->initContainer();
	this->initDescriptText();
	this->initRankText();

	this->initButtons();
}

ScoreState::~ScoreState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
}

//Function
void ScoreState::updateState(const float & dt)
{
	this->updateKeyTime(dt);

	this->updateInput(dt);
	this->updateMousePosition();

	this->updateButton();
}

void ScoreState::updateInput(const float & dt)
{
}

void ScoreState::updateButton()
{
	//Update all the buttons in this state
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		it->second->updateButton(this->mousePosView);
	}

	//Exit this state
	if (this->buttons["Back"]->isPressed() && this->getKeyTime()) {
		this->endState();
	}
}

void ScoreState::renderState(sf::RenderTarget* target)
{
	if (target == NULL) {
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->container);
	target->draw(this->descriptText);
	target->draw(this->rankNameText);
	target->draw(this->rankScoreText);

	this->renderButton(*target);
}

void ScoreState::renderButton(sf::RenderTarget & target)
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		it->second->renderButton(target);
	}
}

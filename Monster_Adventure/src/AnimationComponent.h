//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		-animations								//
//////////////////////////////////////////////////

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <map>

class AnimationComponent
{
private:
	class Animation {
	public:
		//Variable
		sf::Sprite& sprite;
		sf::Texture& textureSheet;

		float animationTimer;
		float timer;
		
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		//Constructor , Destructor
		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
			float animation_timer, 
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height) 
			: sprite(sprite), textureSheet(texture_sheet) ,animationTimer(animation_timer) ,width(width) ,height(height)
		{
			this->timer = 0.0f;
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height); 
		
			this->sprite.setTexture(this->textureSheet);  // <<-- set Texture of sprite here
			this->sprite.setScale(3, 3);
			this->sprite.setTextureRect(this->startRect);
		}
		~Animation() {
		}

		//Function
		void play(const float &dt)
		{
			//Update timer
			this->timer += 500.0f * dt;
			
			if (this->timer >= this->animationTimer) {
				//Reset timer
				this->timer = 0.0f;
				
				if (this->currentRect != this->endRect) {				//Animated
					this->currentRect.left += this->width;
				}
				else {													//Reset
					this->currentRect = this->startRect;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void reset() {
			this->timer = 0.0f;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;

public:
	//Constructor , Destructor
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Function
	void addAnimation(
		const std::string key, 
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	void play(const std::string key, const float &dt);
};


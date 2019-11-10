#include "AnimationComponent.h"

//Constructor , Destructor
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto it = this->animations.begin(); it != this->animations.end(); it++) {
		delete it->second;
	}
}

//Function
void AnimationComponent::addAnimation(
	const std::string key, 
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{
	//If this is a priority animation, set it
	if (priority) {
		this->priorityAnimation = this->animations[key];
	}

	//If there is a priority animation
	if (this->priorityAnimation) {			
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == NULL) {
					this->lastAnimation = this->animations[key];
				}
				else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->play(dt)) {
				this->priorityAnimation = NULL;
			}
		}
	}
	//Play animation of no other priority animation is set
	else {									
		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation == NULL) {
				this->lastAnimation = this->animations[key];
			}
			else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority)
{
	//If this is a priority animation, set it
	if (priority) {
		this->priorityAnimation = this->animations[key];
	}

	//If there is a priority animation
	if (this->priorityAnimation) {			
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == NULL) {
					this->lastAnimation = this->animations[key];
				}
				else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->play(dt, abs(modifier / modifier_max))) {
				this->priorityAnimation = NULL;
			}
		}
	}
	//Play animation of no other priority animation is set
	else {									
		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation == NULL) {
				this->lastAnimation = this->animations[key];
			}
			else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}

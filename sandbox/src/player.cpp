//
//  player.cpp
//  sandbox
//
//  Created by Johanna Sacher on 05.11.26.
//
#include "player.h"

void Player::Setup(ofImage * _icon, int playerLives, float playerSpeed)
{
	speed = playerSpeed;
	lives = playerLives;
	Icon = _icon;
	
	width = Icon -> getWidth() / 2;
	height = Icon -> getHeight() / 2;
	
	Icon -> resize(width, height);
	
	Position.x = ofGetWidth()/2;
	Position.y = ofGetHeight()/2;
}

void Player::Update()
{
	CalculateMovement();
}

void Player::Draw()
{
	Icon -> draw(Position.x - width/2, Position.y - height/2);
}

void Player::Shoot()
{
	
}

bool Player::CanShoot()
{
	return false;
}

void Player::CalculateMovement()
{
	bool isMoving = false;
	
	if(LeftPressed && Position.x > 0 + width/2)
	{
		Position.x -= speed;
		isMoving = true;
	}
	
	if(RightPressed && Position.x < ofGetWidth() - width/2)
	{
		Position.x += speed;
		isMoving = true;
	}
	
	if(UpPressed && Position.y > 0 + height/2)
	{
		Position.y -= speed;
		isMoving = true;
	}
	
	if(DownPressed && Position.y < ofGetHeight() - height/2)
	{
		Position.y += speed;
		isMoving = true;
	}
	
	
	/*if(SpacePressed)
	{
		Position.y -= jumpHeight;
	}*/
}

void Player::PlaySequence(bool isMoving)
{
	// Wenn wir uns momentan nicht bewegen: Setze das Character-Icon wieder auf den Default
	
	// Wenn wir uns bewegen, dann spiele die Sequenz weiter ab
}

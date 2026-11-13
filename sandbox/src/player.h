//
//  player.h
//  sandbox
//
//  Created by Johanna Sacher on 05.11.26.
//
#include "ofMain.h"

class Player
{
public:
	ofPoint Position;
	float width;
	float height;
	float speed;
	int lives;
	
	bool LeftPressed;
	bool RightPressed;
	bool UpPressed;
	bool DownPressed;
	bool SpacePressed;
	
	void Setup(ofImage * _icon, int playerLives, float playerSpeed);
	void Update();
	void Draw();
	void Shoot();
	
	void CalculateMovement();
	void PlaySequence(bool isMoving);
	
	bool CanShoot();
	
	ofImage * Icon;
};

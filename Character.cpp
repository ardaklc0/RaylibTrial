#include "Character.h"
#include <iostream>
using namespace std;

void Character::Jump(Camera camera, float* initialYPosition, float* jumpHeight, float* jumpSpeed, bool* jumping)
{
 	if (IsKeyDown(KEY_SPACE) && !(*jumping))
	{
		*jumping = true;
	}

	if (jumping)
	{
		camera.position.y += *jumpSpeed;
		if (camera.position.y >= *initialYPosition + *jumpHeight)
		{
			*jumpSpeed -= 0.01f;
			cout << jumpSpeed << endl;
		}
		if (*jumpSpeed < 0 && camera.position.y <= *initialYPosition)
		{
			*jumping = false;
			camera.position.y = *initialYPosition; // Reset the camera's Y position
			*jumpSpeed = 0.2f; // Reset jump speed
		}
	}
}	
#include "movement.h"

void Pointmovement::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

void Pointmovement::move(const char colliders[],const int length) {
	bool IsGrounded = IsCollidingInGround(colliders,length);
	if (Grounded == true)
	{
		iterations_in_air = 0;
	}

	if (!IsGrounded)
	{
		Grounded = false;
	}	
	else
	{
		Grounded = true;
	}
		

	int  newX=x;
	int newY=y;
	if(keep_momentum_always)
	keep_momentum = true;

	if (IsGrounded||overwrite_gravity)
	{
		
    keep_momentum = false;
    newX= x + dir.x;
	 newY= y + dir.y;
	}
	else
	{
		iterations_in_air++;
		int tempx = dir.x;
		dir = { 0,1 };
		newY = y + 1;
		if (keep_momentum)
		{
          newX = x +tempx;
		  dir.x=tempx;
		}
		
		
	}                                       // Better use a function in Board to check if the new position is valid
	                                        // + Better use a constant for the wall character
	
	
		if (IsColliding(colliders, length, newX, newY)) {
			dir = { 0, 0 };
		}
		else {
	     
			if (!is_dir_0()) {
				
				prev_char = pBoard->getOgChar(x, y);
				pBoard->draw_InPosition(x, y, prev_char);

			}
                x = newX;
		    	y = newY;
			
		}
		overwrite_gravity = false;
		
}
bool Pointmovement::IsColliding(const char colliders[], const int length ,int Xpos, int Ypos)
{
	char toCheck = pBoard->getOgChar(Xpos, Ypos);
	
	for (int i = 0; i < length; i++)
	{
		
		if (toCheck == colliders[i])
		return true;
	}
	return false;
}
bool Pointmovement::IsCollidingInNextDir(const char colliders[], const int length) 
{
	return IsColliding(colliders, length, x + dir.x, y + dir.y);
}

bool Pointmovement::is_dir_0()
{
	if (dir.x == 0 && dir.y == 0)
		return true;
	return false;
}
void Pointmovement::SetPos(int posx, int posy)
{
	x = posx;
	y = posy;

}
bool  Pointmovement::IsCollidingInGround(const char colliders[], int length)
{
	return IsColliding(colliders, length, x, y + 1);
}


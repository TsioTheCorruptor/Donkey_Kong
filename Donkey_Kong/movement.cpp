#include "movement.h"

void Pointmovement::keyPressed(char key) {//set movement dir according to key pressed
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
	if(keep_momentum_always)//made for moving while in air,and for falling down diagonally
	keep_momentum = true;

	if (IsGrounded||overwrite_gravity)//if in ground or gravity is ignored,move to next dir
	{
		
    keep_momentum = false;
    newX= x + dir.x;
	 newY= y + dir.y;
	}
	else
	{//fall down,if momentum is kept,also add the x dir 
		iterations_in_air++;
		int tempx = dir.x;
		dir = { 0,1 };
		newY = y + 1;
		if (keep_momentum)
		{
          newX = x +tempx;
		  dir.x=tempx;
		}
		
		
	}                                       
	
	//if colliding in new dir,stop movement
		if (IsColliding(colliders, length, newX, newY)) {
			dir = { 0, 0 };
		}
		else {
	     
			if (!is_dir_0()) {//draw back previous chars which we went trough in the game
				
				prev_char = pBoard->getOgChar(x, y);
				pBoard->draw_InPosition(x, y, prev_char);

			}//change position of point according to the code above
                x = newX;
		    	y = newY;
			
		}
		overwrite_gravity = false;//stop ignoring gravity after each call of the function by default
		
}
bool Pointmovement::IsColliding(const char colliders[], const int length ,int Xpos, int Ypos)
{//check collision in specific board location
	char toCheck = pBoard->getOgChar(Xpos, Ypos);
	
	for (int i = 0; i < length; i++)
	{
		
		if (toCheck == colliders[i])
		return true;
	}
	return false;
}
bool Pointmovement::IsCollidingInNextDir(const char colliders[], const int length) 
{//check collision in next dir
	return IsColliding(colliders, length, x + dir.x, y + dir.y);
}

bool Pointmovement::is_dir_0()
{
	if (dir.x == 0 && dir.y == 0)
		return true;
	return false;
}
void Pointmovement::SetPos(int posx, int posy)
{//set pos of point
	x = posx;
	y = posy;

}
bool  Pointmovement::IsCollidingInGround(const char colliders[], int length)
{//check if point is grounded
	return IsColliding(colliders, length, x, y + 1);
}


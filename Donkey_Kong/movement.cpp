#include "movement.h"

void Pointmovement::move(const char colliders[],const int length) {

	bool IsGrounded = IsCollidingInGround(colliders,length);

	if (Grounded == true){
		iterations_in_air = 0;
	}
	if (!IsGrounded){
		Grounded = false;
	}	
	else {
		Grounded = true;
	}
		
	int  newX=x;
	int newY=y;

	//if in ground or gravity is ignored,move to next dir
	if (IsGrounded||overwrite_gravity){
		newX= x + dir.x;
		newY= y + dir.y;
	}
	//fall down,if momentum is kept,also add the x dir 
	else {
		iterations_in_air++;
		dir = { 0,1 };
		newY = y + 1;
	}                                       
	
	//if colliding in new dir,stop movement
	if (IsColliding(colliders, length, newX, newY)) {
		dir = { 0, 0 };
	}
	else {
		if (!is_dir_0()) {//draw back previous chars which we went trough in the game
			prev_char = pBoard->getOgChar(x, y);
			pBoard->draw_InPosition(x, y, prev_char);
		}
		//change position of point according to the code above
        x = newX;
		y = newY;
	}
	overwrite_gravity = false;//stop ignoring gravity after each call of the function by default	
}
//check collision in specific board location
bool Pointmovement::IsColliding(const char colliders[], const int length ,int Xpos, int Ypos) const{

	char toCheck = pBoard->getOgChar(Xpos, Ypos);
	//if (x + dir.x >= 80 || x + dir.x <0 || y + dir.y >= 25 || y + dir.y < 0)
		//return true;
	for (int i = 0; i < length; i++){
		if (toCheck == colliders[i])
		return true;
	}
	return false;
}
//check collision in next dir
bool Pointmovement::IsCollidingInNextDir(const char colliders[], const int length) const{
	return IsColliding(colliders, length, x + dir.x, y + dir.y);
}
bool Pointmovement::is_dir_0() const{
	if (dir.x == 0 && dir.y == 0)
		return true;
	return false;
}
//set pos of point
void Pointmovement::SetPos(int posx, int posy){
	x = posx;
	y = posy;
}
//check if point is grounded
bool Pointmovement::IsCollidingInGround(const char colliders[], int length) const{
	return IsColliding(colliders, length, x, y + 1);
}
//the overwrite_grav decides if the set dir will ignore gravity or not
void Pointmovement::set_dir(int dirx, int diry, bool overwrite_grav){
	dir.x = dirx;
	dir.y = diry;
	overwrite_gravity = overwrite_grav;
}

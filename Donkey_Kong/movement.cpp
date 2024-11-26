#include "movement.h"

void Pointmovement::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

void Pointmovement::move(const char colliders[],int length) {

	int newX = x + dir.x;
	int newY = y + dir.y;
	// Better use a function in Board to check if the new position is valid
	// + Better use a constant for the wall character
	if (IsColliding(colliders,length,newX,newY)) {
		dir = { 0, 0 };
	}
	else {
		if (dir.x!=0||dir.y!=0){
        prevx = x;
		prevy = y;
		prev_char = pBoard->getChar(x, y);
		draw_InPosition(x, y, prev_char);

		}
		
		x = newX;
		y = newY;
	}
}
bool Pointmovement::IsColliding(const char colliders[], int length ,int Xpos, int Ypos)
{
	for (int i = 0; i < length; i++)
	{
		
		if (pBoard->getChar(Xpos, Ypos) == colliders[i])
		return true;
	}
	return false;
}


#pragma once
#include <iostream>
class Mario {


 char mario_char = '@';
public:
	static constexpr char collisions[4] = { 'Q','<','=','>'};
	int col_length = 4;
	 char  get_mario_char()
	{
		return mario_char;
	}
	void  set_mario_char(const char chr)
	{
		mario_char=chr;
	}
};
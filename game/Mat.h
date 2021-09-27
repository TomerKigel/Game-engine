#pragma once

enum types {Obj = 100, mveble, sttc , mnstr, ply,itm,skill = 106};
enum directions {top = 1,bottom,left,right};

enum collision {
	In_air,
	OnGround,
	LeftToWall,
	RightToWall
};

enum Looking {
	lookingleft,
	lookingright
};

enum attack
{
	non_attack,
	init_attack,
	second_attack,
	third_attack,
	dash_attack,
};

enum jump
{
	non_jump,
	jumping,
	double_jumping,
	side_hold,
	bomb_dropping,
	super_bomb_dropping
};

enum moving
{
	non_moving,
	moving_left,
	moving_right,
	dashing_left,
	dashing_right
};

enum shield
{
	non_shield,
	left_shield,
	right_shield
};

enum special
{
	non_special,
	empowerd
};

enum temper
{
	neutral,
	aggresive,
	calm,
	enraged
};

typedef struct inputstatus {
	bool LeftArrowKey = false;
	bool RightArrowKey = false;
	bool UpArrowKey = false;
	bool DownArrowKey = false;
	bool LShiftKey = false;
	bool Akey = false;
	bool FKey = false;
	bool PKey = false;
};

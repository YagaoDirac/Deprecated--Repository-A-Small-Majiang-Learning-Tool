#pragma once
#include<algorithm>
#include"Define.h"
class GlobalTool
{
/*
public:
	GlobalTool();
	~GlobalTool();
*/

public:
	static ErrorType _checkCardNumber(int);
	static int clamp(int, int, int);
	static ErrorType text_2_cards(char* _input, size_t _length, int * result);
	

};


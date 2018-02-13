#pragma once
//#include<vector>
#include"Define.h"
#include"Droped Cards Record.h"
#include"Global Object.h"

class GlobalObject;

class HandCard
{
public:
	HandCard(GlobalObject* 全局变量);
	~HandCard();

	//初始化
public:
	ErrorType init(int 初始手牌[9]);
	ErrorType init(char* str, int safeLength);

	//主要功能
public:
	WinningState HasWon();
	ErrorType tryDropCard(int);
	ErrorType GetCard(int);
private:
	int _hand_cards[9];

public://可能需要改成私有
	GlobalObject* _global;
};
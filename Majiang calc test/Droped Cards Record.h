#pragma once
//#include"define.h"
#include"Global Tool.h"
#include"Global Object.h"

class GlobalObject;

class DropedCardRecord
{
public:
	DropedCardRecord(GlobalObject* 全局变量);
	~DropedCardRecord();

//手动初始化
public:
	ErrorType init();

public:
	ErrorType getCount(int 牌番号, int * result);
	ErrorType dropThisCard(int 牌番号);
	ErrorType checkTotalCounts(int 输入[9]);

public:
	int 初始弃牌[9];

private:
	int _droped_cards[9];

public://可能需要改成私有
	GlobalObject* _global;
};


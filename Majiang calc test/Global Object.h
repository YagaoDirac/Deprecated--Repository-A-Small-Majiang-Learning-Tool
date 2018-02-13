#pragma once
#include"Droped Cards Record.h"
#include"Hand Card.h"

class HandCard;
class DropedCardRecord;

class GlobalObject
{
public:

	HandCard* getHandCard();
	DropedCardRecord* getDropedCardRecord();

	//Á½¸öÖ¸Õë
public:
	HandCard* _HandCard;
	DropedCardRecord* _DropedCardRecord;

};


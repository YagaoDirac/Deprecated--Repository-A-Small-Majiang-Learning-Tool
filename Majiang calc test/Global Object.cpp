#include "Global Object.h"

HandCard * GlobalObject::getHandCard()
{
	return _HandCard;
}

DropedCardRecord * GlobalObject::getDropedCardRecord()
{
	return _DropedCardRecord;
}

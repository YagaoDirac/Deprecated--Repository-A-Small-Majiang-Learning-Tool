#include"Droped Cards Record.h"


DropedCardRecord::DropedCardRecord(GlobalObject * 全局变量)
{
	全局变量->_DropedCardRecord = this;
	_global = 全局变量;

	for (size_t i = 0; i < 9; i++)
		_droped_cards[i] = 0;
}

DropedCardRecord::~DropedCardRecord()
{
}

ErrorType DropedCardRecord::init()
{
	bool 是否对输入的初始弃牌做了修改(false);

//超出允许范围的数字要修改
	for (size_t i = 0; i < 9; i++)
	{
		if (初始弃牌[i]<=0|| 初始弃牌[i]>=5)
		{
			是否对输入的初始弃牌做了修改 = true;
		}
		初始弃牌[i] = GlobalTool::clamp(初始弃牌[i], 1, 4);//如果你的麻将的规则有某种牌的数量不为4，那么修改这个地方
	}
//复制一遍
	for (size_t i = 0; i < 9; i++)
		_droped_cards[i] = 初始弃牌[i];

	if (是否对输入的初始弃牌做了修改)
		return ErrorType::Almost_OK;
	else
		return ErrorType::OK;
}

ErrorType DropedCardRecord::getCount(int 牌番号,int* result)
{
	//检查牌番号
	ErrorType temp = GlobalTool::_checkCardNumber(牌番号);
	if (temp != ErrorType::OK)
		return temp;

	if (nullptr == result)
		return ErrorType::指针为空;

	*result = _droped_cards[牌番号 - 1];
	return ErrorType::OK;
}

ErrorType DropedCardRecord::dropThisCard(int 牌番号)
{
	if (_droped_cards[牌番号 - 1] >= 4)
		return ErrorType::牌超过4张;

	_droped_cards[牌番号 - 1] += 1;
	return ErrorType::OK;
}

ErrorType DropedCardRecord::checkTotalCounts(int 输入[9])
{
	for (size_t i = 0; i < 9; i++)
	{
		if (输入[i] + _droped_cards[i] >= 5)
			return ErrorType::和弃牌堆的牌冲突;
	}

	return ErrorType::OK;
}

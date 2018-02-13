#include "Hand Card.h"



HandCard::HandCard(GlobalObject * 全局变量)
{
	全局变量->_HandCard = this;
	_global = 全局变量;

	for (size_t i = 0; i < 9; i++)
		_hand_cards[i] = 0;
}

HandCard::~HandCard()
{
}

ErrorType HandCard::init(int 初始手牌[9])
{
	bool 对输入值做了修改(false);
	
	for (size_t i = 0; i < 9; i++)
	{
		if (初始手牌[i] < 0 || 初始手牌[i] >= 5)
			对输入值做了修改 = true;
		初始手牌[i] = GlobalTool::clamp(初始手牌[i], 0, 4);
	}

	//检查和棋牌堆的已有的牌是否冲突
	ErrorType temp = _global->getDropedCardRecord()->checkTotalCounts(初始手牌);
	if (temp != ErrorType::OK)
		return temp;

	for (size_t i = 0; i < 9; i++)
	{
		_hand_cards[i] = 初始手牌[i];
	}


	if (对输入值做了修改)
		return ErrorType::Almost_OK;
	else
		return ErrorType::OK;
}

ErrorType HandCard::init(char * str, int safeLength)
{
	if (safeLength <= 0)
		return ErrorType::Bad_Param;
	char* buf = new char[safeLength];
	memcpy(buf, str, safeLength);
	buf[safeLength - 1] = 0;

	GlobalTool::text_2_cards(buf, safeLength, _hand_cards);
	delete[]buf;
	
	//处理特别大的数据
	bool 数据是正常的(true);
	for (size_t i = 0; i < 9; i++)
	{
		_hand_cards[i] = GlobalTool::clamp(_hand_cards[i], 0, 4);
		数据是正常的 = false;
	}
	
	if (数据是正常的)
		return ErrorType::OK;
	else
		return ErrorType::Almost_OK;
}



WinningState HandCard::HasWon()
{
	int 总牌数(0);
	for (size_t i = 0; i < 9; i++)
		总牌数 += _hand_cards[i];

	if (0 == 总牌数)
		return WinningState::打掉了所有的牌;

	//3n+1张是肯定没有说法的
	if (总牌数 % 3 == 1)
		return WinningState::Not_yet;

	//3n的时候就都是3个一组
	if (总牌数 % 3 == 0)
	{
		int 缓存的手牌[9];
		for (size_t i = 0; i < 9; i++)
		{
			缓存的手牌[i] = _hand_cards[i];
		}
		

		//下面才是正常干活

		//这儿的思路是有板子的话优先组合，然后直接去掉，继续尝试组合其他的牌。
		//一个特殊情况是，如果有111222333，那么这个牌按板子和顺子组合，对是否赢是没有影响的，对这个函数所需要得到的结果也就没有影响。
		for (size_t i = 0; i < 9; i++)
		{
			if (0 == 总牌数)
				return WinningState::Win;
			//有板子的话直接去掉
			if (缓存的手牌[i] >= 3)
			{
				缓存的手牌[i] -= 3;
				总牌数 -= 3;
			}
			//没有这个牌就直接检查后面的了
			if (0 == 缓存的手牌[i])
				continue;
			//没有板子的时候检查2个事情，能组成顺子不，和i是否大于7
			if (1 == 缓存的手牌[i] ||2 == 缓存的手牌[i])
			{
				int 该牌的张数(缓存的手牌[i]);
				if (i > 7)
					return WinningState::Not_yet;
				if (缓存的手牌[i + 1]<该牌的张数 || 缓存的手牌[i + 2]<该牌的张数)
					return WinningState::Not_yet;

				缓存的手牌[i] -= 该牌的张数;
				缓存的手牌[i + 1] -= 该牌的张数;
				缓存的手牌[i + 2] -= 该牌的张数;
				总牌数 -= 3;
			}
		}//for i 0 9
	}//if (总牌数 % 3 == 0)



	//3n+2的情况要先判断将
	if (总牌数 % 3 == 2)
	{
		int 缓存的手牌[9];
		for (size_t i = 0; i < 9; i++)
		{
			缓存的手牌[i] = _hand_cards[i];
		}
		int temp总牌数(总牌数);
		//下面才是正常干活

		//思路是，先找将，找到了以后，扔掉，然后按上面的 (总牌数 % 3 == 0) 情况来
		for (size_t 将的番号 = 0; 将的番号 < 9; 将的番号++)
		{
			if (_hand_cards[将的番号] >= 2)
			{
				//先拿掉将
				_hand_cards[将的番号] -= 2;
				temp总牌数 -= 2;

				//

				for (size_t i = 0; i < 9; i++)
				{
					if (0 == temp总牌数)
						return WinningState::Win;
					//有板子的话直接去掉
					if (缓存的手牌[i] >= 3)
					{
						缓存的手牌[i] -= 3;
						temp总牌数 -= 3;
					}
					//没有这个牌就直接检查后面的了
					if (0 == 缓存的手牌[i])
						continue;
					//没有板子的时候检查2个事情，能组成顺子不，和i是否大于7
					if (1 == 缓存的手牌[i] || 2 == 缓存的手牌[i])
					{
						int 该牌的张数(缓存的手牌[i]);
						if (i > 7)
							return WinningState::Not_yet;
						if (缓存的手牌[i + 1]<该牌的张数 || 缓存的手牌[i + 2]<该牌的张数)
							return WinningState::Not_yet;

						缓存的手牌[i] -= 该牌的张数;
						缓存的手牌[i + 1] -= 该牌的张数;
						缓存的手牌[i + 2] -= 该牌的张数;
						temp总牌数 -= 3;
					}
				}//for i 0 9
			}
		}
	}//if (总牌数 % 3 == 2)


	//如果一个情况都没得到，就是弄错了
	return WinningState::Bad_Code;
}

ErrorType HandCard::tryDropCard(int 牌番号)
{
	if (_hand_cards[牌番号 - 1] <= 0)
		return ErrorType::牌不足;
	
	ErrorType temp = _global->getDropedCardRecord()->dropThisCard(牌番号);
	if (ErrorType::OK != temp)
		return temp;
	else
	{
		_hand_cards[牌番号 - 1] -= 1;
		return ErrorType::OK;
	}
}

ErrorType HandCard::GetCard(int 牌番号)
{
	//看是否超过4张
	if (牌番号 <= 0 || 牌番号 >= 10)
		return ErrorType::牌番号错误;

	//跟弃牌堆检查总牌数
	int 弃牌堆中的该牌总数;
	_global->getDropedCardRecord()->getCount(牌番号, &弃牌堆中的该牌总数);
	if (弃牌堆中的该牌总数 + HandCard::_hand_cards[牌番号 - 1] >= 4)
		return ErrorType::和弃牌堆的牌冲突;
	//包含一个特殊情况，就是自己手上有4张牌


	//正常摸牌
	_hand_cards[牌番号 - 1] += 1;
	return ErrorType::OK;
}

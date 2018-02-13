#pragma once

enum class ErrorType
{
	OK,
	Almost_OK,
	Error,
	Bad_Param,
	还没写呢,
	指针为空,
	牌番号错误,
	牌不足,
	牌超过4张,
	和弃牌堆的牌冲突
	
};

enum class WinningState
{
	Win,
	Not_yet,
	打掉了所有的牌,
	Bad_Code
};
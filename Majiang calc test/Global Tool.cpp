#include "Global Tool.h"

ErrorType GlobalTool::_checkCardNumber(int ≈∆∑¨∫≈)
{
	if (≈∆∑¨∫≈ <= 0 || ≈∆∑¨∫≈ >= 10)
		return ErrorType::≈∆∑¨∫≈¥ÌŒÛ;
	else return ErrorType::OK;
}

int GlobalTool::clamp(int _input, int _min, int _max)
{
	return std::max(std::min(_input, _max), _min);
}

ErrorType GlobalTool::text_2_cards(char* _input, size_t _length, int * result)
{
	int temp ÷≈∆[9]{0,0,0,0,0,0,0,0,0};
	char str[2];
	memset(str, 0, 2);

	for (size_t i = 0; i < _length-1; i++)
	{
		char temp_char = _input[i];
		if (temp_char<='0' || temp_char>'9')
			return ErrorType::Error;
		else
		{
			str[0] = temp_char;
			++temp ÷≈∆[strtol(str, nullptr, 0)-1];
		}
	}


	for (size_t i = 0; i < 9; i++)
		result[i] = temp ÷≈∆[i];
	return ErrorType::OK;
}


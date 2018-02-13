//vs2017的话可以在头文件写全局变量，但是这儿不行，所以就写main里了
#include"Hand Card.h"
#include"Droped Cards Record.h"
#include"Global Object.h"



int main()
{
	GlobalObject 全局;
	DropedCardRecord 弃牌堆(&全局);
	HandCard 手牌(&全局);

	手牌.init("1111",5);
	WinningState fdjksl = 手牌.HasWon();
	int fdjklfdsjl(0);
}

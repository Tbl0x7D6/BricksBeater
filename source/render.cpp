#include "render.h"

//extern int frameRate;
// 渲染
void render(rectSet* p_rctSet, BALL* p_ball, bool isCollision)
{
	setfillcolor(WHITE);

	// 矩形绘制
	p_rctSet -> first();
	while(p_rctSet -> next())
	{
		rectNode* node = p_rctSet -> present();

		solidrectangle(node -> rct.left, node -> rct.top, node -> rct.right, node -> rct.bottom);

		if (node -> HP >= 0)  // 边框不显示HP
		{
			TCHAR s_HP[10];
			_itoa(node -> HP, (char*)s_HP, 10);

			drawtext(s_HP, &(node -> rct), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else node -> HP = -1;
	}
	
	if (isCollision) setfillcolor(GREEN);
    else setfillcolor(YELLOW);
	
	solidcircle((int)p_ball -> x, (int)p_ball -> y, (int)p_ball -> radius);
	
	/*
	RECT r = {0, 0, 40, 40};
	TCHAR str[10];
	_itoa(frameRate, (char*)str, 10);
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	*/
}
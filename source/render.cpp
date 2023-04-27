#include "render.h"

//extern int frameRate;
// 渲染
void render(polygonSet* p_polygonSet, BALL* p_ball, bool isCollision)
{
	setfillcolor(WHITE);

	// 多边形绘制
	p_polygonSet -> first();
	while(p_polygonSet -> next())
	{
		polygonNode* node = p_polygonSet -> present();

		solidpolygon(node -> pt, node -> edgeNum);

		TCHAR s_HP[10];
		_itoa(node -> HP, (char*)s_HP, 10);
		RECT rct = {node -> xc - 100, node -> yc + 100, node -> xc + 100, node -> yc - 100};

		drawtext(s_HP, &rct, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
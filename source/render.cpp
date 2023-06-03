#include "render.h"

// 渲染
void render(polygonSet* p_polygonSet, BALL* p_ballSet, int numOfBall)
{
	// 多边形绘制
	p_polygonSet -> first();
	while(p_polygonSet -> next())
	{
		polygonNode* node = p_polygonSet -> present();

		setfillcolor(node -> color);
		solidpolygon(node -> pt, node -> edgeNum);

		// 多边形剩余HP显示
		TCHAR s_HP[10];
		_itoa(node -> HP, (char*)s_HP, 10);
		RECT rct = {node -> xc - 100, node -> yc + 100, node -> xc + 100, node -> yc - 100};

		drawtext(s_HP, &rct, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
	// 球绘制
	setfillcolor(LIGHTCYAN);
	for (int i = 0; i < numOfBall; i++)
		if (!(p_ballSet + i) -> info.removeFlag)
			solidcircle((p_ballSet + i) -> x,
						(p_ballSet + i) -> y,
						(p_ballSet + i) -> radius);
	
	/*
	RECT r = {0, 0, 40, 40};
	TCHAR str[10];
	_itoa(FRAMERATE, (char*)str, 10);
    drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	*/
}
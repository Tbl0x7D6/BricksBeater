#include "mapgenerator.h"

// 生成一个多边形
polygonNode polygonGenerator(int xc, int yc, int edgeNum, int radius, int HP, double theta)
{
	if (theta == 0) theta = PI / 180 * (rand() % 360);

	polygonNode node;
	node.edgeNum = edgeNum;
	node.HP = HP;
	node.xc = xc, node.yc = yc;
	node.radius = radius;

	for (int i = 0; i < edgeNum; i++)
	{
		node.pt[i].x = xc + radius * cos(theta);
		node.pt[i].y = yc + radius * sin(theta);

		theta += 2 * PI / edgeNum;
	}
	return node;
}
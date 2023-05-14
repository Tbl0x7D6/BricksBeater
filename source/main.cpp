#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include "geoelement.h"
#include "render.h"
#include "balloperate.h"

// 生成一个多边形
polygonNode polygonGenerator(int xc, int yc, int edgeNum, int radius, int HP, double theta = 0)
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

int main()
{
	int frameRate = 120;   // 帧率
	int numOfBall = 400;   // 球数目

	scanf("%d", &frameRate);
	
	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();

	double theta;
	BALL *ball = new BALL[numOfBall];
	
	for (int i = 0; i < numOfBall; i++)
	{
		theta = PI / 180 * (rand() % 360);
		ball[i] = BALL(50, 50, theta, RADIUS, VELOCITY);
	}

	//ball.energy = (ball.vx * ball.vx + ball.vy * ball.vy) / 2 - GRAVITY * ball.y;

	polygonSet polygon;

	polygon.insert(polygonGenerator(160, 360, 4, 60, 114514));
	polygon.insert(polygonGenerator(320, 170, 3, 80, 114514));
	polygon.insert(polygonGenerator(480, 370, 5, 60, 114514));

	while (true)
	{
		int startTime = clock();
		
		cleardevice();

		for (int i = 0; i < numOfBall; i++)
			ballOperate(ball + i, &polygon);

		render(&polygon, ball, numOfBall);
		
		int endTime = clock();
		int frameTime = 1000000 / frameRate;
		int deltaTime = 1000000 * (endTime - startTime) / CLOCKS_PER_SEC;
		if (deltaTime < frameTime) usleep(frameTime - deltaTime);
		
		FlushBatchDraw();
	}

	delete ball;
	
	EndBatchDraw();
	closegraph();

	return 0;
}

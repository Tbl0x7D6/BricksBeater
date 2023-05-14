#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include "geoelement.h"
#include "render.h"
#include "balloperate.h"
#include "mapgenerator.h"

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

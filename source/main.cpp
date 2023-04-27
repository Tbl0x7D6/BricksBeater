#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include "geoelement.h"
#include "render.h"

// 帧率
int frameRate = 120;

int main()
{
	scanf("%d", &frameRate);
	
	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();

	double theta;
	theta = PI / 180 * (rand() % 360);
	BALL ball(50, 50, theta, RADIUS, VELOCITY);
	//ball.energy = (ball.vx * ball.vx + ball.vy * ball.vy) / 2 - GRAVITY * ball.y;

	polygonSet polygon;
	polygonNode node;

	node.edgeNum = 5;
	node.HP = 3;
	node.xc = 320, node.yc = 240;
	node.radius = 120;
	theta = PI / 180 * (rand() % 360);
	for (int i = 0; i < node.edgeNum; i++)
	{
		node.pt[i].x = node.xc + node.radius * cos(theta);
		node.pt[i].y = node.yc + node.radius * sin(theta);

		theta += 2 * PI / node.edgeNum;
	}
	polygon.insert(node);

	while (true)
	{
		int startTime = clock();
		
		cleardevice();
		
		bool isCollision = ball.wallDetection();
		
		polygon.first();
		while (!isCollision && polygon.next())
		{
			ball.collisionDetection(polygon.present());
			if (ball.info.isCollision)
			{
				isCollision = true;
				if (polygon.present() -> HP-- == 1) polygon.remove();
			}
		}
		ball.ballUpdate();

		render(&polygon, &ball, isCollision);
		
		int endTime = clock();
		int frameTime = 1000000 / frameRate;
		int deltaTime = 1000000 * (endTime - startTime) / CLOCKS_PER_SEC;
		if (deltaTime < frameTime) usleep(frameTime - deltaTime);
		
		FlushBatchDraw();
	}
	
	_getch();
	EndBatchDraw();
	closegraph();
	return 0;
}

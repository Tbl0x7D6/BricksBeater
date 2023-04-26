#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "geoelement.h"
#include "render.h"

// 帧率
int frameRate = 120;

int main()
{
	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();

	rectSet rct;
	// 边框
	rct.insert({LONG_MIN, -1, LONG_MAX, LONG_MIN}, -1);
	rct.insert({LONG_MIN, LONG_MAX, -1, LONG_MIN}, -1);
	rct.insert({LONG_MIN, LONG_MAX, LONG_MAX, HEIGHT + 1}, -1);
	rct.insert({WIDTH + 1, LONG_MAX, LONG_MAX, LONG_MIN}, -1);

	rct.insert({200, 300, 300, 200}, 10);
	rct.insert({420, 400, 450, 350}, 10);
	rct.insert({350, 150, 420, 100}, 10);

	double theta;
	//theta = PI / 180 * (rand() % 360);
	theta = PI / 4;
	BALL ball(50, 50, theta, RADIUS, VELOCITY);
	//ball.energy = (ball.vx * ball.vx + ball.vy * ball.vy) / 2 - GRAVITY * ball.y;
	
	while (true)
	{
		int startTime = clock();
		
		cleardevice();
		
		bool isCollision = false;
		
		rct.first();
		while(rct.next())
		{
			if (!isCollision && ball.collisionDetection(rct.present() -> rct).isCollision)
			{
				isCollision = true;
				if (rct.present() -> HP-- == 0) rct.remove();
				break;
			}
		}
		ball.ballUpdate();

		render(&rct, &ball, isCollision);
		
		int endTime = clock();
		int frameTime = 1000 / frameRate;
		int deltaTime = 1000 * (endTime - startTime) / CLOCKS_PER_SEC;
		if (deltaTime < frameTime) Sleep(frameTime - deltaTime);
		
		FlushBatchDraw();
	}
	
	_getch();
	EndBatchDraw();
	closegraph();
	return 0;
}

#include "game.h"
#include "render.h"

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

// 阻塞，获取小球发射角度
double getReleaseAngle(polygonSet *polygon)
{
    double theta;

    ExMessage m;  // 消息变量
    
    // 清空消息队列
    while (peekmessage(&m, EX_MOUSE));

	while (true)
	{
		peekmessage(&m, EX_MOUSE);

		if (m.message == WM_MOUSEMOVE)
		{
			if (m.y >= HEIGHT - RADIUS)
			{
				theta = PI / 2;
				continue;
			}
			double nx = m.x - WIDTH / 2.0,
				   ny = m.y - HEIGHT + RADIUS;
			theta = PI + acos(-nx / sqrt(nx * nx + ny * ny));

			cleardevice();
			render(polygon, NULL, 0);
			line(WIDTH / 2, HEIGHT - RADIUS,
				 WIDTH / 2 + cos(theta) * 1000, HEIGHT - RADIUS + sin(theta) * 1000);
			FlushBatchDraw();
			
			continue;
		}
		else if (m.message == WM_LBUTTONUP)
		{
			if (theta < PI) continue;
				break;
		}
	}

    return theta;
}

// 一回合
void oneRound(double theta, int maxBallNum, polygonSet *polygon)
{
    int frame = 0;            // 当前帧数
    int releasedBallNum = 0;  // 已发射的球数目

    BALL *ball = new BALL[maxBallNum];

	//ball.energy = (ball.vx * ball.vx + ball.vy * ball.vy) / 2 - GRAVITY * ball.y;

	while(true)
	{
		int startTime = clock();
		
		cleardevice();

		// 每4帧发射一个球
		if (frame % 4 == 0 && releasedBallNum < maxBallNum)
			ball[releasedBallNum++] = BALL(WIDTH / 2.0, HEIGHT - RADIUS, theta, RADIUS, VELOCITY);

		for (int i = 0; i < releasedBallNum; i++)
			ballOperate(ball + i, polygon);

		render(polygon, ball, releasedBallNum);
		
		int endTime = clock();
		int frameTime = 1000000 / FRAMERATE;
		int deltaTime = 1000000 * (endTime - startTime) / CLOCKS_PER_SEC;
		if (deltaTime < frameTime) usleep(frameTime - deltaTime);
		
		FlushBatchDraw();
		frame++;

        // 如果所有球都触底则结束这一回合
        bool flag = false;
        for (int i = 0; i < releasedBallNum; i++)
        {
            if (!(ball + i) -> info.removeFlag)
            {
                flag = true;
                break;
            }
        }
        if (!flag) break;
	}

	delete ball;
}
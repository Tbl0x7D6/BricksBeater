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

// 在最上面一行以概率p填充多边形
void rowGenerator(polygonSet *polygon, double p, int HP)
{
	int radius = WIDTH / COLUMN;
	polygon -> first();
	for (int i = 0; i < radius; i++)
	{
		double r = double(rand() % 10000) / 10000;
		if (r > p) continue;

		int edgeNum = rand() % 5 + 3;
		polygon -> insert(
			polygonGenerator(radius * (2 * i + 1),
							 radius * 3,
							 edgeNum, 0.9 * radius, HP));
	}
}

// 阻塞，获取小球发射角度
double getReleaseAngle(polygonSet *polygon)
{
    double theta;

    struct ExMessage m;  // 消息变量
    
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

	// 设置时钟精度为1ms
	timeBeginPeriod(1);
	LARGE_INTEGER startCount, endCount, F;
	QueryPerformanceFrequency(&F);

	while(true)
	{
		// 开始计时
		QueryPerformanceCounter(&startCount);
		
		cleardevice();

		// 每4帧发射一个球
		if (frame % 4 == 0 && releasedBallNum < maxBallNum)
			ball[releasedBallNum++] = BALL(WIDTH / 2.0, HEIGHT - RADIUS, theta, RADIUS, VELOCITY);

		// 逐个对球进行模拟
		for (int i = 0; i < releasedBallNum; i++)
			ballOperate(ball + i, polygon);

		render(polygon, ball, releasedBallNum);

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

		// 停止计时，计算这一帧用时并延时
		QueryPerformanceCounter(&endCount);
		long long elapse=(endCount.QuadPart-startCount.QuadPart)*1000000/F.QuadPart;
		int frameTime = 1000000 / FRAMERATE;
		while (elapse < frameTime)
		{
			Sleep(1);
			QueryPerformanceCounter(&endCount);
			elapse=(endCount.QuadPart-startCount.QuadPart)*1000000/F.QuadPart;
		}

		FlushBatchDraw();
		frame++;
	}

	Sleep(500);

	// 将所有的多边形整体下移一格
	int radius = HEIGHT / ROW;
	for (int i = 0; i < radius * 2; i++)
	{
		cleardevice();

		polygon -> first();
		while (polygon -> next())
		{
			struct polygonNode *present = polygon -> present();
			present -> yc++;
			for (int i = 0; i < present -> edgeNum; i++) present -> pt[i].y++;
		}

		render(polygon, ball, 0);
		FlushBatchDraw();
		Sleep(10);
	}

	Sleep(500);

	// 判断是否有多边形超过设定底线

	// 顶端生成新的多边形
	rowGenerator(polygon, 0.5, 20);

	timeEndPeriod(1);
	delete ball;
}
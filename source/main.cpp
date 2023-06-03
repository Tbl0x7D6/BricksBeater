#include "geoelement.h"
#include "game.h"

int main()
{
	printf("**********************************\n");
	printf("*----BricksBeater---by--libeier--*\n");
	printf("**********************************\n\n\n");
	printf("Press any key to start.");
	_getch();

	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	struct polygonSet polygon;

	while (true)
	{
		bool flag = false;
		rowGenerator(&polygon, FILLRATE, 1);
		render(&polygon, NULL, 0);
		FlushBatchDraw();

		int maxBallNum = 1;

		while(!flag)
		{
			double theta = getReleaseAngle(&polygon);
			oneRound(theta, maxBallNum, &polygon);
			flag = gameOver(&polygon);
			maxBallNum++;
		}

		if (flag)
			if (MessageBox(0, (LPCSTR)"Restart?", (LPCSTR)"Game over.", MB_YESNO) != 6)
				break;

		polygon.release();
	}

	polygon.release();
	
	EndBatchDraw();
	closegraph();

	return 0;
}


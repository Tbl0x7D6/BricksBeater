#include <stdio.h>
#include <conio.h>
#include "geoelement.h"
#include "game.h"

int main()
{
	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();

	struct polygonSet polygon;
	rowGenerator(&polygon, 0.5, 20);

	while(true)
	{
		double theta = getReleaseAngle(&polygon);
		oneRound(theta, 10, &polygon);
	}
	
	_getch();
	EndBatchDraw();
	closegraph();

	return 0;
}

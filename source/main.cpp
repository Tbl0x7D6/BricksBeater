#include <stdio.h>
#include <conio.h>
#include "geoelement.h"
#include "game.h"

int main()
{
	//scanf("%d", &frameRate);
	
	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();

	polygonSet polygon;

	polygon.insert(polygonGenerator(160, 360, 4, 60, 2000));
	polygon.insert(polygonGenerator(320, 170, 5, 80, 2000));
	polygon.insert(polygonGenerator(300, 500, 7, 40, 2000));
	polygon.insert(polygonGenerator(160, 650, 3, 70, 2000));
	polygon.insert(polygonGenerator(320, 650, 8, 70, 2000));

	while(true)
	{
		double theta = getReleaseAngle(&polygon);
		oneRound(theta, 127, &polygon);
	}
	
	_getch();
	EndBatchDraw();
	closegraph();

	return 0;
}

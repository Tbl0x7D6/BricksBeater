#include "balloperate.h"

// 对单个球进行模拟
void ballOperate(BALL *ball, polygonSet *polygon)
{
    if (ball -> info.removeFlag) return;

    bool isCollision = ball -> wallDetection();
	polygon -> first();

    // 逐个与多边形检查碰撞
	while (!isCollision && polygon -> next())
	{
        polygonNode *present = polygon -> present();

		ball -> collisionDetection(present);
		if (ball -> info.isCollision)
        {
            isCollision = true;
            if (present -> HP-- == 1) polygon -> remove();
        }
    }

	ball -> ballUpdate();
}
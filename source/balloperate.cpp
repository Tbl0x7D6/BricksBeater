// 我确认本程序完全由本人独立完成。
// 姓名：李贝尔
// 学号：2023040001
// 时间：2023年6月3日

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
        struct polygonNode *present = polygon -> present();

		ball -> collisionDetection(present);
		if (ball -> info.isCollision)
        {
            isCollision = true;
            if (present -> HP-- == 1) polygon -> remove();
        }
    }

	ball -> ballUpdate();
}


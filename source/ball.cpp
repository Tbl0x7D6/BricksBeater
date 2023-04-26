#include "geoelement.h"

// BALL构造函数，初始化位置速度半径
BALL::BALL(double x, double y, double theta, double r, double v)
{
	this->x = x;
	this->y = y;
	vx = v * cos(theta);
	vy = v * sin(theta);
	radius = r;
	velocity = v;
}

// 碰撞检测，将结果存储在BALL::p中
collisionPoint BALL::collisionDetection(RECT rct)
{
	double dx, dy, dis;
	p = {0, 0, 0, 0, false, true, 0};
	
	// 计算圆心到矩形内某点最小距离dis
	// 如果圆心xy某个坐标介于边端点之间则不可能为顶点碰撞
	if (x >= rct.left && x <= rct.right)
	{
		dx = 0;
		p.isVertex = false;
		p.collisionSide = (y > rct.top) ? 2 : 4;
	}
	else if (x < rct.left)
	{
		dx = rct.left - x;
		p.xCollisionPoint = rct.left;
	}
	else
	{
		dx = x - rct.right;
		p.xCollisionPoint = rct.right;
	}
	if (y >= rct.bottom && y <= rct.top)
	{
		dy = 0;
		p.isVertex = false;
		p.collisionSide = (x > rct.right) ? 3 : 1;
	}
	else if (y < rct.bottom)
	{
		dy = rct.bottom - y;
		p.yCollisionPoint = rct.bottom;
	}
	else
	{
		dy = y - rct.top;
		p.yCollisionPoint = rct.top;
	}
	dis = sqrt(dx * dx + dy * dy);
	
	// 不发生碰撞
	if (dis > radius) return p;
	
	// 碰撞
	p.isCollision = true;
	double k;
	
	// 顶点碰撞的情况
	if (p.isVertex)
	{
		double a, b, c, delta;
		
		// 求解修正量k: x -> x - k * vx   y -> y - k * vy   （k>0）
		// 方程：(x-k*vx-xcollisionpoint)^2+(y-k*vy-ycollisionpoint)^2=r^2
		dx = p.xCollisionPoint - x;
		dy = p.yCollisionPoint - y;
		a = velocity * velocity;
		b = 2 * (vx * dx + vy * dy);
		c = dx * dx + dy * dy - radius * radius;
		delta = b * b - 4 * a * c;
		k = (- b + sqrt(delta)) / (2 * a);
		
		p.x = x - k * vx;
		p.y = y - k * vy;

		return p;
	}
	
	// 与边碰撞的情况
	switch (p.collisionSide)
	{
		case 1:
			k = (x - rct.left + radius) / vx;
			p.x = rct.left - radius;
			p.y = y - k * vy;
			break;
		case 3:
			k = (x - rct.right - radius) / vx;
			p.x = rct.right + radius;
			p.y = y - k * vy;
			break;
		case 2:
			k = (y - rct.top - radius) / vy;
			p.x = x - k * vx;
			p.y = rct.top + radius;
			break;
		case 4:
			k = (y - rct.bottom + radius) / vy;
			p.x = x - k * vx;
			p.y = rct.bottom - radius;
			break;

	}

	return p;
}

// 更新小球位置速度参数
void BALL::ballUpdate()
{
	// 未发生碰撞
	if (!p.isCollision)
	{
		//更新坐标
		x += vx * DELTA_T;
		y += vy * DELTA_T;
		
		/*//机械能守恒得y方向速度
		int sign = (vy == 0) ? 1 : fabs(vy) / vy;
		double vySquared = 2 * energy + 2 * gravity * y - vx * vx;
		vy = vySquared > 0 ? sqrt(vySquared) * sign : 0.001;*/
		
		return;
	}
	
	// 发生碰撞，先更新碰撞时的位置
	x = p.x;
	y = p.y;
	
	// 顶点碰撞
	if (p.isVertex)
	{
		// 切点到圆心单位向量n
		double nx = p.x - p.xCollisionPoint,
		       ny = p.y - p.yCollisionPoint;
		double n = sqrt(nx * nx + ny * ny);
		nx /= n;
		ny /= n;
		
		// 更新速度
		double vParallel = vx * nx + vy * ny;
		vx -= 2 * vParallel * nx;
		vy -= 2 * vParallel * ny;
		
		// 微调，保持速度模长仍然为velocity
		double k = velocity / sqrt(vx * vx + vy * vy);
		vx *= k;
		vy *= k;
		
		return;
	}
	
	// 非顶点碰撞
	if (p.collisionSide == 1 || p.collisionSide == 3) vx = -vx;
	else vy = -vy;
}

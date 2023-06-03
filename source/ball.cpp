// 我确认本程序完全由本人独立完成。
// 姓名：李贝尔
// 学号：2023040001
// 时间：2023年6月3日

#include "geoelement.h"

// 默认构造函数
BALL::BALL() {}

// BALL构造函数，初始化位置速度半径
BALL::BALL(double x, double y, double theta, double r, double v)
{
	this->x = x;
	this->y = y;
	vx = v * cos(theta);
	vy = v * sin(theta);
	radius = r;
	velocity = v;
	info.isCollision = false;
	info.removeFlag = false;
}

// 墙碰撞检测和反馈，强制弹出，有碰撞发生为true
bool BALL::wallDetection()
{
	if (x < radius)
	{
		x = radius;
		vx = -vx;
		return true;
	}

	if (x > WIDTH - radius)
	{
		x = WIDTH - radius;
		vx = -vx;
		return true;
	}

	if (y < radius)
	{
		y = radius;
		vy = -vy;
		return true;
	}

	if (y > HEIGHT - radius)
	{
		info.removeFlag = true;
		return true;
	}

	return false;
}

// 多边形碰撞检测，将结果存储在BALL::info中
void BALL::collisionDetection(struct polygonNode *polygon)
{
	double disX = x - polygon -> xc,
		   disY = y - polygon -> yc;

	info.isCollision = false;
	
	// 如果与外接圆不碰撞则不可能和正多边形碰
	if (disX * disX + disY * disY > (radius + polygon -> radius) * (radius + polygon -> radius))
		return;
	
	// 检测球与哪一条边/哪一个顶点碰撞
	// 将多边形拆分为多条线段
	for (int i = 0; i < polygon -> edgeNum; i++)
	{
		POINT *A = polygon -> pt + i,
			  *B = polygon -> pt + (i + 1) % polygon -> edgeNum;
		
		// A->B单位向量t，顺时针转90后n
		double tx = B -> x - A -> x,
			   ty = B -> y - A -> y;
		double t = sqrt(tx * tx + ty * ty);
		tx /= t, ty /= t;
		double nx = ty, ny = -tx;

		// 圆心到直线距离
		double rAx = x - A -> x, rAy = y - A -> y;
		double l = nx * rAx + ny * rAy;
		
		if (0 < l && l < radius)
		{
			// 圆心在AB方向投影与A的距离
			double s = tx * rAx + ty * rAy;
			
			// 如果发生碰撞，分边和两个端点三种情况
			// 边碰
			if (0 < s && s < t)
			{
				// 如果是从内侧碰撞则直接跳过（防止穿墙后反复在内部碰撞）
				double vn = vx * nx + vy * ny;
				if (vn > 0) continue;

				info.isCollision = true;
				info.tErr = (l - radius) / vn;
				info.nx = -nx;
				info.ny = -ny;

				return;
			}

			// A点碰
			double rA2 = rAx * rAx + rAy * rAy;
			if (rA2 < radius * radius)
			{
				info.isCollision = true;
				
				// 求解修正量tErr: x -> x - tErr * vx   y -> y - tErr * vy   （tErr>0）
				// 方程：(x-tErr*vx-xA)^2+(y-tErr*vy-yA)^2=r^2
				double a = velocity * velocity;
				double b = -2 * (vx * rAx + vy * rAy);
				double c = rA2 - radius * radius;
				double delta = b * b - 4 * a * c;
				info.tErr = (-b + sqrt(delta)) / (2 * a);

				info.nx = -(rAx - info.tErr * vx) / radius;
				info.ny = -(rAy - info.tErr * vy) / radius;

				return;
			}

			// B点碰
			double rBx = x - B -> x, rBy = y - B -> y;
			double rB2 = rBx * rBx + rBy * rBy;
			if (rB2 < radius * radius)
			{
				info.isCollision = true;

				double a = velocity * velocity;
				double b = -2 * (vx * rBx + vy * rBy);
				double c = rB2 - radius * radius;
				double delta = b * b - 4 * a * c;
				info.tErr = (-b + sqrt(delta)) / (2 * a);

				info.nx = -(rBx - info.tErr * vx) / radius;
				info.ny = -(rBy - info.tErr * vy) / radius;

				return;
			}
		}
	}
}

// 更新小球位置速度参数
void BALL::ballUpdate()
{
	// 未发生碰撞
	if (!info.isCollision)
	{
		// 更新坐标
		x += vx * DELTA_T;
		y += vy * DELTA_T;
		
		/*//机械能守恒得y方向速度
		int sign = (vy == 0) ? 1 : fabs(vy) / vy;
		double vySquared = 2 * energy + 2 * gravity * y - vx * vx;
		vy = vySquared > 0 ? sqrt(vySquared) * sign : 0.001;*/
		
		return;
	}
	
	// 发生碰撞，先回溯到碰撞时的位置
	x -= vx * info.tErr;
	y -= vy * info.tErr;
	
	// 更新速度
	double vParallel = vx * info.nx + vy * info.ny;
	vx -= 2 * vParallel * info.nx;
	vy -= 2 * vParallel * info.ny;
	
	// 微调，保持速度模长仍然为velocity
	double k = velocity / sqrt(vx * vx + vy * vy);
	vx *= k;
	vy *= k;

	// 更新坐标
	x += vx * DELTA_T;
	y += vy * DELTA_T;

	// 碰撞信息复位
	info.isCollision = false;
}


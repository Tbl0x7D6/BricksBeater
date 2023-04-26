#ifndef _FILE_GEOELEMENT_
#define _FILE_GEOELEMENT_

// 小球参数
#define RADIUS 10.0
#define VELOCITY 2.0
//#define GRAVITY 0.05

// 小球模拟每帧的增量时间
#define DELTA_T 0.5

#include <graphics.h>
#include <math.h>
#include <tchar.h>

#define PI 3.1415926536
//#define DOUBLE_MAX 0x7f7f7f7f7f7f7f7f

// 画布参数
#define WIDTH 640
#define HEIGHT 480

// 碰撞点信息
struct collisionPoint
{
	double x, y;              // 相切时圆心坐标
	double xCollisionPoint,   // 顶点碰撞时碰撞点的坐标
		   yCollisionPoint;
	bool isCollision;         // 是否发生碰撞
	bool isVertex;            // 是否为顶点碰撞
	int collisionSide;        // 非顶点碰撞时1234分别对应左上右下
};

// 小球类
class BALL
{
public:
	double radius;
	double x, y;

private:
	double velocity;
	double vx, vy;
	collisionPoint p;  // 小球碰撞点信息
	//double energy;   // 一个常量值，初始化后不再变化

public:
	// 构造函数，初始化位置速度半径
	BALL(double x, double y, double theta, double r, double v);

	// 碰撞检测相关
	collisionPoint collisionDetection(RECT rct);

	// 更新小球位置和速度
	void ballUpdate();
};

// 单个矩形
struct rectNode
{
	RECT rct;   // 几何参数

	int HP;     // 单个方块剩余血量

	// 双向链表
	rectNode *pre;
	rectNode *next;
};

// 所有矩形集合
class rectSet
{
private:
	rectNode head, tail;  // 头尾，空结构体
	rectNode *it;         // 指向当前节点

public:
	rectSet();

	// 操作
	void insert(RECT rct, int HP);  // 在it后面插入节点，插入后it指向新节点
	void remove();                  // 移除it节点，移除后it指向后面节点

	// 访问
	rectNode* present();            // 返回it指针
	bool next();                    // 移动it，如果是tail返回false
	bool pre();                     // 移动it，如果是head返回false
	void first();                   // 返回head指针
	void last();                    // 返回tail指针
};

#endif
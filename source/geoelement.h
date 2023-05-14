#ifndef _FILE_GEOELEMENT_
#define _FILE_GEOELEMENT_

#include <graphics.h>
#include <math.h>
#include <tchar.h>

#define MAX_EDGE 10

// 小球参数
#define RADIUS 6.0
#define VELOCITY 1.0
//#define GRAVITY 0.05

// 小球模拟每帧的增量时间
#define DELTA_T 5.0

#define PI 3.1415926536

//#define DOUBLE_MAX 0x7f7f7f7f7f7f7f7f

// 画布参数
#define WIDTH 640
#define HEIGHT 480

// 碰撞点信息
struct collisionInfo
{
	bool isCollision;  // 当前帧是否存在碰撞
	double nx, ny;     // 顶点碰撞时碰撞点处的法向量（从圆心向外）
	double tErr;       // 改变速度前先让坐标回溯到tErr之前
};

// 单个（正）多边形
struct polygonNode
{
	POINT pt[MAX_EDGE - 1];  // 顶点，逆时针顺序排列
	int edgeNum;             // 边数
	long xc, yc;             // 中心，用于粗略估计是否碰撞
	long radius;             // 外接球半径，用于粗略估计是否碰撞

	int HP;                  // 单个方块剩余血量

	// 双向链表
	polygonNode *pre;
	polygonNode *next;
};

// 小球类
class BALL
{
public:
	double radius;
	double x, y;
	collisionInfo info;   // 小球碰撞点信息

private:
	double velocity;
	double vx, vy;
	//double energy;   // 一个常量值，初始化后不再变化

public:
	// 默认构造函数
	BALL();

	// 构造函数，初始化位置速度半径
	BALL(double x, double y, double theta, double r, double v);

	// 墙碰撞检测和反馈，强制弹出，有碰撞发生为true
	bool wallDetection();

	// 多边形碰撞检测
	void collisionDetection(polygonNode* polygon);

	// 更新小球位置和速度
	void ballUpdate();
};

// 所有矩形集合
class polygonSet
{
private:
	polygonNode head, tail;  // 头尾，空结构体
	polygonNode *it;         // 指向当前节点

public:
	polygonSet();

	// 操作
	void insert(polygonNode p);  // 在it后面插入节点，插入后it指向新节点
	void remove();               // 移除it节点，移除后it指向后面节点

	// 访问
	polygonNode* present();      // 返回it指针
	bool next();                 // 移动it，如果是tail返回false
	bool pre();                  // 移动it，如果是head返回false
	void first();                // 移动到head
	void last();                 // 移动到tail
};

#endif
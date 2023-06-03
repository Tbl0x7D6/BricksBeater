#ifndef _FILE_GAME_
#define _FILE_GAME_

#include "geoelement.h"
#include "render.h"
#include "balloperate.h"
#include <conio.h>
#include <time.h>
#include <stdio.h>

#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1:0)    // 按键检测

polygonNode polygonGenerator(int xc, int yc,
                             int edgeNum, int radius,
                             int HP, double theta = 0);             // 生成一个多边形
void rowGenerator(polygonSet *polygon, double p, int HP);           // 在最上面一行以概率p填充多边形
double getReleaseAngle(polygonSet *polygon);                        // 阻塞，获取小球发射角度
void translate(polygonSet *polygon);                                // 将所有的多边形整体下移一格
void oneRound(double theta, int maxBallNum, polygonSet *polygon);   // 一回合
bool gameOver(polygonSet *polygon);                                 // 判断游戏是否结束

#endif


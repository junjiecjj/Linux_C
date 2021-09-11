/*************************************************************************
>> File Name: test.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2020年05月30日
>> 此程序的功能是：
************************************************************************/

/* #include <graphics.h> */
#include <stdio.h>
#include <math.h>
#include <currse.h>

#define WIN_WIDTH 1080
#define WIN_HEIGHT 640
#define IMG_MAX 11   //图片数量
#define MINE_NUM 15  //物品数量
#define MAX_ANGLE 80 //最大角度
#define PI 3.141592653
IMAGE img[IMG_MAX];
enum MINE //枚举图片数组下标
{
    i_gold = 1,
    i_money = 3,
    i_soledown = 5,
    i_soleup = 7,
    i_stone = 9,
    i_bk = IMG_MAX - 1,
};
enum MINE_TYPE //物品类型
{
    GOLD,
    STONE,
    MONEY,
    //摆动方向
    LEFT,
    RIGHT,
    //钩子状态
    M_NORMAL,
    M_LONG,
    M_SHORT,
};
struct Sole //角色信息
{
    int x;
    int y;
    int width;
    int height;
    int coin; //金币
} sole;
struct Mine //矿
{
    int x;
    int y;
    int size;  //物品抓取半径
    bool flag; //物品是否存在
    int type;  //物品类型，钱袋，金块，石头
    int gold;  //物品价值
};
struct Hook //钩子属性
{
    int x; //钩子绳子起点坐标
    int y;
    int endx; //钩子末端坐标
    int endy;
    int len;
    int angle; //角度
    int dir;
    int vx; //速度分量
    int vy;
    bool swing; //是否在摆动状态
    int state;  //钩子状态，伸长，缩短，正常
    int index;  //抓到物品的下标
} hook;
//物品结构体数组
struct Mine mine[MINE_NUM];
int distance(Hook hook);
void GameInit()
{
    initgraph(WIN_WIDTH, WIN_HEIGHT);
    srand(GetTickCount());
    //加载图片
    for (int i = 0; i < IMG_MAX - 1; i++)
    {
        char tempname[20];
        sprintf(tempname, "./images/%d.jpg", i);
        if (i <= 1)
        {
            loadimage(&img[i], tempname, 73, 62);
        }
        else
        {
            loadimage(&img[i], tempname);
        }
    }
    loadimage(&img[i_bk], "./images/bk.jpg", WIN_WIDTH, WIN_HEIGHT - 120);
    //初始化角色信息
    sole.width = 140;
    sole.height = 120;
    sole.x = WIN_WIDTH / 2 - sole.width / 2;
    sole.y = 0;
    sole.coin = 0;
    //初始化物品
    for (int i = 0; i < MINE_NUM; i++)
    {
        mine[i].x = rand() % (WIN_WIDTH - 73);
        mine[i].y = rand() % (WIN_HEIGHT - 150) + 150;
        mine[i].flag = true;
        mine[i].type = rand() % 3;
        mine[i].gold = rand() % 200;
        mine[i].size = 60;
    }
    //初始化钩子
    hook.x = sole.x + 40;
    hook.y = sole.y + 100;
    hook.len = 50;
    hook.endx = hook.x;
    hook.endy = hook.y + hook.len;
    hook.angle = 0;
    hook.dir = RIGHT;
    hook.vx = 0;
    hook.vy = 0;
    hook.swing = true;
    hook.state = M_NORMAL;
    hook.index = -1;
}
void GameDraw()
{
    cleardevice();
    //绘制背景
    putimage(0, sole.height, &img[MINE::i_bk]);
    //绘制角色后面的背景
    setfillcolor(RGB(255, 208, 52));
    solidrectangle(0, 0, WIN_WIDTH, sole.height);
    //绘制角色 ,按键切换角色状态
    putimage(sole.x, sole.y, &img[i_soleup - 1], SRCAND);
    putimage(sole.x, sole.y, &img[i_soleup], SRCPAINT);
    //绘制物品
    for (int i = 0; i < MINE_NUM; i++)
    {
        if (mine[i].flag == true)
        {
            switch (mine[i].type)
            {
            case GOLD:
                putimage(mine[i].x, mine[i].y, &img[i_gold - 1], SRCAND);
                putimage(mine[i].x, mine[i].y, &img[i_gold], SRCPAINT);
                break;
            case MONEY:
                putimage(mine[i].x, mine[i].y, &img[i_money - 1], SRCAND);
                putimage(mine[i].x, mine[i].y, &img[i_money], SRCPAINT);
                break;
            case STONE:
                putimage(mine[i].x, mine[i].y, &img[i_stone - 1], SRCAND);
                putimage(mine[i].x, mine[i].y, &img[i_stone], SRCPAINT);
                break;
            }
        }
    }
    //绘制钩子
    setlinecolor(BROWN);
    setlinestyle(PS_SOLID, 5);
    line(hook.x, hook.y, hook.endx, hook.endy);
    setfillcolor(WHITE);
    solidcircle(hook.endx, hook.endy, 5);
    //绘制分数
    char score[30];
    sprintf(score, "分数：%d", sole.coin);
    setbkmode(TRANSPARENT);
    settextstyle(50, 0, "楷体");
    outtextxy(20, 20, score);
    //作者信息
    settextstyle(20, 0, "楷体");
    outtextxy(0, 70, "作者：顽石老师");
    outtextxy(0, 90, "微信公众号：C语言Plus");
}
void HookRock(int angle)
{
    if (hook.state == M_NORMAL)
    {
        if (hook.dir == RIGHT)
        {
            hook.angle += angle;
        }
        else
        {
            hook.angle -= angle;
        }
        if (hook.angle > MAX_ANGLE)
        {
            hook.dir = LEFT;
        }
        else if (hook.angle < -MAX_ANGLE)
        {
            hook.dir = RIGHT;
        }
        hook.endx = hook.x + sin(PI / 180 * hook.angle) * hook.len;
        hook.endy = hook.y + cos(PI / 180 * hook.angle) * hook.len;
    }
}
void GameControl(int speed)
{
    //按键伸长
    if (GetAsyncKeyState(VK_SPACE) & 0x8000 && hook.state == M_NORMAL)
    {
        hook.state = M_LONG;
        hook.vx = sin(PI / 180 * hook.angle) * speed;
        hook.vy = cos(PI / 180 * hook.angle) * speed;
    }
    //碰到边界缩回
    if (hook.endx < 0 || hook.endx > WIN_WIDTH || hook.endy > WIN_HEIGHT)
    {
        hook.state = M_SHORT;
    }
}
void HookMove()
{
    //伸长与缩回处理
    if (hook.state == M_LONG)
    {
        hook.endx += hook.vx;
        hook.endy += hook.vy;
    }
    else if (hook.state == M_SHORT)
    {
        hook.endx -= hook.vx;
        hook.endy -= hook.vy;
        //如果缩短长度和原长一样就停止缩短
        if (distance(hook))
        {
            hook.state = M_NORMAL;
        }
    }
}
//抓物品
void JudgeGrap()
{
    //寻找抓到的物品
    for (int i = 0; i < MINE_NUM; i++)
    {
        if (mine[i].flag == true &&
            hook.endx > mine[i].x && hook.endx < mine[i].x + mine[i].size &&
            hook.endy > mine[i].y && hook.endy < mine[i].y + mine[i].size)
        {
            hook.index = i;
            break;
        }
    }
    //抓到之后处理
    if (hook.index != -1)
    {
        hook.state = M_SHORT;
        mine[hook.index].x = hook.endx - mine[hook.index].size / 2;
        mine[hook.index].y = hook.endy - mine[hook.index].size / 2;
        //如果缩短长度和原长一样就停止缩短
        if (distance(hook))
        {
            mine[hook.index].flag = false;      //物品消失
            sole.coin += mine[hook.index].gold; //加钱
            hook.state = M_NORMAL;              //钩子正常摆动
            hook.index = -1;                    //重置抓到物品的下标
        }
    }
}
int main()
{
    GameInit();
    DWORD t1, t2;
    t1 = t2 = GetTickCount();
    BeginBatchDraw();
    while (1)
    {
        if (t2 - t1 > 10)
        {
            HookRock(1);
            HookMove();
            t1 = t2;
        }
        t2 = GetTickCount();
        GameDraw();
        FlushBatchDraw();
        GameControl(5);
        JudgeGrap();
    }
    return 0;
}

int distance(Hook hook)
{
    int dis = sqrt((hook.endx - hook.x) * (hook.endx - hook.x) + (hook.endy - hook.y) * (hook.endy - hook.y));
    return dis <= hook.len;
}

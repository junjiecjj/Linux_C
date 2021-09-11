/*************************************************************************
>> File Name: 迷宫寻路.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.04.23

题目描述
假设一个探险家被困在了地底的迷宫之中，要从当前位置开始找到一条通往迷宫出口的路径。迷宫可以用一个二维矩阵组成，有的部分是墙，有的部分是路。迷宫之中有的路上还有门，每扇门都在迷宫的某个地方有与之匹配的钥匙，只有先拿到钥匙才能打开门。请设计一个算法，帮助探险家找到脱困的最短路径。如前所述，迷宫是通过一个二维矩阵表示的，每个元素的值的含义如下 0-墙，1-路，2-探险家的起始位置，3-迷宫的出口，大写字母-门，小写字母-对应大写字母所代表的门的钥匙
输入描述:
迷宫的地图，用二维矩阵表示。第一行是表示矩阵的行数和列数M和N
后面的M行是矩阵的数据，每一行对应与矩阵的一行（中间没有空格）。M和N都不超过100, 门不超过10扇。
输出描述:
路径的长度，是一个整数
示例1
输入

5 5
02111
01a0A
01003
01001
01111
输出

7
************************************************************************/

#include<iostream>
using namespace std;
#include<queue>
#include<cstdlib>

 
bool vis[1024][101][101];
int n,m;
char mp[102][102];
int sx,sy;

struct node
{
    int x,y;
    int status;
    int dis;
    node(){}
    node(int xx,int yy,int status,int dis):x(xx),y(yy),status(status),dis(dis) {}
};
 
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
 
 
queue<node> q;
int main(int argc, char const *argv[])
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%s",mp[i]+1);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(mp[i][j]=='2')
            {
                sx=i,sy=j;
                goto loop;
            }
    loop:;
    node p;
    vis[0][sx][sy]=1;
    q.push(node(sx,sy,0,0));
    while(!q.empty()) {
        p=q.front();
        q.pop();
        // printf("%d %d %d %d\n\n",p.status,p.x,p.y,p.dis );
        // vis[p.status][p.x][p.y]=1;
        if(mp[p.x][p.y]=='3')
        {
            printf("%d\n",p.dis );
            break;
        }
        for(int i=0;i<4;++i) {
            int xx=p.x+dx[i],yy=p.y+dy[i];
            if(xx<=0||xx>n||yy<=0||yy>m||mp[xx][yy]=='0'||vis[p.status][xx][yy]) continue;
            if(mp[xx][yy]>='A'&&mp[xx][yy]<='Z') {
                if(p.status&(1<<(mp[xx][yy]-'A')))
                {
                    vis[p.status][xx][yy]=1;
                    q.push(node(xx,yy,p.status,p.dis+1));
                     // printf("A:%d %d %d %d \n",p.status,xx,yy,p.dis+1 );
                }
            }
            else if(mp[xx][yy]>='a'&&mp[xx][yy]<='z') {
                vis[p.status|(1<<(mp[xx][yy]-'a'))][xx][yy]=1;
                q.push(node(xx,yy,p.status|(1<<(mp[xx][yy]-'a')),p.dis+1));
                // printf("a:%d %d %d %d \n",p.status,xx,yy,p.dis+1 );
 
            }
            else
            {
                vis[p.status][xx][yy]=1;
                q.push(node(xx,yy,p.status,p.dis+1));
                // printf("1:%d %d %d %d \n",p.status,xx,yy,p.dis+1 );
 
            }
 
        }
    }
    return 0;
}

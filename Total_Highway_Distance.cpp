﻿//------------------------------------------------------------
//题目：微软2015机试 Total Highway distance
//作者：122345615@qq.com  skymore
//时间：2015/9/30
//题目给出一个无向图，V = N, E = N-1,即一个连通的无根树
//	Total Hiway Distance是所有任意两个顶点间的距离之和
//	操作有 改变(u,v)边的距离，或者查询THD.
//做法是：先求出每一条边在THD中的权值（所计算的次数）即以边(u,v)为桥分开，两边结点数的乘积。先计算出一个THD,每次修改一条边就更新THD.
//------------------------------------------------------------
#include<stdio.h>
#include<queue>
#include<string.h>
#include<iostream>
const int MAX_N = 100000;
const int MAX_M = 50000;
const int MAX_K = 1000;
const bool debug = false;

typedef struct edge
{
    int v;
    long long distance;		//该边的距离
    long long times;	//在THD中，该边的权值(计算的次数)
    bool used;
    int next;
}Edge;
Edge E[2 * MAX_N + 10];
int Len = 0;				//当前已经插入的边的条数
int Head[MAX_N + 10];		//城市i邻接表的头指针
int Degree[MAX_N + 10];		//城市i当前的度
long long NumOfCity[MAX_N + 10];	//城市i所代表的城市数量
//在图的邻接表中，插入(u,v)这条长度为k的边，有向
long long Ans = 0;

int insert(int u, int v, long long k)
{
    Len++;
    //在E[len]处插入这条边
    E[Len].next = Head[u];
    E[Len].v = v;
    E[Len].distance = k;
    E[Len].times = 0;
    E[Len].used = false;
    Head[u] = Len;
    
    return 0;
}

int change(int u, int v, long long k)
{
    int x, y;
    x = Head[u];
    while(E[x].v != v)
    {
        x = E[x].next;
    }
    
    //得到要修改的边E[x]
    Ans -= E[x].distance * E[x].times;
    E[x].distance = k;
    Ans += E[x].distance * E[x].times;
    
    //修改E[x]所对应的边E[y]
    y = Head[v];
    while(E[y].v != u)
    {
        y = E[y].next;
    }
    E[y].distance = k;
    
    return 0;
}


//---------------------------------main------------------------

//---------------------------------main------------------------

//---------------------------------main------------------------
int main()
{
    long long n;
    int m;//n为城市数, m为操作数
    std::cin >> n >> m;
    Ans = 0;
    int i;
    for(i = 0; i < n; i++)
    {
        Head[i] = -1;
        Degree[i] = 0;
        NumOfCity[i] = 1;
    }
    
    int u, v;
    long long k;
    for(i = 0; i < n - 1; i++)
    {
        std::cin >> u >> v >> k;
        insert(u - 1, v - 1, k);
        insert(v - 1, u - 1, k);//无向图，插入两条边
        Degree[u - 1]++;
        Degree[v - 1]++;
    }
    
    std::queue<int> que;
    while( !que.empty() )
    {
        que.pop();
    }
    
    for(i = 0; i < n; i++)
    {
        //printf("Degree[%d] = %d\n", i, Degree[i]);
        if(Degree[i] == 1)
        {
            que.push(i);
        }
    }
    
    if(debug)
    {
        printf("LIST:\n队列中共有%lu个城市，分别是", que.size());
    }

    while( !que.empty() )
    {//把city这个城市剪掉(剪掉边)，合并到E[x].v中
        int city = que.front();
        if(debug)
        {
            printf("---que.pop()---\n城市%d出队列\n", city+1);
        }
        que.pop();
        if(Degree[city] != 1)
        {
            //printf("LAST ONE\n");
            break;
            //printf("-------------------------------\n");
        }
        
        //求x --> (city,v)在city的邻接表的位置, (city,v)是city城市连接剩下的城市的唯一的通路（未剪掉的）
        int x = Head[city];
        while(E[x].used == true)
        {
            x = E[x].next;
        }
        if(debug)
        {
            printf("---cutEdge---\n从把边(%d,%d)删掉，城市%d合并到城市%d中\n", city+1, E[x].v+1, city+1, E[x].v+1);
        }
        Degree[city] = 0;
        Degree[E[x].v]--;
        if(Degree[E[x].v] == 1)
        {
            que.push(E[x].v);
            if(debug)
            {
                printf("---que.push()---\n城市%d的度变为了1，入队列\n",E[x].v+1);
            }
        }
        E[x].used = true;
        E[x].times = NumOfCity[city] * (n-NumOfCity[city]);
        Ans += E[x].distance * E[x].times;
        NumOfCity[E[x].v] += NumOfCity[city];
        
        //求y --> (v,city)在城市E[x].v的邻接表的位置
        int y = Head[E[x].v];
        while(E[y].v != city)
        {
            y = E[y].next;
        }
        E[y].used = true;
        E[y].times = E[x].times;
        
        
    }
    
    char str[10];
    for(i = 0; i < m; i++)
    {
        std::cin >> str;
        if(str[0] == 'Q')
        {
            std::cout << Ans << std::endl;
        }
        else if (str[0] == 'E')
        {
            std::cin >> u >> v >> k;
            change(u - 1, v - 1, k);
        }
    }
    return 0;
}
/*test
 11 3
 1 2 1
 2 3 1
 2 4 1
 2 5 1
 5 6 1
 1 11 1
 1 10 1
 3 8 1
 3 9 1
 4 7 1
 QUERY
 EDIT 1 2 500
 QUERY
 */
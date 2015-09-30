﻿/*------------------------------------------------------------*/
/*题目：微软2015机试 Total Highway distance
/*作者：122345615@qq.com  skymore
/*时间：2015/9/30
/*题目给出一个无向图，V = N, E = N-1,即一个连通的无根树
/*	Total Hiway Distance是所有任意两个顶点间的距离之和
/*	操作有 改变(u,v)边的距离，或者查询THD.
/*做法是：先求出每一条边在THD中的权值（所计算的次数）即以边(u,v)为桥分开，两边结点数的乘积。先计算出一个THD,每次修改一条边就更新THD.
/*------------------------------------------------------------*/
#include<cstdio>
#include<queue>
#include<cstring>
const int MAX_N = 100000;
const int MAX_M = 50000;
const int MAX_K = 1000;

typedef struct edge
{
	int v;
	int distance;		//该边的距离
	long long times;	//在THD中，该边的权值(计算的次数)
	bool used;
	int next;
}Edge;
Edge E[2 * MAX_N + 10];
int Len = 0;				//当前已经插入的边的条数
int Head[MAX_N + 10];
int Degree[MAX_N + 10];
int NumOfCity[MAX_N + 10];	//城市i所代表的城市数量
//在图的邻接表中，插入(u,v)这条长度为k的边，有向
long long Ans = 0;

int insert(int u, int v, int k)
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

int change(int u, int v, int k)
{
    int x, y;
    x = Head[u];
    while(E[x].v != v)
    {
        x = E[u].next;
    }
    Ans -= E[x].distance * E[x].times;
    E[x].distance = k;
    Ans += E[x].distance * E[x].times;

    y = Head[v];
    while(E[y].v != u)
    {
        y = E[y].next;
    }
    E[y].distance = k;
}

//----------main----------
int main()
{
	int n, m;//n为城市数, m为操作数
	scanf("%d%d", &n, &m);

	int i;
	for(i = 0; i < n; i++)
	{
	    Head[i] = -1;
		Degree[i] = 0;
		NumOfCity[i] = 1;
	}

	int u, v, k;
	for(i = 0; i < n - 1; i++)
	{
		scanf("%d%d%d", &u, &v, &k);
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
    printf("-------------------------------\n");
	for(i = 0; i < n; i++)
	{
	    printf("Degree[%d] = %d\n", i, Degree[i]);
		if(Degree[i] == 1)
		{
			que.push(i);
		}
	}
    printf("-------------------------------\n");
    printf("num = %d  %d\n", Len, que.size());
    printf("-------------------------------\n");
	while( !que.empty() )
	{//把city这个城市剪掉和到E[x].v中
		int city = que.front();
		que.pop();
		if(Degree[city] != 1)
		{
		    printf("LAST ONE\n");
		    break;
		    printf("-------------------------------\n");
		}
		//求x为(u,v)在city的邻接表的位置
		int x = Head[city];
		while(E[x].used == true)
        {
            x = E[x].next;
        }

        		printf("u = %d v = %d  numU = %d numV = %d\n", city, E[x].v, NumOfCity[city], NumOfCity[E[x].v]);
        		printf("-------------------------------\n");
        Degree[city] = 0;
		Degree[E[x].v]--;
		E[x].used = true;
		E[x].times = NumOfCity[city] * (n-NumOfCity[city]);
		Ans += E[x].times * E[x].distance;
		NumOfCity[E[x].v] += NumOfCity[city];

        //求y为(u,v)在E[x].v的邻接表的位置
        int y = Head[E[x].v];
        while(E[y].v != city)
        {
            y = E[y].next;
        }
        E[y].used = true;
        E[y].times = E[x].times;

		if(Degree[E[x].v] == 1)
		{
		    printf("PUSH %d\n", E[x].v);
		    printf("-------------------------------\n");
			que.push(E[x].v);
		}
	}

	char str[10];
    for(i = 0; i < m; i++)
    {
        scanf("%s", &str);
        if(str[0] == 'Q')
        {
            printf("%lld\n", Ans);
        }
        else if (str[0] == 'E')
        {
            scanf("%d%d%d", &u, &v, &k);
            change(u - 1, v - 1, k);
        }
    }
	//printf("ans = %lld\n", Ans);
	return 0;
}
/*test
3 3
1 2 200
2 3 300
QUERY
EDIT 1 2 500
QUERY
*/
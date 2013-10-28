#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<vector>
using namespace std;

const int MAX = 110;
int n,m;
int sx,sy,ex,ey;
int mz[MAX][MAX];
int step[MAX][MAX],pw[MAX][MAX];
bool flag[MAX][MAX];
const int pa[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

typedef struct 
{
	int x,y;
}point;
vector<point> qu;

int mmax(int i,int j)
{
	return (i>j)?i:j;
}

int mmin(int i,int j)
{
	if(i<0) return j;
	if(j<0) return i;
	return (i<j)?i:j;
} 

int cal(int x, int y)
{
	if(mz[x][y] < 0) return -1;
	
	point tmp;
	tmp.x = x;
	tmp.y = y;
	qu.push_back(tmp);
	
	step[x][y] = 0;
	pw[x][y] = mz[x][y];
	
	while(!qu.empty())
	{
		point now;
		now = qu.front();
		qu.erase(qu.begin());
		flag[now.x][now.y] = 1;
		
		if(now.x == ex && now.y == ey)
			break;
		
		for(int i=0; i<4; i++)
		{
			point next;
			next.x = now.x + pa[i][0];
			next.y = now.y + pa[i][1];
			
			if(mz[next.x][next.y]<0 || flag[next.x][next.y])
				continue;
			
			if(step[next.x][next.y]<0 || step[now.x][now.y]+1 <= step[next.x][next.y])
			{
				if(step[next.x][next.y]<0) 
					qu.push_back(next);
				step[next.x][next.y] = step[now.x][now.y]+1;
				if(pw[next.x][next.y] < mz[next.x][next.y] + pw[now.x][now.y])
					pw[next.x][next.y] = mz[next.x][next.y] + pw[now.x][now.y];
			}
		}
	}
	
	return pw[ex][ey];
}

int main()
{
	freopen("D-large-practice.in","r",stdin);
	freopen("D-large-practice.out","w",stdout);
	
	int t;
	scanf("%d",&t);
	
	for(int cnt=1; cnt<=t; cnt++)
	{
		scanf("%d%d%d%d%d%d",&n,&m,&sx,&sy,&ex,&ey);
		sx++;
		sy++;
		ex++;
		ey++;
		memset(mz,-1,sizeof(mz));
		memset(step,-1,sizeof(step));
		memset(pw,-1,sizeof(pw));
		memset(flag,0,sizeof(flag));
		qu.clear();
		
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
			{
				scanf("%d",&mz[i][j]);
			}
				
		int ans = cal(sx,sy);
		if(ans < 0) printf("Case #%d: Mission Impossible.\n",cnt);
		else printf("Case #%d: %d\n",cnt,ans);
	}
}
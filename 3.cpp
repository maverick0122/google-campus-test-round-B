#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

const int MAX = 110;
int n;
char mp[MAX][MAX];
int flag[MAX][MAX][2];
bool step[MAX][MAX][2];

int getthrough(int x,int y,int dir,bool isst)
{
	if(step[x][y][dir]) return 0;
	if(flag[x][y][dir] >= 0) 
		return flag[x][y][dir];
		
	if(dir==0)
	{
		if(x<0 || y<0 || y>=n || mp[x][y]!='R') return 0;
		if(!isst && x<1) return 0;
		if(x>=n-1) 
		{
			flag[x][y][dir] = 1;
			return 1;
		}
	}
	else
	{
		if(y<0 || x<0 || x>=n || mp[x][y]!='B') return 0;
		if(!isst && y<1) return 0;
		if(y>=n-1) 
		{
			flag[x][y][dir] = 1;
			return 1;
		}
	}
	step[x][y][dir] = 1;
	
	int ld,rd,l,r,lu,ru;
	ld = rd = l = r = lu = ru = 0;
	
	ld = getthrough(x+1,y-1,dir,0);
	rd = getthrough(x+1,y,dir,0);
	l = getthrough(x,y-1,dir,0);
	r = getthrough(x,y+1,dir,0);
	lu = getthrough(x-1,y,dir,0);
	ru = getthrough(x-1,y+1,dir,0);
	
	if(lu>0 || ru>0 || l>0 || r>0 || ld>0 || rd>0) flag[x][y][dir] = 1;
	else flag[x][y][dir] = 0;
	
	step[x][y][dir] = 0;
	return flag[x][y][dir];
}
 
int check()
{
	memset(flag,-1,sizeof(flag));
	memset(step,0,sizeof(step));
		
	int bcnt,rcnt,left,right,up,down;
	bcnt = rcnt = left = right = up = down = 0;
	
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
		{
			if(mp[i][j]=='B') bcnt++;
			else if(mp[i][j]=='R') rcnt++;
		}
	
	if(abs(bcnt-rcnt) > 1)
		return 0;
	
	int redwin,bluewin;
	redwin = bluewin = 0;
	
	for(int i=0; i<n; i++)
	{
		if(mp[0][i]=='R') redwin |= getthrough(0,i,0,1);
		if(mp[i][0]=='B') bluewin |= getthrough(i,0,1,1);
	}
	
	if((redwin && bcnt>rcnt) || (bluewin && rcnt>bcnt)) return 0;
	if(!redwin && !bluewin) return 3;
	
	int tmpflag[MAX][MAX][2];
	
	memcpy(tmpflag,flag,sizeof(flag));
	
	char winc = 0;
	int dir = -1;
	
	if(redwin) 
	{
		winc = 'R';
		dir = 0;
	}
	if(bluewin) 
	{
		winc = 'B';
		dir = 1;
	}
	
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(tmpflag[i][j][dir]==1)
			{
				mp[i][j] = '.';
				int tmpw = 0;
				memset(flag,-1,sizeof(flag));
				memset(step,0,sizeof(step));
				for(int i=0; i<n; i++)
				{
					if(dir==0 && mp[0][i]=='R') tmpw |= getthrough(0,i,0,1);
					if(dir==1 && mp[i][0]=='B') tmpw |= getthrough(i,0,1,1);
				}
				mp[i][j] = winc;
				
				if(tmpw==0) return dir+1;
			}
		}
	}
	
	return 0;
}

int main()
{
	freopen("C-large-practice.in","r",stdin);
	freopen("C-large-practice.out","w",stdout);
	
	int t;
	scanf("%d",&t);
	
	for(int cnt=1; cnt<=t; cnt++)
	{
		scanf("%d",&n);
		memset(mp,0,sizeof(mp));
		
		for(int i=0; i<n; i++)
			scanf("%s",mp[i]);
		
		int ans = check();
		
		printf("Case #%d: ",cnt);
		if(ans == 0) printf("Impossible\n");
		else if(ans == 1) printf("Red wins\n");
		else if(ans == 2) printf("Blue wins\n");
		else printf("Nobody wins\n");
	}
}
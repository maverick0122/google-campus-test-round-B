#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<map>
using namespace std;

const int MAXR=1100;
const int MAXN=1001000;
int b;
int re[MAXR][4];

typedef struct
{
	int n,p;
	long long sump,sumd;
}node;
node dx[MAXN],dy[MAXN];
int cx,cy;

map<int,int> inx,iny;

int cmp(const void *a, const void *b)
{
	return ((node*)a)->n - ((node*)b)->n;
}

long long caldis(int x,int y)
{
	long long dis=0;
	int ix = inx[x], iy = iny[y];
	dis += (x*dx[ix-1].sump - dx[ix-1].sumd) + (dx[cx].sumd-dx[ix].sumd - x*(dx[cx].sump-dx[ix].sump));
	dis += (y*dy[iy-1].sump - dy[iy-1].sumd) + (dy[cy].sumd-dy[iy].sumd - y*(dy[cy].sump-dy[iy].sump));
	return dis;
}

int main()
{
	freopen("B-large-practice.in","r",stdin);
	freopen("B-large-practice.out","w",stdout);
	
	int t;
	scanf("%d",&t);
	
	for(int cnt=1; cnt<=t; cnt++)
	{
		scanf("%d",&b);
		inx.clear();
		iny.clear();
		memset(dx,0,sizeof(dx));
		memset(dy,0,sizeof(dy));
		cx = cy = 0;
		
		for(int i=0; i<b; i++) 
		{
			for(int j=0; j<4; j++)
				scanf("%d",&re[i][j]);
			int x1 = re[i][0];
			int y1 = re[i][1];
			int x2 = re[i][2];
			int y2 = re[i][3];
			
			for(int j=x1; j<=x2; j++)
			{
				int tmp = inx[j];
				if(tmp==0) tmp = ++cx;
				
				dx[tmp].n = j;
				dx[tmp].p += y2-y1+1;
				inx[j] = tmp;
			}
			for(int k=y1; k<=y2; k++)
			{
				int tmp = iny[k];
				if(tmp==0) tmp = ++cy;
				
				dy[tmp].n = k;
				dy[tmp].p += x2-x1+1;
				iny[k] = tmp;
			}
		}
		
		qsort(dx+1,cx,sizeof(node),cmp);
		qsort(dy+1,cy,sizeof(node),cmp);
		 
		for(int i=1; i<=cx; i++)
		{
			dx[i].sump = (long long)dx[i].p;
			dx[i].sumd = (long long)dx[i].n * dx[i].p;
			inx[dx[i].n] = i;
			//printf("x %d %d %lld %lld\n",dx[i].n,dx[i].p,dx[i].sump,dx[i].sumd);
		}
		for(int i=1; i<=cy; i++)
		{
			dy[i].sump = (long long)dy[i].p;
			dy[i].sumd = (long long)dy[i].n * dy[i].p;
			iny[dy[i].n] = i;
			//printf("y %d %d %lld %lld\n",dy[i].n,dy[i].p,dy[i].sump,dy[i].sumd);
		}
		
		for(int i=1; i<=cx; i++)
		{
			dx[i].sump += dx[i-1].sump;
			dx[i].sumd += dx[i-1].sumd;
			//printf("%d %d %d %lld %lld\n",i,dx[i].n,dx[i].p,dx[i].sump,dx[i].sumd);
		}
		for(int i=1; i<=cy; i++)
		{
			dy[i].sump += dy[i-1].sump;
			dy[i].sumd += dy[i-1].sumd;
		}
		
		int x=-1,y=-1;
		long long d=-1;
		
		for(int i=0; i<b; i++)
		{
			int x1 = re[i][0];
			int y1 = re[i][1];
			int x2 = re[i][2];
			int y2 = re[i][3];
			long long tmpd=0;
			
			for(int j=x1; j<=x2; j++)
				for(int k=y1; k<=y2; k++)
				{
					tmpd = caldis(j,k);
					//printf("%d %d %d %lld\n",i,j,k,tmpd);
					if(d<0 || tmpd < d || (tmpd==d && (j<x || (j==x && k<y))))
					{
						x = j;
						y = k;
						d = tmpd;
					}
				}
			
		}
		printf("Case #%d: %d %d %lld\n",cnt,x,y,d);
	}
} 
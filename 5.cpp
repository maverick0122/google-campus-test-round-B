#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;

typedef struct
{
	int l,r;
}range;

int main()
{
	freopen("E-large-practice.in","r",stdin);
	freopen("E-large-practice.out","w",stdout);
	
	string tmp,text;
	while(getline(cin,tmp,'\n')) 
	{
		text+=tmp;
		text+="\n";
	}
	
	vector<int> nest;
	vector<range> del;
	nest.clear();
	del.clear();
	
	int pos = -1;
	for(int i=0; i<text.size(); i++)
	{
		if(text[i]=='/')
		{
			if(i>0 && text[i-1]=='*' && !nest.empty() && pos!=(i-1))
			{
				int left = nest.back();
				nest.pop_back();
				if(nest.empty())
				{
					range tn;
					tn.l = left;
					tn.r = i;
					del.push_back(tn);
				}
			}
			else if(i<text.size()-1 && text[i+1]=='*')
			{
				nest.push_back(i);
				pos = i+1;
			}
		}
	} 
	
	while(!del.empty())
	{
		range td = del.back();
		text.erase(td.l,td.r-td.l+1);
		del.pop_back();
	}
	
	cout<<"Case #1:\n"<<text;
}
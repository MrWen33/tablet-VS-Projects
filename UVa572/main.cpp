#include <iostream>
#include<memory.h>
#include<cstdio>
using namespace std;
char field[105][105];
int fieldID[105][105];
int M,N;
int blocks;
int ID;

void dfs(int i,int j)
{
    if(i<1||j<1||i>M||j>N)return;
    if(fieldID[i][j]==ID)return;
    if(field[i][j]=='@')
    {
        fieldID[i][j]=ID;
        dfs(i+1,j);
        dfs(i,j+1);
        dfs(i+1,j+1);
        dfs(i-1,j);
        dfs(i,j-1);
        dfs(i-1,j-1);
        dfs(i+1,j-1);
        dfs(i-1,j+1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    while(cin>>M>>N&&M!=0)
    {
        memset(field,0,sizeof(field));
        memset(fieldID,0,sizeof(fieldID));
        blocks=0,ID=1;
        for(int i=1;i<=M;++i)
        {
            for(int j=1;j<=N;++j)
            {
                char c;
                cin>>c;
                field[i][j]=c;
            }
        }
        int blocks=0;
        int ID=1;
        for(int i=1;i<=M;++i)
        {
            for(int j=1;j<=N;++j)
            {
                if(fieldID[i][j]!=0)continue;
                if(field[i][j]=='@')
                {
                    dfs(i,j);
                    ++ID;
                    ++blocks;
                }
            }
        }
        cout<<blocks<<endl;
    }
    return 0;
}

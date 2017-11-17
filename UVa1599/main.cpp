#include <iostream>
#include<vector>
#include<queue>
#include<memory.h>
#define MAXN 100005
using namespace std;

vector<pair<int,int> > G[MAXN];
int N,M;

int len[MAXN];

void init()
{
    memset(len,0,sizeof(len));
    for(int i=0;i<MAXN;++i)
    {
        G[i]=vector<pair<int,int> >();
    }
}

void bfs(int n)
{
    bool visit[MAXN];
    int l=0;
    queue<int> que;
    que.push(n);
    queue<int> hlen;
    hlen.push(1);
    while(!que.empty())
    {
        int cur=que.front();que.pop();
        if(visit[cur])continue;
        visit[cur]=true;
        len[cur]=l;
        int rem=hlen.front()-1;hlen.pop();
        if(rem==0)
        {
            l++;
        }
        else
        {
            hlen.push(rem);
        }
        hlen.push(G[cur].size());
        for(int i=0;i<G[cur].size();++i)
        {
            que.push(G[cur][i].first);
        }
    }
}

void bfs2(int n=1)
{
    bool visit[MAXN];
    int l=len[n];
    queue<int> que;
    queue<int> hlen;
    que.push(n);
    hlen.push(1);
    while(!que.empty())
    {
        int cur=que.front();que.pop();
        if(visit[cur])continue;
        visit[cur]=true;
        int maxColor=0;
        for(int i=0;i<G[cur].size();++i)
        {
            pair<int,int> temp=G[cur][i];
            if(len[temp.first]==l-1)
            {
                if(temp.second>maxColor)maxColor=temp.second;
            }
        }
        int Hl=0;
        for(int i=0;i<G[cur].size();++i)
        {
            pair<int,int> temp=G[cur][i];
            if(temp.first==l-1&&temp.second==maxColor)
            {
                Hl++;
                que.push(temp.first);
            }
        }
        int rem=hlen.front()-1;hlen.pop();
        if(rem==0)
        {
            l--;
        }
        else
        {
            hlen.push(rem);
        }
        if(Hl)hlen.push(Hl);
    }
}

int main()
{
    while(cin>>N>>M)
    {
        init();
        int s,e,c;
        for(int i=0;i<M;++i)
        {
            cin>>s>>e>>c;
            pair<int,int> p1,p2;
            p1.first=e;
            p1.second=c;
            G[s].push_back(p1);
            p2.first=s;
            p2.second=c;
            G[e].push_back(p2);
        }
        bfs(N);
        bfs2();
    }
    return 0;
}

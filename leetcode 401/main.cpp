#include <iostream>
#include<string>
#include<vector>
#include<set>
using namespace std;

int ledval[]={60,120,240,480,1,2,4,8,16,32};
set<int> times;

string num2time(int n)
{

}

void getTimes(int n,bool isSelect,int sum=0,int curPos=0,int curLight=0)
{
    if(curPos>11)return;
    if(isSelect)
    {
        sum+=ledval[curPos];
        curLight+=1;
        if(curLight==n)
        {
            if(sum)times.insert(sum);
            return;
        }
    }
    getTimes(n,true,sum,curPos+1,curLight);
    getTimes(n,false,sum,curPos+1,curLight);
}

int main()
{
    int n;
    while(cin>>n)
    {
        getTimes(n,true);
        getTimes(n,false);
        for(set<int>::iterator i=times.begin();i!=times.end();++i)
        {
            cout<<*i<<endl;
        }
    }
}

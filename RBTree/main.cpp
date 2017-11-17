#include <iostream>
#include<cstdio>
using namespace std;
struct RBNode;
typedef RBNode* RBTree;
struct RBNode
{
    bool color;//True represent red,False represent black
    RBTree L,R,P;
    int val;
    RBNode():color(true),L(NULL),R(NULL),P(NULL),val(0){}
};

void printTree(RBTree T)
{
    if(T==NULL)return;
    printTree(T->L);
    printf("%d ",T->val);
    printTree(T->R);
}

void LeftRotate(RBTree &T)
{
    RBTree T0=T;
    RBTree newT=T0->R;
    T0->R=newT->L;
    if(T0->R!=NULL) T0->R->P=T0;
    newT->L=T0;
    if(newT->L!=NULL) newT->L->P=newT;
    T=newT;
}

void RightRotate(RBTree &T)
{
    RBTree T0=T;
    RBTree newT=T0->L;
    T0->L=newT->R;
    if(T0->L!=NULL) T0->L->P=T0;
    newT->R=T0;
    if(newT->R!=NULL) newT->R->P=newT;
    T=newT;
}

void Fix(RBTree T)
{
    RBTree &F=T->P,U,&G=T->P->P;
    RBTree Next=T;
    if(F->color==false) return;
    if(G->L==F)U=G->R;
    else U=G->L;
    if (U!=NULL&&U->color==true)//当叔叔节点的颜色是红色时
    {
        F->color=false;
        U->color=false;
        G->color=true;
        Next=G;
    }
    else//当叔叔节点的颜色是黑色时
    {
        if(G->L==F)
        {
            if(F->L==T)
            {
                F->color=false;
                G->color=true;
                RightRotate(G);
            }
            else
            {
                LeftRotate(F);
                Next=F->L;
            }
        }
        else
        {
            if(F->R==T)
            {
                F->color=false;
                G->color=true;
                LeftRotate(G);
            }
            else
            {
                RightRotate(F);
                Next=F->R;
            }
        }
    }
    Fix(Next);
}

void Insert(RBTree& _T,int V)
{
    if(_T==NULL)
    {
        _T=new RBNode;
        _T->val=V;
        _T->color=false;
        _T->P=_T;
        return;
    }
    RBTree T=_T;
    bool isFinished=false;
    while(!isFinished)
    {
        if(V>T->val)
        {
            if(T->R==NULL)
            {
                T->R=new RBNode;
                T->R->P=T;
                T->R->val=V;
                isFinished=true;
            }
            T=T->R;
        }
        else if(V<T->val)
        {
            if(T->L==NULL)
            {
                T->L=new RBNode;
                T->L->P=T;
                T->L->val=V;
                isFinished=true;
            }
            T=T->L;
        }
        else if(V==T->val) isFinished=true;
    }
    Fix(T);
}

int main()
{
    RBTree T=NULL;
    Insert(T,5);
    Insert(T,1);
    Insert(T,4);
    Insert(T,4);
    Insert(T,6);
    Insert(T,55);
    Insert(T,214);
    Insert(T,433);
    printTree(T);
    return 0;
}

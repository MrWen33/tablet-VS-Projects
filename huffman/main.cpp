#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include<map>
struct Heap;
typedef Heap* heapTree;
#define PRINT(X) std::cout<<X<<std::ends
using namespace std;
struct node;
typedef node* tree;
struct node
{
    int val;
    string words;
    tree l,r;

    node():l(NULL),r(NULL){}
};

struct Heap {
	int cap;
	int size;
	tree* Elements;
};

heapTree InitHeapTree(int MaxSize);
void Insert(heapTree T,tree N);
void Destory(heapTree T);
void MakeEmpty(heapTree T);
tree DeleteMin(heapTree T);
tree FindMin(heapTree T);
int isEmpty(heapTree T);
int isFull(heapTree T);
void print(heapTree T);

heapTree InitHeapTree(int MaxSize)
{
	heapTree T;
	if (MaxSize < 1) return NULL;
	T = (heapTree)malloc(sizeof(struct Heap));
	if (T == NULL) std::cerr << "Out of space!" << std::endl;
	T->Elements = (tree*)malloc((MaxSize + 1) * sizeof(tree));
	if (T->Elements == NULL)std::cerr << "Out of space!" << std::endl;
	T->cap = MaxSize;
	T->size = 0;
	T->Elements[0] = NULL;
	return T;
}

void Insert(heapTree T, tree N)
{
	int i;

	if (isFull(T))
	{
		std::cerr << "Heap is full!" << std::endl;
		return;
	}
	for (i = ++T->size; i!=1&&T->Elements[i / 2]->val > N->val; i /= 2)
    {
        T->Elements[i] = T->Elements[i / 2];
    }
	T->Elements[i] = N;
}

tree DeleteMin(heapTree T)
{
	if (isEmpty(T))
	{
		std::cerr << "Heap is empty!" << std::endl;
		return NULL;
	}
	tree min = T->Elements[1];
	int i;
	tree lastElement=T->Elements[T->size--];
	for (i = 1;i*2<=T->size;)
	{
		if (i * 2 != T->size&&T->Elements[2 * i]->val > T->Elements[2 * i + 1]->val)
		{
			i = i * 2 + 1;
		}
		else
		{
			i *= 2;
		}
		if(lastElement->val<T->Elements[i]->val)
        {
            i=i/2;
            break;
        }
		T->Elements[i / 2] = T->Elements[i];
	}
	T->Elements[i] = lastElement;
	return min;
}

tree FindMin(heapTree T)
{
	return T->Elements[1];
}

int isEmpty(heapTree T)
{
	return (bool)!T->size;
}

int isFull(heapTree T)
{
	return T->size >= T->cap ? true : false;
}

void print(heapTree T)
{
	if (T == NULL)return;
	for (int i = 1; i <= T->size; ++i)
	{
		PRINT(T->Elements[i]->val);
	}
	std::cout << std::endl;
}

void printLeaves(tree T,string code="")
{
    if(T==NULL)return;
    if(T->l)printLeaves(T->l,code+"0");
    if(T->r)printLeaves(T->r,code+"1");
    if(T->l==NULL&&T->r==NULL)
    {
        PRINT(T->words);
        PRINT(T->val);
        PRINT(code);
        cout<<endl;
    }
}

void printLeavesToFile(tree T,ofstream& out,string code="")
{
    if(T==NULL)return;
    if(T->l)printLeavesToFile(T->l,out,code+"0");
    if(T->r)printLeavesToFile(T->r,out,code+"1");
    if(T->l==NULL&&T->r==NULL)
    {
        out<<T->words<<"\t"<<T->val<<"\t"<<code<<endl;
    }
}

tree getTree(heapTree T)
{
    if(T->size==0)return NULL;
    while(T->size>1)
    {
        tree h1=DeleteMin(T);
        tree h2=DeleteMin(T);
        tree h3=new node;
        h3->val=h1->val+h2->val;
        h3->l=h1;
        h3->r=h2;
        Insert(T,h3);
    }
    return T->Elements[1];
}

void tree2map(tree T,map<string,string>& M,string code="")
{
    if(T==NULL)return;
    if(T->l==NULL&&T->r==NULL)
    {
        M[T->words]=code;
    }
    if(T->l) tree2map(T->l,M,code+"0");
    if(T->r) tree2map(T->r,M,code+"1");
}

void print(tree T)
{
    if(T==NULL)return;
    PRINT(T->val);
    print(T->l);
    print(T->r);
}

int main()
{
	heapTree heap = InitHeapTree(114514);
	ifstream in("input.txt");
	string line;
	while(getline(in,line))
    {
        string word;
        int val=0;
        for(int i=0;i<line.size();++i)
        {
            char c=line[i];
            if('a'<=c&&c<='z') word.push_back(c);
            else if('0'<=c&&c<='9')
            {
                    val*=10;
                    val+=c-'0';
            }
        }
        tree New=new node;
        New->words=word;
        New->val=val;
        Insert(heap,New);
    }
    in.close();
    tree huffman=getTree(heap);
    ofstream out("output.txt");
    //printLeavesToFile(huffman,out);
    map<string,string> word2code;
    tree2map(huffman,word2code);
    for(map<string,string>::iterator i=word2code.begin();i!=word2code.end();++i)
    {
        out<<(*i).first<<":"<<(*i).second<<endl;
    }
    out.close();
	//system("pause");
	return 0;
}

#include<iostream>
#include<string>
#include<queue>
#include<cmath>
#include<cstdlib>
using namespace std;
typedef struct Hnode* Heap;
typedef struct HTNode* HuffmanTree;
typedef HuffmanTree ElementType;
#define MINDATA -9999
#define MAXSIZE 20
struct Hnode
{
    ElementType* Data;
    int Size;
    int Capacity;
};
struct HTNode
{
    int weight;
    string code;
    HuffmanTree left;
    HuffmanTree right;
};
Heap createHeap()
{
    Heap H=new Hnode;
    H->Data=new ElementType[MAXSIZE+1];
    H->Size=0;
    H->Capacity=MAXSIZE;
    H->Data[0]=new HTNode;
    H->Data[0]->weight=MINDATA;
    H->Data[0]->left=H->Data[0]->right=nullptr;
    return H;
}
void percDown(Heap H,int p)
{
    int parent, child;
    ElementType x;
    x=H->Data[p];
    for(parent=p;parent*2<=H->Size;parent=child)
    {
        child=parent*2;
        if(child!=H->Size&&(H->Data[child]->weight>H->Data[child+1]->weight))
        {
            child++;
        }
        if(x->weight<=H->Data[child]->weight)break;
        else H->Data[parent]=H->Data[child];
    }
    H->Data[parent]=x;
}
void buildHeap(Heap H)
{
    for(int i=H->Size/2;i>0;i--)
    {
        percDown(H,i);
    }
}
bool isFull(Heap H)
{
    return (H->Size==H->Capacity);
}
bool isEmpty(Heap H)
{
    return (H->Size==0);
}
bool insert(Heap H,ElementType x)
{
    int i;
    if(isFull(H))
    {
        cout<<"error:the heap is full!";
        return false;
    }
    i=++H->Size;
    for(;H->Data[i/2]->weight>x->weight;i/=2)
    {
        H->Data[i]=H->Data[i/2];
    }
    H->Data[i]=x;
    return true;
}
ElementType deleteMin(Heap H)
{
    int parent,child;
    ElementType MinItem,x;
    if(isEmpty(H))
    {
        cout<<"error:the heap is empty!";
    }
    MinItem=H->Data[1];
    x=H->Data[H->Size--];
    for(parent=1;parent*2<=H->Size;parent=child)
    {
        child=parent*2;
        if(child!=H->Size&&(H->Data[child]->weight>H->Data[child+1]->weight))
        {
            child++;
        }
        if(x->weight<=H->Data[child]->weight)break;
        else H->Data[parent]=H->Data[child];
    }
    H->Data[parent]=x;
    return MinItem;
}
HuffmanTree Huffman(Heap H)
{
    int i,n;
    HuffmanTree T;
    buildHeap(H);
    n=H->Size;
    for(i=1;i<n;i++)
    {
        T=new HTNode;
        T->left=deleteMin(H);
        T->right=deleteMin(H);
        T->weight=T->right->weight+T->left->weight;
        insert(H,T);
    }
    return deleteMin(H);
}
void printHuffmanTree(HuffmanTree T)
{
    if(T->left==nullptr&&T->right==nullptr)
    {
        cout<<T->code<<' ';
        return;
    }
    printHuffmanTree(T->left);
    printHuffmanTree(T->right);
}
void encodeHuffmanTree(HuffmanTree T)
{
    if(T->left)
    {
        T->left->code=T->code+"0";
        encodeHuffmanTree(T->left);
    }
    if(T->right)
    {
        T->right->code=T->code+"1";
        encodeHuffmanTree(T->right);
    }
}
void decodeHuffmanTree(HuffmanTree T,string code)
{
    for(auto x:code)
    {
        if(x=='0')
        {
            T=T->left;
        }
        else
        {
            T=T->right;
        }
    }
    cout<<T->weight;
}
int main()
{
    Heap H=createHeap();
    for(int i=1;i<=5;i++)
    {
        int weight;
        cin>>weight;
        H->Data[i]=new HTNode;
        H->Data[i]->weight=weight;
        H->Data[i]->left=H->Data[i]->right=nullptr;
        H->Size++;
    }
    HuffmanTree T=Huffman(H);
    encodeHuffmanTree(T);
    decodeHuffmanTree(T,"011");
}

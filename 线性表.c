#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define IntSize 100    //表长度的初始定义
typedef int ElemType;
typedef struct{
    ElemType *data;  //指示动态分配存储的指针
    int MaxSize,length;              //数组的最大容量和当前个数
}SqList;                     //动态分配数组顺序表的类型定义

void CreateList(SqList *L,ElemType a[],int n);  //建立顺序表，将数组a的值存入
void output(SqList *L);             //输出顺序表
void InitList(SqList *L);          //初始化顺序表
void DestroyList(SqList *L);       //销毁顺序表
void ClearList(SqList *L);          //清空顺序表
bool ListEmpty(SqList *L);          //判断是否为空
int ListLength(SqList *L);          //顺序表长度
bool GetElem(SqList *L,int i,ElemType e);       //取元素
int LocateElem(SqList *L,ElemType e);            //获得元素在顺序表中的位置
bool ListInsert(SqList *L,int i,ElemType);      //插入元素
bool ListDelete(SqList *L,int i,ElemType e);    //删除元素
void uniteList(SqList *L1,SqList *L2,SqList *L3);   //合并两个顺序表
int main()
{
    SqList *L1,*L2,*L3;
    L1=(SqList*)malloc(sizeof(SqList)*IntSize);
    L2=(SqList*)malloc(sizeof(SqList)*IntSize);
    L3=(SqList*)malloc(sizeof(SqList)*IntSize);
    int a[5] = {1, 2, 3, 4, 5};
    InitList(L1);
    InitList(L2);
    InitList(L3);
    CreateList(L1, a, 5);
    output(L1);
}
void InitList(SqList *L)
{
    L->data=(ElemType*)malloc(IntSize*sizeof(ElemType));
    L->length = 0;
}
void CreateList(SqList *L,ElemType a[],int n)
{
    int i = 0, k = 0;
    while(i<n){
        L->data[i] = a[i];
        i++;
        k++;
    }
    L->length = k;
}
void output(SqList *L)
{
    for (int i = 0; i < L->length;i++)
    {
        printf("%d", L->data[i]);
    }
}
bool ListInsert(SqList *L,int i,ElemType e)
{
    int j;
    if(i<1||i>L->length)
        return false;
    if(L->length>=IntSize)
        return false;
    for (j = L->length; j >= i;j--)
        L->data[j] = L->data[j - 1];
    L->data[i] = e;
    L->length++;
    return true;
}
bool ListDelete(SqList *L,int i,ElemType e)
{
    int j;
    if(i<1||i>L->length)
        return false;
    for (j = i; j < L->length-1;j++)
        L->data[j] = L->data[j + 1];
    L->length--;
    return true;
}
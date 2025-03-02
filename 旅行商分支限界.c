#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
// 宏定义 
#define MAX_CITY_NUMBER 10 // 城市最大数目
#define MAX_COST 10000000 // 两个城市之间费用的最大值
// 全局变量 
int City_Graph[MAX_CITY_NUMBER][MAX_CITY_NUMBER];
// 表示城市间边权重的数组
int City_Size; // 表示实际输入的城市数目
int Best_Cost; // 最小费用
int Best_Cost_Path[MAX_CITY_NUMBER];
// 最小费用时的路径
// 定义结点 
typedef struct Node{
int lcost; // 优先级
int cc; // 当前费用
int rcost; // 剩余所有结点的最小出边费用的和
 int s; // 当前结点的深度，也就是它在解数组中的索引位置
int x[MAX_CITY_NUMBER]; // 当前结点对应的路径
struct Node* pNext; // 指向下一个结点
}Node;
// 定义堆和相关对操作
typedef struct MiniHeap{
Node* pHead; // 堆的头
}MiniHeap;
// 初始化
void InitMiniHeap(MiniHeap* pMiniHeap){
pMiniHeap->pHead = (Node*)malloc(sizeof(Node));
pMiniHeap->pHead->pNext = NULL;
}
// 入堆
void put(MiniHeap* pMiniHeap,Node node){
Node* next;
Node* pre;
Node* pinnode = (Node*)malloc(sizeof(Node)); // 将传进来的结点信息 copy 一份保存
// 这样在函数外部对 node 的修改就不会影响到堆了
pinnode->cc = node.cc;
pinnode->lcost = node.lcost;
pinnode->pNext = node.pNext;
pinnode->rcost = node.rcost;
pinnode->s = node.s;
pinnode->pNext = NULL;
for(int k=0;k<City_Size;k++){
pinnode->x[k] = node.x[k];
}
pre = pMiniHeap->pHead;
next = pMiniHeap->pHead->pNext;
if(next == NULL){
pMiniHeap->pHead->pNext = pinnode;
}
else{
while(next != NULL){
if((next->lcost) > (pinnode->lcost)){ // 发现一个优先级大的，则置于其前面
pinnode->pNext = pre->pNext;
pre->pNext = pinnode;
break; // 跳出
}
pre = next;
next = next->pNext;
 }
pre->pNext = pinnode; // 放在末尾
}
}
// 出堆
Node* RemoveMiniHeap(MiniHeap* pMiniHeap){
Node* pnode = NULL;
if(pMiniHeap->pHead->pNext != NULL){
pnode = pMiniHeap->pHead->pNext;
pMiniHeap->pHead->pNext = pMiniHeap->pHead->pNext->pNext;
}
return pnode;
}
//--------------------- 分支限界法找最优解 --------------------------------
void Traveler(){
int i,j;
int temp_x[MAX_CITY_NUMBER];
Node* pNode = NULL;
int miniSum; // 所有结点最小出边的费用和
int miniOut[MAX_CITY_NUMBER];
// 保存每个结点的最小出边的索引
MiniHeap* heap = (MiniHeap*)malloc(sizeof(MiniHeap)); // 分配堆
InitMiniHeap(heap); // 初始化堆
miniSum = 0;
for (i=0;i<City_Size;i++){
miniOut[i] = MAX_COST; // 初始化时每一个结点都不可达
for(j=0;j<City_Size;j++){
if (City_Graph[i][j]>0 && City_Graph[i][j]<miniOut[i]){
// 从 i 到 j 可达，且更小
miniOut[i] = City_Graph[i][j];
}
}
if (miniOut[i] == MAX_COST){// i 城市没有出边
Best_Cost = -1;
return ;
}
miniSum += miniOut[i];
}
for(i=0;i<City_Size;i++){ // 初始化的最优路径就是把所有结点依次走一遍
Best_Cost_Path[i] = i;
}
Best_Cost = MAX_COST; // 初始化的最优费用是一个很大的数
pNode = (Node*)malloc(sizeof(Node)); // 初始化第一个结点并入堆
 pNode->lcost = 0; // 当前结点的优先权为 0 也就是最优
pNode->cc = 0; // 当前费用为 0（还没有开始旅行）
pNode->rcost = miniSum; // 剩余所有结点的最小出边费用和就是初始化的miniSum
pNode->s = 0; // 层次为 0
pNode->pNext = NULL;
for(int k=0;k<City_Size;k++){
pNode->x[k] = Best_Cost_Path[k]; // 第一个结点所保存的路径也就是初始化的路径
}
put(heap,*pNode); // 入堆
while(pNode != NULL && (pNode->s) < City_Size-1){
// 堆不空 不是叶子
for(int k=0;k<City_Size;k++){
Best_Cost_Path[k] = pNode->x[k] ; // 将最优路径置换为当前结点本身所保存的
}
/*
* * pNode 结点保存的路径中的含有这条路径上所有结点的索引
* * x 路径中保存的这一层结点的编号就是 x[City_Size-2]
* * 下一层结点的编号就是 x[City_Size-1]
*/
if ((pNode->s) == City_Size-2){ // 是叶子的父亲
int edge1 =
City_Graph[(pNode->x)[City_Size-2]][(pNode->x)[City_Size-1]];
int edge2 = City_Graph[(pNode->x)[City_Size-1]][(pNode->x)[0]];
if(edge1 >= 0 && edge2 >= 0 && (pNode->cc+edge1+edge2) < Best_Cost){
//edge1 -1 表示不可达
//叶子可达起点费用更低
Best_Cost = pNode->cc + edge1+edge2;
pNode->cc = Best_Cost;
pNode->lcost = Best_Cost; //优先权为 Best_Cost
pNode->s++;
// 到达叶子层
}
}
else{ // 内部结点
for
(i=pNode->s;i<City_Size;i++){ // 从当前层到叶子层
if(City_Graph[pNode->x[pNode->s]][pNode->x[i]] >= 0){ // 可达
//pNode 的层数就是它在最优路径中的位置
int temp_cc =
pNode->cc+City_Graph[pNode->x[pNode->s]][pNode->x[i]];
int temp_rcost = pNode->rcost-miniOut[pNode->x[pNode->s]];
// 下一个结点的剩余最小出边费用和
// 等 于 当 前 结 点 的rcost 减去当前这个结点的最小出边费用
if (temp_cc+temp_rcost<Best_Cost){ // 下一个结点的最小出边费用和小于当前的最优解，说明可能存在更优解
for (j=0;j<City_Size;j++){ // 完全 copy 路径， 以便下面修改
temp_x[j]=Best_Cost_Path[j];
}
temp_x[pNode->x[pNode->s+1]] = Best_Cost_Path[i];
// 将当前结点的编号放入路径的深度为 s+1 的地方
temp_x[i] = Best_Cost_Path[pNode->s+1]; //??????????????
// 将原路 // 径中的深度为 s+1 的结点编号放入当前路径的
// 相当于将原路径中的的深度为 i 的结点与深度 W为 s+1 的结点交换
Node* pNextNode = (Node*)malloc(sizeof(Node));
pNextNode->cc = temp_cc;
pNextNode->lcost = temp_cc+temp_rcost;
pNextNode->rcost = temp_rcost;
pNextNode->s = pNode->s+1;
pNextNode->pNext = NULL;
for(int k=0;k<City_Size;k++){
pNextNode->x[k] = temp_x[k];
}
put(heap,*pNextNode);
free (pNextNode);
}
}
}
}
pNode = RemoveMiniHeap(heap);
}
}
int main(){
int i,j;
printf(" 请输入旅行的节点数 ");
scanf("%d",&City_Size);
for(i=0;i<City_Size;i++){
printf(" 请分别输入每个节点与其它节点的路程花费 ");
for(j=0;j<City_Size;j++){
scanf("%d",&City_Graph[i][j]);
}
}
Traveler();
printf(" 最小花费 ""%d\n",Best_Cost);
return 1;
}

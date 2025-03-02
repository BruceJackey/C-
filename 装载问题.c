#include<stdio.h>
#define M 100
int n=3;//装载问题的深度 
int x[]={0,0,0};//用来标记是否放入第一艘轮船
int c1=50;//第一艘轮船剩余容量
int w[]={10,40,40};//货物重量
int x1[]={0,0,0};//标记最优解
 
int Constrain(int t){
 int i; 
 int sum=0; 
 static int sum1=0; //最优解
 
 
 for(i=0;i<=t;i++){
 if(x[i]==1) 
  sum+=w[i]; 
 } 
 printf("--------------->%d\n",sum); 
 for(i=0;i<n;i++){
   printf("%d",x1[i]); 
   } 
   printf("\n"); 
 
 if(sum>c1){//如果超载返回否
 x[t]=0;
 return 0; 
 } 
 
  else {//否则记录最优解
   if(sum1<sum){
    for(i=0;i<=t;i++){
    if(x[i]==1)  x1[i]=1; 
    else x1[i]=0; 
   } 
   } 
  return 1;
  } 
}
 
int  Bound(int t){
 if(t<n) 
  return 1;
 else return 0; //如果越界返回否
}
void Backtrack(int t){
 
 int i;
 
 if(t<n){
  for(i=0;i<=1;i++){
  x[t]=i;
  if(Constrain(t)&&Bound(t))//如果没有越界且问题可能有解
   Backtrack(t+1);
  }
 } 
}
int main(){
 int i;
 int sum=0;
Backtrack(0);
 for(i=0;i<n;i++){//检查第二艘船是否满足条件
 if(x1[i]==0) 
sum+=w[i]; 
 }  
if(sum>c1){
printf("无解");
return 0;
}
  for(i=0;i<n;i++){//打印最优解，1代表放入第一艘轮船，0代表不放入第一艘
 if(x1[i]==1) 
  printf("%d  ",w[i]);  
 }  
 
}

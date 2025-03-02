//include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>    
#include <string.h> 


typedef struct {

int number;       //物品总数量
int volume;       //背吧容量
int curValue;     //背包现存价值
int curVolume;    //背包现存容量
int* curBackpack; //背包内存放物品数组，curPackage[i] = 1; 为已   经放入背包中 
                  //                                  = 0; 为未放入背包中
int maxValue;     //背包最大价值量
int* lastBackpack;//最优解背包内物品
int* goodsValue;  //物品价值数组
int* goodsWeight; //物品重量数组
}Backpack;


Backpack bp;

void initBackpack(int v, int n){

    bp.number = n;
    bp.volume = v;
    bp.curValue = 0;
    bp.curVolume = 0;
    bp.maxValue = 0;

    bp.goodsValue = (int*)malloc(bp.number * sizeof(int));
    memset(bp.goodsValue, 0, bp.number * (sizeof(int)));
    bp.goodsWeight = (int*)malloc(bp.number * sizeof(int));
    memset(bp.goodsWeight, 0, bp.number * (sizeof(int)));
    bp.curBackpack = (int*)malloc(bp.number * sizeof(int));
    memset(bp.curBackpack, 0, bp.number * (sizeof(int)));
    bp.lastBackpack = (int*)malloc(bp.number * sizeof(int));
    memset(bp.lastBackpack, 0, bp.number * (sizeof(int)));

    for(int j=0;j < bp.number;j++){
        printf("请输入第%d个物品价值:",(j+1));
        scanf("%d",&bp.goodsValue[j]);
        printf("请输入第%d个物品重量:",(j+1));
        scanf("%d",&bp.goodsWeight[j]);
    }

}


void backTrace(int position){
    if((position+1) > bp.number){
        //当物品全部测试后，查看最大价值量，如何新的价值量大于上一次价值量
        //替换掉，并记忆存放的物品
        if(bp.curValue > bp.maxValue){
            bp.maxValue = bp.curValue;      
            for(int i=0;i < bp.number;i++){
                bp.lastBackpack[i] = bp.curBackpack[i];
            }
        }
        return;
    }

    //需要通过二叉树图一步步了解回溯
    if((bp.curVolume + bp.goodsWeight[position]) <= bp.volume){
        bp.curVolume += bp.goodsWeight[position];
        bp.curValue += bp.goodsValue[position];
        bp.curBackpack[position] = 1;
        backTrace(position+1);
        bp.curVolume -= bp.goodsWeight[position];
        bp.curValue -= bp.goodsValue[position];
    }

    bp.curBackpack[position] = 0;
    backTrace(position+1);
}



int main(int argc, char* argv[])
{
    int volume,number;
    printf("请输入背包容量:");
    scanf("%d",&volume);
    printf("请输入物品数量:");
    scanf("%d",&number);

    initBackpack(volume, number);
    backTrace(0);

    if(bp.maxValue != 0){
        printf("背包最大价值数为:%d\n",bp.maxValue);
        printf("背包内存放的物品为:");
        for(int i=0;i < bp.number;i++){
            if(bp.lastBackpack[i] == 1){
                printf("第%d个物品;",(i+1));
            }
        }
        printf("\n");
    }else{
        printf("\n无最优解\n");
    }
    return 0;
}
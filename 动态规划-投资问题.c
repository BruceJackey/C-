#include<stdio.h>
#include<limits.h>

//f[i][j]表示项目i投资j万元时获得的收益
int f[4][9] = {{0,0,0,0,0,0,0,0,0}, {0,5,15,40,80,90,95,98,100}, {0,5,15,40,60,70,73,74,75}, {0,4,26,40,45,50,51,53,53}};


int main(){
    int ROWS, COLS;
    printf("输入项目数和投资钱数：");
    scanf("%d %d", &ROWS, &COLS);
    int F[ROWS+1][COLS+1];//F[i][j]表示向前i个项目投资j万元所获得的最大收益
    int x[ROWS+1][COLS+1];//x[i][j]表示投资j万元获得最大收益时项目i投资的钱的数量
    for(int i = 0; i <= ROWS; i++){
        F[i][0] = 0;
    }

    for(int i = 0; i <= COLS; i++){//初始化投资第1个项目
        F[1][i] = f[1][i];
        x[1][i] = i;
    }

    for(int i = 2; i <= ROWS; i++){//迭代计算第2个项目到最后一个项目
        for(int j = 1; j <= COLS; j++){
            F[i][j] = INT_MIN;
            int k;
            for(k = 0; k <= j; k++){//F[i][j]的最大值为该项目投入k与前i-1个项目投入j-k的和的最大值
                int temp = f[i][k] + F[i-1][j-k];
                if (temp > F[i][j]) {
                    F[i][j] = temp;
                    x[i][j] = k;//F[i][j]最大时该项目投入的钱数
                }
            }
        }
    }
    //输出投资项目及收益表
    printf("投资额     ");
    for (int i = 0; i <= COLS;i++)
        printf("%3d", i);
    printf("\n");
    for (int j = 1; j <= ROWS;j++)
    {
        printf("第%d个项目  ",j);
    for (int i = 0; i <= COLS;i++)
        printf("%3d", f[j][i]);
    printf("\n");
    }
    //打印最大化收益情况下每个项目的投资数量和最大收益
    int sumInvest = 0,sum=0;
    for(int i = ROWS; i >= 1; i--){
        int curInvest = x[i][COLS-sumInvest];
        sum += f[i][curInvest];
        printf("第%d个项目投资了%d万元。\n", i, curInvest);
        sumInvest += curInvest;
    }
    printf("最大收益为%d万元", sum);
    return 0;
}

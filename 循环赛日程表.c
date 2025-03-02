#include <stdio.h>
#define N 128
int t[N][N];
void copyt(int x1,int y1,int x2,int y2,int size) {
    int i,j,m,n;
    for(i=x1,m=x2;i<x1+size;i++,m++) {
        for(j=y1,n=y2;j<y1+size;j++,n++) {
            t[m][n]=t[i][j];
        }
    }
}
void show(int n) {
    int i,j;
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            printf("%d ",t[i][j]);
        } 
        printf("\n");
    }
}
void play(int x,int y,int n) {//需要填补的表格的左上坐标和大小
    int size=n;
    if(size<=2) {//大小等于2时可以直接填上
        t[x][y]=y,t[x][y+size-1]=y+size-1;
        t[x+size-1][y]=y+size-1,t[x+size-1][y+size-1]=y;
        return ;
    }
    size=n/2;
    play(x,y,size);//填写左上边1/4
    play(x,y+size,size);//填写右上角1/4
    copyt(x,y+size,x+size,y,size);//将左上角1/4复制到右下角
    copyt(x,y,x+size,y+size,size);//将右上角1/4复制到左下角
}
 
int main() {
    int n;
    scanf("%d",&n);
    if((n&(n-1))==0)
        {
        play(1,1,n);
		show(n);
    }
    else
        printf("输入错误！");
    return 0;
}

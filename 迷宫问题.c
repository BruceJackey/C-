#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxSize 100
#define INFINITY 100
#define IEOF -1
//using namespace std;

int Maze[MaxSize][MaxSize];//初始化迷宫Maze[i][j]=0表示（i，j）可走，=0不可走
int Mark[MaxSize][MaxSize];//Mark[i][j]=1标记（i，j）已走过
int distant[MaxSize][MaxSize];//distant[i][j]表示（i，j）离起始点的最小距离
int pathrow[MaxSize][MaxSize];//表示(i,j)的前驱点的横坐标是prex
int pathcol[MaxSize][MaxSize];//表示（i，j）的前驱点的纵坐标是prey

int StartRow,StartCol;
int EndRow,EndCol;
int Row,Col;
int Flag;//终点标志
int mindist;//路径最短长度
int tempcount;

void Init_Variety();
void Init_Window();
void DFS(int NowRow,int NowCol);
int CheckOK(int NowRow,int NowCol,int dRow,int dCol);
void MinDFS(int NowRow,int NowCol,int dist);
void printresult();
void copyresult();
void MinBFS(int NowRow,int NowCol);

//定义点集
struct point{
    int x;
    int y;
};
struct point temp[MaxSize];//存储当前递归路径
struct point result[MaxSize];//存储最短路径

int main(){
    Init_Window();
    Init_Variety();

    DFS(EndRow,EndCol);
    /*
	MinDFS(StartRow,StartCol,0);
	printf("The result of Mindist is %d\n",mindist);
	printresult();
	
 
    MinBFS(EndRow,EndCol);//逆向思维:从终点开始到起点,能够方便输出
    */
   if(!Flag) printf("NOT FOUND!");
}

//初始化变量
void Init_Variety(){
    Flag-0;
    mindist=INFINITY;
    tempcount=IEOF;
    memset(Maze,0,sizeof(Maze));
    memset(Mark,0,sizeof(Mark));
}
//初始化
void Init_Window(){
    printf("Set Row=");
    scanf("%d",&Row);
    
    printf("Set Col=");
    scanf("%d",&Col);

    printf("\n");
    printf("Please Set the maze:\n");

    for (int i=0;i<Row;i++)//读入迷宫信息
    for (int j=0;j<Col;j++)
        scanf("%d",&Maze[i][j]);
    printf("\n");
	printf("Please Set Start Place:\n");
	printf("  Set Start X=");
	scanf("%d",&StartRow);
	
	printf("  Set Start Y=");
	scanf("%d",&StartCol);
	
	printf("\n");
	printf("Please Set End Place:\n");
	
	printf("  Set END   X=");
	scanf("%d",&EndRow);
	
	printf("  Set END   Y=");
	scanf("%d",&EndCol);
	
	printf("\n");
    
}
//回溯法
void DFS(int NowRow ,int NowCol){
    Mark[NowRow][NowCol]=1;//标记当前位置

    //找到出口，递归终止，开始输出
        if (NowRow==StartRow&&NowCol==StartCol){
            Flag=1;
            printf("(%d,%d)->",NowRow,NowCol);
            return;
        }
    int dRow,dCol;
    //开始探索当前位置周围有无可走的格子
    for(dRow=-1;dRow<=1;dRow++)
        for (dCol = -1;dCol <= 1; dCol++)
            if(CheckOK(NowRow,NowCol,dRow,dCol)){
                //如果可以继续走
                DFS(NowRow+dRow,NowCol+dCol);//递归下一个点
                //如果走到过终点就输出这个点，返回上一层
                if(Flag){
                    if(NowRow==EndRow&&NowCol==EndCol)
                        printf("(%d,%d)",NowRow,NowCol);
                    else printf("(%d,%d)->",NowRow,NowCol);
                    return;
                }
                }
                Mark[NowRow][NowCol]=0;//没有通路开始回溯

            }
    //判断是否能走,若能走返回1,否则返回0 
int CheckOK(int NowRow,int NowCol,int dRow,int dCol){
	
	//不能走对角线 
    if (dRow==dCol||dRow==-dCol) return 0;
    //判断是否行越界 
	if (NowRow+dRow<0||NowRow+dRow>=Row) return 0;
	//判断是否列越界 
	if (NowCol+dCol<0||NowCol+dCol>=Col) return 0;
	//判断此路有没有走过，不允许重复走 
	if (Mark[NowRow+dRow][NowCol+dCol]) return 0;
	//判断此路是否通 
	if (Maze[NowRow+dRow][NowCol+dCol]) return 0;
	
	return 1;
	    
}
 
//回溯剪枝求最一条短路径
void MinDFS(int NowRow,int NowCol,int dist){
    if(dist>=mindist) return;
    Mark[NowRow][NowCol]=1;//标记当前位置
    //将点加入result点集
    temp[tempcount].x=NowRow;
    temp[tempcount].y=NowCol;

    //找到出口，保存结果清除当前点后直接返回上一层
    if (NowRow==EndRow&&NowCol==EndCol){
        if (dist<mindist){
            mindist=dist;
                copyresult();//拷贝
                temp[tempcount].x=IEOF;//清除temp点集
                temp[tempcount].y=IEOF;
                tempcount--;
                Mark[NowRow][NowCol]=0;//清除当前标记
        }
        Flag=1;
        return;
    }
    int dRow,dCol;
	
	//探索当前位置周围8个格子有没有能继续走的格子 
	for (dRow=-1;dRow<=1;dRow++)
	    for (dCol=-1;dCol<=1;dCol++)
	        if (CheckOK(NowRow,NowCol,dRow,dCol))  //如果可以继续走
	            MinDFS(NowRow+dRow,NowCol+dCol,dist+1);  //递归至下一个点 
	
	//清除temp点集        
	temp[tempcount].x=IEOF; 
    temp[tempcount].y=IEOF;
    tempcount--;
    
	Mark[NowRow][NowCol]=0;  //清除当前标记位置
	
}



void copyresult(){
	
	int i;
	
	for (i=0;i<=mindist;i++){
		result[i].x=temp[i].x;
		result[i].y=temp[i].y;
	}
	
}
void printresult(){
    if (Flag)
        for (int i=0;i<=mindist;i++)
            printf("Step %d :(%d,%d)\n",i,result[i].x,result[i].y);
	
}
//广度优先搜索求最短路径
/*void MinBFS(int NowRow,int NowCol){
    queue<struct point> Q;
    struct point P,R;
    int dr,dc,dx,dy;
    int i,prex,prey,nx,ny;
	
	//清空数组，将所有元素置为-1 
	memset(distant,IEOF,sizeof(distant));
	memset(pathrow,IEOF,sizeof(pathrow));
	memset(pathcol,IEOF,sizeof(pathcol));
	
	distant[NowRow][NowCol]=0; //初始结点的距离定义为0
	P.x=NowRow;
	P.y=NowCol;
	Q.push(P); //将初始结点压入队列 
	
	while(!Q.empty()){
		P=Q.front(); //返回队列第一个元素 
		Q.pop(); //结点P出队 
		dx=P.x;
		dy=P.y;
		for (dr=-1;dr<=1;dr++)
		    for (dc=-1;dc<=1;dc++)
		       if (distant[dx+dr][dy+dc]==IEOF && CheckOK(dx,dy,dr,dc))  { //如果该结点没遍历过并且能够遍历 
		       	  R.x=dx+dr; //定义子结点R 
		       	  R.y=dy+dc;
		   	      distant[dx+dr][dy+dc]=distant[dx][dy]+1; //计算子结点的距离 
		   	      pathrow[dx+dr][dy+dc]=dx; //记入子节点前驱结点的横坐标 
		   	      pathcol[dx+dr][dy+dc]=dy; //记入子节点前驱结点的纵坐标 
		   	      Q.push(R); //将子结点R压入队列 
		       }
	}
	
	
	if (distant[StartRow][StartCol]!=IEOF) {
	    Flag=1; //如果终点被遍历过则Flag置为1
	    printf("The result of mindist is %d\n",distant[StartRow][StartCol]); //输出最短路径长度
		//还原最短路径 
    	prex=StartRow;
	    prey=StartCol;
	    for (i=0;i<=distant[StartRow][StartCol];i++){ //还原前驱结点
		    printf("Step %d :(%d,%d)\n",i,prex,prey);
		    nx=prex;
		    ny=prey;
	    	prex=pathrow[nx][ny];
		    prey=pathcol[nx][ny];
	    }
	}*/




#include<stdio.h>
#include<stdlib.h>
typedef int DataType;

typedef struct Node{
	DataType Data;
	struct Node *lchild, *rchild;
}BinTNode, *BiTree;

void Create_BinTree(BiTree *T)
{
	char ch;

	scanf("%c",&ch);
	if(ch=='#')
	{
		*T==NULL;
	//	return;
	}
	else
	{
		*T=(BinTNode*)malloc(sizeof(BinTNode));
		(*T)->Data=ch;
		printf("\n建立左子树\n");
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
		Create_BinTree(  &((*T)->lchild ) );//建立左子树
		printf("\n建立右子树\n");
		Create_BinTree(  &((*T)->rchild ) );//建立右子树
	}
	return ;
}

void DestroyBitTree(BiTree *T)//销毁二叉树
{
	if(*T)
	{
		if((*T)->lchild)
			DestroyBitTree(  &((*T)->lchild ) );
		if((*T)->rchild)
			DestroyBitTree(  &((*T)->rchild)  );

	free(*T);
	*T=NULL;
	}

	printf("\n销毁成功!\n");
	return;
}


//遍历二叉树
void PreOrder_Traverase(BiTree T)//先序遍历
{
	if(T==NULL)
	return;
	else
	{
		printf(" %c " , T->Data);
		PreOrder_Traverase(T->lchild);
		PreOrder_Traverase(T->rchild);
	}

}

void InOrder_Traverase(BiTree T)//中序遍历
{
	if(T==NULL)
	return;
	else
	{
		PreOrder_Traverase(T->lchild);
		printf(" %c " , T->Data);
		PreOrder_Traverase(T->rchild);
	}

}

void PostOrder_Traverase(BiTree T)//后序遍历
{
	if(T==NULL)
	return ;
	else
	{
		PreOrder_Traverase(T->lchild);
		PreOrder_Traverase(T->rchild);
		printf(" %c " , T->Data);
	}
}


int main()
{
	BiTree Tree;
	Create_BinTree(&Tree);

	printf("\n先序遍历\n");
	PreOrder_Traverase(Tree);
	printf("\n中序遍历\n");
	InOrder_Traverase(Tree);
	printf("\n后序遍历\n");
	PostOrder_Traverase(Tree);


	DestroyBitTree(&Tree);


	return 0;
}

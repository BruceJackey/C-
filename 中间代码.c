#include<stdio.h>
#include<string.h>
#include <stdlib.h>
char prog[80],token[8];
char ch;
int syn,p,m,n,sum;
int kk=0,ii,N,nn=0;
int k=0,t,i=0;
char tt;
char * rwtab[6] = {"begin","if","then","while","do","end"};
	int scaner();
	int lrparser();
	int statement();
	int yucu();
	char *term();
	char *factor();
	char *expression();
	void emit();
	struct
	{
	char resulted[8];
	char ag1ed[8];
	char oped[8];
	char ag2ed[8];
	}quad[20];

void main()
{
		p=0;
    printf("……………………………………");
	printf("\n please input string: \n");
	printf("……………………………………\n");
	printf("\n");
	printf("……………………………………\n");
	do
	{
		scanf("%c",&ch);
		prog[p++]=ch;
	}while(ch != '#');
	p=0;
	scaner();
	lrparser();
	printf("……………………………………\n");
}
char * newtemp( void)
{
	char * P;
	char M[8];
	P = (char *)malloc(8);
	k++;
	itoa(k,M,10);
	strcpy(P+1,M);
	P[0] = 't';
	return(P);
}
int lrparser()
{
	int schain = 0;
	kk = 0;
	if(syn == 1)
	{
		scaner();
		schain = yucu();
		if(syn = 6)
		{
			scaner();
			if(syn == 0 && (kk == 0))
				printf("success");
		}
		else 
		{
			if(kk!=1)
				printf("缺end错误");
			kk=1;
		}
	}
	else
	{
		printf("begin错误");
		kk=1;
	}
return(schain);
}
int yucu()
{
	int schain = 0;
	schain = statement();
	while (syn == 26)
	{
		scaner();
		schain = statement();
	}
	return(schain);
}
int statement()
{
	char tt[8],eplace[8];
	int schain = 0;
	switch(syn)
	{
	case 10:
		strcpy(tt,token);
		scaner();
		if(syn == 18)
		{
			scaner();
			strcpy(eplace,expression());
			emit(tt,eplace,"","");
			schain = 0;
		}
		else
		{
			printf("缺少赋值号");
			kk=1;
		}
		return(schain);
		break;
	}
}
char * expression(void)
{
	char * tp,* ep2,* eplace,* tt;
	tp = (char *)malloc(12);
	ep2 = (char *)malloc(12);
	eplace = (char *)malloc(12);
	tt = (char *)malloc(12);
	strcpy(eplace,term());
	while(syn == 13 || syn == 14)
	{
		strcpy(tt,token);
		scaner();
		strcpy(ep2,term());
		strcpy(tp,newtemp());
		emit(tp,eplace,tt,ep2);
		strcpy(eplace,tp);
	}
	return(eplace);
}
char * term(void)
{
	char * tp,* ep2,* eplace,* tt;
	tp = (char *)malloc(12);
	ep2 = (char *)malloc(12);
	eplace = (char *)malloc(12);
	tt = (char *)malloc(12);
	strcpy(eplace,factor());
	while(syn == 15 || syn == 16)
	{
		strcpy(tt,token);
		scaner();
		strcpy(ep2,factor());
		strcpy(tp,newtemp());
		emit(tp,eplace,tt,ep2);
		strcpy(eplace,tp);
	}
	return(eplace);
}
char * factor(void)
{
	char * fplace;
	fplace = (char *)malloc(12);
	strcpy(fplace," ");
	if(syn == 10)
	{
		strcpy(fplace,token);
		scaner();
	}
	else if (syn == 11)
	{
		itoa(sum,fplace,10);
		scaner();
	}
	else if(syn == 27)
	{
		scaner();
		strcpy(fplace,expression());
		if(syn == 28)
			scaner();
		else
		{
			printf("')'错误");
			kk=1;
		}
	}
	else
	{
		printf("'('错误");
		kk=1;
	}
	return(fplace);
}
void emit(char * result,char * ag1,char * op,char * ag2)
{
	strcpy(quad[nn].resulted,result);
	strcpy(quad[nn].ag1ed,ag1);
	strcpy(quad[nn].oped,op);
	strcpy(quad[nn].ag2ed,ag2);
	printf("(%d) %s=%s%s%s\n", nn+1,quad[nn].resulted,quad[nn].ag1ed,quad[nn].oped,quad[nn].ag2ed);
	nn++;

}
 scaner()
{ 
   for(n=0;n<8;n++) token[n]=NULL;
   ch=prog[p++];  m=0;
   while(ch==' ') ch=prog[p++] ;
   if((ch>='a') && (ch<='z'))
   { while((ch>='a') && (ch<='z') || (ch>='0') && (ch<='9'))
   {
	  token[m++]=ch;
      ch=prog[p++];
   }   
token[m++]='\0';
p--;
syn=10;
for(n=0;n<6;n++)
    if(strcmp(token,rwtab[n])==0)
    {syn=n+1;     
    break;
	}
}
else    
    if(ch>='0' && ch<='9')
    {sum=0;
	  while((ch>='0')&&(ch<='9'))
      {sum=sum*10+(int)ch-'0';
      ch=prog[p++];
      }
    p--;
    syn=11;
}
else
    switch(ch)
    {
    case'<':m=0;token[m++]=ch;
    if(ch=='>')
    {syn=21;
     token[m++]=ch;
    }
    else if(ch=='=')
    {syn=22;
     token[m++]=ch;
    }
    else
    {syn=20;
	ch=prog[p++];
    }
    break;
    case'>':m=0;
		token[m++]=ch;
    ch=prog[p++];
    if(ch=='=')
    {syn=24;
    token[m++]=ch;
    }
    else
    {syn=23;
     p--;
    break;
    }
    break;
    case':': m=0;
    token[m++]=ch;
    ch=prog[p++];
    if(ch=='=')
    {syn=18;
    token[m++]=ch;
    }
    else
    {syn=17;
    p--;
    }
    break;
   case'+':syn=13;token[0]=ch;break;
   case'-':syn=14;token[0]=ch;break;
   case'*':syn=15;token[0]=ch;break;
   case'/':syn=16;token[0]=ch;break;
   case'=':syn=25;token[0]=ch;break;
   case';':syn=26;token[0]=ch;break;
   case'(':syn=27;token[0]=ch;break;
   case')':syn=28;token[0]=ch;break;
   case'#':syn=0;token[0]=ch;break;
   default:syn=-1;
   }
return syn;
}

#include <iostream>
#include <string.h>		// memset在string.h这个库里面
using namespace std;
char inputstream[50];   //存储输入句子
int temp=0;      //数组下标
int right;      //判断输出信息
void e();
void e1();
void t();
void t1();
void f();
int main()
{
    int right;
right=1;
cout<<"请输入您要分析的字符串以#结束(^为空字符)："<<endl;
cin>>inputstream;
e();
if((inputstream[temp]=='#')&&right)
cout<<"分析成功"<<endl;
else
cout<<"分析失败"<<endl;
return 0;
}
void e()
{
cout<<"E->TE'"<<endl;
t();
e1();
}
void e1()
{
    int right;
if(inputstream[temp]=='+')
{
cout<<"E'->+TE'"<<endl;
temp++;
t();
e1();
}
else
if (inputstream[temp]!='#'||inputstream[temp]!=')')
{
cout<<"T'->^"<<endl;
return ;
}
else
right=0;
}
void t()
{
cout<<"T->FT'"<<endl;
f();
t1();
}
void t1()
{
if(inputstream[temp]=='*')
{
cout<<"T'->*FT'"<<endl;
temp++;
f();
t1();
}
else
if (inputstream[temp]!='#'&&inputstream[temp]!=')'&&inputstream[temp]!='+')
{
cout<<"T'->^"<<endl;
int right;
right=0;
}
}
void f()
{int right;
if(inputstream[temp]=='i')
{
cout<<"F->i"<<endl;
temp++;
}
else

if(inputstream[temp]=='(')
{
cout<<"F->(E)"<<endl;
temp++;
e();
if(inputstream[temp]==')')
{
cout<<"F->(E)"<<endl;
temp++;
}
else

right=0;
}
else right =0;
}


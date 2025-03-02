#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <math.h>
#include <iterator>
#include <cctype>

using namespace std;

typedef struct Sentence{
    string sentence;	//记录句子
    int num;			//记录句子单词个数
}Sentence;

typedef struct sameSentence{
    string libsent;     //记录对到最长公共子序列的lib的句子
	string textsent;    //记录test中对比的句子
    int textnum;		//记录test中对比的句子的单词的个数
	int samenum;	    //最长公共子序列的单词个数
}sameSentence;

sameSentence saveall[1000];   //存储所有对比好的信息

Sentence libSentence[1000];     //按句存储lib文件的内容
int wordSimilarity[1000][1000];
float Score[1000][1000];      //记录最长公共子序列的得分
string str1[1000],str2[1000];   //存储每个句子分割出来的单词

int libline = 0;     //lib文件的句子的个数
int testline = 0;    //test文件的句子的个数

void libtxtToSentence( string file);  // 把lib里的内容按句子存储
void textToSentence( string file );   // 读取text文本的内容并使用动态规划进行查重
float max( float a, float b );
float maxthree( float a, float b, float c );





void libtxtToSentence( string file )   // 把lib里的内容按句子存储
{
    ifstream infile;
    infile.open( file.data() );   //将文件流对象与文件连接起来
    assert( infile.is_open() );   //若失败,则输出错误消息,并终止程序运行

    char currentChar;
	string tempSentence="";
	Sentence temp;
	int num1 = 0;

    infile >> noskipws;

    while ( !infile.eof() )
    {
        infile>>currentChar;

		if((( currentChar >='a' )&&( currentChar <='z' ))||(( currentChar >='A' )&&( currentChar <='Z' )))
		{
			tempSentence += currentChar;

		}else if(( currentChar =='.' )||( currentChar =='?' )||( currentChar =='!' ))
		{
			transform(tempSentence.begin(), tempSentence.end(), tempSentence.begin(), ::tolower);
			temp.num = num1+1;
			temp.sentence = tempSentence;
			libSentence[libline] = temp;     //按每句子存储lib的内容到libSentence[]中
			num1 = 0;
			tempSentence = "";
			libline++;      //lib文件的句子的个数
		}else    //匹配到空格
		{
			if( tempSentence=="" )
			{
				continue;
			}
			else if(tempSentence[tempSentence.size()==1?1:tempSentence.size()-1] != ' ')  //匹配到空格，当前句末不为空格，添加空格
			{
				tempSentence += " ";
				num1 += 1;    //单词个数加1
			}
		}
    }
    infile.close();             //关闭文件输入流
}


void textToSentence( string file )    // 读取text文本的内容并使用动态规划进行查重
{
    ifstream infile;
    infile.open( file.data() );   //将文件流对象与文件连接起来
    assert( infile.is_open() );   //若失败,则输出错误消息,并终止程序运行

    char currentChar;
	string tempSentence="";
	Sentence temp;
	int num1 = 0;

    infile >> noskipws;

    while ( !infile.eof() )
    {
        infile>>currentChar;

		if((( currentChar >='a' )&&( currentChar <='z' ))||(( currentChar >='A' )&&( currentChar <='Z' )))
		{
			tempSentence += currentChar;

		}else if(( currentChar =='.' )||( currentChar =='?' )||( currentChar =='!' ))   //完成一个句子的读取，进行动态规划匹配查重
		{
			transform(tempSentence.begin(), tempSentence.end(), tempSentence.begin(), ::tolower);
			temp.num = num1+1;            // 把当前读取到的test句子的单词个数存下
			temp.sentence = tempSentence;  // 把当前读取到的test句子存下
			num1 = 0;
			tempSentence = "";

			for(int i=0;i<libline-1;i++ )   //分别与lib中的每一句进行对比
			{
				string t;
				int n = 0;
				int k,j;

				for(istringstream is(temp.sentence); is>>t;) {   //存储把test的句子分割出来的单词
					str1[n++] = t;
				}

				n = 0;
				for(istringstream is1(libSentence[i].sentence); is1>>t;) {   //存储把lib的句子分割出来的单词
					str2[n++] = t;
				}

				for( k=0;k<temp.num;k++)   //test当前句子的个数
				{
					for( j=0;j<libSentence[i].num;j++)  //与lib文件的句子的单词分别进行对比
					{
						if(str1[k]==str2[j])
							wordSimilarity[k][j] = 1;
						else
							wordSimilarity[k][j] = 0;
					}
				}

				for(k=0; k<temp.num; k++)
				{
					Score[k][0] = max(Score[k-1][0]-0.5, wordSimilarity[k][0]-0.5*(k-1) );
				}
				for(k=0; k<libSentence[i].num; k++)
				{
					Score[0][k] = max(Score[0][k-1]-0.5, wordSimilarity[0][k]-0.5*(k-1) );
				}
				for(k=1;k<temp.num;k++)
				{
					for(j=1;j<libSentence[i].num;j++)
					{
						Score[k][j] = maxthree( Score[k-1][j]-0.5, Score[k][j-1]-0.5, Score[k-1][j-1]+wordSimilarity[k][j] );
					}
				}

				int sum = Score[temp.num-1][libSentence[i].num-1];

				if(saveall[testline].samenum < sum)
				{
					saveall[testline].libsent = libSentence[i].sentence;
					saveall[testline].samenum = sum;
					saveall[testline].textnum = temp.num;
					saveall[testline].textsent = temp.sentence;
				}
			}
			testline++;   //test文件的句子的个数

		}else  //匹配到空格
		{
			if( tempSentence=="" )
			{
				continue;
			}
			else if(tempSentence[tempSentence.size()==1?1:tempSentence.size()-1] != ' ') //匹配到空格，当前句末不为空格，添加空格
			{
				tempSentence += " ";
				num1 += 1;
			}
		}
    }
    infile.close();             //关闭文件输入流
}


float max( float a, float b )
{
	if( a > b )
		return a;
	else
		return b;
}


float maxthree( float a, float b, float c )
{
	float temp = a;

	if( temp < b )
		temp = b;
	if( temp < c )
		temp = c;

	return temp;
}
int main()
{
	int j;
	float a=0,b=0;  //a用来存储重复单词总数，b用来存储单词总数
	string libfile = "D://lib.txt";
	string textfile = "D://text.txt";

	libtxtToSentence( libfile );

	textToSentence( textfile );

	for( j=0; j<testline-1; j++ )
	{
		cout<<"The "<<j+1<<" compare"<<"\n"<<endl;
		cout<<saveall[j].textsent<<endl;
		cout<<saveall[j].libsent<<endl;
		cout<<"The samenum is  "<<saveall[j].samenum<<"\t"<<"The textnum is  "<<saveall[j].textnum<<endl;
		cout<<"This setence's duplicate checking rate is:"<<float(saveall[j].samenum)/float(saveall[j].textnum)*100<<"\%"<<endl;
		a+=saveall[j].samenum;
		b+=saveall[j].textnum;
		cout<<"\n"<<endl;
	}
    cout<<"The duplicate checking rate is :"<<a/b*100<<"\%"<<endl;
	return 0;
}

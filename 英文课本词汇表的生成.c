#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//单词节点
typedef struct Wordnode
{
    char* word;//保存单词的字符串
    int count;//该单词的数目
    struct Wordnode* next;//下一个单词节点
}WordNode;
 
//单词链表
typedef struct WordList
{
   WordNode* first;//单词链表的首节点
   WordNode* last;//单词链表的末节点
   int nodeCount; //单词节点的数目
}WordList;
//打印词汇表，max_num为打印词汇的个数，如果是-1，则全部打印
void PrintWordList(WordList* wordlist, int max_num );
 
//词汇表排序，isAscend=true为升序排序，否则为降序排序
void SortWordList(WordList* wordlist, int isAscend );
 void SortWordList2(WordList *wordlist, int isAscend);
//从词汇表中查找某个词汇，word为要查找的词汇，如果词汇存在表中，则返回该词汇的节点指针，否则返回NULL
WordNode* FindWord(WordList* wordlist, const char* word);
 
//从文件中读取字符，并保存到字符串中，words为接收字符串地址，count指定读取字符的最大数量，返回值为实际读取的字符个数
int ReadWordsFromFile(FILE* fp, char* words, int count);
 
//词汇统计，words为已经保存了词汇的字符串，wordlist为将要生成的词汇表，flag如果为true则表示区分大小写，为false则不区分大小写。
void WordsStatistic(const char* words, WordList* wordlist,int flag);
 
//从字符串中读取一个单词，start为源字符串words的开始位置下标，end用来接收读取一个单词后，words的下标。返回值为单词的长度，如果返回-1，表示已经读完所有的单词。
int ReadWordFromString(const char* words, int start, int* end, char* word);
 
//释放词汇表的内存空间
void FreeWordList(WordList wordlist);

//按词频快排
//int partition(WordList *L, WordNode Wordnode[], int low, int high);

/*int partition(WordList* L,WordNode Wordnode[], int low, int high)
{
     WordNode* c;
     char* s;
     char* pivotkey;
     int d;
    c = L->first;
    pivotkey = c->word;
    while (low < high)						//从表的两端交替向中间扫描
	{
        while (low < high && strcmp( Wordnode[high].word , pivotkey)>=0)
        {   
            high--;  } 
                s = Wordnode[low].word;
                d = Wordnode[low].count;
                Wordnode[high].word =Wordnode[low].word;
               Wordnode[high].count= Wordnode[low].count;
                Wordnode[low].word = s;
                Wordnode[low].count = d;
                
               //将枢轴记录小的记录交换到低端
        while (low < high && strcmp(Wordnode[low].word, pivotkey )<=0)
        {    
            low++; 
                
	}
               s = Wordnode[low].word;
                d = Wordnode[low].count;
                Wordnode[high].word =Wordnode[low].word;
               Wordnode[high].count= Wordnode[low].count;
                Wordnode[low].word= s;
                Wordnode[low].count = d;
               
    int pivot;
        if (low < high)
        {
            pivot = partition(L, Wordnode,low, high); //将L->r[low..high]一分为二
                                             //算出枢轴值pivot
            partition(L, Wordnode,low, pivot - 1);        //对低子表递归排序
            partition(L, Wordnode,pivot + 1, high);       //对高子表递归排序
        }           
								//返回枢轴所在位置
    }
    return low;	}*/


//从文件中读取若干字节的单词。
//fp:非空的文件指针
//words:用来接收来自文件的字符串
//count:从文件中读取的字节数，如果该参数大于文件实际的字节数，则去取全部的字节
int ReadWordsFromFile(FILE *fp, char *words, int count)
{
    //获取文件的字节数
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
 
    //开始读取字符
    fseek(fp, 0, SEEK_SET);
    int buffer_len = count;
    if (count > file_size)buffer_len = file_size;
    for (int i = 0; i < buffer_len; i++)
    {
        char ch;
        fread(&ch, 1, 1, fp);
        words[i] = ch;
    }
    //字符串结尾
    words[buffer_len] = '\0';
    return buffer_len;
}

//从字符串中读取一个单词,因为每次只能读取一个单词，所以为了能够遍历整个字符串，读取完一个
//单词之后，就返回当前的指针位置，下次读取一个单词，指针就从此开始。（类似于文件的读取）
//words:包含英文段落的字符串
//start:从字符串的这个位置开始读取一个单词
//end:接收返回的指针位置
//word:j接收读到的单词
//返回值：返回读到的单词的长度，-1表示已经到了结尾，0表示没有读取到单词
int ReadWordFromString(const char* words, int start, int* end, char* word)
{
    char ch;
    int count = 0;//单词的长度
 
    *end = start;
    while (1)
    {
        ch = words[*end];
        (*end)++;
        if ((ch >= 48 && ch <= 57) ||  (ch >= 97 && ch <= 122))//如果是谁或者字母，则读取为单词的一部分
        {
            word[count] = ch;
            count++;
        }
        else if((ch >= 65 && ch <= 90) )
        {
            word[count] = tolower(ch);
            count++;
        }
        else if (ch == '\0') return -1;//如果读到字符串末尾，则返回结束标志-1
        else break;//如果字符是标点、空格、换行等非字母和数字型字符，则中断，表示已经完成一个单词的读取
    }
    word[count] = '\0';
    return count;
}

//从单词列表中查找单词，如果找到指定的单词，则返回该单词的节点指针，否则返回NULL
//wordlist:单词链表
//word:要查找的单词
WordNode* FindWord(WordList* wordlist, const char* word)
{
 
    int count = wordlist->nodeCount;
    WordNode* node = wordlist->first;
    //笨办法，遍历整个链表，查找是否存在指定的单词
    for (int i = 0; i < count; i++)
    {
        if (strcmp(word, node->word) == 0)return node;
        node = node->next;
    }
 
    return NULL;
}




//统计单词并生成单词列表
//words:保存英语段落的字符串
//wordlist：一个空的单词列表
//flag:指示是否区分大小写，如果为true,就是区分大小写，false就是不区分大小写
void WordsStatistic(const char* words, WordList* wordlist,int flag )
{
    int start = 0, end;
    while (1)
    {
        char word[100] = { '\0' };//一般没有单词超过100个字母的吧，所以定义100字节的数组足够了
        int word_len;
        word_len = ReadWordFromString(words, start, &end, word);//从字符串中读取一个单词
        start = end;
        if (word_len == -1)break;//字符串已经到了结尾，表示段落已经处理完，可以停止读取单词
        if (word_len == 0)continue;//没有读取到单词，则立即再次读取
        
        //不区分大小写的话（Is 和is被认为是同一个单词），则将单词全部变为小写（如Is变为is）
        if (flag==1) for (int i = 0; i < word_len; i++)
        {
            if (word[i] >= 65 && word[i] <= 90)word[i] = word[i] + (char)32;
        }
      
        WordNode* node;
        node = FindWord(wordlist, word);//读取到一个单词，首先找找这个单词是否在单词链表中，如果在则返回该单词的节点指针
        if (node == NULL)//如果单词链表中不存在该单词，则将该单词添加进去链表中
        {
            WordNode* word_node = (WordNode*)malloc(sizeof(WordNode));//创建一个单词节点
            int word_len = strlen(word);
            word_node->word = (char*)malloc(word_len + 1);//为单词节点的word成员分配空间
            word_node->word[word_len] = '\0';
            word_node->count = 1;
            strcpy(word_node->word, word);//将单词复制到单词节点中
            word_node->next = NULL;
 
            if (wordlist->first == NULL)//如果单词链表为空，则进行以下操作
            {
                wordlist->nodeCount = 1;
                wordlist->first = word_node;
                wordlist->last = word_node;
            }
            else//单词列表部位空，则进行以下操作
            {
                wordlist->last->next = word_node;
                wordlist->last = word_node;
                wordlist->nodeCount++;
            }
        }
        else//如果单词已经存在单词列表中，则将该单词的数目加1
        {
            node->count++;
        }
    }
}
//打印单词列表的前
//wordlist:单词列表
//max_num：打印单词节点的最大数量，如果是-1，则表示打印整个单词链表，如果max_num大于链表的实际长度，也打印全部链表节点。
void PrintWordList(WordList* wordlist, int max_num)
{
    WordNode *node = wordlist->first;
    int n = max_num;
    if (max_num == -1 || max_num > wordlist->nodeCount)n = wordlist->nodeCount;
    //遍历链表并打印
    for (int i = 0; i < n; i++)
    {
        printf("%s：%d\n", node->word, node->count);
        node = node->next;
    }
}

//单词链表排序。冒泡排序，考虑到WordNode的成员数比较少，直接采用值交换的方法，而不是链表节点指针的交换
//wordlist:单词链表
//isAscend：是否升序排序，true为升序排序，false为降序排序
void SortWordList(WordList* wordlist, int isAscend)
{
    WordNode *p;
 
    if (wordlist->nodeCount <= 1)return;//如果单词链表的长度小于1则直接结束排序
 
    for (int i = wordlist->nodeCount - 1; i > 0; i--)
    {
        p = wordlist->first;
        for (int j = 0; j < i; j++)
        {
            if ((isAscend && p->count > p->next->count) || (!isAscend && p->count < p->next->count))
            {
                char* s;
                int c;
                s = p->word;
                c = p->count;
                p->word = p->next->word;
                p->count = p->next->count;
                p->next->word = s;
                p->next->count = c;
            }
            p = p->next;
        }
    }
 
}
void SortWordList2(WordList* wordlist, int isAscend)
{
    WordNode *p;
 
    if (wordlist->nodeCount <= 1)return;//如果单词链表的长度小于1则直接结束排序
 
    for (int i = wordlist->nodeCount - 1; i > 0; i--)
    {
        p = wordlist->first;
        for (int j = 0; j < i; j++)
        {
            if ((isAscend && strcmp((p->word),(p->next->word))<=0) || (!isAscend && strcmp((p->word),(p->next->word))>=0))
            {
                char* s;
                int c;
                s = p->word;
                c = p->count;
                p->word = p->next->word;
                p->count = p->next->count;
                p->next->word = s;
                p->next->count = c;
            }
            p = p->next;
        }
    }
 
}
//释放单词列表
void FreeWordList(WordList wordlist)
{
     WordNode* cur, * next;
    cur = wordlist.first;
    for (int i = 0; i < wordlist.nodeCount; i++)
    {
        next = cur->next;
        free(cur->word);//释放word成员指向的内存
        free(cur);//释放节点的内存
        cur = next;
    }
}


    int main()
    {

        char *words;
        FILE *fp;
        fp = fopen("D:\\text.txt", "r");
        //获取文件的字节数
        int file_size;
        fseek(fp, 0, SEEK_END);
        file_size = ftell(fp);

        //重置文件指针到开头
        fseek(fp, 0, SEEK_SET);

        //从文件中读取单词到字符串
        words = (char *)malloc(file_size + 1);
        ReadWordsFromFile(fp, words, file_size);

        //打印原文
        printf("原文：\n");
        printf("%s\n", words);

        //单词频率统计，不区分大小写
        WordList wordlist;
        wordlist.first = NULL;
        wordlist.last = NULL;
        wordlist.nodeCount = 0;
        WordsStatistic(words, &wordlist, 0); //false表示不区分大小写

        //词汇表排序，降序排序
        SortWordList(&wordlist, 0); //false表示降序排序

        //打印词汇列表，全部打印
        printf("词频统计表：\n");
        PrintWordList(&wordlist, -1); //-1位打印全部链表节点
        
        
        //打印频率最高的10个单词
        printf("高频词汇：\n");
        PrintWordList(&wordlist, 10);

         //字典顺序快排
       // partition(&wordlist, Wordnode, 1, wordlist.nodeCount);
         SortWordList2(&wordlist, 0); 
        //打印词汇列表，全部打印
        printf("字典顺序表：\n");
        PrintWordList(&wordlist, -1); //-1位打印全部链表节点
        fclose(fp);
        free(words);
        FreeWordList(wordlist);
        getchar();
        return 0;
}

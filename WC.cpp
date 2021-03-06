#include<stdio.h>
#include<io.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>

using namespace std;

char s[5];
void print(FILE*fp)//对文件内容进行检索的函数 
{
	int i,j=0;
    int character=0;
    int lines=1;
    int word=0;
    int wordflag=0;
    int nullstring=0;
    int annotation=0;
    int codeline=0;
    int this_lines_character=0;
    int annotationflag=0;//初始化变量 
		while (!feof(fp))
		{//读取文件直到结尾 
			i=fgetc(fp);
			if(i=='\r'||i=='�')
			    continue;//跳过\r和文件结尾标识符
			character+=1;//统计字符数 
			if(i!=' '&&i!='\t'&&i!='\n')
				this_lines_character+=1;
			if(i==j&&j=='/')
				{
				   if(this_lines_character<4)
				   annotationflag=1;//判断这一行是否含有注释 
				}
			if(i=='\n') {
				lines+=1;
				if(this_lines_character<=1)
					nullstring+=1;
				else if(annotationflag==1)
					annotation+=1;
				else 
					codeline+=1;
					annotationflag=this_lines_character=0;
			}//在换行后判断是空行还是注释还是代码行 
			if((i>='a'&&i<='z')||(i>='A'&&i<='Z'))
				wordflag=1;
			else {
				if(wordflag==1) {
					wordflag=0;
					word+=1;
				}
			}//判断单词 
			j=i;
		}
		if(wordflag)
		word++;
		if(j=='\n') {
			nullstring+=1;
		}
		else {
			if(this_lines_character<=1)
	 		nullstring+=1;
	 	else if(annotationflag==1)
	 		annotation+=1;
	 	else
	 		codeline+=1;
		}//C文件会直接在末尾加上两个换行符
		//文件中换行符是由'\r'和'\n'组成
		if(strcmp(s,"-c")==0)
		printf("the number of characters: %d\n",character);
		else if(strcmp(s,"-w")==0)
		printf("the number of words: %d\n",word);
		else if(strcmp(s,"-l")==0)
		printf("the number of lines: %d\n",lines);
		else if(strcmp(s,"-a")==0)
		{
		 printf("the number of nullstring: %d\n",nullstring);
		 printf("the number of codeline: %d\n",codeline);
		 printf("the number of annotation: %d\n",annotation);
	    }//进行对应的输出 
}
void currsion(string path,char *c)
{//path作为当前的路径 
	struct _finddata_t filefind; 
	string curr = path + "\\*.*";// 修改此处改变搜索条件
	int handle;
	if((handle = _findfirst(curr.c_str(), &filefind)) != -1)
	{
		while(! _findnext(handle, &filefind))//遍历当前目录中的所有文件和文件夹 
		{
			if(strcmp(filefind.name, "..") == 0)
				continue;
			if((_A_SUBDIR == filefind.attrib))//是子目录
			{
				printf("[Dir]:\t%s\n", filefind.name);
				curr = path + "\\" + filefind.name;
				currsion(curr,c);// 递归遍历子目录
			}
			else
			{
				char ext[_MAX_EXT];  
				_splitpath(filefind.name,NULL,NULL,NULL,ext);//获取文件后缀 
				if( (strcmp(".txt",ext)==0&&strcmp(c,"*.txt")==0)||(strcmp(".c",ext)==0&&strcmp(c,"*.c")==0))
				{
				 printf("[File]:\t%s\n", filefind.name);
				 string x=filefind.name;
				 x=path+"\\"+x;//打开当前文件的路径 
				 FILE*fp=fopen(x.data(),"r");
				 print(fp);
				 fclose(fp);
			    }
			}
		}
		_findclose(handle);
	}
}
int main(int argc, char *argv[])
{
	memset(s,0,sizeof(s));//通过argc来判断是那种输入
	if(argc==3){
		FILE*fp=fopen(argv[2],"r");
		strcpy(s,argv[1]);
		if(fp==NULL)
		printf("ERROR: NO SUCH FILE\n");
		else
		print(fp);
		fclose(fp);
	}
	else if(argc==4)
	{
		    strcpy(s,argv[2]);
          	string path(".");//.就是当前路径 
	        currsion(path,argv[3]);
    }
    else if(argc==2)
    system("GUI.exe");
    else
    printf("INPUT ERROR\n");
return 0;
}

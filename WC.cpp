#include<stdio.h>
#include<io.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>

using namespace std;

char s[5];
void print(FILE*fp)//¶ÔÎÄ¼şÄÚÈİ½øĞĞ¼ìË÷µÄº¯Êı 
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
    int annotationflag=0;//³õÊ¼»¯±äÁ¿ 
		while (!feof(fp))
		{//¶ÁÈ¡ÎÄ¼şÖ±µ½½áÎ² 
			i=fgetc(fp);
			if(i=='\r'||i=='ÿ')
			    continue;//Ìø¹ı\rºÍÎÄ¼ş½áÎ²±êÊ¶·û
			character+=1;//Í³¼Æ×Ö·ûÊı 
			if(i!=' '&&i!='\t'&&i!='\n')
				this_lines_character+=1;
			if(i==j&&j=='/')
				{
				   if(this_lines_character<4)
				   annotationflag=1;//ÅĞ¶ÏÕâÒ»ĞĞÊÇ·ñº¬ÓĞ×¢ÊÍ 
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
			}//ÔÚ»»ĞĞºóÅĞ¶ÏÊÇ¿ÕĞĞ»¹ÊÇ×¢ÊÍ»¹ÊÇ´úÂëĞĞ 
			if((i>='a'&&i<='z')||(i>='A'&&i<='Z'))
				wordflag=1;
			else {
				if(wordflag==1) {
					wordflag=0;
					word+=1;
				}
			}//ÅĞ¶Ïµ¥´Ê 
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
		}//CÎÄ¼ş»áÖ±½ÓÔÚÄ©Î²¼ÓÉÏÁ½¸ö»»ĞĞ·û
		//ÎÄ¼şÖĞ»»ĞĞ·ûÊÇÓÉ'\r'ºÍ'\n'×é³É
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
	    }//½øĞĞ¶ÔÓ¦µÄÊä³ö 
}
void currsion(string path,char *c)
{//path×÷Îªµ±Ç°µÄÂ·¾¶ 
	struct _finddata_t filefind; 
	string curr = path + "\\*.*";// ĞŞ¸Ä´Ë´¦¸Ä±äËÑË÷Ìõ¼ş
	int handle;
	if((handle = _findfirst(curr.c_str(), &filefind)) != -1)
	{
		while(! _findnext(handle, &filefind))//±éÀúµ±Ç°Ä¿Â¼ÖĞµÄËùÓĞÎÄ¼şºÍÎÄ¼ş¼Ğ 
		{
			if(strcmp(filefind.name, "..") == 0)
				continue;
			if((_A_SUBDIR == filefind.attrib))//ÊÇ×ÓÄ¿Â¼
			{
				printf("[Dir]:\t%s\n", filefind.name);
				curr = path + "\\" + filefind.name;
				currsion(curr,c);// µİ¹é±éÀú×ÓÄ¿Â¼
			}
			else
			{
				char ext[_MAX_EXT];  
				_splitpath(filefind.name,NULL,NULL,NULL,ext);//»ñÈ¡ÎÄ¼şºó×º 
				if( (strcmp(".txt",ext)==0&&strcmp(c,"*.txt")==0)||(strcmp(".c",ext)==0&&strcmp(c,"*.c")==0))
				{
				 printf("[File]:\t%s\n", filefind.name);
				 string x=filefind.name;
				 x=path+"\\"+x;//´ò¿ªµ±Ç°ÎÄ¼şµÄÂ·¾¶ 
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
	memset(s,0,sizeof(s));//Í¨¹ıargcÀ´ÅĞ¶ÏÊÇÄÇÖÖÊäÈë
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
          	string path(".");//.¾ÍÊÇµ±Ç°Â·¾¶ 
	        currsion(path,argv[3]);
    }
    else if(argc==2)
    system("GUI.exe");
    else
    printf("INPUT ERROR\n");
return 0;
}

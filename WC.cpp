#include<stdio.h>
#include<io.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>

using namespace std;

char s[5];
void print(FILE*fp)//���ļ����ݽ��м����ĺ��� 
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
    int annotationflag=0;//��ʼ������ 
		while (!feof(fp))
		{//��ȡ�ļ�ֱ����β 
			i=fgetc(fp);
			if(i=='\r'||i=='�')
			    continue;//����\r���ļ���β��ʶ��
			character+=1;//ͳ���ַ��� 
			if(i!=' '&&i!='\t'&&i!='\n')
				this_lines_character+=1;
			if(i==j&&j=='/')
				{
				   if(this_lines_character<4)
				   annotationflag=1;//�ж���һ���Ƿ���ע�� 
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
			}//�ڻ��к��ж��ǿ��л���ע�ͻ��Ǵ����� 
			if((i>='a'&&i<='z')||(i>='A'&&i<='Z'))
				wordflag=1;
			else {
				if(wordflag==1) {
					wordflag=0;
					word+=1;
				}
			}//�жϵ��� 
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
		}//C�ļ���ֱ����ĩβ�����������з�
		//�ļ��л��з�����'\r'��'\n'���
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
	    }//���ж�Ӧ����� 
}
void currsion(string path,char *c)
{//path��Ϊ��ǰ��·�� 
	struct _finddata_t filefind; 
	string curr = path + "\\*.*";// �޸Ĵ˴��ı���������
	int handle;
	if((handle = _findfirst(curr.c_str(), &filefind)) != -1)
	{
		while(! _findnext(handle, &filefind))//������ǰĿ¼�е������ļ����ļ��� 
		{
			if(strcmp(filefind.name, "..") == 0)
				continue;
			if((_A_SUBDIR == filefind.attrib))//����Ŀ¼
			{
				printf("[Dir]:\t%s\n", filefind.name);
				curr = path + "\\" + filefind.name;
				currsion(curr,c);// �ݹ������Ŀ¼
			}
			else
			{
				char ext[_MAX_EXT];  
				_splitpath(filefind.name,NULL,NULL,NULL,ext);//��ȡ�ļ���׺ 
				if( (strcmp(".txt",ext)==0&&strcmp(c,"*.txt")==0)||(strcmp(".c",ext)==0&&strcmp(c,"*.c")==0))
				{
				 printf("[File]:\t%s\n", filefind.name);
				 string x=filefind.name;
				 x=path+"\\"+x;//�򿪵�ǰ�ļ���·�� 
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
	memset(s,0,sizeof(s));//ͨ��argc���ж�����������
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
          	string path(".");//.���ǵ�ǰ·�� 
	        currsion(path,argv[3]);
    }
    else if(argc==2)
    system("GUI.exe");
    else
    printf("INPUT ERROR\n");
return 0;
}

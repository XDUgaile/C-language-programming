#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
typedef struct chsystem//ͨѶ¼�ṹ��
{
	char name[15];//����
	char tel[20];//�ֻ�
	char tecent[15];//qq����
	char email[20];//����
}cs;
 
typedef struct pcs//ͨѶ¼�ڵ�
{
	cs chat;
	pcs* next;
}*ptcs;
ptcs head=(ptcs)malloc(sizeof(pcs));	//��̬�洢�ռ� 
 
int menu_select()//����ѡ���
{
	char c;
	do
	{
		system("cls");//cls��������ָ�����Ļ
		printf("\n\t\t*********ͨѶ¼����ϵͳ*********\n");
		printf("\t\t��------------------------------��\n");
		printf("\t\t��        1.�����ϵ��          ��\n");
		printf("\t\t��        2.ɾ����ϵ��          ��\n");
		printf("\t\t��        3.�����ϵ���б�      ��\n");
		printf("\t\t��        4.��ѯ��ϵ��          ��\n");
		printf("\t\t��        5.д���ļ�            ��\n");
		printf("\t\t��        6.��ȡ�ļ�            ��\n");
		printf("\t\t��        0.�˳�                ��\n");
		printf("\t\t��------------------------------��\n");
		printf("\t\t����ѡ��(0-6):");    
		c=getchar(); 
	}while(c<'0'||c>'6');//��������Ƿ���Ϲ淶
	return(c-'0');
}
 
int cala(char *p)//�����ַ�������
{
	int i,n=0;
	for(i=0;p[i]!='\0';i++)n++;
	return n;
}
 
void enter()//�����ϵ��
{
	int t,n,a;
	char flag='y';
	ptcs p=head,q;
	while(p->next)p=p->next;
	while(flag!='n'&&flag!='N')
	{
		q=(ptcs)malloc(sizeof(pcs));
		p->next=q;
		p=q;
		q->next=NULL;
		printf("\n\t\t������:\n");
		printf("\t\t����:");//��������
		scanf("\t\t%s",q->chat.name);
		printf("\t\t�ֻ�����:");//�����ֻ���
		scanf("\t\t%s",q->chat.tel);
		printf("\t\tQQ��:");//����QQ��
		scanf("\t\t%s",q->chat.tecent);	
		printf("\t\t��������:");//��������
		scanf("\t\t%s",q->chat.email);
		printf("\n\t\t�Ƿ�������?(Y/N)");      
		scanf("\t\t%c",&flag);  
	}
}
 
void search()//��ѯ��ϵ��
{
	int m,n;
	char flag='y';
	ptcs p=head->next;
	while(flag!='n'&&flag!='N')
	{
		printf("\n\t\t*************��ѯ��ʽ*************\n");
		printf("\t\t��-------------------------------��\n");
		printf("\t\t��          1.��������           ��\n");
		printf("\t\t��          2.�����ֻ���         ��\n");
		printf("\t\t��          3.����QQ����         ��\n");
		printf("\t\t��          4.����               ��\n");
		printf("\t\t��-------------------------------��\n");
		printf("\n\t\t��ѡ���ѯ��ʽ:");
		scanf("\t\t%d",&m);//ѡ���ѯ��ʽ
		do
		{
			n=0;
			if(m!=1&&m!=2&&m!=3&&m!=4)
			{	
				n=1;
				printf("\t\t������Ĳ�ѯ��ʽ������,����������:");
				scanf("\t\t%d",&m);//ѡ���ѯ��ʽ
			}
		}while(n);
		if(!p)
		{
			printf("\t\t��ͨѶ¼Ϊ��!\n");
		}
		if(1==m)
		{
			char nm[15];
			p=head->next;
			printf("\t\t��������Ҫ��ѯ����ϵ��:");
			scanf("\t\t%s",nm);
			while(p!=NULL&&strcmp(p->chat.name,nm)!=0)p=p->next;
			if(!p)
			{
				printf("\t\t��Ҫ��ѯ����ϵ�˲�����!\n");
				printf("\t\t�Ƿ������ѯ?(Y/N)");
				scanf("\t\t%c",&flag);
			}
			printf("\t\t�ֻ�����:%s\n",p->chat.tel);
			printf("\t\tqq��:%s\n",p->chat.tecent);
			printf("\t\t��������:%s\n",p->chat.email);
		}
		if(2==m)
		{
			char te[20];
			p=head->next;
			printf("\t\t��������Ҫ��ѯ���ֻ�����:");
			scanf("\t\t%s",te);
			while(p!=NULL&&strcmp(p->chat.tel,te)!=0)p=p->next;
			if(!p)
			{
				printf("\t\t��Ҫ��ѯ����ϵ�˲�����!\n");
				printf("\t\t�Ƿ������ѯ?(Y/N)");
				scanf("\t\t%c",&flag);
			}
			printf("\t\t����:%s\n",p->chat.name);
			printf("\t\tqq��:%s\n",p->chat.tecent);
			printf("\t\t��������:%s\n",p->chat.email);
		}
		if(3==m)
		{
			char qq[15];
			p=head->next;
			printf("\t\t��������Ҫ��ѯ��qq��:");
			scanf("\t\t%s",qq);
			while(p!=NULL&&strcmp(p->chat.tecent,qq)!=0)p=p->next;
			if(!p)
			{
				printf("\t\t��Ҫ��ѯ����ϵ�˲�����!\n");
				printf("\t\t�Ƿ������ѯ?(Y/N)");
				scanf("\t\t%c",&flag);
			}
			printf("\t\t����:%s\n",p->chat.name);
			printf("\t\t�ֻ���:%s\n",p->chat.tecent);
			printf("\t\t��������:%s\n",p->chat.email); 
		}
		if(4==m)
		printf("\t\t�Ƿ������ѯ?(Y/N)");
		scanf("\t\t%c",&flag);
	}
}
 
void Del()//ɾ��������Ϣ
{
	char nm[20];
	char flag='y';
	ptcs p=head->next,bh,pre;
	if(!p)
	{
		printf("\t\t��ͨѶ¼Ϊ��!\n");
	}
	while(flag!='n'&&flag!='N')
	{
		p=head->next;
		printf("\t\t��������Ҫɾ������ϵ������:");
		scanf("\t\t%s",nm);
		while(p!=NULL&&strcmp(p->chat.name,nm)!=0)
		{
			pre=p;
			p=p->next;
		}
		if(!p)
		{
			printf("\t\t����ϵ�˲�����!\n");
			printf("\t\t�Ƿ����ɾ��?(Y/N)");
			scanf("\t\t%c",&flag);
		}
		bh=p->next;
		if(p==head->next)head->next=bh;
		else pre->next=bh;
		printf("\t\t����ϵ����ɾ��!\n");
		printf("\t\t�Ƿ����ɾ��?(Y/N)");
		scanf("\t\t%c",&flag);
	}
}

void list()//���ͨѶ¼�б�
{
	ptcs p=head->next;
	if(!p)
	{
		printf("\t\t��ͨѶ¼Ϊ��!\n");
	}
	printf("\n\t\t******************************ͨѶ¼�б�******************************\n");
	printf("\t\t����\t\t�ֻ�����\tQQ����\t\t��������\n");
	printf("\t\t----------------------------------------------------------------------\n");
	while(p)
	{
		printf("\t\t%-16s%-16s%-16s%-20s\n",p->chat.name,p->chat.tel,p->chat.tecent,p->chat.email);
		p=p->next;
		printf("\t\t----------------------------------------------------------------------\n");
	}
}
 
int cacu(ptcs p)//��������ĳ���
{
	int n=0;
	while(p)
	{
		p=p->next;
		n++;
	}
	return n;
}

void save()//������д���ļ�
{
	ptcs p=head->next;
	FILE* fp;
	char filename[30];
	if(!p)
	{
		printf("\t\t��ͨѶ¼Ϊ��!");
	}
	printf("\t\tд�뵽�ļ�!\n");
	printf("\t\t��������д����ļ���:");
	scanf("\t\t%s",filename);
	if((fp=fopen(filename,"a+"))==NULL)
	{
		printf("\t\t�޷����ļ�!\n");
		system("pause");
	}
	fprintf(fp,"******************************ͨѶ¼�б�******************************\n");
	fprintf(fp,"����\t\t�ֻ�����\tQQ����\t\t��������\n");
	fprintf(fp,"----------------------------------------------------------------------\n");
	while(p)
	{
		fprintf(fp,"%-16s%-16s%-16s%-20s\n",p->chat.name,p->chat.tel,p->chat.tecent,p->chat.email);
		p=p->next;
		fprintf(fp,"----------------------------------------------------------------------\n");
	}
	fprintf(fp,"\n******************************��%d����ϵ��******************************\n",cacu(head->next));
	fclose(fp);                                         //�ر��ļ�   
	printf("\t Saving file!\n"); 
}
 
void load()//��ȡ�ļ�
{
	char str[100], filename[30];
	FILE* fp;
	printf("\t\t��ȡ�ļ�!\n");
	printf("\t\t��������д����ļ���:");
	scanf("\t\t%s",filename);
	if((fp=fopen(filename,"a+"))==NULL)
	{
		printf("\t\t�޷����ļ�!\n");
		system("pause");//pause��������ָ��ͣ���ļ��Ĵ�����ʾ��Ϣ
	}
	while((fgets(str,100,fp))!=NULL)  
    {  
		printf("\t\t%s",str);  
    }
}

int main()
{
	head->next=NULL;
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
			printf("\n\t\t��Ӽ�¼��ͨѶ¼\n"); //��Ӽ�¼
			enter();
			system("pause");
			break;
		case 2:
			printf("\n\t\t��ͨѶ¼��ɾ����ϵ��\n");	//ɾ����ϵ�� 
			Del();
			system("pause");
			break;
		case 3:
			printf("\n\t\t���ͨѶ¼�б�\n");	//�����ϵ���б� 
			list();
			system("pause");
			break;		
		case 4:
			printf("\n\t\t��ͨѶ¼�в�����ϵ��\n"); 	//������ϵ�� 
			search();
			system("pause");
			break;
		case 5:
			printf("\n\t\tд���ļ�\n");	//����ϵ��д�뵽�ļ� 
			save();
			system("pause");
			break;
		case 6:
			printf("\n\t\t��ȡ�ļ�\n");	//��ȡ��д����ļ� 
			load();
			system("pause");
			break;
		case 0:    
			printf("\n\t\tллʹ�ã��ټ�!\n");  //��������    
			printf("\n\t\t");    
			system("pause");    
			exit(0);    
		}
	}
	return 0;
}

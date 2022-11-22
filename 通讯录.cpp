#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
typedef struct chsystem//通讯录结构体
{
	char name[15];//姓名
	char tel[20];//手机
	char tecent[15];//qq号码
	char email[20];//邮箱
}cs;
 
typedef struct pcs//通讯录节点
{
	cs chat;
	pcs* next;
}*ptcs;
ptcs head=(ptcs)malloc(sizeof(pcs));	//动态存储空间 
 
int menu_select()//功能选择框
{
	char c;
	do
	{
		system("cls");//cls函数，意指清空屏幕
		printf("\n\t\t*********通讯录管理系统*********\n");
		printf("\t\t┌------------------------------┐\n");
		printf("\t\t│        1.添加联系人          │\n");
		printf("\t\t│        2.删除联系人          │\n");
		printf("\t\t│        3.输出联系人列表      │\n");
		printf("\t\t│        4.查询联系人          │\n");
		printf("\t\t│        5.写入文件            │\n");
		printf("\t\t│        6.读取文件            │\n");
		printf("\t\t│        0.退出                │\n");
		printf("\t\t└------------------------------┘\n");
		printf("\t\t请您选择(0-6):");    
		c=getchar(); 
	}while(c<'0'||c>'6');//检查输入是否符合规范
	return(c-'0');
}
 
int cala(char *p)//计算字符串长度
{
	int i,n=0;
	for(i=0;p[i]!='\0';i++)n++;
	return n;
}
 
void enter()//添加联系人
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
		printf("\n\t\t请输入:\n");
		printf("\t\t姓名:");//输入姓名
		scanf("\t\t%s",q->chat.name);
		printf("\t\t手机号码:");//输入手机号
		scanf("\t\t%s",q->chat.tel);
		printf("\t\tQQ号:");//输入QQ号
		scanf("\t\t%s",q->chat.tecent);	
		printf("\t\t电子邮箱:");//输入邮箱
		scanf("\t\t%s",q->chat.email);
		printf("\n\t\t是否继续添加?(Y/N)");      
		scanf("\t\t%c",&flag);  
	}
}
 
void search()//查询联系人
{
	int m,n;
	char flag='y';
	ptcs p=head->next;
	while(flag!='n'&&flag!='N')
	{
		printf("\n\t\t*************查询方式*************\n");
		printf("\t\t┌-------------------------------┐\n");
		printf("\t\t│          1.查找姓名           │\n");
		printf("\t\t│          2.查找手机号         │\n");
		printf("\t\t│          3.查找QQ号码         │\n");
		printf("\t\t│          4.返回               │\n");
		printf("\t\t└-------------------------------┘\n");
		printf("\n\t\t请选择查询方式:");
		scanf("\t\t%d",&m);//选择查询方式
		do
		{
			n=0;
			if(m!=1&&m!=2&&m!=3&&m!=4)
			{	
				n=1;
				printf("\t\t您输入的查询方式不存在,请重新输入:");
				scanf("\t\t%d",&m);//选择查询方式
			}
		}while(n);
		if(!p)
		{
			printf("\t\t该通讯录为空!\n");
		}
		if(1==m)
		{
			char nm[15];
			p=head->next;
			printf("\t\t请输入您要查询的联系人:");
			scanf("\t\t%s",nm);
			while(p!=NULL&&strcmp(p->chat.name,nm)!=0)p=p->next;
			if(!p)
			{
				printf("\t\t您要查询的联系人不存在!\n");
				printf("\t\t是否继续查询?(Y/N)");
				scanf("\t\t%c",&flag);
			}
			printf("\t\t手机号码:%s\n",p->chat.tel);
			printf("\t\tqq号:%s\n",p->chat.tecent);
			printf("\t\t电子邮箱:%s\n",p->chat.email);
		}
		if(2==m)
		{
			char te[20];
			p=head->next;
			printf("\t\t请输入您要查询的手机号码:");
			scanf("\t\t%s",te);
			while(p!=NULL&&strcmp(p->chat.tel,te)!=0)p=p->next;
			if(!p)
			{
				printf("\t\t您要查询的联系人不存在!\n");
				printf("\t\t是否继续查询?(Y/N)");
				scanf("\t\t%c",&flag);
			}
			printf("\t\t姓名:%s\n",p->chat.name);
			printf("\t\tqq号:%s\n",p->chat.tecent);
			printf("\t\t电子邮箱:%s\n",p->chat.email);
		}
		if(3==m)
		{
			char qq[15];
			p=head->next;
			printf("\t\t请输入您要查询的qq号:");
			scanf("\t\t%s",qq);
			while(p!=NULL&&strcmp(p->chat.tecent,qq)!=0)p=p->next;
			if(!p)
			{
				printf("\t\t您要查询的联系人不存在!\n");
				printf("\t\t是否继续查询?(Y/N)");
				scanf("\t\t%c",&flag);
			}
			printf("\t\t姓名:%s\n",p->chat.name);
			printf("\t\t手机号:%s\n",p->chat.tecent);
			printf("\t\t电子邮箱:%s\n",p->chat.email); 
		}
		if(4==m)
		printf("\t\t是否继续查询?(Y/N)");
		scanf("\t\t%c",&flag);
	}
}
 
void Del()//删除个人信息
{
	char nm[20];
	char flag='y';
	ptcs p=head->next,bh,pre;
	if(!p)
	{
		printf("\t\t该通讯录为空!\n");
	}
	while(flag!='n'&&flag!='N')
	{
		p=head->next;
		printf("\t\t请输入您要删除的联系人姓名:");
		scanf("\t\t%s",nm);
		while(p!=NULL&&strcmp(p->chat.name,nm)!=0)
		{
			pre=p;
			p=p->next;
		}
		if(!p)
		{
			printf("\t\t该联系人不存在!\n");
			printf("\t\t是否继续删除?(Y/N)");
			scanf("\t\t%c",&flag);
		}
		bh=p->next;
		if(p==head->next)head->next=bh;
		else pre->next=bh;
		printf("\t\t该联系人已删除!\n");
		printf("\t\t是否继续删除?(Y/N)");
		scanf("\t\t%c",&flag);
	}
}

void list()//输出通讯录列表
{
	ptcs p=head->next;
	if(!p)
	{
		printf("\t\t该通讯录为空!\n");
	}
	printf("\n\t\t******************************通讯录列表******************************\n");
	printf("\t\t姓名\t\t手机号码\tQQ号码\t\t电子邮箱\n");
	printf("\t\t----------------------------------------------------------------------\n");
	while(p)
	{
		printf("\t\t%-16s%-16s%-16s%-20s\n",p->chat.name,p->chat.tel,p->chat.tecent,p->chat.email);
		p=p->next;
		printf("\t\t----------------------------------------------------------------------\n");
	}
}
 
int cacu(ptcs p)//计算链表的长度
{
	int n=0;
	while(p)
	{
		p=p->next;
		n++;
	}
	return n;
}

void save()//将数据写入文件
{
	ptcs p=head->next;
	FILE* fp;
	char filename[30];
	if(!p)
	{
		printf("\t\t该通讯录为空!");
	}
	printf("\t\t写入到文件!\n");
	printf("\t\t请输入所写入的文件名:");
	scanf("\t\t%s",filename);
	if((fp=fopen(filename,"a+"))==NULL)
	{
		printf("\t\t无法打开文件!\n");
		system("pause");
	}
	fprintf(fp,"******************************通讯录列表******************************\n");
	fprintf(fp,"姓名\t\t手机号码\tQQ号码\t\t电子邮箱\n");
	fprintf(fp,"----------------------------------------------------------------------\n");
	while(p)
	{
		fprintf(fp,"%-16s%-16s%-16s%-20s\n",p->chat.name,p->chat.tel,p->chat.tecent,p->chat.email);
		p=p->next;
		fprintf(fp,"----------------------------------------------------------------------\n");
	}
	fprintf(fp,"\n******************************共%d个联系人******************************\n",cacu(head->next));
	fclose(fp);                                         //关闭文件   
	printf("\t Saving file!\n"); 
}
 
void load()//读取文件
{
	char str[100], filename[30];
	FILE* fp;
	printf("\t\t读取文件!\n");
	printf("\t\t请输入所写入的文件名:");
	scanf("\t\t%s",filename);
	if((fp=fopen(filename,"a+"))==NULL)
	{
		printf("\t\t无法打开文件!\n");
		system("pause");//pause函数，意指暂停批文件的处理并显示消息
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
			printf("\n\t\t添加记录到通讯录\n"); //添加记录
			enter();
			system("pause");
			break;
		case 2:
			printf("\n\t\t从通讯录中删除联系人\n");	//删除联系人 
			Del();
			system("pause");
			break;
		case 3:
			printf("\n\t\t输出通讯录列表\n");	//输出联系人列表 
			list();
			system("pause");
			break;		
		case 4:
			printf("\n\t\t在通讯录中查找联系人\n"); 	//查找联系人 
			search();
			system("pause");
			break;
		case 5:
			printf("\n\t\t写入文件\n");	//将联系人写入到文件 
			save();
			system("pause");
			break;
		case 6:
			printf("\n\t\t读取文件\n");	//读取已写入的文件 
			load();
			system("pause");
			break;
		case 0:    
			printf("\n\t\t谢谢使用，再见!\n");  //结束程序    
			printf("\n\t\t");    
			system("pause");    
			exit(0);    
		}
	}
	return 0;
}

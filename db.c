#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#define MAXLEN 10//账号密码最大长度

FILE * fp;//数据库文件指针
FILE * fp2;//表文件指针
FILE * fp3;//修改时用的容器

struct datas{
    char one[20];
    char two[20];
    char three[20];
    char four[20];
};


int database_func();

int create_database();
int delete_database();
int use_database();

int table_func();

int create_table();
int delete_table();
int select_data();
int add_data();
int delete_data();
char str1[100];
char str2[100];
char str3[100];
int flag = -1;


int main(){
    int i=0;
    if(i==0){
        while(database_func());//记得加分号,否则他会以为while的循环体是break;实际上循环体是空语句;
    }
    system("cls");
    printf("感谢使用,再见!");
    return 0;
}

int database_func(){//数据库操作菜单
    system("cls");
    //system("color 26");
    int flag=0,func=0;
    printf("功能界面\n");
    printf("============\n");
    printf("1.数据库创建 create database; 	2.数据库删除 drop database;	3.数据库选择 use database\n");
    printf("============\n");
    printf("请输入需要使用的功能:");
 	scanf("%s",&str1);
    scanf("%s",&str2);
  	if(str1[0]=='c'&&str1[1]=='r'&&str1[2]=='e')	flag=1;
	else if(str1[0]=='d'&&str1[1]=='r'&&str1[2]=='o')	flag=2;
	else if(str1[0]=='u'&&str1[1]=='s'&&str1[2]=='e')	flag =3;
	else if(str1[0]=='e'&&str1[1]=='x'&&str1[2]=='i')	flag =4;
//    scanf("%d",&func);
    switch(flag){
        case 1:while(create_database());break;//创建数据库
        case 2:while(delete_database());break;//删除数据库
        case 3:while(use_database());break;//打开数据库
        case 4:exit(0);break;
    }
    system("cls");//使用功能后,判断是否继续使用
    printf("你有以下两个选择\n");
    printf("=================\n");
    printf(" 1.继续使用\n 2.退出程序\n");
    printf("=================\n");
    printf("请输入你的选择:（数字）");
    scanf("%d",&flag);
    if(flag==1){//继续使用
        return 1;
    }
    if(flag==2){//退出
        return 0;
    }
    return 0;
}


//第二层调用,父函数为database_func

int create_database(){//创建数据库
    system("cls");
    int flag=0;
    char db_name[10],db_url[18];
    printf("新建数据库\n");
    printf("=================\n");
    printf("请输入新库的名字(len<10):");
    scanf("%s",db_name);
    strcpy(db_url,"db_");
    strcat(db_url,db_name);
    strcat(db_url,".txt");
    if((fp=fopen(db_url,"r"))==NULL){//判断是否重复建库
        fp=fopen(db_url,"w");
        fclose(fp);//记得!
        printf("创建成功!\n");
        Sleep(1000);//将进程挂起1000ms 
        return 0;//跳出循环
    }
    else{
        system("cls");
        printf("该库已经被创建,或命名错误\n");
        printf("你有以下两个选择\n");
        printf("=================\n");
        printf(" 1.重新创建\n 2.取消创建数据库\n 3.退出程序\n");
        printf("=================\n");
        printf("请输入你的选择:（数字）");
        scanf("%d",&flag);
        if(flag==1){
            return 1;//再次创建
        }
        if(flag==2){
            return 0;//跳出循环
        }
        if(flag==3){
            exit(0);
        }
        else{
            printf("没有该选项!\n结束创建");
            Sleep(1000);
            return 0;
        }
    }
}


int delete_database(){//删除数据库
    system("cls");
    int flag=0;
    char db_name[10],db_url[18],haven[18];
    printf("删除数据库\n");
    printf("=================\n");
    printf("请输入要删除的数据库的名字:");
    scanf("%s",db_name);
    strcpy(db_url,"db_");
    strcat(db_url,db_name);
    strcat(db_url,".txt");
    //遍历删除库
    fp=fopen(db_url,"r");
    while(fscanf(fp,"%s",haven)!=EOF){//防止读入\n用fscanf
        remove(haven);
    }
    fclose(fp);
    if(!(remove(db_url))){//成功返回零
        printf("删除成功!\n");
        Sleep(1000);
        return 0;//跳出循环
    }
    else{
        system("cls");
        printf("%s\n",strerror(errno));
        printf("删除成功！\n"); 
        printf("你有以下两个选择\n");
        printf("=================\n");
        printf(" 1.再次删除\n 2.取消删除数据库\n 3.退出程序\n");
        printf("=================\n");
        printf("请输入你的选择:（数字）");
        scanf("%d",&flag);
        if(flag==1){
            return 1;//再次创建
        }
        if(flag==2){
            return 0;//跳出循环
        }
        if(flag==3){
            exit(0);
        }
        else{
            printf("没有该选项!\n结束删除");
            Sleep(2000);
            return 0;
        }
    }
}


int use_database(){//打开数据库
    system("cls");
    int flag=0;
    char db_name[10],db_url[18];
    printf("打开数据库\n");
    printf("=================\n");
    printf("请输入要打开的数据库的名字:");
    
    scanf("%s",db_name);
    strcpy(db_url,"db_");
    strcat(db_url,db_name);
    strcat(db_url,".txt");
    if((fp=fopen(db_url,"r"))!=NULL){//判断数据库是否存在
        fp=fopen(db_url,"a+");
        printf("成功打开!\n");
        Sleep(1000);
        while(table_func(db_url));
        fclose(fp);//循环的过程中文件一直打开,如果不及时清空缓冲区就一直无法写入
        return 0;//跳出循环
    }
    else{
        system("cls");
        printf("该库已经不存在\n");
        printf("你有以下两个选择\n");
        printf("=================\n");
        printf(" 1.打开另一个\n 2.取消打开数据库\n 3.退出程序\n");
        printf("=================\n");
        printf("请输入你的选择:（数字）");
        scanf("%d",&flag);
        if(flag==1){
            return 1;//再次创建
        }
        if(flag==2){
            return 0;//跳出循环
        }
        if(flag==3){
            exit(0);
        }
        else{
            printf("没有该选项!\n结束创建");
            Sleep(2000);
            return 0;
        }
    }
}


//第三层调用,父函数为use_database

int table_func(char * db_url){//表操作菜单
    system("cls");
    int flag=0,func=0;
    char db_name[13]={0};
    strcpy(db_name,strtok(db_url,".txt"));
    printf("%s库\n",db_name);
    printf("============\n");
    printf(" 1.创建表create table\n 2.删除表drop table\n 3.显示信息info table\n 4.插入信息insert into\n 5.删除信息delete from\n 6.查询信息select information\n 7.退出程序exit grammer\n");
    printf("============\n");
    printf("请输入需要使用的功能:");
   	scanf("%s", &str1);
   	scanf("%s", &str2);
    if(str1[0]=='c'&&str1[1]=='r'&&str1[2]=='e')	flag=1;
	else if(str1[0]=='d'&&str1[1]=='r'&&str1[2]=='o')	flag=2;
	else if(str1[0]=='i'&&str1[1]=='n'&&str1[2]=='f')	flag=3;
	else if(str1[0]=='i'&&str1[1]=='n'&&str1[2]=='s')	flag=4;
	else if(str1[0]=='d'&&str1[1]=='e'&&str1[2]=='l')	flag=5;
	else if(str1[0]=='s'&&str1[1]=='e'&&str1[2]=='l')	flag=3;
	else if(str1[0]=='e'&&str1[1]=='x'&&str1[2]=='i') 	flag=6;
    switch(flag){
        case 1:while(create_table(db_url));break;//创建表
        case 2:while(delete_table(db_url));break;//删除表
        case 3:while(select_data(db_url));break;//查询数据
        case 4:while(add_data(db_url));break;//增加数据
        case 5:while(delete_data(db_url));break;//删除数据
        case 6:exit(0);break;
    }
    //使用功能后,判断是否继续使用
    system("cls");
    printf("你有以下两个选择\n");
    printf("=================\n");
    printf(" 1.继续使用\n 2.退出库\n 3.退出程序\n");
    printf("=================\n");
    printf("请输入你的选择:（数字）");
    scanf("%d",&flag);
    if(flag==1){//继续使用
        return 1;
    }
    if(flag==2){//退出
        return 0;
    }
    if(flag==3){
        exit(0);
    }
    return 0;
}


//第四层调用,父函数为table_func

int create_table(char *db_url){//创建表,和创建库差不多,要把表名放入库文件中
    system("cls");
    int flag=0,n=0,i=0;
    char tb_name[10],tb_url[15];
    fseek(fp,0,SEEK_SET);//将文件光标回到开头,防止多次操作导致光标在文件末尾无法读取到前面的内容
    struct datas data;
    //初始化
    strcpy(data.one,"null");
    strcpy(data.two,"null");
    strcpy(data.three,"null");
    strcpy(data.four,"null");
    printf("新建表\n");
    printf("=================\n");
    printf("请输入新表的名字(len<10):");
    scanf("%s",&tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt");
    if((fp2=fopen(tb_url,"r"))==NULL){//判断是否重复建表
        fp2=fopen(tb_url,"w");
        printf("请输入新表的字段数(<=4):");
        scanf("%d",&n);
        if(n>4){
            printf("对不起,程序无法支持创建这么多字段的表\n");
        }
        else{
            for(i=0;i<n;i++){
                printf("请输入第%d个字段名:",i+1);
                switch(i){
                    case 0:scanf("%s",data.one);break;
                    case 1:scanf("%s",data.two);break;
                    case 2:scanf("%s",data.three);break;
                    case 3:scanf("%s",data.four);break;
                }
            }
        }
        fprintf(fp2,"%d\n",n);
        fprintf(fp2,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four);
        fclose(fp2);
        fflush(stdin);
        fprintf(fp,"%s\n",tb_url);//把表名放进数据库中
        fflush(fp);//清空缓冲区,使表名在
        printf("创建成功!\n");
        Sleep(1000);
        return 0;//跳出循环
    }
    else{
        system("cls");
        printf("该表已经被创建,或命名错误\n");
        printf("你有以下两个选择\n");
        printf("=================\n");
        printf(" 1.重新创建\n 2.取消创建表\n 3.退出程序\n");
        printf("=================\n");
        printf("请输入你的选择:（数字）");
        scanf("%d",&flag);
        if(flag==1){
            return 1;//再次创建
        }
        if(flag==2){
            return 0;//跳出循环
        }
        if(flag==3){
            exit(0);
        }
        else{
            printf("没有该选项!\n结束创建");
            Sleep(2000);
            return 0;
        }
    }
}


int delete_table(char *db_url){
    system("cls");
    int flag=0;
    char tb_name[10],tb_url[15],haven[16];
    fseek(fp,0,SEEK_SET);//将文件光标回到开头,防止多次操作导致光标在文件末尾无法读取到前面的内容
    printf("删除表\n");
    printf("=================\n");
    printf("请输入要删除的表的名字:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");//文件里的tb_url始终有\n跟着
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){//一行一个信息
        if(!(strcmp(haven,tb_url))){//发现匹配表
            if(!(remove(tb_name))){//成功返回零
                printf("删除成功!\n");
                Sleep(2000);
                return 0;//跳出循环
            }
            else{//删除失败
                system("cls");
                printf("删除出错\n");
                printf("你有以下两个选择\n");
                printf("=================\n");
                printf(" 1.重新删除\n 2.结束删除表\n 3.退出程序\n");
                printf("=================\n");
                printf("请输入你的选择:（数字）");
                scanf("%d",&flag);
                if(flag==1){
                    return 1;//再次创建
                }
                if(flag==2){
                    return 0;//跳出循环
                }
                if(flag==3){
                    exit(0);
                }
                else{
                    printf("没有该选项!\n结束删除");
                    return 0;
                }
            }
        }
    }
    //匹配成功的都出去了,匹配失败才会执行下面的语句
    system("cls");
    printf("库里没有这个表");
    printf("你有以下两个选择\n");
    printf("=================\n");
    printf(" 1.删除另一个表\n 2.取消删除表操作\n 3.退出程序\n");
    printf("=================\n");
    printf("请输入你的选择:（数字）");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//再次创建
    }
    if(flag==2){
        return 0;//跳出循环
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("没有该选项!\n结束删除");
        Sleep(2000);
        return 0;
    }
}


int select_data(char *db_url){
    system("cls");
    int flag=0,a;
    struct datas data;
    strcpy(data.one,"null");
    strcpy(data.two,"null");
    strcpy(data.three,"null");
    strcpy(data.four,"null");
    char tb_name[10],tb_url[15],haven[16];
    fseek(fp,0,SEEK_SET);//将文件光标回到开头,防止多次操作导致光标在文件末尾无法读取到前面的内容
    printf("查询表\n");
    printf("=================\n");
    printf("请输入要查询的表的名字:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){//一行一个信息
        if(!strcmp(haven,tb_url)){//发现匹配表
            if((fp2=fopen(tb_name,"r"))!=NULL){//确认表没有被删
                fscanf(fp2,"%d\n",&a);//把字段数读取掉
                while(fscanf(fp2,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four)!=EOF){
                    printf("%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four);
                }
                printf("查询成功!\n");
                fclose(fp2);
                printf("输入任意键继续......");
                getch();//读取任意键,达到暂停的效果
                return 0;//跳出循环
            }
            else{
                system("cls");
                printf("表可能已经被删除\n");
                printf("你有以下两个选择\n");
                printf("=================\n");
                printf(" 1.重新查询\n 2.结束查询表\n 3.退出程序\n");
                printf("=================\n");
                printf("请输入你的选择:（数字）");
                scanf("%d",&flag);
                if(flag==1){
                    return 1;//再次创建
                }
                if(flag==2){
                    return 0;//跳出循环
                }
                if(flag==3){
                    exit(0);
                }
                else{
                    printf("没有该选项!\n结束删除");
                    return 0;
                }
            }
        }
    }
    //匹配成功的都出去了,匹配失败才会执行下面的语句
    system("cls");
    printf("库里没有这个表");
    printf("你有以下两个选择\n");
    printf("=================\n");
    printf(" 1.查询另一个表\n 2.取消查询表操作\n 3.退出程序\n");
    printf("=================\n");
    printf("请输入你的选择:（数字）");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//再次创建
    }
    if(flag==2){
        return 0;//跳出循环
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("没有该选项!\n结束删除");
        Sleep(2000);
        return 0;
    }
}


int add_data(){
    system("cls");
    int flag=0,i=0,n=0;
    struct datas data;
    //初始化结构体
    strcpy(data.one,"null");
    strcpy(data.two,"null");
    strcpy(data.three,"null");
    strcpy(data.four,"null");
    fseek(fp,0,SEEK_SET);//将文件光标回到开头,防止多次操作导致光标在文件末尾无法读取到前面的内容
    char tb_name[10],tb_url[15],haven[16];
    printf("增加数据\n");
    printf("=================\n");
    printf("请输入要增加数据的表的名字:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){//一行一个信息
        if(!strcmp(haven,tb_url)){//发现匹配表
            if((fp2=fopen(tb_name,"a+"))!=NULL){
                fscanf(fp2,"%d\n",&n);
                if(n==0){//如果文件已经被删除
                    system("cls");
                    printf("文件已被删除\n");
                    printf("你有以下两个选择\n");
                    printf("=================\n");
                    printf(" 1.重新查询\n 2.结束查询表\n 3.退出程序\n");
                    printf("=================\n");
                    printf("请输入你的选择:（数字）");
                    scanf("%d",&flag);
                    if(flag==1){
                        return 1;//再次创建
                    }
                    if(flag==2){
                        return 0;//跳出循环
                    }
                    if(flag==3){
                        exit(0);
                    }
                    else{
                        printf("没有该选项!\n结束删除");
                        return 0;
                    }
                }
                for(i=0;i<n;i++){
                    printf("请输入第%d列的数据:",i+1);
                    switch(i){
                        case 0:scanf("%s",data.one);break;
                        case 1:scanf("%s",data.two);break;
                        case 2:scanf("%s",data.three);break;
                        case 3:scanf("%s",data.four);break;
                    }
                }
                fseek(fp2,0,SEEK_END);//读写转换的时候要重新定位光标的位置,否则fprintf会失败返回EOF
                fprintf(fp2,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four);
                printf("添加数据成功!\n");
                fflush(fp2);
                fclose(fp2);
                Sleep(1000);
                return 0;//跳出循环
            }
        }
    }
    //匹配成功的都出去了,匹配失败才会执行下面的语句
    system("cls");
    printf("库里没有这个表");
    printf("你有以下两个选择\n");
    printf("=================\n");
    printf(" 1.查询另一个表\n 2.取消查询表操作\n 3.退出程序\n");
    printf("=================\n");
    printf("请输入你的选择:（数字）");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//再次创建
    }
    if(flag==2){
        return 0;//跳出循环
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("没有该选项!\n结束删除");
        Sleep(2000);
        return 0;
    }
}


int delete_data(){
    system("cls");
    int flag=0,i=1,n,a;//这里初始化i为1
    struct datas data={0};//初始化结构体
    char tb_name[10],tb_url[15],haven[16];
    fseek(fp,0,SEEK_SET);//将文件光标回到开头,防止多次操作导致光标在文件末尾无法读取到前面的内容
    printf("删除数据\n");
    printf("=================\n");
    printf("请输入要删除数据的表的名字:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){
        if(!strcmp(haven,tb_url)){//发现匹配表
            if((fp2=fopen(tb_name,"r"))!=NULL){//只能读,否则数据没了
                fscanf(fp2,"%d\n",&a);
                fp3=fopen("__temp.txt","w");//修改专用文件
                printf("请输入要删除的行号:");
                scanf("%d",&n);
                n=n+1;//此时光标已经到了第二行,确保第两行不会被删掉
                fprintf(fp3,"%d\n",a);
                while(fscanf(fp2,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four)!=EOF){
                    if(i==n){
                        i++;//记得加否则后面都没了
                        continue;
                    }
                    else{
                        fprintf(fp3,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four);
                    }
                    i++;
                }
                fclose(fp2);
                remove(tb_name);//删除旧文件
                fclose(fp3);//注意位置
                rename("__temp.txt",tb_name);
                printf("删除数据成功!\n");
                Sleep(1000);//读取任意键,达到暂停的效果
                return 0;//跳出循环
            }
            else{
                system("cls");
                printf("文件出错\n");
                printf("你有以下两个选择\n");
                printf("=================\n");
                printf(" 1.重新删除\n 2.结束删除表\n 3.退出程序\n");
                printf("=================\n");
                printf("请输入你的选择:");
                scanf("%d",&flag);
                if(flag==1){
                    return 1;//再次创建
                }
                if(flag==2){
                    return 0;//跳出循环
                }
                if(flag==3){
                    exit(0);
                }
                else{
                    printf("没有该选项!\n结束删除");
                    return 0;
                }
            }
        }
    }
    //匹配成功的都出去了,匹配失败才会执行下面的语句
    system("cls");
    printf("库里没有这个表");
    printf("你有以下两个选择\n");
    printf("=================\n");
    printf(" 1.删除另一个表的数据\n 2.取消删除表操作\n 3.退出程序\n");
    printf("=================\n");
    printf("请输入你的选择:");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//再次创建
    }
    if(flag==2){
        return 0;//跳出循环
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("没有该选项!\n结束删除");
        Sleep(2000);
        return 0;
    }
}


int update_data(){
    system("cls");
    int flag=0,i,n,t;
    fseek(fp,0,SEEK_SET);//将文件光标回到开头,防止多次操作导致光标在文件末尾无法读取到前面的内容
    struct datas data;
    struct datas data2;
    //初始化结构体
    strcpy(data.one,"null");
    strcpy(data.two,"null");
    strcpy(data.three,"null");
    strcpy(data.four,"null");
    strcpy(data2.one,"null");
    strcpy(data2.two,"null");
    strcpy(data2.three,"null");
    strcpy(data2.four,"null");
    char tb_name[10],tb_url[15],haven[16];
    printf("修改数据\n");
    printf("=================\n");
    printf("请输入要修改数据的表的名字:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){
        if(!strcmp(haven,tb_url)){//发现匹配表
            if((fp2=fopen(tb_name,"r"))!=NULL){//只读
                fp3=fopen("__temp.txt","w");//修改专用文件
                printf("请输入要修改的行号:");
                scanf("%d",&n);
                fscanf(fp2,"%d\n",&t);
                fprintf(fp3,"%d\n",t);
                n++;//防止第二行被改
                for(i=0;i<t;i++){
                    printf("请输入第%d个字段名:",i+1);
                    switch(i){
                        case 0:scanf("%s",data2.one);break;
                        case 1:scanf("%s",data2.two);break;
                        case 2:scanf("%s",data2.three);break;
                        case 3:scanf("%s",data2.four);break;
                    }
                }
                i=1;//对齐
                while(fscanf(fp2,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four)!=EOF){
                    if(i==n){
                        fprintf(fp3,"%22s%22s%22s%22s\n",data2.one,data2.two,data2.three,data2.four);
                    }
                    else{
                        fprintf(fp3,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four);
                    }
                    i++;
                }
                fclose(fp2);
                remove(tb_name);//删除旧文件
                fclose(fp3);//注意顺序
                rename("__temp.txt",tb_name);//重命名
                printf("修改数据成功!\n");
                Sleep(1000);//读取任意键,达到暂停的效果
                return 0;//跳出循环
            }
            else{
                system("cls");
                printf("文件出错\n");
                printf("你有以下两个选择\n");
                printf("=================\n");
                printf(" 1.重新修改\n 2.结束修改表\n 3.退出程序\n");
                printf("=================\n");
                printf("请输入你的选择:");
                scanf("%d",&flag);
                if(flag==1){
                    return 1;//再次创建
                }
                if(flag==2){
                    return 0;//跳出循环
                }
                if(flag==3){
                    exit(0);
                }
                else{
                    printf("没有该选项!\n结束修改");
                    return 0;
                }
            }
        }
    }
    //匹配成功的都出去了,匹配失败才会执行下面的语句
    system("cls");
    printf("库里没有这个表");
    printf("你有以下两个选择\n");
    printf("=================\n");
    printf(" 1.修改另一个表的数据\n 2.取消修改表操作\n 3.退出程序\n");
    printf("=================\n");
    printf("请输入你的选择:");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//再次创建
    }
    if(flag==2){
        return 0;//跳出循环
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("没有该选项!\n结束修改");
        Sleep(2000);
        return 0;
    }
}


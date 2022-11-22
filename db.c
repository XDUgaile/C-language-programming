#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#define MAXLEN 10//�˺�������󳤶�

FILE * fp;//���ݿ��ļ�ָ��
FILE * fp2;//���ļ�ָ��
FILE * fp3;//�޸�ʱ�õ�����

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
        while(database_func());//�ǵüӷֺ�,����������Ϊwhile��ѭ������break;ʵ����ѭ�����ǿ����;
    }
    system("cls");
    printf("��лʹ��,�ټ�!");
    return 0;
}

int database_func(){//���ݿ�����˵�
    system("cls");
    //system("color 26");
    int flag=0,func=0;
    printf("���ܽ���\n");
    printf("============\n");
    printf("1.���ݿⴴ�� create database; 	2.���ݿ�ɾ�� drop database;	3.���ݿ�ѡ�� use database\n");
    printf("============\n");
    printf("��������Ҫʹ�õĹ���:");
 	scanf("%s",&str1);
    scanf("%s",&str2);
  	if(str1[0]=='c'&&str1[1]=='r'&&str1[2]=='e')	flag=1;
	else if(str1[0]=='d'&&str1[1]=='r'&&str1[2]=='o')	flag=2;
	else if(str1[0]=='u'&&str1[1]=='s'&&str1[2]=='e')	flag =3;
	else if(str1[0]=='e'&&str1[1]=='x'&&str1[2]=='i')	flag =4;
//    scanf("%d",&func);
    switch(flag){
        case 1:while(create_database());break;//�������ݿ�
        case 2:while(delete_database());break;//ɾ�����ݿ�
        case 3:while(use_database());break;//�����ݿ�
        case 4:exit(0);break;
    }
    system("cls");//ʹ�ù��ܺ�,�ж��Ƿ����ʹ��
    printf("������������ѡ��\n");
    printf("=================\n");
    printf(" 1.����ʹ��\n 2.�˳�����\n");
    printf("=================\n");
    printf("���������ѡ��:�����֣�");
    scanf("%d",&flag);
    if(flag==1){//����ʹ��
        return 1;
    }
    if(flag==2){//�˳�
        return 0;
    }
    return 0;
}


//�ڶ������,������Ϊdatabase_func

int create_database(){//�������ݿ�
    system("cls");
    int flag=0;
    char db_name[10],db_url[18];
    printf("�½����ݿ�\n");
    printf("=================\n");
    printf("�������¿������(len<10):");
    scanf("%s",db_name);
    strcpy(db_url,"db_");
    strcat(db_url,db_name);
    strcat(db_url,".txt");
    if((fp=fopen(db_url,"r"))==NULL){//�ж��Ƿ��ظ�����
        fp=fopen(db_url,"w");
        fclose(fp);//�ǵ�!
        printf("�����ɹ�!\n");
        Sleep(1000);//�����̹���1000ms 
        return 0;//����ѭ��
    }
    else{
        system("cls");
        printf("�ÿ��Ѿ�������,����������\n");
        printf("������������ѡ��\n");
        printf("=================\n");
        printf(" 1.���´���\n 2.ȡ���������ݿ�\n 3.�˳�����\n");
        printf("=================\n");
        printf("���������ѡ��:�����֣�");
        scanf("%d",&flag);
        if(flag==1){
            return 1;//�ٴδ���
        }
        if(flag==2){
            return 0;//����ѭ��
        }
        if(flag==3){
            exit(0);
        }
        else{
            printf("û�и�ѡ��!\n��������");
            Sleep(1000);
            return 0;
        }
    }
}


int delete_database(){//ɾ�����ݿ�
    system("cls");
    int flag=0;
    char db_name[10],db_url[18],haven[18];
    printf("ɾ�����ݿ�\n");
    printf("=================\n");
    printf("������Ҫɾ�������ݿ������:");
    scanf("%s",db_name);
    strcpy(db_url,"db_");
    strcat(db_url,db_name);
    strcat(db_url,".txt");
    //����ɾ����
    fp=fopen(db_url,"r");
    while(fscanf(fp,"%s",haven)!=EOF){//��ֹ����\n��fscanf
        remove(haven);
    }
    fclose(fp);
    if(!(remove(db_url))){//�ɹ�������
        printf("ɾ���ɹ�!\n");
        Sleep(1000);
        return 0;//����ѭ��
    }
    else{
        system("cls");
        printf("%s\n",strerror(errno));
        printf("ɾ���ɹ���\n"); 
        printf("������������ѡ��\n");
        printf("=================\n");
        printf(" 1.�ٴ�ɾ��\n 2.ȡ��ɾ�����ݿ�\n 3.�˳�����\n");
        printf("=================\n");
        printf("���������ѡ��:�����֣�");
        scanf("%d",&flag);
        if(flag==1){
            return 1;//�ٴδ���
        }
        if(flag==2){
            return 0;//����ѭ��
        }
        if(flag==3){
            exit(0);
        }
        else{
            printf("û�и�ѡ��!\n����ɾ��");
            Sleep(2000);
            return 0;
        }
    }
}


int use_database(){//�����ݿ�
    system("cls");
    int flag=0;
    char db_name[10],db_url[18];
    printf("�����ݿ�\n");
    printf("=================\n");
    printf("������Ҫ�򿪵����ݿ������:");
    
    scanf("%s",db_name);
    strcpy(db_url,"db_");
    strcat(db_url,db_name);
    strcat(db_url,".txt");
    if((fp=fopen(db_url,"r"))!=NULL){//�ж����ݿ��Ƿ����
        fp=fopen(db_url,"a+");
        printf("�ɹ���!\n");
        Sleep(1000);
        while(table_func(db_url));
        fclose(fp);//ѭ���Ĺ������ļ�һֱ��,�������ʱ��ջ�������һֱ�޷�д��
        return 0;//����ѭ��
    }
    else{
        system("cls");
        printf("�ÿ��Ѿ�������\n");
        printf("������������ѡ��\n");
        printf("=================\n");
        printf(" 1.����һ��\n 2.ȡ�������ݿ�\n 3.�˳�����\n");
        printf("=================\n");
        printf("���������ѡ��:�����֣�");
        scanf("%d",&flag);
        if(flag==1){
            return 1;//�ٴδ���
        }
        if(flag==2){
            return 0;//����ѭ��
        }
        if(flag==3){
            exit(0);
        }
        else{
            printf("û�и�ѡ��!\n��������");
            Sleep(2000);
            return 0;
        }
    }
}


//���������,������Ϊuse_database

int table_func(char * db_url){//������˵�
    system("cls");
    int flag=0,func=0;
    char db_name[13]={0};
    strcpy(db_name,strtok(db_url,".txt"));
    printf("%s��\n",db_name);
    printf("============\n");
    printf(" 1.������create table\n 2.ɾ����drop table\n 3.��ʾ��Ϣinfo table\n 4.������Ϣinsert into\n 5.ɾ����Ϣdelete from\n 6.��ѯ��Ϣselect information\n 7.�˳�����exit grammer\n");
    printf("============\n");
    printf("��������Ҫʹ�õĹ���:");
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
        case 1:while(create_table(db_url));break;//������
        case 2:while(delete_table(db_url));break;//ɾ����
        case 3:while(select_data(db_url));break;//��ѯ����
        case 4:while(add_data(db_url));break;//��������
        case 5:while(delete_data(db_url));break;//ɾ������
        case 6:exit(0);break;
    }
    //ʹ�ù��ܺ�,�ж��Ƿ����ʹ��
    system("cls");
    printf("������������ѡ��\n");
    printf("=================\n");
    printf(" 1.����ʹ��\n 2.�˳���\n 3.�˳�����\n");
    printf("=================\n");
    printf("���������ѡ��:�����֣�");
    scanf("%d",&flag);
    if(flag==1){//����ʹ��
        return 1;
    }
    if(flag==2){//�˳�
        return 0;
    }
    if(flag==3){
        exit(0);
    }
    return 0;
}


//���Ĳ����,������Ϊtable_func

int create_table(char *db_url){//������,�ʹ�������,Ҫ�ѱ���������ļ���
    system("cls");
    int flag=0,n=0,i=0;
    char tb_name[10],tb_url[15];
    fseek(fp,0,SEEK_SET);//���ļ����ص���ͷ,��ֹ��β������¹�����ļ�ĩβ�޷���ȡ��ǰ�������
    struct datas data;
    //��ʼ��
    strcpy(data.one,"null");
    strcpy(data.two,"null");
    strcpy(data.three,"null");
    strcpy(data.four,"null");
    printf("�½���\n");
    printf("=================\n");
    printf("�������±������(len<10):");
    scanf("%s",&tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt");
    if((fp2=fopen(tb_url,"r"))==NULL){//�ж��Ƿ��ظ�����
        fp2=fopen(tb_url,"w");
        printf("�������±���ֶ���(<=4):");
        scanf("%d",&n);
        if(n>4){
            printf("�Բ���,�����޷�֧�ִ�����ô���ֶεı�\n");
        }
        else{
            for(i=0;i<n;i++){
                printf("�������%d���ֶ���:",i+1);
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
        fprintf(fp,"%s\n",tb_url);//�ѱ����Ž����ݿ���
        fflush(fp);//��ջ�����,ʹ������
        printf("�����ɹ�!\n");
        Sleep(1000);
        return 0;//����ѭ��
    }
    else{
        system("cls");
        printf("�ñ��Ѿ�������,����������\n");
        printf("������������ѡ��\n");
        printf("=================\n");
        printf(" 1.���´���\n 2.ȡ��������\n 3.�˳�����\n");
        printf("=================\n");
        printf("���������ѡ��:�����֣�");
        scanf("%d",&flag);
        if(flag==1){
            return 1;//�ٴδ���
        }
        if(flag==2){
            return 0;//����ѭ��
        }
        if(flag==3){
            exit(0);
        }
        else{
            printf("û�и�ѡ��!\n��������");
            Sleep(2000);
            return 0;
        }
    }
}


int delete_table(char *db_url){
    system("cls");
    int flag=0;
    char tb_name[10],tb_url[15],haven[16];
    fseek(fp,0,SEEK_SET);//���ļ����ص���ͷ,��ֹ��β������¹�����ļ�ĩβ�޷���ȡ��ǰ�������
    printf("ɾ����\n");
    printf("=================\n");
    printf("������Ҫɾ���ı������:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");//�ļ����tb_urlʼ����\n����
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){//һ��һ����Ϣ
        if(!(strcmp(haven,tb_url))){//����ƥ���
            if(!(remove(tb_name))){//�ɹ�������
                printf("ɾ���ɹ�!\n");
                Sleep(2000);
                return 0;//����ѭ��
            }
            else{//ɾ��ʧ��
                system("cls");
                printf("ɾ������\n");
                printf("������������ѡ��\n");
                printf("=================\n");
                printf(" 1.����ɾ��\n 2.����ɾ����\n 3.�˳�����\n");
                printf("=================\n");
                printf("���������ѡ��:�����֣�");
                scanf("%d",&flag);
                if(flag==1){
                    return 1;//�ٴδ���
                }
                if(flag==2){
                    return 0;//����ѭ��
                }
                if(flag==3){
                    exit(0);
                }
                else{
                    printf("û�и�ѡ��!\n����ɾ��");
                    return 0;
                }
            }
        }
    }
    //ƥ��ɹ��Ķ���ȥ��,ƥ��ʧ�ܲŻ�ִ����������
    system("cls");
    printf("����û�������");
    printf("������������ѡ��\n");
    printf("=================\n");
    printf(" 1.ɾ����һ����\n 2.ȡ��ɾ�������\n 3.�˳�����\n");
    printf("=================\n");
    printf("���������ѡ��:�����֣�");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//�ٴδ���
    }
    if(flag==2){
        return 0;//����ѭ��
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("û�и�ѡ��!\n����ɾ��");
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
    fseek(fp,0,SEEK_SET);//���ļ����ص���ͷ,��ֹ��β������¹�����ļ�ĩβ�޷���ȡ��ǰ�������
    printf("��ѯ��\n");
    printf("=================\n");
    printf("������Ҫ��ѯ�ı������:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){//һ��һ����Ϣ
        if(!strcmp(haven,tb_url)){//����ƥ���
            if((fp2=fopen(tb_name,"r"))!=NULL){//ȷ�ϱ�û�б�ɾ
                fscanf(fp2,"%d\n",&a);//���ֶ�����ȡ��
                while(fscanf(fp2,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four)!=EOF){
                    printf("%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four);
                }
                printf("��ѯ�ɹ�!\n");
                fclose(fp2);
                printf("�������������......");
                getch();//��ȡ�����,�ﵽ��ͣ��Ч��
                return 0;//����ѭ��
            }
            else{
                system("cls");
                printf("������Ѿ���ɾ��\n");
                printf("������������ѡ��\n");
                printf("=================\n");
                printf(" 1.���²�ѯ\n 2.������ѯ��\n 3.�˳�����\n");
                printf("=================\n");
                printf("���������ѡ��:�����֣�");
                scanf("%d",&flag);
                if(flag==1){
                    return 1;//�ٴδ���
                }
                if(flag==2){
                    return 0;//����ѭ��
                }
                if(flag==3){
                    exit(0);
                }
                else{
                    printf("û�и�ѡ��!\n����ɾ��");
                    return 0;
                }
            }
        }
    }
    //ƥ��ɹ��Ķ���ȥ��,ƥ��ʧ�ܲŻ�ִ����������
    system("cls");
    printf("����û�������");
    printf("������������ѡ��\n");
    printf("=================\n");
    printf(" 1.��ѯ��һ����\n 2.ȡ����ѯ�����\n 3.�˳�����\n");
    printf("=================\n");
    printf("���������ѡ��:�����֣�");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//�ٴδ���
    }
    if(flag==2){
        return 0;//����ѭ��
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("û�и�ѡ��!\n����ɾ��");
        Sleep(2000);
        return 0;
    }
}


int add_data(){
    system("cls");
    int flag=0,i=0,n=0;
    struct datas data;
    //��ʼ���ṹ��
    strcpy(data.one,"null");
    strcpy(data.two,"null");
    strcpy(data.three,"null");
    strcpy(data.four,"null");
    fseek(fp,0,SEEK_SET);//���ļ����ص���ͷ,��ֹ��β������¹�����ļ�ĩβ�޷���ȡ��ǰ�������
    char tb_name[10],tb_url[15],haven[16];
    printf("��������\n");
    printf("=================\n");
    printf("������Ҫ�������ݵı������:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){//һ��һ����Ϣ
        if(!strcmp(haven,tb_url)){//����ƥ���
            if((fp2=fopen(tb_name,"a+"))!=NULL){
                fscanf(fp2,"%d\n",&n);
                if(n==0){//����ļ��Ѿ���ɾ��
                    system("cls");
                    printf("�ļ��ѱ�ɾ��\n");
                    printf("������������ѡ��\n");
                    printf("=================\n");
                    printf(" 1.���²�ѯ\n 2.������ѯ��\n 3.�˳�����\n");
                    printf("=================\n");
                    printf("���������ѡ��:�����֣�");
                    scanf("%d",&flag);
                    if(flag==1){
                        return 1;//�ٴδ���
                    }
                    if(flag==2){
                        return 0;//����ѭ��
                    }
                    if(flag==3){
                        exit(0);
                    }
                    else{
                        printf("û�и�ѡ��!\n����ɾ��");
                        return 0;
                    }
                }
                for(i=0;i<n;i++){
                    printf("�������%d�е�����:",i+1);
                    switch(i){
                        case 0:scanf("%s",data.one);break;
                        case 1:scanf("%s",data.two);break;
                        case 2:scanf("%s",data.three);break;
                        case 3:scanf("%s",data.four);break;
                    }
                }
                fseek(fp2,0,SEEK_END);//��дת����ʱ��Ҫ���¶�λ����λ��,����fprintf��ʧ�ܷ���EOF
                fprintf(fp2,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four);
                printf("������ݳɹ�!\n");
                fflush(fp2);
                fclose(fp2);
                Sleep(1000);
                return 0;//����ѭ��
            }
        }
    }
    //ƥ��ɹ��Ķ���ȥ��,ƥ��ʧ�ܲŻ�ִ����������
    system("cls");
    printf("����û�������");
    printf("������������ѡ��\n");
    printf("=================\n");
    printf(" 1.��ѯ��һ����\n 2.ȡ����ѯ�����\n 3.�˳�����\n");
    printf("=================\n");
    printf("���������ѡ��:�����֣�");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//�ٴδ���
    }
    if(flag==2){
        return 0;//����ѭ��
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("û�и�ѡ��!\n����ɾ��");
        Sleep(2000);
        return 0;
    }
}


int delete_data(){
    system("cls");
    int flag=0,i=1,n,a;//�����ʼ��iΪ1
    struct datas data={0};//��ʼ���ṹ��
    char tb_name[10],tb_url[15],haven[16];
    fseek(fp,0,SEEK_SET);//���ļ����ص���ͷ,��ֹ��β������¹�����ļ�ĩβ�޷���ȡ��ǰ�������
    printf("ɾ������\n");
    printf("=================\n");
    printf("������Ҫɾ�����ݵı������:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){
        if(!strcmp(haven,tb_url)){//����ƥ���
            if((fp2=fopen(tb_name,"r"))!=NULL){//ֻ�ܶ�,��������û��
                fscanf(fp2,"%d\n",&a);
                fp3=fopen("__temp.txt","w");//�޸�ר���ļ�
                printf("������Ҫɾ�����к�:");
                scanf("%d",&n);
                n=n+1;//��ʱ����Ѿ����˵ڶ���,ȷ�������в��ᱻɾ��
                fprintf(fp3,"%d\n",a);
                while(fscanf(fp2,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four)!=EOF){
                    if(i==n){
                        i++;//�ǵüӷ�����涼û��
                        continue;
                    }
                    else{
                        fprintf(fp3,"%22s%22s%22s%22s\n",data.one,data.two,data.three,data.four);
                    }
                    i++;
                }
                fclose(fp2);
                remove(tb_name);//ɾ�����ļ�
                fclose(fp3);//ע��λ��
                rename("__temp.txt",tb_name);
                printf("ɾ�����ݳɹ�!\n");
                Sleep(1000);//��ȡ�����,�ﵽ��ͣ��Ч��
                return 0;//����ѭ��
            }
            else{
                system("cls");
                printf("�ļ�����\n");
                printf("������������ѡ��\n");
                printf("=================\n");
                printf(" 1.����ɾ��\n 2.����ɾ����\n 3.�˳�����\n");
                printf("=================\n");
                printf("���������ѡ��:");
                scanf("%d",&flag);
                if(flag==1){
                    return 1;//�ٴδ���
                }
                if(flag==2){
                    return 0;//����ѭ��
                }
                if(flag==3){
                    exit(0);
                }
                else{
                    printf("û�и�ѡ��!\n����ɾ��");
                    return 0;
                }
            }
        }
    }
    //ƥ��ɹ��Ķ���ȥ��,ƥ��ʧ�ܲŻ�ִ����������
    system("cls");
    printf("����û�������");
    printf("������������ѡ��\n");
    printf("=================\n");
    printf(" 1.ɾ����һ���������\n 2.ȡ��ɾ�������\n 3.�˳�����\n");
    printf("=================\n");
    printf("���������ѡ��:");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//�ٴδ���
    }
    if(flag==2){
        return 0;//����ѭ��
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("û�и�ѡ��!\n����ɾ��");
        Sleep(2000);
        return 0;
    }
}


int update_data(){
    system("cls");
    int flag=0,i,n,t;
    fseek(fp,0,SEEK_SET);//���ļ����ص���ͷ,��ֹ��β������¹�����ļ�ĩβ�޷���ȡ��ǰ�������
    struct datas data;
    struct datas data2;
    //��ʼ���ṹ��
    strcpy(data.one,"null");
    strcpy(data.two,"null");
    strcpy(data.three,"null");
    strcpy(data.four,"null");
    strcpy(data2.one,"null");
    strcpy(data2.two,"null");
    strcpy(data2.three,"null");
    strcpy(data2.four,"null");
    char tb_name[10],tb_url[15],haven[16];
    printf("�޸�����\n");
    printf("=================\n");
    printf("������Ҫ�޸����ݵı������:");
    scanf("%s",tb_name);
    strcpy(tb_url,tb_name);
    strcat(tb_url,".txt\n");
    strcat(tb_name,".txt");
    while(fgets(haven,16,fp)!=NULL){
        if(!strcmp(haven,tb_url)){//����ƥ���
            if((fp2=fopen(tb_name,"r"))!=NULL){//ֻ��
                fp3=fopen("__temp.txt","w");//�޸�ר���ļ�
                printf("������Ҫ�޸ĵ��к�:");
                scanf("%d",&n);
                fscanf(fp2,"%d\n",&t);
                fprintf(fp3,"%d\n",t);
                n++;//��ֹ�ڶ��б���
                for(i=0;i<t;i++){
                    printf("�������%d���ֶ���:",i+1);
                    switch(i){
                        case 0:scanf("%s",data2.one);break;
                        case 1:scanf("%s",data2.two);break;
                        case 2:scanf("%s",data2.three);break;
                        case 3:scanf("%s",data2.four);break;
                    }
                }
                i=1;//����
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
                remove(tb_name);//ɾ�����ļ�
                fclose(fp3);//ע��˳��
                rename("__temp.txt",tb_name);//������
                printf("�޸����ݳɹ�!\n");
                Sleep(1000);//��ȡ�����,�ﵽ��ͣ��Ч��
                return 0;//����ѭ��
            }
            else{
                system("cls");
                printf("�ļ�����\n");
                printf("������������ѡ��\n");
                printf("=================\n");
                printf(" 1.�����޸�\n 2.�����޸ı�\n 3.�˳�����\n");
                printf("=================\n");
                printf("���������ѡ��:");
                scanf("%d",&flag);
                if(flag==1){
                    return 1;//�ٴδ���
                }
                if(flag==2){
                    return 0;//����ѭ��
                }
                if(flag==3){
                    exit(0);
                }
                else{
                    printf("û�и�ѡ��!\n�����޸�");
                    return 0;
                }
            }
        }
    }
    //ƥ��ɹ��Ķ���ȥ��,ƥ��ʧ�ܲŻ�ִ����������
    system("cls");
    printf("����û�������");
    printf("������������ѡ��\n");
    printf("=================\n");
    printf(" 1.�޸���һ���������\n 2.ȡ���޸ı����\n 3.�˳�����\n");
    printf("=================\n");
    printf("���������ѡ��:");
    scanf("%d",&flag);
    if(flag==1){
        return 1;//�ٴδ���
    }
    if(flag==2){
        return 0;//����ѭ��
    }
    if(flag==3){
        exit(0);
    }
    else{
        printf("û�и�ѡ��!\n�����޸�");
        Sleep(2000);
        return 0;
    }
}


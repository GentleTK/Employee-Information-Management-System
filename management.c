#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
/*
	定义结构体类型，声明新类型Employee,Ln 11 --> Ln 19 为数据域
*/
typedef struct employ_info
{
	char num[6];				//Ln 11
	char name[10];
	char sex[10];
	char birth[10];
	char edu[10];
	char post[10];
	char salary[10];
	char addr[20];
	char phone[20];				//Ln 19
	struct employ_info * next;		//指针域
}Employee;

void Menu();					//系统菜单 
void Show(Employee * Head);			//浏览信息
void Search(Employee * Head);			//查询信息
void save(Employee * Head);			//保存信息
Employee * Update(Employee * Head);		//修改信息
Employee * Delete(Employee * Head);		//删除信息
Employee * add(Employee * Head);		//添加信息
Employee * create();				//保存链表为磁盘文件
Employee * openfile();				//新创建链表读取磁盘文件

int  main()
{
	Employee * Head=NULL;			//链表初始化
	int select;
	do
	{
		Menu();
		printf("请输入您的选择（1-7）：");
		scanf("%d",&select);
		switch(select)
		{
			case 1:system("cls");Head = create();break;
			case 2:system("cls");Show(Head);break;
			case 3:system("cls");Head = add(Head);break;
			case 4:system("cls");Head = Delete(Head);break;
			case 5:system("cls");Search(Head);break;
			case 6:system("cls");Head = Update(Head);break;
			case 7:break;
			default:printf("错误选择！请重选");break;
		}
	}while(select != 7);
	return 0;
}
/*
	系统菜单 
*/ 
void Menu()
{
	printf("\n***************职工信息管理**************\n");
	printf("*\t1---创建职工记录(Create)\t*\n");
	printf("*\t2---浏览职工信息(Show)\t\t*\n");
	printf("*\t3---添加职工信息(Add)\t\t*\n");
	printf("*\t4---删除职工信息(Delete)\t*\n");
	printf("*\t5---查询职工信息(Search)\t*\n");
	printf("*\t6---修改职工信息(Update)\t*\n");
	printf("*\t7---退出(Exit)\t\t\t*\n");
	printf("*****************************************\n");
}
/*
	创建链表（采用尾插法），此函数返回一个指向链表头的指针
*/
Employee * create()
{
	Employee * p,* Head,* end; 
	char ch;
	Head = p = end = (Employee * )malloc(sizeof(Employee));//创建一个结点
	do
	{
		end = p;//end为指向表尾的指针，将表尾指针指向新插入的结点
		printf("请输入职工号: ");
		scanf("%s",p->num);
		printf("请输入姓名：");
		scanf("%s", p->name);
		printf("请输入性别：");
		scanf("%s", p->sex);
		printf("请输入出生年月：");
		scanf("%s", p->birth);
		printf("请输入学历：");
		scanf("%s", p->edu);
		printf("请输入职务：");
		scanf("%s", p->post);
		printf("请输入工资：");
		scanf("%s", p->salary);
		printf("请输入地址：");
		scanf("%s", p->addr);
		printf("请输入电话号码：");
		scanf("%s", p->phone);
		getchar();
		printf("是否继续录入？按Y/y继续 ");
		scanf("%c", &ch);
		p = (Employee *)malloc(sizeof(Employee));
		end->next = p;//将新生成的结点插在表尾
	}while(ch == 'y' || ch == 'Y'); 
	end->next = NULL;//尾结点指针置空
	save(Head);
	return Head;//返回的是Head的值，即链表中第一个结点的起始地址
}
/*
	浏览信息(输出链表),	注意:要想浏览必须打开文件,若无文件,则需录入信息保存为文件再打开浏览
*/
void Show(Employee * Head)
{
	Employee * p;//定义struct employ_info类型的变量p
	Head = openfile();
	p = Head;//使p指向第一个结点
	if(p == NULL)
	{
		printf("未打开任何文件！\n");
		getchar();
		return;
	}
	printf("\n职工号  姓名  性别  出生年月  学历  职务   工资	   住址	   电话号码\n");
	printf("-----------------------------------------------------------------------\n");
	while(p != NULL)
	{
		printf("\n");
		printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
		p = p->next;
	}
	getchar();//显示结果，否则一闪而过
}
/*
	添加职工信息(添加前需打开文件，添加成功后需保存)
*/
Employee * add(Employee * Head)
{
	Employee * p,* c,* f,* h;
	Head = openfile();
	if(Head == NULL)
	{
		printf("未能打开任何文件！\n");
		getchar();
		return NULL;
	}
	h = c = f = Head;
	p = (Employee * )malloc(sizeof(Employee));//分配空间(新添节点，即新添加的记录)
	printf("请按提示添加职工信息\n");
	printf("职工号：");
	scanf("%s", p->num);
	printf("姓名：");
	scanf("%s", p->name);
	printf("性别：");
	scanf("%s", p->sex);
	printf("出生年月：");
	scanf("%s", p->birth);
	printf("学历：");
	scanf("%s", p->edu);
	printf("职务：");
	scanf("%s", p->post);
	printf("工资：");
	scanf("%s", p->salary);
	printf("住址：");
	scanf("%s", p->addr);
	printf("电话号码：");
	scanf("%s", p->phone);
	if(strcmp(f->num,p->num)>0)//和表头作比较
	{
		p->next = f;
		h = p;
		save(h);
		printf("添加成功！\n");
		return h;
	}
	if(f->next == NULL)//只有一个可用结点
	{
		f->next = p;
		p->next = NULL;
		save(h);
		printf("添加成功！\n");
		return h;
	}
	while(f->next != NULL)
	{
		f = f->next;
		if(strcmp(f->num,p->num)>0)
		{
			c->next = p;
			p->next = f;
			save(h);
			printf("添加成功！\n");
			return h;
		}
		else
			c = c->next;
	}
	if(f->next == NULL)
	{
		f->next = p;
		p->next = NULL;
		save(h);
		printf("添加成功！\n");
		return h;
	}
}
/*
	删除职工信息(需先打开职工记录,删除信息后需保存!)
*/
Employee *  Delete(Employee * Head)
{
	Employee * p,* c;
	char str_number[20];
	Head = openfile();
	if(Head == NULL)
	{
		printf("未能打开任何文件！\n");
		getchar();
		return NULL;
	}
	p = c = Head;
	printf("请输入要删除数据的职工号：");
	scanf("%s", str_number);
	if(strcmp(p->num, str_number) == 0)
	{
		Head = Head->next;//Head->next即为头指针的直接后继地址的指针
		save(Head);
		printf("删除成功！\n");
		return Head;
	}
	p = p->next;
	while(p != NULL)
	{
		if(strcmp(p->num, str_number) == 0)
		{
			if(p->next != NULL)
				c->next = p->next;//让前一个结点指向p的后继结点
			if(p->next == NULL)
				c->next = NULL;//让c指向空（尾结点）
			save(Head);
			printf("删除成功！\n");
			return Head;
		}
		p = p->next;
		c = c->next;
	}
	
	printf("没有找到可以删除的数据！！");
	return Head;
}
/*
	查询职工信息，可按职工号和姓名查询(需先打开职工记录)
*/
void Search(Employee * Head)
{
	Employee * p;
	char str[20];
	int i, j = 0;//定义i变量来确定查询方式（1.按职工号/2.按姓名）,定义j变量来判断所查职工是否存在
	Head = openfile();
	p = Head;
	if(Head == NULL)
	{
		printf("未能打开任何文件！\n");
		getchar();
		return ;
	}
	printf("1.按职工号查询    2.按姓名查询\n");
	scanf("%d", &i);
	if(i == 1)
		printf("请输入要查询的职工号：");
	else
		printf("请输入姓名：");
	scanf("%s", str);
	while(p != NULL)
	{
		if(i == 1)//按职工号查询
		{
			if(strcmp(p->num,str) == 0)
			{
				printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
				j = 1;
				break;
			}
		}
		if(i == 2)//按姓名查询
		{
			if(strcmp(p->name, str) == 0)
			{
				printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
				j = 1;
			}
		}
		p = p->next;
	}
	getchar();//显示结果，否则一闪而过
	if(j == 0)
		printf("查无此人！！");
	return;
}
/*
	修改职工信息(需先打开职工记录,修改后信息后需保存!)
*/
Employee * Update(Employee * Head)
{
	Employee * p;
	char str_number[20];
	Head = openfile();
	if(Head == NULL)
	{
		printf("未能打开任何文件！\n");
		getchar();
		return NULL;
	}
	p = Head;
	printf("请输入要修改的职工号：");
	scanf("%s",str_number);
	while(p != NULL)
	{
		if(strcmp(p->num, str_number) == 0)//与输入的职工号进行比较，若相同则进行修改
		{
			printf("职工号:%s\n姓名:%s\n性别:%s\n出生年月:%s\n学历:%s\n职务:%s\n工资:%s\n住址:%s\n电话号码:%s\n",
				p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
			printf("请按提示输入修改后的内容:\n");
			printf("职工号：");
			scanf("%s", p->num);
			printf("姓名：");
			scanf("%s", p->name);
			printf("性别：");
			scanf("%s", p->sex);
			printf("出生年月：");
			scanf("%s", p->birth);
			printf("学历：");
			scanf("%s", p->edu);
			printf("职务：");
			scanf("%s", p->post);
			printf("工资：");
			scanf("%s", p->salary);
			printf("住址：");
			scanf("%s", p->addr);
			printf("电话号码：");
			scanf("%s", p->phone);
			save(Head);
			printf("修改成功！\n");
			return Head;
		}
		p = p->next;
	}
	printf("没有找到要修改的记录！！");
	return Head;
}
/*
	保存链表为磁盘文件(用格式化的方式写文件)
*/
void save(Employee * Head)
{  
    FILE * fp;  
	Employee * p;  
	system("cls");
	if((fp = fopen("EmployeeInfo.txt","w")) == NULL)
	{
		printf("创建文件失败！\n");
		return;
	}
	p = Head;
    while(p != NULL) 
	{  
        fprintf(fp,"%s\n", p->num);
		fprintf(fp,"%s\n", p->name);
		fprintf(fp,"%s\n", p->sex);
		fprintf(fp,"%s\n", p->birth);
		fprintf(fp,"%s\n", p->edu);
		fprintf(fp,"%s\n", p->post);
		fprintf(fp,"%s\n", p->salary);
		fprintf(fp,"%s\n", p->addr);
		fprintf(fp,"%s\n", p->phone);
		p = p->next;
    }  
    fputs("over",fp);
    fclose(fp);  
}  
/*
	新创建链表读取磁盘文件(用格式化的方式读文件)
*/
Employee * openfile()
{
	Employee * Head,* p,* f;
	FILE * fp;
	if((fp = fopen("EmployeeInfo.txt","r")) == NULL)
	{
		printf("打开文件失败！\n");
		return;
	}
	Head = f = p = (Employee * )malloc(sizeof(Employee));//建立一个结点
	fscanf(fp, "%s%s%s%s%s%s%s%s%s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
	while(!feof(fp))
	{
		p = (Employee * )malloc(sizeof(Employee));
		f->next = p;//节点连接
		fscanf(fp, "%s%s%s%s%s%s%s%s%s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
		if(strcmp(p->num,"over")==0)
		{
			f->next = NULL;
			return Head;
		}
		f = p;
	}
	fclose(fp);
	f->next = NULL;
	return Head;
}

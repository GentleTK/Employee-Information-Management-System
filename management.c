# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct EmployeeInfo
{
	char id[5];
	char name[10];
	char sex[10];
	char birth[10];
	char edu[10];
	char post[10];
	char salary[10];
	char addr[10];
	char phone[10];	
	struct EmployeeInfo *next;
}employee;

employee *createNode(void);							// ����һ��ְ����Ϣ�ڵ� 
employee *openFile(void);							// ��ְ����Ϣ�ļ� 
void saveFile(employee *head);						// ����ְ����Ϣ�����ļ� 
void Display(void);									// ���ְ����Ϣ 
void menu(void);									// ϵͳ���ܲ˵� 
void insert_Tail(employee *pHead, employee *pNew);	// β�巨����ְ����Ϣ���� 
void Add(void);										// ���ְ����Ϣ 
void Delete(void);									// ɾ��ְ����Ϣ 
void Query(void);									// ��ѯְ����Ϣ 
void Modify(void);									// �޸�ְ����Ϣ 

int main(void)
{
	int select;
	do
	{
		menu();
		printf("Please input your select(1-6): ");
		scanf("%d", &select);
		switch(select)
		{
			case 1:system("cls");Add();break;
			case 2:system("cls");Delete();break;
			case 3:system("cls");Query();break;
			case 4:system("cls");Modify();break;
			case 5:system("cls");Display();break;
			case 6:break;
			default:printf("Input error, please input again!\n");break;
		}
	}while(6 != select);
	return 0;
} 

/*
	ϵͳ�˵� 
*/
void menu(void)
{
	printf("\n***************Employee Information Management System**************\n");
	printf("*\t\t(1)  Add     Employee Information\t\t  *\n");
	printf("*\t\t(2)  Delete  Employee Information\t\t  *\n");
	printf("*\t\t(3)  Query   Employee Information\t\t  *\n");
	printf("*\t\t(4)  Modify  Employee Information\t\t  *\n");
	printf("*\t\t(5)  Display Employee Information\t\t  *\n");
	printf("*\t\t(6)  Exit\t\t\t\t\t  *\n");
	printf("*******************************************************************\n");
}

/*
	����һ��ְ����Ϣ�ڵ� 
	���ظýڵ��ָ�� 
*/
employee *createNode(void)
{
	employee *pNode = (employee *)malloc(sizeof(employee));
	if(NULL == pNode)
	{
		printf("Malloc error!\n");
	}
	memset(pNode, 0, sizeof(employee *));
	printf("Please input id: ");
	scanf("%s", pNode->id);
	printf("Please input name: ");
	scanf("%s", pNode->name);
	printf("Please input sex: ");
	scanf("%s", pNode->sex);
	printf("Please input birth: ");
	scanf("%s", pNode->birth);
	printf("Please input edu: ");
	scanf("%s", pNode->edu);
	printf("Please input post: ");
	scanf("%s", pNode->post);
	printf("Please input salary: ");
	scanf("%s", pNode->salary);
	printf("Please input addr: ");
	scanf("%s", pNode->addr);
	printf("Please input phone: ");
	scanf("%s", pNode->phone);
	pNode->next = NULL;
	return pNode;
}

/*
	β�巨����ְ����Ϣ���� 
	pHead:ͷָ�� 
	pNew: Ҫ����ڵ��ָ�� 
*/
void insert_Tail(employee *pHead, employee *pNew)
{
	employee *p = pHead;
	while(NULL != p->next)// �ҵ����һ���ڵ�
	{
		p = p->next;
	}
	p->next = pNew;// ָ�����Ľڵ�
}

/*
	����ְ����Ϣ��¼ 
*/
void Add(void)
{
	FILE *fp;
	employee *pHead;
	if(NULL == (fp = fopen("employeeInfo.txt", "r")))// �ļ������ڣ�����ͷ�ڵ� 
	{
		pHead = (employee *)malloc(sizeof(employee));
		if(NULL == pHead)
		{
			printf("Malloc error!\n");
		}
		memset(pHead, 0, sizeof(employee));
	}
	else// ��ְ����¼�����ļ� 
	{
		pHead = openFile(); 
	}
	do
	{
		insert_Tail(pHead, createNode());
		getchar();
		printf("Press n/N to exit: ");
	}while(getchar() != 'n' && getchar() != 'N'); 
	saveFile(pHead);
}

/*
	����ְ����Ϣ���� 
*/
void Display(void)
{
	employee *p = openFile();
	printf("\nID\tName\tSex\tBirth\tEdu\tPost\tSalary\tAddr\tPhoneNum\n");
	while (NULL != p)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", p->id, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
		p = p->next;
	}
} 

/*
	ɾ��ְ����Ϣ 
*/ 
void Delete(void)
{
	employee *head, *p;
	employee *pPrv = NULL;
	char idstr[5];
	int findok = 0;
	head = p = openFile();
	printf("Please input ID which you want to delete: ");
	scanf("%s", idstr); 
	while(NULL != p->next)
	{
		pPrv = p;// ������һ���ڵ��nextָ�� 
		p = p->next;
		if(!strcmp(idstr, p->id))// �ҵ�Ҫɾ���Ľڵ� 
		{
			findok = 1;
			if(NULL != p->next)// Ҫɾ���Ĳ���β�ڵ� 
			{
				pPrv->next = p->next;
				saveFile(head);
				free(p);
			}
			else
			{
				pPrv->next = NULL;
				saveFile(head);
				free(p);
			}
			printf("Delete success!\n"); 
		}
	}
	if(!findok) 
	{
		printf("Information not found!\n");
	}
} 

/*
	����ְ����¼ 
*/
void Query(void)
{
	employee *p = openFile();
	char str[10]; 
	int choose, findok = 0;
	printf("Please choose query mode:1.By ID.	2.By name.");
	scanf("%d", &choose);
	if(1 == choose)
	{
		printf("Please input ID which you want to query: ");
	}
	else
	{
		printf("Please input name which you want to query: ");
	}
	scanf("%s", str);
	while(NULL != p->next)
	{
		p = p->next;
		if(((1==choose)&&!strcmp(str, p->id)) || ((2==choose)&&!strcmp(str, p->name)))
		{
			findok = 1;
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", p->id, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
			printf("Find suceess!\n");
		}
	}
	if(!findok)
	{
		printf("Information not found!\n");
	}
} 

/*
	�޸�ְ����¼ 
*/ 
void Modify(void)
{
	employee *head, *p;
	char idstr[10]; 
	int findok = 0;
	head = p = openFile();
	printf("Please input ID which you want to Modify: ");
	scanf("%s", idstr);
	while(NULL != p->next)
	{
		p = p->next;
		if(!strcmp(idstr, p->id))
		{
			findok = 1;
			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", p->id, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
			printf("Find suceess!\n");
			printf("Please follow the prompt to enter the changes.\n");
			printf("ID: ");
			scanf("%s", p->id);
			printf("Name: ");
			scanf("%s", p->name);
			printf("Sex: ");
			scanf("%s", p->sex);
			printf("Birth: ");
			scanf("%s", p->birth);
			printf("Edu: ");
			scanf("%s", p->edu);
			printf("Post: ");
			scanf("%s", p->post);
			printf("Salary: ");
			scanf("%s", p->salary);
			printf("Addr: ");
			scanf("%s", p->addr);
			printf("Phone: ");
			scanf("%s", p->phone);
			saveFile(head);
			printf("Modify success!\n");
		}
	}
	if(!findok)
	{
		printf("Information not found!\n");
	}
}

/*
	���������ļ� 
*/
void saveFile(employee *head)
{
	employee *p = head->next;
	FILE *fp;
	if(NULL == (fp = fopen("employeeInfo.txt", "w")))
	{
		printf("Create file fail!\n");
		exit(0);
	}
	while(NULL != p)
	{
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", p->id, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
		p = p->next;
	}
	fputs("over",fp);
    fclose(fp); 
}

/*
	��ְ����¼
	����ְ����¼�����ͷָ�� 
*/
employee *openFile(void)
{
	employee *pHead, *head, *pNew, *end;
	FILE *fp;
	if(NULL == (fp = fopen("employeeInfo.txt", "r")))
	{
		printf("Open file fail!\n");
		exit(0);
	}
	pHead = (employee *)malloc(sizeof(employee));// ͷָ�� 
	head = end = (employee *)malloc(sizeof(employee));
	if(NULL == end || NULL == pHead) 
	{
		printf("Malloc error!\n");
	}
	memset(end, 0, sizeof(employee *));
	memset(pHead, 0, sizeof(employee));
	fscanf(fp, "%s%s%s%s%s%s%s%s%s", end->id, end->name, end->sex, end->birth, end->edu, end->post, end->salary, end->addr, end->phone);
	while(!feof(fp))
	{
		pNew = (employee *)malloc(sizeof(employee));
		end->next = pNew;
		fscanf(fp, "%s%s%s%s%s%s%s%s%s", pNew->id, pNew->name, pNew->sex, pNew->birth, pNew->edu, pNew->post, pNew->salary, pNew->addr, pNew->phone);
		if(!strcmp(pNew->id,"over"))
		{
			end->next = NULL;
		}
		end = pNew;// endָ��ǰ�²����β�ڵ�
	}
	end->next = NULL;
	pHead->next = head;// ָ���һ����Ч�ڵ� 
	fclose(fp);
	return pHead;
}

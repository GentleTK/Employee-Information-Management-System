#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

/*
	����ṹ�����ͣ�����������Employee,Ln 11 --> Ln 19 Ϊ������
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
	struct employ_info * next;	//ָ����
}Employee;

void Menu();							//ϵͳ�˵� 
void Show(Employee * Head);				//�����Ϣ
void Search(Employee * Head);			//��ѯ��Ϣ
void save(Employee * Head);				//������Ϣ
Employee * Update(Employee * Head);		//�޸���Ϣ
Employee * Delete(Employee * Head);		//ɾ����Ϣ
Employee * add(Employee * Head);		//�����Ϣ
Employee * create();					//��������Ϊ�����ļ�
Employee * openfile();					//�´��������ȡ�����ļ�

int  main()
{
	Employee * Head=NULL;				//�����ʼ��
	int select;
	do
	{
		Menu();
		printf("����������ѡ��1-7����");
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
			default:printf("����ѡ������ѡ");break;
		}
	}while(select != 7);
	return 0;
}
/*
	ϵͳ�˵� 
*/ 
void Menu()
{
	printf("\n***************ְ����Ϣ����**************\n");
	printf("*\t1---����ְ����¼(Create)\t*\n");
	printf("*\t2---���ְ����Ϣ(Show)\t\t*\n");
	printf("*\t3---���ְ����Ϣ(Add)\t\t*\n");
	printf("*\t4---ɾ��ְ����Ϣ(Delete)\t*\n");
	printf("*\t5---��ѯְ����Ϣ(Search)\t*\n");
	printf("*\t6---�޸�ְ����Ϣ(Update)\t*\n");
	printf("*\t7---�˳�(Exit)\t\t\t*\n");
	printf("*****************************************\n");
}
/*
	������������β�巨�����˺�������һ��ָ������ͷ��ָ��
*/
Employee * create()
{
	Employee * p,* Head,* end; 
	char ch;
	Head = p = end = (Employee * )malloc(sizeof(Employee));//����һ�����
	do
	{
		end = p;//endΪָ���β��ָ�룬����βָ��ָ���²���Ľ��
		printf("������ְ����: ");
		scanf("%s",p->num);
		printf("������������");
		scanf("%s", p->name);
		printf("�������Ա�");
		scanf("%s", p->sex);
		printf("������������£�");
		scanf("%s", p->birth);
		printf("������ѧ����");
		scanf("%s", p->edu);
		printf("������ְ��");
		scanf("%s", p->post);
		printf("�����빤�ʣ�");
		scanf("%s", p->salary);
		printf("�������ַ��");
		scanf("%s", p->addr);
		printf("������绰���룺");
		scanf("%s", p->phone);
		getchar();
		printf("�Ƿ����¼�룿��Y/y���� ");
		scanf("%c", &ch);
		p = (Employee *)malloc(sizeof(Employee));
		end->next = p;//�������ɵĽ����ڱ�β
	}while(ch == 'y' || ch == 'Y'); 
	end->next = NULL;//β���ָ���ÿ�
	save(Head);
	return Head;//���ص���Head��ֵ���������е�һ��������ʼ��ַ
}
/*
	�����Ϣ(�������),	ע��:Ҫ�����������ļ�,�����ļ�,����¼����Ϣ����Ϊ�ļ��ٴ����
*/
void Show(Employee * Head)
{
	Employee * p;//����struct employ_info���͵ı���p
	Head = openfile();
	p = Head;//ʹpָ���һ�����
	if(p == NULL)
	{
		printf("δ���κ��ļ���\n");
		getchar();
		return;
	}
	printf("\nְ����  ����  �Ա�  ��������  ѧ��  ְ��   ����	   סַ	   �绰����\n");
	printf("-----------------------------------------------------------------------\n");
	while(p != NULL)
	{
		printf("\n");
		printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
		p = p->next;
	}
	getchar();//��ʾ���������һ������
}
/*
	���ְ����Ϣ(���ǰ����ļ�����ӳɹ����豣��)
*/
Employee * add(Employee * Head)
{
	Employee * p,* c,* f,* h;
	Head = openfile();
	if(Head == NULL)
	{
		printf("δ�ܴ��κ��ļ���\n");
		getchar();
		return NULL;
	}
	h = c = f = Head;
	p = (Employee * )malloc(sizeof(Employee));//����ռ�(����ڵ㣬������ӵļ�¼)
	printf("�밴��ʾ���ְ����Ϣ\n");
	printf("ְ���ţ�");
	scanf("%s", p->num);
	printf("������");
	scanf("%s", p->name);
	printf("�Ա�");
	scanf("%s", p->sex);
	printf("�������£�");
	scanf("%s", p->birth);
	printf("ѧ����");
	scanf("%s", p->edu);
	printf("ְ��");
	scanf("%s", p->post);
	printf("���ʣ�");
	scanf("%s", p->salary);
	printf("סַ��");
	scanf("%s", p->addr);
	printf("�绰���룺");
	scanf("%s", p->phone);
	if(strcmp(f->num,p->num)>0)//�ͱ�ͷ���Ƚ�
	{
		p->next = f;
		h = p;
		save(h);
		printf("��ӳɹ���\n");
		return h;
	}
	if(f->next == NULL)//ֻ��һ�����ý��
	{
		f->next = p;
		p->next = NULL;
		save(h);
		printf("��ӳɹ���\n");
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
			printf("��ӳɹ���\n");
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
		printf("��ӳɹ���\n");
		return h;
	}
}
/*
	ɾ��ְ����Ϣ(���ȴ�ְ����¼,ɾ����Ϣ���豣��!)
*/
Employee *  Delete(Employee * Head)
{
	Employee * p,* c;
	char str_number[20];
	Head = openfile();
	if(Head == NULL)
	{
		printf("δ�ܴ��κ��ļ���\n");
		getchar();
		return NULL;
	}
	p = c = Head;
	printf("������Ҫɾ�����ݵ�ְ���ţ�");
	scanf("%s", str_number);
	if(strcmp(p->num, str_number) == 0)
	{
		Head = Head->next;//Head->next��Ϊͷָ���ֱ�Ӻ�̵�ַ��ָ��
		save(Head);
		printf("ɾ���ɹ���\n");
		return Head;
	}
	p = p->next;
	while(p != NULL)
	{
		if(strcmp(p->num, str_number) == 0)
		{
			if(p->next != NULL)
				c->next = p->next;//��ǰһ�����ָ��p�ĺ�̽��
			if(p->next == NULL)
				c->next = NULL;//��cָ��գ�β��㣩
			save(Head);
			printf("ɾ���ɹ���\n");
			return Head;
		}
		p = p->next;
		c = c->next;
	}
	
	printf("û���ҵ�����ɾ�������ݣ���");
	return Head;
}
/*
	��ѯְ����Ϣ���ɰ�ְ���ź�������ѯ(���ȴ�ְ����¼)
*/
void Search(Employee * Head)
{
	Employee * p;
	char str[20];
	int i, j = 0;//����i������ȷ����ѯ��ʽ��1.��ְ����/2.��������,����j�������ж�����ְ���Ƿ����
	Head = openfile();
	p = Head;
	if(Head == NULL)
	{
		printf("δ�ܴ��κ��ļ���\n");
		getchar();
		return ;
	}
	printf("1.��ְ���Ų�ѯ    2.��������ѯ\n");
	scanf("%d", &i);
	if(i == 1)
		printf("������Ҫ��ѯ��ְ���ţ�");
	else
		printf("������������");
	scanf("%s", str);
	while(p != NULL)
	{
		if(i == 1)//��ְ���Ų�ѯ
		{
			if(strcmp(p->num,str) == 0)
			{
				printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
				j = 1;
				break;
			}
		}
		if(i == 2)//��������ѯ
		{
			if(strcmp(p->name, str) == 0)
			{
				printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
				j = 1;
			}
		}
		p = p->next;
	}
	getchar();//��ʾ���������һ������
	if(j == 0)
		printf("���޴��ˣ���");
	return;
}
/*
	�޸�ְ����Ϣ(���ȴ�ְ����¼,�޸ĺ���Ϣ���豣��!)
*/
Employee * Update(Employee * Head)
{
	Employee * p;
	char str_number[20];
	Head = openfile();
	if(Head == NULL)
	{
		printf("δ�ܴ��κ��ļ���\n");
		getchar();
		return NULL;
	}
	p = Head;
	printf("������Ҫ�޸ĵ�ְ���ţ�");
	scanf("%s",str_number);
	while(p != NULL)
	{
		if(strcmp(p->num, str_number) == 0)//�������ְ���Ž��бȽϣ�����ͬ������޸�
		{
			printf("ְ����:%s\n����:%s\n�Ա�:%s\n��������:%s\nѧ��:%s\nְ��:%s\n����:%s\nסַ:%s\n�绰����:%s\n",
				p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
			printf("�밴��ʾ�����޸ĺ������:\n");
			printf("ְ���ţ�");
			scanf("%s", p->num);
			printf("������");
			scanf("%s", p->name);
			printf("�Ա�");
			scanf("%s", p->sex);
			printf("�������£�");
			scanf("%s", p->birth);
			printf("ѧ����");
			scanf("%s", p->edu);
			printf("ְ��");
			scanf("%s", p->post);
			printf("���ʣ�");
			scanf("%s", p->salary);
			printf("סַ��");
			scanf("%s", p->addr);
			printf("�绰���룺");
			scanf("%s", p->phone);
			save(Head);
			printf("�޸ĳɹ���\n");
			return Head;
		}
		p = p->next;
	}
	printf("û���ҵ�Ҫ�޸ĵļ�¼����");
	return Head;
}
/*
	��������Ϊ�����ļ�(�ø�ʽ���ķ�ʽд�ļ�)
*/
void save(Employee * Head)
{  
    FILE * fp;  
	Employee * p;  
	system("cls");
	if((fp = fopen("EmployeeInfo.txt","w")) == NULL)
	{
		printf("�����ļ�ʧ�ܣ�\n");
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
	�´��������ȡ�����ļ�(�ø�ʽ���ķ�ʽ���ļ�)
*/
Employee * openfile()
{
	Employee * Head,* p,* f;
	FILE * fp;
	if((fp = fopen("EmployeeInfo.txt","r")) == NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		return;
	}
	Head = f = p = (Employee * )malloc(sizeof(Employee));//����һ�����
	fscanf(fp, "%s%s%s%s%s%s%s%s%s", p->num, p->name, p->sex, p->birth, p->edu, p->post, p->salary, p->addr, p->phone);
	while(!feof(fp))
	{
		p = (Employee * )malloc(sizeof(Employee));
		f->next = p;//�ڵ�����
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

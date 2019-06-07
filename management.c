#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define NULL 0
/*
	����ṹ�����ͣ�����������Employee,Ln 11 --> Ln 19 Ϊ������
*/
typedef struct employ_info
{
	char num[6];//Ln 11
	char name[10];
	char sex[10];
	char birth[10];
	char edu[10];
	char post[10];
	char salary[10];
	char addr[20];
	char phone[20];//Ln 19
	struct employ_info * next;//ָ����
}Employee;
void Show(Employee * Head);//�����Ϣ
void Search(Employee * Head);//��ѯ��Ϣ
void save(Employee * Head);//������Ϣ
Employee * Update(Employee * Head);//�޸���Ϣ
Employee * Delete(Employee * Head);//ɾ����Ϣ
Employee * add(Employee * Head);//�����Ϣ
Employee * create();//��������Ϊ�����ļ�
Employee * openfile();//�´��������ȡ�����ļ�

int  main()
{
	Employee * Head=NULL;//�����ʼ��
	int n;
	do
	{
		printf("\n***************ְ����Ϣ����**************\n");
		printf("*	1---¼��ְ����Ϣ(Input)		*\n");
		printf("*	2---����ְ����Ϣ(Save)		*\n");
		printf("*	3---���ְ����Ϣ(Show)		*\n");
		printf("*	4---��ְ����¼(Openfile)	*\n");
		printf("*	5---���ְ����¼(Add)		*\n");
		printf("*	6---��ѯְ����Ϣ(Search)	*\n");
		printf("*	7---�޸�ְ����Ϣ(Update)	*\n");
		printf("*	8---ɾ��ְ����Ϣ(Delete)	*\n");
		printf("*	9---�˳�(Exit)		    	*\n");
		printf("*****************************************\n");
		printf("����������ѡ��1-9����");
		scanf("%d",&n);
		switch(n)
		{
			case 1:Head=create();break;
			case 2:save(Head);break;
			case 3:Show(Head);break;
			case 4:Head=openfile();break;
			case 5:Head=add(Head);break;
			case 6:Search(Head);break;
			case 7:Head=Update(Head);break;
			case 8:Head=Delete(Head);break;
			case 9:break;
			default:printf("����ѡ������ѡ");break;
		}
	}while(n!=9);
	return 0;
}

/*
	������������β�巨�����˺�������һ��ָ������ͷ��ָ��
*/
Employee * create()
{
	Employee * p,* Head,* end;
	Head=p=end=(Employee * )malloc(sizeof(Employee));//����һ�����
	printf("������ְ����Ϣ:\n");
	printf("������ְ����(ְ���Ų�Ϊ0��):");
	scanf("%s",p->num);
	while(strcmp(p->num,"0")!=0)//ע�⣺�涨ְ���Ų�Ϊ0
	{
		end=p;//endΪָ���β��ָ�룬����βָ��ָ���²���Ľ��
		printf("������������");
		scanf("%s",p->name);
		printf("�������Ա�");
		scanf("%s",p->sex);
		printf("������������£�");
		scanf("%s",p->birth);
		printf("������ѧ����");
		scanf("%s",p->edu);
		printf("������ְ��");
		scanf("%s",p->post);
		printf("�����빤�ʣ�");
		scanf("%s",p->salary);
		printf("�������ַ��");
		scanf("%s",p->addr);
		printf("������绰���룺");
		scanf("%s",p->phone);
		p=(Employee *)malloc(sizeof(Employee));
		end->next=p;//�������ɵĽ����ڱ�β
		printf("������ְ���ţ�");//���ڿ���whileѭ��������ְ����Ϊ0ʱ����
		scanf("%s",p->num);
	}
	end->next=NULL;//β���ָ���ÿ�
	return Head;//���ص���Head��ֵ���������е�һ��������ʼ��ַ
}

/*
	�����Ϣ(�������),	ע��:Ҫ�����������ļ�,�����ļ�,����¼����Ϣ����Ϊ�ļ��ٴ����
*/
void Show(Employee * Head)
{
	Employee * p;//����struct employ_info���͵ı���p
	p=Head;//ʹpָ���һ�����
	if(p==NULL)
	{
		printf("δ���κ��ļ���\n");
		getchar();
		return;
	}
	printf("\nְ����  ����  �Ա�  ��������  ѧ��  ְ��   ����	   סַ	   �绰����\n");
	printf("-----------------------------------------------------------------------\n");
	while(p!=NULL)
	{
		printf("\n");
		printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s",p->num,p->name,p->sex,p->birth,p->edu,p->post,p->salary,p->addr,p->phone);
		p=p->next;
	}
	getchar();//��ʾ���������һ������
}

/*
	��ѯְ����Ϣ���ɰ�ְ���ź�������ѯ(���ȴ�ְ����¼)
*/
void Search(Employee * Head)
{
	Employee * p;
	char str[20];
	int i,j=0;//����i������ȷ����ѯ��ʽ��1.��ְ����/2.��������,����j�������ж�����ְ���Ƿ����
	p=Head;
	if(Head==NULL)
	{
		printf("δ�ܴ��κ��ļ���\n");
		getchar();
		return ;
	}
	printf("1.��ְ���Ų�ѯ    2.��������ѯ\n");
	scanf("%d",&i);
	if(i==1)
		printf("������Ҫ��ѯ��ְ���ţ�");
	else
		printf("������������");
	scanf("%s",str);
	while(p!=NULL)
	{
		if(i==1)//��ְ���Ų�ѯ
		{
			if(strcmp(p->num,str)==0)
			{
				printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s",p->num,p->name,p->sex,p->birth,p->edu,p->post,p->salary,p->addr,p->phone);
				j=1;
				break;
			}
		}
		if(i==2)//��������ѯ
		{
			if(strcmp(p->name,str)==0)
			{
				printf("%4s%8s%4s%10s%8s%8s%6s%10s%12s",p->num,p->name,p->sex,p->birth,p->edu,p->post,p->salary,p->addr,p->phone);
				j=1;
			}
		}
		p=p->next;
	}
	getchar();//��ʾ���������һ������
	if(j==0)
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
	if(Head==NULL)
	{
		printf("δ�ܴ��κ��ļ���\n");
		getchar();
		return NULL;
	}
	p=Head;
	printf("������Ҫ�޸ĵ�ְ���ţ�");
	scanf("%s",str_number);
	while(p!=NULL)
	{
		if(strcmp(p->num,str_number)==0)//�������ְ���Ž��бȽϣ�����ͬ������޸�
		{
			printf("ְ����:%s\n����:%s\n�Ա�:%s\n��������:%s\nѧ��:%s\nְ��:%s\n����:%s\nסַ:%s\n�绰����:%s\n",
				p->num,p->name,p->sex,p->birth,p->edu,p->post,p->salary,p->addr,p->phone);
			printf("�밴��ʾ�����޸ĺ������:\n");
			printf("ְ���ţ�");
			scanf("%s",p->num);
			printf("������");
			scanf("%s",p->name);
			printf("�Ա�");
			scanf("%s",p->sex);
			printf("�������£�");
			scanf("%s",p->birth);
			printf("ѧ����");
			scanf("%s",p->edu);
			printf("ְ��");
			scanf("%s",p->post);
			printf("���ʣ�");
			scanf("%s",p->salary);
			printf("סַ��");
			scanf("%s",p->addr);
			printf("�绰���룺");
			scanf("%s",p->phone);
			printf("�޸ĳɹ���\n");
			getchar();
			return Head;
		}
		p=p->next;
	}
	printf("û���ҵ�Ҫ�޸ĵļ�¼����");
	return Head;
}

/*
	ɾ��ְ����Ϣ(���ȴ�ְ����¼,ɾ����Ϣ���豣��!)
*/
Employee *  Delete(Employee * Head)
{
	Employee * p,* c;
	char str_number[20];
	if(Head==NULL)
	{
		printf("δ�ܴ��κ��ļ���\n");
		getchar();
		return NULL;
	}
	p=c=Head;
	printf("������Ҫɾ�����ݵ�ְ���ţ�");
	scanf("%s",str_number);
	if(strcmp(p->num,str_number)==0)
	{
		Head=Head->next;//Head->next��Ϊͷָ���ֱ�Ӻ�̵�ַ��ָ��
		printf("ɾ���ɹ���\n");
		return Head;
	}
	p=p->next;
	while(p!=NULL)
	{
		if(strcmp(p->num,str_number)==0)
		{
			if(p->next!=NULL)
				c->next=p->next;//��ǰһ�����ָ��p�ĺ�̽��
			if(p->next==NULL)
				c->next=NULL;//��cָ��գ�β��㣩
			printf("ɾ���ɹ���\n");
			return Head;
		}
		p=p->next;
		c=c->next;
	}
	printf("û���ҵ�����ɾ�������ݣ���");
	return Head;
}

/*
	��������Ϊ�����ļ�(�ø�ʽ���ķ�ʽд�ļ�)
*/
void save(Employee * Head)
{  
    FILE * fp;  
	Employee * p;  
	char filename[20];
	int ch;
	printf("������Ҫ������ļ���:");
	scanf("%s",filename);
    if((fp = fopen(filename, "r"))!=NULL)  
	{
		printf("���ļ��Ѵ��ڣ��Ƿ񸲸�?\n");
		printf("1.����		2.������\n");
		scanf("%d",&ch);
		if(ch!=1)
		{
			printf("����������Ҫ������ļ�����");
			scanf("%s",filename);
		}
	}
	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("�����ļ�ʧ�ܣ�\n");
		return;
	}
	getchar();
	p=Head;
    while(p!=NULL) 
	{  
        fprintf(fp,"%s\n",p->num);
		fprintf(fp,"%s\n",p->name);
		fprintf(fp,"%s\n",p->sex);
		fprintf(fp,"%s\n",p->birth);
		fprintf(fp,"%s\n",p->edu);
		fprintf(fp,"%s\n",p->post);
		fprintf(fp,"%s\n",p->salary);
		fprintf(fp,"%s\n",p->addr);
		fprintf(fp,"%s\n",p->phone);
		p=p->next;
    }  
	fputs("over",fp);
	printf("�ļ�����ɹ���\n");
	getchar();
    fclose(fp);  
}  

/*
	�´��������ȡ�����ļ�(�ø�ʽ���ķ�ʽ���ļ�)
*/
Employee * openfile()
{
	Employee * Head,* p,* f;
	FILE * fp;
	char filename[20];
	int ch;
	printf("������Ҫ�򿪵��ļ���:");
	scanf("%s",filename);
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		printf("1.���������ļ���   2.�˳�\n");
		scanf("%d",&ch);
		if(ch==1)
			scanf("%s",filename);
		else if(ch==2)
			getchar();
		return NULL;
	}
	Head=f=p=(Employee * )malloc(sizeof(Employee));//����һ�����
	fscanf(fp,"%s%s%s%s%s%s%s%s%s",p->num,p->name,p->sex,p->birth,p->edu,p->post,p->salary,p->addr,p->phone);
	while(!feof(fp))
	{
		p=(Employee * )malloc(sizeof(Employee));
		f->next=p;//�ڵ�����
		fscanf(fp,"%s%s%s%s%s%s%s%s%s",p->num,p->name,p->sex,p->birth,p->edu,p->post,p->salary,p->addr,p->phone);
		if(strcmp(p->num,"over")==0)
		{
			f->next=NULL;
			printf("�ļ��򿪳ɹ����ɣ����/���/��ѯ/�޸�/ɾ������Ϣ");
			getchar();
			return Head;
		}
		f=p;
	}
	fclose(fp);
	f->next=NULL;
	return Head;
}

/*
	���ְ����Ϣ(���ǰ����ļ�����ӳɹ����豣��)
*/
Employee * add(Employee * Head)
{
	Employee * p,* c,* f,* h;
	if(Head==NULL)
	{
		printf("δ�ܴ��κ��ļ���\n");
		getchar();
		return NULL;
	}
	h=c=f=Head;
	p=(Employee * )malloc(sizeof(Employee));//����ռ�(����ڵ㣬������ӵļ�¼)
	printf("ְ���ţ�");
	scanf("%s",p->num);
	printf("������");
	scanf("%s",p->name);
	printf("�Ա�");
	scanf("%s",p->sex);
	printf("�������£�");
	scanf("%s",p->birth);
	printf("ѧ����");
	scanf("%s",p->edu);
	printf("ְ��");
	scanf("%s",p->post);
	printf("���ʣ�");
	scanf("%s",p->salary);
	printf("סַ��");
	scanf("%s",p->addr);
	printf("�绰���룺");
	scanf("%s",p->phone);
	if(strcmp(f->num,p->num)>0)//�ͱ�ͷ���Ƚ�
	{
		p->next=f;
		h=p;
		printf("��ӳɹ���\n");
		return h;
	}
	if(f->next==NULL)//ֻ��һ�����ý��
	{
		f->next=p;
		p->next=NULL;
		printf("��ӳɹ���\n");
		return h;
	}
	while(f->next!=NULL)
	{
		f=f->next;
		if(strcmp(f->num,p->num)>0)
		{
			c->next=p;
			p->next=f;
			printf("��ӳɹ���\n");
			return h;
		}
		else
			c=c->next;
	}
	if(f->next==NULL)
	{
		f->next=p;
		p->next=NULL;
		printf("��ӳɹ���\n");
		return h;
	}
}

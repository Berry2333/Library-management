
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
enum Menu { xxoo = 0, Dengji, Liulan, Jieyur, Guihuan, Chazhao, Tianjia, Shanchu,Paixu ,Tuichu };

//3.�������
	//���ݽṹ
	//���ݴ���-->ͼ����Ϣ-->����-->
	// 

//ͼ����Ϣ
struct bookInfo {

	char name[20];
	float price;
	int num;
};
//ʵ������
struct Node {
	struct bookInfo data;
	struct Node* next;
};

struct Node* list = NULL;

//������ͷ
struct Node* createHead() {
	//��̬�ڴ�����
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	//������������ ʹ��ǰ��ʼ��
	headNode->next = NULL;
	return headNode;
}

//�����ڵ�:Ϊ������׼��
//���û����ݱ�Ϊ�ṹ�����
struct Node* creatNode(struct bookInfo data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//������� ��ͷ������
void insertNodeByhead(struct Node* headNode, struct bookInfo data) {
	struct Node* newNode = creatNode(data);
	
	newNode->next = headNode->next;
	headNode->next = newNode;

}
//��β����
void insertNodeByTail(struct Node* headNode, struct bookInfo data) {
	struct Node* newNode = creatNode(data);
	struct Node* pMove = headNode;
	while (pMove->next != NULL) {
		pMove = pMove->next;
	}
	pMove->next = newNode;
}
//���в���
void insertNodeByMod(struct Node* headNode, struct bookInfo data,int insertNum) {
	struct Node* newNode = creatNode(data);
	struct Node* pMove = headNode;
	for (int i = 0; i < insertNum; i++) {
		pMove = pMove->next;
		if (pMove->next == NULL) {
			pMove->next = newNode;
			return;
		}
	}
	newNode->next = pMove->next;
	pMove->next = newNode;
}
//ָ��λ��ɾ��
void deletNodeByMod(struct Node* headNode, char* deletetNum) {
	if (NULL == headNode->next) {
		return;
	}
	struct Node* pMove = headNode;

	for (pMove; strcmp(pMove->next->data.name, deletetNum); pMove = pMove->next) {
		
		if (pMove->next == NULL) {			
			return;
		}
	}
	struct Node* pDelete = pMove->next;
	pMove->next = pMove->next->next;
	cout << "ɾ���ɹ�!" << endl;

	pDelete == NULL;
	free(pDelete);
	
}

//��ӡ����
void printList(struct Node* headNode) {
	struct Node* pMove = headNode->next;
	printf("����\t�۸�\t����\n");
	while (pMove) {
		//cout << pMove->data.name << endl;
		printf("%s\t%.1f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
		pMove = pMove->next;
	}
}

void wirteInfoFromFile(const char* fileName, struct Node* headNode) {
	FILE* fp = fopen(fileName, "w");
	struct Node* pMove = headNode->next;
	while (pMove != NULL) {
		fprintf(fp, "%s\t%.1f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
		pMove = pMove->next;
	}
	fclose(fp);
}
void readInfoFromFile(const char* fileName, struct Node* headNode) {
	FILE* fp = fopen(fileName, "r");
	
	if (fp == NULL) {
		fp = fopen(fileName, "w+");
	}
	struct bookInfo tempData;
	while (fscanf(fp, "%s\t%f\t%d\n", tempData.name, &tempData.price, &tempData.num)!= EOF) {
		insertNodeByhead(list, tempData);
	}
	fclose(fp);
}

struct Node* searchByName(struct Node* headNode, char* bookName) {
	struct Node* pMove = headNode;
	for (pMove; strcmp(pMove->next->data.name, bookName); pMove = pMove->next) {
		if (pMove->next == NULL) {
			return NULL;
		}
	}
	return pMove->next;
}

//
// ð������
void bubbleSortlist(struct Node* headNode) {
	for (struct Node* p = headNode->next; p != NULL; p = p->next) {
		for (struct Node* q = headNode->next; q->next != NULL; q = q->next) {
			if (q->data.price > q->next->data.price) {
				struct bookInfo tempData = q->data;
				q->data = q->next->data;
				q->next->data = tempData;
			}
		}
	}
}

//1.д����
void makeMenu() {
	cout << "-----------------------------------" << endl;
	cout << "\txxooͼ�����ϵͳ" << endl;
	cout << "\t1.�Ǽ��鼮" << endl;
	cout << "\t2.����鼮" << endl;
	cout << "\t3.�����鼮" << endl;
	cout << "\t4.�黹�鼮" << endl;
	cout << "\t5.�����鼮" << endl;
	cout << "\t6.����鼮" << endl;
	cout << "\t7.ɾ���鼮" << endl;
	cout << "\t8.�����鼮" << endl;
	cout << "\t9.�˳�ϵͳ" << endl;
	
	cout << "-----------------------------------" << endl;
	cout << "�����루1~9��" << endl;
}
//����
void KeyDown() {

	int userKey;
	struct bookInfo tempBook;//��ʱ�����洢�鼮��Ϣ
	struct Node* result = NULL;
	cin >> userKey;
	switch (userKey)
	{

	case Dengji:
		cout << "���Ǽ��鼮��" << endl;
		printf("�����鼮��Ϣ��name,price,num��");
		scanf("%s%f%d", tempBook.name, &tempBook.price, &tempBook.num);
		insertNodeByhead(list, tempBook);
		wirteInfoFromFile("bookinfo.txt", list);
		break;
	case Liulan:
		cout << "������鼮��" << endl;
		printList(list);
		break;
	case Jieyur:
		cout << "�������鼮��" << endl;
		cout << "����������鼮��" << endl;
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			cout << "δ�ҵ�����鼮" << endl;
		}
		else {
			if (result->data.num > 0) {
				result->data.num--;
				cout << "���ĳɹ�" << endl;
			}
			else {
				cout << "�޿��" << endl;
			}
		}

		break;
	case Guihuan:
		cout << "���黹�鼮��" << endl;
		cout << "����������鼮��" << endl;
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			cout << "�Ƿ��鼮��" << endl;
		}
		else {

			result->data.num++;
			cout << "����ɹ�" << endl;

		}
		break;
	case Chazhao:
		cout << "�������鼮��" << endl;
		cout << "����������鼮��" << endl;
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			cout << "δ�ҵ�����鼮" << endl;
		}
		else {
			printf("����\t�۸�\t����\n");
			printf("%s\t%.1f\t%d\n", result->data.name, result->data.price, result->data.num);
		}
		break;
	case Tianjia:
		cout << "������鼮��" << endl;
		break;
	case Shanchu:
		cout << "��ɾ���鼮��" << endl;
		cout << "������ɾ���鼮��" << endl;
		scanf("%s", tempBook.name);
		deletNodeByMod(list, tempBook.name);
		wirteInfoFromFile("bookinfo.txt", list);
		break;
	case Paixu:
		cout << "�������鼮��" << endl;
		bubbleSortlist(list);
		break;
	case Tuichu:
		cout << "~~~�˳�ϵͳ~~~" << endl;
		system("pause");
		exit(0);//�رճ���
		break;
	default:
		cout << "ERROR!!!!!!" << endl;

		break;
	}
	

}


int main() {
	
	list = createHead();
	readInfoFromFile("bookinfo.txt", list);

	
	
	while (1){
		makeMenu();
		KeyDown();
		system("pause");
		system("cls");
	}
	

	return 0;
}
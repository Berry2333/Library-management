
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
enum Menu { xxoo = 0, Dengji, Liulan, Jieyur, Guihuan, Chazhao, Tianjia, Shanchu,Paixu ,Tuichu };

//3.数据设计
	//数据结构
	//数据处理-->图书信息-->容器-->
	// 

//图书信息
struct bookInfo {

	char name[20];
	float price;
	int num;
};
//实现链表
struct Node {
	struct bookInfo data;
	struct Node* next;
};

struct Node* list = NULL;

//创建表头
struct Node* createHead() {
	//动态内存申请
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	//变量基本规则 使用前初始化
	headNode->next = NULL;
	return headNode;
}

//创建节点:为插入做准备
//把用户数据变为结构体变量
struct Node* creatNode(struct bookInfo data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//链表插入 表头法插入
void insertNodeByhead(struct Node* headNode, struct bookInfo data) {
	struct Node* newNode = creatNode(data);
	
	newNode->next = headNode->next;
	headNode->next = newNode;

}
//表尾插入
void insertNodeByTail(struct Node* headNode, struct bookInfo data) {
	struct Node* newNode = creatNode(data);
	struct Node* pMove = headNode;
	while (pMove->next != NULL) {
		pMove = pMove->next;
	}
	pMove->next = newNode;
}
//表中插入
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
//指定位置删除
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
	cout << "删除成功!" << endl;

	pDelete == NULL;
	free(pDelete);
	
}

//打印链表
void printList(struct Node* headNode) {
	struct Node* pMove = headNode->next;
	printf("书名\t价格\t数量\n");
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
// 冒泡排序
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

//1.写界面
void makeMenu() {
	cout << "-----------------------------------" << endl;
	cout << "\txxoo图书管理系统" << endl;
	cout << "\t1.登记书籍" << endl;
	cout << "\t2.浏览书籍" << endl;
	cout << "\t3.借阅书籍" << endl;
	cout << "\t4.归还书籍" << endl;
	cout << "\t5.查找书籍" << endl;
	cout << "\t6.添加书籍" << endl;
	cout << "\t7.删除书籍" << endl;
	cout << "\t8.排序书籍" << endl;
	cout << "\t9.退出系统" << endl;
	
	cout << "-----------------------------------" << endl;
	cout << "请输入（1~9）" << endl;
}
//交互
void KeyDown() {

	int userKey;
	struct bookInfo tempBook;//临时变量存储书籍信息
	struct Node* result = NULL;
	cin >> userKey;
	switch (userKey)
	{

	case Dengji:
		cout << "【登记书籍】" << endl;
		printf("输入书籍信息（name,price,num）");
		scanf("%s%f%d", tempBook.name, &tempBook.price, &tempBook.num);
		insertNodeByhead(list, tempBook);
		wirteInfoFromFile("bookinfo.txt", list);
		break;
	case Liulan:
		cout << "【浏览书籍】" << endl;
		printList(list);
		break;
	case Jieyur:
		cout << "【借阅书籍】" << endl;
		cout << "请输入借阅书籍名" << endl;
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			cout << "未找到相关书籍" << endl;
		}
		else {
			if (result->data.num > 0) {
				result->data.num--;
				cout << "借阅成功" << endl;
			}
			else {
				cout << "无库存" << endl;
			}
		}

		break;
	case Guihuan:
		cout << "【归还书籍】" << endl;
		cout << "请输入借阅书籍名" << endl;
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			cout << "非法书籍名" << endl;
		}
		else {

			result->data.num++;
			cout << "还书成功" << endl;

		}
		break;
	case Chazhao:
		cout << "【查找书籍】" << endl;
		cout << "请输入查找书籍名" << endl;
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			cout << "未找到相关书籍" << endl;
		}
		else {
			printf("书名\t价格\t数量\n");
			printf("%s\t%.1f\t%d\n", result->data.name, result->data.price, result->data.num);
		}
		break;
	case Tianjia:
		cout << "【添加书籍】" << endl;
		break;
	case Shanchu:
		cout << "【删除书籍】" << endl;
		cout << "请输入删除书籍名" << endl;
		scanf("%s", tempBook.name);
		deletNodeByMod(list, tempBook.name);
		wirteInfoFromFile("bookinfo.txt", list);
		break;
	case Paixu:
		cout << "【排序书籍】" << endl;
		bubbleSortlist(list);
		break;
	case Tuichu:
		cout << "~~~退出系统~~~" << endl;
		system("pause");
		exit(0);//关闭程序
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
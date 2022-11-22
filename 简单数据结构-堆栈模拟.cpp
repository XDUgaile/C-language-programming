#include<iostream>
#include<cstdio>
using namespace std;

template<typename T>
struct Node {
	T val;
	Node* nxt;
	Node(T v, Node* n):val(v), nxt(n) {}
};

template<typename T>
class stack {
private:
	Node<T>* head;
	Node<T>* new_node(const T& v, Node<T>* n);
	int sz;
public:
	stack();
	void push(const T& v);
	T pop();
	T top();
	int size();
	bool empty();
	void clear();
};

/*******************
/ ���캯��
/ ��ʼ��szΪ0
/ ��ʼ��headΪNULL
********************/
template<typename T>
stack<T>::stack() {
	sz = 0;
	head = NULL;
}

/*******************
/ ѹ��
/ para v: ѹ��ջ��ֵ
/ return: none
********************/
template <typename T>
void stack<T>::push(const T& v) {
	sz++;
	head = new_node(v, head);
}

/*******************
/ ����
/ return: ջ��Ԫ��
********************/
template <typename T>
T stack<T>::pop() {
	if (sz) {
		T val = top();
		Node<T>* node = head;
		head = head -> nxt;
		delete(node);
		sz--;
		return val;
	}
	else
		return T();
}

/*******************
/ ջ��
/ return: ջ��Ԫ��
********************/
template <typename T>
T stack<T>::top() {
	return head -> val;
}

/*******************
/ ��ȡջ��Ԫ�ظ���
/ return: Ԫ�ظ���
********************/
template<typename T>
int stack<T>::size() {
	return sz;
}

/*******************
/ �ж�ջ�Ƿ�Ϊ��
/ return: Ԫ�ظ���
********************/
template <typename T>
bool stack<T>::empty() {
	return sz == 0;
}

/*******************
/ ���ջ
********************/
template <typename T>
void stack<T>::clear() {
	while (!empty())
		pop();
}

/*******************
/ �½�Ԫ��
/ para v: Ԫ��ֵ
/ para n: Ԫ�ؽڵ�
/ return: Ԫ��
********************/
template <typename T>
Node<T>* stack<T>::new_node(const T& v, Node<T>* n) {
	return new Node<T>(v, n);
}

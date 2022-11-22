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
/ 构造函数
/ 初始化sz为0
/ 初始化head为NULL
********************/
template<typename T>
stack<T>::stack() {
	sz = 0;
	head = NULL;
}

/*******************
/ 压入
/ para v: 压入栈的值
/ return: none
********************/
template <typename T>
void stack<T>::push(const T& v) {
	sz++;
	head = new_node(v, head);
}

/*******************
/ 弹出
/ return: 栈顶元素
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
/ 栈顶
/ return: 栈顶元素
********************/
template <typename T>
T stack<T>::top() {
	return head -> val;
}

/*******************
/ 获取栈中元素个数
/ return: 元素个数
********************/
template<typename T>
int stack<T>::size() {
	return sz;
}

/*******************
/ 判断栈是否为空
/ return: 元素个数
********************/
template <typename T>
bool stack<T>::empty() {
	return sz == 0;
}

/*******************
/ 清空栈
********************/
template <typename T>
void stack<T>::clear() {
	while (!empty())
		pop();
}

/*******************
/ 新建元素
/ para v: 元素值
/ para n: 元素节点
/ return: 元素
********************/
template <typename T>
Node<T>* stack<T>::new_node(const T& v, Node<T>* n) {
	return new Node<T>(v, n);
}

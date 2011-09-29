#ifndef __STACK_H__
#define __STACK_H__

#include "List.h"

template<class T>
class Stack:protected List<T>	{
	
public:
	Stack();
	virtual ~Stack();
	void push(T data);
	int pop();
	T peek();
	bool isEmpty();
};

template<class T>
Stack<T>::Stack(): List()	{
}

template<class T>
Stack<T>::~Stack() {
}

template<class T>
void Stack<T>::push(T a)	{
	this->addTail(a);
}

template<class T>
int Stack<T>::pop()	{
	return removeTail();
}

template<class T>
bool Stack<T>::isEmpty()	{
	return List::isEmpty();
}

template<class T>
T Stack<T>::peek()	{
	return List::peek();
}

#endif
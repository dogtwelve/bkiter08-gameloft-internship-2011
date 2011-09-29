#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "List.h"

template<class T>
class Queue:protected List<T>
{	
public:
	Queue();
	virtual ~Queue();
	void enqueue(T);
	int dequeue();

	T front();
	bool isEmpty();
};

template<class T>
Queue<T>::Queue(): List()	{
}

template<class T>
Queue<T>::~Queue() {
}

template<class T>
void Queue<T>::enqueue(T data) {
	this->addTail(data);
}

template<class T>
int Queue<T>::dequeue() {
	return removeHead();
}

template<class T>
bool Queue<T>::isEmpty() {
	return List::isEmpty();
}

template<class T>
T Queue<T>::front()	{
	return List::front();
}

#endif
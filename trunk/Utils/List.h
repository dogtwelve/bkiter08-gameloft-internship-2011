#ifndef __LIST_H__
#define __LIST_H__
//hao edit
#ifndef NULL
#define NULL 0
#endif

template<class T>
class List	{
	struct Node {
		T data;
		Node* next;
	};
public:
	List();
	virtual ~List();
	void addHead(T data);
	void addTail(T data);
	int removeHead();
	int removeTail();

	T front();
	T peek();
	bool isEmpty();
private:
	Node* pHead;
};



template<class T>
List<T>::List(): pHead(NULL)
{

}

template<class T>
List<T>::~List()
{
	Node* ptr;
	while(pHead != NULL) {
		ptr = pHead;
		pHead = pHead->next;
		delete ptr;
	}
}

template<class T>
void List<T>::addHead(T data)
{
	Node* node = new Node;
	node->data = data;
	node->next = pHead;
	pHead = node;
}

template<class T>
void List<T>::addTail(T data)
{
	if(isEmpty()) {
		addHead(data);
		return;
	}

	Node* ptr = pHead;
	while(ptr->next != NULL) {
		ptr = ptr->next;
	}

	Node* node = new Node;
	node->data = data;
	node->next = NULL;
	ptr->next = node;
}

template<class T>
int List<T>::removeHead()
{
	if(isEmpty()) {
		return -1;		
	} else {
		Node* ptr = pHead;
		pHead = pHead->next;
		delete ptr;
		return 0;
	}
}

template<class T>
int List<T>::removeTail()
{
	if(isEmpty()) {
		return -1; 
	} else if(pHead->next == NULL) {
		delete pHead;
		pHead = NULL;
	} else {
		Node* ptr = pHead->next;
		Node* prev = pHead;
		while(ptr->next != NULL) {
			prev = ptr;
			ptr = ptr->next;
		}
		prev->next = NULL;
		delete ptr;
	}
	return 0;
}

template<class T>
T List<T>::peek()
{
	if(isEmpty()) {
		return NULL;
	} else {
		Node* ptr = pHead;
		while(ptr->next != NULL) {
			ptr = ptr->next;
		}
		return ptr->data;
	}
}

template<class T>
T List<T>::front()
{
	if(isEmpty()) {
		return NULL;
	} else {
		return pHead->data;
	}
}

template<class T>
bool List<T>::isEmpty() 
{
	return (pHead == NULL);
}

#endif
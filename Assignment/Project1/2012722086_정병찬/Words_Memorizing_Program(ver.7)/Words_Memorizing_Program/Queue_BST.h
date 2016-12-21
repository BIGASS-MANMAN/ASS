#pragma once
template<class T>
class Queue_BST
{
private:
	T* queue;
	int front, rear, capacity;

public:
	Queue_BST(int queuecapacity = 10);
	bool IsEmpty() const;
	T& Front() const;
	T& Rear() const;
	void Push(const T& item);
	void Pop();
};

//Create queue with size of capacity by using dynamic alloation
template<class T>
inline Queue_BST<T>::Queue_BST(int queuecapacity) : capacity(queuecapacity)
{
	if (capacity < 1) throw"Queue capacity must be > 0";
	queue = new T[capacity];
	front = rear = 0;
}

// Check whether queue is empty
template<class T>
inline bool Queue_BST<T>::IsEmpty() const
{
	return front == rear;
}

// Get the front element of queue
template<class T>
inline T & Queue_BST<T>::Front() const
{
	if (IsEmpty()) throw"Queue is empty. No front element";
	return queue[(front + 1) % capacity];
}

// Get the rear element of queue
template<class T>
inline T & Queue_BST<T>::Rear() const
{
	if (IsEmpty()) throw"Queue is empty. No rear element";
	return queue[rear];
}

// Push of queue
template<class T>
inline void Queue_BST<T>::Push(const T & x)
{
	if ((rear + 1) % capacity == front)
	{
		T* newQueue = new T[2 * capacity];

		int start = (front + 1) % capacity;
		if (start < 2)
		{
			copy(queue + start, queue + start + capacity - 1, newQueue);
		}
		else
		{
			copy(queue + start, queue + capacity, newQueue);
			copy(queue, queue + rear + 1, newQueue + capacity - start);

		}

		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] queue;
		queue = newQueue;
	}

	rear = (rear + 1) % capacity;
	queue[rear] = x;

}

// Delete the front element of queue
template<class T>
inline void Queue_BST<T>::Pop()
{
	if (IsEmpty()) throw"Queue is empty.Cannot delete";
	front = (front + 1) % capacity;
	queue[front].~T();
}

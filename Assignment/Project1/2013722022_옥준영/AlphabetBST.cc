#include "AlphabetBST.h"

template <class T>
class Stack_alphabet
{
public:
	Stack_alphabet(int stackCapacity = 10);
	bool IsEmpty() const;
	T&Top() const;		// return Top node
	T&Front() const;	// return Front node
	void Push(const T&item);
	void Pop();
	void Pop_Front();
private:
	T *stack;
	int top;
	int capacity;
};

template <class T>
Stack_alphabet<T>::Stack_alphabet(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
inline bool Stack_alphabet<T>::IsEmpty() const { return top == -1; }	// return 1, if class is empty

template <class T>
inline T& Stack_alphabet<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[top];		// return top node
}

template <class T>
inline T& Stack_alphabet<T>::Front() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[0];		// return front node
}

template <class T>
void Stack_alphabet<T>::Push(const T& x)
{
	if (top == capacity - 1)	// capacity is full
	{	// extend capacity
		ChangeSize1D(stack, capacity, 2 * capacity);	
		capacity *= 2;
	}
	stack[++top] = x;
}

template <class T>
void Stack_alphabet<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete";
	stack[top--].~T();		// Deallocate Top node and change top location
}

template <class T>
void Stack_alphabet<T>::Pop_Front()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete";
	stack[0].~T();		// deallocate front data
	for(int i=0; i<capacity-1; i++)		// shift stack one space forward
		stack[i] = stack[i + 1];
	top--;		// change top location
	capacity--;		// decrease capacity
}

// return minimum between n1 and n2
inline int min(const int n1, const int n2)
{
	if (n1 > n2)
		return n2;
	else
		return n1;
}

template <class T>
inline void copy(T first, T last, T dest)	// copy array to new array
{
	while (first < last)
		*dest++ = *first++;
}

template <class T>
inline void ChangeSize1D(T*&a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New lengh must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize);		// number to copy
	copy(a, a + number, temp);		// copy array to new array
	delete[] a;		// deallocate old memory
	a = temp;
}

AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
}

AlphabetBST::~AlphabetBST()
{
	Deallocate(root);		// Dealloacte all node from root
}

void			AlphabetBST::Insert(AlphabetNode * node)	// run
{
	AlphabetNode *p = root, *pp = 0;	// pp is parent of p

	while (p)
	{
		pp = p;
		if (node->GetAlphabet() < p->GetAlphabet()) p = p->GetLeft();		// move left, if p is bigger than node
		else if (node->GetAlphabet() > p->GetAlphabet()) p = p->GetRight();	// move right, if node is bigger than p
	}
	if (root)	// root is not empty
		if (node->GetAlphabet() < pp->GetAlphabet()) pp->SetLeft(node);	// insert node to left of pp, if pp is bigger than node
		else pp->SetRight(node);	// insert node to right of pp
	else root = node;		// node is root

}

bool			AlphabetBST::Print(char * order)						// PRINT
{
	if (WordCnt == 0)
		return 0;
	else
	{	// print data to "log.txt" file and display
		ofstream log;
		log.open("log.txt", ios::app);
		
		if (strcmp(order, "R_PRE") == 0)	// Recursive Preorder
		{
			log << "======== PRINT ========" << endl;
			cout << "======== PRINT ========" << endl;
			R_Preorder(root, order);
			log << "=======================" << endl << endl;
			cout << "=======================" << endl << endl;
			return 1;
		}
		
		if (strcmp(order, "R_IN") == 0)		// Recursive Inorder
		{
			log << "======== PRINT ========" << endl;
			cout << "======== PRINT ========" << endl;
			R_Inorder(root, order);
			log << "=======================" << endl << endl;
			cout << "=======================" << endl << endl;
			return 1;
		}

		if (strcmp(order, "R_POST") == 0)	// Recursive Postorder
		{
			log << "======== PRINT ========" << endl;
			cout << "======== PRINT ========" << endl;
			R_Postorder(root, order);
			log << "=======================" << endl << endl;
			cout << "=======================" << endl << endl;
			return 1;
		}

		if (strcmp(order, "I_PRE") == 0)	// Iterative Preorder
		{
			log << "======== PRINT ========" << endl;
			cout << "======== PRINT ========" << endl;
			I_Preorder(order);
			log << "=======================" << endl << endl;
			cout << "=======================" << endl << endl;
			return 1;
		}

		if (strcmp(order, "I_IN") == 0)		// Iterative Inorder
		{
			log << "======== PRINT ========" << endl;
			cout << "======== PRINT ========" << endl;
			I_Inorder(order);
			log << "=======================" << endl << endl;
			cout << "=======================" << endl << endl;
			return 1;
		}

		if (strcmp(order, "I_POST") == 0)	// Iterative Postorder
		{
			log << "======== PRINT ========" << endl;
			cout << "======== PRINT ========" << endl;
			I_Postorder(order);
			log << "=======================" << endl << endl;
			cout << "=======================" << endl << endl;
			return 1;
		}

		if (strcmp(order, "I_LEVEL") == 0)	// Iterative Levelorder
		{
			log << "======== PRINT ========" << endl;
			cout << "======== PRINT ========" << endl;
			I_Levelorder(order);
			log << "=======================" << endl << endl;
			cout << "=======================" << endl << endl;
			return 1;
		}

		log.close();
		return 0;
	}
	
}


AlphabetNode *	AlphabetBST::Search(char alphabet)			// LOAD, MOVE, TEST, SEARCH, UPDATE
{
	AlphabetNode * cur = root;
	
	while (cur)
	{
		if (alphabet < cur->GetAlphabet())	
			cur = cur->GetLeft();		// move left
		else if (alphabet > cur->GetAlphabet())
			cur = cur->GetRight();		// move right
		else
			return cur;			// return found node
	}
	return 0;		// not found
}

bool AlphabetBST::Save()							// SAVE
{	
	// Save data using preorder 
	Stack_alphabet <AlphabetNode*> s;
	AlphabetNode *cur = root;
	int cnt = 0;		// count saved word
	while (1) {
		while (cur)		// cur is not NULL
		{
			if (cur->GetBST()->Save() == 1)		// success saving word
				cnt++;		// increase count
			s.Push(cur);
			cur = cur->GetLeft();
		}
		if (s.IsEmpty()) break;
		cur = s.Top();
		s.Pop();
		cur = cur->GetRight();
	}
	if (cnt == 0)	// No saved word
		return 0;
	else
		return 1;
}

void	AlphabetBST::alphabet_insert()		// insert alphabet node
{
	char order[] = { 'P','H','X','D','L','T','Z','B','F','J','N','R','V',
					 'Y','A','C','E','G','I','K','M','O','Q','S','U','W' };
	for (int i = 0; i < 26; i++)		// insert alphabet in order array
	{
		AlphabetNode *node = new AlphabetNode;
		node->SetAlphabet(order[i]);
		Insert(node);
	}
	return;
}

int			AlphabetBST::GetCnt()
{
	return WordCnt;
}

void		AlphabetBST::R_Inorder(AlphabetNode * node, char * order)
{
	if (node != '\0')
	{
		R_Inorder(node->GetLeft(), order);
		node->GetBST()->Print(order);
		R_Inorder(node->GetRight(), order);
	}
}

void		AlphabetBST::R_Preorder(AlphabetNode * node, char * order)
{
	if (node != '\0')
	{
		node->GetBST()->Print(order);
		R_Preorder(node->GetLeft(), order);
		R_Preorder(node->GetRight(), order);
	}
}

void		AlphabetBST::R_Postorder(AlphabetNode * node, char * order)
{
	if (node != '\0')
	{
		R_Postorder(node->GetLeft(), order);
		R_Postorder(node->GetRight(), order);
		node->GetBST()->Print(order);
	}
}

void		AlphabetBST::I_Inorder(char * order)
{
	Stack_alphabet <AlphabetNode*> s;
	AlphabetNode *cur = root;
	while (1) {
		while (cur)		// cur is not NULL
		{
			s.Push(cur);
			cur = cur->GetLeft();
		}
		if (s.IsEmpty()) return;
		cur = s.Top();
		s.Pop();
		cur->GetBST()->Print(order);
		cur = cur->GetRight();
	}
}

void		AlphabetBST::I_Preorder(char * order)
{
	Stack_alphabet <AlphabetNode*> s;
	AlphabetNode *cur = root;
	while (1) {
		while (cur)		// cur is not NULL
		{
			cur->GetBST()->Print(order);
			s.Push(cur);
			cur = cur->GetLeft();
		}
		if (s.IsEmpty()) return;
		cur = s.Top();
		s.Pop();
		cur = cur->GetRight();
	}
}

void		AlphabetBST::I_Postorder(char * order)
{
	Stack_alphabet <AlphabetNode*> s;
	AlphabetNode *cur = root;
	AlphabetNode *top = '\0';
	do
	{	// move to leftside node
		while (cur)		// cur is not NULL
		{
			if (cur->GetRight())
				s.Push(cur->GetRight());
			s.Push(cur);
			cur = cur->GetLeft();
		}
		cur = s.Top();
		s.Pop();

		
		if (!s.IsEmpty())	// set top data of stack
			top = s.Top();
		else
			top = '\0';
		// if cur has right node and right node equal top node in stack
		if (cur->GetRight() && top == cur->GetRight())
		{
			s.Pop();
			s.Push(cur);
			cur = cur->GetRight();
		}
		else
		{
			cur->GetBST()->Print(order);
			cur = '\0';
		}
	} while (!s.IsEmpty());

}

void		AlphabetBST::I_Levelorder(char * order)
{
	Stack_alphabet <AlphabetNode*> s;
	AlphabetNode *cur = root;
	while (cur)		// cur is not NULL
	{
		cur->GetBST()->Print(order);
		if (cur->GetLeft())s.Push(cur->GetLeft());
		if (cur->GetRight())s.Push(cur->GetRight());
		if (s.IsEmpty()) return;
		cur = s.Front();
		s.Pop_Front();
	}

}

void		AlphabetBST::Deallocate(AlphabetNode* node)		// Deallocate AlphabetNode in class
{	// using recursive manner
	if (node != '\0')
	{
		Deallocate(node->GetLeft());		// Dell
		Deallocate(node->GetRight());
		delete node;
	}
}

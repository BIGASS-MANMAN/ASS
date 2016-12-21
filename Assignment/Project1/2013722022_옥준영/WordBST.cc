#include "WordBST.h"

template <class T>
class Stack_word
{
public:
	Stack_word(int stackCapacity = 10);
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
Stack_word<T>::Stack_word(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
inline bool Stack_word<T>::IsEmpty() const { return top == -1; }		// return 1, if class is empty

template <class T>
inline T& Stack_word<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[top];		// return top node
}

template <class T>
inline T& Stack_word<T>::Front() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[0];		// return front node
}

template <class T>
void Stack_word<T>::Push(const T& x)
{
	if (top == capacity - 1)	// capacity is full
	{	// extend capacity
		ChangeSize1D(stack, capacity, 2 * capacity);	
		capacity *= 2;
	}
	stack[++top] = x;
}

template <class T>
void Stack_word<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete";
	stack[top--].~T();		// Deallocate Top node and change top location
}

template <class T>
void Stack_word<T>::Pop_Front()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete";
	stack[0].~T();		// deallocate front data
	for (int i = 0; i<capacity - 1; i++)	// shift stack one space forward
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
inline void copy(T* first, T* last, T* dest)		// copy array to new array
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

WordBST::WordBST()
{
	root = '\0';
}

WordBST::~WordBST()
{
	Deallocate(root);		// Dealloacte all node from root
}

void		WordBST::Insert(WordNode * node)			// LOAD, MOVE
{
	WordNode *p = root, *pp = 0;	// pp is parent of p
	
	while (p)
	{
		pp = p;
		if (strcmp(node->GetWord(), p->GetWord()) < 0) p = p->GetLeft();		// move left, if p is bigger than node
		else if (strcmp(node->GetWord(), p->GetWord()) > 0) p = p->GetRight();	// move right, if node is bigger than p
	}
	if (root)	// root is not empty
		if (strcmp(node->GetWord(), pp->GetWord()) < 0) pp->SetLeft(node); // insert node to left of pp, if pp is bigger than node
		else pp->SetRight(node);	// insert node to right of pp
	else root = node;		// node is root
}

WordNode *	WordBST::Delete(char * word)				// TEST
{
	WordNode *p = root, *q = 0;		// q is parent of p

	while (p && strcmp(word,p->GetWord())!=0)	
	{
		q = p;
		if (strcmp(word ,p->GetWord()) < 0) p = p->GetLeft();
		else p = p->GetRight();
	}

	if (p == 0)	return 0;	// not found

	if (p->GetLeft() == 0 && p->GetRight() == 0)		// p is leaf node
	{
		if (q == 0) root = 0;		// p is root
		else if (q->GetLeft() == p) q->SetLeft(0);
		else q->SetRight(0);
		return p;
	}

	if (p->GetLeft() != 0 && p->GetRight() == 0)		// p only has left node
	{
		WordNode *prevprev = p, *prev = p->GetLeft(), *curr = p->GetLeft()->GetRight();
		WordNode *temp = new WordNode;		// temp has data of prev
		while (curr)		// search largest word in left subtree
		{
			prevprev = prev;
			prev = curr;		// prev is largest node
			curr = curr->GetRight();
		}
		temp->SetWord(p->GetWord());
		temp->SetMean(p->GetMean());
		p->SetWord(prev->GetWord());		// change word of p
		p->SetMean(prev->GetMean());		// change mean of p
		if (prevprev == p)	prevprev->SetLeft(prev->GetLeft());
		else prevprev->SetRight(prev->GetLeft());
		delete prev;		// deallocate prev
		return temp;
	}
	if (p->GetLeft() == 0 && p->GetRight() != 0)		// p only has right node
	{
		WordNode *prevprev = p, *prev = p->GetRight(), *curr = p->GetRight()->GetLeft();
		WordNode *temp = new WordNode;		// temp has data of prev
		while (curr)		// search smallest word in right subtree
		{
			prevprev = prev;
			prev = curr;		// prev is smallest node
			curr = curr->GetLeft();
		}
		temp->SetWord(p->GetWord());
		temp->SetMean(p->GetMean());
		p->SetWord(prev->GetWord());		// change word of p
		p->SetMean(prev->GetMean());		// change mean of p
		if (prevprev == p)	prevprev->SetRight(prev->GetRight());
		else prevprev->SetLeft(prev->GetRight());
		delete prev;		// deallocate prev
		return temp;
	}
	// p has left and right node
	// find the largest node in the left subtree
	WordNode *prevprev = p, *prev = p->GetLeft(), *curr = p->GetLeft()->GetRight();
	WordNode *temp = new WordNode;		// temp has data of prev
	while (curr)		// search largest word in left subtree
	{
		prevprev = prev;
		prev = curr;		// prev is largest node
		curr = curr->GetRight();
	}
	temp->SetWord(p->GetWord());
	temp->SetMean(p->GetMean());
	p->SetWord(prev->GetWord());		// change word of p
	p->SetMean(prev->GetMean());		// change mean of p
	if (prevprev == p)	prevprev->SetLeft(prev->GetLeft());
	else prevprev->SetRight(prev->GetLeft());
	delete prev;
	return temp;
}


WordNode *	WordBST::Search(char * word)				// ADD, TEST, SEARCH, UPDATE
{
	WordNode *cur = root;

	while (cur)
	{
		if (strcmp(word,cur->GetWord()) < 0)
			cur = cur->GetLeft();
		else if (strcmp(word,cur->GetWord()) > 0)
			cur = cur->GetRight();
		else
			return cur;
	}
	return 0;		// not found
}


bool		WordBST::Print(char * order)							// PRINT
{	// print data to "log.txt" file and display
	if (root == '\0')
		return 0;
	else
	{
		if (strcmp(order, "R_PRE") == 0)	// Recursive Preorder
		{
			R_Preorder(root);
			return 1;
		}
		if (strcmp(order, "R_IN") == 0)		// Recursive Inorder
		{
			R_Inorder(root);
			return 1;
		}
		if (strcmp(order, "R_POST") == 0)	// Recursive Postorder
		{
			R_Postorder(root);
			return 1;
		}
		if (strcmp(order, "I_PRE") == 0)	// Iterative Preorder
		{
			I_Preorder();
			return 1;
		}
		if (strcmp(order, "I_IN") == 0)		// Iterative Inorder
		{
			I_Inorder();
			return 1;
		}
		if (strcmp(order, "I_POST") == 0)	// Iterative Postorder
		{
			I_Postorder();
			return 1;
		}
		if (strcmp(order, "I_LEVEL") == 0)	// Iterative Levelorder
		{
			I_Levelorder();
			return 1;
		}
		return 0;		// incorrect order
	}
}

bool		WordBST::Save()								// SAVE
{
	if (root == '\0')
		return 0;
	else
	{	// print data to "memorizing_word.txt" file
		ofstream fout;
		fout.open("memorizing_word.txt", ios::app);
		Stack_word <WordNode*> s;
		WordNode *cur = root;
		while (1) {
			while (cur)
			{
				fout << cur->GetWord() << "\t" << cur->GetMean() << endl;
				s.Push(cur);
				cur = cur->GetLeft();
			}
			if (s.IsEmpty()) break;
			cur = s.Top();
			s.Pop();
			cur = cur->GetRight();
		}
		fout.close();
		return 1;
	}
}

void		WordBST::visit(WordNode* node)		// Print WordNode data
{	// print data to "log.txt" file and display
	ofstream log;
	log.open("log.txt", ios::app);
	log << node->GetWord() << " " << node->GetMean() << endl;
	cout << node->GetWord() << " " << node->GetMean() << endl;
	log.close();
}

void		WordBST::R_Preorder(WordNode* node)
{
	if (node != '\0')
	{
		visit(node);
		R_Preorder(node->GetLeft());
		R_Preorder(node->GetRight());
	}
}

void		WordBST::R_Inorder(WordNode* node)
{
	if (node != '\0')
	{
		R_Inorder(node->GetLeft());
		visit(node);
		R_Inorder(node->GetRight());
	}
}

void		WordBST::R_Postorder(WordNode* node)
{
	if (node != '\0')
	{
		R_Postorder(node->GetLeft());
		R_Postorder(node->GetRight());
		visit(node);
	}
}


void		WordBST::I_Inorder()
{
	Stack_word <WordNode*> s;
	WordNode *cur = root;
	while (1){
		while (cur)		// cur is not NULL
		{
			s.Push(cur);
			cur = cur->GetLeft();
		}
		if (s.IsEmpty()) return;
		cur = s.Top();
		s.Pop();
		visit(cur);
		cur = cur->GetRight();
	}
}

void		WordBST::I_Preorder()
{
	Stack_word <WordNode*> s;
	WordNode *cur = root;
	while (1) {
		while (cur)		// cur is not NULL
		{
			visit(cur);
			s.Push(cur);
			cur = cur->GetLeft();
		}
		if (s.IsEmpty()) return;
		cur = s.Top();
		s.Pop();
		cur = cur->GetRight();
	}
}

void		WordBST::I_Postorder()
{
	if (root == '\0')
		return;
	Stack_word <WordNode*> s;
	WordNode *cur = root;
	WordNode *top = '\0';
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
			visit(cur);
			cur = '\0';
		}
	} while (!s.IsEmpty());
}

void		WordBST::I_Levelorder()
{
	Stack_word <WordNode*> s;
	WordNode *cur = root;
	while (cur)		// cur is not NULL
	{
		visit(cur);
		if (cur->GetLeft())s.Push(cur->GetLeft());
		if (cur->GetRight())s.Push(cur->GetRight());
		if (s.IsEmpty()) return;
		cur = s.Front();
		s.Pop_Front();
	}
}

void		WordBST::Deallocate(WordNode* node)		// Deallocate WordNode in class
{	// using recursive manner
	if (node != '\0')
	{
		Deallocate(node->GetLeft());
		Deallocate(node->GetRight());
		if (node->GetWord() != '\0')
			delete[] node->GetWord();
		if (node->GetMean() != '\0')
			delete[] node->GetMean();
		delete node;
	}

}



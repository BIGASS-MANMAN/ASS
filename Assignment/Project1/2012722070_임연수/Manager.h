#ifndef _MANAGER_H_ // to avoid duplicated definition, use the identification symbol '_MANAGER_H_'
#define _MANAGER_H_

/* it used to constant MACRO				 */ 
/* the definition about some of file's names */
#define TO_MEMORIZE			"to_memorize_word.txt"
#define MEMORIZING			"memorizing_word.txt" 
#define MEMORIZED			"memorized_word.txt"
#define ADD_FILENAME		"word.txt"


/* about implementation alphabet binary search tree */
#define LETTERS			26
#define InitLETTERING	"phxdltzbfjnrvyacegikmoqsuw"

/* including some of header files that we need */
#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h" 
/* the declaration of the class named 'Manager' */
class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	char *argv[2];				// it works like argument vectors because it seems like arguments about the one-line command 

	Manager();					// The constructor of the class named 'Manager'
	~Manager();					// The destructor of the class named 'Manager' 

	void run(const char * command);	// to implement system, this function sets some of init-values.
									// for example, it implements the alphabet bst, reads the some of files, excutes command line by line.
	bool LOAD();				// LOAD some of text files about data-bases of each data structures,   				
	bool ADD();					// ADD the text file called by 'word.txt' that stored dictionary files that have already not used.
	bool MOVE();				// MOVE the node from TO_MEMORIZE(queue) to MEMORIZING(bst).
	bool SAVE();				// SAVE the node from each data structures(queue, bst, cll) to each file.
	bool TEST();				// TEST whether you remember the mean or not. if success, move the node from MEMORIZING(bst) to MEMORIZED(cll).
	bool SEARCH();				// SEARCH the word, and then show it's mean.	 
	bool PRINT();				// PRINT data-bases in one of data-sturutures, 
								// it can sometimes get the special option, how odering(traversal) is.
	bool UPDATE();				// UPDATE the mean about the word to parameter value.
};

#endif

SURC = main.cc Manager.h Manager.cc Queue.h Queue.cc AlphabetBST.h AlphabetBST.cc AlphabetNode.h AlphabetNode.cc WordBST.h WordBST.cc WordNode.h WordNode.cc CircularLinkedList.h CircularLinkedList.cc
EXEC = wordbook
CC = g++
all: $(SURC)
	$(CC) -o $(EXEC) $^
clean:
	rm -rf $(EXEC)
	rm -rf *.bak
	rm -rf *~


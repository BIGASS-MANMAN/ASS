#include "request.h"

request::request()
{
	ShortestPath = '\0';
	index = 0;
	from = '\0';
	to = '\0';
	badwidth = 0;
	S_Next = '\0';
	F_Next = '\0';
}
request::request(int Index, char From, char To, int Bandwidth)
{
	index = Index;
	from = From;
	to = To;
	badwidth = Bandwidth;
	S_Next = '\0';
	F_Next = '\0';

}
void request::setShortPath(node* path, int count, node* adjList)
{
	ShortestPath = new node[count];
	int i = 0, j = 0, cnt = 0;
	node* pCur = adjList;
	node temp;

	while (pCur->getID()!=this->to)
	{
		pCur = pCur->getNext();
	}

	ShortestPath[j] = *pCur;
	i = pCur->getIndex();
	j++;
		
	
	while ((&path[i])->getID() != '\0')
	{
		if ((&path[i])->getID() == this->from)
		{
			ShortestPath[j] = path[(&path[i])->getIndex()];
			break;
		}
		ShortestPath[j] = path[i];
		j++;
		i = (&path[i])->getIndex();
	}

	i = 0;
	for (i; ShortestPath[i].getID() != '\0'; i++)
	{
		cnt++;
	}

	j = 0;
	i = cnt-1;
	for (j; j < (cnt /2); j++)
	{
		temp = ShortestPath[j];
		ShortestPath[j] = ShortestPath[i];
		ShortestPath[i] = temp;
		i--;
	}
}
node* request::getShortPath()
{
	return this->ShortestPath;
}

void request::setS_Next(request* pNext)//set success request's next request
{
	S_Next = pNext;
}
void request::setF_Next(request* pNext)//set fail request's next request
{
	F_Next = pNext;
}
void request::setLF_S_Next(request* pNext)
{
	LF_S_Next = pNext;
}
void request::setLF_F_Next(request* pNext)
{
	LF_F_Next = pNext;
}
request* request::getS_Next()//return success request's next request
{
	return S_Next;
}
request* request::getF_Next()//return fail request's next request
{
	return F_Next;
}
request* request::getLF_S_Next()
{
	return LF_S_Next;
}
request* request::getLF_F_Next()
{
	return LF_F_Next;
}

int request::getIndex()
{
	return this->index;
}
int request::getBandwidth()
{
	return this->badwidth;
}

char request::getFrom()
{
	return this->from;
}
char request::getTo()
{
	return this->to;
}
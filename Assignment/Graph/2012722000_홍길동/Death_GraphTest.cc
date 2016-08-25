#include "/usr/local/Auto_Scoring_System/Assignment/Graph/2012722000_홍길동/LeftistTree.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Graph/2012722000_홍길동/Manager.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Graph/2012722000_홍길동/dijkstra.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Graph/2012722000_홍길동/edge.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Graph/2012722000_홍길동/graph.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Graph/2012722000_홍길동/node.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Graph/2012722000_홍길동/request.h"
#include "gtest/gtest.h"

class GraphTest : public testing::Test {
    protected:
	virtual void SetUp() {
	    manager.ProcessRoute("route.in");
	}

	char* Graph_traversal(Manager M)
	{
	    char arr[1024]={0,};
	    node* nodeCur = M.getGraphRoot();
	    edge* edgeCur = '\0';
	    int index = 0;
	    while(nodeCur != '\0')
	    {
		edgeCur = nodeCur->getEdge();
		while(edgeCur != '\0')
		{
		    arr[index++] = edgeCur->getFrom()->getID();
		    arr[index++] = edgeCur->getTo()->getID();
		    edgeCur = edgeCur->getNext();
		}
		nodeCur = nodeCur->getNext();
	    }
	    cout<<arr<<endl;
	    return arr;
	}

	Manager manager;
};

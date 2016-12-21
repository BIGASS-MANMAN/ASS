#include"Manager.h"
#include <iostream>
using namespace std;

int main(void)
{
	ofstream flog;
	flog.open("log.txt", ios::trunc); // delete log.txt
	flog.close();
	Manager manager;
	AlphabetNode A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
	A.SetAlphabet('A');
	B.SetAlphabet('B');
	C.SetAlphabet('C');
	D.SetAlphabet('D');
	E.SetAlphabet('E');
	F.SetAlphabet('F');
	G.SetAlphabet('G');
	H.SetAlphabet('H');
	I.SetAlphabet('I');
	J.SetAlphabet('J');
	K.SetAlphabet('K');
	L.SetAlphabet('L');
	M.SetAlphabet('M');
	N.SetAlphabet('N');
	O.SetAlphabet('O');
	P.SetAlphabet('P');
	Q.SetAlphabet('Q');
	R.SetAlphabet('R');
	S.SetAlphabet('S');
	T.SetAlphabet('T');
	U.SetAlphabet('U');
	V.SetAlphabet('V');
	W.SetAlphabet('W');
	X.SetAlphabet('X');
	Y.SetAlphabet('Y');
	Z.SetAlphabet('Z');
	manager.bst->Insert(&P);
	manager.bst->Insert(&H);
	manager.bst->Insert(&X);
	manager.bst->Insert(&D);
	manager.bst->Insert(&L);
	manager.bst->Insert(&T);
	manager.bst->Insert(&Z);
	manager.bst->Insert(&B);
	manager.bst->Insert(&F);
	manager.bst->Insert(&J);
	manager.bst->Insert(&N);
	manager.bst->Insert(&R);
	manager.bst->Insert(&V);
	manager.bst->Insert(&Y);
	manager.bst->Insert(&A);
	manager.bst->Insert(&C);
	manager.bst->Insert(&E);
	manager.bst->Insert(&G);
	manager.bst->Insert(&I);
	manager.bst->Insert(&K);
	manager.bst->Insert(&M);
	manager.bst->Insert(&O);
	manager.bst->Insert(&Q);
	manager.bst->Insert(&S);
	manager.bst->Insert(&U);
	manager.bst->Insert(&W);
	manager.run("command.txt");
	return 0;


}

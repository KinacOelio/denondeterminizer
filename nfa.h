#include <stdbool.h>
typedef struct _nfa{
	bool lambda;
	char* alphabet;
	char* states;
	int Ntokens;
	int Nstates;
	char transitionFunction[100][100][100];
} NFA;
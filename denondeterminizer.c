#include "nfa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

NFA constructor();
void lambdaClosure(NFA nfa, char* state, char* closure);
NFA inputTransitionFunction(NFA nfa);
NFA determinizer(NFA itf);

void main(){
	//[state][token][product(S)]
	//the 1st column is reserved for the empty string token lambda
	NFA nfa = constructor();
	char closure[100];
	lambdaClosure(nfa, "2", closure);
	printf("%s\n", closure);
	NFA itf = inputTransitionFunction(nfa);
	printf("asd %s\n", itf.transitionFunction[2][2]);
	//NFA dfa = determinizer(itf);
}


//takes the file and returns a built nfa
NFA constructor(){ 
	NFA nfa;
	nfa.Ntokens = 0;
	nfa.Nstates = 0;
	char line[100];
	int rowPos = 0;
	while(fgets(line, 100, stdin) != 0){
		char* element = strtok(line, ",");
		int colPos = 0;
		nfa.Ntokens = 0;
		while(element != 0){
			printf("%i\n", rowPos);
			printf("element: %s\n", element);
			strcpy(nfa.transitionFunction[rowPos][colPos], element);
			element = strtok(0, ",");
			colPos++;
			nfa.Ntokens++;
		}
		rowPos++;
		nfa.Nstates++;
	}
	nfa.Ntokens--;
	nfa.Nstates--;
	return nfa;
}


void lambdaClosure(NFA nfa, char* state, char* closure){
	int cursor = 0;
	strcpy(closure, state);
	//for each element if the state set sent
	while(state[cursor] != 0){
		//if there is something in the lambda transition
		//the '/' is the equivalent of chartostring + 1
		if(nfa.transitionFunction[state[cursor]-'/'][1] != 0){
			//for each element in the lambda transition
			int cursor2 = 0;
			char* lambdaArray = nfa.transitionFunction[state[cursor]-'/'][1];
			while(lambdaArray[cursor2] != 0){
				//if that element is not already in the closure
				char charToStringTemp[1];
				charToStringTemp[0] = lambdaArray[cursor2];
				if(strstr(closure, charToStringTemp) == 0){
					//add it to the closure
					strcat(closure, charToStringTemp);
				}
				cursor2++;
			}
		}												
		cursor++;
	}

}

NFA inputTransitionFunction (NFA nfa){
	int row = 1;
	NFA itf;
	char* state = nfa.transitionFunction[row][0];
	//for each state of the NFA
	while(row <= nfa.Nstates){
		printf("state: %s\n", state);
		int col = 2;
		char* token = nfa.transitionFunction[0][col];
		//for each token if the nfa
		while(col <= nfa.Ntokens){
			printf("token: %s\n", token);
			//Here is where the actual itf value is generated
			char nfaStateClosure[11];
			lambdaClosure(nfa, state, nfaStateClosure);
			int cursor = 0;
			//for each element of the lambda closure of the state
			while(nfaStateClosure[cursor] != 0){
				char secondaryClosure[11];
				lambdaClosure(nfa, nfa.transitionFunction[row][col], secondaryClosure);		
				printf("secondaryClosure element%s\n", nfa.transitionFunction[row][col]);
				printf("secondaryClosure: %s\n", secondaryClosure);
				//if(strcmp(secondaryClosure, "N") != 0 && strstr(itf.transitionFunction[row][col], secondaryClosure) == 0)
				strcat(itf.transitionFunction[row][col], secondaryClosure);
				printf("new unit: %s row: %i col: %i\n", itf.transitionFunction[row][col], row, col);
				cursor++;
			}
		col++;
		token = nfa.transitionFunction[0][col];
		}
	row++;	
	state = nfa.transitionFunction[row][0];	
	}
	return itf;
}
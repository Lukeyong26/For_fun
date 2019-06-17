// BigNum.c ... LARGE positive integer values

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BigNum.h"

// Initialise a BigNum to N bytes, all zero
void initBigNum (BigNum *bn, int Nbytes)
{
	

	bn->bytes = malloc(sizeof(Byte)*Nbytes);
	assert(bn->bytes != NULL);
	bn->nbytes = Nbytes;
	
	for (int i = 0; i < Nbytes; i++) {
		bn->bytes[i] = '0';
	}
	
	
}

// Add two BigNums and store result in a third BigNum
void addBigNums (BigNum bnA, BigNum bnB, BigNum *res)
{

	int resSize = bnA.nbytes;
	if (resSize < bnB.nbytes) {
		resSize = bnB.nbytes;
	}

	if (res->nbytes < resSize) {
		res->nbytes = resSize;
		res->bytes = realloc(res->bytes, sizeof(Byte)*resSize);
	}
	
	for (int i=0; i < resSize; i++) {
		int A = bnA.bytes[i] - '0';
		int B = bnB.bytes[i] - '0';
		int value =  A + B;
		if (value > 10) {
			res->bytes[i+1] = '1';
		}
		res->bytes[i] += value%10;
	}
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum (char *s, BigNum *bn)
{
	if (!isdigit(s[0])) return 0;

	int numStart = 0;
	for (int i=0; i != '\0'; i++) {
		if (isspace(s[i])) continue;
		if (!isdigit(s[i])) {
			numStart = i;
			break;
		}
	}

	int numSize = 0;
	int i = 0;
	while (s[i] != '\0') {
		if(isdigit(s[i])) numSize++;
		if(!isdigit(s[i])) break;
		i++;
	}
	
	int numActual = (numSize - numStart);
	if (bn->nbytes < numActual) {
		bn->nbytes = numActual;
		bn->bytes = realloc(bn->bytes, sizeof(Byte)*numActual);
	}
	
	for (int j=numStart; j <= numSize; j++) {
		bn->bytes[numActual] = s[j]-'0';
		numActual--;
	}
	return 1;
}

// Display a BigNum in decimal format
void showBigNum (BigNum bn)
{
	int start = 0;
	for (int i=bn.nbytes-1; i >=0; i--) {
		if (bn.bytes[i] != '0') {
			start = i;
			break;
		}
	}

	for (int j=start; j >=0; j--) {
		printf("%c",bn.bytes[j]);
	}
}

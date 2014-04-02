//********************************************************************
//                                                                   *
//   Programador : Raúl Negrón          CCOM 3033 Sección 001        * 
//   Num. Est.   : 801-13-4680          Segundo Semestre 2013-14     * 
//   Prelab 10                          Prof. Rafael Arce            *     
//   Archivo     : prelab10.cpp      	Fecha : Abril 1, 2014        *
//                                                                   *
//********************************************************************

#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;


bool isPrime(int n) {
	if (n < 2) return false ;
	else if (n == 2) return true ;
	else if (n % 2 == 0) return false ;
 	else {
		for (int i = 3; (i * i) <= n ; i += 2) {
			if (n % i == 0) return false ;
		}
	}
	
	return true ; 
}

int sumTheEvenElements(int A[], int size) {
	int sum = 0 ;
	for (int i = 0; i < size; i++) {
		if (A[i] % 2 == 0) sum += A[i] ;
	}
	return sum ;
}

int sumTheEvenIndices(int A[], int size) {
	int sum = 0 ;
	for (int i = 0; i < size; i++) {
		if (i % 2 == 0) sum += A[i] ;
	}
	return sum ;
}	

int sumHalfTheArray(int A[], int size) {
	int sum = 0 ;
	int end ;
	if (size % 2 != 0) end = size / 2 + 1 ;
	else end = size / 2 ;
	
	for (int i = 0 ; i < end ; i ++) {
		sum += A[i] ;
	}
	return sum ;
}

int countThePrimes(int A[], int size) {
	int count = 0 ;
	for (int i = 0 ; i < size ; i++) {
		if ( isPrime(A[i]) ) count++ ;
	}
	return count ;
}

int minAbsDifference(int A[], int size) {
	int absMin = abs(A[0] - A[1]) ;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (abs(A[i] - A[j]) < absMin && i != j) 
				absMin = abs(A[i] - A[j]) ;
		}
	}
	return absMin ;
}

void testSumTheEvenElements() {
	int A[] = {1, 5, 11, 17} ;
	assert(sumTheEvenElements(A, 4) == 0) ;
	int B[] = {1, 5, 20} ;
	assert(sumTheEvenElements(B, 3) == 20) ;
	int C[] = {0, 5, 10, 20, 45} ;
	assert(sumTheEvenElements(C, 5) == 30) ;
}

void testSumTheEvenIndices() {
	int A[] = {1, 5, 11, 17} ;
	assert(sumTheEvenIndices(A, 4) == 12) ;
	int B[] = {1, 5, 20} ;
	assert(sumTheEvenIndices(B, 3) == 21) ;
	int C[] = {0, 5, 10, 20, 45} ;
	assert(sumTheEvenIndices(C, 5) == 55) ;
}

void testSumHalfTheArray() {
	int A[] = {1, 5, 11, 17} ;
	assert(sumHalfTheArray(A, 4) == 6) ;
	int B[] = {1, 5, 20} ;
	assert(sumHalfTheArray(B, 3) == 6) ;
	int C[] = {0, 5, 10, 20, 45} ;
	assert(sumHalfTheArray(C, 5) == 15) ;
}

void testCountThePrimes() {
	int A[] = {2, 4, 5, 9, 6, 7} ;
	assert(countThePrimes(A, 6) == 3) ;
	int B[] = {1, 0, 7, 13, 2, -5} ;
	assert(countThePrimes(B, 6) == 3) ;
}

void testMinAbsDifference() {
	int A[] = {10, 5, 11, 17} ;
	assert(minAbsDifference(A, 4) == 1) ;
	int B[] = {0, -5, 20, -3} ;
	assert(minAbsDifference(B, 4) == 2) ;
	int C[] = {0, 5, 10, 20, 45} ;
	assert(minAbsDifference(C, 5) == 5) ;
}

int main() {
	
	testSumTheEvenElements() ;
	testSumTheEvenIndices() ;
	testSumHalfTheArray() ;
	testCountThePrimes() ;
	testMinAbsDifference() ;
	
	return 0 ;
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../E5.h" 

#define EPS 0.01

int main(void) {
  	complexADT comp1 = newComplex( 1, 2 ); // comp1 = 1 + 2i
	complexADT comp2 = newComplex( 2, -3 ); // comp2 = 2 - 3i
	complexADT ans;

	ans = sumaComplex( comp1, comp2 );
	assert( real(ans) - 3 < EPS && imag(ans) + 1 < EPS );
	freeComplex( ans );

	ans = restaComplex( comp1, comp2 );
	assert( real(ans) - 1 < EPS && imag(ans) - 5 < EPS );	
	freeComplex( ans );

	ans = multComplex( comp1, comp2 );
	assert( real(ans) - 8 < EPS && imag(ans) - 1 < EPS );
	freeComplex( ans );

	ans = divComplex( comp1, comp2 );
	assert( real(ans) + 0.31 < EPS && imag(ans) - 0.54 < EPS );
	freeComplex( ans );

	ans = conjuComplex( comp1 );
	assert( real(ans) - 1 < EPS && imag(ans) + 2 < EPS );

	freeComplex( comp1 );
	freeComplex( comp2 );
	freeComplex( ans );

	printf("OK!\n");
}

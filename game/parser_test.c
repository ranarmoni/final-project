#include "parser.h"
#include <stdio.h>

int main(void){
	/*
	int x;
	 */
	int *y,i;
/*
	printf("reading amount\n");
	x =readFixedAmnt();
	printf("%d",x);
	printf("reading amount\n");
	x =readFixedAmnt();
	printf("%d",x);
	printf("reading amount\n");
	x =readFixedAmnt();
	printf("%d",x);
*/

	printf("reading command\n");
	y = readCommand();
	for(i=0;i<4;++i){
		printf("%d",y[i]);
	}

	printf("reading command\n");
	y = readCommand();
	for(i=0;i<4;++i){
		printf("%d",y[i]);
	}

	printf("reading command\n");
	y = readCommand();
	for(i=0;i<4;++i){
		printf("%d",y[i]);
	}
	return 1;
}

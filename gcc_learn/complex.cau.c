#include<stdio.h>
void  main(){
	double counter;
	double res;
	double tmp;
	for(counter=0;counter<2000.0*2000.0*2000.0/20.0+2023;counter+=(5-1)/4){
		tmp=counter/2023;
		res=counter;		
	}
	printf("res is: %f\n",res);
	//return 0;
}

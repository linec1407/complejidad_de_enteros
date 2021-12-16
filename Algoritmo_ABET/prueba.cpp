#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static const int max_fx = 127;
using namespace std;

typedef struct{
	long int num;
	int *arr;
}array_complex;
bool arr_complex_init(array_complex *a,long int n){
	
	a->arr = (int*) calloc(n , sizeof(int));
	
	if(a->arr==NULL){
		return false;
	}
	else{
		a->num = n;
		a->arr[1]=1;// f(1)=1
		for(long int i=2 ; i<n ; i++){
			a->arr[i] = max_fx;
		}
		return true;
	}
	
}
int g_x(int n){
    
	if(n%3==0){
		n = n/3;
		return pow(3,n);
	}
	else if(n%3==1){
		n = n/3;
		return pow(3,n-1)*4;
	}
	else{
		n = n/3;
		return pow(3,n)*2;
	}
}
void sumandos_f_x(array_complex *a,long int n){
	
	long int limit_n;
	int num,k;
	
	num = a->arr[n-1];//f(n-1)
	
	k = num/2;
	while(g_x(k) + g_x(num-k) < n ){
		k--;
	}
	limit_n = g_x(k);
	
	for(long int i=1;i<=limit_n;i++){
		if(a->arr[n] > a->arr[i] + a->arr[n-i]){
			a->arr[n] = a->arr[i] + a->arr[n-i];
		}
	}
}
void multiplos_f_x(array_complex *a,long int n){
	for(int i=2;i<=n and i*n < a->num;i++){
		if(a->arr[i*n] > a->arr[i] + a->arr[n]){
			a->arr[i*n] = a->arr[i] + a->arr[n];
		}
	}
}
int main(int argc, char *argv[]){
	
    array_complex f_x;
    if(argc>1){
    	sscanf(argv[1], "%u", &(f_x.num));
	}
	else{
	    cout<<"No hay argumentos."<<endl;	
	    return 1;
	}
    
    if(!arr_complex_init(&f_x,f_x.num)){
    	cout<<"No hay suficiente espacio de memoria."<<endl;
    	return 2;
	}
	for(long int i=1 ; i<f_x.num ; i++){
		sumandos_f_x(&f_x,i);
		multiplos_f_x(&f_x,i);
		cout<<"f("<<i<<")="<<f_x.arr[i]<<endl;
	}
	
	return 0;
}

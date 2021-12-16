#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <time.h>

using namespace std;

ofstream file;

static const int max_fx = 127;


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
void fx_free(array_complex *a){
	a->num = 0;
	free(a->arr);
	a->arr = NULL;
}
int main(){
	
	clock_t start = clock();
	
    array_complex f_x;
    
    cin>>f_x.num;
    
    if(!arr_complex_init(&f_x,f_x.num)){
    	cout<<"No hay suficiente espacio de memoria."<<endl;
    	return 2;
	}
	
	file.open("fuller_output.txt");
	
	for(long int i=2 ; i<f_x.num ; i++){
		sumandos_f_x(&f_x,i);
		multiplos_f_x(&f_x,i);
		cout<<"f("<<i<<")="<<f_x.arr[i]<<endl;
		file<<"f("<<i<<")="<<f_x.arr[i]<<endl;
	}
	
	clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    
    cout<<"\nTime  medido: "<<elapsed<<"segundos.\n";
    file<<"\nTime  medido: "<<elapsed<<"segundos.\n";
	
	fx_free(&f_x);
	
	return 0;
}

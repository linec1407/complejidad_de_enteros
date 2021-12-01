#include <iostream>
#include <stdlib.h>
#include <stdio.h>

static const int max_fx = 127;
using namespace std;

typedef struct{
	int num;
	int *arr;
}array_complex;
bool arr_complex_init(array_complex *a,int n){
	
	a->arr = (int*) calloc(n , sizeof(int));// creamos el vector que almacena las complejidades, de tamaño n
	
	if(a->arr==NULL){// si no se logró crear
		return false;
	}
	else{// sí se logró crear
		a->arr[1]=1;// f(1)=1
		for( int i=2 ; i<n ; i++){
			a->arr[i] = max_fx;
		}
		return true;
	}
	
}
void sumandos_f_x(array_complex *a,int n){
	for(int i=1;i<=n/2;i++){ // f(n) <= f(a) + f(n-a) 
		if(a->arr[n] > a->arr[i] + a->arr[n-i]){
			a->arr[n] = a->arr[i] + a->arr[n-i];
		}
	}
}
void multiplos_f_x(array_complex *a,int n){
	for(int i=2;i<=n and i*n < a->num;i++){// f(n) <= f(d) + f(n/d) 
		if(a->arr[i*n] > a->arr[i] + a->arr[n]){
			a->arr[i*n] = a->arr[i] + a->arr[n];
		}
	}
}
int main(){
    array_complex f_x;
    
    cin>>f_x.num;
    
    if(!arr_complex_init(&f_x,f_x.num)){
    	cout<<"No hay suficiente espacio de memoria."<<endl;
    	return 0;
	}
	for(int i=1 ; i<f_x.num ; i++){
		sumandos_f_x(&f_x,i);
		multiplos_f_x(&f_x,i);
		cout<<"f("<<i<<")="<<f_x.arr[i]<<endl;
	}
	
	
	return 0;
}

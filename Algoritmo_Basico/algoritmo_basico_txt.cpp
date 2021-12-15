#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>

using namespace std;

ofstream file; 

static const int max_fx = 127;

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
    	return 0;
	}
	
	file.open("algoritmo_basico_output.txt");
	
	for(int i=1 ; i<f_x.num ; i++){
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

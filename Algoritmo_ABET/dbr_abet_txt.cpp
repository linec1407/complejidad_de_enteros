//dbr_ABET_txt

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


using namespace std;

ofstream file; 

static const int max_fx = 127;

int arr_bases[262] =  {2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 27, 32, 36, 48, 54, 64, 72, 81, 96, 108, 128, 144, 162, 192,
216, 243, 256, 288, 324, 384, 432, 486, 512, 576, 648, 729, 768, 864, 972, 1024, 1152, 1296, 1458, 1536, 1728, 
1944, 2048, 2187, 2304, 2592, 2916, 3072, 3456, 3888, 4096, 4374, 4608, 5184, 5832, 6144, 6561, 6912, 7776, 8192,
8748, 9216, 10368, 11664, 12288, 13122, 13824, 15552, 16384, 17496, 18432, 19683, 20736, 23328, 24576, 26244,
27648, 31104, 32768, 34992, 36864, 39366, 41472, 46656, 49152, 52488, 55296, 59049, 62208, 65536, 69984, 73728,
78732, 82944, 93312, 98304, 104976, 110592, 118098, 124416, 131072, 139968, 147456, 157464, 165888, 177147,
186624, 196608, 209952, 221184, 236196, 248832, 262144, 279936, 294912, 314928, 331776, 354294, 373248, 393216,
419904, 442368, 472392, 497664, 524288, 531441, 559872, 589824, 629856, 663552, 708588, 746496, 786432, 839808,
884736, 944784, 995328, 1048576, 1062882, 1119744, 1179648, 1259712, 1327104, 1417176, 1492992, 1572864, 1594323, 1679616,
1769472, 1889568, 1990656, 2097152, 2125764, 2239488, 2359296, 2519424, 2654208, 2834352, 2985984, 3145728,
3188646, 3359232, 3538944, 3779136, 3981312, 4194304, 4251528, 4478976, 4718592, 4782969, 5038848, 5308416,
5668704, 5971968, 6291456, 6377292, 6718464, 7077888, 7558272, 7962624, 8388608, 8503056, 8957952, 9437184,
9565938, 10077696, 10616832, 11337408, 11943936, 12582912, 12754584, 13436928, 14155776, 14348907, 15116544,
15925248, 16777216, 17006112, 17915904, 18874368, 19131876, 20155392, 21233664, 22674816, 23887872, 25165824,
25509168, 26873856, 28311552, 28697814, 30233088, 31850496, 33554432, 34012224, 35831808, 37748736, 38263752,
40310784, 42467328, 43046721, 45349632, 47775744, 50331648, 51018336, 53747712, 56623104, 57395628, 60466176,
63700992, 67108864, 68024448, 71663616, 75497472, 76527504, 80621568, 84934656, 86093442, 90699264, 95551488,
100663296, 102036672, 107495424, 113246208, 114791256, 120932352, 127401984, 129140163, 134217728, 136048896,
143327232, 150994944, 153055008, 161243136, 169869312, 172186884, 181398528, 191102976, 201326592};
int lon_bases = 262;

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
bool Dbr_array_init(int ***p_Dbr){
	int **Dbr_arr;
	
	*p_Dbr = (int **) calloc(lon_bases,sizeof(int*)); 
	Dbr_arr= *p_Dbr;
	if(Dbr_arr==NULL){ // No hay espacio de memoria
		return false;
	}
	
	for(int i=0;i<lon_bases;i++){
		Dbr_arr[i] = (int *) calloc(arr_bases[i],sizeof(int));//este vector alamcena los D(b,r) para un b en especìfico 
		if(Dbr_arr[i]==NULL){ // No hay espacio de memoria
		    return false;
	    } 
	}
	Dbr_arr[0][0] = 2;// D(2,0)=2
	Dbr_arr[0][1] = 3;// D(0,1)=3
    return true;
}
bool primo(int num){
	if(num<=1) return false;

	for(int i=2;i<=sqrt(num);i++){
		if(num%i==0) return false;
	}
	return true;
}
int ind_bases(int num){
	
	for(int i=0;i<lon_bases;i++){
		if(arr_bases[i]==num){
			return i;
		}
	}
	return -1;
}
int valor_Dbr(int b,int r,int valor, array_complex *a, int **Dbr_arr){
	int valor_1,valor_2,valor_3,ind,d;
	
	ind = ind_bases(b);
	
	if(primo(b)){// cuando b es primo, D0(b,r) = f(b) + f(r)
		valor = a->arr[b] + a->arr[r];
	}
	else{
		if(r==0){// D(b,0) = f(b)
			valor = a->arr[b];
		}
		// r|b, D(b,r) = f(b) + 1 
		else if(b%r==0 or r==1){
			valor = a->arr[b]+1;
		}
		else if(Dbr_arr[ind][r]!=0 ){
			valor = Dbr_arr[ind][r];
		}
		else{
			if(valor>a->arr[b]+a->arr[r]){// D(b,r) <= f(b) + f(r)
				valor = a->arr[b] + a->arr[r];
			}
			for(int i=0 ; i<ind ; i++){
				d = arr_bases[i];
				if(b % d == 0){// d|b
				
					valor_1 = valor_Dbr(d,r%d,valor,a,Dbr_arr);// D( d , r % d )
					valor_2 = valor_Dbr(b/d,int(r/d),valor,a,Dbr_arr); // D( b/d , [|r/d|])
					valor_3 = valor_1 + valor_2;
					
					if(valor > valor_3){ //D(b,r) <= D(d,r%d) + D(b/d,[|r/d|])
						valor = valor_3;
					}
				}
			}
		}
	}
	
	return valor;
}
void fx_free(array_complex *a){
	a->num = 0;
	free(a->arr);
	a->arr = NULL;
}
void Dbr_free(int **arr){
	int *p;
	for(int i=0;i<lon_bases ; i++){
		p = arr[i];
	}
	free(arr);
	arr = NULL;
}
int main(){
	
	clock_t start = clock();
	int **Dbr,sum_Dbr;
    array_complex f_x;
    float C = 1/(2*log(2))*(5);// Cavg <= 1/(b*log(b)) * Sum_{r=0}^{b-1} D(b,r)
    
    f_x.num = arr_bases[lon_bases-1] + 1;// necesitamos calcular la complejidad hasta la última base
    
    if(!Dbr_array_init(&Dbr)){
    	cout<<"No hay suficiente espacio de memoria."<<endl;
    	return 0;
	}
    if(!arr_complex_init(&f_x,f_x.num)){
    	cout<<"No hay suficiente espacio de memoria."<<endl;
    	return 0;
	}
	
	file.open("dbr_abet_output.txt");
	
	cout<<"Output en \"dbr_abet_output.txt\""<<endl;
	// primero calculamos las complejidades hasta la última base a analizar
	cout<<"calculando complejidades hasta "<<f_x.num-1<<" ..."<<endl;
	for(long int i=2 ; i<f_x.num ; i++){
		sumandos_f_x(&f_x,i);
		multiplos_f_x(&f_x,i);
	}
    // calculamos los D(b,r) para los 2^n*3^m
	for(int i=1 ; i<lon_bases ; i++){
		
		int D_br,b;
		float aux_C;
		sum_Dbr = 0;
		b = arr_bases[i];
		for(int r=0 ; r<b ; r++){
			//cout<<arr_bases[i]<<" "<<i<<" "<<r<<endl;
			//cout<<Dbr[i][r]<<endl;
			
			Dbr[i][r] = valor_Dbr(b,r,2*max_fx,&f_x,Dbr);
			D_br = Dbr[i][r];
			
			sum_Dbr = sum_Dbr + Dbr[i][r];
			
		}
		aux_C = 1/(float(b)*log(float(b)))*float(sum_Dbr);
		
		if(C > aux_C){
			C = aux_C;
		}
		
		cout<<"C = "<<C<<" , "<<"sum_Dbr = "<<sum_Dbr<<" ,b = "<<b<<endl;
		file<<"C = "<<C<<" , "<<"sum_Dbr = "<<sum_Dbr<<" ,b = "<<b<<endl;
	}
	/*
	for(int i=0;i<lon_bases;i++){
		for(int j=0;j<arr_bases[i];j++){
			cout<<Dbr[i][j]<<" ";
		}
		cout<<endl;
	}*/
	clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    
    cout<<"\nTime  medido: "<<elapsed<<"segundos.\n";
    file<<"\nTime  medido: "<<elapsed<<"segundos.\n";
	
	Dbr_free(Dbr);
	fx_free(&f_x);
	return 0;
}


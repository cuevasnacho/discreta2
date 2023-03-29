#include <bits/stdc++.h>
using namespace std;

int primos[5] =  {2, 3, 5, 7, 11}; // Notar que para representar hasta 10 numeros solo necesito guardar los primeros 5 primos 

int main(void){
    int n,i,size,j;
    vector<int>v;
    cout << "Ingresa la cantidad de nodos menor a 10" << endl;
    cin >> n;
    
    //Se cambia facil por un binary search => O(log(cant de primos))
    i = 4; 
    while(primos[i] > n){
        i--;
    }
    size = primos[i+1];

    int* a = (int*)calloc(size,sizeof(int));
    
    // O(M) pero de este no me lo puedo sacar de ninguna forma
    // Una vez obtenido el indice faltaria pushear las conecciones
    for (i = 0; i < n; i++){
        cin >> j;
        if (!a[j%size])
            a[j%size] = j;
        else
            v.push_back(j);
    }

    // A lo sumo O(n*v.size())
    for (auto u: v){
        i = (u%size);
        i++;
        while (!a[i]){
            i = (i + 1) % size;
        }
        a[i] = u;
    }
    cout << "Mostrando mapeo" << endl;
    cout << "Nuevo nombre : " << "Viejo nombre" << endl;

    for (i = 0; i < n; i++){
        cout << i << " : " << a[i] << endl;
    }
    free(a);

}

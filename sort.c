//// Massimo Giaccone 0001029148 - Modulo 2 - 11/01/2022

//  sort.c
//  sort


#include "sort.h"

// funzione scambia, importante per tutti gli ordinamenti
void scambia(element *a, element *b)
{
    element tmp = *a;
     *a = *b;
     *b = tmp;
}

int compare(element e1, element e2){
    
    if(e1<e2)
        return -1;
    else
        if(e1>e2)
            return 1;
    return 0;
    
}

//******* NAIVE SORT *******

//funzione che scandisce l'array e se trova un elemento maggiore, lo assume come new max e ritorna la sua posizione
int trovaPosMax(element v[], int n){
    int i;
    int posMax=0;
    
    for (i=1; i<n; i++)
        if (v[posMax]<v[i]) posMax=i;
    
    return posMax;
}
//codifica naive sort
void naiveSort(element v[], int n){
    int p;
    
    while (n>1) {
    p = trovaPosMax(v,n);
    if (p<n-1) scambia(&v[p],&v[n-1]);
    n--;
    }
}

//confronti necessari O(N^2/2). Ordina anche l'array ordinato.

//******* BUBBLE SORT *******

void bubbleSort(element v[], int n){
    int i;
    int ordinato = 0;
    
    while (n>1 && !ordinato){
        ordinato = 1;
        for (i=0; i<n-1; i++)
            if (compare(v[i], v[i+1]) > 0) {
                scambia(&v[i],&v[i+1]);
                ordinato = 0;
            }
        n--;
    }
}

//Nel caso peggiore confronti necessari O(N^2/2), nel caso migliore O(N); caso medio tra N-1 e N^2/2.

//******* INSERT SORT *******

void insOrd(element v[], int pos){
    int i = pos-1;
    element x = v[pos];
    
    while (i>=0 && x<v[i]) {
        v[i+1]= v[i]; /* crea lo spazio */
        i--;
    }
    v[i+1]=x; /* inserisce l’elemento */
}

void insertSort(int v[], int n){
    int k;
    for (k=1; k<n; k++)
     insOrd(v,k);
}
//Nel caso peggiore confronti necessari O(N^2/2), nel caso migliore N-1; caso medio O(N^2/4).

//******* MERGE SORT *******

//funzione che svolge l'ordinamento.
void merge(element v[], int i1, int i2, int fine, element vout[]) {
    int i=i1, j=i2, k=i1;
    
    while ( i <= i2-1 && j <= fine ) {
    if (compare(v[i], v[j]) < 0)
        vout[k] = v[i++];
    else
        vout[k] = v[j++];
    k++;
    }
    
    while (i<=i2-1){
        vout[k] = v[i++];
        k++;
    }
    
    while (j<=fine){
        vout[k] = v[j++];
        k++;
    }
    for (i=i1; i<=fine; i++)
        v[i] = vout[i];
}

//funzione che suddivide l'array. Utilizza questo per ordinare.
void mergeSort(element v[], int first, int last, element vout[]){
    int mid;
    
    if ( first < last ) {
    mid = (last + first) / 2;
    mergeSort(v, first, mid, vout);
    mergeSort(v, mid+1, last, vout);
    merge(v, first, mid+1, last, vout);
    }
}
//Nel caso migliore O(N+log2(N)).

//******* QUICK SORT *******
void quickSortR(element a[], int iniz, int fine){
    int i, j, iPivot;
    element pivot;
    
    if (iniz < fine){
        i = iniz;
        j = fine;
        iPivot = fine;
        pivot = a[iPivot];
        do{ /* trova la posizione del pivot */
            while (i < j && compare(a[i], pivot) <= 0) i++;
            while (j > i && compare(a[j], pivot) >= 0) j--;
            if (i < j) scambia(&a[i], &a[j]);
        }while (i < j);
     /* determinati i due sottoinsiemi */
      /* posiziona il pivot */
        
      if (i != iPivot && compare(a[i], a[iPivot]) != 0){
      scambia(&a[i], &a[iPivot]);
      iPivot = i;
      }
        
      /* ricorsione sulle sottoparti, se necessario */
      if (iniz < iPivot -1)
          quickSortR(a, iniz, iPivot - 1);
      if (iPivot + 1 < fine)
          quickSortR(a, iPivot + 1, fine);
        
      } /* (iniz < fine) */
     } /* quickSortR */

//Efficiente come il merge sort se si utilizza un pivot corretto. Nel caso contrario, efficienza simile al bubble sort.

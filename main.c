#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int h = 0; // indica la altura que se encuentra cada nodo
int Tamano_ListaBurbuja = 0; // tamaño de las listas tanto de burbuja como quicksort
double TiempoInsertado=0.0;
double TiempoTranscurridoRecorridoArbol=0.0;
double TiempoTrasncurridoOrdenamientoBurbuja=0.0;
double TiempoTranscurridoOrdenamientoQuicksort=0.0;

typedef struct Nume{ // estructra de nodo Numero pero para listasimple para metodo burbuja
    int Num;
    struct Nume *Siguiente;
}Nume;

typedef struct ListaBurbuja{ //lista para insertar datos del archivo (uso en metodo burbuja)
    struct Nume *Primero;
}ListaBurbuja;

typedef struct Numer{ // estructra de nodo Numero pero para listasimple para metodo burbuja
    int Num;
    struct Numer *Siguiente;
    struct Numer *Anterior;
}Numer;

typedef struct ListaQuicksort{
    struct Numer *Primero;
    struct Numer *Ultimo;
}ListaQuicksort;

void InsertarLisaBurbuja(ListaBurbuja *Lista, int num){ // insertar en la lista los datos del archivo Lista simple
    Nume *Nuevo;
    Nuevo = malloc(sizeof(Nume));
    Nuevo->Siguiente = NULL;
    Nuevo->Num = num;

    if(Lista->Primero==NULL){ // si la lista esta vacia
        Lista->Primero= Nuevo;
    }else{
        Nume *NodoAux;
        NodoAux = Lista->Primero;

        while(NodoAux->Siguiente!=NULL){
            NodoAux = NodoAux->Siguiente;
        }
        NodoAux->Siguiente = Nuevo;
        NodoAux = Nuevo;
    }
}

void MostrarListaBur(ListaBurbuja *Lista){ // Muestra la lista donde se inserto y se ordeno en base a burbuja
    Nume *Nodoaux = Lista->Primero;
    while(Nodoaux!=NULL){
        printf("%d ",Nodoaux->Num);
        Nodoaux = Nodoaux->Siguiente;
    }
}

Nume *BuscarNodoBurbuja(ListaBurbuja *Lista,int num){ // busca el nodo suponiendo indices y lo devuelve (funciona como array[indece]
    int ind = 0;
    Nume *Nodoaux = Lista->Primero;
    Nume *NodoRetornado;
    while(Nodoaux!=NULL){
        if(ind==num){
            NodoRetornado = Nodoaux;
            Nodoaux = NULL;
        }else{
            ++ind;
            Nodoaux = Nodoaux->Siguiente;
        }
    }
    return NodoRetornado;
}

void Ordenamiento_Burbuja(ListaBurbuja *ListaBur){ // Ordena todos los datos en sus lista
    int i, j;
    int temp;
    Nume *Nodoauxj;

     for (i=1; i<Tamano_ListaBurbuja; i++){
          for (j=0; j<Tamano_ListaBurbuja - i; j++){
                Nodoauxj = BuscarNodoBurbuja(ListaBur,j);
               if (Nodoauxj->Num > Nodoauxj->Siguiente->Num)
                    {
                    /* Intercambiamos */
                    temp = Nodoauxj->Num;
                    Nodoauxj->Num = Nodoauxj->Siguiente->Num;
                    Nodoauxj->Siguiente->Num = temp;
                    }
            }
        }
}

void InsertarListaQuick(ListaQuicksort *Lista, int num){ // inserta en la lista los datos del archivo Lista doble
    Numer *Nuevo;
    Nuevo = malloc(sizeof(Nume));
    Nuevo->Siguiente = NULL;
    Nuevo->Anterior = NULL;
    Nuevo->Num = num;

    if(Lista->Primero==NULL){ // si la lista esta vacia
        Lista->Primero= Nuevo;
    }else{
        Numer *NodoAux;
        NodoAux = Lista->Primero;

        while(NodoAux->Siguiente!=NULL){
            NodoAux = NodoAux->Siguiente;
        }
        Lista->Ultimo = NodoAux;
        Lista->Ultimo->Siguiente = Nuevo;
        Nuevo->Anterior = Lista->Ultimo;
        Lista->Ultimo = Nuevo;
    }
}

void MostrarListaQuick(ListaQuicksort *Lista){ // Muestra la lista donde se inserto y se ordeno en base a Quicksort
    Numer *Nodoaux = Lista->Primero;
    while(Nodoaux!=NULL){
        printf("%d ",Nodoaux->Num);
        Nodoaux = Nodoaux->Siguiente;
    }
}

Numer *BuscarNodoQuick(ListaQuicksort *Lista,int num){ // busca el nodo suponiendo indices y lo devuelve (funciona como array[indece]
    int indice = 0;
    Numer *Nodoaux = Lista->Primero;
    Numer *NodoRetornado;
    while(Nodoaux!=NULL){
        if(indice==num){
            NodoRetornado = Nodoaux;
            Nodoaux = NULL;
        }else{
            ++indice;
            Nodoaux = Nodoaux->Siguiente;
        }
    }
    return NodoRetornado;
}

int divide(ListaQuicksort *Lista, int start, int end) { // metodo que divive en bloques la lista para poder seguir con el ordenamiento quicksort
    int left;
    int right;
    int pivot;
    int temp;
    Numer *NodoAuxLeft;
    Numer *NodoAuxRight;
    Numer *NodoStart = BuscarNodoQuick(Lista,start);
    pivot = BuscarNodoQuick(Lista,start)->Num;
    left = start;
    right = end;

    // Mientras no se cruzen los índices
    while (left < right) { //left y righ son indecis
        while (BuscarNodoQuick(Lista,right)->Num > pivot) {
            right--;
        }
        NodoAuxRight = BuscarNodoQuick(Lista,right); // obtenemos el ultimo nodo right
        while ((left < right) && (BuscarNodoQuick(Lista,left)->Num <= pivot)) {
            left++;
        }
        NodoAuxLeft = BuscarNodoQuick(Lista,left); // obtenemos el ultimo nodo Left
        // Si todavía no se cruzan los indices seguimos intercambiando
        if (left < right) {
            temp = NodoAuxLeft->Num;
            NodoAuxLeft->Num = NodoAuxRight->Num;
            NodoAuxRight->Num = temp;
        }
    }

    // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
    temp = NodoAuxRight->Num;
    NodoAuxRight->Num = NodoStart->Num;
    NodoStart->Num = temp;

    // La nueva posición del pivot
    return right;
}

void quicksort(ListaQuicksort *Lista, int start, int end){ // Ordena todos los datos en su lista, se amarra del metodo divide
    int pivot;
    if (start < end) {
        pivot = divide(Lista, start, end);
        // Ordeno la lista de los menores
        quicksort(Lista, start, pivot - 1);
        // Ordeno la lista de los mayores
        quicksort(Lista, pivot + 1, end);
    }
}

typedef struct Numero{ // estructura de nodo Numero
    int num;
    int Factor_Equilibrio;
    struct Numero *Izquierdo;
    struct Numero *Derecho;
}Numero;

typedef struct ArbolAVl { // Estructura de arbo AVL
    struct Numero *Raiz;
}ArbolAVl;

ListaBurbuja *ListaBur; // declaracion de variable de la lista burbuja
ListaQuicksort *ListaQuick; // declaracion de variable de la lista quicksort
ArbolAVl *AVL; // Declaracion del arbol AVL

Numero *rotacionII(Numero *Num, Numero *Num1){ //Rotacion Izquierda IZquierda
    Num->Izquierdo = Num1->Derecho;
    Num1->Derecho = Num;
    if(Num1->Factor_Equilibrio==-1){
        Num->Factor_Equilibrio =0;
        Num1->Factor_Equilibrio = 0;
    }
    else{
        Num->Factor_Equilibrio = -1;
        Num1->Factor_Equilibrio = 1;
    }
    return Num1;
}

Numero *rotacionDD(Numero *Num, Numero *Num1){ // Rotacion Derecha derecha
    Num->Derecho = Num1->Izquierdo;
    Num1->Izquierdo = Num;
    if(Num1->Factor_Equilibrio==1){
        Num->Factor_Equilibrio =0;
        Num1->Factor_Equilibrio = 0;
    }
    else{
        Num->Factor_Equilibrio = 1;
        Num1->Factor_Equilibrio = -1;
    }
    return Num1;
}

Numero *rotacionID(Numero *Num, Numero *Num1){ //Rotacion Izquierda Derecha
    Numero *Num2;
    Num2 = Num1->Derecho;
    Num1->Derecho = Num2->Izquierdo;
    Num2->Izquierdo = Num1;
    Num->Izquierdo = Num2->Derecho;
    Num2->Derecho = Num;
    if(Num2->Factor_Equilibrio==1){
        Num1->Factor_Equilibrio = -1;
    }
    else{
        Num1->Factor_Equilibrio=0;
    }
    if(Num2->Factor_Equilibrio==-1){
        Num->Factor_Equilibrio = 1;
    }
    else{
        Num->Factor_Equilibrio=0;
    }
    Num2->Factor_Equilibrio=0;
    return Num2;
}

Numero *rotacionDI(Numero *Num, Numero *Num1){ // Rotacion Derecha Izquierda
    Numero *Num2;
    Num2 = Num1->Izquierdo;
    Num1->Izquierdo = Num2->Derecho;
    Num2->Derecho = Num1;
    Num->Derecho = Num2->Izquierdo;
    Num2->Izquierdo = Num;
    if(Num2->Factor_Equilibrio==1){
        Num->Factor_Equilibrio = -1;
    }
    else{
        Num->Factor_Equilibrio=0;
    }
    if(Num2->Factor_Equilibrio==-1){
        Num1->Factor_Equilibrio = 1;
    }
    else{
        Num1->Factor_Equilibrio=0;
    }
    Num2->Factor_Equilibrio=0;
    return Num2;
}

Numero *InsertarAVL(Numero *Nodo, int num){ // Agregar al AVL con Rotaciones
    Numero *Nodoaux;
    if(Nodo==NULL){
        //printf("inserto nuevo\n");
        Numero *Nuevo;
        Nuevo = (Numero *)malloc(sizeof(Numero));
        Nodo = Nuevo;
        Nodo->num = num;
        Nodo->Derecho = NULL;
        Nodo->Izquierdo = NULL;
        Nodo->Factor_Equilibrio=0;
        h = 1;
    }

    else{
        if(Nodo->num > num){
            //printf("Izq!\n");
            Nodo->Izquierdo = InsertarAVL(Nodo->Izquierdo,num);
            if(h!=0){
                switch(Nodo->Factor_Equilibrio){
                    case 1:
                        Nodo->Factor_Equilibrio = 0;
                        h=0;
                        break;
                    case 0:
                        Nodo->Factor_Equilibrio = -1;
                        break;
                    case -1:
                        Nodoaux = Nodo->Izquierdo;
                        if(Nodoaux->Factor_Equilibrio==-1){
                            Nodo = rotacionII(Nodo,Nodoaux);
                        }
                        else{
                            Nodo = rotacionID(Nodo,Nodoaux);
                        }
                        h=0;
                        break;
                }
            }
        }
        else if(Nodo->num < num){
            //printf("Der\n");
            Nodo->Derecho = InsertarAVL(Nodo->Derecho,num);
            if(h!=0){
                switch(Nodo->Factor_Equilibrio){
                    case 1:
                        Nodoaux = Nodo->Derecho;
                        if(Nodoaux->Factor_Equilibrio==1){
                            Nodo = rotacionDD(Nodo,Nodoaux);
                        }
                        else{
                            Nodo = rotacionDI(Nodo,Nodoaux);
                        }
                        h=0;
                        break;
                    case 0:
                        Nodo->Factor_Equilibrio = 1;
                        break;
                    case -1:
                        Nodo->Factor_Equilibrio = 0;
                        h=0;
                        break;
                }
            }
        }
        else{
            h=0;
        }
    }
    return Nodo;
}

void verAvl(Numero *Nodo){ // Mostrar el AVL para verificacion de insercion
    if(Nodo==NULL){
        return;
    }
    int Numaux = Nodo->num;
    printf("%d",Numaux);
    verAvl(Nodo->Izquierdo);
    verAvl(Nodo->Derecho);
}

void RecorridoINORDEN(Numero *Nodo){ //Recorrido del arbol AVL en orden
    if(Nodo==NULL){
        return;
    }
    RecorridoINORDEN(Nodo->Izquierdo);
    int Numaux = Nodo->num;
    printf("%d ",Numaux);
    RecorridoINORDEN(Nodo->Derecho);
}

double timeval_diff(struct timeval *a, struct timeval *b){
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

struct timeval t_ini, t_fin;

void LeerArchivo(char* NombreArchivo){ // lee el archivo que contiene los datos

    FILE* Archivo=NULL;
    char Lectura_PorLinea[100];
    int endFile=0;
    Archivo = fopen(NombreArchivo,"r");
    if(Archivo==NULL) return -1;
    endFile = fscanf(Archivo," %[^\n]",&Lectura_PorLinea);
    int n = atoi(Lectura_PorLinea);
    //obtener el tiempo de insertado
    gettimeofday(&t_ini, NULL);
    AVL->Raiz = InsertarAVL(AVL->Raiz,n); // ingresa en el arbol aVL
    gettimeofday(&t_fin, NULL);
    TiempoInsertado = timeval_diff(&t_fin, &t_ini);
    //termina la obtencion del tiempo de insertado
    InsertarLisaBurbuja(ListaBur,n); // ingresa en la lista de burbuja
    InsertarListaQuick(ListaQuick,n); // ingresa en la lista de Quicksort
    Tamano_ListaBurbuja+= 1;
    while(endFile!=EOF){ // mientas la linea sea diferencte de final del archivo
        //printf("%s\n",Lectura_PorLinea);
        endFile = fscanf(Archivo," %[^\n]",&Lectura_PorLinea);
        if(endFile!=EOF){
            int n = atoi(Lectura_PorLinea); // convierte  de un char a un entero
             //obtener el tiempo de insertado
            gettimeofday(&t_ini, NULL);
            AVL->Raiz = InsertarAVL(AVL->Raiz,n); // ingresa en el arbol aVL
            gettimeofday(&t_fin, NULL);
            TiempoInsertado += timeval_diff(&t_fin, &t_ini);
            //termina la obtencion del tiempo de insertado
            InsertarLisaBurbuja(ListaBur,n); // ingresa en la lista burbuja
            InsertarListaQuick(ListaQuick,n); // ingresa en la lista de Quicksort
            Tamano_ListaBurbuja+= 1;
        }
    }
    printf("\nTiempo de ejecución: %lf segundos", TiempoInsertado);
    printf("\nSe ingresaron los datos\n");
    fclose(Archivo);

}

void Menu(){ // muestra el menu de la aplicacio y sus respectivas opciones
    int salir=0;
    int opcion=0;
    char NombreArchivo[250];
    while(salir==0){
        printf("\n----------------------------------------------------------------\n");
        printf("Opciones de la aplicacion:\n");
        printf("1. Ingresar Datos\n");
        printf("2. Recorrido del Arbol (InOrden)\n");
        printf("3. Ordenamiento por metodo burbuja\n");
        printf("4. Ordenamiento por metodo Quicksort\n");
        printf("5. Tiempos\n");
        printf("6. Salir\n");
        printf("\n----------------------------------------------------------------\n");
        printf("Opcion: ");
        scanf("%d",&opcion);
        switch(opcion){
            case 1:
                printf("Ingrese el nombre de archivo para la carga de datos\n");
                fflush(stdin);
                scanf("%s",&NombreArchivo);
                LeerArchivo(NombreArchivo);
                break;
            case 2:
                printf("\nSalida de datos ordenados en el recorrido del AVL...\n");
                gettimeofday(&t_ini, NULL);
                RecorridoINORDEN(AVL->Raiz);
                gettimeofday(&t_fin, NULL);
                TiempoTranscurridoRecorridoArbol = timeval_diff(&t_fin, &t_ini);
                printf("\nTiempo de ejecución: %lf segundos\n", TiempoTranscurridoRecorridoArbol);
                break;
            case 3:
                printf ("\nOrdenamiento de datos con metodo burbuja: \n");
                gettimeofday(&t_ini, NULL);
                Ordenamiento_Burbuja(ListaBur);
                MostrarListaBur(ListaBur);
                gettimeofday(&t_fin, NULL);
                TiempoTrasncurridoOrdenamientoBurbuja = timeval_diff(&t_fin, &t_ini);
                printf("\nTiempo de ejecución: %lf segundos\n", TiempoTrasncurridoOrdenamientoBurbuja);
                break;
            case 4:
                printf("\nOrdenamiento de datos con metodo Quicksort:\n");
                gettimeofday(&t_ini, NULL);
                quicksort(ListaQuick,0,Tamano_ListaBurbuja-1);
                MostrarListaQuick(ListaQuick);
                gettimeofday(&t_fin, NULL);
                TiempoTranscurridoOrdenamientoQuicksort= timeval_diff(&t_fin, &t_ini);
                printf("\nTiempo de ejecución: %lf segundos\n", TiempoTranscurridoOrdenamientoQuicksort);
                break;
            case 5:
                printf("\nTiempos----------------------------:\n");
                printf("Tiempo de insertado en el Arbol AVL: %lf s\n",TiempoInsertado);
                printf("Recorrido de Arbol: %lf s\n",TiempoTranscurridoRecorridoArbol);
                printf("Ordenamiento Burbuja: %lf s\n",TiempoTrasncurridoOrdenamientoBurbuja);
                printf("Ordenamiento QuickSort: %lf s\n",TiempoTranscurridoOrdenamientoQuicksort);
                break;
            case 6:
                salir = 6;
                break;
        }
    }

}

int main(){
    AVL =malloc(sizeof(ArbolAVl));
    ListaBur = malloc(sizeof(ListaBurbuja));
    ListaQuick = malloc(sizeof(ListaQuicksort));
    //AVL->Raiz = InsertarAVL(AVL->Raiz,5);
    //AVL->Raiz = InsertarAVL(AVL->Raiz,10);
    //AVL->Raiz = InsertarAVL(AVL->Raiz,2);
    //AVL->Raiz = InsertarAVL(AVL->Raiz,4);
    //AVL->Raiz = InsertarAVL(AVL->Raiz,1);
    //AVL->Raiz = InsertarAVL(AVL->Raiz,14);
    //AVL->Raiz = InsertarAVL(AVL->Raiz,17);
    Menu();
    //verAvl(AVL->Raiz);
    //RecorridoINORDEN(AVL->Raiz);
    //LeerArchivo("Archivo.txt");

    return 0;
}

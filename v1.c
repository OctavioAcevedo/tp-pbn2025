#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo * next;
}nodo_t;

nodo_t* crearNodo(int dato); //Crea un nodo nuevo con un dato dado.  
void insertarAlInicio(nodo_t** cabeza, int dato); //Inserta un nodo al comienzo de la lista.  
void insertarAlFinal(nodo_t** cabeza, int dato); //Inserta un nodo al final de la lista.  
void eliminarNodo(nodo_t** cabeza, int dato); //Elimina el primer nodo que contenga el dato especificado.  
nodo_t* buscarNodo(nodo_t* cabeza, int dato); //Devuelve un puntero al nodo que contiene el dato (o NULL si no se encuentra).  
void imprimirLista(nodo_t* cabeza); //Imprime todos los elementos de la lista.  
void liberarLista(nodo_t** cabeza); //Libera toda la memoria utilizada por la lista.

int main() {
    nodo_t* cabeza = NULL; // Se inicializa la lista vacía
    int opcion, dato;

    do {
        printf("\n MENÚ \n");
        printf("1. Insertar al inicio \n");
        printf("2. Insertar al final \n");
        printf("3. Eliminar nodo \n");
        //printf("4. Buscar nodo \n");
        printf("5. Imprimir lista \n");
        printf("6. Salir \n"); // implementa liberarLista()
        
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingresar dato a insertar al inicio: ");
                scanf("%d", &dato);
                insertarAlInicio(&cabeza, dato);
                break;
            case 2:
                printf("Ingresar dato a insertar al final: ");
                scanf("%d", &dato);
                insertarAlFinal(&cabeza, dato);
                break;
            case 3:
                printf("Ingresar dato a eliminar: ");
                scanf("%d", &dato);
                eliminarNodo(&cabeza, dato);
                break;
            /*case 4:
                printf("Ingresar dato a buscar: ");
                scanf("%d", &dato);
                if(buscarNodo(cabeza, dato) != NULL) {
                    printf("El dato %d forma parte de la lista.\n", dato);
                } else {
                    printf("El dato %d no forma parte de la lista.\n", dato);
                }
                break;*/
            case 5:
                printf("La lista actual es: ");
                imprimirLista(cabeza);
                break;
            case 6:
                //liberarLista(&cabeza);
                printf("Programa finalizado con éxito \n");
                break;
            default:
                printf("Opción no válida. Ingresar una opción entre 1 y 6 \n");
        }
    } while (opcion != 6);

    return 0;
    
}

int main(){
    nodo_t * nuevo;
    nuevo = crearNodo(5);
    printf("nuevo nodo con valor %d creado\n", nuevo->dato);
    printf("-> inserto 6 al inicio\n");
    insertarAlInicio(&nuevo, 6);
    imprimirLista(nuevo);
    printf("-> borro valor 6\n");
    eliminarNodo(&nuevo,6);
    imprimirLista(nuevo);
    printf("-> borro valor 5\n");
    eliminarNodo(&nuevo,5);
    imprimirLista(nuevo);

    return 0;
}

nodo_t* crearNodo(int dato){
    nodo_t * nuevoNodo;
    nuevoNodo = (nodo_t * ) malloc(sizeof(nodo_t));
    nuevoNodo->dato = dato;
    nuevoNodo->next = NULL;
    return nuevoNodo;
}

void insertarAlInicio(nodo_t** cabeza, int dato){
    nodo_t * nuevoNodo;
    nuevoNodo = (nodo_t * ) malloc(sizeof(nodo_t));
    // por que con nodo_t * nuevaCabeza = (nodo_t * ) malloc(sizeof(nodo_t)); de una no funciona?
    nuevoNodo->dato = dato;
    nuevoNodo->next = *cabeza;
    *cabeza = nuevoNodo;
}

void insertarAlFinal(nodo_t** cabeza, int dato){
    nodo_t * nuevoNodo;
    nodo_t * actual = (*cabeza);

    nuevoNodo = (nodo_t * ) malloc(sizeof(nodo_t));
    nuevoNodo->dato = dato;
    
    while(actual->next != NULL){
        actual = actual->next;
    }
    
    actual->next = nuevoNodo;
}

void eliminarNodo(nodo_t** cabeza, int dato){
    nodo_t * actual = (*cabeza);
    nodo_t * anterior  = NULL;
    struct nodo * siguiente = NULL;
    int valorRetorno;
    int i = 0;

    
    if (actual->dato == dato){
        //hace falta nullear el ->dato?
        if (actual->next){
            siguiente = actual->next;
            free(actual);
            actual = NULL;
            *cabeza = siguiente;
        }else{
            free(*cabeza);
            *cabeza = NULL;
        }
        return;
    }

    while(actual){
        anterior = actual;
        actual = actual->next;
        siguiente = actual->next;

        if (actual->dato == dato){
            anterior->next = siguiente;
            free(actual);
            actual = NULL;
            return;
        }
        actual = actual->next;
    }
};

void imprimirLista(nodo_t* cabeza){
    nodo_t * actual = cabeza;
    int i = 0;

    if (!actual){
        printf("La lista está vacia!\n");
    }

    while(actual){
        printf("elemento %d: %d\n",i,actual->dato);
        i++;
        if (actual->next == NULL){
            break;
        }
        actual = actual->next;
    }
};




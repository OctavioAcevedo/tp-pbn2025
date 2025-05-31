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
void limpiarTerminal();

int main() {
    nodo_t* cabeza = NULL; // Se inicializa la lista vacía
    char opcion;
    int dato;
    limpiarTerminal();
    do {
        printf("MENÚ \n");
        printf("1. Insertar al inicio \n");
        printf("2. Insertar al final \n");
        printf("3. Eliminar nodo \n");
        printf("4. Buscar nodo \n");
        printf("5. Imprimir lista \n");
        printf("6. Liberar lista \n");
        printf("7. Salir \n");
        
        scanf("%s", &opcion);
        limpiarTerminal();

        switch (opcion) {
            case '1':
                limpiarTerminal();
                printf("1. Insertar al inicio \n");
                printf("Ingresar dato a insertar: ");
                scanf("%d", &dato);
                insertarAlInicio(&cabeza, dato);
                break;
            case '2':
                limpiarTerminal();
                printf("2. Insertar al final \n");
                printf("Ingresar dato a insertar: ");
                scanf("%d", &dato);
                insertarAlFinal(&cabeza, dato);
                break;
            case '3':
                limpiarTerminal();
                printf("3. Eliminar nodo \n");
                printf("Ingresar dato a eliminar: ");
                scanf("%d", &dato);
                eliminarNodo(&cabeza, dato);
                break;
            case '4':
                limpiarTerminal();
                printf("4. Buscar nodo \n");
                printf("Ingresar dato a buscar: ");
                scanf("%d", &dato);
                if(buscarNodo(cabeza, dato) != NULL) {
                    printf("El dato %d forma parte de la lista.\n", dato);
                } else {
                    printf("El dato %d no forma parte de la lista.\n", dato);
                }
                break;
            case '5':
                limpiarTerminal();
                printf("5. Imprimir lista \n");
                printf("La lista actual es: ");
                imprimirLista(cabeza);
                break;
            case '6':
                limpiarTerminal();
                printf("6. Limpiar lista \n");
                liberarLista(&cabeza);
                printf("Lista liberada. \n");
                break;
            case '7':
                limpiarTerminal();
                printf("7. Salir \n");
                liberarLista(&cabeza);
                printf("Programa finalizado con éxito \n");
                break;   
            default:
                printf("Opción no válida. Ingresar una opción entre 1 y 7 \n");
        }
    } while (opcion != 7);

    return 0;
    
}

void limpiarTerminal(){
    printf("\e[1;1H\e[2J");
};

nodo_t* crearNodo(int dato){
    nodo_t * nuevoNodo;
    nuevoNodo = (nodo_t * ) malloc(sizeof(nodo_t));
    // por que con nodo_t * nuevaCabeza = (nodo_t * ) malloc(sizeof(nodo_t)); de una no funciona?
    nuevoNodo->dato = dato;
    nuevoNodo->next = NULL;
    return nuevoNodo;
}

void insertarAlInicio(nodo_t** cabeza, int dato){
    nodo_t * nuevoNodo = crearNodo(dato);
    nuevoNodo->next = *cabeza;
    *cabeza = nuevoNodo;
}

void insertarAlFinal(nodo_t** cabeza, int dato){
    nodo_t * nuevoNodo = crearNodo(dato);
    nodo_t * actual = (*cabeza);
    
    if (!actual){
        *cabeza = nuevoNodo;
        return;
    }
    while(actual->next != NULL){
        actual = actual->next;
    }
    
    actual->next = nuevoNodo;
    return;
}

void eliminarNodo(nodo_t** cabeza, int dato){
    nodo_t * actual = (*cabeza);
    nodo_t * anterior  = NULL;
    struct nodo * siguiente = NULL;
    int valorRetorno;
    int i = 0;

    if (actual){
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
            printf("Nodo eliminado!\n");
            return;
        }

        while(actual->next){
            if(actual->next->dato == dato){
                anterior = actual;
                actual = actual->next;
                siguiente = actual->next;
                anterior->next = siguiente;
                free(actual);
                actual = NULL;
                printf("Nodo eliminado!\n");
                return;
            }
            actual = actual->next;
        }
    }
    printf("El dato %d no forma parte de la lista.\n", dato);
};

void imprimirLista(nodo_t* cabeza){
    nodo_t * actual = cabeza;

    printf("[");
    while(actual){
        printf("%d",actual->dato);
        if (actual->next == NULL){
            break;
        }
        printf(", ");
        actual = actual->next;
    }
    printf("]\n");
};

void liberarLista(nodo_t** cabeza){
    nodo_t * actual = *cabeza;
    nodo_t * siguiente;

    while(actual){
        siguiente = actual->next;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}

nodo_t* buscarNodo(nodo_t* cabeza, int dato){
    nodo_t* actual = cabeza;
    while (actual) {
        if (actual->dato == dato) {
            return actual;
        }
        actual = actual->next;
    }
    return NULL;
}
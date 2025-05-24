**Consigna: Implementación de una Lista Enlazada Simple en C**

**Objetivo:**  
Implementar una estructura de datos de lista enlazada simple utilizando lenguaje C, con funcionalidades básicas de inserción, eliminación, búsqueda e impresión de elementos.

**Requisitos:**

1. **Definir una estructura `Nodo`** que contenga:  
   * Un campo `int dato` para almacenar el valor del nodo.  
   * Un puntero al siguiente nodo.  
2. **Funciones obligatorias:**  
   * `Nodo* crearNodo(int dato)` – Crea un nodo nuevo con un dato dado.  
   * `void insertarAlInicio(Nodo** cabeza, int dato)` – Inserta un nodo al comienzo de la lista.  
   * `void insertarAlFinal(Nodo** cabeza, int dato)` – Inserta un nodo al final de la lista.  
   * `void eliminarNodo(Nodo** cabeza, int dato)` – Elimina el primer nodo que contenga el dato especificado.  
   * `Nodo* buscarNodo(Nodo* cabeza, int dato)` – Devuelve un puntero al nodo que contiene el dato (o NULL si no se encuentra).  
   * `void imprimirLista(Nodo* cabeza)` – Imprime todos los elementos de la lista.  
   * `void liberarLista(Nodo** cabeza)` – Libera toda la memoria utilizada por la lista.  
3. **Programa principal:**  
   * Implementa un menú interactivo para probar las funciones anteriores (agregar, eliminar, buscar, imprimir, salir).  
   * Permitir al usuario ingresar valores por consola.

**Criterios de evaluación:**

* Correcta implementación de las funciones.  
* Uso adecuado de punteros.  
* Manejo de memoria dinámica (`malloc`, `free`).  
* Código bien comentado y organizado.


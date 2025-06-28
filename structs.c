#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct materia
{
    char *nombre;
    struct inscripcion *inscripcionesHead;
    struct materia *next;
    struct materia *prev;
} Materia;

typedef struct estudiante
{
    int legajo;
    char *nombre;
    char *apellido;
    int edad;
    struct inscripcion *inscripcionesHead;
    struct estudiante *next;
    struct estudiante *prev;
} Estudiante;

typedef struct inscripcion
{
    struct materia *materia;
    struct estudiante *estudiante;
    int nota;
    struct inscripcion *nextMateria;
    struct inscripcion *prevMateria;
    struct inscripcion *nextEstudiante;
    struct inscripcion *prevEstudiante;
} Inscripcion;

Estudiante *legajo1 = NULL;
Materia *materia1 = NULL;

int cantidadEstudiantes = 0;
int cantidadMaterias = 0;
int cantidadMateriasListadas = 0;

void limpiarTerminal();
float promedioEstudiante(int legajo);
void mostrarpromedios();

//Estudiantes
void altaEstudiante(char *nombre, char *apellido, int edad);
Estudiante *listarEstudiantes();
void modificarEstudiante(int legajo, char *nombre, char *apellido, int edad);
void listarPorNombreApellido(char *nombreApellido);
void listarPorEdad(int edadMin, int edadMax);
void eliminarEstudiante(int legajo);
Estudiante *buscarPorLegajo(int legajo);

//Materias
void altaMateria(char *nombre);
void listarMaterias();
void modificarMateria(char *nombre, char *nuevoNombre);
void eliminarMateria(char *nombreMateria);
Materia *buscarMateria(char *nombreMateria);

//Inscripciones
void inscribirMateria(int legajo, char *nombreMateria);
Inscripcion *buscarInscripcion(int legajo, char *nombreMateria);
Inscripcion *listarMateriasPorEstudiante(int legajo);
void listarEstudiantesPorMateria(char *nombreMateria);
void rendirMateria(int legajo, char *nombreMateria, int nota);
void darDeBajaMateria(int legajo, char *nombreMateria, Inscripcion *inscripcionInput);
/*
int main()
{
    altaEstudiante("Juan", "Perez", 20);
    altaEstudiante("Maria", "Gomez", 22);
    altaEstudiante("Pedro", "Lopez", 21);
    altaEstudiante("Ana", "Martinez", 19);

    altaMateria("Analisis Matematico I");
    altaMateria("AyP I");
    altaMateria("AyP II");
    altaMateria("Programación bajo nivel");
    altaMateria("Diseño Lógico");

    inscribirMateria(1, "Analisis Matematico I");
    inscribirMateria(1, "AyP I");
    inscribirMateria(2, "AyP II");
    inscribirMateria(3, "Programación bajo nivel");
    inscribirMateria(4, "Diseño Lógico");
    inscribirMateria(2, "Analisis Matematico I");
    inscribirMateria(3, "AyP I");
    inscribirMateria(4, "AyP II");
    inscribirMateria(1, "Diseño Lógico");
    inscribirMateria(2, "Programación bajo nivel");

    rendirMateria(1, "AyP I", 8); 
    rendirMateria(2, "AyP II", 7);
    rendirMateria(2, "Analisis Matematico I", 4);
    rendirMateria(2, "Programación bajo nivel", 9);
    rendirMateria(3, "AyP I", 6);
    rendirMateria(3, "Programación bajo nivel", 7);
    printf("Promedio del estudiante 2: %.2f\n", promedioEstudiante(2));

    listarEstudiantes();
    listarEstudiantesPorMateria("Diseño Lógico");
    listarMateriasPorEstudiante(legajo1->legajo);

    eliminarEstudiante(1);

    listarEstudiantes();
    listarEstudiantesPorMateria("Diseño Lógico");
    listarMateriasPorEstudiante(legajo1->legajo);
    mostrarpromedios();

    // Espera un input para que el usuario pueda ver los resultados antes de cerrar la consola
    printf("Presione Enter para continuar...\n");
    getchar();
    return 0;
}
    */

void altaEstudiante(char *nombre, char *apellido, int edad)
{
    Estudiante *nuevo;
    nuevo = (Estudiante *)malloc(sizeof(Estudiante));

    nuevo->legajo = 1;
    nuevo->nombre = nombre;
    nuevo->apellido = apellido;
    nuevo->edad = edad;
    nuevo->inscripcionesHead = NULL;
    nuevo->next = NULL;
    nuevo->prev = NULL;

    if (!legajo1)
    {
        nuevo->legajo = 1;
        legajo1 = nuevo;
    }
    else
    {
        Estudiante *actual = legajo1;
        while (actual->next)
        {
            actual = actual->next;
        }
        actual->next = nuevo;
        nuevo->prev = actual;
        nuevo->legajo = actual->legajo + 1;
    }
    cantidadEstudiantes++;
}

Estudiante* listarEstudiantes()
{
    int i = 0;
    Estudiante* arrayRet = malloc(cantidadEstudiantes * sizeof(Estudiante));

    Estudiante *actual = legajo1;
    while (actual)
    {
        printf("Legajo: %d, Nombre: %s %s, Edad: %d\n", actual->legajo, actual->nombre, actual->apellido, actual->edad);
        arrayRet[i] = *actual;
        actual = actual->next;
        i++;
    }

    return arrayRet;
}

int cantidadDeEstudiantes()
{
    return cantidadEstudiantes;
}

void modificarEstudiante(int legajo, char *nombre, char *apellido, int edad)
{
    Estudiante *estudiante = buscarPorLegajo(legajo);
    if (estudiante)
    {
        estudiante->nombre = nombre;
        estudiante->apellido = apellido;
        estudiante->edad = edad;
    }
}

void listarPorNombreApellido(char *nombreApellido)
{
    Estudiante *actual = legajo1;
    int encontrado = 0;
    while (actual)
    {
        if (strcmp(actual->nombre, nombreApellido) == 0 || strcmp(actual->apellido, nombreApellido) == 0)
        {
            encontrado = 1;
            printf("Estudiante encontrado: Legajo: %d, Nombre: %s %s, Edad: %d\n", actual->legajo, actual->nombre, actual->apellido, actual->edad);
        }
        actual = actual->next;
    }

    if (encontrado == 0)
    {
        printf("No se encontraron estudiantes para la busqueda %s\n", nombreApellido);
    }
    return;
}

void listarPorEdad(int edadMin, int edadMax)
{
    if (edadMin > edadMax)
    {
        printf("El rango de edad es invalido.\n");
        return;
    }

    Estudiante *actual = legajo1;
    int encontrado = 0;
    while (actual)
    {
        if (actual->edad >= edadMin && actual->edad <= edadMax)
        {
            encontrado = 1;
            printf("Estudiante encontrado: Legajo: %d, Nombre: %s %s, Edad: %d\n", actual->legajo, actual->nombre, actual->apellido, actual->edad);
        }
        actual = actual->next;
    }

    if (encontrado == 0)
    {
        printf("No se encontraron estudiantes dentro del rango de edad %d - %d\n", edadMin, edadMax);
    }
}

void eliminarEstudiante(int legajo)
{
    Estudiante *estudianteAEliminar = buscarPorLegajo(legajo);

    if (estudianteAEliminar == NULL)
    {
        return;
    }

    Inscripcion *inscripcionActual = estudianteAEliminar->inscripcionesHead;
    // Se recorren todas las inscripciones del estudiante para eliminarlas
    while (inscripcionActual != NULL)
    {
        Inscripcion *siguienteInscripcion = inscripcionActual->nextMateria;

        darDeBajaMateria(legajo,inscripcionActual->materia->nombre,inscripcionActual);

        inscripcionActual = siguienteInscripcion;
    }
    // enlaces y desenlaces de la lista general de estudiantes para eliminarlo
    if (estudianteAEliminar->prev != NULL)
    {
        estudianteAEliminar->prev->next = estudianteAEliminar->next;
    }
    else
    {
        // actualización del head para la primera materia a eliminar de la lista general
        legajo1 = estudianteAEliminar->next;
    }
    if (estudianteAEliminar->next != NULL)
    {
        estudianteAEliminar->next->prev = estudianteAEliminar->prev;
    }

    free(estudianteAEliminar);
    cantidadEstudiantes--;
    printf("Se eliminó el estudiante legajo %d.\n", legajo);
}
// cambiar por busqueda binaria o alguna otra mas performante (los legajos estan ordenados)
Estudiante *buscarPorLegajo(int legajo)
{
    Estudiante *actual = legajo1;
    while (actual)
    {
        if (actual->legajo == legajo)
        {
            return actual;
        }
        if (actual->legajo > legajo)
        {
            break;
        }
        actual = actual->next;
    }
    printf("No se encontro el estudiante con legajo %d\n", legajo);
    return NULL;
};


void altaMateria(char *nombre)
{
    Materia *nuevaMateria;
    nuevaMateria = (Materia *)malloc(sizeof(Materia));

    nuevaMateria->nombre = nombre;
    nuevaMateria->inscripcionesHead = NULL;
    nuevaMateria->next = NULL;
    nuevaMateria->prev = NULL;

    if (!materia1)
    {
        materia1 = nuevaMateria;
    }
    else
    {
        Materia *actual = materia1;
        while (actual->next)
        {
            actual = actual->next;
        }
        actual->next = nuevaMateria;
        nuevaMateria->prev = actual;
    }
    cantidadMaterias++;
}

void listarMaterias()
{
    Materia *actual = materia1;
    while (actual)
    {
        printf("Materia: %s\n", actual->nombre);
        actual = actual->next;
    }
}

void modificarMateria(char *nombre, char *nuevoNombre)
{
    Materia *materia = buscarMateria(nombre);
    if (materia)
    {
        materia->nombre = nuevoNombre;
    }
}

void eliminarMateria(char *nombreMateria)
{
    Materia *materiaAEliminar = buscarMateria(nombreMateria);

    if (materiaAEliminar == NULL)
    {
        return;
    }

    Inscripcion *inscripcionActual = materiaAEliminar->inscripcionesHead;
    // Se recorren todas las inscripciones para eliminarlas
    while (inscripcionActual != NULL)
    {
        Inscripcion *siguienteInscripcion = inscripcionActual->nextEstudiante;

        darDeBajaMateria(-1,NULL,inscripcionActual);

        inscripcionActual = siguienteInscripcion;
    }
    // enlaces y desenlaces de la lista general de materias para eliminarla
    if (materiaAEliminar->prev != NULL)
    {
        materiaAEliminar->prev->next = materiaAEliminar->next;
    }
    else
    {
        // actualización del head para la primera materia a eliminar de la lista general
        materia1 = materiaAEliminar->next;
    }
    if (materiaAEliminar->next != NULL)
    {
        materiaAEliminar->next->prev = materiaAEliminar->prev;
    }

    free(materiaAEliminar);
    cantidadMaterias--;
    printf("Se eliminó la materia '%s'.\n", nombreMateria);
}

Materia *buscarMateria(char *nombreMateria)
{
    Materia *actual = materia1;
    while (actual)
    {
        if (strcmp(actual->nombre, nombreMateria) == 0)
        {
            return actual;
        }
        actual = actual->next;
    }
    printf("No se encontro la materia %s\n", nombreMateria);
    return NULL;
};


Inscripcion *buscarInscripcion(int legajo, char *nombreMateria)
{
    Estudiante *estudiante = buscarPorLegajo(legajo);
    Materia *materia = buscarMateria(nombreMateria);
    if (estudiante && materia)
    {
        Inscripcion *inscripcion = estudiante->inscripcionesHead;
        while (inscripcion)
        {
            if (inscripcion->materia == materia)
            {
                return inscripcion;
            }
            inscripcion = inscripcion->nextMateria;
        }
    }
    // Si no se encontró la inscripción
    printf("El estudiante con legajo %d no está inscripto en la materia %s.\n", legajo, nombreMateria);
    return NULL;
}

void inscribirMateria(int legajo, char *nombreMateria)
{
    Estudiante *estudiante = buscarPorLegajo(legajo);
    Materia *materia = buscarMateria(nombreMateria);

    if (estudiante && materia)
    {
        Inscripcion *nuevaInscripcion = (Inscripcion *)malloc(sizeof(Inscripcion));
        nuevaInscripcion->estudiante = estudiante;
        nuevaInscripcion->materia = materia;
        nuevaInscripcion->nota = 0;
        nuevaInscripcion->nextMateria = NULL;
        nuevaInscripcion->prevMateria = NULL;
        nuevaInscripcion->nextEstudiante = NULL;
        nuevaInscripcion->prevEstudiante = NULL;

        // Insertar en la lista de inscripciones del estudiante
        if (!estudiante->inscripcionesHead)
        {
            estudiante->inscripcionesHead = nuevaInscripcion;
        }
        else
        {
            Inscripcion *actual = estudiante->inscripcionesHead;
            while (actual->nextMateria)
            {
                actual = actual->nextMateria;
            }
            actual->nextMateria = nuevaInscripcion;
            nuevaInscripcion->prevMateria = actual;
        }

        // Insertar en la lista de inscripciones de la materia
        if (!materia->inscripcionesHead)
        {
            materia->inscripcionesHead = nuevaInscripcion;
        }
        else
        {
            Inscripcion *actual = materia->inscripcionesHead;
            while (actual->nextEstudiante)
            {
                actual = actual->nextEstudiante;
            }
            actual->nextEstudiante = nuevaInscripcion;
            nuevaInscripcion->prevEstudiante = actual;
        }
    }
}

int cantidadDeMateriasListadas()
{
    return cantidadMateriasListadas;
}

Inscripcion* listarMateriasPorEstudiante(int legajo)
{
    Inscripcion* arrayRet = malloc(cantidadEstudiantes * sizeof(Inscripcion));
    cantidadMateriasListadas = 0;

    Estudiante *estudiante = buscarPorLegajo(legajo);
    if (estudiante)
    {
        int i = 0;

        Inscripcion *actual = estudiante->inscripcionesHead;
        printf("Materias inscriptas por el estudiante %s %s (Legajo: %d):\n", estudiante->nombre, estudiante->apellido, estudiante->legajo);
        while (actual)
        {
            if (actual->nota == 0)
            {
                printf("- %s - calificación: N/A\n", actual->materia->nombre);
            }
            else
            {
                printf("- %s - calificación: %i\n", actual->materia->nombre, actual->nota);
            }

            arrayRet[i] = *actual;
            i++;
            actual = actual->nextMateria;
            cantidadMateriasListadas++;
        }
        return arrayRet;
    }
}

void listarEstudiantesPorMateria(char *nombreMateria)
{
    Materia *materia = buscarMateria(nombreMateria);
    if (materia)
    {
        Inscripcion *actual = materia->inscripcionesHead;
        printf("Estudiantes inscriptos en la materia %s:\n", materia->nombre);
        while (actual)
        {
            printf("- %s %s (Legajo: %d) - calificación: %i\n", actual->estudiante->nombre, actual->estudiante->apellido, actual->estudiante->legajo, actual->nota);
            actual = actual->nextEstudiante;
        }
    }
}

void rendirMateria(int legajo, char *nombreMateria, int nota)
{
    Inscripcion *inscripcion = buscarInscripcion(legajo, nombreMateria);
    if (!inscripcion)
        return;

    inscripcion->nota = nota;
    printf("El estudiante %s, tiene nota %d en la materia %s.\n",
           inscripcion->estudiante->nombre, nota, nombreMateria);
}

void darDeBajaMateria(int legajo, char *nombreMateria, Inscripcion *inscripcionInput)
{
    Inscripcion *inscripcion = malloc(sizeof(Inscripcion));

    if(inscripcionInput)
        inscripcion = inscripcionInput;
    else  
        inscripcion = buscarInscripcion(legajo, nombreMateria);

    if (!inscripcion)
        return;

    // Elimina de la lista de inscripciones del estudiante
    if (inscripcion->prevMateria)
        inscripcion->prevMateria->nextMateria = inscripcion->nextMateria;
    else
        inscripcion->estudiante->inscripcionesHead = inscripcion->nextMateria;
    if (inscripcion->nextMateria)
        inscripcion->nextMateria->prevMateria = inscripcion->prevMateria;

    // Elimina de la lista de inscripciones de la materia
    if (inscripcion->prevEstudiante)
        inscripcion->prevEstudiante->nextEstudiante = inscripcion->nextEstudiante;
    else
        inscripcion->materia->inscripcionesHead = inscripcion->nextEstudiante;
    if (inscripcion->nextEstudiante)
        inscripcion->nextEstudiante->prevEstudiante = inscripcion->prevEstudiante;

    printf("Se eliminó la inscripción de %s para el estudiante con legajo %d.\n", nombreMateria, legajo);
    free(inscripcion);
}

void limpiarTerminal(){
    printf("\e[1;1H\e[2J");
};
float promedioEstudiante(int legajo)
{   Estudiante *estudiante = buscarPorLegajo(legajo);
    if(estudiante == NULL)
    {
        printf("no se encontro el estudiante con legajo %d\n", legajo);
        return 0.0; 
    }
    Inscripcion *inscripcion = estudiante->inscripcionesHead;
    if(inscripcion == NULL)
    {
        printf("El estudiante con legajo %d no tiene inscripciones.\n", legajo);
        return 0.0;
    }
    float sumarNotas =0.0;
    int cantidadInscripciones = 0;
    while(inscripcion)
    {
        if(inscripcion->nota>0.0){
            sumarNotas+= inscripcion->nota;
            cantidadInscripciones++;
        }
        inscripcion= inscripcion->nextMateria;
    }
        if (cantidadInscripciones == 0) {
        printf("El estudiante con legajo %d no tiene notas cargadas.\n", legajo);
        return -1.0;
    }
    return sumarNotas/(float)cantidadInscripciones;

}
void mostrarpromedios()
{
    Estudiante *actual = legajo1;

     if (!actual) {
        printf("No hay estudiantes cargados.\n");
        return;
    }
    while (actual)
    {
        float promedio = promedioEstudiante(actual->legajo);
        printf("Legajo: %d, Nombre: %s %s, Promedio: %.2f\n", actual->legajo, actual->nombre, actual->apellido, promedio);
        actual = actual->next;
    }
}


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

void altaEstudiante(char *nombre, char *apellido, int edad);
void altaMateria(char *nombre);
void eliminarMateria(char *nombreMateria);
void inscribirMateria(int legajo, char *nombreMateria);
Estudiante *buscarPorLegajo(int legajo);
Materia *buscarMateria(char *nombreMateria);
Inscripcion *buscarInscripcion(int legajo, char *nombreMateria);
void listarMateriasPorEstudiante(int legajo);
void listarEstudiantesPorMateria(char *nombreMateria);
void rendirMateria(int legajo, char *nombreMateria, int nota);
void darDeBajaMateria(int legajo, char *nombreMateria);

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
    rendirMateria(2, "AyP I", 7);

    darDeBajaMateria(1, "Analisis Matematico I");
    darDeBajaMateria(2, "AyP I");

    while (legajo1)
    {
        listarMateriasPorEstudiante(legajo1->legajo);
        legajo1 = legajo1->next;
    }

    // Espera un input para que el usuario pueda ver los resultados antes de cerrar la consola
    printf("Presione Enter para continuar...\n");
    getchar();
    return 0;
}

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

void listarMateriasPorEstudiante(int legajo)
{
    Estudiante *estudiante = buscarPorLegajo(legajo);
    if (estudiante)
    {
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
            actual = actual->nextMateria;
        }
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
        Estudiante *estudianteInscrito = inscripcionActual->estudiante;

        // Reemplazo: usar darDeBajaMateria en vez de los ifs manuales
        darDeBajaMateria(estudianteInscrito->legajo, nombreMateria);

        // Ya no se hace free aquí, lo hace darDeBajaMateria
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
    printf("Se eliminó la materia '%s'.\n", nombreMateria);
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

void darDeBajaMateria(int legajo, char *nombreMateria)
{
    Inscripcion *inscripcion = buscarInscripcion(legajo, nombreMateria);
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
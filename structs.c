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

void limpiarTerminal();

// Estudiantes
void altaEstudiante(char *nombre, char *apellido, int edad);
void listarEstudiantes();
void modificarEstudiante(int legajo, char *nombre, char *apellido, int edad);
void listarPorNombreApellido(char *nombreApellido);
void listarPorEdad(int edadMin, int edadMax);
Estudiante *buscarPorLegajo(int legajo);

// Materias
void altaMateria(char *nombre);
void listarMaterias();
void modificarMateria(char *nombre, char *nuevoNombre);
Materia *buscarMateria(char *nombreMateria);

// Inscripciones
void inscribirMateria(int legajo, char *nombreMateria);
void listarMateriasPorEstudiante(int legajo);
void listarEstudiantesPorMateria(char *nombreMateria);

int main()
{
    limpiarTerminal();

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

    listarEstudiantes();
    listarMaterias();

    listarPorNombreApellido("Juan");
    listarPorNombreApellido("-");
    listarPorEdad(20, 22);
    listarPorEdad(17, 18);
    listarPorEdad(17, 10);

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

void listarEstudiantes()
{
    Estudiante *actual = legajo1;
    while (actual)
    {
        printf("Legajo: %d, Nombre: %s %s, Edad: %d\n", actual->legajo, actual->nombre, actual->apellido, actual->edad);
        actual = actual->next;
    }
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
        printf("No se encontro el estudiante para la busqueda %s\n", nombreApellido);
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
        printf("No se encontraron estudiantes dentro del rango de edad %d - %d \n", edadMin, edadMax);
    }
}

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

void limpiarTerminal()
{
    printf("\e[1;1H\e[2J");
};

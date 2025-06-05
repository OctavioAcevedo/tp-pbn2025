#include <stdio.h>
#include <stdlib.h>

typedef struct materia{
    char nombre[30];
    Materia * correlativasHead;
    Materia * next;
    Materia * prev;
}Materia;

typedef struct materiaInscripta{
    Materia materia;
    int nota;
    MateriaInscripta * next;
    MateriaInscripta * prev;
}MateriaInscripta;

typedef struct estudiante {
    int legajo;
    char nombre[30];
    char apellido[30];
    int edad;
    MateriaInscripta * materiasHead;
    Estudiante * next;
    Estudiante * prev;
}Estudiante;
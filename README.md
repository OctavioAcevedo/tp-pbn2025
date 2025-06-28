# TP Final Programación Bajo Nivel - Gestor Académico

**UNTREF - 2025**
**Integrantes del grupo:**
- **Octavio Acevedo - Legajo 75261**
- **Mathias Aleandri - Legajo 66043**
- **Brenda Rocha - Legajo 64592**
- **Christian Maldonado - Legajo -**

# Funcionalidades Desarrolladas (`structs.c`)

Este archivo contiene la lógica y las estructuras de datos principales del gestor académico.

## Caracteristicas generales
   - `Estudiante *` y `Materia *` son nodos de sus respectivas listas doblemente enlazadas utilizadas para hacer la lógica de las funciones.

   - `Inscripcion *` es el nodo de dos listas a la vez, una que relaciona las inscripciones de un estudiante (con los enlaces `nextMateria` y `prevMateria`) y otra que relaciona las inscripciones de una materia (con los enlaces `nextEstudiante` y `prevMateria`). De esta forma se pueden segmentar los listados para ambos casos añadiendo un poco de complejidad extra al código.

   - Las funciones de `structs.c` funcionan por si solas y pueden ser usadas directamente en un programa ejecutado por terminal, cuentan con `printf()` informativos de todas las operaciones


## Estructuras de datos

- **Estudiante**
  - Representa a un estudiante.
  - Campos: legajo, nombre, apellido, edad, puntero a la lista de sus inscripciones, punteros `next`/`prev` para los enlaces de la lista general.
- **Materia**
  - Representa una materia.
  - Campos: nombre, puntero a la lista de sus inscripciones, punteros `next`/`prev` para los enlaces de la lista general.
- **Inscripcion**
  - Representa la inscripción de un estudiante a una materia y su nota.
  - Campos: punteros a la materia y al estudiante, nota.
  - punteros `nextMateria`/`prevMateria` y `nextEstudiante`/`prevEstudiante` para mantener la inscripción las dos listas implementadas.

## Funcionalidades principales

- **Altas, bajas y modificaciones:**
  - Alta, modificación y eliminación de estudiantes.
  - Alta, modificación y eliminación de materias.
  - Inscribir estudiantes en materias.
  - Dar de baja inscripciones.
  - Rendir/cargar nota de una materia para un estudiante.

- **Listados y consultas:**
  - Listar todos los estudiantes.
  - Listar todas las materias.
  - Listar materias por estudiante.
  - Listar estudiantes por materia.
  - Listar estudiantes por nombre/apellido.
  - Listar estudiantes por rango de edad.


# Interfaz de Menú (`menu.c`)

Este archivo implementa la interfaz de usuario en consola para un gestor académico de estudiantes y materias, utilizando la biblioteca ncurses (PDCurses en Windows).

## Funcionalidad principal

- **Menú principal:** Permite elegir entre modo Estudiante, Administrador o salir del programa.
- **Gestión de estudiantes:**
  - Listar estudiantes inscriptos.
  - Dar de alta nuevos estudiantes.
  - Ver detalles de un estudiante, modificar sus datos o eliminarlo.
  - Ver y rendir materias asociadas a un estudiante.
- **Gestión de materias:**
  - Listar materias disponibles.
  - Dar de alta nuevas materias.
  - Ver detalles de una materia, modificar su nombre o eliminarla.
  - Ver estudiantes inscriptos en una materia.
- **Navegación:** El usuario navega por los menús usando las flechas del teclado y selecciona opciones con Enter.
- **Interfaz interactiva:** Los menús y formularios se muestran en pantalla y se actualizan dinámicamente según la interacción del usuario.

## Notas

- El archivo depende de las funciones de manejo de datos definidas en `structs.c` para la lógica de estudiantes, materias e inscripciones.

- El código está pensado para ser ejecutado en consola Windows y requiere la biblioteca ncurses/PDCurses.

- Known issues (particularidades / deficiencias del codigo)

   - La interfaz no funciona con caracteres especiales (ñ o tildes)

    - En la modificacion y alta de estudiantes o materias los inputs no validan el tipo ni tamaño del dato (por ejemplo se puede)

    - En la modificacion de estudiante o materia, al volver al detalle de la entidad no se ven aplicados los cambios ya que los mostrados son a partir de una variable auxiliar, los cambios se ven cuando se vuelve al listado general

    - El nombre ingresado en la modificacion de estudiantes o materias no pueden tener un espacio, ya que significa el final del string imitando el dato ingresado a la primer palabra

    - En la interfaz grafica no se incluye el uso de las funciones `listarPorNombreApellido()` `listarPorEdad()` ni `inscribirMateria()`, aunque estan implementadas y funcionando.

- La interfaz gráfica se puede debuguear en vscode añadiendo la siguiente configuracion al launch.json en .vscode:

```json{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug programa",
            "type": "cppdbg",
            "request": "launch",
            "program": "C:/Users/oacevedo/OneDrive - VeriTran/Escritorio/c/facu/AYP3/git/menu.exe",   // ⚠️ Modificar: Especificar ruta local en donde se encuentra el archivo menu.exe
            "args": [],
            "stopAtEntry": false,
            "cwd": "C:/Users/oacevedo/OneDrive - VeriTran/Escritorio/c/facu/AYP3/git",   // ⚠️ Modificar: Especificar ruta local en donde se encuentra el directorio del proyecto
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/msys64/ucrt64/bin/gdb.exe",  // ⚠️ Ruta al gdb, modificar si no se instalo con la ruta default
            "setupCommands": [
                {
                    "description": "Habilitar impresión de pretty-printers para gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}



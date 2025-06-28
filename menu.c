#include "structs.c"
#include <curses.h>

// compilar: gcc menu.c -I .\PDCurses\ -L .\PDCurses\wincon\ -l:pdcurses.a -g -o menu.exe


void menu();
void vistaListadoDeEstudiantes();
void vistaNuevoEstudiante();
void vistaDetalleEstudiante(Estudiante *estudiante);
void vistaListadoMateriasPorEstudiante(Estudiante *estudiante);
void vistaModificarEstudiante(Estudiante *estudiante);
void vistaListadoDeMaterias();
void vistaNuevaMateria();
void vistaDetalleMateria(Materia *materia);
void vistaModificarMateria(Materia *materia);
void vistaListadoEstudiantesPorMateria(Materia *materia);

int menu2Opciones(int opcionPosY, char *titulo, char *opcion1, char *opcion2);
int menu3Opciones(int opcionPosY, char *titulo, char *opcion1, char *opcion2, char *opcion3);

void cargarDatos()
{
    altaEstudiante("Juan", "Perez", 20);
    altaEstudiante("Maria", "Gomez", 22);
    altaEstudiante("Pedro", "Lopez", 21);
    altaEstudiante("Ana", "Martinez", 19);

    altaMateria("Analisis Matematico I");
    altaMateria("AyP I");
    altaMateria("AyP II");
    altaMateria("Programacion bajo nivel");
    altaMateria("Estructura de Datos");

    inscribirMateria(1, "Analisis Matematico I");
    inscribirMateria(1, "AyP I");
    inscribirMateria(2, "AyP II");
    inscribirMateria(3, "Programacion bajo nivel");
    inscribirMateria(4, "Estructura de Datos");
    inscribirMateria(2, "Analisis Matematico I");
    inscribirMateria(3, "AyP I");
    inscribirMateria(4, "AyP II");
    inscribirMateria(1, "Estructura de Datos");
    inscribirMateria(2, "Programacion bajo nivel");
}

int main()
{
    cargarDatos(); // Cargar datos de ejemplo

    initscr();            // Iniciar ncurses
    cbreak();             // Desactivar buffer de línea
    noecho();             // No mostrar caracteres al escribir
    keypad(stdscr, TRUE); // Habilitar teclas especiales
    curs_set(0);          // Ocultar el cursor

    menu();
    return 0;
}

void menu()
{

    const char *opcionesMenuAdmin[] = {"Materias->", "Estudiantes ->", "[<- Salir"};
    const int cantOpciones = 3;

    int choice = 0;
    int ch;

    while (1)
    {
        clear();
        mvprintw(0, 0, "Bienvenido al GESTOR ACADEMICO - presiona Enter para seleccionar una opcion");

        int posY = 1;
        int posX = 2;

        for (int i = 0; i < cantOpciones; i++)
        {
            if (i == cantOpciones - 1)
            {
                posY += 2;
                posX = 1;
            }
            else
                posY++;

            if (i == choice)
            {
                attron(A_REVERSE); // Resaltar selección
                mvprintw(posY, posX, "%s", opcionesMenuAdmin[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(posY, posX, "%s", opcionesMenuAdmin[i]);
            }
        }

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = cantOpciones - 1;
            break;
        case KEY_DOWN:
            choice++;
            if (choice >= cantOpciones)
                choice = 0;
            break;
        case 10: // Enter
            if (choice == 0)
            { // "Materias"
                vistaListadoDeMaterias();
            }
            if (choice == 1)
            { // "Estudiantes"
                vistaListadoDeEstudiantes();
            }
            if (choice == cantOpciones - 1)
            { // "Salir"
                int opcionSalir = menu2Opciones(7, "Salir del programa?", "Si, salir", "No, volver al menu");
                if (opcionSalir == 0)
                {
                    endwin();
                    return;
                }
                else
                    break;
            }
        }
    }
}

// vistas estudiantes
void vistaListadoDeEstudiantes()
{

    int choice = 0;
    int ch;

    Estudiante *seleccion = malloc(sizeof(Estudiante));

    while (1)
    {
        clear();
        mvprintw(0, 0, "ESTUDIANTES INSCRIPTOS - Presione Enter para ver detalles");

        Estudiante *array = listarEstudiantes();
        int cantidadEstudiantes = cantidadDeEstudiantes();

        for (int i = 0; i < cantidadEstudiantes; i++)
        {
            Estudiante *opcion = &array[i];

            if (i == choice) // Resaltar opcion si es la seleccionada
            {
                attron(A_REVERSE);
                mvprintw(2 + i, 2, "Legajo %d - %s, %s - E: %d ->", opcion->legajo, opcion->apellido, opcion->nombre, opcion->edad);
                attroff(A_REVERSE);
                seleccion = opcion; // Actualizar seleccion
            }
            else
            {
                mvprintw(2 + i, 2, "Legajo %d - %s, %s - E: %d ->", opcion->legajo, opcion->apellido, opcion->nombre, opcion->edad);
            }
        }

        int i = cantidadEstudiantes;

        if (choice == cantidadEstudiantes)
        {
            attron(A_REVERSE);
            mvprintw(3 + i, 1, "%s", "Dar de alta nuevo estudiante->");
            attroff(A_REVERSE);
        }
        else
            mvprintw(3 + i, 1, "%s", "Dar de alta nuevo estudiante->");

        if (choice == cantidadEstudiantes + 1)
        {
            attron(A_REVERSE);
            mvprintw(4 + i, 1, "%s", "<- Atras");
            attroff(A_REVERSE);
        }
        else
            mvprintw(4 + i, 1, "%s", "<- Atras");

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = cantidadEstudiantes - 1;
            break;
        case KEY_DOWN:
            choice++;
            if (choice >= cantidadEstudiantes + 2)
                choice = 0;
            break;
        case 10: // Enter
            if (choice == cantidadEstudiantes)
            {
                vistaNuevoEstudiante(); // Dar de alta nuevo estudiante
                break;
            }

            if (choice == cantidadEstudiantes + 1)
                return;

            vistaDetalleEstudiante(seleccion); // Ver detalles del estudiante seleccionado
            break;
        }
    }

    endwin(); // Restaurar terminal
    return;
}

void vistaNuevoEstudiante()
{
    char nombre[50], apellido[50];
    char *nombreString = malloc(50 * sizeof(char));
    char *apellidoString = malloc(50 * sizeof(char));
    int edad;

    clear();
    echo();
    mvprintw(0, 0, "NUEVO ESTUDIANTE");
    mvprintw(2, 0, "Ingrese el nombre del estudiante (max. 50 caracteres): ");
    getstr(nombre);
    mvprintw(3, 0, "Ingrese el apellido del estudiante  (max. 50 caracteres): ");
    getstr(apellido);
    mvprintw(4, 0, "Ingrese la edad del estudiante: ");
    scanw("%d", &edad);
    noecho();

    strcpy(nombreString, nombre);
    strcpy(apellidoString, apellido);

    altaEstudiante(nombreString, apellidoString, edad);
    return;
}

void vistaDetalleEstudiante(Estudiante *estudiante)
{
    int opcion = 0;
    while (1)
    {
        clear();
        mvprintw(0, 0, "ESTUDIANTE Legajo %d", estudiante->legajo);
        mvprintw(1, 2, "Nombre Completo: %s, %s", estudiante->apellido, estudiante->nombre);
        mvprintw(2, 2, "Edad: %d", estudiante->edad);

        mvprintw(4, 1, "Acciones:");
        char *acciones[] = {"Ver y Rendir materias ->", "Modificar Estudiante ->", "Eliminar Estudiante ->", "<- Atras"};
        for (int i = 0; i < 4; i++)
        {
            int posY = 5 + i;
            int posX = 1;

            if (i == 3) // Posiciones para opcion "Atras"
            {
                posY++;
            }

            if (i == opcion)
            {
                attron(A_REVERSE);
                mvprintw(posY, posX, "%s", acciones[i]);
                attroff(A_REVERSE);
            }
            else
                mvprintw(posY, posX, "%s", acciones[i]);
        }

        int ch = getch();
        switch (ch)
        {
        case KEY_DOWN:
            opcion++;
            if (opcion > 3)
                opcion = 0;
            break;
        case KEY_UP:
            opcion--;
            if (opcion < 0)
                opcion = 0;
            break;
        case 10: // Enter
            if (opcion == 0)
            { // "Ver y Calificar materias"
                vistaListadoMateriasPorEstudiante(estudiante);
            }
            else if (opcion == 1)
            { // "Modificar Estudiante"
                vistaModificarEstudiante(estudiante);
            }
            else if (opcion == 2)
            { // "Eliminar Estudiante"
                int opcionEliminar = menu2Opciones(10, "Confirma la baja del estudiante?", "Si, eliminar", "No, cancelar");
                // Borra mensaje
                move(10, 0);
                clrtoeol();
                move(11, 0);
                clrtoeol();
                move(12, 0);
                clrtoeol();
                if (opcionEliminar == 0) // Si confirma la eliminacion
                {
                    eliminarEstudiante(estudiante->legajo);
                    mvprintw(11, 2, "Estudiante dado de baja. - Presione alguna tecla para continuar...");
                    getch(); // Esperar tecla para continuar
                    return;
                }
            }
            else if (opcion == 3)
            { // "<- Atras"
                return;
            }
            break;
        }
    }
}

void vistaListadoMateriasPorEstudiante(Estudiante *estudiante)
{

    int choice = 0;
    int ch;

    char *seleccion = malloc(50 * sizeof(char));
    int seleccionNota = 0; // Variable para almacenar la nota seleccionada

    while (1)
    {
        clear();
        mvprintw(0, 0, "MATERIAS INSCRIPTAS - Estudiante legajo %d - %s, %s", estudiante->legajo, estudiante->apellido, estudiante->nombre);

        Inscripcion *array = listarMateriasPorEstudiante(estudiante->legajo);
        int cantidadMaterias = cantidadDeMateriasListadas();

        for (int i = 0; i < cantidadMaterias; i++)
        {
            Inscripcion *opcion = &array[i];

            if (i == choice) // Resaltar opcion si es la seleccionada
            {
                attron(A_REVERSE);
                if (opcion->nota == 0)
                {
                    mvprintw(2 + i, 2, "Materia: %s ", opcion->materia->nombre);
                    mvprintw(2 + i, 40, "Nota: N/A ->");
                }
                else
                {
                    mvprintw(2 + i, 2, "Materia: %s ", opcion->materia->nombre);
                    mvprintw(2 + i, 40, "Nota: %d ->", opcion->nota);
                }
                attroff(A_REVERSE);
                seleccion = opcion->materia->nombre; // Actualizar seleccion
                seleccionNota = opcion->nota;        // Actualizar seleccion
            }
            else
            {
                if (opcion->nota == 0)
                {
                    mvprintw(2 + i, 2, "Materia: %s ", opcion->materia->nombre);
                    mvprintw(2 + i, 40, "Nota: N/A ->");
                }
                else
                {
                    mvprintw(2 + i, 2, "Materia: %s ", opcion->materia->nombre);
                    mvprintw(2 + i, 40, "Nota: %d ->", opcion->nota);
                }
            }
        }

        int i = cantidadMaterias;

        if (choice == cantidadMaterias)
        {
            attron(A_REVERSE);
            mvprintw(3 + i, 1, "%s", "<- Atras");
            attroff(A_REVERSE);
        }
        else
            mvprintw(3 + i, 1, "%s", "<- Atras");

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = cantidadMaterias - 1;
            break;
        case KEY_DOWN:
            choice++;
            if (choice >= cantidadMaterias + 1)
                choice = 0;
            break;
        case 10: // Enter
            if (choice == cantidadMaterias)
            {
                return; // Volver al menu anterior
            }
            int accion = menu3Opciones(cantidadMaterias + 5, "Acciones sobre materia seleccionada", "Rendir Materia", "Dar de baja inscripcion", "<- Atras");
            switch (accion)
            {
            case 0:
                if (seleccionNota == 0) // Rendir Materia
                {
                    int nuevaNota;
                    echo();
                    mvprintw(cantidadMaterias + 10, 2, "Ingrese la nota o -1 para cancelar: ");
                    scanw("%d", &nuevaNota);
                    noecho();
                    if (nuevaNota == -1)
                        break;

                    if (nuevaNota >= 0 && nuevaNota <= 10)
                    {
                        rendirMateria(estudiante->legajo, seleccion, nuevaNota);
                        mvprintw(cantidadMaterias + 11, 2, "Materia %s calificada con nota %d - Presione alguna tecla para continuar...", seleccion, nuevaNota);
                        getch(); // Esperar tecla para continuar
                    }
                    else
                    {
                        mvprintw(cantidadMaterias + 11, 2, "Nota invalida. Debe ser entre 0 y 10. - Presione alguna tecla para continuar...");
                        getch(); // Esperar tecla para continuar
                    }
                }
                else
                {
                    mvprintw(cantidadMaterias + 10, 2, "La materia ya fue rendida. - Presione alguna tecla para continuar...");
                    getch(); // Esperar tecla para continuar
                }
                break;
            case 1:
                int opcionEliminar = menu2Opciones(cantidadMaterias + 10, "Confirma la baja de la inscripcion?", "Si, eliminar", "No, cancelar");
                // Borra mensaje
                move(cantidadMaterias + 10, 0);
                clrtoeol();
                move(cantidadMaterias + 11, 0);
                clrtoeol();
                move(cantidadMaterias + 12, 0);
                clrtoeol();
                if (opcionEliminar == 0) // Si confirma la eliminacion
                {
                    darDeBajaMateria(estudiante->legajo, seleccion, NULL);
                    mvprintw(cantidadMaterias + 11, 2, "Inscripcion a la materia %s eliminada. - Presione alguna tecla para continuar...", seleccion);
                    getch(); // Esperar tecla para continuar
                }
                break;
            case 2:
                break;
            }
        }
    }
}

void vistaModificarEstudiante(Estudiante *estudiante)
{
    int ch = 0;
    int choice = 0;

    char *nombres[] = {"Nombre: ", "Apellido:"};
    int datoEdad = estudiante->edad;
    char *acciones[] = {"<-Confirmar y volver", "<- Atras"};

    char *nuevoNombre = malloc(50 * sizeof(char));
    strcpy(nuevoNombre, estudiante->nombre);
    char *nuevoApellido = malloc(50 * sizeof(char));
    strcpy(nuevoApellido, estudiante->apellido);
    int nuevaEdad = estudiante->edad;

    char *datos[] = {nuevoNombre, nuevoApellido};

    while (1)
    {
        clear();
        int initPosY = 1;
        int posY = initPosY;

        // Opciones nombre y apellido
        for (int i = 0; i < 2; i++)
        {
            mvprintw(posY, 1, "%s", nombres[i]);
            if (i == choice)
            {
                attron(A_REVERSE); // Resaltar opcion seleccionada
                mvprintw(posY, 12, "%s", datos[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(posY, 12, "%s", datos[i]);
            }
            posY++;
        }
        // Opcion edad
        mvprintw(posY, 1, "%s", "Edad: ");
        if (choice == 2)
        {
            attron(A_REVERSE); // Resaltar opcion 1
            mvprintw(posY, 12, "%d", datoEdad);
            attroff(A_REVERSE);
        }
        else
        {
            mvprintw(posY, 12, "%d", datoEdad);
        }
        posY++;
        // Opciones de confirmacion y atras
        for (int i = 0; i < 2; i++)
        {
            posY++;
            if (i == choice - 3) // Ajustar el índice para las opciones de confirmación y atrás
            {
                attron(A_REVERSE); // Resaltar opcion seleccionada
                mvprintw(posY, 1, "%s", acciones[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(posY, 1, "%s", acciones[i]);
            }
        }
        ch = getch();
        switch (ch)
        {
        case KEY_DOWN:
            choice++;
            if (choice > 4)
                choice = 0;
            break;
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = 4;
            break;
        case 10:
            if (choice < 2) // Modificar nombre o apellido
            {
                char input[50];
                echo();
                mvscanw(initPosY + choice, 12, "%49s", input);
                noecho();
                if (choice == 0)
                {
                    strcpy(nuevoNombre, input);
                }
                else if (choice == 1)
                {
                    strcpy(nuevoApellido, input);
                }
                strcpy(datos[choice], input); // Actualizar el dato en pantalla
            }
            else if (choice == 2) // Modificar edad
            {

                echo();
                mvscanw(initPosY + choice, 12, "%d", &nuevaEdad);
                noecho();
                datoEdad = nuevaEdad; // Actualizar el dato en pantalla
            }
            else if (choice == 3) // Confirmar y volver
            {
                modificarEstudiante(estudiante->legajo, nuevoNombre, nuevoApellido, nuevaEdad);
                return;
            }
            else if (choice == 4) // Atras
                return;
            break; // Retorna la opción seleccionada
        }
    }
}

// vistas materias
void vistaListadoDeMaterias()
{

    int choice = 0;
    int ch;

    Materia *seleccion = malloc(sizeof(Materia));

    while (1)
    {
        clear();
        mvprintw(0, 0, "MATERIAS DISPONIBLES - Presione Enter para ver aciones");

        Materia *array = listarMaterias();
        int cantidadMaterias = cantidadDeMaterias();

        for (int i = 0; i < cantidadMaterias; i++)
        {
            Materia *opcion = &array[i];

            if (i == choice) // Resaltar opcion si es la seleccionada
            {
                attron(A_REVERSE);
                mvprintw(2 + i, 2, "Nombre: %s ->", opcion->nombre);
                attroff(A_REVERSE);
                seleccion = opcion; // Actualizar seleccion
            }
            else
            {
                mvprintw(2 + i, 2, "Nombre: %s ->", opcion->nombre);
            }
        }

        int i = cantidadMaterias;

        if (choice == cantidadMaterias)
        {
            attron(A_REVERSE);
            mvprintw(3 + i, 1, "%s", "Dar de alta nueva materia->");
            attroff(A_REVERSE);
        }
        else
            mvprintw(3 + i, 1, "%s", "Dar de alta nueva materia->");

        if (choice == cantidadMaterias + 1)
        {
            attron(A_REVERSE);
            mvprintw(4 + i, 1, "%s", "<- Atras");
            attroff(A_REVERSE);
        }
        else
            mvprintw(4 + i, 1, "%s", "<- Atras");

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = cantidadMaterias - 1;
            break;
        case KEY_DOWN:
            choice++;
            if (choice >= cantidadMaterias + 2)
                choice = 0;
            break;
        case 10: // Enter
            if (choice == cantidadMaterias)
            {
                vistaNuevaMateria(); // Dar de alta nueva materia
                break;
            }

            if (choice == cantidadMaterias + 1)
                return;

            // Si no es una de las dos opciones, se muestra el detalle de la materia seleccionada
            vistaDetalleMateria(seleccion);

            break;
        }
    }

    endwin(); // Restaurar terminal
    return;
}

void vistaNuevaMateria()
{
    char nombre[50];
    char *nombreString = malloc(50 * sizeof(char));

    clear();
    echo();
    mvprintw(0, 0, "NUEVA MATERIA");
    mvprintw(2, 0, "Ingrese el nombre de la materia (max. 50 caracteres): ");
    getstr(nombre);
    noecho();

    strcpy(nombreString, nombre);

    altaMateria(nombreString);
    return;
}

void vistaDetalleMateria(Materia *materia)
{
    int opcion = 0;
    while (1)
    {
        clear();
        mvprintw(0, 0, "MATERIA %s", materia->nombre);

        mvprintw(2, 1, "Acciones:");
        char *acciones[] = {"Ver y estudiantes inscriptos ->", "Modificar materia ->", "Eliminar materia ->", "<- Atras"};
        for (int i = 0; i < 4; i++)
        {
            int posY = 2 + i;
            int posX = 1;

            if (i == 3) // Posiciones para opcion "Atras"
            {
                posY++;
            }

            if (i == opcion)
            {
                attron(A_REVERSE);
                mvprintw(posY, posX, "%s", acciones[i]);
                attroff(A_REVERSE);
            }
            else
                mvprintw(posY, posX, "%s", acciones[i]);
        }

        int ch = getch();
        switch (ch)
        {
        case KEY_DOWN:
            opcion++;
            if (opcion > 3)
                opcion = 0;
            break;
        case KEY_UP:
            opcion--;
            if (opcion < 0)
                opcion = 0;
            break;
        case 10: // Enter
            if (opcion == 0)
            { // "Ver y Calificar materias"
                vistaListadoEstudiantesPorMateria(materia);
            }
            else if (opcion == 1)
            { // "Modificar materia"
                vistaModificarMateria(materia);
            }
            else if (opcion == 2)
            { // "Eliminar materia"
                int opcionEliminar = menu2Opciones(10, "Confirma la baja de la materia?", "Si, eliminar", "No, cancelar");
                // Borra mensaje
                move(10, 0);
                clrtoeol();
                move(11, 0);
                clrtoeol();
                move(12, 0);
                clrtoeol();
                if (opcionEliminar == 0) // Si confirma la eliminacion
                {
                    eliminarMateria(materia->nombre);
                    mvprintw(11, 2, "Materia dada de baja. - Presione alguna tecla para continuar...");
                    getch(); // Esperar tecla para continuar
                    return;
                }
            }
            else if (opcion == 3)
            { // "<- Atras"
                return;
            }
            break;
        }
    }
}

void vistaListadoEstudiantesPorMateria(Materia *materia)
{

    int choice = 0;
    int ch;

    int seleccionNota = 0; // Variable para almacenar la nota seleccionada

    while (1)
    {
        clear();
        mvprintw(0, 0, "ESTUDIANTES INSCRIPTOS - %s", materia->nombre);

        Inscripcion *array = listarEstudiantesPorMateria(materia->nombre);
        int cantidadEstudiantes = cantidadDeEstudiantesListados();

        for (int i = 0; i < cantidadEstudiantes; i++)
        {
            Inscripcion *opcion = &array[i];

            if (i == choice) // Resaltar opcion si es la seleccionada
            {
                attron(A_REVERSE);
                if (opcion->nota == 0)
                    mvprintw(2 + i, 2, "Legajo %d - %s, %s - Nota: N/A", opcion->estudiante->legajo, opcion->estudiante->apellido, opcion->estudiante->nombre);
                else
                    mvprintw(2 + i, 2, "Legajo %d - %s, %s - Nota: %d", opcion->estudiante->legajo, opcion->estudiante->apellido, opcion->estudiante->nombre, opcion->nota);
                attroff(A_REVERSE);
            }
            else
            {
                if (opcion->nota == 0)
                    mvprintw(2 + i, 2, "Legajo %d - %s, %s - Nota: N/A", opcion->estudiante->legajo, opcion->estudiante->apellido, opcion->estudiante->nombre);
                else
                    mvprintw(2 + i, 2, "Legajo %d - %s, %s - Nota: %d", opcion->estudiante->legajo, opcion->estudiante->apellido, opcion->estudiante->nombre, opcion->nota);
            }
        }

        int i = cantidadEstudiantes;

        if (choice == cantidadEstudiantes)
        {
            attron(A_REVERSE);
            mvprintw(3 + i, 1, "%s", "<- Atras");
            attroff(A_REVERSE);
        }
        else
            mvprintw(3 + i, 1, "%s", "<- Atras");

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = cantidadEstudiantes - 1;
            break;
        case KEY_DOWN:
            choice++;
            if (choice >= cantidadEstudiantes + 1)
                choice = 0;
            break;
        case 10: // Enter
            if (choice == cantidadEstudiantes)
            {
                return; // Volver al menu anterior
            }
        }
    }
}

void vistaModificarMateria(Materia *materia)
{
    int ch = 0;
    int choice = 0;

    char *acciones[] = {"<-Confirmar y volver", "<- Atras"};

    char *nuevoNombre = malloc(50 * sizeof(char));
    strcpy(nuevoNombre, materia->nombre);

    while (1)
    {
        clear();
        int initPosY = 1;
        int posY = initPosY;

        // Opcion nombre
        mvprintw(posY, 1, "Nombre: ");
        if (choice == 0)
        {
            attron(A_REVERSE); // Resaltar opcion seleccionada
            mvprintw(posY, 12, "%s", nuevoNombre);
            attroff(A_REVERSE);
        }
        else
        {
            mvprintw(posY, 12, "%s", nuevoNombre);
        }
        posY++;

        // Opciones de confirmacion y atras
        for (int i = 0; i < 2; i++)
        {
            posY++;
            if (i == choice - 1) // Ajustar el índice para las opciones de confirmación y atrás
            {
                attron(A_REVERSE); // Resaltar opcion seleccionada
                mvprintw(posY, 1, "%s", acciones[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(posY, 1, "%s", acciones[i]);
            }
        }
        ch = getch();
        switch (ch)
        {
        case KEY_DOWN:
            choice++;
            if (choice > 2)
                choice = 0;
            break;
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = 2;
            break;
        case 10:
            if (choice == 0) // Modificar nombre
            {
                char input[50];
                echo();
                mvscanw(initPosY + choice, 12, "%49s", input);
                noecho();
                strcpy(nuevoNombre, input); // Actualizar el dato en pantalla
            }
            else if (choice == 1) // Confirmar y volver
            {
                modificarMateria(materia->nombre, nuevoNombre);
                return;
            }
            else if (choice == 2) // Atras
                return;
            break; // Retorna la opción seleccionada
        }
    }
}

// funciones auxiliares
int menu2Opciones(int opcionPosY, char *titulo, char *opcion1, char *opcion2)
{
    int ch = 0;
    mvprintw(opcionPosY, 0, "%s", titulo);
    int opcion = 0;
    while (1)
    {
        if (opcion == 0)
        {
            attron(A_REVERSE); // Resaltar opcion 1
            mvprintw(opcionPosY + 1, 2, "%s", opcion1);
            attroff(A_REVERSE);
            mvprintw(opcionPosY + 2, 2, "%s", opcion2);
        }
        else
        {
            mvprintw(opcionPosY + 1, 2, "%s", opcion1);
            attron(A_REVERSE); // Resaltar opcion 2
            mvprintw(opcionPosY + 2, 2, "%s", opcion2);
            attroff(A_REVERSE);
        }
        ch = getch();
        switch (ch)
        {
        case KEY_DOWN:
            opcion++;
            if (opcion > 1)
                opcion = 0;
            break;
        case KEY_UP:
            opcion--;
            if (opcion < 0)
                opcion = 1;
            break;
        case 10:           // Enter
            return opcion; // Retorna la opción seleccionada
        }
    }
}

int menu3Opciones(int opcionPosY, char *titulo, char *opcion1, char *opcion2, char *opcion3)
{
    int ch = 0;
    char *opciones[] = {opcion1, opcion2, opcion3};

    mvprintw(opcionPosY, 0, "%s", titulo);
    int opcion = 0;
    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == opcion)
            {
                attron(A_REVERSE); // Resaltar opcion seleccionada
                mvprintw(opcionPosY + 1 + i, 2, "%s", opciones[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(opcionPosY + 1 + i, 2, "%s", opciones[i]);
            }
        }

        ch = getch();
        switch (ch)
        {
        case KEY_DOWN:
            opcion++;
            if (opcion > 2)
                opcion = 0;
            break;
        case KEY_UP:
            opcion--;
            if (opcion < 0)
                opcion = 2;
            break;
        case 10:           // Enter
            return opcion; // Retorna la opción seleccionada
        }
    }
}
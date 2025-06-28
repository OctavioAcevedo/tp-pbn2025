#include "structs.c"
#include <curses.h>

/* compilar: gcc menu.c -I .\PDCurses\ -L .\PDCurses\wincon\ -l:pdcurses.a -g -o menu.exe
*/

/* vulnerabilidad: no se valida la entrada del usuario, se puede ingresar cualquier cosa sin respetar el tipo de dato esperado
*/

/* comentario: no funcan los caracteres especiales (ñ o tildes)
*/

/*comentario: en la modificacion de estudiante o materia, al volver al detalle de la entidad no se
ven aplicados los cambios ya que los mostrados son una variable auxiliar, los cambios se ven cuando se vuelve al listado
*/
const char *items[] = {"Nodo 1", "Nodo 2", "Nodo 3", "Salir"};
#define NUM_ITEMS (sizeof(items) / sizeof(items[0]))

void menuAdministrador();
void vistaListadoDeEstudiantes();
void vistaNuevoEstudiante();
void vistaDetalleEstudiante(Estudiante *estudiante);
void vistaListadoMateriasPorEstudiante(Estudiante *estudiante);
void vistaModificarEstudiante(Estudiante *estudiante);
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
    altaMateria("Diseño Logico");

    inscribirMateria(1, "Analisis Matematico I");
    inscribirMateria(1, "AyP I");
    inscribirMateria(2, "AyP II");
    inscribirMateria(3, "Programacion bajo nivel");
    inscribirMateria(4, "Diseño Logico");
    inscribirMateria(2, "Analisis Matematico I");
    inscribirMateria(3, "AyP I");
    inscribirMateria(4, "AyP II");
    inscribirMateria(1, "Diseño Logico");
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

    const char *opcionesMenu1[] = {"Estudiante", "Administrador", "Salir"};
    int cantMenuPrincipal = 3;

    int choice = 0;
    int ch;

    while (1)
    {
        clear();
        mvprintw(0, 0, "Bienvenido al gestor estudiantes!");

        int opcionPosY = 2;

        for (int i = 0; i < cantMenuPrincipal; i++)
        {
            if (i == cantMenuPrincipal - 1)
                opcionPosY += 2;
            else
                opcionPosY++;

            if (i == choice)
            {
                attron(A_REVERSE); // Resaltar selección
                mvprintw(opcionPosY, 2, "%s", opcionesMenu1[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(opcionPosY, 2, "%s", opcionesMenu1[i]);
            }
        }

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = cantMenuPrincipal - 1;
            break;
        case KEY_DOWN:
            choice++;
            if (choice >= cantMenuPrincipal)
                choice = 0;
            break;
        case 10: // Enter
            if (choice == 1)
            {                        // "Administrador"
                menuAdministrador(); // Llamar al menu de administrador
            }
            else if (choice == cantMenuPrincipal - 1)
            { // "Salir"
                int opcionSalir = menu2Opciones(10, "Salir del programa?", "Si, salir", "No, volver al menu");
                if (opcionSalir == 0)
                {
                    endwin();
                    return 0;
                }
                else
                    break;
            }
            else
            {
                // Aquí puedes ejecutar una acción sobre el nodo seleccionado
                mvprintw(10, 2, "Seleccionaste %s", opcionesMenu1[choice]);
                refresh();
                getch(); // Esperar tecla para continuar
            }
            break;
        }
    }

    endwin(); // Restaurar terminal
    return 0;
}

void menuAdministrador()
{

    const char *opcionesMenuAdmin[] = {"Materias->", "Estudiantes ->", "<- Atras"};
    const int cantOpciones = 3;

    int choice = 0;
    int ch;

    while (1)
    {
        clear();
        mvprintw(0, 0, "MENU ADMINISTRADOR - Seleccione una opción:");

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
            if (choice == cantOpciones - 1)
            { // "Atras"
                return;
            }
            if (choice == 1)
            { // "Estudiantes"
                vistaListadoDeEstudiantes();
            }
            break;
        }
    }
}

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
                 int opcionEliminar = menu2Opciones(10, "Confirma la baja de la inscripcion?", "Si, eliminar", "No, cancelar");
                //Borra mensaje
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
                //Borra mensaje
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

int ejemplo()
{
    initscr();            // Iniciar ncurses
    cbreak();             // Desactivar buffer de línea
    noecho();             // No mostrar caracteres al escribir
    keypad(stdscr, TRUE); // Habilitar teclas especiales
    curs_set(0);          // Ocultar el cursor

    int choice = 0;
    int ch;

    while (1)
    {
        clear();
        mvprintw(0, 0, "Selecciona un nodo:");

        for (int i = 0; i < NUM_ITEMS; i++)
        {
            if (i == choice)
            {
                attron(A_REVERSE); // Resaltar selección
                mvprintw(2 + i, 2, "%s", items[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(2 + i, 2, "%s", items[i]);
            }
        }

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = NUM_ITEMS - 1;
            break;
        case KEY_DOWN:
            choice++;
            if (choice >= NUM_ITEMS)
                choice = 0;
            break;
        case 10: // Enter
            if (choice == NUM_ITEMS - 1)
            { // "Salir"
                endwin();
                return 0;
            }
            else
            {
                // Aquí puedes ejecutar una acción sobre el nodo seleccionado
                mvprintw(10, 2, "Seleccionaste %s", items[choice]);
                refresh();
                getch(); // Esperar tecla para continuar
            }
            break;
        }
    }

    endwin(); // Restaurar terminal
    return 0;
}
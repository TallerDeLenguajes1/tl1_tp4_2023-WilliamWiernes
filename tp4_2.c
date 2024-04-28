#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DESC 100
#define MIN_DUR 10
#define MAX_DUR 100

typedef struct
{
    int TareaID;       // Numerado en ciclo iterativo
    char *Descripcion; // Descripción de la tarea
    int Duracion;      // Entre 10 – 100
} Tarea;

typedef struct Nodo
{
    Tarea T;                // Tarea
    struct Nodo *Siguiente; // Puntero a la siguiente Tarea
} Nodo;

// Módulos
int MenuOpciones();
Nodo *CrearTarea(int ID);
void InsertarTarea(Nodo **Tareas, Nodo *Tarea);
void ListarTareasPyR(Nodo *TareasPendientes, Nodo *TareasRealizadas);
void TareaRealizada(Nodo **TareasPendientes, Nodo **TareasRealizadas, int IDSeleccion);
void BuscarTareaIDPC(Nodo *TareasPendientes, Nodo *TareasRealizadas);
void BuscarID(Nodo *TareasPendientes, Nodo *TareasRealizadas);
void BuscarPC(Nodo *TareasPendientes, Nodo *TareasRealizadas);

int main()
{
    // 1.-
    Nodo *TareasPendientes = NULL;
    int id = 1000;
    int finalizar = 0;

    // 2.-
    Nodo *TareasRealizadas = NULL;
    int IDSeleccion;

    int menu;
    do
    {
        menu = MenuOpciones();

        switch (menu)
        {
        case 0:
            printf("\nSaliendo...");
            break;
        case 1:
            /* 1.- Desarrolle una interfaz de carga de tareas
            para solicitar tareas pendientes, en la cual se solicite
            descripción y duración de la misma (el id debe ser
            generado automáticamente por el sistema, de manera
            autoincremental comenzando desde el número 1000). Al cabo
            de cada tarea consulte al usuario si desea ingresar
            una nueva tarea o finalizar la carga. */
            printf("\n~~~1. Cargar Tareas Pendientes~~~");
            do
            {
                InsertarTarea(&TareasPendientes, CrearTarea(id));
                id++;

                printf("\nDesea finalizar la carga de tareas pendientes? 0 -> NO, Otro Num -> SI: ");
                fflush(stdin);
                scanf("%d", &finalizar);
            } while (finalizar == 0);
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            break;
        case 2:
            /* 2.- Implemente una interfaz para elegir qué
            tareas de la lista de pendientes deben ser
            transferidas a la lista de tareas realizadas. */
            printf("\n~~~2. Marcar Tarea como Realizada~~~");
            printf("\nID de la Tarea Realizada: ");
            fflush(stdin);
            scanf("%d", &IDSeleccion);

            TareaRealizada(&TareasPendientes, &TareasRealizadas, IDSeleccion);
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            break;
        case 3:
            /* 3.- Implemente una funcionalidad que permita
            listar todas las tareas pendientes y realizadas. */
            printf("\n~~~3. Mostrar Tareas Pendientes y Realizadas~~~");
            ListarTareasPyR(TareasPendientes, TareasRealizadas);
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            break;
        case 4:
            /* 4) Implemente una funcionalidad que permita
            consultar tareas por id o palabra clave y
            mostrarlas por pantalla, indicando si corresponde
            a una tarea pendiente o realizada.*/
            printf("\n~~~4. Buscar por ID o Palabra Clave~~~ ");
            BuscarTareaIDPC(TareasPendientes, TareasRealizadas);
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            break;
        default:
            printf("\n~~~~~~~~~~~~~~~~~~~~");
            printf("\nOpcion no reconocida");
            printf("\n~~~~~~~~~~~~~~~~~~~~");
            break;
        }
    } while (menu != 0);

    return 0;
}

int MenuOpciones()
{
    int menu;
    printf("\n\n~~~Menu De Opciones~~~");
    printf("\n0. Salir");
    printf("\n1. Cargar Tareas Pendientes");
    printf("\n2. Marcar Tarea como Realizada");
    printf("\n3. Mostrar Tareas Pendientes y Realizadas");
    printf("\n4. Buscar por ID o Palabra Clave");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nSeleccion: ");
    fflush(stdin);
    scanf("%d", &menu);

    return menu;
}

Nodo *CrearTarea(int ID)
{
    // Variables auxiliares
    char *Buff = (char *)malloc(MAX_DESC * sizeof(char));
    int duracion;

    Nodo *NuevaTarea = (Nodo *)malloc(sizeof(Nodo));

    NuevaTarea->T.TareaID = ID;
    printf("\nTarea pendiente con ID %d:", NuevaTarea->T.TareaID);

    do
    {
        printf("\n\tIngrese la descripcion (%d palabras maximo): ", MAX_DESC);
        fflush(stdin);
        gets(Buff);
    } while (strlen(Buff) > MAX_DESC);
    NuevaTarea->T.Descripcion = (char *)malloc((strlen(Buff) + 1) * sizeof(char));
    strcpy(NuevaTarea->T.Descripcion, Buff);

    do
    {
        printf("\n\tIngrese la duracion (%d - %d): ", MIN_DUR, MAX_DUR);
        fflush(stdin);
        scanf("%d", &duracion);
    } while (duracion < MIN_DUR || duracion > MAX_DUR);
    NuevaTarea->T.Duracion = duracion;

    NuevaTarea->Siguiente = NULL;

    free(Buff);

    return NuevaTarea;
}

void InsertarTarea(Nodo **Tareas, Nodo *Tarea)
{
    Tarea->Siguiente = *Tareas;
    *Tareas = Tarea;
}

void ListarTareasPyR(Nodo *TareasPendientes, Nodo *TareasRealizadas)
{
    printf("\nTareas Pendientes:");
    Nodo *AuxP = TareasPendientes;
    if (AuxP != NULL)
    {
        while (AuxP)
        {
            printf("\nTarea ID %d", AuxP->T.TareaID);
            printf("\n\tDescripcion: %s", AuxP->T.Descripcion);
            printf("\n\tDuracion: %d", AuxP->T.Duracion);

            AuxP = AuxP->Siguiente;
        }
    }
    else
    {
        printf("\nNo hay Tareas Pendientes.");
    }

    printf("\nTareas Realizadas:");
    Nodo *AuxR = TareasRealizadas;
    if (AuxR != NULL)
    {
        while (AuxR)
        {
            printf("\nTarea ID %d", AuxR->T.TareaID);
            printf("\n\tDescripcion: %s", AuxR->T.Descripcion);
            printf("\n\tDuracion: %d", AuxR->T.Duracion);

            AuxR = AuxR->Siguiente;
        }
    }
    else
    {
        printf("\nNo hay Tareas Realizadas.");
    }
}

void TareaRealizada(Nodo **TareasPendientes, Nodo **TareasRealizadas, int IDSeleccion)
{
    Nodo *Actual = *TareasPendientes;
    Nodo *Anterior = NULL;

    // Busco la tarea con el ID seleccionado en la lista de pendientes
    while (Actual != NULL && Actual->T.TareaID != IDSeleccion)
    {
        Anterior = Actual;
        Actual = Actual->Siguiente;
    }

    if (Actual != NULL) // Si es NULL llegó al final de la lista, y no encontró nada.
    {
        // Encuentro la tarea en la lista de pendientes
        if (Anterior != NULL)
        {
            // Si no es la primera tarea de la lista
            Anterior->Siguiente = Actual->Siguiente;
        }
        else
        {
            // Si es la primera tarea de la lista
            *TareasPendientes = Actual->Siguiente;
        }

        // Guardo la tarea en la lista de realizadas
        Actual->Siguiente = *TareasRealizadas;
        *TareasRealizadas = Actual;

        printf("\nTarea con ID %d marcada como Realizada correctamente", IDSeleccion);
    }
    else
    {
        printf("\nNo se encontro Tarea con ID %d en Pendientes", IDSeleccion);
    }
}

void BuscarID(Nodo *TareasPendientes, Nodo *TareasRealizadas)
{
    Nodo *AuxP = TareasPendientes;
    int IDSeleccion;

    printf("\nIngrese el ID de la Tarea: ");
    scanf("%d", &IDSeleccion);

    // Primero busco la tarea en Pendientes
    while (AuxP != NULL && AuxP->T.TareaID != IDSeleccion)
    {
        AuxP = AuxP->Siguiente;
    }

    if (AuxP != NULL)
    {
        printf("\nTarea ID %d esta Pendiente:", AuxP->T.TareaID);
        printf("\n\tDescripcion: %s", AuxP->T.Descripcion);
        printf("\n\tDuracion: %d", AuxP->T.Duracion);
        return;
    }

    // Si no está en Pendientes, busco en Realizadas
    Nodo *AuxR = TareasRealizadas;

    while (AuxR != NULL && AuxR->T.TareaID != IDSeleccion)
    {
        AuxR = AuxR->Siguiente;
    }

    if (AuxR != NULL)
    {
        printf("\nTarea ID %d esta Realizada:", AuxR->T.TareaID);
        printf("\n\tDescripcion: %s", AuxR->T.Descripcion);
        printf("\n\tDuracion: %d", AuxR->T.Duracion);
        return;
    }

    // Si no, muestro un mensaje de error
    printf("\nNo se encontro la Tarea con ID %d", IDSeleccion);
}

void BuscarPC(Nodo *TareasPendientes, Nodo *TareasRealizadas)
{
    Nodo *AuxP = TareasPendientes;
    char *Busqueda = (char *)malloc(MAX_DESC * sizeof(char));
    int bandera = 0;

    do
    {
        printf("\nIngrese su busqueda (%d palabras maximo): ", MAX_DESC);
        fflush(stdin);
        gets(Busqueda);
    } while (strlen(Busqueda) > MAX_DESC);

    while (AuxP)
    {
        // Muestro todas las Pendientes que coincidan con la Palabra Clave
        if (strstr(AuxP->T.Descripcion, Busqueda))
        {
            printf("\nTarea ID %d esta Pendiente", AuxP->T.TareaID);
            printf("\n\tDescripcion: %s", AuxP->T.Descripcion);
            printf("\n\tDuracion: %d", AuxP->T.Duracion);
            bandera = 1;
        }
        AuxP = AuxP->Siguiente;
    }

    Nodo *AuxR = TareasRealizadas;

    while (AuxR)
    {
        // Muestro todas las Realizadas que coincidan con la Palabra Clave
        if (strstr(AuxR->T.Descripcion, Busqueda))
        {
            printf("\nTarea ID %d esta Realizada", AuxR->T.TareaID);
            printf("\n\tDescripcion: %s", AuxR->T.Descripcion);
            printf("\n\tDuracion: %d", AuxR->T.Duracion);
            bandera = 1;
        }
        AuxR = AuxR->Siguiente;
    }

    if(bandera == 0)
        printf("\nNo se encontro una Tarea con la palabra clave %s", Busqueda);

    free(Busqueda);
}

void BuscarTareaIDPC(Nodo *TareasPendientes, Nodo *TareasRealizadas)
{
    int opcion;

    printf("\n1. Buscar por ID");
    printf("\n2. Buscar por Palabra Clave");
    printf("\nSeleccion: ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        BuscarID(TareasPendientes, TareasRealizadas);
        break;
    case 2:
        BuscarPC(TareasPendientes, TareasRealizadas);
        break;
    default:
        printf("\nOpcion no reconocida");
        break;
    }
}
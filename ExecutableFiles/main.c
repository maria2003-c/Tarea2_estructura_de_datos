#include <stdio.h>
#include "../DeclarationFiles/funciones.h"

/*Inicializa las estructuras vacias del catalogo y luego entra a un 
ciclo do-while para mostrar el menu interactivo. 
Redirige a las distintas opciones segun lo que ingrese el usuario 
y se ejecuta hasta que se ingresa el 0.*/
int main() {
    Catalogo* mi_catalogo = inicializar_catalogo();
    int opcion;

    do {
        printf("\n======= STREAMFINDER 🍿 =======\n");
        printf("1. Cargar Catálogo\n");
        printf("2. Buscar por Género\n");
        printf("3. Buscar por Director\n");
        printf("4. Buscar por Década\n");
        printf("5. Búsqueda Avanzada (Género + Década)\n");
        printf("6. Gestionar Mi Watchlist\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");

        if (scanf("%d", &opcion) != 1) break;

        switch(opcion) {
            case 1: cargar_catalogo(mi_catalogo); break;
            case 2: buscar_por_genero(mi_catalogo); break;
            case 3: buscar_por_director(mi_catalogo); break;
            case 4: buscar_por_decada(mi_catalogo); break;
            case 5: busqueda_avanzada(mi_catalogo); break;
            case 6: gestionar_watchlist(mi_catalogo); break;
            case 0: printf("Saliendo de StreamFinder...\n"); break;
            default: printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 0);

    return 0;
}
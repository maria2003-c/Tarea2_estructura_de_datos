#include "../DeclarationFiles/funciones.h"

void extraer_campo(char* linea, int indice, char* destino, int limite) {
    int i = 0, j = 0, comillas = 0, idx_actual = 0;

    while (linea[i] != '\0' && linea[i] != '\n' && linea[i] != '\r') {
        if (linea[i] == '\"') {
            comillas = !comillas; 
        } else if (linea[i] == ',' && !comillas) {
            if (idx_actual == indice) break;
            idx_actual++;
            j = 0; 
        } else {
            if (idx_actual == indice) {
                if (j < limite - 1) { 
                    destino[j++] = linea[i];
                }
            }
        }
        i++;
    }
    destino[j] = '\0';
}

Catalogo* inicializar_catalogo() {
    Catalogo* cat = (Catalogo*)malloc(sizeof(Catalogo));
    cat->mapa_id = map_create(3000);        
    cat->mapa_generos = map_create(200);    
    cat->mapa_directores = map_create(3000); 
    cat->watchlist = list_create();
    return cat;
}

void cargar_catalogo(Catalogo* cat) {
    char archivo[100];
    printf("Ingrese el nombre del archivo (ej. Top1500.csv): ");
    scanf("%s", archivo);

    FILE* file = fopen(archivo, "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s\n", archivo);
        return;
    }

    char linea[2048];
    fgets(linea, 2048, file); 

    int cont = 0;
    while (fgets(linea, 2048, file)) {
        if (strlen(linea) < 10) continue; 

        Pelicula* p = (Pelicula*)malloc(sizeof(Pelicula));
        char temp_num[100];

        extraer_campo(linea, 1, p->id, sizeof(p->id));
        extraer_campo(linea, 5, p->titulo, sizeof(p->titulo));
        extraer_campo(linea, 11, p->generos, sizeof(p->generos));
        extraer_campo(linea, 14, p->directores, sizeof(p->directores));

        extraer_campo(linea, 8, temp_num, sizeof(temp_num));
        p->rating = atof(temp_num);

        extraer_campo(linea, 10, temp_num, sizeof(temp_num));
        p->anio = atoi(temp_num);

        
        map_insert(cat->mapa_id, p->id, p);

        char copia_gen[500];
        strcpy(copia_gen, p->generos);
        char* token = strtok(copia_gen, ", ");
        while (token != NULL) {
            List* lista_gen = (List*)map_search(cat->mapa_generos, token);
            if (lista_gen == NULL) {
                lista_gen = list_create();
                map_insert(cat->mapa_generos, strdup(token), lista_gen);
            }
            list_pushBack(lista_gen, p);
            token = strtok(NULL, ", ");
        }

        List* lista_dir = (List*)map_search(cat->mapa_directores, p->directores);
        if (lista_dir == NULL) {
            lista_dir = list_create();
            map_insert(cat->mapa_directores, strdup(p->directores), lista_dir);
        }
        list_pushBack(lista_dir, p);

        cont++;
    }
    fclose(file);
    printf("¡Catálogo cargado! Se indexaron %d películas.\n", cont);
}

void buscar_por_genero(Catalogo* cat) {
    char genero[100];
    printf("Ingrese el género a buscar (Ej. Sci-Fi, Action, Drama): ");
    scanf("%99s", genero);

    List* resultados = (List*)map_search(cat->mapa_generos, genero);
    if (!resultados) {
        printf("No se encontraron películas para el género '%s'.\n", genero);
        return;
    }

    Pelicula* p = (Pelicula*)list_first(resultados);
    while (p != NULL) {
        printf("- [%s] %s (%d) | Rating: %.1f\n", p->id, p->titulo, p->anio, p->rating);
        p = (Pelicula*)list_next(resultados);
    }
}

void buscar_por_director(Catalogo* cat) {
    char director[200];
    printf("Ingrese nombre del director (considerar mayúsculas): ");
    getchar();
    fgets(director, 200, stdin);
    director[strcspn(director, "\n")] = 0; 

    List* resultados = (List*)map_search(cat->mapa_directores, director);
    if (!resultados) {
        printf("No se encontraron películas del director '%s'.\n", director);
        return;
    }

    Pelicula* p = (Pelicula*)list_first(resultados);
    while (p != NULL) {
        printf("- [%s] %s (%d) | Rating: %.1f\n", p->id, p->titulo, p->anio, p->rating);
        p = (Pelicula*)list_next(resultados);
    }
}

void buscar_por_decada(Catalogo* cat) {
    int anio;
    printf("Ingrese un año de referencia para la década (Ej. 1990): ");
    scanf("%d", &anio);

    int decada_inicio = (anio / 10) * 10;
    int decada_fin = decada_inicio + 9;

    printf("\nPelículas entre %d y %d:\n", decada_inicio, decada_fin);
    Pelicula* p = (Pelicula*)map_first(cat->mapa_id);
    int encontradas = 0;
    while (p != NULL) {
        if (p->anio >= decada_inicio && p->anio <= decada_fin) {
            printf("- %s (%d)\n", p->titulo, p->anio);
            encontradas++;
        }
        p = (Pelicula*)map_next(cat->mapa_id);
    }
    if(encontradas == 0) printf("No hay películas en esa década.\n");
}

void busqueda_avanzada(Catalogo* cat) {
    char genero[100];
    int anio;
    printf("Ingrese Género: ");
    scanf("%99s", genero);
    printf("Ingrese Año (Década): ");
    scanf("%d", &anio);

    int decada_inicio = (anio / 10) * 10;
    int decada_fin = decada_inicio + 9;

    List* resultados = (List*)map_search(cat->mapa_generos, genero);
    if (!resultados) {
        printf("No hay películas de ese género.\n");
        return;
    }

    printf("\nResultados para '%s' en los %ds:\n", genero, decada_inicio);
    Pelicula* p = (Pelicula*)list_first(resultados);
    int encontradas = 0;
    while (p != NULL) {
        if (p->anio >= decada_inicio && p->anio <= decada_fin) {
            printf("- %s (%d) | %s\n", p->titulo, p->anio, p->directores);
            encontradas++;
        }
        p = (Pelicula*)list_next(resultados);
    }
    if(encontradas == 0) printf("No hubo coincidencias.\n");
}

void gestionar_watchlist(Catalogo* cat) {
    int opcion;
    char id[50];
    printf("\n--- Mi Watchlist ---\n");
    printf("1. Agregar Película\n");
    printf("2. Eliminar Película\n");
    printf("3. Mostrar Watchlist\n");
    printf("Seleccione: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        printf("Ingrese ID de la película (Ej. tt0068646): ");
        scanf("%49s", id);
        Pelicula* p = (Pelicula*)map_search(cat->mapa_id, id);
        if (p) {
            list_pushBack(cat->watchlist, p);
            printf("'%s' añadida a tu Watchlist.\n", p->titulo);
        } else {
            printf("Error: El ID %s no existe en el catálogo.\n", id);
        }
    } else if (opcion == 2) {
        printf("Ingrese ID a eliminar: ");
        scanf("%49s", id);
        Pelicula* p = (Pelicula*)map_search(cat->mapa_id, id);
        if (p && list_erase(cat->watchlist, p)) {
            printf("Película eliminada de la Watchlist.\n");
        } else {
            printf("Película no encontrada en tu Watchlist.\n");
        }
    } else if (opcion == 3) {
        Pelicula* p = (Pelicula*)list_first(cat->watchlist);
        if (!p) printf("Tu Watchlist está vacía.\n");
        while (p != NULL) {
            printf("- [%s] %s (%d)\n", p->id, p->titulo, p->anio);
            p = (Pelicula*)list_next(cat->watchlist);
        }
    }
}
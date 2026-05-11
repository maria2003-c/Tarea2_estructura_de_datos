#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "complement.h"


typedef struct {
    char id[100];
    char titulo[700];
    char generos[700];
    char directores[700];
    int anio;
    float rating;
} Pelicula;

typedef struct {
    Map* mapa_id;
    Map* mapa_generos;
    Map* mapa_directores;
    List* watchlist;
} Catalogo;

Catalogo* inicializar_catalogo();
void cargar_catalogo(Catalogo* cat);
void buscar_por_genero(Catalogo* cat);
void buscar_por_director(Catalogo* cat);
void buscar_por_decada(Catalogo* cat);
void busqueda_avanzada(Catalogo* cat);
void gestionar_watchlist(Catalogo* cat);

#endif
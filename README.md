StreamFinder
===

Este programa es una herramienta de línea de comandos diseñada para gestionar y explorar un catálogo masivo de películas y series de manera eficiente. Su característica principal es el uso intensivo de Tipos de Datos Abstractos (TDAs), específicamente Mapas (Hash Maps) y Listas Enlazadas, para garantizar que las búsquedas complejas respondan de forma instantánea sin tener que recorrer todo el catálogo linealmente. 

---
# Compilación y ejecución

El programa fue desarrollado en lenguaje C diseñado modularmente para el manejo eficiente y seguro de la memoria y la lectura de archivos CSV.

## Requisitos previos

1. Tener un compilador de C (como `gcc`).
2. Contar con los archivos base del proyecto ordenados en sus carpetas (`DeclarationFiles` y `ExecutableFiles`).
3. Tener el archivo de datos `Top1500.csv` en la carpeta raíz del proyecto.

### Compilación

Para compilar el proyecto, asegúrate de estar en la carpeta raíz y ejecuta el siguiente comando en tu terminal:

```bash
gcc ExecutableFiles/main.c ExecutableFiles/funciones.c ExecutableFiles/complement.c -o StreamFinder
```

Este comando vinculará la lógica del planificador con la implementación del TDA y generará un archivo ejecutable llamado `StreamFinder`.

### Ejecución

Una vez compilado, inicia el programa con el siguiente comando:

```bash
./StreamFinder
```
---
# Funcionalidades implementadas

## Funcionan Correctamente

1. **Cargar Catálogo:** Lee el archivo CSV procesando correctamente campos con comas internas. Indexa de inmediato las películas en tres Hash Maps independientes (por ID, por Género y por Director) para optimizar el rendimiento futuro. 
2. **Buscar por Género:** Permite buscar categorías (ej. "Sci-Fi", "Action") y retorna los resultados al instante (O(1)) gracias al índice de Mapas. 
3. **Buscar por Director:** Localiza todas las obras de un director específico ingresado por la usuaria de forma inmediata.
4. **Buscar por Década:** A partir de un año base (ej. 1990), calcula el rango y muestra todas las películas lanzadas en esa década. 
5. **Búsqueda Avanzada (Doble Criterio):** Primero localiza instantáneamente el género a través del Mapa, y luego filtra eficientemente esa lista reducida por la década solicitada. 
6. **Gestionar Mi Watchlist:** Permite crear una lista personalizada de pendientes. Al agregar por ID, el sistema valida en tiempo constante (O(1)) que la película exista realmente en el catálogo cargado antes de añadirla. Permite además eliminar y mostrar la lista.

---
# Ejemplo de uso

### Paso 1: Cargar la base de datos
La usuaria inicia el programa y carga el archivo CSV.

    ======= STREAMFINDER 🍿 =======
    1. Cargar Catálogo
    2. Buscar por Género
    ...
    Seleccione una opción: 1

    Ingrese el nombre del archivo (ej. Top1500.csv): Top1500.csv
    ¡Catálogo cargado! Se indexaron 1500 películas.

### Paso 2: Realizar una búsqueda avanzada
Se cruzan datos para encontrar películas muy específicas. 

    Seleccione una opción: 5

    Ingrese Género: Drama
    Ingrese Año (Década): 1990

    Resultados para 'Drama' en los 1990s:
    - The Shawshank Redemption (1994) | Frank Darabont
    - Forrest Gump (1994) | Robert Zemeckis
    - Fight Club (1999) | David Fincher

### Paso 3: Agregar películas a la Watchlist
La usuaria copia el ID de una película que le interesó y la guarda para más tarde.

    eleccione una opción: 6

    --- Mi Watchlist ---
    1. Agregar Película
    2. Eliminar Película
    3. Mostrar Watchlist
    Seleccione: 1

    Ingrese ID de la película (Ej. tt0068646): tt0111161
    'The Shawshank Redemption' añadida a tu Watchlist.

### Paso 4: Visualizar la lista de pendientes
Revisa las películas que ha guardado. 

    Seleccione: 3

    - [tt0111161] The Shawshank Redemption (1994)

### Paso 5: Salir del programa
La usuaria finaliza la sesión.

    Seleccione una opción: 0

    Saliendo de StreamFinder...
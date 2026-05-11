StreamFinder
===

Este programa es un sistema de gestión de pendientes diseñado para organizar tareas por categorías personalizadas. Su característica principal es el cumplimiento estricto del orden de llegada (FIFO): la tarea que se registró primero es siempre la primera en ser atendida, sin importar su categoría. 

---
# Compilación y ejecución

El programa fue desarrollado en lenguaje C y utiliza Tipos de Datos Abstractos (TDAs) para el manejo eficiente de la memoria.

## Requisitos previos

1. Tener un compilador de C (como `gcc`).
2. Contar con los archivos del TDA Lista (`complement.h` y `complement.c`). 

### Compilación

Para compilar el proyecto, asegúrate de estar en la carpeta raíz y ejecuta el siguiente comando en tu terminal:

```bash
gcc ExecutableFiles/main.c ExecutableFiles/funciones.c ExecutableFiles/complement.c -o StreamFinder && ./StreamFinder
```

Este comando vinculará la lógica del planificador con la implementación del TDA y generará un archivo ejecutable llamado `SmartTODO`.

### Ejecución

Una vez compilado, inicia el programa con el siguiente comando:

```bash
./SmartTODO
```
---
# Funcionalidades implementadas

## Funcionan Correctamente

1. **Nueva Categoría:** Permite registrar nombres de categorías (ej. "Trabajo", "Hogar") para agrupar tareas. 
2. **Eliminar Categoría (Limpieza Total):** Elimina una categoría de la lista y borra automáticamente todas las tareas asociadas a ella. 
3. **Registrar Pendiente:** Añade una tarea solicitando descripción y categoría, asignando automáticamente la hora de registro. 
4. **Atender Siguiente (Despacho):** Busca y muestra la tarea más antigua del sistema, eliminándola permanentemente para liberar el pendiente. 
5. **Visualización del Tablero General:** Muestra la lista completa de pendientes ordenados cronológicamente desde el más antiguo. 
6. **Filtrado por Categoría:** Permite visualizar únicamente las tareas de una categoría específica sin eliminarlas. 

---
# Ejemplo de uso

### Paso 1: Configurar categorías
El usuario crea las categorías necesarias para organizar sus pendientes.

    === MENU PRINCIPAL ===
    1. Nueva Categoria
    2. Eliminar Categoria
    3. Registrar Tarea
    ...
    Ingrese la opcion: 1

    Ingrese el nombre de la categoria a crear: Oficina
    Categoria agregada exitosamente.

### Paso 2: Registrar una tarea
Se añade un pendiente vinculándolo a una categoría existente. 

    Ingrese la opcion: 3

    Ingrese categoria: Oficina
    Ingrese descripcion: Enviar reporte mensual
    Tarea registrada a las 10:05.

### Paso 3: Atender el siguiente pendiente
El sistema prioriza la tarea más antigua para ser despachada.

    Ingrese la opcion: 4

    Atendiendo: Enviar reporte mensual | Categoria: Oficina | Registrada a las: 10:05
    Tarea eliminada del sistema.

### Paso 4: Visualizar tablero general
Se revisan todos los pendientes actuales ordenados por llegada. 

    Ingrese la opcion: 5

    === TABLERO GENERAL ===
    Comprar pan (Hogar)
    Llamar a cliente (Oficina)

### Paso 5: Salir del programa
El usuario finaliza la gestión de sus tareas. 

    Ingrese la opcion: 0

    Muchas gracias por usar el administrador de tareas.
    Adiós.
# tp_algoritmos_2026

## NO PUSHAR COSAS SIN COMPILAR PEDIR AYUDA Y HABLAR EN EL GRUPO

## Cómo arrancar a trabajar y hacer cambios?
SIEMPRE HACER GIT PULL
1. Si hay conflictos y problemas hablar al grupo
2. En caso de demorar mucho intentar resolverlo
3. Consultar con chatGPT

## Cómo compilar?
Ejecutar el siguiente comando
```cmd
g++ *.cpp -o tp_ejecutable
```

## Cómo ejecutar el programa?
Ejecutar el siguiente comando
```cmd
./tp_ejecutable
```

## Cómo agregar nuevos subprogramas?
1. Crear el archivo del subprograma en la raiz. Ejemplo
    ```
    mostrar_ataque.cpp
    ```
2. Agregar la interfaz del subprograma en **tp_lib.h**
3. Volver a compilar el proyecto

## Cómo agregar nuevas funciones comunes?
1. Crear la funcion en el archivo `funciones_comunes.cpp`.
    Ejemplo
    ```c++
    bool ValidarDespegue(tAtaque *Ataque, tAccion accion) {
      //contenido
    }
    ```
2. Agregar la interfaz de la función común en **funciones_comunes.h**
3. Volver a compilar el proyecto
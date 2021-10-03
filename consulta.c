#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>

int Posicion(char *nombre_jugador, int id_partida);

int main(void) {
    // Si dos jugadores tienen la misma puntuacion compartiran la posicion mas baja
    // Pero el jugador de detras seguira teniendo la posicion correspondiente
    printf("Posicion de %s en la partida %d: %d\n", "Jonathan", 1, Posicion("Jonathan", 1));
    printf("Posicion de %s en la partida %d: %d\n", "Alba", 1, Posicion("Alba", 1));
    printf("Posicion de %s en la partida %d: %d\n", "Raul", 1, Posicion("Raul", 1));
    printf("Posicion de %s en la partida %d: %d\n", "Miguel", 1, Posicion("Miguel", 1));

    // Si un jugador no participo en la partida devolvera -1
    printf("\nPosicion de %s en la partida %d: %d\n", "Jonathan", 2, Posicion("Jonathan", 2));
    printf("Posicion de %s en la partida %d: %d\n", "Alba", 2, Posicion("Alba", 2));
    printf("Posicion de %s en la partida %d: %d\n", "Raul", 2, Posicion("Raul", 2));
    printf("Posicion de %s en la partida %d: %d\n", "Miguel", 2, Posicion("Miguel", 2));
}

int Posicion(char *nombre_jugador, int id_partida) {
    /*
    Descripcion:
        Devuelve la posicion en la que ha quedado el jugador en la partida.
    Parametros:
        nombre_jugador: pointer a nombre del jugador
        id_partida: id de la partida
    Retorno:
        Posicion del jugador en la partida desde 1, -1 si no participa o ha habido un error.
    */
    MYSQL *conn;
    MYSQL_RES *tabla;
    MYSQL_ROW fila;
    char buffer[160];
    int numj, puntuacion, *puntos;
    int i, j, aux;

    if ((conn = mysql_init(NULL)) == NULL) {
        printf("Error al inicializar MySQL: %u %s\n", mysql_errno(conn), mysql_error(conn));
        return -1;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "mysql", "catan", 0, NULL, 0);
    if (conn == NULL) {
        printf("Error al conectar con MySQL: %u %s\n", mysql_errno(conn), mysql_error(conn));
        return -1;
    }

    sprintf(buffer, "SELECT Jugador.nombre, Participacion.puntos FROM (Jugador, Participacion)"
            "WHERE Participacion.IdP = %d AND Jugador.id = Participacion.idJ;", id_partida);

    if (mysql_query(conn, buffer) != 0) {
        printf("Error en la consulta de datos: %u %s\n", mysql_errno(conn), mysql_error(conn));
        return -1;
    }

    tabla = mysql_store_result(conn);
    numj = mysql_num_rows(tabla);

    // Reservamos la memoria del array de puntos dinámicamente
    puntos = (int *)calloc(numj, sizeof(int));
    puntuacion = -1;
    i = 0;
    while ((fila = mysql_fetch_row(tabla)) != NULL) {
        // Guardamos la puntuacion que nos interesa a parte
        if (strcmp(nombre_jugador, fila[0]) == 0) {
            puntuacion = atoi(fila[1]);
        }
        // Guardamos todas las puntuaciones en un vector
        puntos[i++] = atoi(fila[1]);
    }

    // El jugador no participo en la partida
    if (puntuacion == -1)
        return -1;

    // Cerrar la conexion y liberar la memoria
    mysql_close(conn);

    // Ordenar las puntuaciones de mayor a menor (bubblesort)
    for (i = 0; i < numj - 1; i++) {
        for (j = 0; j < (numj - i - 1); j++) {
            if (puntos[j+1] > puntos[j]) {
                aux = puntos[j];
                puntos[j] = puntos[j+1];
                puntos[j+1] = aux;
            }
        }
    }


    for (i = 0; i < numj; i++) {
        if (puntos[i] == puntuacion) {
            // Liberamos la memoria de puntos y devolvemos el valor
            free(puntos);
            return i+1;
        }
    }
}


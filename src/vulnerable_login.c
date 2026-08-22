/*
 * CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
 *
 * Demo 1: el overflow "pisa" una variable vecina en el stack y altera
 * el flujo del programa sin que el usuario conozca ninguna contraseña.
 *
 * Fines educativos unicamente. Compilar con las protecciones del
 * compilador deshabilitadas a proposito (ver Makefile) para poder
 * observar el comportamiento clasico descripto en CWE-120.
 */
#include <stdio.h>
#include <string.h>

void login(void) {
    char usuario[16];      /* buffer de entrada, sin verificar tamaño */
    int  acceso_admin = 0; /* variable vecina en el stack */

    printf("Usuario: ");
    fflush(stdout);

    /* CWE-120: gets() nunca verifica cuantos bytes escribe en el buffer */
    gets(usuario);

    if (acceso_admin) {
        printf("[OK] Acceso concedido como administrador.\n");
    } else {
        printf("[--] Acceso denegado para el usuario '%s'.\n", usuario);
    }
}

int main(void) {
    login();
    return 0;
}

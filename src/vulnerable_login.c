/*
 * CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
 *
 * Demo 1: el overflow "pisa" una variable vecina en el stack y altera
 * el flujo del programa sin que el usuario conozca ninguna contraseña.
 
 */
#include <stdio.h>
#include <string.h>

void login(void) {
    char usuario[16];      /* buffer de entrada, sin verificar tamaño */
    int  acceso_admin = 0; /* variable vecina en el stack */

    printf("Usuario: ");
    fflush(stdout);

    /* CWE-120: scanf con %s no limita la cantidad de caracteres copiados */
    /* Se puede escribir más de 16 caracteres y sobrescribir la variable acceso_admin */
    scanf("%s", usuario);

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

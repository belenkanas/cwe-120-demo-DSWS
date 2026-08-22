/*
 * Version corregida de vulnerable_login.c
 * Mitigacion aplicada (Fase de Implementacion, CWE-120):
 *   - Reglas de asignacion y administracion de memoria:
 *     se usa fgets(), que SI recibe el tamaño del buffer como parametro
 *     y nunca escribe mas alla de sus limites.
 */
#include <stdio.h>
#include <string.h>

void login(void) {
    char usuario[16];
    int  acceso_admin = 0;

    printf("Usuario: ");
    fflush(stdout);

    if (fgets(usuario, sizeof(usuario), stdin) == NULL) {
        return;
    }
    /* fgets conserva el '\n' final; lo removemos si esta presente */
    usuario[strcspn(usuario, "\n")] = '\0';

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

/*
 * Version corregida de vulnerable_apellido.c
 * Mitigacion aplicada (Fase de Implementacion, CWE-120):
 *   - Se limita explicitamente el ancho de campo en scanf ("%19s")
 *     para que nunca escriba mas de 19 caracteres + '\0' en un buffer
 *     de 20 bytes. Es el equivalente, para scanf, a "truncar la
 *     cadena de entrada a una longitud razonable" que menciona
 *     la diapositiva de mitigaciones.
 */
#include <stdio.h>

int main(void) {
    char last_name[20];

    printf("Enter your last name: ");
    fflush(stdout);

    scanf("%19s", last_name);

    printf("Hola, %s\n", last_name);
    return 0;
}

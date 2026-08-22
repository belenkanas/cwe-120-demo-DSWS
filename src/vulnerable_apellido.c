/*
 * CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
 *
 * Demo 2: reproduccion directa del ejemplo teorico de la diapositiva 7
 * (tomado de la definicion oficial de CWE-120). Un buffer de 20 bytes
 * recibe una entrada mas larga y se corrompe la memoria vecina,
 * lo que termina en un segmentation fault.
 *
 * Fines educativos unicamente.
 */
#include <stdio.h>

int main(void) {
    char last_name[20];

    printf("Enter your last name: ");
    fflush(stdout);

    /* CWE-120: scanf con %s no limita la cantidad de caracteres copiados */
    scanf("%s", last_name);

    printf("Hola, %s\n", last_name);
    return 0;
}

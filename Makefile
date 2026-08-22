CC = gcc
CFLAGS_SAFE = -g -O0 -Wall
# Flags SOLO para los binarios vulnerables: se apaga a proposito el
# stack protector de gcc para poder observar el comportamiento
# "clasico" que describe CWE-120. NUNCA usar estas flags en software real.
CFLAGS_VULN = -g -O0 -fno-stack-protector -z execstack -no-pie -Wno-deprecated-declarations

all: vulnerable_login vulnerable_apellido fixed_login fixed_apellido

vulnerable_login: src/vulnerable_login.c
	$(CC) $(CFLAGS_VULN) -o $@ $<

vulnerable_apellido: src/vulnerable_apellido.c
	$(CC) $(CFLAGS_VULN) -o $@ $<

fixed_login: src/fixed_login.c
	$(CC) $(CFLAGS_SAFE) -o $@ $<

fixed_apellido: src/fixed_apellido.c
	$(CC) $(CFLAGS_SAFE) -o $@ $<

clean:
	rm -f vulnerable_login vulnerable_apellido fixed_login fixed_apellido

.PHONY: all clean

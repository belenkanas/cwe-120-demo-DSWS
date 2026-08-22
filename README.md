# CWE-120 — Classic Buffer Overflow (demo educativa)

Demo local para la presentación de **CWE-120: Buffer Copy without Checking
Size of Input ('Classic Buffer Overflow')**, curso de Desarrollo Seguro de
Software (UCU).

> ⚠️ **Uso educativo únicamente.** El Makefile deshabilita a propósito
> protecciones del compilador (stack protector, NX, PIE) para poder
> observar el comportamiento "clásico" que describe CWE-120. Nunca
> compilar software real con estas flags.

## Requisitos

- Linux (o WSL) con `gcc` y `make`.
- Opcional: `gdb`, para inspeccionar la corrupción de memoria en vivo.

## Estructura

```
cwe-120-demo/
├── README.md
├── Makefile
└── src/
    ├── vulnerable_login.c     # Demo 1: bypass de un chequeo por overflow
    ├── fixed_login.c          # Demo 1 corregida (fgets)
    ├── vulnerable_apellido.c  # Demo 2: ejemplo oficial de CWE-120 (crash)
    └── fixed_apellido.c       # Demo 2 corregida (scanf con ancho fijo)
```

## Compilar

```bash
make        # compila los 4 binarios
make clean  # limpia
```

## Demo 1 — Bypass de un control por desbordamiento (`vulnerable_login`)

`usuario[16]` y `acceso_admin` (un `int`, inicializado en `0`) son
variables vecinas en el stack. Si la entrada supera el tamaño del
buffer, sigue escribiéndose en la memoria contigua — en este caso, en
`acceso_admin` — y se puede "conceder acceso" sin conocer ninguna
contraseña.

```bash
# Caso normal
echo "belen" | ./vulnerable_login
# -> [--] Acceso denegado para el usuario 'belen'.

# Caso con overflow: 32 caracteres alcanzan para pisar acceso_admin
python3 -c "print('A'*32)" | ./vulnerable_login
# -> [OK] Acceso concedido como administrador.
```

Con la versión corregida, el mismo payload ya no altera el flujo:

```bash
python3 -c "print('A'*32)" | ./fixed_login
# -> [--] Acceso denegado para el usuario 'AAAA...' (truncado a 15 caracteres)
```

**Por qué funciona:** `gets()` (CWE-120) copia toda la entrada sin
límite. `fgets(usuario, sizeof(usuario), stdin)` sí conoce el tamaño
del buffer y nunca escribe más allá de sus límites.

## Demo 2 — El ejemplo oficial de CWE-120 (`vulnerable_apellido`)

Reproduce el código de la diapositiva 7 (`char last_name[20]` +
`scanf("%s", last_name)`). Con una entrada larga se corrompe memoria
más allá del buffer y el programa termina en `Segmentation fault`,
mostrando el impacto de **Disponibilidad (DoS)** de la diapositiva 6.

```bash
python3 -c "print('A'*50)" | ./vulnerable_apellido
# -> Segmentation fault
```

Con la versión corregida (`scanf("%19s", last_name)`), la misma
entrada se trunca de forma segura y el programa no crashea:

```bash
python3 -c "print('A'*50)" | ./fixed_apellido
# -> Hola, AAAAAAAAAAAAAAAAAAA
```

### Opcional: ver la corrupción con gdb

```bash
gdb ./vulnerable_apellido
(gdb) run <<< $(python3 -c "print('A'*50)")
(gdb) bt        # backtrace: se ve la dirección de retorno corrupta
```

Esto alcanza para mostrar en clase *por qué* pasa (memoria contigua
sobrescrita), sin necesidad de construir un exploit real.

## Relación con la presentación

| Diapositiva | Contenido | Archivo de la demo |
|---|---|---|
| 7 — Ejemplos teóricos | Código base (`last_name[20]`) | `vulnerable_apellido.c` |
| 6 — Consecuencias comunes | DoS: caída del programa | `vulnerable_apellido.c` (crash) |
| 4/5 — Mitigaciones potenciales | Validación de datos de entrada / truncar la entrada | `fixed_login.c`, `fixed_apellido.c` |

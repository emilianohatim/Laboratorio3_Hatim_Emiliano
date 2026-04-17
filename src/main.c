#include <stdint.h>
#include "alumno.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "config.h"

#define apellido  "Hatim"
#define nombre    "Emiliano"
#define documento 44028377

int main() {
    // alumno_t alumno = AlumnoCrear(apellido, nombre, documento);
    alumno_t alumno = AlumnoCrear_Allocate(apellido, nombre, documento);
    char resultado[256];
    if (AlumnoSerializar(alumno, resultado, sizeof(resultado)) != -1) {
        printf("JSON \n%s\n", resultado);
    } else {
        printf("el buffer es demasiado chico\n");
    }
    return 0;
}
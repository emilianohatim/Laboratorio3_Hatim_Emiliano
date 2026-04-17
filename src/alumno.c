#include <stdint.h>
#include "alumno.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

struct alumno {
    char nombre[32];
    char apellido[32];
    uint32_t documento;
    bool ocupado;
};

alumno_t AlumnoCrear_Allocate(char * apellido, char * nombre, uint32_t documento) {
    static struct alumno instancias[MAX_INSTANCIAS_ALUMNOS] = {0};
    alumno_t result = NULL;
    for (int i = 0; i < MAX_INSTANCIAS_ALUMNOS; i++) {
        if (!instancias[i].ocupado) {
            instancias[i].ocupado = true;
            strncpy(instancias[i].apellido, apellido, sizeof(instancias[i].apellido) - 1);
            instancias[i].apellido[sizeof(instancias[i].apellido) - 1] = '\0';
            strncpy(instancias[i].nombre, nombre, sizeof(instancias[i].nombre) - 1);
            instancias[i].nombre[sizeof(instancias[i].nombre) - 1] = '\0';
            instancias[i].documento = documento;
            result = &instancias[i];
            break;
        }
    }
    return result;
}

alumno_t AlumnoCrear(char * apellido, char * nombre, uint32_t documento) {
    alumno_t self = malloc(sizeof(struct alumno));
    if (self != NULL) {
        strncpy(self->apellido, apellido, sizeof(self->apellido) - 1);
        self->apellido[sizeof(self->apellido) - 1] = '\0';
        strncpy(self->nombre, nombre, sizeof(self->nombre) - 1);
        self->nombre[sizeof(self->nombre) - 1] = '\0';
        self->documento = documento;
    };
    return self;
}

static void SerializarCampoNumerico(uint32_t numero, char * cadena) {
    char * destino = cadena + strlen(cadena);
    if (numero == 0) {
        *destino++ = '0';
        *destino = '\0';
        return;
    }
    char longitud[11]; // porque uint32_t llega hasta 10 digitos + fin de linea
    int i = 0;
    while (numero > 0) {                     // extraigo digitos de atras hacia adelante
        longitud[i++] = (numero % 10) + '0'; // convierto digito en caracter ASCII
        numero /= 10;
    }
    int j = 0;
    while (i > 0) { // invierto cadena para que quede al derecho
        *destino++ = longitud[--i];
    }
    *destino = '\0';
}

static void SerializarCampoDeTexto(char * origen, char * palabra) {
    char * destino = origen + strlen(origen);      // posicionamiento al final de la cadena de caracteres
    while (*palabra != '\0') {                     // recorro caracter por caracter
        if (*palabra == '"' || *palabra == '\\') { // detecto caracteres como " o \.
            *destino = '\\';
            destino++;
        }
        *destino = *palabra;
        destino++;
        palabra++; // copio el caracter original
    }
    *destino = '\0';
}

int AlumnoSerializar(alumno_t alumno, char * resultado, size_t tamaño) {
    if (alumno == NULL || resultado == NULL) {
        return -1;
    }
    resultado[0] = '\0';
    strcat(resultado, "{\"Apellido\":\"");
    SerializarCampoDeTexto(resultado, alumno->apellido);
    strcat(resultado, "\",\"Nombre\":\"");
    SerializarCampoDeTexto(resultado, alumno->nombre);
    strcat(resultado, "\",\"Documento\":");
    SerializarCampoNumerico(alumno->documento, resultado);
    strcat(resultado, "}");
    if (strlen(resultado) >= (size_t)tamaño) {
        return -1;
    }
    return (int)strlen(resultado);
}

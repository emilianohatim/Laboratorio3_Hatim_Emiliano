/*********************************************************************************************************************
Copyright 2016-2025, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnologia
Universidad Nacional de Tucuman
http://www.microprocesadores.unt.edu.ar/

Copyright 2016-2026, Emiliano Hatim <emilianohatim01@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/**
 * @file alumno.c
 * @author Hatim Emiliano (emilianohatim01@gmail.com)
 * @brief Archivo alumno.c
 * @version 0.1
 * @date 2026-04-10
 *
 * @copyright Copyright (c) 2026
 *
 */

/* === Headers files inclusions ================================================================ */

#include <stdint.h>
#include "alumno.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/**
 * @brief Estructura para representar a un alumno
 * @param nombre nombre del alumno
 * @param apellido apellido del alumno
 * @param documento número de documento del alumno
 * @param ocupado bandera para indicar si la instancia está ocupada (solo para AlumnoCrear_Allocate)
 */

struct alumno {
    char nombre[32];
    char apellido[32];
    uint32_t documento;
    bool ocupado;
};

/* === Private function declarations =========================================================== */

/* === Private variable definitions ============================================================ */

/* === Public variable definition  ============================================================= */

/* === Private function definitions ============================================================ */

/**
 * @brief Serializa un campo numérico en una cadena de caracteres
 *
 * @param numero Valor numérico que se convierte en texto
 * @param cadena Puntero al buffer de destino donde se concatenará el número serializado
 * @return void
 */

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

/**
 * @brief Serializa un campo de texto en una cadena de caracteres
 *
 * @param origen Puntero al buffer de destino donde se escribirá el texto serializado
 * @param palabra Puntero a la cadena de caracteres original que se desea copiar
 * @return void
 */

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

/* === Public function implementations ============================================================= */

/**
 * @brief Crea una instancia de alumno utilizando asignación estática
 *
 * @param apellido Cadena de caracteres con el apellido del alumno
 * @param nombre Cadena de caracteres con el nomre del alumno
 * @param documento Número de documento de identidad del alumno
 * @return alumno_t Puntero a la instancia del alumno creado, o NULL si no hay espacio disponible
 */

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

/**
 * @brief Crea una instancia de alumno utilizando asignación dinámica
 *
 * @param apellido Cadena de caracteres con el apellido del alumno
 * @param nombre Cadena de caracteres con el nomre del alumno
 * @param documento Número de documento de identidad del alumno
 * @return alumno_t Puntero a la instancia del alumno creado, o NULL si no hay espacio disponible
 */

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

/**
 * @brief Serializa una instancia de alumno en una cadena de caracteres
 *
 * @param alumno Puntero a la estructura con los datos del alumno
 * @param resultado Puntero al buffer donde se guardará la cadena resultante en formato JSON
 * @param tamaño Tamaño máximo disponible en el buffer apuntado por 'resultado'
 * @return int el tamaño de la cadena resultante, o -1 si el buffer es demasiado chico
 *
 */

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

/* === End of documentation ==================================================================== */

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
 * @file main.c
 * @author Emiliano Hatim (emilianohatim01@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-04-17
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
#include <stdio.h>
#include "config.h"

/* === Macros definitions ====================================================================== */

#define apellido  "Hatim"
#define nombre    "Emiliano"
#define documento 44028377

/* === Private data type declarations ========================================================== */

/* === Private function declarations =========================================================== */

/* === Private variable definitions ============================================================ */

/* === Public variable definition  ============================================================= */

/* === Private function definitions ============================================================ */

/* === Public function implementation ========================================================== */

/**
 * @brief
 *
 * Si se quiere utilizar una funcion que emplea memoria dinamica, escriba "//" a la izquierda de la linea alumno_t
 * alumno = AlumnoCrear_Allocate(apellido, nombre, documento); y elimine el "//" que se encunetra a la izquierda de la
 * linea alumno_t alumno = AlumnoCrear(apellido, nombre, documento);
 *
 * Si se quiere utilizar una funcion que emplea memoria estática, escriba "//" a la izquierda de la linea alumno_t
 * alumno = AlumnoCrear(apellido, nombre, documento); y elimine el "//" que se encunetra a la izquierda de la linea
 * alumno_t alumno = AlumnoCrear_Allocate(apellido, nombre, documento);
 *
 * @return int Imprime el JSON resultante o un mensaje de error si el buffer es demasiado chico
 */

int main() {
    alumno_t alumno = AlumnoCrear(apellido, nombre, documento);
    // alumno_t alumno = AlumnoCrear_Allocate(apellido, nombre, documento);
    char resultado[256];
    if (AlumnoSerializar(alumno, resultado, sizeof(resultado)) != -1) {
        printf("JSON \n%s\n", resultado);
    } else {
        printf("el buffer es demasiado chico\n");
    }
    return 0;
}

/* === End of documentation ==================================================================== */

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

#ifndef ALUMNO_H
#define ALUMNO_H

/**
 * @file alumno.h
 * @author Emiliano Hatim (emilianohatim01@gmail.com)
 * @brief Definición de la estructura y funciones para manejar datos de un alumno
 * @version 1.0
 *
 * @date 2024-06
 * @copyright Copyright (c) 2026
 */

/* === Headers files inclusions ==================================================================================== */

#include <stdint.h>
#include <stddef.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/**
 * @brief Estructura para representar a un alumno
 */

typedef struct alumno * alumno_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Declaración de las funciones para crear un alumno y serializarlo a JSON
 *
 */

alumno_t AlumnoCrear_Allocate(char * apellido, char * nombre, uint32_t documento);
alumno_t AlumnoCrear(char * apellido, char * nombre, uint32_t documento);
int AlumnoSerializar(alumno_t datos, char * resultado, size_t tamaño);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif

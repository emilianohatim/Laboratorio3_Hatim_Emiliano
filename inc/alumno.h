#ifndef ALUMNO_H
#define ALUMNO_H

typedef struct alumno * alumno_t;

alumno_t AlumnoCrear_Allocate(char * apellido, char * nombre, uint32_t documento);
alumno_t AlumnoCrear(char * apellido, char * nombre, uint32_t documento);
int AlumnoSerializar(alumno_t datos, char * resultado, size_t tamaño);

#endif

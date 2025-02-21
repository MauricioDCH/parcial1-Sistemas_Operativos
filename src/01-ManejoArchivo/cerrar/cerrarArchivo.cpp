// Archivo: cerrarArchivo.cpp

#include <unistd.h>         // Para usar close()

#include "cerrarArchivo.h"

void CerrarArchivo::cerrarArchivo(int file_descriptor, std::string nombre_archivo){
    write(STDOUT_FILENO, "\nSECCIÓN DE CERRAR EL ARCHIVO...\n", 35);
    char buffer_salida[1024];
    int length_formateo_salida = snprintf(buffer_salida, sizeof(buffer_salida), "El archivo '%s' se cerró correctamente: \n",
                                nombre_archivo.c_str());
    write(STDOUT_FILENO, buffer_salida, length_formateo_salida);
    close(file_descriptor);
}
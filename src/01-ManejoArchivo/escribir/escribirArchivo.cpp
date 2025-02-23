// Archivo: escribirArchivo.cpp

#include "escribirArchivo.h"

int EscribirArchivo::escribirArchivo(int fileDescriptorSalida, std::vector<uint8_t> datos, std::string& nombre_archivo_entrada) {
    write(STDOUT_FILENO, "\nSECCIÓN DE ESCRITURA DE ARCHIVO...\n", 37);
    // Escribir los datos en el archivo de salida
    ssize_t bytes_escritos = write(fileDescriptorSalida, datos.data(), datos.size());
    if (bytes_escritos == -1) {
        write(STDERR_FILENO, "Error al escribir en el archivo\n", 32);
    } else {
        char buffer_nombre_archivo[256];
    int length_buffer_nombre_archivo = snprintf(buffer_nombre_archivo, sizeof(buffer_nombre_archivo), "Datos escritos correctamente en: %s\n", nombre_archivo_entrada.c_str());
    write(STDOUT_FILENO, buffer_nombre_archivo, length_buffer_nombre_archivo);
    }
    return fileDescriptorSalida;
}
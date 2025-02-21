// Archivo: leerArchivo.cpp

#include "leerArchivo.h"

VectFD LeerArchivo::leerArchivo(int fileDescriptor, std::string& nombre_archivo_entrada) {
    VectFD vectorAndFD;
    vectorAndFD.fileDescriptor = fileDescriptor;
    std::string nombre_archivo = nombre_archivo_entrada;
    char buffer_nombre_archivo[256];
    int length_buffer_nombre_archivo = snprintf(buffer_nombre_archivo, sizeof(buffer_nombre_archivo), "Contenido del archivo: %s\n", nombre_archivo.c_str());

    write(STDOUT_FILENO, "\nSECCIÓN DE LECTURA DEL ARCHIVO...\n", 36);
    
    if (fileDescriptor == -1) {
        write(STDERR_FILENO, "Error al abrir el archivo\n", 26);
        return vectorAndFD;         // Retornar struct vacío con FD inválido
    }

    write(STDOUT_FILENO, "Archivo abierto correctamente.\n", 31);

    vectorAndFD.datos.clear();      // Limpiamos el vector antes de leer nuevos datos
    uint8_t buffer[1024];           // Buffer temporal de 1024 bytes
    ssize_t bytesLeidos;

    // `read(fd, buffer, sizeof(buffer))` lee el archivo en bloques de 1024 bytes
    while ((bytesLeidos = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
        vectorAndFD.datos.insert(vectorAndFD.datos.end(), buffer, buffer + bytesLeidos);  // Almacena los bytes en `datos`
    }

    // Mostrar el contenido del archivo
    //write(STDOUT_FILENO, "Contenido del archivo:\n", 23);
    write(STDOUT_FILENO, buffer_nombre_archivo, length_buffer_nombre_archivo);
    write(STDOUT_FILENO, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", 146);
    write(STDOUT_FILENO, "                                                                   INICIO DEL ARCHIVO                                                           \n", 145);
    write(STDOUT_FILENO, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n\n", 146);
    for (uint8_t byte : vectorAndFD.datos) {
        write(STDOUT_FILENO, &byte, 1);
    }
    write(STDOUT_FILENO, "\n\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", 146);
    write(STDOUT_FILENO, "\n                                                                    FIN DEL ARCHIVO                                                          \n", 144);
    write(STDOUT_FILENO, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", 146);
    return vectorAndFD;
}

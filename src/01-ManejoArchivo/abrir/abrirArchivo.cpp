// Archivo: abrirArchivo.cpp

#include "abrirArchivo.h"

int AbrirArchivo::abrirArchivoParaLectura(std::string& nombre_archivo_entrada){
    write(STDOUT_FILENO, "\nSECCIÓN DE ABRIR EL ARCHIVO PARA LECTURA...\n", 46);
    int fileDescriptor = open(nombre_archivo_entrada.c_str(), O_RDONLY);
    if(fileDescriptor == -1){
        write(STDERR_FILENO, "Error al abrir el archivo\n", 26);
        return -1;
    }
    write(STDOUT_FILENO, "Archivo abierto correctamente\n", 31);

    char buffer_salida[1024];
    int length_formateo_salida = snprintf(buffer_salida, sizeof(buffer_salida), "FileDescriptor: %d\nRuta y nombre del archivo abierto: %s\n\n",
                                fileDescriptor, nombre_archivo_entrada.c_str());
    // En caso de errores.
    if (length_formateo_salida < 0) {
        const char* error_msg = "Error en snprintf\n";
        write(STDOUT_FILENO, error_msg, strlen(error_msg));
        return -1;
    }
    write(STDOUT_FILENO, buffer_salida, length_formateo_salida);

    return fileDescriptor;
}

int AbrirArchivo::abrirArchivoParaEscritura(std::string& nombre_archivo_salida){
    write(STDOUT_FILENO, "SECCIÓN DE ABRIR EL ARCHIVO PARA ESCRITURA...\n", 47);
    // `open()` abre el archivo para escritura (creándolo si no existe)
    // `O_WRONLY` → Solo escritura
    // `O_CREAT` → Crea el archivo si no existe
    // `O_TRUNC` → Si el archivo existe, lo sobreescribe
    // `0644` → Permisos de lectura/escritura para el dueño, lectura para otros
    //int fileDescriptor = open(nombre_archivo_salida.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fileDescriptor = open(nombre_archivo_salida.c_str(), O_WRONLY | O_CREAT, 0644);
    if(fileDescriptor == -1){
        write(STDERR_FILENO, "Error al abrir el archivo\n", 26);
        return -1;
    }
    write(STDOUT_FILENO, "Archivo abierto correctamente\n", 31);

    char buffer_salida[1024];
    int length_formateo_salida = snprintf(buffer_salida, sizeof(buffer_salida), "FileDescriptor: %d\nRuta y nombre del archivo abierto: %s\n\n",
                                fileDescriptor, nombre_archivo_salida.c_str());
    // En caso de errores.
    if (length_formateo_salida < 0) {
        const char* error_msg = "Error en snprintf\n";
        write(STDOUT_FILENO, error_msg, strlen(error_msg));
        return -1;
    }
    write(STDOUT_FILENO, buffer_salida, length_formateo_salida);

    return fileDescriptor;
}
// Archivo: abrirArchivo.h

#ifndef ABRIR_ARCHIVO_H
#define ABRIR_ARCHIVO_H

#include <unistd.h>     // Para usar write
#include <fcntl.h>      // Para usar open
#include <string>       // Para usar string
#include <string.h>     // Para strlen()

class AbrirArchivo{
    private:
        std::string nombre_archivo_entrada;
        std::string nombre_archivo_salida;
    public:
        int abrirArchivoParaLectura(std::string& nombre_archivo_entrada);
        int abrirArchivoParaEscritura(std::string& nombre_archivo_salida);
};

#endif
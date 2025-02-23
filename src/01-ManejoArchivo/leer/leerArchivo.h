// Archivo: leerArchivo.h

#ifndef LEER_ARCHIVO_H
#define LEER_ARCHIVO_H

#include <unistd.h>    // Para usar `read()`, `write()`
#include <fcntl.h> // Para usar open
#include <vector>      // Para usar std::vector
#include <cstdint>     // Para usar tipos de datos de tamaño fijo como uint8_t
#include <string>
#include "../../04-Utils/vectorFD.h"

class LeerArchivo{
    public:
        VectFD leerArchivo(int fileDescriptor, std::string& nombre_archivo_entrada);
};

#endif
// Archivo: escribirArchivo.h

#ifndef ESCRIBIR_ARCHIVO_H
#define ESCRIBIR_ARCHIVO_H

#include <unistd.h>     // Para usar `read()`, `write()`
#include <fcntl.h>      // Para usar open
#include <vector>       // Para usar std::vector
#include <string>       // Para usar string
#include <string.h>     // Para strlen()
#include <cstdint>      // Para usar tipos de datos de tamaño fijo como uint8_t
#include <bitset>       // Para representar cada byte en su forma binaria (8 bits)

struct Data_and_Bits{
    std::vector<uint8_t> datos;  // Vector para almacenar el contenido del archivo en bytes
    std::vector<std::string> bits; // Vector para almacenar la representación en bits de cada byte
};


class EscribirArchivo{
    public:
        int escribirArchivo(int fileDescriptor, std::vector<uint8_t> datos, std::string& nombre_archivo_entrada);
};

#endif
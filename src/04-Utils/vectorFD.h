#ifndef VECTFD_H
#define VECTFD_H

#include <vector>
#include <cstdint>

struct VectFD {
    int fileDescriptor;
    std::vector<uint8_t> datos;  // Vector para almacenar el contenido del archivo en bytes
};

struct VectFD_Original_Encriptado{
    int fileDescriptor_Original;
    std::vector<uint8_t> datos_Original;
    int fileDescriptor_Encriptado;
    std::vector<uint8_t> datos_Encriptado;
};

struct VectFD_Encriptado_Desencriptado{
    int fileDescriptor_Encriptado;
    std::vector<uint8_t> datos_Encriptado;
    int fileDescriptor_Desencriptado;
    std::vector<uint8_t> datos_Desencriptado;
};

#endif

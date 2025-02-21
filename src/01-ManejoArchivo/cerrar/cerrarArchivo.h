// Archivo: cerrarArchivo.h

#ifndef CERRAR_ARCHIVO_H
#define CERRAR_ARCHIVO_H
#include <string>
class CerrarArchivo{
    private:
        int fd;
    public:
        void cerrarArchivo(int file_descriptor, std::string nombre_archivo);
};

#endif
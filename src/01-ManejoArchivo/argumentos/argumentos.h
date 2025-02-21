// Archivo: argumentos.h

#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

#include <unistd.h>     // Para usar write
#include <cstdio>       // Para snprintf

class MostrarArgumentos{
    public:
        void mostrarComandos(char* argv[]);
};

#endif
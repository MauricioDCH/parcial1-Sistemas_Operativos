/* 
    Archivo: permutations_arrays-substitutions_boxes.h
    Archivo obtenido de: https://www.schneier.com/wp-content/uploads/2015/12/constants-2.txt
*/ 

#ifndef PERMUTACIONES_SUSTITUCIONES_H
#define PERMUTACIONES_SUSTITUCIONES_H

#include <array>
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>    // Para usar `read()`, `write()`
#include <sys/stat.h>
#include <cstring>
#include "../04-Utils/vectorFD.h"

#define NUMERO_DE_EJECUCIONES 16
#define NUMERO_DE_PERMUTACIONES 18
#define NUMERO_DE_CAJAS 4
#define NUMERO_DE_ELEMENTOS_POR_CAJA 256

using DWORD = uint32_t;
#define WORD unsigned short
#define BYTE unsigned char

extern const std::array<DWORD, NUMERO_DE_PERMUTACIONES> BLOWFISH_PERMUTATIONS_ARRAY;
extern const std::array<std::array<DWORD, NUMERO_DE_ELEMENTOS_POR_CAJA>, NUMERO_DE_CAJAS>BLOWFISH_SUBSTITUTIONS_BOXES;
#endif
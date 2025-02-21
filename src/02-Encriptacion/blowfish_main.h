// Archivo: blowfish_main.h

#ifndef BLOWFISH_MAIN_H
#define BLOWFISH_MAIN_H

#include "permutations_arrays-substitutions_boxes.h"

#define MAXIMO_NUMERO_DE_BYTES_DE_CLAVE 56  // 56 Bytes --> 448 bits

// Little Endian (Intel).
struct ByteStruct{
    unsigned int byte3:8;
    unsigned int byte2:8;
    unsigned int byte1:8;
    unsigned int byte0:8;
};

union Word {
    DWORD dword;
    ByteStruct bytes;
};
extern Word converter; 

class BlowFish_Algoritmo{
    private:
        std::array<DWORD, NUMERO_DE_PERMUTACIONES> PermutationsArray = BLOWFISH_PERMUTATIONS_ARRAY;
        std::array<std::array<DWORD, NUMERO_DE_ELEMENTOS_POR_CAJA>, NUMERO_DE_CAJAS> SubstitutionBoxes = BLOWFISH_SUBSTITUTIONS_BOXES;
        void XORClaveConPermutaciones(const std::string &clave);
        
    public:
        void Blowfish_encriptador_por_bloque(DWORD& sub_bloque_lado_izquierdo, DWORD& sub_bloque_lado_derecho);
        void Blowfish_desencriptador_por_bloque(DWORD& sub_bloque_lado_izquierdo, DWORD& sub_bloque_lado_derecho);
        BlowFish_Algoritmo();
        DWORD Funcion_f(DWORD sub_bloque_lado_izquierdo);
        void Inicializacion_parametros_con_clave(const std::string &clave);
        //std::string Convertir_a_string(DWORD string_en_hexa);
        VectFD_Original_Encriptado EncriptarArchivo(const VectFD& datosEntrada, std::string clave, BlowFish_Algoritmo& blowfish);
        VectFD_Encriptado_Desencriptado DesencriptarArchivo(const VectFD& datosEntrada, BlowFish_Algoritmo& blowfish);
};
#endif

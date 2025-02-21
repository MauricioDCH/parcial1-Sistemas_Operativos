// Archivo: blowfish_main.cpp

#include "blowfish_main.h"

BlowFish_Algoritmo::BlowFish_Algoritmo() {
    PermutationsArray = BLOWFISH_PERMUTATIONS_ARRAY; 
    SubstitutionBoxes = BLOWFISH_SUBSTITUTIONS_BOXES;
}

DWORD BlowFish_Algoritmo::Funcion_f(DWORD sub_bloque_lado_izquierdo) {
    Word temporal_f;
    temporal_f.dword = sub_bloque_lado_izquierdo;
    
    DWORD resultado;
    resultado = SubstitutionBoxes[0][temporal_f.bytes.byte0] + SubstitutionBoxes[1][temporal_f.bytes.byte1];
    resultado ^= SubstitutionBoxes[2][temporal_f.bytes.byte2];
    resultado += SubstitutionBoxes[3][temporal_f.bytes.byte3];
    
    return resultado;
}

void BlowFish_Algoritmo::XORClaveConPermutaciones(const std::string &clave) {
    Word temporal_xor;
    DWORD index, j_index = 0, longitud_clave = clave.length();

    for (index = 0; index < NUMERO_DE_EJECUCIONES + 2; ++index) {
        temporal_xor.dword = 0;
        // Asigna cada byte directamente
        temporal_xor.bytes.byte0 = clave[j_index];
        temporal_xor.bytes.byte1 = clave[(j_index + 1) % longitud_clave];
        temporal_xor.bytes.byte2 = clave[(j_index + 2) % longitud_clave];
        temporal_xor.bytes.byte3 = clave[(j_index + 3) % longitud_clave];
        j_index = (j_index + 4) % longitud_clave;
        PermutationsArray[index] ^= temporal_xor.dword;
    }
}

void BlowFish_Algoritmo::Inicializacion_parametros_con_clave(const std::string &clave) {
    DWORD datos_lado_izquierdo, datos_lado_derecho, index, j_index;

    XORClaveConPermutaciones(clave);

    datos_lado_izquierdo = 0;
    datos_lado_derecho = 0;

    for (index = 0; index < NUMERO_DE_EJECUCIONES + 2; index += 2) {
        Blowfish_encriptador_por_bloque(datos_lado_izquierdo, datos_lado_derecho);
        PermutationsArray[index] = datos_lado_izquierdo;
        PermutationsArray[index + 1] = datos_lado_derecho;
    }

    for (index = 0; index < NUMERO_DE_CAJAS; ++index){
        for (j_index = 0; j_index < NUMERO_DE_ELEMENTOS_POR_CAJA; j_index += 2){
            Blowfish_encriptador_por_bloque(datos_lado_izquierdo, datos_lado_derecho);
            SubstitutionBoxes[index][j_index] = datos_lado_izquierdo;
            SubstitutionBoxes[index][j_index + 1] = datos_lado_derecho;
        }
    }
}

void BlowFish_Algoritmo::Blowfish_encriptador_por_bloque(DWORD& sub_bloque_lado_izquierdo, DWORD& sub_bloque_lado_derecho){
    DWORD Sub_bloque_lado_izquierdo, Sub_bloque_lado_derecho, index;

    Sub_bloque_lado_izquierdo = sub_bloque_lado_izquierdo;
    Sub_bloque_lado_derecho = sub_bloque_lado_derecho;

    for (index = 0; index < NUMERO_DE_EJECUCIONES; ++index) {
        Sub_bloque_lado_izquierdo ^= PermutationsArray[index];
        Sub_bloque_lado_derecho = Funcion_f(Sub_bloque_lado_izquierdo) ^ Sub_bloque_lado_derecho;
        std::swap(Sub_bloque_lado_izquierdo, Sub_bloque_lado_derecho);
    }
    sub_bloque_lado_derecho = Sub_bloque_lado_izquierdo;
    sub_bloque_lado_izquierdo = Sub_bloque_lado_derecho;

    std::swap(Sub_bloque_lado_izquierdo, Sub_bloque_lado_derecho);
    Sub_bloque_lado_derecho ^= PermutationsArray[NUMERO_DE_EJECUCIONES];
    Sub_bloque_lado_izquierdo ^= PermutationsArray[NUMERO_DE_EJECUCIONES + 1];
    sub_bloque_lado_izquierdo = Sub_bloque_lado_izquierdo;
    sub_bloque_lado_derecho = Sub_bloque_lado_derecho;
}

void BlowFish_Algoritmo::Blowfish_desencriptador_por_bloque(DWORD& sub_bloque_lado_izquierdo, DWORD& sub_bloque_lado_derecho){
    DWORD Sub_bloque_lado_izquierdo, Sub_bloque_lado_derecho, index;

    Sub_bloque_lado_izquierdo = sub_bloque_lado_izquierdo;
    Sub_bloque_lado_derecho = sub_bloque_lado_derecho;

    for (index = (NUMERO_DE_EJECUCIONES + 1); index > 1; --index) {
        Sub_bloque_lado_izquierdo ^= PermutationsArray[index];
        Sub_bloque_lado_derecho = Funcion_f(Sub_bloque_lado_izquierdo) ^ Sub_bloque_lado_derecho;
        std::swap(Sub_bloque_lado_izquierdo, Sub_bloque_lado_derecho);
    }
    sub_bloque_lado_derecho = Sub_bloque_lado_izquierdo;
    sub_bloque_lado_izquierdo = Sub_bloque_lado_derecho;

    std::swap(Sub_bloque_lado_izquierdo, Sub_bloque_lado_derecho);
    Sub_bloque_lado_derecho ^= PermutationsArray[1];
    Sub_bloque_lado_izquierdo ^= PermutationsArray[0];
    sub_bloque_lado_izquierdo = Sub_bloque_lado_izquierdo;
    sub_bloque_lado_derecho = Sub_bloque_lado_derecho;
}

VectFD_Original_Encriptado BlowFish_Algoritmo::EncriptarArchivo(const VectFD& datosEntrada, std::string clave, BlowFish_Algoritmo& blowfish) {
    VectFD_Original_Encriptado vector_fd_original_encriptado;
    Inicializacion_parametros_con_clave(clave);

    vector_fd_original_encriptado.fileDescriptor_Original = datosEntrada.fileDescriptor;
    vector_fd_original_encriptado.datos_Original = datosEntrada.datos;

    size_t tamano_original = datosEntrada.datos.size();

    // Guardamos el tamaño original en el vector de datos encriptados
    vector_fd_original_encriptado.datos_Encriptado.resize(sizeof(size_t));
    std::memcpy(vector_fd_original_encriptado.datos_Encriptado.data(), &tamano_original, sizeof(size_t));

    DWORD lado_izquierdo, lado_derecho;
    size_t total_bytes = datosEntrada.datos.size();
    size_t i = 0;

    // Procesar los datos en bloques de 8 bytes
    while (i < total_bytes) {
        char buffer[8] = {0}; // Bloque de 64 bits (8 bytes), inicializado en 0
        size_t bytes_a_procesar = std::min(size_t(8), total_bytes - i);

        std::memcpy(buffer, &datosEntrada.datos[i], bytes_a_procesar);

        // Convertir los 8 bytes en dos DWORDs (uint32_t)
        lado_izquierdo = *reinterpret_cast<DWORD *>(buffer);
        lado_derecho = *reinterpret_cast<DWORD *>(buffer + 4);

        // Encriptar el bloque
        blowfish.Blowfish_encriptador_por_bloque(lado_izquierdo, lado_derecho);

        // Agregar los datos encriptados al vector
        uint8_t encrypted_block[8];
        std::memcpy(encrypted_block, &lado_izquierdo, sizeof(DWORD));
        std::memcpy(encrypted_block + 4, &lado_derecho, sizeof(DWORD));

        vector_fd_original_encriptado.datos_Encriptado.insert(
            vector_fd_original_encriptado.datos_Encriptado.end(), encrypted_block, encrypted_block + 8);

        i += 8;
    }

    return vector_fd_original_encriptado;
}

VectFD_Encriptado_Desencriptado BlowFish_Algoritmo::DesencriptarArchivo(const VectFD& datos_encriptado, BlowFish_Algoritmo& blowfish) {
    VectFD_Encriptado_Desencriptado vector_fd_encriptado_desencriptado;
    vector_fd_encriptado_desencriptado.fileDescriptor_Encriptado = datos_encriptado.fileDescriptor;

    if (datos_encriptado.datos.empty()) {
        std::cerr << "Error: No hay datos encriptados para desencriptar." << std::endl;
        return vector_fd_encriptado_desencriptado;
    }

    size_t tamano_original;
    std::memcpy(&tamano_original, datos_encriptado.datos.data(), sizeof(size_t));

    if (tamano_original > datos_encriptado.datos.size() - sizeof(size_t)) {
        write(STDERR_FILENO, "Error: Tamaño de datos incorrecto\n", 35);
        return vector_fd_encriptado_desencriptado;
    }

    DWORD lado_izquierdo, lado_derecho;
    std::vector<uint8_t> buffer;

    // Procesar los datos en bloques de 8 bytes
    size_t i = sizeof(size_t); // Saltamos los primeros bytes que almacenan el tamaño original
    while (i + 8 <= datos_encriptado.datos.size()) { 
        // Leer los 8 bytes encriptados
        std::memcpy(&lado_izquierdo, &datos_encriptado.datos[i], sizeof(DWORD));
        std::memcpy(&lado_derecho, &datos_encriptado.datos[i + 4], sizeof(DWORD));

        // Desencriptar el bloque
        blowfish.Blowfish_desencriptador_por_bloque(lado_izquierdo, lado_derecho);

        // Guardar en buffer
        buffer.insert(buffer.end(),
                      reinterpret_cast<uint8_t*>(&lado_izquierdo),
                      reinterpret_cast<uint8_t*>(&lado_izquierdo) + sizeof(DWORD));
        buffer.insert(buffer.end(),
                      reinterpret_cast<uint8_t*>(&lado_derecho),
                      reinterpret_cast<uint8_t*>(&lado_derecho) + sizeof(DWORD));

        i += 8;
    }

    buffer.resize(tamano_original);
    vector_fd_encriptado_desencriptado.datos_Desencriptado = buffer;

    return vector_fd_encriptado_desencriptado;
}

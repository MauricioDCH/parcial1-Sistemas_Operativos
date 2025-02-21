// Archivo: escribirArchivo.cpp

#include "escribirArchivo.h"
/*
Data_and_Bits EscribirArchivo::convertirABits(std::vector<uint8_t> datos_desde_archivo) {
    Data_and_Bits datos_con_bits;
    datos_con_bits.datos = datos_desde_archivo;
    datos_con_bits.bits.clear();  // Limpiar el vector de bits

    for (uint8_t byte : datos_con_bits.datos) {
        datos_con_bits.bits.push_back(std::bitset<8>(byte).to_string());  // Convierte cada byte a 8 bits
    }

    return datos_con_bits;
}

void EscribirArchivo::mostrarDatosEnBits(Data_and_Bits datos_y_bits) {
    write(STDOUT_FILENO, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", 146);
    write(STDOUT_FILENO, "N° ASCII -> BITS:\n", 20);
    char buffer[256];  // Buffer temporal para cada línea de salida
    size_t len;

    for (size_t i = 0; i < datos_y_bits.datos.size(); ++i) {
        len = snprintf(buffer, sizeof(buffer), "%d -> %s\n", datos_y_bits.datos[i], datos_y_bits.bits[i].c_str());
        write(STDOUT_FILENO, buffer, len);
    }
    write(STDOUT_FILENO, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", 146);
}

std::vector<std::vector<int>> EscribirArchivo::matrizBits(std::vector<uint8_t> datos_desde_archivo) {
    std::vector<std::vector<int>> matriz;

    for (uint8_t byte : datos_desde_archivo) {
        std::vector<int> filaBits(8);
        for (int i = 7; i >= 0; --i) {
            filaBits[7 - i] = (byte >> i) & 1; // Extrae cada bit del byte || FORMA MÁS RÁPIDA DE MULTIPLICAR O DIVIDIR POR 2.
        }
        //Tengo                   4 en byte = 00000100
        //Para tener 8, sería un sólo <<  4 = 00001000
        //Para tener 2, sería un sólo >>  2 = 00000010
        //Para tener 1, sería un sólo >>  1 = 00000001
        
        matriz.push_back(filaBits);
    }
    
    return matriz;
}

void EscribirArchivo::mostrarMatriz(std::vector<std::vector<int>> matriz){
    int tamano = matriz.size();
    int indice = 0;
    char buffer[256];  // Buffer temporal para cada línea de salida
    int len_mostrar_matriz = snprintf(buffer, sizeof(buffer), "\nMatriz de bits del archivo:\n Tamaño lista: %d\n", tamano);
    write(STDOUT_FILENO, buffer, len_mostrar_matriz);
    // Por el profesor.
    for (const auto& letra : matriz) {
        int len = snprintf(buffer, sizeof(buffer), "[%d/%d] ", indice, tamano - 1);
        write(STDOUT_FILENO, buffer, len);
        for (int bit : letra) 
            write(STDOUT_FILENO, std::to_string(bit).c_str(), 1);
        indice++;
        write(STDOUT_FILENO, "\n", 1);
    }
    write(STDOUT_FILENO, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n", 146);
}
*/
int EscribirArchivo::escribirArchivo(int fileDescriptorSalida, std::vector<uint8_t> datos, std::string& nombre_archivo_entrada) {
    write(STDOUT_FILENO, "\nSECCIÓN DE ESCRITURA DE ARCHIVO...\n", 37);
    // Escribir los datos en el archivo de salida
    ssize_t bytes_escritos = write(fileDescriptorSalida, datos.data(), datos.size());
    if (bytes_escritos == -1) {
        write(STDERR_FILENO, "Error al escribir en el archivo\n", 32);
    } else {
        char buffer_nombre_archivo[256];
    int length_buffer_nombre_archivo = snprintf(buffer_nombre_archivo, sizeof(buffer_nombre_archivo), "Datos escritos correctamente en: %s\n", nombre_archivo_entrada.c_str());
    write(STDOUT_FILENO, buffer_nombre_archivo, length_buffer_nombre_archivo);
    }
    return fileDescriptorSalida;
}
// Archivo: main.cpp

//#include <iostream> 
#include <fcntl.h>  // Para las constantes O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC
#include <cstdio>   // Para snprintf
#include <unistd.h> // Para write()
#include <iostream>

#include "01-ManejoArchivo/abrir/abrirArchivo.h"
#include "01-ManejoArchivo/cerrar/cerrarArchivo.h"
#include "01-ManejoArchivo/leer/leerArchivo.h"
#include "01-ManejoArchivo/escribir/escribirArchivo.h"
#include "01-ManejoArchivo/argumentos/argumentos.h"
#include "02-Encriptacion/blowfish_main.h"
#include "04-Utils/vectorFD.h"


int main(int argc, char* argv[]) {
    MostrarArgumentos mostrarArgumentos;
    char buffer_op_invalida[256];
    int length_formateo_op_invalida = snprintf(buffer_op_invalida, sizeof(buffer_op_invalida), "Opción no válida.\nDigita: '%s -h' o '%s --help' para verificar los comandos disponibles.\n", argv[0], argv[0]);
    
    // ---------------------------------------------------------------------------------------------------------------------------------
    // INICIALIZACIÓN DE STRUCTS.
    VectFD vector_fd_original, vector_fd_encriptado, vector_fd_desencriptado;
    VectFD_Original_Encriptado vector_fd_original_encriptado;
    VectFD_Encriptado_Desencriptado vector_fd_encriptado_desencriptado;
    Data_and_Bits datos_y_bits_originales;
    BlowFish_Algoritmo blowfish;

    // ---------------------------------------------------------------------------------------------------------------------------------
    // IMPORTACIÓN DE CLASES.
    AbrirArchivo abrirArchivo;
    CerrarArchivo cerrarArchivo;
    LeerArchivo leerArchivo;
    EscribirArchivo escribirArchivo;
    // ---------------------------------------------------------------------------------------------------------------------------------

    // Si los argumentos son 1 o mayor a 3, imprimir el uso correcto del programa
    if (argc == 1 || argc > 3) {
        mostrarArgumentos.mostrarComandos(argv);
        return 1;
    }
    // Si los argumentos son 2 o 3, verificar si la opción es válida
    else if (argc == 2)
    {
        if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
            mostrarArgumentos.mostrarComandos(argv);
        }
        else if (std::string(argv[1]) == "--version" || std::string(argv[1]) == "-v") {
            write(STDOUT_FILENO, "Versión 1.0\n", 13);
        }
        else {
            write(STDOUT_FILENO, buffer_op_invalida, length_formateo_op_invalida);
        }
    }
    else if (argc == 3){
        std::string nombre_archivo_entrada = argv[2];

size_t pos = nombre_archivo_entrada.find_last_of('.');
std::string nombre = nombre_archivo_entrada.substr(0, pos);
std::string extension = (pos != std::string::npos) ? nombre_archivo_entrada.substr(pos + 1) : "";

std::string clave = "f57jWa%$2s|Dc5$!";

if(std::string(argv[1]) == "--encrypt" || std::string(argv[1]) == "-e") {
    write(STDOUT_FILENO, "Encriptar\n", 10);

    std::string nombre_archivo_encriptado = nombre_archivo_entrada + ".encrypt";
    vector_fd_original.fileDescriptor = abrirArchivo.abrirArchivoParaLectura(nombre_archivo_entrada);
    vector_fd_encriptado.fileDescriptor = abrirArchivo.abrirArchivoParaEscritura(nombre_archivo_encriptado);

    vector_fd_original = leerArchivo.leerArchivo(vector_fd_original.fileDescriptor, nombre_archivo_entrada);

    // Encriptar
    vector_fd_original_encriptado = blowfish.EncriptarArchivo(vector_fd_original, clave, blowfish);
    vector_fd_original_encriptado.fileDescriptor_Encriptado = vector_fd_encriptado.fileDescriptor;

    int file_descriptor_salida_encriptado = escribirArchivo.escribirArchivo(
        vector_fd_original_encriptado.fileDescriptor_Encriptado,
        vector_fd_original_encriptado.datos_Encriptado,
        nombre_archivo_encriptado
    );

    // **Asignar correctamente los datos encriptados**
    vector_fd_encriptado.fileDescriptor = file_descriptor_salida_encriptado;
    vector_fd_encriptado.datos = vector_fd_original_encriptado.datos_Encriptado;

    cerrarArchivo.cerrarArchivo(vector_fd_original.fileDescriptor, nombre_archivo_entrada);
    cerrarArchivo.cerrarArchivo(file_descriptor_salida_encriptado, nombre_archivo_encriptado);
}
else if(std::string(argv[1]) == "--decrypt" || std::string(argv[1]) == "-d") {
    write(STDOUT_FILENO, "Desencriptar\n", 13);

    std::string nombre_archivo_desencriptado = nombre_archivo_entrada + "_decrypt." + extension;
    vector_fd_original.fileDescriptor = abrirArchivo.abrirArchivoParaLectura(nombre_archivo_entrada);
    vector_fd_desencriptado.fileDescriptor = abrirArchivo.abrirArchivoParaEscritura(nombre_archivo_desencriptado);

    vector_fd_original = leerArchivo.leerArchivo(vector_fd_original.fileDescriptor, nombre_archivo_entrada);

    // **Usar el archivo encriptado para la desencriptación**
    vector_fd_encriptado_desencriptado = blowfish.DesencriptarArchivo(vector_fd_encriptado, blowfish);
    vector_fd_encriptado_desencriptado.fileDescriptor_Desencriptado = vector_fd_desencriptado.fileDescriptor;

    int file_descriptor_salida_desencriptado = escribirArchivo.escribirArchivo(
        vector_fd_encriptado_desencriptado.fileDescriptor_Desencriptado,
        vector_fd_encriptado_desencriptado.datos_Desencriptado,
        nombre_archivo_desencriptado
    );

    cerrarArchivo.cerrarArchivo(vector_fd_original.fileDescriptor, nombre_archivo_entrada);
    cerrarArchivo.cerrarArchivo(file_descriptor_salida_desencriptado, nombre_archivo_desencriptado);
}
        return 0;
    }
}
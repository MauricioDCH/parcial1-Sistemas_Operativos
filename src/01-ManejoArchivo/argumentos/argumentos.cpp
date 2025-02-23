// Archivo: argumentos.cpp

#include "argumentos.h"

void MostrarArgumentos::mostrarComandos(char* argv[]){
    char buffer_uso1[256];
    char buffer_uso2[256];

    int length_formateo_uso1 = snprintf(buffer_uso1, sizeof(buffer_uso1), "Uso: \nCOMANDO 1 --> %s [OPCIÓN-1]\n", argv[0]);
    int length_formateo_uso2 = snprintf(buffer_uso2, sizeof(buffer_uso2), "COMANDO 2 --> %s [OPCIÓN-2] <archivo>\n\n", argv[0]);

    write(STDERR_FILENO, buffer_uso1, length_formateo_uso1);
    write(STDERR_FILENO, buffer_uso2, length_formateo_uso2);
    write(STDOUT_FILENO, "  [OPCIÓN-1]\n", 14);
    write(STDOUT_FILENO, "      -h, --help:  -----------------------------> Mostrar este mensaje de ayuda.\n", 82);
    write(STDOUT_FILENO, "      -v, --version:  --------------------------> Mostrar la versión del programa.\n\n", 86);
    write(STDOUT_FILENO, "  [OPCIÓN-2]\n", 14);
    write(STDOUT_FILENO, "      -e <archivo>, --encrypt <archivo>:  ------> Encriptar el archivo.\n", 73);
    write(STDOUT_FILENO, "      -d <archivo>, --decrypt <archivo>:  ------> Desencriptar el archivo\n", 75);
}
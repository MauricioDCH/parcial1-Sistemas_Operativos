# Definir el compilador y las banderas de compilación
CC = g++
CFLAGS = -Wall -std=c++17

# Nombre del ejecutable
EXEC = mdchApril

# Regla principal: compilar el ejecutable
all: cleanFilesdotO $(EXEC)

# Regla para crear el ejecutable
$(EXEC): main.o abrirArchivo.o cerrarArchivo.o leerArchivo.o \
		escribirArchivo.o argumentos.o \
		permutations_arrays-substitutions_boxes.o \
		blowfish_main.o
	$(CC) $(CFLAGS) -o $(EXEC) $^

# Reglas para compilar los archivos fuente en archivos objeto
main.o: main.cpp \
	01-ManejoArchivo/abrir/abrirArchivo.h \
	01-ManejoArchivo/cerrar/cerrarArchivo.h \
	01-ManejoArchivo/leer/leerArchivo.h \
	01-ManejoArchivo/escribir/escribirArchivo.h \
	01-ManejoArchivo/argumentos/argumentos.h \
	02-Encriptacion/permutations_arrays-substitutions_boxes.h \
	02-Encriptacion/blowfish_main.h \
	04-Utils/vectorFD.h
	$(CC) $(CFLAGS) -c $<

blowfish_main.o: 02-Encriptacion/blowfish_main.cpp \
				02-Encriptacion/blowfish_main.h \
				04-Utils/vectorFD.h
	$(CC) $(CFLAGS) -c $<

permutations_arrays-substitutions_boxes.o: \
		02-Encriptacion/permutations_arrays-substitutions_boxes.cpp \
		02-Encriptacion/permutations_arrays-substitutions_boxes.h
	$(CC) $(CFLAGS) -c $<

argumentos.o: 01-ManejoArchivo/argumentos/argumentos.cpp \
			01-ManejoArchivo/argumentos/argumentos.h
	$(CC) $(CFLAGS) -c $<

abrirArchivo.o: 01-ManejoArchivo/abrir/abrirArchivo.cpp \
				01-ManejoArchivo/abrir/abrirArchivo.h
	$(CC) $(CFLAGS) -c $<

cerrarArchivo.o: 01-ManejoArchivo/cerrar/cerrarArchivo.cpp \
				01-ManejoArchivo/cerrar/cerrarArchivo.h
	$(CC) $(CFLAGS) -c $<

leerArchivo.o: 01-ManejoArchivo/leer/leerArchivo.cpp \
			01-ManejoArchivo/leer/leerArchivo.h \
			04-Utils/vectorFD.h
	$(CC) $(CFLAGS) -c $<

escribirArchivo.o: 01-ManejoArchivo/escribir/escribirArchivo.cpp \
				01-ManejoArchivo/escribir/escribirArchivo.h
	$(CC) $(CFLAGS) -c $<

# Regla para limpiar los archivos compilados
cleanFilesdotO:
	rm -f $(EXEC) *.o

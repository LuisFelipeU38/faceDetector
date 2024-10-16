# Variables
CXX = g++
CXXFLAGS = -fopenmp -Wall -O2
OPENCV_FLAGS = `pkg-config --cflags --libs opencv4`

# Archivo ejecutable
EXEC = detect_faces
SRC = main.cpp
OBJ = main.o

# Regla principal
all: $(EXEC)

# Compilación del ejecutable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ) $(OPENCV_FLAGS)

# Compilación del archivo fuente
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) $(OPENCV_FLAGS)

# Limpiar los archivos compilados
clean:
	rm -f $(OBJ) $(EXEC)

# Ejecutar el programa y pasarle el nombre de la imagen como argumento
run: $(EXEC)
	@if [ -z "$(IMG)" ]; then \
		echo "Error: Debes especificar el nombre de la imagen. Ejemplo: make run IMG=people.jpg"; \
	else \
		./$(EXEC) $(IMG); \
	fi

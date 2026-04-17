SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./build/obj
BIN_DIR = ./build/bin
DOC_DIR = ./build/doc
EJECUTABLE = $(BIN_DIR)/programa

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
#wildcard lista los archivos con extension .c
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRC_FILES))
#patsubst convierte los archivos .c en .o

all: $(EJECUTABLE)

#all es el objetivo y $(EJECUTABLE) la dependencia

$(EJECUTABLE): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
#creo carpetas con mkdir -p
	gcc -o $(EJECUTABLE) $(OBJ_FILES)
#ejecuto enlazador con gcc para crear el ejecutable

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc -c $< -o $@ -I $(INC_DIR) -MMD

#el -I es para indicarle al compilador que busque los archivos
#de inclusion en la carpeta inc, -MMD crea archivos .d
#indica al compilador que los archivos .c dependen de los .h tambien

-include $(OBJ_DIR)/*.d

#-include lee los archivos .d

doc:
	mkdir -p $(DOC_DIR)
	doxygen Doxyfile

clean:
	rm -rf build

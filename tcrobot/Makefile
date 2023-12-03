CC := arm-linux-gnueabihf-gcc
CFLAGS := -Wall -Wextra -static
SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj

# Lista de arquivos .c na pasta src
SRC := $(wildcard $(SRC_DIR)/*.c)

# Gera a lista de arquivos .o na pasta obj
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nome do programa
TARGET := app

# Regra padrão para construir o programa
all: $(TARGET)

# Regra para construir o programa a partir dos arquivos .o
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Regra para construir os arquivos .o a partir dos arquivos .c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Regra para limpar os arquivos .o e o programa
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
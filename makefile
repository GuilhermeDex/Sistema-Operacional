# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -pthread -g -Iinclude

# Nome do executável
TARGET = jogar

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar os objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para criar o diretório de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra de limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

DEVKITARM = /opt/devkitpro/devkitarm

TOOLS = $(DEVKITARM)/bin
CC = $(TOOLS)/arm-none-eabi-gcc
OBJCOPY = $(TOOLS)/arm-none-eabi-objcopy
GBAFIX = /opt/devkitpro/tools/bin/gbafix

TARGET = $(BIN)/gbaPerlin

SRC = source
INCLUDE = include
OBJ = obj
BIN = bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: $(OBJECTS)
	$(CC) $(OBJECTS) -mthumb-interwork -mthumb -specs=gba.specs -o $(TARGET).elf
	$(OBJCOPY) -v -O binary $(TARGET).elf $(TARGET).gba
	$(GBAFIX) $(TARGET).gba

dirs:
	test -d $(OBJ) || mkdir $(OBJ)
	test -d $(BIN) || mkdir $(BIN)

$(OBJ)/%.o: $(SRC)/%.c dirs
	$(CC) -I $(INCLUDE) -c $< -mthumb-interwork -mthumb -O2 -o $@
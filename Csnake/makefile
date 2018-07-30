OBJ0  = settings_menu.c

OBJ1 = main_menu.c

COMPILER = gcc

OBJ0_NAME = -o settings_menu

OBJ1_NAME = -o main_menu

COMPILER_FLAGS = -w -g

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

settings: $(OBJ0)
	$(COMPILER) $(OBJ0) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(OBJ0_NAME)
main: $(OBJ0)
	$(COMPILER) $(OBJ1) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(OBJ1_NAME)

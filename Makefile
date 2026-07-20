LIB_NAME = libjstring.a

# DIRECTORIES
SRC_DIR = ./src/

OBJ_DIR = ./obj/

INC_DIR = ./inc/
LIB_DIR = ./lib/

# C FILES
SRC_FILES = $(SRC_DIR)js_array.c \
						$(SRC_DIR)js_array_size.c \
						$(SRC_DIR)js_array_sort.c \
						$(SRC_DIR)js_carray.c \
						$(SRC_DIR)js_dup.c \
						$(SRC_DIR)js_empty_array.c \
						$(SRC_DIR)js_free.c \
						$(SRC_DIR)js_free_array.c \
						$(SRC_DIR)js_itoa.c \
						$(SRC_DIR)js_join.c \
						$(SRC_DIR)js_new.c \
						$(SRC_DIR)js_remove.c \
						$(SRC_DIR)js_remove_back.c \
						$(SRC_DIR)js_remove_front.c \
						$(SRC_DIR)js_reverse.c \
						$(SRC_DIR)js_substr.c \
						$(SRC_DIR)js_tolower.c \
						$(SRC_DIR)js_toupper.c \
						$(SRC_DIR)js_trim.c \
						$(SRC_DIR)js_uitoa.c \
						$(SRC_DIR)utils.c \

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# COMPILATION / LINKING / REMOVAL
MKDIR = mkdir -p
REMOVE = rm -f
REMOVE_DIR = rm -rf

AR = ar rcs
CC = clang
CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR)

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES) | $(LIB_DIR)
	@echo "j_string: Creating archive"
	@$(AR) $(LIB_DIR)$(LIB_NAME) $(OBJ_FILES)
	@echo "j_string: Ready"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

$(LIB_DIR):
	@$(MKDIR) $(LIB_DIR)

clean:
	@echo "j_string: Removing .o files"
	@$(REMOVE_DIR) $(OBJ_DIR)

fclean:
	@echo "j_string: Removing .o files and library"
	@$(REMOVE_DIR) $(OBJ_DIR)
	@$(REMOVE_DIR) $(LIB_DIR)

re: fclean all

debug:
	@$(MAKE) re CFLAGS="$(CFLAGS) -g3 -O0 -fsanitize=address,undefined"

.PHONY: all clean fclean re debug

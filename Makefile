LIB_NAME = libjstring.a

# DIRECTORIES
SRC_DIR = ./src/

OBJ_DIR = ./obj/

INC_DIR = ./inc/
LIB_DIR = ./lib/

# C FILES
SRC_FILES = $(SRC_DIR)app_cpy_insert_push.c \
						$(SRC_DIR)array.c \
						$(SRC_DIR)clear_pop_remove.c \
						$(SRC_DIR)getters.c \
						$(SRC_DIR)misc.c \
						$(SRC_DIR)new_dup_free_join_substr.c \
						$(SRC_DIR)split.c \
						$(SRC_DIR)trim.c \

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

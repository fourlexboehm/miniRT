NAME	= miniRT
OS		= $(shell uname)

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

# src / obj files
SRC		= main.c utils/utils.c render.c utils/vector_fun.c utils/vector_fun2.c utils/cylinder_utils.c \
 		viewport/viewport.c viewport/camera.c colour.c raytracer.c \
		parser/parser.c parser/parser_utils.c parser/parser_utils2.c \
		colliders/plane_collider.c colliders/sphere_collider.c colliders/cylinder_collider.c \
		colour2.c collider_fun.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

# mlx library
ifeq ($(OS), Linux)
	MLX		= ./miniLibX_X11/
	MLX_LNK	= -L $(MLX) -l mlx -lXext -lX11
else
	MLX		= ./miniLibX/
	MLX_LNK	= -L $(MLX) -l mlx -framework OpenGL -framework AppKit
endif

MLX_INC	= -I $(MLX)
MLX_LIB	= $(addprefix $(MLX),mlx.a)

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft -l pthread

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/viewport
	mkdir -p $(OBJDIR)/utils
	mkdir -p $(OBJDIR)/parser
	mkdir -p $(OBJDIR)/colliders

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

r:
	clear
	make
	clear
	@./$(NAME) scenes/scene_1.rt

rr:
	clear
	make re
	clear
	@./$(NAME) scenes/scene_1.rt

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all

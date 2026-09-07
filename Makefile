# **************************************************************************** #
#                                   CODEXION                                   #
# **************************************************************************** #

NAME        = codexion

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

SRC_DIR     = src
INC_DIR     = include

MAIN_SRC    = $(SRC_DIR)/main/main.c

PARSER_SRC  = \
	$(SRC_DIR)/parser/parse_args.c \
	$(SRC_DIR)/parser/validate_args.c \
	$(SRC_DIR)/parser/scheduler_parse.c

INIT_SRC    = \
	$(SRC_DIR)/init/init_simulation.c \
	$(SRC_DIR)/init/init_coders.c \
	$(SRC_DIR)/init/init_dongles.c \
	$(SRC_DIR)/init/init_monitor.c \
	$(SRC_DIR)/init/destroy_simulation.c

CODER_SRC   = \
	$(SRC_DIR)/coder/coder_thread.c \
	$(SRC_DIR)/coder/coder_actions.c \
	$(SRC_DIR)/coder/coder_timestamps.c

DONGLE_SRC  = \
	$(SRC_DIR)/dongle/dongle_take.c \
	$(SRC_DIR)/dongle/dongle_release.c \
	$(SRC_DIR)/dongle/dongle_queue.c

SCHED_SRC   = \
	$(SRC_DIR)/scheduler/priority_queue.c \
	$(SRC_DIR)/scheduler/fifo.c \
	$(SRC_DIR)/scheduler/edf.c

MONITOR_SRC = \
	$(SRC_DIR)/monitor/monitor_thread.c \
	$(SRC_DIR)/monitor/burnout_check.c

LOG_SRC     = \
	$(SRC_DIR)/log/log.c \
	$(SRC_DIR)/log/timestamp.c

UTILS_SRC   = \
	$(SRC_DIR)/utils/ft_atoll_strict.c \
	$(SRC_DIR)/utils/is_number.c \
	$(SRC_DIR)/utils/error_exit.c \
	$(SRC_DIR)/utils/time_ms.c

SRC         = $(MAIN_SRC) $(PARSER_SRC) $(INIT_SRC) $(CODER_SRC) \
			  $(DONGLE_SRC) $(SCHED_SRC) $(MONITOR_SRC) $(LOG_SRC) $(UTILS_SRC)

OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

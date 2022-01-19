CLIENT_N = client
SERVER_N = server

SRC_C = client.c
SRC_S = server.c
BSRC_C = client_bonus.c
BSRC_S = server_bonus.c

PATH_CLI = ./src_cli/
PATH_SRV = ./src_srv/

SRCS_CLI = ${addprefix ${PATH_CLI}, ${SRC_C}}
SRCS_SRV = ${addprefix ${PATH_SRV}, ${SRC_S}}
BSRCS_CLI = ${addprefix ${PATH_CLI}, ${BSRC_C}}
BSRCS_SRV = ${addprefix ${PATH_SRV}, ${BSRC_S}}

OBJ_CLI = ${SRCS_CLI:.c=.o}
BOBJ_CLI = ${BSRCS_CLI:.c=.o}
OBJ_SRV = ${SRCS_SRV:.c=.o}
BOBJ_SRV = ${BSRCS_SRV:.c=.o}

DPDS = ${SRCS_CLI:.c=.d} ${BSRCS_CLI:.c=.d} ${SRCS_SRV:.c=.d} ${BSRCS_SRV:.c=.d}

CC = gcc

RM = rm -f

CFLAG = -Wall -Wextra -Werror

all:	${CLIENT_N} ${SERVER_N}

%.o : %.c
	${CC} ${CFLAG} -MMD -c $< -o $@

include ${wildcard ${DPDS}}

${CLIENT_N}:	${OBJ_CLI}
	${CC} ${CFLAG} -o $@ ${OBJ_CLI}

${SERVER_N}:	${OBJ_SRV}
	${CC} ${CFLAG} -o $@ ${OBJ_SRV}

debug:
	make CFLAG="${CFLAG} -g3" all

bonus:
	make SRC_C="${BSRC_C}" ${CLIENT_N}
	make SRC_S="${BSRC_S}" ${SERVER_N}

clean:
	${RM} ${OBJ_CLI} ${BOBJ_CLI} ${OBJ_SRV} ${BOBJ_SRV} ${DPDS}

fclean:	clean
	${RM} ${CLIENT_N} ${SERVER_N}

re:	fclean all

.PHONY: all bonus clean fclean re debug

NAME = race03

INC = pokerCheck.h
SRC = *.c
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
all: rf

rf:
	cp inc/$(INC) src/$(SRC) .
	clang $(CFLAGS) $(SRC) -o $(NAME)
	rm $(INC) $(SRC)

uninstall:
	rm $(NAME)

reinstall: uninstall rf

clean:
	rm $(INC) $(SRC)

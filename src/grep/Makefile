CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
# FLAGS =
utils.o: ../common/utils.c
	$(CC) -c $(FLAGS) ../common/utils.c
grep.o: grep.c
	$(CC) -c $(FLAGS) grep.c
s21_grep: grep.o utils.o
	$(CC) $(FLAGS) grep.o utils.o -o s21_grep
s21_grep_test:
	chmod 777 test_grep.sh
	./test_grep.sh
clean:
	rm -rf *.o

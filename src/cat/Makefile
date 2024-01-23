CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
# FLAGS =

utils.o: ../common/utils.c
	$(CC) -c $(FLAGS) ../common/utils.c
cat.o: cat.c
	$(CC) -c $(FLAGS) cat.c
s21_cat: cat.o utils.o
	$(CC) $(FLAGS) cat.o utils.o -o s21_cat
s21_cat_test:
	chmod 777 test_cat.sh
	./test_cat.sh
clean:
	rm -rf *.o
## Compilation automatique de source C
# Compilteur
CC := gcc
#options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb
# Règle de compilation

all :  test_listes_int test_listes_generiques algues

test_listes_int : test_listes_int.o listes_int.o
	$(CC) $(CFLAGS) -o $@ $^

test_int : test_listes_int
	./test_listes_int; diff -s test_listes_int_out_acomparer.txt test_listes_int_out.txt

memoire_listes_int : test_listes_int
	valgrind --leak-check=full ./test_listes_int


test_listes_generiques : test_listes_generiques.o listes_generiques.o
	$(CC) $(CFLAGS) -o $@ $^

algues : algues.o listes_generiques.o
	$(CC) $(CFLAGS) -o $@ $^

test : test_listes_generiques
	./test_listes_generiques; diff -s test_out_acomparer.txt test_out.txt

test_algues : algues
	./algues; diff -s algues_out_acomparer.txt algues_out.txt


memoire1 : test_listes_generiques
	valgrind --leak-check=full ./test_listes_generiques


memoire2 : algues
	valgrind --leak-check=full ./algues


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 



clean:
	rm *.o


TP_NUMERO := 2
TGZ_FILES :=  *.c *.h ?akefile cr.pdf
TP_DIR := TD$(TP_NUMERO)

rendu :
	[ -e cr.pdf ] || echo > cr.pdf
	cd .. ; tar czf $(TP_DIR)/rendu.tgz $(TGZ_FILES:%=$(TP_DIR)/%)


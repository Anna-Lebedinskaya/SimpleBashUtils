GC = gcc -Wall -Werror -Wextra -std=c11
opt_cat = -b -e -n -s -t -v -be -nst -tv -st
STR1 = include
STR2 = test
FILE1 = s21_grep.h
FILE2 = s21_grep.c

all: s21_cat s21_grep

s21_cat: s21_cat.o
	$(GC) cat/s21_cat.o -o cat/s21_cat

s21_cat.o:
	$(GC) -c cat/s21_cat.c -o cat/s21_cat.o

s21_grep: s21_grep.o
	$(GC) grep/s21_grep.o -o grep/s21_grep

s21_grep.o:
	$(GC) -c grep/s21_grep.c -o grep/s21_grep.o

clean:
	rm -f cat/*.o grep/*.o cat/s21_cat grep/s21_grep
	rm -f rez1 rez2

test_cat:
	cat/s21_cat $(opt_cat) cat/s21_cat.h > rez1
	cat $(opt_cat) cat/s21_cat.h > rez2
	diff -s rez1 rez2

test_grep:
	grep/s21_grep -e $(STR1) grep/$(FILE1) > rez1 && grep -e $(STR1) grep/$(FILE1) > rez2 && diff rez1 rez2
	grep/s21_grep -e $(STR1) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -e $(STR1) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	grep/s21_grep -e $(STR1) -e $(STR2) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -e $(STR1) -e $(STR2) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	grep/s21_grep -i $(STR1) grep/$(FILE1) > rez1 && grep -i $(STR1) grep/$(FILE1) > rez2 && diff rez1 rez2
	grep/s21_grep -i $(STR1) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -i $(STR1) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	grep/s21_grep -v $(STR1) grep/$(FILE1) > rez1 && grep -v $(STR1) grep/$(FILE1) > rez2 && diff rez1 rez2
	grep/s21_grep -v $(STR1) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -v $(STR1) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	grep/s21_grep -c $(STR1) grep/$(FILE1) > rez1 && grep -c $(STR1) grep/$(FILE1) > rez2 && diff rez1 rez2
	grep/s21_grep -c $(STR1) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -c $(STR1) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	grep/s21_grep -l $(STR1) grep/$(FILE1) > rez1 && grep -l $(STR1) grep/$(FILE1) > rez2 && diff rez1 rez2
	grep/s21_grep -l $(STR1) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -l $(STR1) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	grep/s21_grep -n $(STR1) grep/$(FILE1) > rez1 && grep -n $(STR1) grep/$(FILE1) > rez2 && diff rez1 rez2
	grep/s21_grep -n $(STR1) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -n $(STR1) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	grep/s21_grep -h $(STR1) grep/$(FILE1) > rez1 && grep -h $(STR1) grep/$(FILE1) > rez2 && diff rez1 rez2
	grep/s21_grep -h $(STR1) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -h $(STR1) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	grep/s21_grep -s $(STR1) grep/$(FILE1) > rez1 && grep -s $(STR1) grep/$(FILE1) > rez2 && diff rez1 rez2	
	grep/s21_grep -s $(STR1) grep/$(FILE1) grep/$(FILE2) > rez1 && grep -s $(STR1) grep/$(FILE1) grep/$(FILE2) > rez2 && diff rez1 rez2
	
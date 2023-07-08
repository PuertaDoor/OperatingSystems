CC = gcc
CFLAGS = -W -Wall -std=c89 -pedantic -O3

algo_remplacement_page : algo_remplacement_page.c liste.o allocation.o
												 $(CC) $(CFLAGS) algo_remplacement_page.c liste.o allocation.o -o algo_remplacement_page

liste.o : liste.c liste.h allocation.h
					$(CC) $(CFLAGS) liste.c -c

allocation.o : allocation.c allocation.h
							 $(CC) $(CFLAGS) allocation.c -c

clean :
			 rm -f *~ *.o algo_remplacement_page

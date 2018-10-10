CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra -pedantic -g
LINKS=-lpthread -lssl -lcrypto


all: feedreader run

feedreader: main.c arguments.c requests.c
		$(CC) $(CFLAGS) -o feedreader main.c arguments.c requests.c $(LINKS)

run:
		./feedreader http://www.fit.vutbr.cz/news/news-rss.php
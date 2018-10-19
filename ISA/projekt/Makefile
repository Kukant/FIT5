CC=c++
CFLAGS=$(pkg-config --cflags openssl)
LDLIBS=$(pkg-config --libs openssl)
XMLFLAGS=`xml2-config --cflags`
XMLLIBS=`xml2-config --libs`


all: feedreader run

feedreader: main.cpp arguments.cpp requests.cpp xml_reader.cpp
		$(CC) $(CFLAGS) $(XMLFLAGS) -std=gnu++11 -o feedreader main.cpp arguments.cpp requests.cpp xml_reader.cpp -lssl -lcrypto $(XMLLIBS)

run:
		./feedreader http://www.fit.vutbr.cz/news/news-rss.php

clean:
		rm feedreader

rebuild: clean feedreader
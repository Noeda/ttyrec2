CC = gcc
CFLAGS = -O2 -lutil -DHAVE_openpty
VERSION = 1.0.8

TARGET = ttyrec ttyplay ttytime ttyrec2_to_ttyrec

DIST =	ttyrec.c ttyplay.c ttyrec.h io.c io.h ttytime.c\
	README Makefile ttyrec.1 ttyplay.1 ttytime.1\
    ttyrec2_to_ttyrec.c

all: $(TARGET)

ttyrec: ttyrec.o io.o
	$(CC) $(CFLAGS) -o ttyrec ttyrec.o io.o

ttyplay: ttyplay.o io.o
	$(CC) $(CFLAGS) -o ttyplay ttyplay.o io.o

ttytime: ttytime.o io.o
	$(CC) $(CFLAGS) -o ttytime ttytime.o io.o

ttyrec2_to_ttyrec: ttyrec2_to_ttyrec.o io.o
	$(CC) $(CFLAGS) -o ttyrec2_to_ttyrec ttyrec2_to_ttyrec.o io.o

clean:
	rm -f *.o $(TARGET) ttyrecord *~

dist:
	rm -rf ttyrec-$(VERSION)
	rm -f ttyrec-$(VERSION).tar.gz

	mkdir ttyrec-$(VERSION)
	cp $(DIST) ttyrec-$(VERSION)
	tar zcf ttyrec-$(VERSION).tar.gz  ttyrec-$(VERSION)
	rm -rf ttyrec-$(VERSION)

CC = gcc
CFLAGS = -O2 -Wall -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lxlsxio_read -lzip -lexpat
PREFIX = /usr/local

BIN = xlsx_cat
SRC = xlsx_cat.c

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)

install: $(BIN)
	install -Dm755 $(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(PREFIX)/bin/$(BIN)

clean:
	rm -f $(BIN)

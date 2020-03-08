PROJ=makea

CC=emcc

CFLAGS=-O3 -s WASM=1 -o

ifeq ($(OS),Windows_NT)
	RM=del
else
	RM=rm
endif

public/$(PROJ).html:lib/$(PROJ).c
	$(CC) $^ $(CFLAGS) $@


.PHONY:clean
clean:
	$(RM) delfile.txt
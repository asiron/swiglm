CC=swipl-ld
CFLAGS=-shared -I./include

release: swiglm-release install

debug: swiglm-debug install

swiglm-release:
	$(CC) $(CFLAGS) -o bin/swiglm src/swiglm.cpp

swiglm-debug:
	$(CC) $(CFLAGS) -DDEBUG -o bin/swiglm src/swiglm.cpp

install:
	sudo cp bin/swiglm.so /usr/lib/swi-prolog/lib/i386

clean:
	rm -f bin/*
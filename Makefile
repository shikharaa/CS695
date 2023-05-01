CC=gcc
CFLAGS= -lcurl -lm -I. -DBBBW -DSHELLPRINT -DHTTP
DEPS = core/beaglebonebw/basics.h  core/beaglebonebw/connectServer/gpio/gpio.c core/beaglebonebw/connectServer/apache/simpleBBB.c  core/beaglebonebw/data/bme280/bme280.h
OBJ = core/beaglebonebw/basics.o  core/beaglebonebw/connectServer/gpio/gpio.o core/beaglebonebw/connectServer/apache/simpleBBB.o core/beaglebonebw/data/bme280/bme280.o  main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

BeagleboneB-HTTP: $(OBJ)
	@echo "\nCompiling..."
	$(CC) -o $@ $^ $(CFLAGS) 
	@echo "\nCompiled Finished, now you can run your code with: '$ ./BeagleboneB-HTTP'\n"
	@$ find . -name "*.o" -type f -delete

help:
	@echo "\n'make' to compile"
	@echo "'make clean' to delete .o files\n"

.PHONY: clean
clean:
	@$ find . -name "*.o" -type f -delete

CC = gcc
CFLAGS = -Wall
OUT_DIR = out

ls: src/ls.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $(OUT_DIR)/ls src/ls.c

clean:
	rm -rf $(OUT_DIR)

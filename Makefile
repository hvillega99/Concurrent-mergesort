sort: main.c
	gcc -o sort main.c -pthread

.PHONY: clean
clean:
	rm -f sort

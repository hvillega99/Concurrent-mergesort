merge: main.c
	gcc -o merge main.c -pthread

.PHONY: clean
clean:
	rm -f merge

all: toralize.c
	gcc toralize.c -o toralize

clean:
	@@rm toralize
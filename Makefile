CC = g++
CFLAGS = -std=c++23

SRCS = $(wildcard *.cpp)
EXEC = kodowanie

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

run: $(EXEC)
	./$(EXEC) norm_wiki_sample.txt codemap.txt encoded.txt encoded.txt codemap.txt result.txt

clean:
	rm -f $(EXEC)
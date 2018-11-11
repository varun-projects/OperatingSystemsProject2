src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lpthread

prog2: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) prog2
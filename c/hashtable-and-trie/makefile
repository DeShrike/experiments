CC = gcc
# CFLAGS = -O3
CFLAGS = -Wall -g
LIBS = -lm

EXT = c
SRCS = demo.$(EXT) trie.$(EXT) hashtable.$(EXT)
OBJS = $(patsubst %.$(EXT), %.o, $(SRCS))
TARGET = demo

all: $(TARGET)

rmbin:
	rm $(TARGET)

#########################################

$(OBJS): %.o : %.$(EXT)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

#############################################

clean:
	rm *.o

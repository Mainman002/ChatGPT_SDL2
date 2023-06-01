CC = gcc
CFLAGS = -v -Wall -Wextra -std=c99 -I./include
LIBS = -I/opt/homebrew/Cellar/sdl2/2.26.5/include -L/opt/homebrew/Cellar/sdl2/2.26.5/lib -lSDL2 -lSDL2_image

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE = $(BINDIR)/MySDL.app

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)

.PHONY: clean

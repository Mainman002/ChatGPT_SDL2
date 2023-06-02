CC = gcc
CFLAGS = -v -Wall -Wextra -std=c99 -I./include
LIBS = -lSDL2 -lSDL2_image

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE = $(BINDIR)/MySDL.app

# Default target
all: $(EXECUTABLE)

# Build for macOS
macos: CC = gcc
macos: CFLAGS += -I/opt/homebrew/Cellar/sdl2/2.26.5/include
macos: LIBS += -L/opt/homebrew/Cellar/sdl2/2.26.5/lib
macos: $(EXECUTABLE)

# Build for Windows
windows: CC = x86_64-w64-mingw32-gcc
windows: CFLAGS += -I/path/to/windows/sdl2/include
windows: LIBS += -L/path/to/windows/sdl2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
windows: EXECUTABLE := $(BINDIR)/MySDL.exe
windows: $(EXECUTABLE)

# Build for Linux
linux: CC = gcc
linux: CFLAGS += -I/path/to/linux/sdl2/include
linux: LIBS += -L/path/to/linux/sdl2/lib -lSDL2 -lSDL2_image
linux: $(EXECUTABLE)

# Build for macOS by default
.DEFAULT_GOAL := macos

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)

run-macos: macos
	@open $(EXECUTABLE)

run-windows: windows
	@wine $(EXECUTABLE)

run-linux: linux
	@$(EXECUTABLE)

.PHONY: all macos windows linux clean

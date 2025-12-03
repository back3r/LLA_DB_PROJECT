# Compiler and flags
CC      = clang
CSTD    = -std=c23
CFLAGS  = -Wall -Wextra -pedantic
DEBUG   = -g

# Directories
SRCDIR  = src
INCDIR  = include
ODIR    = obj
BINDIR  = bin

# Files
SRC     = $(wildcard $(SRCDIR)/*.c)
OBJ     = $(patsubst $(SRCDIR)/%.c, $(ODIR)/%.o, $(SRC))
BIN     = $(BINDIR)/main

# Default target
all: $(BIN)

# Link the final executable
$(BIN): $(OBJ) | $(BINDIR)
	@echo "Linking $(BIN)..."
	$(CC) $(CFLAGS) $(CSTD) -o $@ $^

# Compile each source file into obj/*.o
$(ODIR)/%.o: $(SRCDIR)/%.c | $(ODIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(CSTD) -I$(INCDIR) -c -o $@ $<

# Debug build
debug: CFLAGS += $(DEBUG)
debug: clean all
	@echo "Debug build complete!"

# Create directories if missing
$(ODIR):
	mkdir -p $(ODIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Remove all build files
clean:
	rm -f $(ODIR)/*.o
	rm -f $(BIN)

run: all
	./$(BIN)

.PHONY: all clean debug run

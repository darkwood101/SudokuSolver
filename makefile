# Compiler flags, compile command
CXX := g++
CXXFLAGS := -W -Wextra -Wall -Wshadow -O2 -std=c++17
cxxcompile = @echo " " $(2) && $(CXX) $(CXXFLAGS) $(DEPCXXFLAGS) $(INC) $(1)

# Build target
TARGET := sudokusolver
all: $(TARGET)

# Generic run command
run = @$(if $(2), echo " " $(2) $(3) &&,) $(1) $(3)

# Dependencies
DEPSDIR := .deps
DEPFILES := $(wildcard $(DEPSDIR)/*.d)
include $(DEPFILES)
DEPCXXFLAGS = -MD -MF $(DEPSDIR)/$(@F).d -MP

# Header files
INC := -Iinclude

# Source files
SRCDIR := src
SRCFILES := $(wildcard $(SRCDIR)/*.cc)

# Object files
OBJDIR := obj
OBJFILES := $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRCFILES))

# Create directories if they don't exist
$(OBJFILES): | $(OBJDIR) $(DEPSDIR)

$(OBJDIR):
	$(call run, mkdir -p $@, CREATE $@/)

$(DEPSDIR):
	$(call run, mkdir -p $@, CREATE $@/)

# How to make object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(call cxxcompile, -o $@ -c $<, COMPILE $<)

# How to make the executable
$(TARGET): $(OBJFILES)
	$(call cxxcompile, -o $@ $^, LINK)
	$(call run, true, "Build successful!")

# Remove dependencies, object files, and the executable
clean:
	$(call run, rm -rf $(OBJDIR) $(DEPSDIR) $(TARGET), CLEAN)

.PHONY: all clean

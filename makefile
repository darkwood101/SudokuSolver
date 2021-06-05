CC=g++

TARGET=sudokusolver

SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.cc)
CFLAGS= -fsanitize=address -O2 -Wextra -Wall -Wshadow

OBJ_DIR=obj
OBJ=$(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

DEP_DIR=.deps
DEPFLAGS= -MMD -MF $(DEP_DIR)/$*.d -MP
DEP=$(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo LINKING: $(TARGET)
	@$(CC) -o $@ $^ -fsanitize=address
	@echo
	@echo Build successful!

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR) $(DEP_DIR)
	@echo COMPILING: $@
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

clean:
	@echo CLEANING: dependency files
	@$(RM) -r $(DEP_DIR)
	@echo CLEANING: object files
	@$(RM) -r $(OBJ_DIR)
	@echo CLEANING: executable files
	@$(RM) $(TARGET)
	@echo
	@echo Clean successful!

.PHONY: all clean

-include $(DEP)

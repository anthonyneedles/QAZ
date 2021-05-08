# User Definitions ############################################################

TARGET = QAZ

# The type of build we want:
#   Debug   - All print statements
#   Release - No print statements, greatly reduces .text section size
BUILD_TYPE = Release

# The board we are using, dictating pinouts
#   QAZ_65        - QAZ 65% board
#   QAZ_TESTBOARD - QAZ Testboard
BOARD = QAZ_65

# Paths and Options  ##########################################################

BUILD_DIR   = build
SOURCE_DIR  = src
SCRIPT_DIR  = scripts
DOCS_DIR    = docs
DOXYGEN_DIR = $(DOCS_DIR)/doxygen
VERSION     = $(SOURCE_DIR)/version.hpp
EXECUTABLE  = $(BUILD_DIR)/$(SOURCE_DIR)/$(TARGET)

LINT_EXCLUDED_FILES := $(shell cat $(SCRIPT_DIR)/clint-excluded-files.txt)
LINTFLAGS  = --linelength=100 --recursive --root=$(SOURCE_DIR) --extensions=hpp,cpp,c,h
LINTFLAGS += --filter=-whitespace/braces,-readability/todo,-runtime/references
LINTFLAGS += $(foreach x, $(LINT_EXCLUDED_FILES), --exclude=$(x))

SF_ADDR = 0x08000000

CLEAN_DIRS = $(BUILD_DIR) $(DOXYGEN_DIR)

hdr_print = "\033[1;38;5;74m"$(1)"\033[0m"

# Build Rules ##################################################################

.PHONY: $(TARGET)
$(TARGET): $(BUILD_DIR)/Makefile
		@bash $(SCRIPT_DIR)/create-version.sh $(VERSION) $(BOARD)
		@make -C $(BUILD_DIR) --no-print-directory
		@arm-none-eabi-objcopy -O binary $(EXECUTABLE).elf $(EXECUTABLE).bin
		@bash $(SCRIPT_DIR)/verbose-bin-copy.sh $(EXECUTABLE).elf $(BOARD) $(BUILD_TYPE)
		@bash $(SCRIPT_DIR)/verbose-bin-copy.sh $(EXECUTABLE).bin $(BOARD) $(BUILD_TYPE)

.PHONY: all
all: build docs lint

$(BUILD_DIR)/Makefile:
		@cmake -DCMAKE_BUILD_TYPE="$(BUILD_TYPE)" -DBSP="$(BOARD)" -DTARGET=$(TARGET) \
				--no-print-directory -S . -B $(BUILD_DIR)

.PHONY: clean
clean:
	  @echo "Cleaning: $(CLEAN_DIRS)"
		@rm -rf $(CLEAN_DIRS)

.PHONY: docs
docs:
	  @echo $(call hdr_print,"Running Doxygen:")
		doxygen $(SCRIPT_DIR)/Doxyfile

.PHONY: lint
lint:
		@echo $(call hdr_print,"Running cpplint:")
		@echo -n $(foreach x, $(LINT_EXCLUDED_FILES), "\rExcluding $(x)\n")
		@$(SCRIPT_DIR)/cpplint.py $(LINTFLAGS) $(SOURCE_DIR)/*

.PHONY: flash
flash: $(TARGET)
		@echo $(call hdr_print,"Flashing $^ at $(SF_ADDR)")
		st-flash write $(EXECUTABLE).bin $(SF_ADDR)

.PHONY: help
help:
		@echo ""
		@echo $(call hdr_print,"$(TARGET)")
		@echo "  Build complete software target"
		@echo ""
		@echo $(call hdr_print,"all")
		@echo "  Build software target, doxygen, and lint"
		@echo ""
		@echo $(call hdr_print,"clean")
		@echo "  Removes all generated files"
		@echo ""
		@echo $(call hdr_print,"docs")
		@echo "  Use Doxygen to create project documentation"
		@echo ""
		@echo $(call hdr_print,"lint")
		@echo "  Run cpplint.py on $(SOURCE_DIR)"
		@echo ""
		@echo $(call hdr_print,"flash")
		@echo "  Flash binary at $(SF_ADDR), make '$(TARGET)' if no binary"

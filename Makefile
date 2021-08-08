# Configuration  ##############################################################

TARGET = QAZ

-include UserConfig.mk

# these should be set in `UserConfig.mk`: see `UserConfig.mk.template`
ifndef BUILD_TYPE
$(error "BUILD_TYPE must be defined. Have you created UserConfig.mk yet?")
endif
ifndef BOARD
$(error "BOARD must be defined. Have you created UserConfig.mk yet?")
endif

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

hdr_print = ">> \033[1;38;5;74m"$(1)"\033[0m"

# Build Rules ##################################################################

# dummy marker file to track when the Makefile changes
-include .rebuild-marker

.PHONY: $(TARGET)
$(TARGET): $(BUILD_DIR)/Makefile
		@echo $(call hdr_print,"BUILD_TYPE = ${BUILD_TYPE}")
		@echo $(call hdr_print,"     BOARD = ${BOARD}")
		@bash $(SCRIPT_DIR)/create-version.sh $(VERSION) $(BOARD)
		@make -C $(BUILD_DIR) --no-print-directory
		@arm-none-eabi-objcopy -O binary $(EXECUTABLE).elf $(EXECUTABLE).bin
		@bash $(SCRIPT_DIR)/verbose-bin-copy.sh $(EXECUTABLE).elf $(BOARD) $(BUILD_TYPE)
		@bash $(SCRIPT_DIR)/verbose-bin-copy.sh $(EXECUTABLE).bin $(BOARD) $(BUILD_TYPE)
		@arm-none-eabi-size $(EXECUTABLE).elf

.rebuild-marker: Makefile
	@echo $(call hdr_print,"Makefile change detected! Rebuilding...")
	@touch $@
	@make -s clean

.PHONY: all
all: $(TARGET) docs lint

$(BUILD_DIR)/Makefile:
		@cmake -DCMAKE_BUILD_TYPE="$(BUILD_TYPE)" -DBSP="$(BOARD)" -DTARGET=$(TARGET) \
				--no-print-directory -S . -B $(BUILD_DIR)

.PHONY: clean
clean:
	  @echo $(call hdr_print,"Cleaning: $(CLEAN_DIRS)")
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

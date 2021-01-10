# User Definitions  ############################################################

TARGET  = QAZ

CXX_SRC = core/clock.cpp                 \
					core/time_slice.cpp            \
					comm/i2c.cpp                   \
					comm/uart.cpp                  \
					lp500x/lp500x.cpp              \
					qaz/key_matrix.cpp             \
					qaz/lighting.cpp               \
					qaz/main.cpp                   \
					usb/usb.cpp                    \
					usb/kb_hid.cpp                 \
					usb/usb_descriptors.cpp        \
					util/debug.cpp                 \
		      util/hb.cpp                             

C_SRC   =

S_SRC	  = core/startup_stm32f042.s

INC     = ./CMSIS/Core/Include                \
					./CMSIS/Device/ST/STM32F0xx/Include \
					./src

# The type of build we want:
#   DEBUG   - All print statements
#   RELEASE - No print statements, greatly reduces .text section size
BUILD_TYPE = DEBUG

# The board we are using, dictating pinouts
#   QAZ_65        - QAZ 65% board
#   QAZ_TESTBOARD - QAZ Testboard
BOARD = QAZ_65

# Paths and Output #############################################################

ALL_SRC := $(CXX_SRC) $(C_SRC) $(S_SRC)

BLD_DIR := ./build
SRC_DIR := ./src
DOC_DIR := ./docs

OBJ_DIR := $(BLD_DIR)/obj
DEP_DIR := $(BLD_DIR)/dep
BIN_DIR := $(BLD_DIR)/bin
LOG_DIR := $(BLD_DIR)/log
OCD_DIR := $(BLD_DIR)/openocd
SRP_DIR := $(BLD_DIR)/scripts
DOX_DIR := $(DOC_DIR)/doxygen

BIN = $(BIN_DIR)/$(TARGET).bin
ELF = $(BIN_DIR)/$(TARGET).elf

# list of every subdir in src/ but with dep/obj dir prefixes
OBJ_DIRS := $(sort $(addprefix $(OBJ_DIR)/, $(dir $(ALL_SRC))))
DEP_DIRS := $(sort $(addprefix $(DEP_DIR)/, $(dir $(ALL_SRC))))

OBJ = $(CXX_SRC:%.cpp=$(OBJ_DIR)/%.o) $(C_SRC:%.c=$(OBJ_DIR)/%.o) $(S_SRC:%.s=$(OBJ_DIR)/%.o)
DEP = $(CXX_SRC:%.cpp=$(DEP_DIR)/%.d) $(C_SRC:%.c=$(DEP_DIR)/%.d) $(S_SRC:%.s=$(DEP_DIR)/%.d)

LST = $(LOG_DIR)/$(TARGET).lst
MAP = $(LOG_DIR)/$(TARGET).map
ODS = $(LOG_DIR)/$(TARGET)-od.sym
RES = $(LOG_DIR)/$(TARGET)-re.sym
LOG = $(LST) $(MAP) $(ODS) $(RES)

CLEAN = $(BIN_DIR) $(DEP_DIR) $(LOG_DIR) $(OBJ_DIR) $(DOX_DIR)

hdr_print = "\n\033[1;38;5;174m$(1)\033[0m"

# Tool Definitions #############################################################

PREFIX      = arm-none-eabi-

ARCH_FLAGS  = -mcpu=cortex-m0 -mthumb -msoft-float

BUILD_FLAGS = $(BUILD_TYPE) $(BOARD)

CC = $(PREFIX)gcc
CCFLAGS  = -std=gnu99 -ggdb3 -O2 -Wall -Wextra
CCFLAGS += -ffunction-sections -fdata-sections
CCFLAGS += -MMD -MP -MF $(DEP_DIR)/$*.d
CCFLAGS += $(foreach i, $(BUILD_FLAGS), -D$(i))
CCFLAGS += $(foreach d, $(INC), -I$(d))
CCFLAGS += $(ARCH_FLAGS)

CXX = $(PREFIX)g++
CXXFLAGS  = -std=c++17 -ggdb3 -O2 -Wall -Wextra
CXXFLAGS += -fno-rtti -fno-exceptions
CXXFLAGS += -ffunction-sections -fdata-sections
CXXFLAGS += -MMD -MP -MF $(DEP_DIR)/$*.d
CXXFLAGS += $(foreach i, $(BUILD_FLAGS), -D$(i))
CXXFLAGS += $(foreach d, $(INC), -I$(d))
CXXFLAGS += $(ARCH_FLAGS)

CP = $(PREFIX)objcopy
CPFLAGS  = -O binary

OD = $(PREFIX)objdump

RE = $(PREFIX)readelf

SZ = $(PREFIX)size

LD = $(PREFIX)g++
LDFLAGS  = -T $(BLD_DIR)/stm32f042k6.ld --specs=nosys.specs
LDFLAGS += -Wl,-Map,$(MAP),-gc-sections
LDFLAGS += $(ARCH_FLAGS)

SF = st-flash
SFFLAGS  = write
SF_ADDR  = 0x08000000

LINTFLAGS  = --linelength=100 --recursive --root $(SRC_DIR)
LINTFLAGS += --filter=-whitespace/braces,-readability/todo,-runtime/references

# Build Rules ##################################################################

.PHONY: $(TARGET)
$(TARGET): $(BIN) $(ELF) $(LOG)
		@echo $(call hdr_print,"Make success for target \'$(TARGET)\'")

.PHONY: all
all: clean $(TARGET) doc lint

$(BIN): $(ELF) | $(BIN_DIR)
		@echo $(call hdr_print,"Creating $@ from $^:")
		rm -f $(BIN_DIR)/*.bin
		$(CP) $(CPFLAGS) $(ELF) $(BIN)
		sh $(SRP_DIR)/git-hash-bin-copy.sh $(BIN)

$(ELF): $(OBJ) | $(BIN_DIR) $(LOG_DIR)
		@echo $(call hdr_print,"Linking $@ from $^:")
		rm -f $(BIN_DIR)/*.elf
		$(LD) $(LDFLAGS) $(OBJ) -o $(ELF)
		sh $(SRP_DIR)/git-hash-bin-copy.sh $(ELF)
		$(SZ) $(ELF)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIRS) $(DEP_DIRS)
		@echo $(call hdr_print,"Compiling $@ from $<:")
		$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIRS) $(DEP_DIRS)
		@echo $(call hdr_print,"Compiling $@ from $<:")
		$(CC) $(CCFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s | $(OBJ_DIRS) $(DEP_DIRS)
		@echo $(call hdr_print,"Compiling $@ from $<:")
		$(CC) $(CCFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIRS) $(DEP_DIRS) $(LOG_DIR) $(DOX_DIR):
		@echo $(call hdr_print,"Making dir $@")
		@mkdir --parents $@

$(LOG): $(ELF) | $(LOG_DIR)
		@echo $(call hdr_print,"Making log files: $(LOG)")
		$(OD) -S $(ELF) > $(LST)
		$(OD) -x $(ELF) > $(ODS)
		$(RE) -a $(ELF) > $(RES)

# include dependency files, which hold all dependency targets for all sources
# so if a file changes (header or source), all dependent files will rebuild
-include $(DEP)

# Utility Rules ################################################################

.PHONY: clean
clean:
		@echo $(call hdr_print,"Cleaning $(CLEAN)")
		@rm -rf $(CLEAN)

.PHONY: doc | $(DOC_DIR)
doc:
		@echo $(call hdr_print,"Running Doxygen:")
		doxygen $(BLD_DIR)/Doxyfile

.PHONY: lint
lint:
		@echo $(call hdr_print,"Running cpplint.py:")
		$(SRP_DIR)/cpplint.py $(LINTFLAGS) $(SRC_DIR)/*

.PHONY: flash
flash: $(BIN)
		@echo $(call hdr_print,"Flashing $^ at $(SF_ADDR)")
		$(SF) $(SFFLAGS) $(BIN) $(SF_ADDR)

.PHONY: tmux
tmux:
		sh $(SRP_DIR)/tmux-bootstrap.sh $(TARGET)

.PHONY: help
help:
		@echo ""
		@echo "clean"
		@echo "  Removes all object, dependency, and bin files"
		@echo ""
		@echo "$(TARGET)"
		@echo "  Build complete software target"
		@echo ""
		@echo "all"
		@echo "  Build software target, doxygen, and lint"
		@echo ""
		@echo "doc"
		@echo "  Use Doxygen to create project documentation"
		@echo ""
		@echo "lint"
		@echo "  Run cpplint.py on $(SRC_DIR)"
		@echo ""
		@echo "flash"
		@echo "  Flash binary at $(SF_ADDR), make '$(TARGET)' if no binary"
		@echo ""
		@echo "tmux"
		@echo "  Run tmux bootstrap (only if '$(TARGET)' session doesn't already exist)"

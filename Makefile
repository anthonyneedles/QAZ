# User Definitions  ############################################################

TARGET  = qaz

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

ALL_SRC = $(CXX_SRC) $(C_SRC) $(S_SRC)

BLD_DIR = ./build
SRC_DIR = ./src
DOC_DIR = ./docs

OBJ_DIR = $(BLD_DIR)/obj
DEP_DIR = $(BLD_DIR)/dep
BIN_DIR = $(BLD_DIR)/bin
LOG_DIR = $(BLD_DIR)/log
OCD_DIR = $(BLD_DIR)/openocd
SRP_DIR = $(BLD_DIR)/scripts
DOX_DIR = $(DOC_DIR)/doxygen

BIN = $(BIN_DIR)/$(TARGET).bin
ELF = $(BIN_DIR)/$(TARGET).elf

# list of every subdir in src/ but with dep/obj dir prefixes
OBJ_DIRS = $(sort $(addprefix $(OBJ_DIR)/, $(dir $(ALL_SRC))))
DEP_DIRS = $(sort $(addprefix $(DEP_DIR)/, $(dir $(ALL_SRC))))

# startup .o must be first so -flto doesn't optimize away ISRs...
OBJ = $(S_SRC:%.s=$(OBJ_DIR)/%.o) $(C_SRC:%.c=$(OBJ_DIR)/%.o) $(CXX_SRC:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(S_SRC:%.s=$(DEP_DIR)/%.d) $(C_SRC:%.c=$(DEP_DIR)/%.d) $(CXX_SRC:%.cpp=$(DEP_DIR)/%.d)

LST = $(LOG_DIR)/$(TARGET).lst
MAP = $(LOG_DIR)/$(TARGET).map
ODS = $(LOG_DIR)/$(TARGET)-od.sym
RES = $(LOG_DIR)/$(TARGET)-re.sym
LOG = $(LST) $(MAP) $(ODS) $(RES)

CLEAN = $(BIN_DIR) $(DEP_DIR) $(LOG_DIR) $(OBJ_DIR) $(DOX_DIR)

hdr_print = "\033[1;38;5;74m"$(1)"\033[0m"

# Tool Definitions #############################################################

PREFIX      = arm-none-eabi-

ARCH_FLAGS  = -mcpu=cortex-m0 -mthumb -msoft-float

BUILD_FLAGS = $(BUILD_TYPE) $(BOARD)

COMMONFLAGS  = -Werror -Wall -Wextra -pedantic
COMMONFLAGS += -ffunction-sections -fdata-sections
COMMONFLAGS += -MMD -MP -MF $(DEP_DIR)/$*.d
COMMONFLAGS += $(foreach d, $(BUILD_FLAGS), -D$(d))
COMMONFLAGS += $(foreach i, $(INC), -I$(i))
COMMONFLAGS += $(ARCH_FLAGS)
ifeq ($(BUILD_TYPE),DEBUG)
		COMMONFLAGS += -Og -ggdb3
else
		COMMONFLAGS += -O2 -flto
endif

CC = $(PREFIX)gcc
CCFLAGS  = $(COMMONFLAGS)
CCFLAGS += -std=gnu99

CXX = $(PREFIX)g++
CXXFLAGS  = $(COMMONFLAGS)
CXXFLAGS += -std=c++17 -fno-rtti -fno-exceptions -fno-threadsafe-statics
CXXFLAGS += -Wshadow -Wlogical-op -Wsuggest-override
CXXFLAGS += -Wsuggest-final-types -Wsuggest-final-methods

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
		@echo $(call hdr_print,"Make success for target '$(TARGET)'")
		@$(SZ) $(ELF)

.PHONY: all
all: clean $(TARGET) doc lint

$(BIN): $(ELF) | $(BIN_DIR)
		@rm -f $(BIN_DIR)/*.bin
		@$(CP) $(CPFLAGS) $(ELF) $(BIN)
		@bash $(SRP_DIR)/verbose-bin-copy.sh $(BIN) $(BOARD) $(BUILD_TYPE)

$(ELF): $(OBJ) | $(BIN_DIR) $(LOG_DIR)
		@echo $(call hdr_print,"Linking $@")
		@rm -f $(BIN_DIR)/*.elf
		@$(LD) $(LDFLAGS) $(OBJ) -o $(ELF)
		@bash $(SRP_DIR)/verbose-bin-copy.sh $(ELF) $(BOARD) $(BUILD_TYPE)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIRS) $(DEP_DIRS)
		@echo $(call hdr_print,"Compiling $<")
		@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIRS) $(DEP_DIRS)
		@echo $(call hdr_print,"Compiling $<")
		@$(CC) $(CCFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s | $(OBJ_DIRS) $(DEP_DIRS)
		@echo $(call hdr_print,"Compiling $<")
		@$(CC) $(CCFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIRS) $(DEP_DIRS) $(LOG_DIR) $(DOX_DIR):
		@mkdir --parents $@

$(LOG): $(ELF) | $(LOG_DIR)
		@echo $(call hdr_print,"Generating $(LOG)")
		@$(OD) -S $(ELF) > $(LST)
		@$(OD) -x $(ELF) > $(ODS)
		@$(RE) -a $(ELF) > $(RES)

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
	@echo $(call hdr_print,"Running cpplint:")
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
		@echo "  Removes all generated files"
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

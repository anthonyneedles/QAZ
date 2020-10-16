# User Definitions  ############################################################

TARGET = QAZ

CXX_SRC =

C_SRC   = main.c       \
				  clock.c      \
					debug.c      \
					time_slice.c \
		      hb.c         \
					key_matrix.c

S_SRC	  = startup_stm32f042.s

INC     = ./CMSIS/Include                     \
					./CMSIS/Device/ST/STM32F0xx/Include

HARDWARE   = 
BUILD_TYPE = DEBUG        # DEBUG or RELEASE
CLK_SOURCE = EXT_CRYSTAL  # EXT_CRYSTAL or HSI_48

# Paths and Output #############################################################

BLD_DIR := ./build
SRC_DIR := ./src

BIN_DIR := $(BLD_DIR)/bin
DEP_DIR := $(BLD_DIR)/dep
LOG_DIR := $(BLD_DIR)/log
OBJ_DIR := $(BLD_DIR)/obj
OCD_DIR := $(BLD_DIR)/openocd

BIN = $(BIN_DIR)/$(TARGET).bin
ELF = $(BIN_DIR)/$(TARGET).elf

OBJ = $(CXX_SRC:%.cpp=$(OBJ_DIR)/%.o) $(C_SRC:%.c=$(OBJ_DIR)/%.o) $(S_SRC:%.s=$(OBJ_DIR)/%.o)
DEP = $(CXX_SRC:%.cpp=$(OBJ_DIR)/%.d) $(C_SRC:%.c=$(DEP_DIR)/%.d) $(S_SRC:%.s=$(DEP_DIR)/%.d)

LST = $(LOG_DIR)/$(TARGET).lst
MAP = $(LOG_DIR)/$(TARGET).map
ODS = $(LOG_DIR)/$(TARGET)-od.sym
RES = $(LOG_DIR)/$(TARGET)-re.sym
LOG = $(LST) $(MAP) $(ODS) $(RES)

CLEAN = $(BIN_DIR)/* $(DEP_DIR)/* $(LOG_DIR)/* $(OBJ_DIR)/*

hdr_print = "\n\033[1;38;5;174m$(1)\033[0m"

# Tool Definitions #############################################################

PREFIX      = arm-none-eabi-

ARCH_FLAGS  = -mcpu=cortex-m0 -mthumb -msoft-float

BUILD_FLAGS = $(HARDWARE) $(BUILD_TYPE) $(CLK_SOURCE)  

CC = $(PREFIX)gcc
CCFLAGS  = -std=gnu99 -ggdb3 -O2 -Wall -Wextra
CCFLAGS += -ffunction-sections -fdata-sections
CCFLAGS += -MMD -MP -MF $(DEP_DIR)/$*.d
CCFLAGS += $(foreach i, $(BUILD_FLAGS), -D$(i))
CCFLAGS += $(foreach d, $(INC),         -I$(d))
CCFLAGS += $(ARCH_FLAGS)

CXX = $(PREFIX)g++
CXXFLAGS  = -std=c++17 -ggdb3 -O2 -Wall -Wextra
CXXFLAGS += -fno-rtti -fno-exceptions
CXXFLAGS += -ffunction-sections -fdata-sections
CXXFLAGS += -MMD -MP -MF $(DEP_DIR)/$*.d
CXXFLAGS += $(foreach i, $(BUILD_FLAGS), -D$(i))
CXXFLAGS += $(foreach d, $(INC),         -I$(d))
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

# Build Rules ##################################################################

.PHONY: all
all: $(TARGET)

.PHONY: $(TARGET)
$(TARGET): $(BIN) $(ELF) $(ROM) $(LOG)
		@echo $(call hdr_print,"Make success for target \'$(TARGET)\'")

$(BIN): $(ELF) | $(BIN_DIR)
		@echo $(call hdr_print,"Creating $@ from $^:")
		$(CP) $(CPFLAGS) $(ELF) $(BIN)

$(ELF): $(OBJ) | $(BIN_DIR) $(LOG_DIR)
		@echo $(call hdr_print,"Linking $@ from $^:")
		$(LD) $(LDFLAGS) $(OBJ) -o $(ELF)
		$(SZ) $(ELF)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(DEP_DIR)
		@echo $(call hdr_print,"Compiling $@ from $<:")
		$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR) $(DEP_DIR)
		@echo $(call hdr_print,"Compiling $@ from $<:")
		$(CC) $(CCFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s | $(OBJ_DIR) $(DEP_DIR)
		@echo $(call hdr_print,"Compiling $@ from $<:")
		$(CC) $(CCFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(DEP_DIR) $(LOG_DIR):
		@echo $(call hdr_print,"Making dir $@")
		mkdir $@

$(LOG): $(ELF) | $(LOG_DIR)
		@echo $(call hdr_print,"Making log files: $(LOG)")
		$(OD) -S $(ELF) > $(LST)
		$(OD) -x $(ELF) > $(ODS)
		$(RE) -a $(ELF) > $(RES)

-include $(DEP)

# Utility Rules ################################################################

.PHONY: log
log: $(LOG)

.PHONY: clean
clean:
		@echo $(call hdr_print,"Cleaning $(CLEAN)")
		@rm -f $(CLEAN)

.PHONY: flash
flash: $(BIN)
		@echo $(call hdr_print,"Flashing $^ at $(SF_ADDR)")
		$(SF) $(SFFLAGS) $(BIN) $(SF_ADDR)

.PHONY: help
help:
		@echo ""
		@echo "clean"
		@echo "  Removes all object, dependency, and bin files"
		@echo ""
		@echo "$(TARGET)"
		@echo "  Build complete software target"
		@echo ""
		@echo "flash"
		@echo "  Flash binary at $(SF_ADDR), make '$(TARGET)' if no binary"
		@echo ""

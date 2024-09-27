RPI_VERSION ?= 4

# Directory to mount the boot files
BOOTMNT ?= /run/media/zmp/SDCard/BOOT

ARMGNU ?= aarch64-linux-gnu

# C options
# -Wall: all warnings as errors
# -nostdlib: baremetal, so no standlib
# -nostartfiles: no startup files
# -ffreestanding:
# -Iinclude: include directory
# -mgeneral-regs-only: use only general registers
COPS = -DRPI_VERSION=$(RPI_VERSION) -Wall -nostdlib -nostartfiles \
	-ffreestanding -Iinclude -mgeneral-regs-only

# Assembly options
ASMOPS = -Iinclude


BUILD_DIR = build
SRC_DIR = src

all : kernel8.img

clean : 
	rm -rf $(BUILD_DIR) *.img

# C Object files
# - For each X.c file in SRC_DIR, 
# create a corresponding X_c.o in BUILD_DIR
# - Make sure the build directory exist
# - Compile the .c files into .o, without linking, and generate the 
# associated dependency file
#
# mkdir -p $(@D): This ensures that the directory for the output file
# exists by creating it if it doesn't. 
# $(@D) extracts the directory part from the target file path
#
# $(ARMGNU)-gcc: This invokes the ARM GCC compiler
# $(COPS): additional compiler options.
# -MMD: This flag tells the compiler to generate a dependency file in
# the Makefile format, which can be used later to track file
# dependencies for incremental builds.
# -c: tells the compiler to compile the source file without linking.
# $<: This refers to the first dependency, which in this case is 
# $(SRC_DIR)/%.c (the .c file).
# -o $@: This specifies the output file. $@ is a variable that holds
# the target name (i.e., $(BUILD_DIR)/%_c.o
$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
# Take each file in C_FILES.
# For each .c file in $(SRC_DIR) (represented by $(SRC_DIR)/%.c),
# $replace the .c extension and part of the path with
# $(BUILD_DIR)/%_c.o.
# % is a wildcard representing the filename
# -- If C_FILES = src/file1.c src/file2.c and BUILD_DIR = build, 
#    the result would be:
#      OBJ_FILES = build/file1_c.o build/file2_c.o.
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

# For each file in OBJ_FILES, replace the .o by .d extension
DEP_FILES = $(OBJ_FILES:%.o=%.d)
# Include all the generated DEP_FILES in the Makefile. These .d files, 
# created during compilation with the -MMD option, contain dependency
# information so that the Makefile knows which files to recompile when
# headers or sources change.
# The -include directive means that the Makefile will try to include
# these dependency files but will not throw an error if they don’t
# exist (for instance, the first time the Makefile is run, 
# before any .d files are generated).
-include $(DEP_FILES)


# - Link the object files, using the linker script into an ELF file
# - Convert the ELF file into a RAW executable binary (.img)
# - Rename the kernel image file, so we avoid collision with the RPI
# default one
kernel8.img : $(SRC_DIR)/linker.ld $(OBJ_FILES)
	@echo "Building for RPI $(value RPI_VERSION)"
	@echo "Deploy to $(value BOOTMNT)"
	@echo ""
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img 
ifeq ($(RPI_VERSION), 4)
	sudo cp kernel8.img $(BOOTMNT)/kernel8-rpi4.img
else
	sudo cp kernel8.img $(BOOTMNT)/
endif
	sudo cp config.txt $(BOOTMNT)/
	sync

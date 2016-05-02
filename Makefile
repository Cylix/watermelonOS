###
# Compiler
###
AS		=	i686-elf-as
CC		=	i686-elf-gcc
GRUB	= grub-mkrescue

###
# Flags
###
CFLAGS	+=	-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS	+=	-nostdlib -lgcc


###
# Directories configuration
###
CFG_DIR		= config
SRC_DIR		= src
BUILD_DIR	=	build
ISO_DIR		=	$(BUILD_DIR)/isodir
BOOT_DIR	=	$(ISO_DIR)/boot
GRUB_DIR	=	$(BOOT_DIR)/grub

###
# Configuration files
###
LD_CFG		=	$(CFG_DIR)/linker.ld
GRUB_CFG	=	$(CFG_DIR)/grub.cfg

###
# Kernel sources
###
SRC		=	$(SRC_DIR)/boot.s		\
				$(SRC_DIR)/kernel.c
OBJ		=	$(patsubst %.s, %.o, $(patsubst %.c, %.o, $(SRC)))

###
# Output name configuration
###
BIN	=	WatermelonOS.bin
ISO	=	WatermelonOS.iso

###
# all rule
###
all: $(BIN) $(ISO)

###
# WatermelonOS.bin rule
###
$(BIN):	$(OBJ)
				mkdir -p $(BUILD_DIR) $(ISO_DIR) $(BOOT_DIR) $(GRUB_DIR)
				$(CC) -T $(LD_CFG) -o $(BOOT_DIR)/$(BIN) $(OBJ) $(LDFLAGS)

###
# WatermelonOS.iso rule
###
$(ISO):	$(BIN)
				mkdir -p $(BUILD_DIR) $(ISO_DIR) $(BOOT_DIR) $(GRUB_DIR)
				cp $(GRUB_CFG) $(GRUB_DIR)
				$(GRUB) -o $(BUILD_DIR)/$(ISO) $(ISO_DIR)

###
# clean rule
###
clean:
				rm -f $(OBJ)

###
# fclean rule
###
fclean:	clean
				rm -rf $(BUILD_DIR)
				rm -rf $(BOOT_DIR)

###
# re rule
###
re: 		fclean all

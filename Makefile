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
GRUB_DIR	=	isodir
LD_DIR		= linker
SRC_DIR		= src
BUILD_DIR	=	build

###
# Linker configuration file
###
LD_CFG	=	$(LD_DIR)/linker.ld

###
# Kernel sources
###
SRC		=	$(SRC_DIR)/boot.s		\
				$(SRC_DIR)/kernel.c
OBJ		=	$(patsubst %.s, %.o, $(patsubst %.c, %.o, $(SRC)))

###
# Output name configuration
###
BIN	=	$(BUILD_DIR)/WatermelonOS.bin
ISO	=	$(BUILD_DIR)/WatermelonOS.iso

###
# all rule
###
all:	$(BIN) $(ISO)

###
# WatermelonOS.bin rule
###
$(BIN):	$(OBJ)
				mkdir -p $(BUILD_DIR)
				$(CC) -T $(LD_CFG) -o $(BIN) $(OBJ) $(LDFLAGS)

###
# WatermelonOS.iso rule
###
$(ISO):	$(BIN)
				cp $(BIN) $(GRUB_DIR)/boot/
				$(GRUB) -o $(ISO) $(GRUB_DIR)

###
# clean rule
###
clean:
				rm -f $(OBJ)

###
# fclean rule
###
fclean:	clean
				rm -f $(BIN)
				rm -f $(ISO)

###
# re rull
###
re: 		fclean all

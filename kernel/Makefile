###
# Arch
###
HOST			?=	$(shell ../default-host.sh)
HOSTARCH	:=	$(shell ../target-triplet-to-arch.sh $(HOST))


###
# Default flags
###
CFLAGS		?= -O2 -g
LDFLAGS		?=
LIBS			?=


###
# Installation directories configuration
###
DESTDIR			?=
PREFIX			?=	/usr/local
EXEC_PREFIX	?=	$(PREFIX)
BOOTDIR			?=	$(EXEC_PREFIX)/boot
INCLUDEDIR	?=	$(PREFIX)/include
ARCHDIR			:=	arch/$(HOSTARCH)


###
# include arch specific makefile configuration
###
include $(ARCHDIR)/make.config


###
# Mandatory flags
###
CFLAGS		:= $(CFLAGS) $(KERNEL_ARCH_CFLAGS) -ffreestanding -fbuiltin -Wall -Wextra -Iinclude -std=gnu11 -D__is_kernel
LDFLAGS		:= $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS			:= $(LIBS) $(KERNEL_ARCH_LIBS) -nostdlib -lk -lgcc


###
# Object files
###
OBJS			:=	$(KERNEL_ARCH_OBJS) 			\
							kernel/kernel.o						\
							kernel/frame_allocator.o


###
# Build name
###
NAME 			:=	WatermelonOS.kernel


###
# all rule
###
all: $(NAME)


###
# kernel build rule
###
$(NAME): 	$(OBJS) $(ARCHDIR)/linker.ld
					$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(OBJS) $(LDFLAGS) $(LIBS)


###
# clean rule
###
clean:
				rm -f $(OBJS)


###
# fclean rule
###
fclean:	clean
				rm -f $(NAME)


###
# re rule
###
re: fclean all


###
# install rule
###
install: install-headers install-kernel


###
# install-headers rule
###
install-headers:
									mkdir -p $(DESTDIR)$(INCLUDEDIR)
									cp -Rv include/* $(DESTDIR)$(INCLUDEDIR)


###
# install-kernel rule
###
install-kernel: $(NAME)
								mkdir -p $(DESTDIR)$(BOOTDIR)
								cp $(NAME) $(DESTDIR)$(BOOTDIR)


###
# .PHONY
###
.PHONY: all clean fclean re install install-headers install-kernel

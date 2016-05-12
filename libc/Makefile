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
INCLUDEDIR	?=	$(PREFIX)/include
LIBDIR			?=	$(EXEC_PREFIX)/lib
ARCHDIR			:=	arch/$(HOSTARCH)


###
# include arch specific makefile configuration
###
include $(ARCHDIR)/make.config


###
# Mandatory flags
###
CFLAGS			:=	$(CFLAGS) -Wall -Wextra -Iinclude -std=gnu11
LIBC_CFLAGS	:=	$(CFLAGS) $(ARCH_CFLAGS) -D__is_libc
LIBK_CFLAGS	:=	$(CFLAGS) $(KERNEL_ARCH_CFLAGS) -ffreestanding -fbuiltin -D__is_kernel


###
# Object files
###
FREEOBJS		:=	$(ARCH_FREEOBJS) 	\
								stdio/printf.o 		\
								stdio/putchar.o 	\
								stdio/puts.o 			\
								stdlib/abort.o 		\
								stdlib/itoa.o			\
								stdlib/uitoa.o		\
								string/memcmp.o 	\
								string/memcpy.o 	\
								string/memmove.o 	\
								string/memset.o 	\
								string/strlen.o 	\

HOSTEDOBJS	:=	$(ARCH_HOSTEDOBJS) \

OBJS				:=	$(FREEOBJS) \
								$(HOSTEDOBJS) \

LIBK_OBJS		:=	$(FREEOBJS:.o=.libk.o)


###
# Build name
###
LIBC				:= libc.a
LIBK				:= libk.a
BINARIES		:= $(LIBC) $(LIBK)


###
# all rule
###
all: $(BINARIES)


###
# libc build rule
###
$(LIBC):	$(OBJS)
					$(AR) rcs $@ $(OBJS)


###
# libk build rule
###
$(LIBK):	$(LIBK_OBJS)
					$(AR) rcs $@ $(LIBK_OBJS)


###
# .o generation (from .c) specification for libc sources
###
%.o: %.c
					$(CC) -c $< -o $@ $(LIBC_CFLAGS)


###
# .o generation (from .s) specification for libc sources
###
%.o: %.S
					$(CC) -c $< -o $@ $(LIBC_CFLAGS)


###
# .o generation (from .c) specification for libk sources
###
%.libk.o: %.c
					$(CC) -c $< -o $@ $(LIBK_CFLAGS)


###
# .o generation (from .s) specification for libk sources
###
%.libk.o: %.S
					$(CC) -c $< -o $@ $(LIBK_CFLAGS)


###
# clean rule
###
clean:
				rm -f $(OBJS) $(LIBK_OBJS)


###
# fclean rule
###
fclean:	clean
				rm -f $(BINARIES)


###
# re rule
###
re: fclean all


###
# install rule
###
install: install-headers install-libs


###
# install-headers rule
###
install-headers:
									mkdir -p $(DESTDIR)$(INCLUDEDIR)
									cp -Rv include/* $(DESTDIR)$(INCLUDEDIR)


###
# install-libs rule
###
install-libs: $(BINARIES)
							mkdir -p $(DESTDIR)$(LIBDIR)
							cp $(BINARIES) $(DESTDIR)$(LIBDIR)


###
# .PHONY
###
.PHONY: all clean fclean re install install-headers install-libs

  .global paging_enable

  .section .text

paging_enable:
  # Create new frame
  push %ebp
  mov %esp, %ebp

  # Enable paging by setting bit #31 of CR0
  mov %cr0, %eax
  or $0x80000000, %eax
  mov %eax, %cr0

  # Restore caller's frame
  mov %ebp, %esp
  pop %ebp
  ret

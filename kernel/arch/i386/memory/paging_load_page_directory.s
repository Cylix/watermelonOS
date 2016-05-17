  .global paging_load_page_directory

  .section .text

paging_load_page_directory:
  # Create new frame
  push %ebp
  mov %esp, %ebp

  # Store page directory in CR3 register
  mov 8(%ebp), %eax
  mov %eax, %cr3

  # Restore caller's frame
  mov %ebp, %esp
  pop %ebp
  ret

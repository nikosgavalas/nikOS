# to run:
# $ make debug
# $ gdb -x debug.gdb

target remote localhost:1234
symbol-file kernel.elf 
break kmain

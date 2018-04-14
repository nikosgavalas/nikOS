# to run:
# $ make debug
# $ gdb -x debug.gdb
# and 'continue'

target remote localhost:1234
symbol-file kernel.elf 
break kmain

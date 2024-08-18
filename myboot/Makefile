CC :=arm-linux-gcc

.PHONY:all
all:	myboot

#mystart.o:	mystart.S
#	arm-linux-gcc -c mystart.S
#mylowlevel_init.o:	mylowlevel_init.S
#	arm-linux-gcc -c mylowlevel_init.S
#%.o:	%.S
#	arm-linux-gcc -c $<

%.o:	%.S
	$(CC) -o $@ -c $<

.PHONY:mksd
mksd:
	sudo dd iflag=dsync oflag=dsync if=myboot.16k of=/dev/sdb seek=1

myboot:	mystart.o mylowlevel_init.o myboot.lds
	arm-linux-ld -Tmyboot.lds -o myboot mystart.o mylowlevel_init.o
	arm-linux-objcopy -O binary myboot myboot.bin
	./split16k myboot.bin myboot.16k

.PHONY:clean
clean:
	rm *.o myboot myboot.bin myboot.16k -f



1：myboot里面是对于mini2440的uboot学习，点亮了led2，并编写了makefile以及需要的源文件，
makefile里面有编译以及lds的链接过程。最后需要使用dd命令烧写到sd卡上（makefile里面也有这个命令）
2：uboot.16k划分例程里面是将uboot.bin的前16k-16byte划分出来，转载到uboot.16k中，
其中uboot.16k的前16byte是校验和，后面16k-16byte的内容是uboot.bin的二进制内容

1: In myboot, there is U-Boot learning for mini2440, with LED2 lit up and makefiles and required source files written,
The makefile contains the compilation and LDS linking process. 
Finally, the dd command needs to be burned onto the SD card (this command is also included in the makefile)
2: In the uboot.16k partitioning routine, the first 16k-16bytes of uboot.bin are partitioned and transferred to uboot.16k,
The first 16 bytes of uboot.16k are the checksum, and the remaining 16k-16 bytes are the binary content of uboot.bin

SECTIONS
{
    . = 0XD0020010;
    .text : {
        mystart.o
        * (.text)
    }
    .data : {
        * (.data)
    }
    .bss_start = .;
    .bss : {
        * (.bss)
    }
    .bss_end = .;
}
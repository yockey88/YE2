    option casemap:none

nl = 10
max_size = 256

    .data
fmt_str byte 'Hello, Assembly!' , 10 , 0

    .code
    externdef printf:proc

    public asm_func
asm_func proc
    sub rsp , 56
    
    lea rcx , fmt_str
    call printf

    add rsp , 56 
    ret
asm_func endp

    END
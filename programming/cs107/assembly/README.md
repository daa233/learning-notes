
This is simple demo to compile C program to Assembly code.

Steps:
1. Compilation
    ```shell
    $ gcc -S demo.c -o demo.s
    ```
2. Assembly
    ```shell
    $ as demo.s -o demo.o
    ```
3. Linking
    ```shell
    $ gcc -o demo demo.o
    ```
4. Run
    ```shell
    $ ./demo
    Hello World!
    ```


The example content of the assembly code `demo.s`:
```s
	.file	"demo.c"
	.text
	.section	.rodata
.LC0:
	.string	"Hello World!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
```

You can access the website [Compiler Explorer](https://godbolt.org/) to get more clear assembly code like following:
```s
.LC0:
        .string "Hello World!"
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     DWORD PTR [rbp-4], edi
        mov     QWORD PTR [rbp-16], rsi
        mov     edi, OFFSET FLAT:.LC0
        call    puts
        mov     eax, 0
        leave
        ret
```
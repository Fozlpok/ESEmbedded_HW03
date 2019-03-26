HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------
**If you volunteer to give the presentation next week, check this.**

--------------------

**★★★ Please take your note here ★★★**

#  實驗內容

透過觀察反組譯在 C 是如何return 


# main.c

```
void reset_handler(void)
{
	int a=1;
	a=fun1(a);
		
}

int fun1(int a)
{
	a*=2;
	a=fun2(a);
	return a;
}
int fun2(int a)
{
	a*=2;
	return a;

}
```
# 反組譯

```
Disassembly of section .mytext:

00000000 <reset_handler-0x8>:
   0:	20000100 	andcs	r0, r0, r0, lsl #2
   4:	00000009 	andeq	r0, r0, r9

00000008 <reset_handler>:
   8:	b580      	push	{r7, lr}
   a:	b082      	sub	sp, #8
   c:	af00      	add	r7, sp, #0
   e:	2301      	movs	r3, #1
  10:	607b      	str	r3, [r7, #4]
  12:	6878      	ldr	r0, [r7, #4]
  14:	f000 f804 	bl	20 <fun1>
  18:	6078      	str	r0, [r7, #4]
  1a:	3708      	adds	r7, #8
  1c:	46bd      	mov	sp, r7
  1e:	bd80      	pop	{r7, pc}

00000020 <fun1>:
  20:	b580      	push	{r7, lr}
  22:	b082      	sub	sp, #8
  24:	af00      	add	r7, sp, #0
  26:	6078      	str	r0, [r7, #4]
  28:	687b      	ldr	r3, [r7, #4]
  2a:	005b      	lsls	r3, r3, #1
  2c:	607b      	str	r3, [r7, #4]
  2e:	6878      	ldr	r0, [r7, #4]
  30:	f000 f806 	bl	40 <fun2>
  34:	6078      	str	r0, [r7, #4]
  36:	687b      	ldr	r3, [r7, #4]
  38:	4618      	mov	r0, r3
  3a:	3708      	adds	r7, #8
  3c:	46bd      	mov	sp, r7
  3e:	bd80      	pop	{r7, pc}

00000040 <fun2>:
  40:	b480      	push	{r7}
  42:	b083      	sub	sp, #12
  44:	af00      	add	r7, sp, #0
  46:	6078      	str	r0, [r7, #4]
  48:	687b      	ldr	r3, [r7, #4]
  4a:	005b      	lsls	r3, r3, #1
  4c:	607b      	str	r3, [r7, #4]
  4e:	687b      	ldr	r3, [r7, #4]
  50:	4618      	mov	r0, r3
  52:	370c      	adds	r7, #12
  54:	46bd      	mov	sp, r7
  56:	f85d 7b04 	ldr.w	r7, [sp], #4
  5a:	4770      	bx	lr
```
# 結果

1. reset_handler引數存到 r0~r3 的暫存器中
2. 傳‵回傳資料會由 r0 放資料
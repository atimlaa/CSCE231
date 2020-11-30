/*
* CS:APP Data Lab
*
* <Aryan Timla (atimla)>
*
* bits.c - Source file with your solutions to the Lab.
*          This is the file you will hand in to your instructor.
*
* WARNING: Do not include the <stdio.h> header; it confuses the dlc
* compiler. You can still use printf for debugging without including
* <stdio.h>, although you might get a compiler warning. In general,
* it's not good practice to ignore compiler warnings, but in this
* case it's OK.
*/

/*
* 0x7F800000 is positive infinity, and 0xFF800000 is negative infinity.
* 0x00800000 (smallest normal), 0x007fffff (biggest denormal)
* 0x80000000 is same as shifting by 31 bits i.e. getting the sign
* 1000 0000 0000 0000 0000 0000 0000 0000
* 0xFF = int(255).
* It look like this in binary: 00000000 00000000 00000000 11111111.
* When you do a bit wise AND with 0xFF on any number,
* it is going to mask all but the lowest 8 bits of the number
*/

#if 0
/*
* Instructions to Students:
*
* STEP 1: Read the following instructions carefully.
*/

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code
must conform to the following style:

int Funct(arg1, arg2, ...) {
  /* brief description of how your implementation works */
  int var1 = Expr1;
  ...
  int varM = ExprM;

  varJ = ExprJ;
  ...
  varN = ExprN;
  return ExprR;
}

Each "Expr" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.


You may assume that your machine:
1. Uses 2s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
* pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
*/
int pow2plus1(int x) {
  /* exploit ability of shifts to compute powers of 2 */
  return (1 << x) + 1;
}

/*
* pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
*/
int pow2plus4(int x) {
  /* exploit ability of shifts to compute powers of 2 */
  int result = (1 << x);
  result += 4;
  return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.  This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc (data lab checker) compiler (described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc. Note that '=' is not
counted; you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
header comment for each function. If there are any inconsistencies
between the maximum ops in the writeup and in this file, consider
this file the authoritative source.

/*
* STEP 2: Modify the following functions according the coding rules.
*
*   IMPORTANT. TO AVOID GRADING SURPRISES:
*   1. Use the dlc compiler to check that your solutions conform
*      to the coding rules.
*   2. Use the BDD checker to formally verify that your solutions produce
*      the correct answers.
*/


#endif
/* Copyright (C) 1991-2015 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with the GNU C Library; if not, see
<http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
include it implicitly at the start of every compilation.  It must
not itself include <features.h> or any other header that includes
<features.h> because the implicit include comes before any feature
test macros that may be defined in a source file before it first
explicitly includes a system header.  GCC knows the name of this
header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
and complex.  If the GCC (4.9 and later) predefined macros
specifying compiler intent are available, use them to determine
whether the overall intent is to support these features; otherwise,
presume an older compiler has intent to support these features and
define these macros by default.  */
/* wchar_t uses Unicode 7.0.0.  Version 7.0 of the Unicode Standard is
synchronized with ISO/IEC 10646:2012, plus Amendments 1 (published
on April, 2013) and 2 (not yet published as of February, 2015).
Additionally, it includes the accelerated publication of U+20BD
RUBLE SIGN.  Therefore Unicode 7.0.0 is between 10646:2012 and
10646:2014, and so we use the date ISO/IEC 10646:2012 Amd.1 was
published.  */
/* We do not support C11 <threads.h>.  */
/*
* float_neg - Return bit-level equivalent of expression -f for
*   floating point argument f.
*   Both the argument and result are passed as unsigned int's, but
*   they are to be interpreted as the bit-level representations of
*   single-precision floating point values.
*   When argument is NaN, return argument.
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 10
*   Rating: 2
*/

unsigned float_neg(unsigned uf) {
  unsigned neg_uf = uf ^ 0x80000000;
  unsigned exp = (uf & 0x7F800000) >> 23;
  unsigned frac = uf & 0x007FFFFF;

  // if the exponent contains only ones and frac in not zero
  if (exp == 0xFF && frac!=0x00){
    // if NaN returnes the argument itself
    return uf;
  }
  else {
    return neg_uf;
  }
}

/*
* float_i2f - Return bit-level equivalent of expression (float) x
*   Result is returned as unsigned int, but
*   it is to be interpreted as the bit-level representation of a
*   single-precision floating point values.
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 30
*   Rating: 4
*/
unsigned float_i2f(int x) {
  int sign = x & 0x80000000;
  int exp = 158;
  int bias = 127;

  // if sign-bit is 1, negate
  if(sign == 0x80000000){
    x = ~x + 1;
  }
  // base case
  if (x == 0) {
    return 0;
  }

  while ((x & 0x80000000) == 0){
    exp--;
    x <<= 1;
  }
  int frac = (x & 0x7FFFFFFF) >> 8;
  // rounding
  if (x & 128 && ((frac & 1) || ((x & bias) > 0))){
    // if ((x & 0xFF > bias) || ((x & 128) && frac & 1)) {
    frac++;
  }

  return sign + (exp << 23) + frac;
}
/*
* float_twice - Return bit-level equivalent of expression 2*f for
*   floating point argument f.
*   Both the argument and result are passed as unsigned int's, but
*   they are to be interpreted as the bit-level representation of
*   single-precision floating point values.
*   When argument is NaN, return argument
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 30
*   Rating: 4
*/
unsigned float_twice(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = uf & 0x7F800000;
  unsigned frac = uf & 0x007FFFFF;
  unsigned result;

  if(exp == 0x7F800000){  // NaN
    return uf;
  }else if(exp == 0){
    result = sign | frac << 1;
  }else{
    result = uf + 0x800000;
  }
  return result;
}
/*
* float_abs - Return bit-level equivalent of absolute value of f for
*   floating point argument f.
*   Both the argument and result are passed as unsigned int's, but
*   they are to be interpreted as the bit-level representations of
*   single-precision floating point values.
*   When argument is NaN, return argument..
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 10
*   Rating: 2
*/
unsigned float_abs(unsigned uf) {
  unsigned exp = uf & 0x7F800000;
  unsigned frac = uf & 0x007FFFFF;

  // if the exponent contains only ones and frac in not zero
  if (exp == 0x7F800000 && frac != 0x00){
    // if NaN returnes the argument itself
    return uf;
  }
  unsigned abs = uf & 0x7FFFFFFF;
  return abs;
}
/*
* float_f2i - Return bit-level equivalent of expression (int) f
*   for floating point argument f.
*   Argument is passed as unsigned int, but
*   it is to be interpreted as the bit-level representation of a
*   single-precision floating point value.
*   Anything out of range (including NaN and infinity) should return
*   0x80000000u.
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 30
*   Rating: 4
*/
int float_f2i(unsigned uf) {
  int sign = uf & 0x80000000;
  int exp = uf & 0x7F800000;
  int bias = 127;
  int e = (exp >> 23) - bias;
  int frac = uf & 0x7FFFFF;
  //NaN or out of range
  if(exp == 0x7F800000 || e > 30){   //127+31=158 so
    return 0x80000000u;
  }
  if(exp == 0){
    return 0;
  }
  if(e < 0){
    return 0;
  }

  //nomalized
  frac = frac | 0x800000;
  if (e >= 23){
    frac = frac << (e - 23);
  } else{
    frac = frac >> (23 - e);
  }
  // if sign-bit is 1, negate
  if(sign == 0x80000000){
    return ~frac + 1;
  }

  return frac;
}

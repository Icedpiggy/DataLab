/* 
 * CS:APP Data Lab 
 * 
 * 林诗航 24300240228
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /* 直接将 1 左移 31 位即可 */
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /* 异或结果中这一位为 1 也就是既不为 2 也不为 0 */
	return ~(x & y) & ~(~x & ~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* 由于使用算术右移，那么 x >> 31 在 x >= 0 时为 0，在 x < 0 时为 0xffffffff，另使用 ~x + 1 得到 -x*/
  return (x >> 31) & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /* 将 src 与 dst 的字节提取，直接异或上去即可 */
  src = src << 3;
  dst = dst << 3;
  int B = ((x >> src) ^ (x >> dst)) & 0xff;
  return x ^ (B << dst);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* 逻辑右移，需要把符号位删掉，在算术右移的基础上仅保留低 32 - n 位 */
  int s = (x >> 31) & 1;
  x = x ^ (s << 31);
  return x >> n | (s << (32 + ~n)) ;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /* 创建 0x0f0f0f0f 的 mask，将两部分分别逻辑左移逻辑右移 4 位再合起来，无需处理符号位 */
  int msk = 0x0f;
  msk = msk | msk << 8;
  msk = msk | msk << 16;
  return ((x & msk) << 4) | ((x >> 4) & msk);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* x 的 low1bit 为 x & -x = x & (~x + 1)，那么 low0bit 为 ~x & (x + 1)，先得到将末位 0 置 1 的 y，再做一次 low1bit */
  int y = x ^ (~x & (x + 1));
  return ~y & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* 将 x 前后 16b 拆开并异或为 16b 数不改变 parity，重复直到压成 1b，为了节省运算数量使用左移，没有必要将 x 的后若干位清空 */
  x = x ^ (x << 16);
  x = x ^ (x << 8);
  x = x ^ (x << 4);
  x = x ^ (x << 2);
  x = x ^ (x << 1);
  return (~x >> 31) & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* 将符号位单独处理，将不重叠的三部分合并即可 */
  int s = (x >> 31) & 1;
  x = x ^ (s << 31);
  return (x >> n) | (x << (33 + ~n)) | (s << (32 + ~n));
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* 加上 2^(n-1)，若后 n bit 为 0，则第 n 位置零 */
  int _1 = ~0;
  int msk = (1 << n) + _1;
  x = x + (1 << (n + _1));
  int a = !(x & msk);
  x = (x ^ (x & (a << n))) & ~msk;
  return x;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* 即计算 C 语言下的 x + (y - x) / 2，使用 32b + 1b 的数，绝对值向下取整 */
  int d1b = (y & 1) + ~(x & 1) + 1;
  int d32b = (y >> 1) + ~(x >> 1) + 1;
  int o = d1b >> 1;
  d32b = d32b + o;
  d1b = d1b + ~(o << 1) + 1;
  int msk = ((!!d32b << 31) >> 31) & ((d32b >> 31) ^ (d1b >> 31));
  int d = d32b + (msk & d1b);
  return x + d;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* 即 a-x b-x 异号或其中一个为 0，但是 a 与 -x 同号时可以直接确定 a-x 的符号，异号时计算不会溢出，注意 -x 符号的求法，避免 0x80000000 问题 */
  int xz = !x, az = !a, bz = !b;
  int xs = ((!xz << 31) >> 31) & ~(x >> 31), as = a >> 31, bs = b >> 31;
  int axsc = (!(xs ^ as)) | xz | az, bxsc = (!(xs ^ bs)) | xz | bz;
  axsc = (axsc << 31) >> 31;
  bxsc = (bxsc << 31) >> 31;

  int axs = (axsc & (xs | as)) | (~axsc & ((a + ~x + 1) >> 31));
  int bxs = (bxsc & (xs | bs)) | (~bxsc & ((b + ~x + 1) >> 31));
  
  return (!(a ^ x)) | (!(b ^ x)) | ((axs ^ bxs) & 1);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /* 计算 429496729 = 0x19999999 减去 x 的绝对值，直接求 -|x| 以避免 0x80000000 问题 */
  int s = ~(x >> 31);
  int r = (x << 2) + x;
  int a = (x ^ s) + (s & 1);
  
  int c = 0x19;
  c = c << 8 | 0x99;
  c = c << 8 | 0x99;
  c = c << 8 | 0x99;
  c = (c + a) >> 31;

  return (c & ((1 << 31) + s)) | (~c & r);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* 使用 32b + 29b 的数，需保证两部分同号 */
  int msk = ~(7 << 29);
  int s29b = (x & msk) + (y & msk) + (z & msk);
  int s32b = (x >> 29) + (y >> 29) + (z >> 29);

  int o = s29b >> 29;
  s32b = s32b + o;
  s29b = s29b + ~(o << 29) + 1;
  
  int has0 = !s29b | !s32b;
  int adjust = ((!has0 << 31) & (s29b ^ s32b)) >> 31;
  int s29bs = s29b >> 31;
  s32b = s32b + (adjust & s29bs);
  s29b = s29b + (adjust & (~(s29bs << 29) + 1));
  int s32bs = s32b >> 31;
  int ans0 = ((3 - s32b) >> 31) & 1;
  int ans1 = ((4 + s32b) >> 31) | (((!(4 ^ s32b) & !!s29b) << 31) >> 31);
  return (~s32bs & ans0) | (s32bs & ans1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  /* 实现的相当不优美，次正规数、e == 255的情况等需要分类讨论 */
  unsigned s = uf & 0x80000000, e = (uf >> 23) & 0xff, m = uf & 0x007fffff;
  if (e == 255 || (e == 0 && m == 0)) return uf;
  if (e >= 1) m = m | 0x00800000;
  m = m * 3;
  if (m >> 25)
  {
    m = m + 2;
    unsigned a = !(m & 3);
    m = m >> 2;
    m = m ^ (m & a);
    e = e + 1;
    if (e == 0xff) m = 0;
  }
  else
  {
    m = m + 1;
    unsigned a = !(m & 1);
    m = m >> 1;
    m = m ^ (m & a);
    if (e == 0 && (m >> 23)) e = e + 1;
  }
  return s | (e << 23) | (m & 0x007fffff);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  /* 先特判结果为 inf nan 0 的情况，然后再做 roundEvenPow2 */
  unsigned s = uf & 0x80000000, e = (uf >> 23) & 0xff, m = uf & 0x007fffff;
  if (e >= 150) return uf;
  if (e <= 125 || (e == 126 && m == 0)) return s;
  m = (m | 0x00800000) + (1 << (149 - e));
  if (m >> 24) // 至多 1 次，无需 while
  {
    m = m + (1 << (149 - e));
    unsigned msk = (1 << (151 - e)) - 1;
    unsigned a = !(m & msk);
    m = m >> (151 - e);
    m = m ^ (m & a);
    m = m << (150 - e);
    e = e + 1;
  }
  else
  {
    unsigned msk = (1 << (150 - e)) - 1;
    unsigned a = !(m & msk);
    m = m >> (150 - e);
    m = m ^ (m & a);
    m = m << (150 - e);
  }
  return s | (e << 23) | (m & 0x007fffff);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  /* 实现的相当不优美，先求出这个数的对数，分类讨论，对于 l > 23 的情况需 roundEvenPow2 */
  unsigned s = x & 0x80000000, e = 0, m = 0;
  unsigned y = x;
  if (s) y = -y;
  int l = -1;
  unsigned t = y;
  
  while (t) t = t >> 1, l = l + 1;
  // 可以通过枚举 16 8 4 2 1 做倍增，避免用 while，但是会多用 13 次运算
  // if (t >> 16) t = t >> 16, l = l + 16;
  // if (t >> 8) t = t >> 8, l = l + 8;
  // if (t >> 4) t = t >> 4, l = l + 4;
  // if (t >> 2) t = t >> 2, l = l + 2;
  // if (t >> 1) t = t >> 1, l = l + 1;
  
  if (l > 23)
  {
    m = y + (1 << (l - 24));
    if (l < 31 && m >> (l + 1)) // 至多 1 次，无需 while
    {
      m = m + (1 << (l - 24));
      l = l + 1;
    }
    unsigned msk = (1 << (l - 23)) - 1;
    unsigned a = !(m & msk);
    m = m >> (l - 23);
    m = m ^ (m & a);
    e = 127 + l;
  }
  else if (l >= 0)
  {
    m = y << (23 - l);
    e = 127 + l;
  }
  return s | (e << 23) | (m & 0x007fffff);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* 无需单独处理符号位，可以将 x 视作 32 个 1b 数，相邻 2 个 1b 数相加即可得到 16 个 2b 数，重复以上过程即可，创建0x55555555、0x33333333、0x0f0f0f0f 等 mask，mask 的构造可以一起做，从而降低次数 */
  int m16 = 0xff | (0xff << 8); 
  int m8 = m16 ^ (m16 << 8);
  int m4 = m8 ^ (m8 << 4);
  int m2 = m4 ^ (m4 << 2);
  int m1 = m2 ^ (m2 << 1);

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m4) + ((x >> 4) & m4);
  x = (x & m8) + ((x >> 8) & m8);
  x = (x & m16) + (x >> 16);
  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
  /* 类似 swapNibblePairs，多次创建 mask 然后做交换，mask 的构造可以一起做，从而降低次数 */
  int m16 = 0xff | (0xff << 8); 
  int m8 = m16 ^ (m16 << 8);
  int m4 = m8 ^ (m8 << 4);
  int m2 = m4 ^ (m4 << 2);
  int m1 = m2 ^ (m2 << 1);

  x = ((x & m1) << 1) | ((x >> 1) & m1);
  x = ((x & m2) << 2) | ((x >> 2) & m2);
  x = ((x & m4) << 4) | ((x >> 4) & m4);
  x = ((x & m8) << 8) | ((x >> 8) & m8);
  x = (x << 16) | ((x >> 16) & m16);
  return x;
}

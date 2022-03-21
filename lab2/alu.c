/**
* Integer Lab
* Starter Code and Sample Solution (c)2018-2019 Christopher A. Bohn (bohn-at-unl-dot-edu), University of Nebraska-Lincoln
*
* This is the only file students should edit.
*
* In this lab, students are required to implement integer arithmetic for unsigned 16-bit integers and signed (twos complement)
* 16-bit integers using only bitwise and (&), bitwise or (|), bitwise xor (^), bitwise complement (~), and bit shifts (<< and >>).
* DO NOT USE built-in addition (+), subtraction (-), multiplication (*), division (/), nor modulo (%).
*/

/**
* STUDENT:  Aryan Timla
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "alu.h"

/* Adds the two arguments and stores the sum in the return structure's result field.  If the operation overflowed then the
* overflow flag is set. */
addition_subtraction_result add( uint16_t augend, uint16_t addend ) {
  addition_subtraction_result addition;

  uint16_t result = augend ^ addend;
  uint16_t carry = augend & addend;
  while(carry != 0){
    uint16_t shiftcarry = carry << 1;
    carry = result & shiftcarry;
    result ^= shiftcarry;
  }
  addition.result = result;

  //Overflow check
  //for unsigned
  if (is_signed == false) {
    if (result < augend){
      addition.overflow = true;
    }else{
      addition.overflow = false;
    }
    // if (is_signed == false) {
    //   augend = augend >> 15;
    //   addend = addend >> 15;
    //   result = result >> 15;
    //   if (augend == 0x0000 && addend == 0x0000 && result == 0x0001){
    //     addition.overflow = true;
    //   }else if(augend == 0x0001 && addend == 0x0001 && result == 0x0000){
    //       addition.overflow = true;
    //   }else{
    //     addition.overflow = false;
    //   }
  }

  //for signed
  if (is_signed == true) {
    if(augend > 0 && addend > 0 && result < 0){
      addition.overflow = true;
    } else if(augend < 0 && addend < 0 && result > 0){
      addition.overflow = true;
    }else{
      addition.overflow = false;
    }
  }

  return addition;
}

/* Subtracts the second argument from the first, stores the difference in the return structure's result field.  If the
* operation overflowed then the overflow flag is set. */
addition_subtraction_result subtract( uint16_t menuend, uint16_t subtrahend ) {
  addition_subtraction_result subtraction;
  uint16_t sub = add((~subtrahend),1).result;
  uint16_t result = add(menuend,sub).result;
  subtraction.result = result;

  //Overflow check
  //for unsigned
  if (is_signed == false) {
    if (result > menuend){
      subtraction.overflow = true;
    }else{
      subtraction.overflow = false;
    }
  }

  //for signed
  if (is_signed == true) {
    if(menuend > 0 && subtrahend < 0 && result < 0){
      subtraction.overflow = true;
    } else if(menuend < 0 && subtrahend > 0 && result > 0){
      subtraction.overflow = true;
    }else{
      subtraction.overflow = false;
    }
  }

  return subtraction;
}


/* 32 bit addition
* Created as helper function to calculate full_product
*/
addition_subtraction_result add32(uint32_t augend, uint32_t addend) {
  addition_subtraction_result addition;
  uint32_t result = augend ^ addend;
  uint32_t carry = augend & addend;
  while(carry != 0){
    uint32_t shiftcarry = carry << 1;
    carry = result & shiftcarry;
    result ^= shiftcarry;
  }
  addition.result = result;
  return addition;
}


/* Multiplies the two arguments.  The function stores lowest 16 bits of the product in the return structure's product field and
* the full 32-bit product in the full_product field.  If the product doesn't fit in the 16-bit product field then the overflow
* flag is set. */
multiplication_result multiply( uint16_t multiplicand, uint16_t multiplier ) {
  multiplication_result multiplication;
  uint16_t result;
  //product calculation
  while (multiplier != 0) {
    if (multiplier & 1){
      result = add(result,multiplicand).result;
    }
    multiplicand <<= 1;
    multiplier >>= 1;
  }
  multiplication.product = result;



  //full_product calculation
  uint32_t fullresult;
  while (multiplier != 0) {
    if (multiplier & 1){
      fullresult = add32(fullresult,multiplicand).result;
    }
    multiplicand <<= 1;
    multiplier >>= 1;
  }
  multiplication.full_product = fullresult;

  return multiplication;
}

/* Divides the first argument by the second.  The function stores the quotient in the return structure's quotient field and the
* the quotient in the remainder field.  If the divisor is zero then the quotient and remainder fields should
* be ignored, and the division_by_zero field should be set. */
division_result divide( uint16_t dividend, uint16_t divisor ) {
  division_result division;
  // uint16_t quotient = 0;
  // uint16_t remainder = 0;
  // uint16_t subdiv;
  //Basic conditions
  if (divisor == 0) {
      division.division_by_zero = true;
    }
  if(is_signed == false){
    if (dividend == divisor) {
      division.quotient = 1;
      division.remainder = 0;
    } else if (dividend == 0) {
      division.quotient = 0;
      division.remainder = 0;
    }
  }

  //     } else if (dividend < divisor) {
  //   divisor >>= 1;
  //   quotient >>= 1;
  //   division.remainder = dividend;
  // }
  // while (divisor <= dividend) {
  //   divisor = divisor << 1;
  //   quotient = quotient << 1;
  // }
  // if(dividend < 0){
  //   subdiv = subtract(dividend,divisor).result;
  //   quotient = add(quotient,divide(subdiv,divisor).quotient).result;
  // }
  // }
  return division;
}

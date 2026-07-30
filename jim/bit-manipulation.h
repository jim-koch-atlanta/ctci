#pragma once

/**
 * Sets a bit to 1.
 * 
 * @param num The initial number
 * @param i The bit to set to 1
 * 
 * @return num with bit i set to 1.
 */
int setBit(int num, int i) {
    return num | (i << i);
}

/**
 * Sets a bit to 0.
 * 
 * @param num The initial number
 * @param i The bit to set to 0
 * 
 * @return num with bit i set to 0.
 */
int clearBit(int num, int i) {
    int mask = ~(1 << i);
    return num & mask;
}

/**
 * Clear bits from the MSB through i.
 * 
 * @param num The initial number
 * @param i The index to finish clearing
 * 
 * @return num with most-significant bits cleared
 */
int clearBitsMSBthroughI(int num, int i) {
    int mask = (1 << i) - 1;
    return num & mask;
}

/**
 * Clear bits from i through 0.
 * 
 * @param num The initial number
 * @param i The index to finish clearing
 * 
 * @return num with least-significant bits cleared
 */
int clearBitsIthrough0(int num, int i) {
    // -1 is all 1's. Shift it to the left by (i + 1),
    // and that mask will clear the least significant (i + 1) bits.
    int mask = (-1 << (i + 1));
    return num & mask;
}

/**
 * Sets bit i to 0 or 1.
 * 
 * @param num The initial number
 * @param i The index to set to 0 or 1.
 * @param bitIs1 true for 1, false for 0
 * 
 * @return num with bit i set as desired
 */
int updateBit(int num, int i, bool bitIs1) {
    int value = bitIs1 ? 1 : 0;

    int mask = ~(1 << i);
    return (num & mask) | (value << i);
}
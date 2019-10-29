//
// Created by tomer on 10/24/19.
//
#define MB 0

#include "n_bit_array.h"


BLOCK_TYPE n_bit_array::get_bits(size_t address, size_t length) {
    size_t aIndex = address / BLOCK_SIZE, bitIndex = address % BLOCK_SIZE;
    size_t bitsFromRight = MOD_INVERSE(bitIndex);
    BLOCK_TYPE res = A[aIndex];
    if (bitIndex + length < BLOCK_SIZE) {
        BLOCK_TYPE temp = ON((bitsFromRight + 1), (bitsFromRight + 1 - length));
        res &= temp;
        size_t shift_right = ++bitsFromRight - length;
        res >>= shift_right;
    } else if (bitIndex + length == BLOCK_SIZE) {
        res &= MASK(bitsFromRight + 1);
    } else {
        size_t temp_length = bitIndex + length - BLOCK_SIZE;
        res &= get_bits(address, length - temp_length);
        res <<= temp_length;
        res += get_bits((aIndex + 1) * BLOCK_SIZE, temp_length);
    }
    return res;
}

void n_bit_array::set_bits(size_t address, size_t bitsToWriteCounter, size_t value) {
    value &= MASK(bitsToWriteCounter);
    size_t aIndex = address / BLOCK_SIZE, bitIndex = address % BLOCK_SIZE;
    size_t rBitsCounter = MOD_INVERSE(bitIndex) + 1;

    if (bitIndex + bitsToWriteCounter < BLOCK_SIZE) {
        value <<= (BLOCK_SIZE - (bitIndex + bitsToWriteCounter));
        setHelp(aIndex, value, rBitsCounter, rBitsCounter - bitsToWriteCounter);
    } else if (bitIndex + bitsToWriteCounter == BLOCK_SIZE) {
        setHelp(aIndex, value, rBitsCounter, 0);
    } else {
        size_t exceedingBits = bitIndex + bitsToWriteCounter - BLOCK_SIZE;
        uint64_t firstVal = value >> exceedingBits;
        uint64_t secondVal = value & MASK(exceedingBits);
        secondVal <<= (BLOCK_SIZE - exceedingBits);
        setHelp(aIndex, firstVal, rBitsCounter, 0);
        if (exceedingBits > BLOCK_SIZE)
            set_bits((++aIndex) * BLOCK_SIZE, exceedingBits, secondVal);
        else
            setHelp(++aIndex, secondVal, BLOCK_SIZE, BLOCK_SIZE - exceedingBits);
    }
}


void n_bit_array::push(size_t start) {
}

void n_bit_array::pull(size_t start) {

}

void n_bit_array::get_cell(size_t q_index, BLOCK_TYPE *dataArray, size_t arraySize) {
    size_t address = q_index * (this->data_size + MB);
    for (int i = 0; i < arraySize - 1; ++i) {
        dataArray[i] = get_bits(address, BLOCK_SIZE);
        address += BLOCK_SIZE;
    }
    auto bitsLeft = (data_size + MB) % BLOCK_SIZE;
    dataArray[arraySize - 1] = get_bits(address, bitsLeft);
}

void n_bit_array::set_cell(size_t q_index, BLOCK_TYPE *dataArray, size_t arraySize) {
    size_t address = q_index * (this->data_size + MB);
    for (int i = 0; i < arraySize - 1; ++i) {
        set_bits(address, BLOCK_SIZE, dataArray[i]);
        address += BLOCK_SIZE;
    }
    auto bitsLeft = (data_size + MB) % BLOCK_SIZE;
    set_bits(address, bitsLeft, dataArray[arraySize - 1]);
}

void n_bit_array::set_cell(size_t q_index, BLOCK_TYPE *dataArray, size_t arraySize, BLOCK_TYPE tempMB) {
    size_t address = q_index * (this->data_size + MB);
    for (int i = 0; i < arraySize - 1; ++i) {
        set_bits(address, BLOCK_SIZE, dataArray[i]);
        address += BLOCK_SIZE;
    }
    auto bitsLeft = (data_size + MB) % BLOCK_SIZE;
    set_bits(address, bitsLeft, (dataArray[arraySize - 1] << MB) | tempMB);
}

void n_bit_array::set_bit(size_t address, bool setOn) {
    size_t aIndex, bitIndex, shift;
    bitIndex = address % BLOCK_SIZE;
    aIndex = address / BLOCK_SIZE;
    shift = MOD_INVERSE(bitIndex);
    size_t temp = (1ULL << shift);
    (setOn) ? A[aIndex] |= temp : A[aIndex] ^= temp;
}

void n_bit_array::setHelp(size_t aIndex, size_t value, size_t borderStart, size_t borderEnd) {
    A[aIndex] &= OFF(borderStart, borderEnd);
    value &= ON(borderStart, borderEnd);
    A[aIndex] |= value;
}

BLOCK_TYPE n_bit_array::getMB(size_t q_index) {
    size_t address = q_index * (data_size + MB) + data_size;
    return uint32_t(get_bits(address, MB));
}


bool n_bit_array::operator<(const n_bit_array &rhs) const {
    return A < rhs.A;
}

bool n_bit_array::operator>(const n_bit_array &rhs) const {
    return rhs < *this;
}

bool n_bit_array::operator<=(const n_bit_array &rhs) const {
    return !(rhs < *this);
}

bool n_bit_array::operator>=(const n_bit_array &rhs) const {
    return !(*this < rhs);
}


size_t n_bit_array::get_size() const {
    return size;
}

size_t n_bit_array::get_capacity() const {
    return capacity;
}

size_t n_bit_array::get_data_size() const {
    return data_size;
}

cmake_minimum_required(VERSION 3.15)
project(Clion_Code)

set(CMAKE_CXX_STANDARD 14)

add_executable(Clion_Code
        Bit_Array/BitArray.h Bit_Array/BitArray.cpp
        main.cpp Bit_Array/Naive_bit_array/n_bit_array.cpp Bit_Array/Naive_bit_array/n_bit_array.h PD/PD.cpp PD/PD.h PD/Header.cpp PD/Header.h PD/Body.cpp PD/Body.h bit_operations/bit_op.cpp bit_operations/bit_op.h Tests/Tests.cpp Tests/Tests.h Global_functions/basic_functions.cpp Global_functions/basic_functions.h)
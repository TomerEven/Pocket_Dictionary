cmake_minimum_required(VERSION 3.15)
project(Clion_Code)

set(CMAKE_CXX_STANDARD 14)
#SET(CMAKE_CXX_FLAGS "-O3")
#SET(CMAKE_C_FLAGS "-O3")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(Clion_Code
        Global_functions/basic_functions.cpp Global_functions/basic_functions.h
        Bit_Array/BitArray.h Bit_Array/BitArray.cpp

        Hash/Hash.h Hash/Hash.cpp
        Hash/MurmurHash3.h Hash/MurmurHash3.cpp

        PD/Header.cpp PD/Header.h
        PD/Body.cpp PD/Body.h
        PD/PD.cpp PD/PD.h

        Safe_PD/v_Header.cpp Safe_PD/v_Header.h
        Safe_PD/v_Body.cpp Safe_PD/v_Body.h
        Safe_PD/safe_PD.cpp Safe_PD/safe_PD.h

        Tests/validation_tests.cpp Tests/validation_tests.h
        Tests/old_benchmark_tests.cpp Tests/old_benchmark_tests.h
        Tests/benchmark_tests.cpp Tests/benchmark_tests.h

        Bit_Array/Naive_bit_array/n_bit_array.cpp Bit_Array/Naive_bit_array/n_bit_array.h
        bit_operations/bit_op.cpp bit_operations/bit_op.h
        main.cpp
        Simple_Crate/s_crate.cpp Simple_Crate/s_crate.h PD/spare_pd.cpp PD/spare_pd.h SID/SID.cpp SID/SID.h SID/CSD.cpp SID/CSD.h POW2C/pow2c_filter.cpp POW2C/pow2c_filter.h Hash/Permutation.cpp Hash/Permutation.h Naive_PD/naive_PD.cpp Naive_PD/naive_PD.h Naive_PD/naive_Header.cpp Naive_PD/naive_Header.h Naive_PD/naive_Body.cpp Naive_PD/naive_Body.h POW2C/pow2c_naive_filter.cpp POW2C/pow2c_naive_filter.h)
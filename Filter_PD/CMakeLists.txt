cmake_minimum_required(VERSION 3.10)
project(Filter_PD)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-O3")
SET(CMAKE_C_FLAGS "-O3")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(Filter_PD
        Global_functions/basic_functions.cpp Global_functions/basic_functions.h

        hash_util/Hash.h hash_util/Hash.cpp
        hash_util/MurmurHash3.h hash_util/MurmurHash3.cpp

        PD/Non_Contiguous_PD/Header.cpp PD/Non_Contiguous_PD/Header.h
        PD/Non_Contiguous_PD/Body.cpp PD/Non_Contiguous_PD/Body.h
        PD/Non_Contiguous_PD/PD.cpp PD/Non_Contiguous_PD/PD.h

        PD/Safe_PD/v_Header.cpp PD/Safe_PD/v_Header.h
        PD/Safe_PD/v_Body.cpp PD/Safe_PD/v_Body.h
        PD/Safe_PD/safe_PD.cpp PD/Safe_PD/safe_PD.h

        PD/Naive_PD/naive_PD.cpp PD/Naive_PD/naive_PD.h
        PD/Naive_PD/naive_Header.cpp PD/Naive_PD/naive_Header.h
        PD/Naive_PD/naive_Body.cpp PD/Naive_PD/naive_Body.h

        PD/Constant_size_PD/const_Header.cpp PD/Constant_size_PD/const_Header.h
        PD/Constant_size_PD/const_Body.cpp PD/Constant_size_PD/const_Body.h
        PD/Constant_size_PD/const_PD.cpp PD/Constant_size_PD/const_PD.h
        PD/Contiguous_PD/constant_contiguous_PD/cc_PD.cpp PD/Contiguous_PD/constant_contiguous_PD/cc_PD.h

        CPD/Naive_Counter_Endec.cpp CPD/Naive_Counter_Endec.hpp
        CPD/CPD.cpp CPD/CPD.hpp
        CPD/Counters_Array.cpp CPD/Counters_Array.hpp
        CPD/CPD_validator.cpp CPD/CPD_validator.hpp


        main.cpp

        Global_functions/macros.h Filters/POW2C/const_filter.cpp Filters/POW2C/const_filter.h
        Global_functions/cuckoo_and_counting_macros.hpp Tests/Validation/validate_counting_filter.cpp
        bit_operations/bit_word_converter.cpp bit_operations/bit_word_converter.hpp
        bit_operations/bit_op.cpp bit_operations/bit_op.h
        bit_operations/my_bit_op.cpp bit_operations/my_bit_op.hpp


        PD/Contiguous_PD/cg_PD.cpp PD/Contiguous_PD/cg_PD.h
        PD/Naive_PD/cg_naive_PD.cpp PD/Naive_PD/cg_naive_PD.h
        hash_util/static_hashing.h
        #        hash_util/hashutil_backup/lookup3.h
        hash_util/Permutation.cpp hash_util/Permutation.h

        Hash_Table/multi_hash_table.hpp
        Hash_Table/hash_table_var.cpp Hash_Table/hash_table_var.hpp
        Hash_Table/hash_table.cpp Hash_Table/hash_table.hpp

        Filters/POW2C/gen_2Power.cpp Filters/POW2C/gen_2Power.h
        Filters/POW2C/pow2c_filter.cpp Filters/POW2C/pow2c_filter.h
        Filters/POW2C/pow2c_naive_filter.cpp Filters/POW2C/pow2c_naive_filter.h
        Filters/Dict/dict.cpp Filters/Dict/dict.hpp
        Filters/Dict/multi_dict.cpp Filters/Dict/multi_dict.hpp


        Tests/Validation/validate_bit_op.cpp Tests/Validation/validate_bit_op.hpp
        Tests/Validation/validate_counters.cpp Tests/Validation/validate_counters.hpp
        Tests/Validation/validate_hash_table.cpp Tests/Validation/validate_hash_table.hpp

        Tests/Validation/validate_filter.cpp Hash_Table/multi_hash_table.cpp
        Tests/Validation/validate_counter_PD.cpp Tests/Validation/validate_counter_PD.hpp
        Tests/Validation/validation_tests.cpp Tests/Validation/validation_tests.h
        Tests/Validation/validate_filter.hpp
        Tests/Validation/validate_counting_filter.hpp

        Tests/Benchmarking/benchmark_tests.cpp Tests/Benchmarking/benchmark_tests.h
        Tests/Benchmarking/benchmark_counting_filter.cpp Tests/Benchmarking/benchmark_counting_filter.hpp
        Tests/Test_output_formatting/test_printer.cpp Tests/Test_output_formatting/test_printer.hpp

        )



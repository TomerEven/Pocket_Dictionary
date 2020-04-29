//
// Created by tomer on 4/12/20.
//
#include "test_printer.hpp"

namespace name_compare {

    void table_print_rates(size_t var_num, string *var_names, size_t *values, size_t *divisors) {
        size_t max_length = 0;
        for (int i = 0; i < var_num; ++i) {
            max_length = max(var_names[i].length(), max_length);
        }



        // values for controlling format
        const uint32_t name_width = int(max_length);
        const int int_width = 7;
        const int dbl_width = 12;
        const int num_flds = 7;
        const std::string sep = " |";
        const uint32_t total_width = name_width * 2u + int_width * 2u + dbl_width * 3u + sep.size() * num_flds;
        const std::string line = sep + std::string(total_width - 1, '-') + '|';
        std::cout << line << '\n' << sep << left;

        const std::string spacing = std::string(name_width, ' ');
//        std::string header =
//                line + '\n' + sep + spacing + "var " + sep + spacing + "value";

        const size_t column_num = 4;
        string columns[column_num] = {"var_name", "ratio", "actual value", "divider"};
        size_t counter = 0;
        while (counter < column_num - 1) {
            cout << std::setw(name_width) << columns[counter++] << sep;
        }
        cout << std::setw(name_width) << columns[counter] << std::string(4, ' ') << sep;
        /*cout << std::setw(name_width) << "ratio " << sep;
        cout << std::setw(name_width) << "actual value" << sep;
        cout << std::setw(name_width) << "divider" << sep;
//        for (const auto &column : columns) {
//            cout << std::setw(name_width) << column << sep;
//        }*/
        cout << '\n' << line << '\n';

//    assert(var_num % column_num == 0);
        for (int i = 0; i < var_num; ++i) {
            std::cout << sep << std::setw(name_width) << var_names[i];
            double rate = divisors[i] / (values[i] / 1e6);
            std::cout << sep << std::setw(name_width) << rate;
            std::cout << sep << std::setw(name_width) << divisors[i];
            std::cout << sep << std::setw(name_width) << values[i];
            auto temp_length = total_width - name_width * column_num;
            assert (temp_length > 0);
            std::cout << std::string(4, ' ') << sep << '\n';
        }
        std::cout << line << endl;

    }

    void
    table_print_false_positive_rates(size_t expected_FP_count, size_t high_load_FP_count, size_t mid_load_FP_count) {
        /*const auto var_num = 9;
            string var_names[var_num] = {"start", "start_array_index", "start_bit_pos",
                                         "end", "end_array_index", "end_bit_pos",
                                         "new_end", "new_end_array_index", "new_end_bit_pos"};
            size_t values[var_num] = {start, start / slot_size, start % slot_size,
                                      end, end / slot_size, end % slot_size,
                                      new_end, new_end / slot_size, new_end % slot_size};

            size_t max_length = 0;
            for (auto & var_name : var_names) {
                max_length = max(var_name.length(), max_length);
            }*/
        size_t var_num = 3;
        string names[3] = {"expected_FP_count", "high_load_FP_count", "mid_load_FP_count"};
        size_t values[3] = {expected_FP_count, high_load_FP_count, mid_load_FP_count};
        size_t max_length = 0;
        for (int i = 0; i < var_num; ++i) {
            max_length = max(names[i].length(), max_length);
        }

        // values for controlling format
        const int name_width = int(max_length);
        const int int_width = 7;
        const int dbl_width = 12;
        const int num_flds = 7;
        const std::string sep = " |";
        const int total_width = name_width * 2 + int_width * 2 + dbl_width * 3 + sep.size() *
                                                                                 num_flds; // NOLINT(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
        const std::string line = sep + std::string(total_width - 1, '-') + '|';
        const std::string spacing = std::string(name_width, ' ');
        std::string header =
                line + '\n' + sep + spacing + "var " + sep + spacing + "value";
        size_t spaces_to_add = total_width - header.size();
        header += std::string(spaces_to_add, ' ') + sep + '\n' + line + '\n';

        std::cout << header;
//        std::cout << line << '\n' << sep << std::setw(name_width) << left << "var " << sep << std::setw(name_width)
//                  << "value"
//                  << sep << '\n' << line << '\n';

        for (int i = 0; i < var_num; ++i) {
            std::string temp_line = sep + spacing + names[i] + sep + spacing + to_string(values[i]);
            size_t temp_spaces_to_add = total_width - temp_line.size();
            temp_line += std::string(temp_spaces_to_add, ' ') + sep + '\n';
            std::cout << temp_line;

//            std::cout << sep << std::setw(name_width) << names[i] << sep << std::setw(name_width) << values[i]
//                      << sep
//                      << '\n';
        }
        std::cout << line << endl;


    }
}



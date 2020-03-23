//
// Created by tomer on 10/25/19.
//

#include "basic_functions.h"


template<typename T>
void print_array_as_integers(T *a, size_t size) {
    cout << "[" << (int) a[0];
    for (size_t i = 1; i < size; ++i) {
        cout << ", " << (int) a[i];
    }
    cout << "]" << endl;
}

void print_array(uint8_t *a, size_t a_size) {
    cout << "[" << (int) a[0];
    for (size_t i = 1; i < a_size; ++i) {
        cout << ", " << (int) a[i];
    }
    cout << "]" << endl;

}


void print_array(int *a, size_t a_size) {
    cout << "[" << a[0];
    for (size_t i = 1; i < a_size; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;

}

void print_array(uint32_t *a, size_t a_size) {
    cout << "[" << a[0];
    for (size_t i = 1; i < a_size; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;

}

void print_bool_array(bool *a, size_t a_size) {
    cout << "[" << a[0];
    for (size_t i = 0; i < a_size; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;
}

template<typename T>
ostream &print_array_as_consecutive_memory(T *a, size_t size, ostream &os) {
    for (size_t i = 0; i < size; ++i) {
        os << my_bin(a[i]);
    }
    os << endl;
    return os;
}


void print_array_as_consecutive_memory(const uint32_t *a, size_t a_size) {
    for (size_t i = 0; i < a_size; ++i) {
        cout << my_bin(a[i]);
    }
    cout << endl;
}

void print_vector(vector<int> *v) {
    cout << "[" << v->at(0);
    for (size_t i = 1; i < v->size(); ++i) {
        cout << ", " << v->at(i);
    }
    cout << "]" << endl;

}

void print_vector(vector<bool> *v) {
    cout << "[" << v->at(0);
    for (size_t i = 1; i < v->size(); ++i) {
        cout << ", " << v->at(i);
    }
    cout << "]" << endl;

}

void print_vector_by_unpacking(vector<bool> *v, size_t unpack_size) {
    size_t a_size = v->size() / unpack_size + (v->size() % unpack_size != 0);
    uint32_t a[a_size];
    assert(unpack_size <= 32);
    for (size_t i = 0; i < a_size; ++i) {
        a[i] = read_FP_from_vector_by_index(v, i * unpack_size, unpack_size);
    }
    print_array(a, a_size);
}

void print_vector_as_words(const vector<bool> *v) {
    size_t number_of_words = (v->size() / 32) + (v->size() % 32 != 0);
    uint32_t a[number_of_words];
    for (size_t j = 0; j < number_of_words; ++j) {
        a[j] = 0;
    }
    vector_to_word_array(v, a, number_of_words);

    print_array(a, number_of_words);
    /*cout << "[" << a[0];
    for (size_t i = 1; i < number_of_words; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;*/
}

void print_bool_vector_no_spaces(const vector<bool> *v) {
    for (auto b : *v)
        cout << b;
    cout << endl;
}

void to_vector(vector<bool> *vec, const uint32_t *a, size_t a_size) {
    size_t slot_size = (sizeof(a[0]) * 8);
    size_t vec_new_size = slot_size * a_size, vec_index = 0;
    vec->resize(vec_new_size);
    for (size_t i = 0; i < a_size; ++i) {
        size_t b = 1ULL << (slot_size - 1);
        for (size_t j = 0; j < slot_size; ++j) {
            vec->at(vec_index) = (b & a[i]);
            b >>= 1ULL;
            vec_index++;
        }
    }
}

void to_vector(vector<bool> *vec, const uint8_t *a, size_t a_size) {
    size_t bit_in_slot = (sizeof(a[0]) * 8);
    size_t vec_new_size = bit_in_slot * a_size, vec_index = 0;
    vec->resize(vec_new_size);
    for (size_t i = 0; i < a_size; ++i) {
        size_t b = 1ULL << (bit_in_slot - 1);
        for (size_t j = 0; j < bit_in_slot; ++j) {
            vec->at(vec_index) = (b & a[i]);
            b >>= 1ULL;
            vec_index++;
        }
    }
}

void vector_to_word_array(const vector<bool> *v, uint32_t *a, size_t a_size) {
    size_t expected_size = (v->size() / 32) + (v->size() % 32 != 0);
    assert(a_size == expected_size);
    for (size_t i = 0; i < a_size - 1; ++i) {
        ulong b = (1ul << 31ul);
        for (int j = 0; j < 32; ++j) {
            assert(b > 0);
            if (v->at(32 * i + j)) {
                a[i] |= b;
            }
            b >>= 1ul;
        }
    }
    ulong b = (1ul << 31ul);
    for (size_t k = 0; k < v->size() % 32; ++k) {
        if (v->at(32 * (a_size - 1) + k)) {
            a[a_size - 1] |= b;
        }
        b >>= 1ul;
    }
}

auto read_FP_from_vector_by_index(const vector<bool> *v, size_t bit_start_index, size_t fp_size) -> uint32_t {
    assert(bit_start_index + fp_size <= v->size());

//    BODY_BLOCK_TYPE res = v->at(bit_start_index);
    uint32_t res = 0;
    for (size_t i = 0; i < fp_size; ++i) {
        res <<= 1ul;
        res |= v->at(bit_start_index + i);
    }
    return res;
}

void write_FP_to_vector_by_index(vector<bool> *v, size_t index, uint32_t remainder, size_t fp_size) {
    assert(index + fp_size <= v->size());

    ulong b = 1ULL << (fp_size - 1);
    for (size_t i = 0; i < fp_size; ++i) {
        v->at(index + i) = (remainder & b) != 0;
        b >>= 1ul;
    }
}

template<typename T>
string my_bin(T n, size_t length) {
    string s;
    ulong shift = sizeof(T) * CHAR_BIT;
    ulong b = 1ull << (ulong) (32 - 1);
    for (int i = 0; i < 32; ++i) {
        if (b & n)
            s.append("1");
        else
            s.append("0");
        b >>= 1ul;
    }
    return s;
}


string my_bin(size_t n, size_t length) {
    string s;
    ulong b = 1ull << (ulong) (32 - 1);
    for (int i = 0; i < 32; ++i) {
        if (b & n)
            s.append("1");
        else
            s.append("0");
        b >>= 1ul;
    }
//    cout << s << endl;
    return s;
}

int compare_vector_and_array(const vector<bool> *v, const uint8_t *a) {
    size_t size = min(v->size(), sizeof(a) / sizeof(a[0]));
    size_t step = sizeof(a[0]) * sizeof(char);
    for (size_t i = 0; i < size; i += step) {
        if (a[i] != read_FP_from_vector_by_index(v, i, step)) return i;
    }
    return -1;

}

int compare_vector_and_array(const vector<bool> *v, const uint32_t *a) {
    size_t size = min(v->size(), sizeof(a) / sizeof(a[0]));
    size_t step = sizeof(a[0]) * sizeof(char);
    for (size_t i = 0; i < size; i += step) {
        if (a[i] != read_FP_from_vector_by_index(v, i, step)) return i;
    }
    return -1;
}

string to_sci(double x, int add_to_counter, size_t precision) {
    if (x == 0) { return "0E0"; }
    if (x < 0) { return "-" + to_sci(-x); }
    if (round(x) == x) { return to_sci(x - 1e-5); }

    string temp = to_string(x);
    auto dot_index = temp.find('.');
    assert(temp.find('.') != -1);

    if (dot_index == 1) {
        if (temp[0] != '0') {
            return temp.substr(0, precision + 2) + "E" + to_string(add_to_counter);
        }
        int counter = 0;
        while (x < 1) {
            x *= 10;
            counter--;
        }
        return to_sci(x, counter, precision);

        /*
        auto counter = 1;
        for (int i = 2; i < temp.length(); ++i) {
            if (temp[i] == '0')
                counter++;
            else
                break;
        }

        string res = (to_string(temp[counter + 2]) + ".") + temp.substr(counter + 3, counter + 3 + precision);
        res += "E-" + to_string(counter + add_to_counter);
        return res;*/
    }

    size_t counter = 0;
    while (x > 10) {
        x /= 10;
        counter++;
    }
    return to_sci(x, counter, precision);

}


int loglog2(int x) {
    log(x);
}


void formatting() {
    /*Taken from http://www.cplusplus.com/forum/beginner/181119/*/
    // arbitrary test data, test repeats the same data thrice
    std::string fname = "Ebenezer";
    std::string lname = "Scrooge";
    int hourWork = 23;
    int hourRate = 5;
    double gp = 123.48501;
    double taxamt = 2.4392;
    double netpay = 121.04579;

    // values for controlling format
    const int name_width = 15;
    const int int_width = 7;
    const int dbl_width = 12;
    const int num_flds = 7;
    const std::string sep = " |";
    const int total_width = name_width * 2 + int_width * 2 + dbl_width * 3 + sep.size() * num_flds;
    const std::string line = sep + std::string(total_width - 1, '-') + '|';

    std::cout << line << '\n' << sep
              << std::setw(name_width) << "var " << sep << std::setw(name_width) << "last name" << sep
              << std::setw(int_width) << "hours" << sep << std::setw(int_width) << "rate" << sep
              << std::setw(dbl_width) << "gross pay" << sep << std::setw(dbl_width) << "tax" << sep
              << std::setw(dbl_width) << "net pay" << sep << '\n' << line << '\n';

    for (int i = 0; i < 3; ++i) {
        std::cout << sep << std::setw(name_width) << fname << sep << std::setw(name_width) << lname << sep
                  << std::setw(int_width) << hourWork << sep << std::setw(int_width) << hourRate << sep
                  << std::fixed << std::setprecision(2)
                  << std::setw(dbl_width) << gp << sep << std::setw(dbl_width) << taxamt << sep
                  << std::setw(dbl_width) << netpay << sep << '\n';
    }
    std::cout << line << '\n';
}

void table_print(size_t var_num, string *var_names, size_t *values) {
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
    size_t max_length = 0;
    for (int i = 0; i < var_num; ++i) {
        max_length = max(var_names[i].length(), max_length);
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
    std::cout << line << '\n' << sep << std::setw(name_width) << left << "var " << sep << std::setw(name_width)
              << "value"
              << sep << '\n' << line << '\n';

    for (int i = 0; i < var_num; ++i) {
        std::cout << sep << std::setw(name_width) << var_names[i] << sep << std::setw(name_width) << values[i] << sep
                  << '\n';
    }
    std::cout << line << endl;

}

void table_print_columns(size_t var_num, size_t column_num, string *var_names, string *columns, size_t *values) {
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
    size_t max_length = 0;
    for (int i = 0; i < var_num; ++i) {
        max_length = max(var_names[i].length(), max_length);
    }
    for (int k = 0; k < column_num; ++k) {
        max_length = max(columns[k].length(), max_length);
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
    std::cout << line << '\n' << sep << left;
    cout << std::setw(name_width) << "var_name" << sep;
    for (int j = 0; j < column_num; ++j) {
        cout << std::setw(name_width) << columns[j] << sep;
    }
    cout << '\n' << line << '\n';

    assert(var_num % column_num == 0);
    for (int i = 0; i < var_num; ++i) {
        std::cout << sep << std::setw(name_width) << var_names[i];

        for (int j = 0; j < column_num; ++j) {
            auto index = i * column_num + j;
            std::cout << sep << std::setw(name_width) << values[index];
        }
        std::cout << '\n';

    }
    std::cout << line << endl;

}


template void print_array_as_integers<uint32_t>(uint32_t *a, size_t size);

template string my_bin<uint32_t>(uint32_t n, size_t length);

template ostream &print_array_as_consecutive_memory<uint32_t>(uint32_t *a, size_t size, ostream &os);
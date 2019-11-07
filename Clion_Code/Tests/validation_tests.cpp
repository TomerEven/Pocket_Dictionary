//
// Created by tomer on 10/25/19.
//

#include "validation_tests.h"
#include "benchmark_tests.h"

bool t1(bool to_print) {
    size_t m = 16, f = 8, l = 5;
    PD d = PD(m, f, l);
    if (to_print) {
        cout << "start print:\n";
        d.print();
        cout << endl;
    }
    for (int i = 0; i < 8; ++i) {
        size_t q = i / 2;
        FP_TYPE r = i + 1;
        d.insert(q, r);
//        d.print();
//        cout << endl;
        if (to_print) { d.print(); }
        if (not d.lookup(q, r)) {
            cout << i << " index failed." << endl;
            d.print();
            d.lookup(q, r);
            return false;
        }
//        cout << i << " finished.\n$$$\n" << endl;
    }
    cout << "Passed t1!" << endl;
    return true;
}

bool t2(bool to_print) {
    size_t m = 16, f = 8, l = 5;
    PD d = PD(m, f, l);
//    cout << "start print:\n";
//    d.print();
//    cout << endl;
    for (int i = 0; i < 8; ++i) {
        size_t q = i / 2;
        FP_TYPE r = i + 1;
        d.insert(q, r);
        if (to_print) {
            cout << i << "\t";
            d.print();
        }
        if (not d.lookup(q, r)) {
            cout << i << " lookup failed." << endl;
            return false;
        }
        d.remove(q, r);
        if (to_print) {
            cout << i << "\t";
            d.print();
        }
        if (d.lookup(q, r)) {
            cout << i << " lookup after deletion failed." << endl;
            return false;
        }
    }
    cout << "Passed t2!" << endl;
    return true;
}

bool t3(bool to_print) {
    size_t m = 16, f = 8, l = 5;
    PD d = PD(m, f, l);
    for (int i = 0; i < 8; ++i) {
        size_t q = i / 2;
        FP_TYPE r = i + 1;
        d.insert(q, r);
        if (to_print) {
            cout << i << "\t";
            d.print();
        }
        if (not d.lookup(q, r)) {
            cout << i << " lookup failed." << endl;
            return false;
        }
    }
    if (to_print) { cout << "insertion done!" << endl; }
    for (int i = 0; i < 8; ++i) {
        size_t q = i / 2;
        FP_TYPE r = i + 1;
        d.remove(q, r);
        if (to_print) {
            cout << i << "\t";
            d.print();
        }
        if (d.lookup(q, r)) {
            cout << i << " lookup failed." << endl;
            return false;
        }
    }


//    return true;



    /*d.remove(q, r);
    if (to_print) {
        cout << i << "\t";
        d.print();
    }
    if (d.lookup(q, r)) {
        cout << i << " lookup after deletion failed." << endl;
        return false;
    }*/
    cout << "Passed t3!" << endl;
    return true;
}

bool t4(bool to_print) {
    size_t m = 16, f = 8, l = 5;
    PD d = PD(m, f, l);
    for (int i = 8; i > 0; --i) {
        size_t q = (i - 1) / 2;
        FP_TYPE r = i;
        d.insert(q, r);
        if (to_print) {
            cout << i << "\t";
            d.print();
        }
        if (not d.lookup(q, r)) {
            cout << i << " lookup failed." << endl;
            return false;
        }
    }
    if (to_print) { cout << "insertion done!" << endl; }
    for (int i = 0; i < 8; ++i) {
        size_t q = i / 2;
        FP_TYPE r = i + 1;
        if (not d.lookup(q, r)) {
            cout << i << " lookup before failed." << endl;
            return false;
        }
        d.remove(q, r);
        if (to_print) {
            cout << i << "\t";
            d.print();
        }
        if (d.lookup(q, r)) {
            cout << i << " lookup after failed." << endl;
            return false;
        }
    }
    cout << "Passed t4!" << endl;
    return true;
}

bool t5(size_t m, size_t f, size_t l, bool to_print) {
    assert(f < (1ULL << l));
    PD d = PD(m, f, l);
    for (int i = f; i > 0; --i) {
        size_t q = (i - 1) / 2;
        FP_TYPE r = i;
        d.insert(q, r);
        if (to_print) {
            cout << i << "\t";
            d.print();
        }
        if (not d.lookup(q, r)) {
            cout << i << " lookup failed." << endl;
            return false;
        }
    }
    if (to_print) { cout << "insertion done!" << endl; }
    for (int i = 0; i < f; ++i) {
        size_t q = i / 2;
        FP_TYPE r = i + 1;
        if (not d.lookup(q, r)) {
            cout << i << " lookup before failed." << endl;
            return false;
        }
        d.remove(q, r);
        if (to_print) {
            cout << i << "\t";
            d.print();
        }
        if (d.lookup(q, r)) {
            cout << i << " lookup after failed." << endl;
            return false;
        }
    }
    cout << "Passed t5!" << endl;
    return true;
}

bool r0(size_t reps, bool to_print) {
    size_t f = rand() % (256 - 32) + 32;
    size_t m = f + 1 + (rand() % (f - 1));
    size_t l = 11 + (rand() % (31 - 11));

    PD d = PD(m, f, l);


    if (to_print) {
        cout << "m is: " << m << endl;
        cout << "f is: " << f << endl;
        cout << "l is: " << l << endl;
    }

    return r0_core(reps, &d, m, f, l, to_print);
    return false;
}

template<class T>
bool r0_core_template(size_t reps, T *d, size_t m, size_t f, size_t l, bool to_print) {
    vector<int> in_q(0), out_q(f), in_r(0), out_r(f);

    for (int i = 0; i < f; ++i) {
        out_q[i] = rand() % m;
        out_r[i] = rand() % SL(l - 1);
    }

    for (size_t i = 0; i < reps; ++i) {
        if (to_print) { cout << i << "\t"; }
        if (rand() % 2) {
            if (out_q.empty()) {
                if (to_print) { cout << "emp" << endl; }
                continue;
            }
            if (to_print) { cout << "in" << endl; }

            size_t index = rand() % out_q.size();
            size_t q = out_q[index], r = out_r[index];
            if (d->lookup(q, r)) {
                d->lookup(q, r);
                auto it = find(in_q.begin(), in_q.end(), q);
                if (it != in_q.end()) {
                    size_t index = distance(in_q.begin(), it);
                    if (in_q[index] != r) {
                        cout << "case 1 fail " << i << endl;
                        return false;
                    }
                } else {
                    cout << "case 1 fail " << i << endl;
                    return false;
                }

            }
            d->insert(q, r);
            if (not d->lookup(q, r)) {
                d->lookup(q, r);
                cout << "case 2 fail " << i << endl;
                return false;
            }

            in_q.push_back(q);
            in_r.push_back(r);

            out_q.erase(out_q.begin() + index);
            out_r.erase(out_r.begin() + index);


        } else {
            if (in_q.empty()) {
                if (to_print) { cout << "emp" << endl; }
                continue;
            }

            size_t index = rand() % in_q.size();
            size_t q = in_q[index], r = in_r[index];
            if (to_print) { cout << "del\t" << endl; }

            if (not d->lookup(q, r)) {
                d->lookup(q, r);
                cout << "case 3 fail " << i << endl;
                return false;
            }

            d->remove(q, r);
            if (d->lookup(q, r)) {
                d->lookup(q, r);
                cout << "case 4 fail " << i << endl;
                return false;
            }


            out_q.push_back(q);
            out_r.push_back(r);

            in_q.erase(in_q.begin() + index);
            in_r.erase(in_r.begin() + index);
        }
    }
    cout << "r0 passed" << endl;
    return true;

}

bool r0_core(size_t reps, PD *d, size_t m, size_t f, size_t l, bool to_print) {
    vector<int> in_q(0), out_q(f), in_r(0), out_r(f);

    for (int i = 0; i < f; ++i) {
        out_q[i] = rand() % m;
        out_r[i] = rand() % SL(l - 1);
    }

    for (size_t i = 0; i < reps; ++i) {
        if (to_print) { cout << i << "\t"; }
        if (rand() % 2) {
            if (out_q.empty()) {
                if (to_print) { cout << "emp" << endl; }
                continue;
            }
            if (to_print) { cout << "in" << endl; }

            size_t index = rand() % out_q.size();
            size_t q = out_q[index], r = out_r[index];
            if (d->lookup(q, r)) {
                d->lookup(q, r);
                auto it = find(in_q.begin(), in_q.end(), q);
                if (it != in_q.end()) {
                    size_t index = distance(in_q.begin(), it);
                    if (in_q[index] != r) {
                        cout << "case 1 fail " << i << endl;
                        return false;
                    }
                } else {
                    cout << "case 1 fail " << i << endl;
                    return false;
                }

            }
            d->insert(q, r);
            if (not d->lookup(q, r)) {
                d->lookup(q, r);
                cout << "case 2 fail " << i << endl;
                return false;
            }

            in_q.push_back(q);
            in_r.push_back(r);

            out_q.erase(out_q.begin() + index);
            out_r.erase(out_r.begin() + index);


        } else {
            if (in_q.empty()) {
                if (to_print) { cout << "emp" << endl; }
                continue;
            }

            size_t index = rand() % in_q.size();
            size_t q = in_q[index], r = in_r[index];
            if (to_print) { cout << "del\t" << endl; }

            if (not d->lookup(q, r)) {
                d->lookup(q, r);
                cout << "case 3 fail " << i << endl;
                return false;
            }

            d->remove(q, r);
            if (d->lookup(q, r)) {
                d->lookup(q, r);
                cout << "case 4 fail " << i << endl;
                return false;
            }


            out_q.push_back(q);
            out_r.push_back(r);

            in_q.erase(in_q.begin() + index);
            in_r.erase(in_r.begin() + index);
        }
    }
    cout << "r0 passed" << endl;
    return true;

}

bool s0(size_t reps, bool to_print) {
    size_t f = rand() % (256 - 32) + 32;
    size_t m = f + 1 + (rand() % (f - 1));
    size_t l = 11 + (rand() % (31 - 11));

    safe_PD d = safe_PD(m, f, l);
    if (to_print) {
        cout << "m is: " << m << endl;
        cout << "f is: " << f << endl;
        cout << "l is: " << l << endl;
    }
    vector<int> in_q(0), out_q(f), in_r(0), out_r(f);

    for (int i = 0; i < f; ++i) {
        out_q[i] = rand() % m;
        out_r[i] = rand() % SL(l - 1);
    }

    for (size_t i = 0; i < reps; ++i) {
        if (to_print) { cout << i << "\t"; }
        if (rand() % 2) {
            if (out_q.empty()) {
                if (to_print) { cout << "emp" << endl; }
                continue;
            }
            if (to_print) { cout << "in" << endl; }

            size_t index = rand() % out_q.size();
            size_t q = out_q[index], r = out_r[index];
            if (d.lookup(q, r)) {
                d.lookup(q, r);
                auto it = find(in_q.begin(), in_q.end(), q);
                if (it != in_q.end()) {
                    size_t index = distance(in_q.begin(), it);
                    if (in_q[index] != r) {
                        cout << "case 1 fail " << i << endl;
                        return false;
                    }
                } else {
                    cout << "case 1 fail " << i << endl;
                    return false;
                }

            }
            d.insert(q, r);
            if (not d.lookup(q, r)) {
                d.lookup(q, r);
                cout << "case 2 fail " << i << endl;
                return false;
            }

            in_q.push_back(q);
            in_r.push_back(r);

            out_q.erase(out_q.begin() + index);
            out_r.erase(out_r.begin() + index);


        } else {
            if (in_q.empty()) {
                if (to_print) { cout << "emp" << endl; }
                continue;
            }

            size_t index = rand() % in_q.size();
            size_t q = in_q[index], r = in_r[index];
            if (to_print) { cout << "del\t" << endl; }

            if (not d.lookup(q, r)) {
                d.lookup(q, r);
                cout << "case 3 fail " << i << endl;
                return false;
            }

            d.remove(q, r);
            if (d.lookup(q, r)) {
                d.lookup(q, r);
                cout << "case 4 fail " << i << endl;
                return false;
            }


            out_q.push_back(q);
            out_r.push_back(r);

            in_q.erase(in_q.begin() + index);
            in_r.erase(in_r.begin() + index);
        }
    }
    cout << "s0 passed" << endl;
    return true;

}

bool r1(size_t reps, bool to_print) {
    default_random_engine generator;
    uniform_int_distribution<int> f_dist(32, 256);
    size_t f = f_dist(generator);
    uniform_int_distribution<int> m_dist(f + 1, f << 1);
    size_t m = m_dist(generator);
    uniform_int_distribution<int> l_dist(11, 31);
    size_t l = l_dist(generator);

    cout << "m is: " << m << endl;
    cout << "f is: " << f << endl;
    cout << "l is: " << l << endl;


    uniform_int_distribution<int> remainder_dist(0, MASK((l - 1)));
    uniform_int_distribution<int> quotient_dist(0, m - 1);
    vector<int> in_q(0), out_q(f), in_r(0), out_r(f);
    for (int i = 0; i < f; ++i) {
        in_q[i] = quotient_dist(generator);
        in_r[i] = remainder_dist(generator);
    }

    for (size_t i = 0; i < reps; ++i) {
        if (rand() % 2) {
            if (!out_q.size())
                continue;

            size_t index = rand() % out_q.size();
//            d.in
        }
    }



//    uint m = uniform_int_distribution<int> distribution(32, 256);

}

bool naive_pd_r0(size_t reps, bool to_print) {

    size_t f = rand() % (256 - 32) + 32;
    size_t m = f + 1 + (rand() % (f - 1));
    size_t l = 11 + (rand() % (31 - 11));

    naive_PD d = naive_PD(m, f, l);
    if (to_print) {
        cout << "m is: " << m << endl;
        cout << "f is: " << f << endl;
        cout << "l is: " << l << endl;
    }
    vector<int> in_q(0), out_q(f), in_r(0), out_r(f);

    for (int i = 0; i < f; ++i) {
        out_q[i] = rand() % m;
        out_r[i] = rand() % SL(l - 1);
    }

    for (size_t i = 0; i < reps; ++i) {
        if (to_print) { cout << i << "\t"; }
        if (rand() % 2) {
            if (out_q.empty()) {
                if (to_print) { cout << "emp" << endl; }
                continue;
            }
            if (to_print) { cout << "in" << endl; }

            size_t index = rand() % out_q.size();
            size_t q = out_q[index], r = out_r[index];
            if (d.lookup(q, r)) {
                d.lookup(q, r);
                auto it = find(in_q.begin(), in_q.end(), q);
                if (it != in_q.end()) {
                    size_t index = distance(in_q.begin(), it);
                    if (in_q[index] != r) {
                        cout << "case 1 fail " << i << endl;
                        return false;
                    }
                } else {
                    cout << "case 1 fail " << i << endl;
                    return false;
                }

            }
            d.insert(q, r);
            if (not d.lookup(q, r)) {
                d.lookup(q, r);
                cout << "case 2 fail " << i << endl;
                return false;
            }

            in_q.push_back(q);
            in_r.push_back(r);

            out_q.erase(out_q.begin() + index);
            out_r.erase(out_r.begin() + index);


        } else {
            if (in_q.empty()) {
                if (to_print) { cout << "emp" << endl; }
                continue;
            }

            size_t index = rand() % in_q.size();
            size_t q = in_q[index], r = in_r[index];
            if (to_print) { cout << "del\t" << endl; }

            if (not d.lookup(q, r)) {
                d.lookup(q, r);
                cout << "case 3 fail " << i << endl;
                return false;
            }

            d.remove(q, r);
            if (d.lookup(q, r)) {
                d.lookup(q, r);
                cout << "case 4 fail " << i << endl;
                return false;
            }


            out_q.push_back(q);
            out_r.push_back(r);

            in_q.erase(in_q.begin() + index);
            in_r.erase(in_r.begin() + index);
        }
    }
    cout << "naive_pd_r0 passed" << endl;
    return true;

}

bool vector_rw_t1() {
    vector<bool> v(32, false);
    size_t fp_size = 11, index = 1;
    for (int i = 0; i < 129; ++i) {
        for (int j = 0; j < 10; ++j) {
            index = j;
            write_FP_to_vector_by_index(&v, index, i, fp_size);
            bool cond = (i == read_FP_from_vector_by_index(&v, index, fp_size));
            if (!cond) {
                cout << "Fail index " << i << endl;
                cout << "got " << read_FP_from_vector_by_index(&v, index, fp_size);
                cout << " insted of" << i << endl;
                return false;
            }
            write_FP_to_vector_by_index(&v, index, 0, fp_size);
            cond = (0 == read_FP_from_vector_by_index(&v, index, fp_size));
            if (!cond) {
                cout << "Case 2. Fail index " << i << endl;
                return false;
            }
        }
    }
    cout << "Passed vector_rw_t1!" << endl;
    return true;
}

bool validate_header_get_interval_function(size_t reps) {
    size_t a_size = 4;
    HEADER_BLOCK_TYPE a[a_size];
    for (size_t j = 0; j < reps; ++j) {
        for (size_t i = 0; i < a_size; ++i) {
            a[i] = random();
        }
        auto zero_count = array_zero_count(a, a_size);
        uint32_t q = random() % zero_count;
        cout << j << ":\t";
        validate_get_interval_functions(a, a_size, q);
    }
    return true;
}




//bool interval_t0() {
//
//}

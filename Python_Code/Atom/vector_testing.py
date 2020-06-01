from random import *
from math import *


def b(n: int) -> str:
    return bin(n)[2:]


def b_wlz(n: int, k: int = 32) -> str:
    temp = bin(n)[2:]
    assert len(temp) <= k
    return "0"*(k - len(temp)) + temp


def slm(p: int) -> int:
    return (1 << p) - 1


def f(n): return 1 << (1 << n)


def naive_sol(vec: str, quotient: int) -> tuple:
    if quotient == 0:
        if vec[0] == '0':
            return 0, 0
        else:
            return 0, vec.find('0')

    indexes = [i for i in range(len(vec)) if vec[i] == '0']
    return indexes[quotient - 1] + 1, indexes[quotient]


def vector_get_inteval():
    pass


def vector_get_inteval(vec: str, quotient: int) -> tuple:
    zero_counter = 0
    continue_from_index = 0
    start_index = -1
    end_index = -1

    for i in range(len(vec)):
        if zero_counter >= quotient - 1:
            start_index = i
            continue_from_index = i
            break
        if vec[i] == '0':
            zero_counter += 1

    # print("h continue_from_index {:}".format( continue_from_index))
    for i in range(continue_from_index, len(vec)):
        if vec[i] == '0':
            return start_index, i
            # end_index = i

        #     zero_counter += 1
        # if zero_counter == quotient + 1:
        #     end_index = i
        #     return start_index, end_index
    assert False


def att(vec: str, quotient: int) -> tuple:
    zero_counter = -1
    continue_from_index = 0
    start_index = -1
    end_index = -1

    for i in range(len(vec)):
        if zero_counter == quotient - 1:
            start_index = i
            continue_from_index = i
            break
        if vec[i] == '0':
            zero_counter += 1

    # print("h continue_from_index {:}".format( continue_from_index))
    for i in range(continue_from_index, len(vec)):
        if vec[i] == '0':
            return start_index, i
            # end_index = i

        #     zero_counter += 1
        # if zero_counter == quotient + 1:
        #     end_index = i
        #     return start_index, end_index
    assert False


def att2(vec: str, quotient: int) -> tuple:
    zero_counter = 0
    continue_from_index = 0
    start_index = -1
    end_index = -1

    for i in range(len(vec)):
        if zero_counter == quotient:
            start_index = i
            continue_from_index = i
            break
        if vec[i] == '0':
            zero_counter += 1

    for i in range(continue_from_index, len(vec)):
        if vec[i] == '0':
            return start_index, i
    assert False


def get_k_set_interval(vec: str, k: int, to_counter_plus_one: bool = False) -> tuple:
    """return tupl

    Parameters
    ----------
    vec : str
        String of {0,1}*.
    k : int
        ????????????????????
        ????????????????????
    ## to_counter_plus_one : bool
    ##     If True, assume vec beggins in 1.

    Returns
    -------
    tuple of integers. (start, end)
        vec[start - 1] == the index of the "k"'th set bit in vec.
        vec[end] == the index of the "k + 1"'th set bit in vec.

    ##    Remark: If "to_counter_plus_one" == True, then:
    ##    vec[start - 1] == min{the index of the [k-1]'th set bit in vec, 0}
    ##    vec[end] == the index of the "k"'th set bit in vec.

    """
    assert(k >= 0)
    assert set(vec) <= {"1", "0"}

    # to_minus = -int(to_counter_plus_one)
    set_bit_counter = 0
    continue_from_index = 0
    start_index = -1
    end_index = -1

    for i in range(len(vec)):
        if set_bit_counter == k:
            start_index = i
            continue_from_index = i
            break
        if vec[i] == '1':
            set_bit_counter += 1

    for i in range(continue_from_index, len(vec)):
        if vec[i] == '1':
            return start_index, i

    assert False


def select(x: int, r: int) -> int:
    assert (0 < x <= ((1 << 32)-1))
    s = bin(x)[2:]
    s = "0" * (32 - len(s)) + s
    l = [i for i in range(len(s)) if s[i] == '1']
    assert (len(l) > r)
    return l[r]


def my_int(vec: str, start: int, end: int) -> int:
    if not(start <= end <= len(vec)):
        print(start, end, len(vec))
    assert (start <= end <= len(vec))
    x = 0
    for i in range(start, end):
        x <<= 1
        x |= int(vec[i])
    return x


def v_my_int_single(vec: str, start: int, end: int) -> bool:
    x, y = my_int(vec, start, end), int(vec[start: end], 2)
    if x != y:
        print(x, y)
        return False
    return True


def v_my_int(reps: int) -> bool:
    for i in range(reps):
        vec = b_wlz(randint(0, (1 << 32) - 1))
        start, end = sample(range(len(vec)), 2)
        if start > end:
            start, end = end, start

        if not v_my_int_single(vec, start, end):
            print(i)
            return False
    return True

def extract_symbol(start: int, end: int, i: int, val: int, next_val: int, slot_size: int = 32):
    s_index = start // slot_size
    e_index = end // slot_size
    if s_index == e_index:
        new_s = start % slot_size
        new_e = end % slot_size
        vec = b_wlz(val, slot_size)
        return int(vec[new_s:new_e], 2)

    new_s = start % slot_size
    new_e = (end % slot_size) + slot_size
    assert (new_e == (end % (slot_size << 1)))

    vec = b_wlz(val, slot_size) + b(next_val, slot_size)
    return int(vec[new_s:new_e], 2)

def g(n:int, s:int, e:int, slot_size:int = 32):
    return int(b_wlz(n, slot_size)[s:e], 2)

def g2(n:int, s:int, e:int, slot_size:int = 32):
    (n & (slm(slot_size - s))) >> (slot_size - e)

###
###
###
int(b_wlz(692736011)[15:23], 2)
(x & slm(32-15)) >> (32 - 23)
###
###
###

def my(x: int):
    print("tomer")


def r_str(length: int) -> str:
    return "".join([str(randint(0, 1)) for _ in range(length)])


def check(reps: int) -> bool:
    for i in range(reps):
        length = randint(3, 65)
        temp_s = r_str(length)
        count = temp_s.count('0')
        for i in range(count):
            if att(temp_s, i) != naive_sol(temp_s, i):
                print(temp_s)
                print(i)
                return False
    return True


def check2(reps: int) -> bool:
    for i in range(reps):
        length = randint(3, 65)
        temp_s = r_str(length)
        count = temp_s.count('0')
        for i in range(count):
            if att(temp_s, i) != att2(temp_s, i):
                print(temp_s)
                print(i)
                return False
    return True

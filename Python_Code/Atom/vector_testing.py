from random import *
from math import *


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


def select(x:int, r:int)->int:
    assert (0< x <= ((1<<32)-1))
    s = bin(x)[2:]
    s = "0"* (32 - len(s)) + s
    l = [i for i in range(len(s)) if s[i] == '1']
    assert (len(l) > r)
    return l[r]


select(1<<28,0)

temp = bin(0x5555)[2:]
temp
temp.count("1")
select(0x5555,0) + 32
select(0x5555,6) + 32
select(0x5555,7) + 32

for n in range(10):
    print(f(n)**2 == f(n+1))

    print(i, f(i), f(i+1)//f(i))

log2(18446744073709551615)
(1 << 64) - 1 == 18446744073709551615


def my(x: int):
    print("tomer")


1 << 31
2147483648 >> 31


for i in range(3):
    if (att(s, i) != att2(s, i)):
        print(i)
        break

s = "001001"
s = ""
x = int(s, 2)
~x
s = bin(~x)[3:]
s
att(s, 1)
att2(s, 1)
s
get_k_set_interval(s, 0)
get_k_set_interval(s, 1)


s = "0010010"
get_k_set_interval(s, 1)
get_k_set_interval(s, 1, True)
s[2:6]
att(s, 1)
att(s, 2)


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


check(200)
check2(200)
#
# s = "011110110010110"
# # s = "0 11110 110010110"
# s[1]
# s[5]
# att(s,1)
# naive_sol(s,1)
# check(1<<10)
# a = "tomer"
# a.find("tom")
# a.find("tom")
# a.f
# s3
# s3 = r_str(8)
# s3.count("0")
# att(s3,0)
# att(s3,1)
# att(s3,2)
# att(s3,3)
# att(s3,4)
# vector_get_inteval(s3,0)
# vector_get_inteval(s3,1)
# vector_get_inteval(s3,2)
# vector_get_inteval(s3,3)
# s1 = "0111010"
# s2 = "10111010"
# vector_get_inteval(s1,0)
# vector_get_inteval(s2,0)
# att(s1,0)
# att(s2,0)


# l1 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
# l2 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
len(l1)
len(l2)
l1[:-2] == l2

for i in range(615):
    if l1[i] != l2[i]:
        print(i)
        break

for i in range(186, 615):
    if l1[i] != l2[i]:
        print(i)
        break

184/8
l1.count(1)
l2.count(1)
l1[184]
l1[185]
l2[184]
l2[185]

l1[1]
1 << 8
bin(1 << 7)
5*32 + 24

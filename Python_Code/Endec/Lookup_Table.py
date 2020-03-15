import math
from random import *


# def new_encoding(n:int, )

def add_leading_zeros(s: str, length: int) -> str:
    assert len(s) <= length
    return "0"*(length - len(s)) + s


# def overlap_count(s:str,sub:str)->int:
#     c = 0
#     for i in range(len(s)):
#         c += s[i].startswith(sub)

def occurrences(string: str, sub: str) -> int:
    count = start = 0
    while True:
        start = string.find(sub, start) + 1
        if start > 0:
            count += 1
        else:
            return count

# add_leading_zeros("11",4)


def get_all_bin_str(length: int) -> list:
    return [add_leading_zeros(bin(i)[2:], length) for i in range(1 << length)]
    # for i in range(2 << length):


def get_all_bin_str_up_to_length(length: int) -> list:
    fl = [""]
    for i in range(length):
        fl += get_all_bin_str(i+1)
    return fl


def surround_by_sub(s: str, sub: str) -> str:
    return sub + s + sub


def get_fixed_size_length_sum(number_of_symbols: int) -> int:
    assert number_of_symbols > 1
    single = math.ceil(math.log2(number_of_symbols))
    fixed_sum_length = single * number_of_symbols
    return fixed_sum_length


def check(sub: str, max_length: int = 8) -> list:
    temp = get_all_bin_str_up_to_length(max_length)
    temp = [surround_by_sub(s, sub) for s in temp]
    fl = [s for s in temp if occurrences(s, sub) == 2]
    return fl


def length_sum(l: list, sub: str) -> int:
    res = 0
    for s in l:
        assert s.startswith(sub) and s.endswith(sub)
        res += len(s) - len(sub)
    return res


def compare():
    line = "{} {:} {:}"
    print(line.format("sub", "length", "length sum"))
    l3 = get_all_bin_str_up_to_length(3)
    for sub in l3:
        # sub = bin(i)[2:]
        temp = check(sub)
        arg = (sub, len(temp), length_sum(temp, sub))
        line = "{:3} {:4} {:8}"
        print(line.format(*arg))


compare()


def compare2(lim: int):
    msg = "fixed size would take:"
    single = math.ceil(math.log2(lim))
    print(msg, single * lim, "\n")
    line = "{} {:} {:}"
    print(line.format("sub", "length", "lim length sum"))
    l3 = get_all_bin_str_up_to_length(3)
    for sub in l3:
        # sub = bin(i)[2:]
        temp = check(sub)
        arg = (sub, len(temp), length_sum(temp[:lim], sub))
        line = "{:3} {:4} {:8}"
        print(line.format(*arg))


def compare3(lim: int, max_length: int = 8):
    msg = "fixed size would take:"
    single = math.ceil(math.log2(lim))
    print(msg, single * lim, "\n")
    line = "{} {:} {:}"
    print(line.format("sub", "length", "lim length sum"))
    l3 = get_all_bin_str_up_to_length(3)
    for sub in l3:
        # sub = bin(i)[2:]
        temp = check(sub, max_length)
        arg = (sub, len(temp), length_sum(temp[:lim], sub))
        line = "{:3} {:4} {:8}"
        print(line.format(*arg))


def find_sub_optimal_number_rep(sub: str, max_length: int = 8) -> int:
    temp = check(sub, max_length)
    temp_length = len(sub)
    min_val = 4242
    min_index = 0
    min_indexes_list = [0]
    for largest_number in range(1, len(temp)):
        single = math.ceil(math.log2(largest_number))
        fixed_sum_length = single * (largest_number + 1)
        temp_length += len(temp[largest_number]) - len(sub)
        diff = temp_length - fixed_sum_length
        if diff < min_val:
            min_indexes_list = [largest_number]
            min_val = diff
        elif diff == min_val:
            min_indexes_list.append(largest_number)
    return min_indexes_list, min_val


def find_all_not_worse_length(sub: str, max_length: int = 8) -> int:
    temp = check(sub, max_length)
    temp_length = len(sub)
    # min_val = 4242
    min_index = 0
    min_indexes_list = [0]
    for largest_number in range(1, len(temp)):
        single = math.ceil(math.log2(largest_number))
        fixed_sum_length = single * (largest_number + 1)
        temp_length += len(temp[largest_number]) - len(sub)
        # if fixed_sum_length - temp_length <= 0:
        # min_indexes_list = [largest_number]
        # min_val = fixed_sum_length - temp_length
        if fixed_sum_length - temp_length >= 0:
            min_indexes_list.append(largest_number)
    return min_indexes_list


def diff_between_sub_and_fixed(sub: str, number_of_symbols: int, max_length: int = 8, to_print: bool = False) -> int:
    temp = check(sub, max_length)[:number_of_symbols]
    if len(temp) < number_of_symbols:
        print("max_length should be increased (temp does not contain enough symbols.)")
        return -1
    temp_length_sum = length_sum(temp, sub)
    return temp_length_sum - get_fixed_size_length_sum(number_of_symbols)

def get_words(sub: str) -> list:
    temp = check(sub)
    return [s[len(sub):] for s in temp]


words = get_words("01")[:18]
l = ["1" + w[:-2] for w in words]
words
l
k = [int(i,2) for i in l]
k[:16]
res = [i if i in k else -1 for i in range(33)]
res
len(res)
d = {i: words[i] for i in range(len(words))}
d2 = {i: words[i][:-2] for i in range(len(words))}
d
d2

get_words("01")[:11]
get_words("11")[:10]
get_words("11")[:14]

temp = check("01")[:10]
temp = [s[2:] for s in temp]
temp
diff_between_sub_and_fixed("01",8)
diff_between_sub_and_fixed("01",9)
diff_between_sub_and_fixed("01",10)
diff_between_sub_and_fixed("01",11)
diff_between_sub_and_fixed("01",13)
diff_between_sub_and_fixed("01",14)
diff_between_sub_and_fixed("01",15)
diff_between_sub_and_fixed("01",16)
diff_between_sub_and_fixed("01",17)
for i in range(6,18):
    print(i,diff_between_sub_and_fixed("01",i))
for i in range(6,18):
    print(i,diff_between_sub_and_fixed("001",i))
for i in range(6,18):
    print(i,diff_between_sub_and_fixed("0011",i))
diff_between_sub_and_fixed("001",6)
diff_between_sub_and_fixed("001",8)
find_sub_optimal_number_rep("01")
find_sub_optimal_number_rep("001", 18)
find_sub_optimal_number_rep("0010")
find_sub_optimal_number_rep("0110")
find_sub_optimal_number_rep("0110")
find_all_not_worse_length("01", 12)
find_all_not_worse_length("001", 18)
find_all_not_worse_length("001", 12)
find_all_not_worse_length("011", 12)
find_all_not_worse_length("010", 12)
find_all_not_worse_length("0101", 12)
find_all_not_worse_length("0001", 12)
find_all_not_worse_length("1001", 12)
find_all_not_worse_length("1101", 12)
find_all_not_worse_length("1111", 12)
find_all_not_worse_length("1111", 12)

for i in range(6, 14):
    print(i)
    compare2(i)


compare2(15)
compare2(21)
compare2(38)
compare2(33)
compare2(34)
compare2(35)
compare3(36)
compare2(26)
compare2(45)
compare2(8)
compare2(7)
compare2(5)


c01 = check("01")
c11 = check("11")
c00 = check("00")

len(c01)
len(c11)
len(c00)
k = [surround_by_sub(s, "01") for s in l3]

fl = []
for s in k:
    if occurrences(s, "01") == 2:
        fl.append(s)

k
fl
l3 = get_all_bin_str(3)

l = get_all_bin_str(4)
l5 = get_all_bin_str(5)

s = "01010"
s.count("010")
occurrences(s, "010")
l5


# lookup table
# {0: '01',
#  1: '001',
#  2: '101',
#  3: '0001',
#  4: '1001',
#  5: '1101',
#  6: '00001',
#  7: '10001',
#  8: '11001',
#  9: '11101',
#  10: '000001',
#  11: '100001',
#  12: '110001',
#  13: '111001',
#  14: '111101'}
# OR
# {0: '',
#  1: '0',
#  2: '1',
#  3: '00',
#  4: '10',
#  5: '11',
#  6: '000',
#  7: '100',
#  8: '110',
#  9: '111',
#  10: '0000',
#  11: '1000',
#  12: '1100',
#  13: '1110',
#  14: '1111'}
def f(x:int):
    print(x,bin(x)[2:])

l = [0x1,0x5,0x15,0x55,0x155,0x555,0x1555]
line = "{:5} {}"
for i in l:
    print(line.format(i,bin(i)[2:]))
for i in ran
f(0x1)
f(0x5)
f(0x15)
f(0x55)
f(0x155)
0x5
0x1
0x15
0x15
int(0x5,2)
int("01"*1,2)
int("01"*2,2)
int("01"*3,2)
int("01"*4,2)
int("01"*5,2)
int("01"*8,2)
hex(int("01"*8,2))
hex(int("01"*9,2))
hex(int("01"*10,2))
hex(int("01"*11,2))
hex(int("01"*12,2))

oct(int("01"*8,2))
oct(int("01"*9,2))
oct(int("01"*10,2))
oct(int("01"*11,2))
oct(int("01"*12,2))

int("01"*8,4)
int("01"*8,2) + int("10"*8,2)

(0x5555 << 16) | (0x5555) == 0x55555555
int("01"*32,2) == 0x5555555555555555
int("01"*16,2) == 0x55555555
int("01"*8,2) == 0x5555
int("01"*4,2) == 0x55

0x55<< 1
oct(170)
oct(85)
bin(0x55)[2:]
bin(0x44)[2:]

words

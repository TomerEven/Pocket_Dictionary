from typing import *


class naive_pd(object):
    """
    :param m Quotients (q_i) range interval. (forall q_i, q_i in [m])
    :param f Number of elements in PD.
    :param l Remainder (r_i) length. (|r_i| = l)

    """
    head: list
    body: list
    r: int
    m: int
    max_capacity: int
    capacity: int

    def __init__(self, m: int, f: int, l: int):
        # Todo: decrease size by 1.
        self.head = [0] * (f + m + 1)
        self.body = [""] * f
        self.r = l
        self.m = m
        self.max_capacity = f
        self.capacity = 0

    def insert(self, q: int, r: str):
        if self.capacity == self.max_capacity:
            print("Insertion failed, since PD contains", self.max_capacity, "elements")
            return
        self.capacity += 1
        assert self.is_head_last_bit_zero()

        # head_insertion
        start, end = find_lookup_interval(self.head, q)
        length = end - start
        assert self.is_head_last_bit_zero()
        temp = self.head.copy()
        for i in reversed(range(end + 1, len(self.head))):
            self.head[i] = self.head[i - 1]
        assert self.head[end + 1] == 0
        if not self.is_head_last_bit_zero():
            print()
            print(temp)
            print(self.head)
            assert False

        self.head[end] = 1
        # if end != 0:
        # assert self.head[end + 1] == 0

        # find where in the run should the new element be inserted.
        body_start_index = self.get_body_start_index_by_head_start_index(start)
        body_index = body_start_index + length
        for i in range(length):
            if self.body[body_start_index + i] >= r:
                body_index = body_start_index + i
                break

        # push
        for i in reversed(range(body_index + 1, len(self.body))):
            self.body[i] = self.body[i - 1]
        self.body[body_index] = r

        assert self.is_head_last_bit_zero()
        #
        # for i in range(length):
        #     if self.body[start + i] >= r:
        #         self.body.insert(start + i, r)
        #         return
        # self.body.insert(start + length, r)

    def lookup(self, q: int, r: str) -> bool:
        start, end = find_lookup_interval(self.head, q)
        length = end - start
        # if length == 0:
        #     return False
        body_start_index = self.get_body_start_index_by_head_start_index(start)
        for i in range(length):
            if self.body[body_start_index + i] == r:
                assert self.is_head_last_bit_zero()
                return True
        assert self.is_head_last_bit_zero()
        return False

    def remove(self, q: int, r: str):
        start, end = find_lookup_interval(self.head, q)
        length = end - start
        if length == 0:
            print("Delete failed, since PD  does not contain any element with given quotient")
            return

        # find where in the run is the element that is going to be deleted.
        body_start_index = self.get_body_start_index_by_head_start_index(start)
        body_index = -1
        for i in range(length):
            if self.body[body_start_index + i] == r:
                body_index = body_start_index + i
                break
        else:
            print("Delete failed, since PD does not contain any element with given remainder")

        # for i in range(start, end):
        #     if self.body[i] == r:
        #         body_index = i
        #         break

        # update body
        for i in range(body_index, len(self.body) - 1):
            self.body[i] = self.body[i + 1]

        # Todo? did not clear self.body[-1].

        assert self.is_head_last_bit_zero()

        assert end > 0
        assert self.head[end] == 0
        # update head
        for i in range(end, len(self.head)):
            self.head[i - 1] = self.head[i]

        assert self.is_head_last_bit_zero()

        self.capacity -= 1
        return

        # for i in range(length):
        #     if self.body[start + i] == r:
        #         del self.body[start + i]
        #         break
        # else:
        #     print("Delete failed, since PD does not contain any element with given remainder")
        #     del self.body[start + length]
        #
        # assert self.head[start + length]
        # del self.head[start + length]

    def get_body_start_index_by_head_start_index(self, start: int) -> int:
        return self.head[:start].count(1)

    def __repr__(self) -> str:
        return super().__repr__()

    def __str__(self):
        return str(self.head) + "\n" + str(self.body)
        # print(self.head)
        # print(self.body)

    def check_zeros_in_head(self):
        return self.head.count(0) == self.max_capacity

    def is_head_last_bit_zero(self) -> bool:
        return self.head[-1] == 0

    def get_head_as_runs(self) -> list:
        s = "".join([str(i) for i in self.head])
        k = s.split("0")
        return [i + "0" for i in k]


def valid_interval_result(l: list, q: int) -> Tuple[int, int]:
    # return two tuple of two ints. the start of the run, and it end which is zero.
    assert q >= 0
    if q == 0:
        if l[0] == 0:
            return 0, 0
        else:
            return 0, l.index(0)

    indexes = [i for i in range(len(l)) if l[i] == 0]
    assert len(indexes) > q
    return indexes[q - 1] + 1, indexes[q]


def validate_interval(l: list, start: int, end: int) -> bool:
    res = True
    if start != 0:
        c = (l[start - 1] != 0)
        if c:
            print("start predeccesor is not zero")
            res = False
    if l[end] != 0:
        print("end is not zero")
        res = False

    if end < start:
        print("end is smaller then start")
        res = False

    return res


def find_lookup_interval(head: list, q: int) -> Tuple[int, int]:
    zero_counter = 1  # zero appear in the end of a run, not on the run's start.
    index = 0

    while zero_counter <= q:
        if head[index] == 0:
            zero_counter += 1
        index += 1
    start = index

    one_counter = 0
    # for i in range(index)
    while index < len(head) and head[index]:
        one_counter += 1
        index += 1

    sanity_check = head[start:].index(0)
    assert sanity_check == one_counter
    assert validate_interval(head, start, index)
    if valid_interval_result(head, q) != (start, index):
        print("got", (start, index), " instead of", valid_interval_result(head, q))
        assert False
    return start, index
    # return start, one_counter


def lsm(x):
    return (x ^ (x & (x-1)))


for i in range(32):
    print(i, lsm(i))


def split_by_runs(l: list):
    s = "".join([str(i) for i in l])
    k = s.split("0")
    temp = [i + "0" for i in k]
    temp
    return temp


1 << 7
split_by_runs(h2)
bi(170)
int('01010101', 2)


def bi(n): return bin(n)[2:]


def ci(n, k): return to_bin_with_leading_zeros(n, k)


def to_bin_with_leading_zeros(n: int, length: int) -> str:
    s = bin(n)[2:]
    diff = length - len(s)
    if diff > 0:
        return "0" * diff + s
    elif diff == 0:
        return s
    else:
        assert False


# def ci(n:int,length)->str
bi(216)
bi(170)
bin(85)
170
~170
"0111"
7+7*16
bi(119)
s2 = '01110111'*4
h2 = [int(i) for i in s2]

h2 =
bin(-171 - 1)
h = [int(i) for i in bi(216)]
h
head = [1, 0] * 4 + [0, 0, 0]
head
for i in range(4):
    print(i, find_lookup_interval(head, i))


for i in range(4):
    print(i, find_lookup_interval(h, i))

for i in range(8):
    print(i, find_lookup_interval(h2, i))

0	(0, 0)
1	(1, 4)
2	(5, 8)
3	(9, 9)
4	(13, 13)
5	(17, 17)
6	(21, 21)
7	(25, 25)

find_lookup_interval(head, 0)
find_lookup_interval(head, 1)
find_lookup_interval(head, 2)
find_lookup_interval(head, 3)
find_lookup_interval(head, 4)
find_lookup_interval(head, 5)
find_lookup_interval(head, 6)


def dealing_with_last_index(l: list, index: int) -> int:
    pass


def naive_dealing_with_last_index(n: int, index: int, block_size: int = 8) -> int:
    left_shift = block_size - index - 1
    upper = (n >> left_shift) << (left_shift)
    lower = (n >> 1) & ((1 << left_shift) - 1)
    # print(upper, bi(upper)[:left_shift + 1])
    # print(lower,bi(lower))
    return upper | lower | (1<<left_shift)

def f2(n: int, index: int, block_size: int = 8) -> int:
    left_shift = block_size - index
    upper = (n >> left_shift) << (left_shift)
    lower = (n >> 1) & ((1 << left_shift) - 1)
    # print(upper, bi(upper)[:left_shift ])
    # print(lower,bi(lower))
    return upper | lower | (1<<(left_shift - 1))


for i in range(256):
    for k in range(8):
        if naive_dealing_with_last_index(i,k) != f2(i,k):
            print(i,k)
            assert False

1
s3 = "10001001"
n = int(s3,2)
n
ci(137,8)
'1000 1001'
bin(137)
bin(148)
naive_dealing_with_last_index(137,3)
naive_dealing_with_last_index(137,3)
ci(164,8)
n = 170
ci(n,8)
naive_dealing_with_last_index(n,3)
naive_dealing_with_last_index(n,3)

ci(181,8)
ci(189,8)
naive_dealing_with_last_index(n,5)
ci(173,8)
# indexes = [i for i in range(len(l)) if l[i] == 0]
# indexes
# split_by_runs(l)
# l = [0, 1, 1, 0, 0, 1, 0]
# # ls = [str(i) for i in l]
# s = "".join(ls)
# s
# check_interval(l, 0)
# check_interval(l, 1)
# check_interval(l, 2)
# check_interval(l, 3)
# check_interval(l, 4)
#
# for i in range(l.count(0)):
#     res = check_interval(l, i)
#     length = res[1] - res[0]
#     print(i, length, res)
#
# if q == 1:
#     temp = l.index(0)
#     return temp, l[temp + 1:].index(0)

#
# start, length = 0, 0
# zero_counter = 1
# index = 0
# for i in range(len(l)):
#     if l[i] == 0:
#         zero_counter += 1
# while index < len(l) and zero_counter < q:
#     if l[index] == 0:
#         zero_counter += 1
#     index += 1
# start =
#
# l = [1, 0, 1, 0, 1, 1, 0]
# l.index
# k = list(range(8)) + list(range(8))
# del k[12]
# k.index(4)
# k[12]

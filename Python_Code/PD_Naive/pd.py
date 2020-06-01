from typing import *



class PD(object):
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
        self.head = [0] * (f)
        self.body = [0] * (f)
        self.r = l
        self.m = m
        self.max_capacity = f
        self.capacity = 0

    def insert(self, q: int, r: str):
        if self.capacity == self.max_capacity:
            print("Insertion failed, since PD contains", self.max_capacity, "elements")
            return
        self.capacity += 1
        start, length = find_lookup_interval(self.head, q)
        self.head.insert(start + length, 1)

        for i in range(length):
            if self.body[start + i] >= r:
                self.body.insert(start + i, r)
                return
        self.body.insert(start + length, r)

    def lookup(self, q: int, r: str):
        start, length = find_lookup_interval(self.head, q)
        for i in range(length):
            if self.body[start + i] == r:
                return True
        return False

    def remove(self, q: int, r: str):
        start, length = find_lookup_interval(self.head, q)
        if length == 0:
            print("Delete failed, since PD  does not contain any element with given quotient")
            return
        self.capacity -= 1

        for i in range(length):
            if self.body[start + i] == r:
                del self.body[start + i]
                break
        else:
            print("Delete failed, since PD does not contain any element with given remainder")
            del self.body[start + length]

        assert self.head[start + length]
        del self.head[start + length]

    def __repr__(self) -> str:
        return super().__repr__()

    def __str__(self):
        return str(self.head) + "\n" + str(self.body)
        # print(self.head)
        # print(self.body)

    def check_zeros_in_head(self):
        return self.head.count(0) == self.max_capacity


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
    return start, one_counter


def check_interval(l: list, q: int) -> Tuple[int, int]:
    # return two tuple of two ints. the start of the run, and it end which is zero.
    assert q >= 0
    if q == 0:
        if l[0] == 0:
            return 0, 0
        else:
            return 0, l.index(0)

    indexes = [i for i in range(len(l)) if l[i] == 0]
    assert len(indexes) > q
    return indexes[q-1] + 1, indexes[q]

def split_by_runs(l:list):
    s = "".join([str(i) for i in l])
    k = s.split("0")
    temp = [i + "0" for i in k]
    temp
    return temp

indexes = [i for i in range(len(l)) if l[i] == 0]
indexes
split_by_runs(l)
l = [0,1,1,0,0,1,0]
# ls = [str(i) for i in l]
s=  "".join(ls)
s
check_interval(l,0)
check_interval(l,1)
check_interval(l,2)
check_interval(l,3)
check_interval(l,4)

for i in range(l.count(0)):
    res = check_interval(l,i)
    length = res[1] - res[0]
    print(i, length, res)




l1 = ["" for _ in range(8)]
l2 = [""] * 8
l1
l2
l1 == l2
l1[2] = "tomer"
l1[2] = "tomer"
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
l1 = [1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0]
l1.count(1)
# l.find()

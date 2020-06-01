from random import *

from PD_Naive.naive_pd import *

# in1 = [(0, 000001), (0, 000010), (0, 000011), (1, 000100), (3, 000101), (3, 000110), (4, 000111), (4, 001000)]
inp_1 = [(0, '00001'), (0, '00010'), (0, '00011'), (1, '00100'),
         (3, '00101'), (3, '00110'), (4, '00111'), (4, '01000')]


def coin():
    return randint(0, 1)


#
# in1q = [0, 0, 0, 1, 3, 3, 4, 4]
# in1 = [(in1q[i], to_bin_with_leading_zeros(i+1, 5)) for i in range(len(in1q))]
# print(in1)
# len(in1q)
# in1 = [(0, to_bin_with_leading_zeros(0))]
# in1 = [(0, to_bin_with_leading_zeros(0))]


def to_bin_with_leading_zeros(n: int, length: int) -> str:
    s = bin(n)[2:]
    diff = length - len(s)
    if diff > 0:
        return "0" * diff + s
    elif diff == 0:
        return s
    else:
        assert False


def t1(m: int, f: int, l: int):
    """
    :param m Quotients (q_i) range interval. (forall q_i, q_i in [m])
    :param f Number of elements in PD.
    :param l Remainder (r_i) length. (|r_i| = l)
    :return:
    """
    assert f <= m
    quotient = list(range(f))
    remainder = [to_bin_with_leading_zeros(i, l) for i in range(f)]
    d = naive_pd(m, f, l)
    for i in range(f):
        q, r = quotient[i], remainder[i]
        d.insert(q, r)
        temp = d.lookup(q, r)
        if not temp:
            print("Failed in {:} lookup".format(i))
            print(d)
            return False
    print("Passed t1.")
    return True


def t2(m: int, f: int, l: int):
    assert f <= m
    quotient = list(range(f))
    remainder = [to_bin_with_leading_zeros(i, l) for i in range(f)]
    d = naive_pd(m, f, l)
    for i in range(f):
        q, r = quotient[i], remainder[i]
        d.insert(q, r)
        temp = d.lookup(q, r)
        if not temp:
            print("Failed in {:} lookup".format(i))
            print(d)
            return False
        d.remove(q, r)
        temp = d.lookup(q, r)
        if temp:
            print("Failed in {:} lookup after deletion".format(i))
            print(d)
            return False
    print("Passed t2.")
    return True


# random insertion and deletion


def t3(reps: int = 1 << 7):
    f = randint(8, 128)
    m = randint(f + 1, f * 2)
    l = randint(11, 31)
    assert f <= m

    def single_key():
        return randint(0, m), to_bin_with_leading_zeros(randint(1, (1 << l) - 1), l)

    elements = {single_key() for _ in range(f)}
    inserted_elements = set()
    assert len(elements) == f
    # quotient=sample(range(m), f)
    # assert len(quotient) == len(set(quotient))
    # remainder=[to_bin_with_leading_zeros(randint, l) for i in range(f)]
    d = naive_pd(m, f, l)
    for i in range(reps):
        # print(d.get_head_as_runs())
        if coin():
            if not elements:
                continue

            temp = sample(elements, 1)[0]
            elements.remove(temp)
            d.insert(*temp)
            inserted_elements.add(temp)
            if not d.lookup(*temp):
                print("Failed in {:} lookup. case 1.".format(i))
                # print(d)
                return False
        else:
            if not inserted_elements:
                continue

            temp = sample(inserted_elements, 1)[0]
            if not d.lookup(*temp):
                print("Failed in {:} lookup. case 2.".format(i))
                # print(d)
                return False

            inserted_elements.remove(temp)
            d.remove(*temp)
            elements.add(temp)
            if d.lookup(*temp):
                print("Failed in {:} lookup. False positive".format(i))
                # print(d)
                return False

        #
        # q, r = quotient[i], remainder[i]
        # d.insert(q, r)
        # temp = d.lookup(q, r)
        # if not temp:
        #     print("Failed in {:} lookup".format(i))
        #     print(d)
        #     return False
        # d.remove(q, r)
        # temp = d.lookup(q, r)
        # if temp:
        #     print("Failed in {:} lookup after deletion".format(i))
        #     print(d)
        #     return False
    # print("Passed t3.")
    return True

int("10"*4,2)
int("110"*2 +"00",2)
bi = lambda n:bin(n)[2:]
s = bi(170)
bi(170)
bi(216)
s
[i for i in range(len(s)) if s[i] == '0']

170 & ()
s1 = "1110100110110"
len(s1)
t1(16, 3, 5)
t1(16, 9, 5)
t1(16, 15, 5)
#
t2(16, 3, 5)
t2(16, 9, 5)
t2(16, 15, 5)
# sample(list(range(4)), 2)
t3(1 << 9)

for i in range(5):
    assert t3(1 << 9)

for i in range(1 << 8):
    assert t3()
    print(i, end="\t")

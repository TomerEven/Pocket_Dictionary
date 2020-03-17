################################################################################
###Functions:

def f(s: str) -> str:
    x = int(s, 2)
    res = (~x) & (x << 1)
    return bin(res)[2:]


def find_sub_indexes_attempt(s: str, sub: str = "01"):
    assert sub == "01"
    temp = f(s)
    return find_sub_indexes(temp, "1")
    # return [i for i in l]

def find_sub_indexes_attempt2(s: str, sub: str = "01"):
    assert sub == "01"
    temp = f(s)
    l = find_sub_indexes(temp, "1")
    if temp.startswith("1"):
        return [i - 1 for i in l[1:]]
    else:
        print("never here")
        return l


def find_sub_indexes(s: str, sub: str):
    """
    Returns all the indexes where the "sub" string appears in "s".
    """
    indexes_list = []
    counter = 0
    while counter < len(s):
        temp = s[counter:].find(sub)
        if temp == -1:
            return indexes_list
        # counter += temp
        # print(counter, temp, s[counter + temp:counter + temp + len(sub)])
        assert(s[counter + temp:counter + temp + len(sub)] == sub)
        indexes_list.append(counter + temp)
        counter += temp + 1
    print("here")
    return indexes_list

def compare(reps:int, rng):
    el = sample(rng, reps)
    for i in el:
        w = bin(i)[2:]
        if find_sub_indexes(w, "01") != find_sub_indexes_attempt2(w):
            print(i)
            print(find_sub_indexes(w, "01") ,find_sub_indexes_attempt2(w))
            assert False


rng = range(1 << 31, (1<<32) - 1)
compare(1<<12, rng)




################################################################################



words
[int("01" + w,2) for w in words]
len(words)
from random import *
1+1
words = ['01', '001', '101', '0001', '1001', '1101', '00001', '10001', '11001', '11101', '000001']
w2 = ["01" + w for w in words]
w2


def get_random_word_concat(words_list: list, number_of_words: int) -> str:
    s = ""
    for i in range(number_of_words):
        s += words_list[randint(1, len(words_list)) - 1]
    return s


get_random_word_concat(words, 4)
w3 = '1110110001000100001'
w3
f(w3)


working_words = ["0101", "01001"]
for w in working_words:
    assert find_sub_indexes(w, "01") == find_sub_indexes_attempt(w)

f()

def check(reps:int, rng):
    el = sample(rng, reps)
    for i in el:
        # w = "01" + bin(i)[2:] + "01"
        # w = "0" + bin(i)[2:] + "01"
        # w = "0" + bin(i)[2:]
        # w = "1" + bin(i)[2:]
        # w = bin(i)[2:] + "01"
        w = bin(i)[2:]
        if find_sub_indexes(w, "01") != find_sub_indexes_attempt2(w):
            print(i)
            print(find_sub_indexes(w, "01") ,find_sub_indexes_attempt2(w))
            assert False


rng = range(1 << 31, (1<<32) - 1)

check(1<<12, rng)

check(1<<12, range(1000,10000000))

reps = 1<<4
for i in range(reps):
    # r = randint(0, 1<<10)
    # w = "01" + bin(i)[2:] + "01"
    # w = "0"+bin(i)[2:] + "01"
    w = bin(i)[2:] + "01"
    # w = bin(i)[2:]
    if find_sub_indexes(w, "01") != find_sub_indexes_attempt(w):
        print(i)
        print(find_sub_indexes(w, "01") ,find_sub_indexes_attempt(w))
    # print(r)

for i in range(1,10011):
    w = bin(i)[2:]
    assert f(w).startswith("1")

w = "01001"
w = "01" + bin(83)[2:] + "01"
find_sub_indexes(w, "01"), find_sub_indexes_attempt(w)

find_sub_indexes(w, "01"), find_sub_indexes_attempt(w)

for w in words:
    w = "01" + w
    if find_sub_indexes(w, "01") != find_sub_indexes_attempt(w):
        print(w)
find_sub_indexes(w3, "01") == find_sub_indexes_attempt(w3)
find_sub_indexes(w3[2:], "01") == find_sub_indexes_attempt(w3[2:])
find_sub_indexes(w3, "01"), find_sub_indexes_attempt(w3)


def f(s: str) -> str:
    x = int(s, 2)
    res = (~x) & (x << 1)
    return bin(res)[2:]



# def f(s: str) -> str:
#     x = int(s, 2)
#     res = (~x) & (x << 1)
#     return bin(res)[2:]


f("0")
f("00")
f("01")
f("001")
f("010")
f("011")
f("111")

f("1")
f("10")
f("10")
def find_sub_indexes_attempt(s: str, sub: str = "01"):
    assert sub == "01"
    temp = f(s)
    return find_sub_indexes(temp, "1")
    # return [i for i in l]

def find_sub_indexes_attempt2(s: str, sub: str = "01"):
    assert sub == "01"
    temp = f(s)
    l = find_sub_indexes(temp, "1")
    if temp.startswith("1"):
        return [i - 1 for i in l[1:]]
    else:
        print("here")
        return l


def find_sub_indexes(s: str, sub: str):
    """
    Returns all the indexes where the "sub" string appears in "s".
    """
    indexes_list = []
    counter = 0
    while counter < len(s):
        temp = s[counter:].find(sub)
        if temp == -1:
            return indexes_list
        # counter += temp
        # print(counter, temp, s[counter + temp:counter + temp + len(sub)])
        assert(s[counter + temp:counter + temp + len(sub)] == sub)
        indexes_list.append(counter + temp)
        counter += temp + 1
    print("here")
    return indexes_list


temp_word.find("tomer")
temp_word.find("0")
temp_word.split("01")
# def naive_parsing(s:str):
"0011".find("10")

temp_word
find_sub_indexes(temp_word, "01")
find_sub_indexes_attempt(temp_word)
find_comma_indexes(f(temp_word), "1")
temp_word[4:6]
temp_word = words[1] + words[2] + words[3]
temp_word
f(temp_word)

w2

temp = [f(w) for w in w2]
temp

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
l =

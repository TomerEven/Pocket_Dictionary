from random import *
from hashlib import *
import mmh3
from math import *

SEEDS = [randint(1 << 10, 1 << 15) for i in range(1 << 4)]

CHARS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'


def list_average(l: list) -> float:
    return sum(l) / len(l)


def rand_string_single(length=8, char_range=16) -> str:
    return "".join([CHARS[randint(0, char_range)] for _ in range(length)])


def rand_string_list(size: int, length=8, char_range=16) -> list:
    return [rand_string_single(length, char_range) for _ in range(size)]


def rand_string_set(size: int, length=8, char_range=16) -> set:
    return {rand_string_single(length, char_range) for _ in range(size)}


def get_hash_func(size: int, seed1_index: int, seed2_index: int) -> callable:
    seed1, seed2 = SEEDS[seed1_index], SEEDS[seed2_index]
    min_const = 11
    if size < 11:
        min_const = 1
    const = randint(min_const, size)
    return lambda el, size: (mmh3.hash(el, seed1) + const * mmh3.hash(el, seed2)) % size


def balls_into_bins(bins_num: int, balls_num: int) -> list:
    def h(el):
        return mmh3.hash(el, randint(1 << 4, 1 << 16)) % bins_num

    bins = [0] * bins_num
    el_list = rand_string_list(balls_num)
    for s in el_list:
        bins[h(s)] += 1

    return bins


def bins_overflow_analyse(bins: list):
    sq_n = round(len(bins)**.5)
    load_l = [0] * sq_n
    of_l = [0] * sq_n
    for k in range(sq_n):
        for b in bins[k*sq_n:(k + 1)*sq_n]:
            load_l[k] += b
            if b > 1:
                of_l[k] += (b - 1)
    return load_l, of_l


def bins_overflow_analyse_gen(bins: list, interval_f: callable):
    interval_size = round(interval_f(len(bins)))
    temp_range = round(len(bins)//interval_size)
    load_l = [0] * temp_range
    of_l = [0] * temp_range
    for k in range(temp_range):
        for b in bins[k*interval_size:(k + 1)*interval_size]:
            load_l[k] += b
            if b > 1:
                of_l[k] += (b - 1)
    return load_l, of_l


def w(bins_num: int, balls_num: int):
    bins = balls_into_bins(bins_num, balls_num)
    load_l, of_l = bins_overflow_analyse(bins)
    return bins, load_l, of_l


def gen_w(bins_num: int, balls_num: int, interval_f: callable):
    bins = balls_into_bins(bins_num, balls_num)
    load_l, of_l = bins_overflow_analyse_gen(bins, interval_f)
    return bins, load_l, of_l


def exp_gen_w(bins_num: int, balls_num: int, interval_f: callable, reps:int):
    l = [0] * 6
    for i in range(reps):
        temp_l = gen_w(bins_num, balls_num, interval_f)
        for j in range(3):
            l[j] += list_average(temp_l[j])
        for j in range(3):
            l[3 + j] += max(temp_l[j])

    return [i / reps for i in l]




exp_gen_w(1<<10, 1<<10, log2, 32)
exp_gen_w(1<<10, 1<<10, log2, 32)
exp_gen_w(1<<10, 1<<10, log2, 32)
exp_gen_w(1<<10, 1<<10, log2, 128)
exp_gen_w(1<<12, 1<<12, log2, 128)
exp_gen_w(1<<12, 1<<12, log2, 256)
exp_gen_w(1<<12, 1<<12, log2, 512)
exp_gen_w(1<<12, 1<<12, log2_square, 512)

def log2_square(x):
    return log2(x)**2

exp_gen_w(1<<10, 1<<10, log2, 32)

a,b,c = gen_w(1<<10, 1<<10, log2)

log2(1<<10)
list_average(b)
list_average(c)

max(a)
max(b)
max(c)


def claim_check(m: int, n: int, reps: int):
    temp_max = 0
    for i in range(reps):
        a, b, c = w(m, n)
        temp_max = max(temp_max, max(b))
        if max(b) > 2*list_average(b):
            print(i)
            arg = max(b), list_average(b)
            print("max b is: {:}, b average is: {:}.".format(*arg))
            break
    return temp_max


def exp_analyse(arg, reps: int):
    s = 0
    for i in range(reps):
        temp = w(*arg)
        s += max(temp[1])
    return s / reps


arg = 1 << 10, 1 << 10
exp_analyse(arg, 32)
exp_analyse(arg, 32)
exp_analyse(arg, 54)
exp_analyse(arg, 64)
exp_analyse(arg, 128)
exp_analyse(arg, 128)
exp_analyse(arg, 256)
exp_analyse(arg, 256)

44.5/32


a, b, c = w(1 << 10, 1 << 10)
list_average(a)
list_average(b)
list_average(c)

max(a)
max(b)
max(c)
55/32
101/64
104/64
335/256

claim_check(1 << 10, 1 << 10, 1 << 8)
claim_check(1 << 12, 1 << 12, 1 << 8)
claim_check(1 << 12, 1 << 12, 1 << 9)
claim_check(1 << 12, 1 << 12, 1 << 10)
claim_check(1 << 16, 1 << 16, 1 << 10)


pow(2,-10)
pow(2,-9)
pow(2,-8)
pow(2,-7)
pow(2,-6)
x = 1/log(2)

4/(x - 1)
x - 1
4/(x-1)
ln(2)

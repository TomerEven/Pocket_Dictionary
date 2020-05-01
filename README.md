# Pocket_Dictionary

see [Comparing filters](https://github.com/TheHolyJoker/Comparing_Filters) for benchmarks, specifically for PD based filter vs Cuckoo filter.
My previous Bloom filter and Quotient filter are also included in the comparison.


## How to install and compile
```bash
git clone git@github.com:TomerEven/Pocket_Dictionary.git
cd Pocket_Dictionary/Filter_PD
mkdir build_dir
cd build_dir
cmake ..
make
```

## How to run
In `build_dir` directory
- There are 3 types of benchmarking for PD based filter:

```bash
./Filter_PD <type>
```

```bash
./Filter_PD <type> <max number of elements> <error probability exponent> <number of lookup to preform>
```
```bash
./Filter_PD <type> <max number of elements> <error probability exponent> <number of lookup to preform> <first level counter size> <second level counter size> <first level load factor> <second level load factor> 
```
- `type`: 0 or 1. 1 is for filter based on counting PD (CPD), 0 is for PD.
- `max number of elements`: The max number of distinct elements the filter is supposed to contain in any time. This effects the space usage.
- `error probability exponent`: Set the probability the filter will err (False positive), to be `2^error probability exponent`
- `number of lookup to preform`: Number of random lookups that will preformed.
- `first level counter size`: Number of bits each counter in the CPD has.
- `second level counter size`: Number of bits each counter in the counter hash table. Also maximal number of repetition each element can have.
- `first level load factor`: In average, how loaded should each PD be. 
- `second level load factor`: Sets the hash table size.






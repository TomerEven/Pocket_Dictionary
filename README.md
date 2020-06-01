# Pocket_Dictionary
```
@misc{bercea2019fullydynamic,
    title={Fully-Dynamic Space-Efficient Dictionaries and Filters with Constant Number of Memory Accesses},
    author={Ioana O. Bercea and Guy Even},
    year={2019},
    eprint={1911.05060},
    archivePrefix={arXiv},
    primaryClass={cs.DS}
}
```
See https://arxiv.org/pdf/1911.05060.pdf page 12, for a single page explanation on Pocket Dictionary, that is self-contained, and includes drawings. 

## How to install and compile
```bash
git clone https://github.com/TomerEven/Pocket_Dictionary.git
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
- `type`: 0 or 1.<br> 
*0* is for a filter based on Pocket Dictionary.<br>
*1* is for a filter based on counting PD (CPD) 

- `max number of elements`: The max number of distinct elements the filter is supposed to contain in any time. This effects the space usage.

- `error probability exponent`: Set the probability the filter will err (False positive), to be `2^error probability exponent`
- `number of lookup to preform`: Number of random lookups that will preformed.
- `first level counter size`: Number of bits each counter in the CPD has.
- `second level counter size`: Number of bits each counter in the counter hash table. Also maximal number of repetition each element can have.
- `first level load factor`: In average, how loaded should each PD be. 
- `second level load factor`: Sets the hash table size.

## Benchmarking

[Comparing filters](https://github.com/TheHolyJoker/Comparing_Filters) for benchmarks.

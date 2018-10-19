# Counting Filter on *q*-grams using SSE instructions (CF2)

## About
All CF2 variants were designed for research purpose [SG16]. 

Paper is available at [ResearchGate](https://www.researchgate.net/publication/339727109_Engineering_the_Counting_Filter_for_string_matching_algorithms)

There are a couple of variants of the solution:
* cf_gfg - applied only for the matching with translocations and inversions problem [GFG11],
* cf1 - counting filter, a standard implementation [JTU96, N97],
* cf1_gram - the above with q-gram superalphabet,
* cf2 - our naive approach,
* cf2_sse - with SSE instructions,
* cf2_sse_gram - with SSE instructions and q-gram superalphabet,
* cf2_skip - cf2 that skips unnecessary steps,
* cf2_skip_sse - the above with SSE instructions,
* cf2_skip_sse_gram - the above with q-gram superalphabet.

This source code was written for research purpose and has a minimal error checking.
The code may be not be very readable and comments may not be adequate.
There is no warranty, your use of this code is at your own risk.

## Citing
```
@incollection {SG16,
  author    = {R. Susik and {Sz.} Grabowski},
  title     = {Engineering the Counting Filter for String Matching Algorithms},
  booktitle = {Algorithms, Networking and Sensing for Data Processing, Mobile Computing and Applications},
  publisher = {\L{}\'od\'z University of Technology Press},
  year      = {2016},
  pages     = {125--140},
  isbn      = {978-83-7283-7},
}
```

## Requirements

* C++ Compiler - MS Visual Studio
* CPU with SSE instructions support
* Python (for [testing](#testing))

## Compilation

To compile all variants of algorithm simply run:

```shell
git clone https://github.com/rsusik/cf2 cf2
cd cf2
nmake all
```

## Usage

The *make all* compilation generates multiple variants of the algorithm. All of them can be executed from command line as follows:

```shell
ALGORITHM_NAME PATTERNS_FILE PATERN_SIZE TEXT_FILE
```

where:

* PATTERNS_FILE - location of file with patterns
* PATERN_SIZE - pattern size (e.g. 32)
* TEXT_FILE - text file

There are also additional parameters (Q_GRAM size and NEW_SIGMA) defined in cpp files.
It is not recomended to change these parameters.

For more details please refer to mentioned paper.

Example:
```shell
cf2_skip_k1.exe "D:/patterns.r10/patterns.dna.200MB.32.bin" 8 "D:/sets/dna.200MB"
```

The files with patterns has all the patterns written one by one with no separator.
Algorithm reads m fist bytes as the first pattern, then next m bytes as the second and so on.

## Testing

**For testing purpose test_cf_win.py can be used.**

Example:
```shell
python test_cf_win.py cf2_k2.exe,cf2_simd_k2.exe dna.200MB 10 8,12,16,24,32,64 
```

*Please replace the paths in the test_cf_win.py*.

## References

[SG16] R. Susik and Sz. Grabowski.
*Engineering the Counting Filter for String Matching Algorithms*,
pages 125–140. Lodz University of Technology Press, 2016.

[JTU96] P. Jokinen, J. Tarhio, and E. Ukkonen.
*A comparison of approximate string matching algorithms*,
pages 1439–1458. Software Practice & Experience, 1996.

[N97] G. Navarro.
*Multiple approximate string matching by counting*,
pages 125–139. In Proc. 4th South American Workshop on String Processing (WSP’97), 1997.

[GFG11] Sz. Grabowski, S. Faro, E. Giaquinta.
*String Matching with Inversions and Translocations in Linear Average Time (Most of the Time)*,
pages 516–520. Information Processing Letters, 2011.

## Authors
* Robert Susik
* Szymon Grabowski


#ifndef COMMON_H
#define COMMON_H

/* Compile mode detection */
#if defined(_WIN32) || defined(_WIN64)
	#define WINDOWS
	#if defined(_WIN64)
		#define ENV64BIT
	#else
		#define ENV32BIT
	#endif
#endif

#if defined(__GNUC__)
	#define UNIX
	#if defined(__x86_64__) || defined(__ppc64__)
		#define ENV64BIT
	#else
		#define ENV32BIT
	#endif
#endif

#include <xmmintrin.h> /* SSE */
#include <emmintrin.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <math.h>
#include <limits>
#include <iostream>
#include <algorithm> /* std:sort */

#ifdef WINDOWS
#define NOMINMAX /* to disable windows.h min,max */
#include <windows.h>
#include <stdint.h> /* int64_t, etc. for Visual Studio */
#endif

/* Print results flag */
#define PRINT_RESULTSS
#define VERIFY_MEMCMPP

/* Typedefs */
#ifdef ENV64BIT
	typedef		int64_t word;
	typedef		long double ldouble;
#endif
#ifdef ENV32BIT
	typedef		int32_t word;
	typedef		double ldouble;
#endif

typedef unsigned char uchar;

/* Constants */
const unsigned int MAX_WORD_SIZE = sizeof(word)*8;

/* Sizes of types */
const size_t CH_SIZE = sizeof(char);
const size_t PCH_SIZE = sizeof(char*);
const size_t PINT_SIZE = sizeof(unsigned int*);
const size_t BOOL_SIZE = sizeof(bool);
const size_t UCH_SIZE = sizeof(uchar);

/* Other variables */
long counter = 0;
bool *indexes = 0;
#define U 2
int	k = 4; /* q */
int64_t v_count = 0;

#ifndef K_DIFF
#define K_DIFF 0
#endif

#ifndef ASIZE
#define ASIZE 256
#endif

#ifndef Q_GRAM
#define Q_GRAM 0
#endif

#ifndef NEW_SIGMA
#define NEW_SIGMA 0
#endif

/* Time measurement stuff */
#ifdef UNIX

typedef struct {
	timespec start;
	timespec stop;
	timespec sum;
} t_timemes;
#define t_init(t) t.sum.tv_nsec = 0; t.sum.tv_sec = 0
#define t_start(t) clock_gettime(CLOCK_MONOTONIC, &(t.start))
#define t_stop(t) clock_gettime(CLOCK_MONOTONIC, &(t.stop)); \
t.sum.tv_sec += t.stop.tv_sec - t.start.tv_sec; \
t.sum.tv_nsec += t.stop.tv_nsec - t.start.tv_nsec
#define t_get_seconds(t) (double)t.sum.tv_sec + (double)t.sum.tv_nsec / (double)1000000000

#else

typedef struct {
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER tick;
	double start;   // A point in time
	double stop;
	double sum;
} t_timemes;
#define t_init(t) t.sum = 0; QueryPerformanceFrequency(&(t.ticksPerSecond))
#define t_start(t) QueryPerformanceCounter(&(t.tick)); t.start = double(t.tick.QuadPart)/t.ticksPerSecond.QuadPart
#define t_stop(t) QueryPerformanceCounter(&(t.tick)); \
t.stop = double(t.tick.QuadPart)/t.ticksPerSecond.QuadPart; \
t.sum += t.stop - t.start
#define t_get_seconds(t) t.sum

#endif


/* FUNCTIONS */
/*
static inline word ilog2( ldouble n ) {
	return (word) ( log( n ) / log( (ldouble)2 ) );  
}
*/
#define log2 0.69314718055994529
#define ilog2(n) (word) ( log( n ) / log2 )

#define	ILOG_2( x ) ilog2( x )

void print_result(double search_time, long ver_count, long matches, long sigma, int q, int kdiff) {
	printf("%d\t%d\t%d\t%f\t%ld\t%ld", sigma, q, kdiff, search_time, ver_count, matches);
}

void print_resultn(double search_time, long ver_count, long matches, long sigma, int q, int kdiff) {
	print_result(search_time, ver_count, matches, sigma, q, kdiff);
	printf("\n");
}

unsigned int get_number_of_occurences(const uchar *T, const int n, const uchar s) {
	int occurences = 0;
	for(int i = 0; i < n; i++)
		if(T[i]==s) 
			occurences++;
	return occurences;
}

static int	* build_verify_table( int m, int k, int r, int l )
{
	int	mk;
	int	h;
	int	mpk = m / k;
	int	c, f, * t;

	t = (int*)malloc( MAX_WORD_SIZE * sizeof( int ));

	for( f = 0; f < r; f++ ) {
		c = ( 1 - f - mpk ) * k;
		mk = ( mpk * l - 1 + f * l );

		for( h = 0; h < k; h++, c-- ) {
			t[ mk ] = c; 
			mk += mpk * l + r - 1;
		}
	}

	return t;
}

int double_cmp(const void *a, const void *b)
{
	const double *da = (const double *)a; 
	const double *db = (const double *)b; 
	return (int)(*da - *db); 
}

template <class T> long read_file_content( T**buffer, const char* filename ) {
	long length;
	FILE * file = fopen (filename, "rb");
	if (file) {
		fseek (file, 0, SEEK_END);
		length = ftell (file);
		fseek (file, 0, SEEK_SET);
		*buffer = (T*)malloc (length+1);
		if (*buffer==NULL) return 0;
		fread (*buffer, 1, length, file);
		*(*buffer+length) = '\0';
		fclose (file);
	}
	return length;
}


template <class T> void printf_binnary(T var) {
	unsigned int size = sizeof(T)*8;
	
	for ( int i = size - 1; i >= 0; i--) {
		printf("%d", var >> i & 1);
	}
}

template <class T> char * deb_printf_binnary(T var) {
	unsigned int size = sizeof(T)*8;
	char *str = new char[size];
	char *tmp = str;
	for ( int i = size - 1; i >= 0; i--) {
		sprintf(tmp++, "%d", var >> i & 1);
	}
	return str;
}


int map [256];

bool CreateMapByHistogram_compar (unsigned long* i, unsigned long* j) { return (*i > *j); }
template<class T> int CreateMapByHistogram(T* t, int n) {
	// Map array creation
	int sigma = 0;
	int threshold = 16;	// how much sigma is the most
	unsigned long symbols [256];
	unsigned long * symbolsp[256];
	for (int i = 0; i < 256; ++i) {
		symbols[i] = 0;
		symbolsp[i] = &(symbols[i]);
	}
	for (long i = 0; i < n; ++i) 
		symbols[ t[i] ] ++;
	std::sort(symbolsp, &(symbolsp[255]), CreateMapByHistogram_compar);
	for (int i = 0; i < 256; ++i) map[i] = NULL;
	for (int i = 0; i < threshold; ++i) {
		if(*symbolsp[i]) {
			*symbolsp[i] = sigma++;
		} else {
			*symbolsp[i] = sigma-1;
		}
	}
	for (int i = threshold; i < 256; ++i) {
		*symbolsp[i] = sigma<threshold?sigma-1:threshold-1;
	}
	//printf("HISTOGRAM\n");
	for (int i = 0; i < 256; ++i) {
		map[i] = symbols[i];
		//printf("%d (%c) = %d\n", i, i, map[i]);
	}
	return sigma;
}


template<class T> int CreateMapByHistogramBinPack(T* t, int n) {
	// Map array creation
	int sigma = 0;
	int new_sigma = NEW_SIGMA;
	unsigned long symbols [256];
	unsigned long * symbolsp[256];
	long sum = 0;
	int binSize = n / new_sigma;
	for (int i = 0; i < 256; ++i) {
		symbols[i] = 0;
		symbolsp[i] = &(symbols[i]);
	}
	for (long i = 0; i < n; ++i) 
		symbols[ t[i] ] ++;

	std::sort(symbolsp, &(symbolsp[255]), CreateMapByHistogram_compar);
	// symbolsp is now most common symbols (the most at first position)

	for (int i = 0; i < 256; ++i) map[i] = NULL;
	for (int i = 0; i < 256; ++i) {
		sum += *symbolsp[i];
		if(sum > binSize) {
			sum = sum - binSize;
			*symbolsp[i] = sigma++;
		} else {
			*symbolsp[i] = sigma;
		}
	}
	// printf("HISTOGRAM\n");
	for (int i = 0; i < 256; ++i) {
		map[i] = symbols[i]; // printf("%d (%c) = %d\n", i, i, map[i]);
	}

	//for(int i = 0; i < new_sigma; ++i) { printf("%d:\t[ ", i); for (int j = 0; j < 256; ++j) { if( symbols[j] == i ) printf(" '%c' ", j); } printf(" ] \n"); }
	return ++sigma;
}


template <unsigned int Q, unsigned int SIGMA> struct get_ { 
    static unsigned long long int gram(const uchar * s, const long start /* at start set to 1 */ ) {
        return map[s[Q - 1]] * start + get_<Q - 1, SIGMA>::gram(s, start*SIGMA);
    }
};

template <unsigned int SIGMA> struct get_<0, SIGMA> { 
    static unsigned long long int gram(const uchar * s, const long start /* at start set to 1 */ ) { return 0; }
};

template <unsigned int Q, unsigned int SIGMA> unsigned long long int get_q_gram(const uchar *s) {
	return get_<Q, SIGMA>::gram(s, 1);
};

void KDIFFERENCES (const uchar *y, int n, int index, const uchar *x, int m, int k) {
	int T[256][256];

	++v_count;
   // Preprocessing
   
   // Offset aby wyrownac indeksowanie do 0
   int offset = 1;
   for (int i = -1; i < n; ++i) {
      T[-1 + offset ][ i + offset ] = 0;
   }
   
   for (int i = -1; i < m; ++i) {
      T[ i + offset ][ -1 + offset ] = i + 1;
   }

   // Searching
   int j = 0;
   for( j=0; j < n; j++) {
		for(int i=0; i<m; i++) {
			int p = x[i] == y[j] ? 0 : 1;
			T[i + offset][j + offset] = std::min( 
				T[i - 1 + offset][j - 1 + offset] + p, 
				std::min( T[i + offset][j - 1 + offset] + 1, T[i - 1 + offset][j + offset] + 1)	
			);
		}
      
      if( T[m][j + offset] <= k ) {
         indexes[ j + index - m + 1] = true;
      }
   }
}


// */




#endif

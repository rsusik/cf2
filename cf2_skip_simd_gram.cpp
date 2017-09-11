#define NEW_SIGMA 4
#define Q_GRAM 2
#include "common.h"

void cf2_skip_simd_gram (const uchar *P, const int m, const uchar *T, const int n, const int sigma, const int k) {
	__m128i sum128 = _mm_setzero_si128();
	__m128i hp = _mm_setzero_si128(), ht = _mm_setzero_si128();// = { 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
	int sum = 0;
	int i = 0;
	for ( i = 0; i < m - 1; i++) {
		hp.m128i_u8[ get_q_gram<Q_GRAM, NEW_SIGMA>(P+i) ]++;	// pattern
		ht.m128i_u8[ get_q_gram<Q_GRAM, NEW_SIGMA>(T+i) ]++;	// text
	}
	for(; i < n-m;) {
		sum128 = _mm_sad_epu8(hp, ht);
		
		if ( (sum = (sum128.m128i_u16[0] + sum128.m128i_u16[4])) <= k*(2) ) {
			++v_count;
#ifdef VERIFY_MEMCMP
			if(memcmp(T+i-(m-1), P, m)==0) {
				indexes[i-(m-1)] = true;
			}
#endif
		}
		
		// skip some steps
		for(int j = 1; j < sum/(2*Q_GRAM)-k; j++) {
			--ht.m128i_u8[ get_q_gram<Q_GRAM, NEW_SIGMA>(T+i-(m-1)) ];
			++ht.m128i_u8[ get_q_gram<Q_GRAM, NEW_SIGMA>(T+i) ];
			i++;
		}

		--ht.m128i_u8[ get_q_gram<Q_GRAM, NEW_SIGMA>(T+i-(m-1)) ];
		++ht.m128i_u8[ get_q_gram<Q_GRAM, NEW_SIGMA>(T+i) ];
		i++;
	}
}


/* MAIN */

int main(int argc, char *argv[]) {
	if ( argc < 4 ) return EXIT_FAILURE;
	t_timemes t_data_acc = {0}, t_pre = {0}, t_run = {0};
	t_init(t_data_acc); t_init(t_pre); t_init(t_run);
	t_start(t_pre);
	
	const char *patterns_filename = argv[1], *patt_size_pch = argv[2], *filename = argv[3];
	unsigned int patt_size = atoi(patt_size_pch), text_size = 0;
	uchar *text = NULL, *pattern = NULL;
	FILE * file = NULL;

	text_size = read_file_content<uchar>(&text, filename);
	if (text == NULL) return EXIT_FAILURE;

	pattern = (uchar*)calloc (patt_size+1, CH_SIZE);
	if (pattern == NULL) { printf("Error: Can't allocate memory for pattern."); free(text); return EXIT_FAILURE; }

	file = fopen (patterns_filename, "rb");
	if (!file) { printf("Error: Can't open patterns file."); free(text); free(pattern); return EXIT_FAILURE; }
	
	indexes = (bool*)calloc(text_size, BOOL_SIZE);

	int sigma = CreateMapByHistogramBinPack<uchar>(text, text_size);
	
	while (fread (pattern, CH_SIZE, patt_size, file)==patt_size) {
		t_start(t_run);
		cf2_skip_simd_gram(pattern, patt_size, text, text_size, sigma, K_DIFF);
		t_stop(t_run);
	}

	for(unsigned long l = 0; l < text_size; ++l) if( indexes[l] ) ++counter;
	print_resultn(t_get_seconds(t_run), v_count, counter, sigma, Q_GRAM, K_DIFF);
	free(text);
	free(pattern);
	free(indexes);
	fclose(file);
	return EXIT_SUCCESS;
}

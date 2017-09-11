#include "common.h"

// http://arxiv.org/pdf/1012.0280v1.pdf
void cf_gfg(const uchar *p, const int m, const uchar *t, const int n, const int alfa, const int beta) {
	int G[ASIZE];
	int s = 0;
	for(int i = 0; i < ASIZE; i++) {
		G[i] = 0;
	}
	for(s = 0; s < m; s++) {
		++G[p[s]];
		--G[t[s]];
	}
	int delta = 0;
	for(int c = 0; c < ASIZE; c++) {
		delta += abs(G[c]);
	}

	for(s = 0; s < n - m; s++) {
		if(delta==0) {
			++v_count;
		}
		delta = delta - abs(G[t[s]]) - abs(G[t[s+m]]);
		++G[t[s]];
		--G[t[s+m]];
		delta = delta + abs(G[t[s]]) + abs(G[t[s+m]]);
	}

	if(delta==0) { 
		++v_count;
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
		cf_gfg(pattern, patt_size, text, text_size, sigma, K_DIFF);
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

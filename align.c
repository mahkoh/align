#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>   
#include <stdbool.h> 

struct word {
	void   *link; // we can't use struct word * here because of strict aliasing
	char   *val;
	size_t len;
};

struct line {
	void        *link;
	struct word *words;
};

// reverse singly-linked list
static void *rev(void *end)
{
	void **cur = end;
	void **prev;
	void **next = NULL;
	while (cur) {
		prev = *cur;
		*cur = next;
		next =  cur;
		 cur = prev;
	}
	return next;
}

static struct word *word_new(struct word *prev, size_t len, char *val)
{
	struct word *word = malloc(sizeof(*word));
	word->link = prev;
	word->len  = len; 
	word->val  = val; 
	return word;
}

static struct line *line_new(struct line *prev, struct word *words)
{
	struct line *line = malloc(sizeof(*line));
	line->link  = prev; 
	line->words = words;
	return line;
}

static bool is_indent(int c)
{
	return c == ' ' || c == '\t';
}

static size_t read_word(char *line, char sd)
{
	size_t c = 0;
	bool esc = false;
	bool str = false;
	for (; line[c]; c++) {
		if (!esc && line[c] == sd)
			str = !str;
		esc = !esc && line[c] == '\\';
		if (line[c] == '\n' || (!str && isspace(line[c])))
			break;
	}
	return c;
}

static char *read_argument(char name, char **argv)
{
	if (!*argv) {
		fprintf(stderr, "-%c needs an argument\n", name);
		exit(1);
	}
	return *argv;
}

int main(int argc, char **argv)
{
	FILE *in              = stdin;
	bool right_align      = false;
	char sd               = '"'; // string delimiter
	const char *os        = " "; // output separator
	const char *prog_name = *argv++;

	for (; *argv; argv++) {
		if (**argv != '-')
			break;
		switch (argv[0][1]) {
		case 'r': right_align = true; break;
		case 'o': os = read_argument('o', ++argv);    break;
		case 's': sd = read_argument('s', ++argv)[0]; break;
		case 'h':
			printf("%s [-s <string delimiter>] "
			          "[-h] "
			          "[-r] "
			          "[-o <output separator>] "
			          "[file]\n"
			          , prog_name);
			return 0;
		case '-': argv++; goto NO_FLAG;
		default:
			fprintf(stderr, "Unknown flag -%c\n", **argv ? **argv : ' ');
			return 1;
		}
	}
NO_FLAG:
	if (*argv) {
		in = fopen(*argv, "r");
		if (!in) {
			fprintf(stderr, "can't open file\n");
			return 1;
		}
	}

	size_t max_col     = 0;
	size_t *max_width  = calloc(1, sizeof(*max_width));
	struct line *lines = NULL;
	char   *line_p     = NULL;
	size_t n           = 0;
	char   *indent     = NULL;
	while (getline(&line_p, &n, in) != -1) {
		char *line = line_p;
		if (!indent) {
			while(is_indent(*line))
				line++;
			indent = strndup(line_p, (size_t)(line-line_p));
		}

		for (; isspace(*line); line++);
		struct word *words = NULL;
		for (size_t col = 0; *line; col++) {
			size_t c = read_word(line, sd);
			words = word_new(words, c, strndup(line, c));
			if (col > max_col) {
				max_col = col;
				max_width = realloc(max_width, (col+1)*sizeof(*max_width));
				max_width[col] = c;
			} else if (c > max_width[col]) {
				max_width[col] = c;
			}
			for (line += c; isspace(*line); line++);
		}
		lines = line_new(lines, rev(words));
		free(line_p);
		line_p = NULL;
	}
	lines = rev(lines);

	size_t max_max_width = 1;
	for (size_t i = 0; i <= max_col; i++) {
		if (max_width[i] > max_max_width)
			max_max_width = max_width[i];
	}
	char *padding = malloc(max_max_width);
	memset(padding, ' ', max_max_width);

	for (; lines; lines = lines->link) {
		struct word *w = lines->words;
		if (w)
			fputs(indent, stdout);
		for (size_t col = 0; w; col++) {
			if (right_align) {
				fwrite(padding, max_width[col]-w->len, 1, stdout);
				fwrite(w->val,  w->len,                1, stdout);
			} else {
				fwrite(w->val,  w->len,                1, stdout);
				if (w->link)
					fwrite(padding, max_width[col]-w->len, 1, stdout);
			}
			w = w->link;
			if (w)
				fputs(os, stdout);
		}
		fputs("\n", stdout);
	}
}

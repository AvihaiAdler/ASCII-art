#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "input.txt"
#define MAX_BUF_SIZE 256
#define GLYPH_FILE_PATH 50

bool get_glyph_path(char *buf, size_t size, char letter) {
  if (!buf || !size) return false;

  int len = snprintf(NULL, 0, "glyphs/capitals/%c.cab", letter);
  if ((size_t)len > size - 1) return false;

  sprintf(buf, "glyphs/capitals/%c.cab", letter);
  return true;
}

void insert_letter(char *art, char letter, size_t pos, size_t len) {
  if (!art) return;

  char glyph_path[GLYPH_FILE_PATH];
  if (!get_glyph_path(glyph_path, sizeof glyph_path, letter)) return;

  FILE *gfp = fopen(glyph_path, "r");
  if (!gfp) return;

  for (int i = 0; i < GLYPH_HEIGHT; i++) {
    for (int j = 0; j < GLYPH_WIDTH + 1; j++) {
      int c = fgetc(gfp);
      if (c == EOF) break;
      if (c == '\n') c = ' ';

      art[i * len * (GLYPH_WIDTH + GLYPH_SPACING) + j +
          pos * (GLYPH_WIDTH + GLYPH_SPACING)] = (char)c;
    }
    art[i * len * (GLYPH_WIDTH + GLYPH_SPACING) + GLYPH_WIDTH +
        pos * (GLYPH_WIDTH + GLYPH_SPACING)] = ' ';
  }

  fclose(gfp);
}

char *convert_to_art(char *str, size_t len, size_t *art_len) {
  if (!str || !len || !art_len) return NULL;

  char *art = malloc(len * (GLYPH_WIDTH + GLYPH_SPACING) * GLYPH_HEIGHT);
  *art_len = len * (GLYPH_WIDTH + GLYPH_SPACING) * GLYPH_HEIGHT;
  memset(art, ' ', *art_len);

  for (size_t pos = 0; pos < len; pos++) {
    if (!isalpha(str[pos])) continue;

    char letter = islower(str[pos]) ? (char)toupper(str[pos]) : str[pos];

    insert_letter(art, letter, pos, len);
  }

  for (int i = 0; i < GLYPH_HEIGHT; i++) {
    art[i * len * (GLYPH_WIDTH + GLYPH_SPACING) +
        len * (GLYPH_WIDTH + GLYPH_SPACING) - 1] = '\n';
  }

  return art;
}

void print_glyphs(char *mat, size_t len) {
  for (size_t i = 0; i < len; i++) {
    fputc(mat[i], stdout);
  }
}

int main(void) {
  FILE *input_fp = fopen(INPUT, "r");
  if (!input_fp) {
    perror("fopen()");
    return EXIT_FAILURE;
  }

  char buf[MAX_BUF_SIZE];
  while (fgets(buf, sizeof buf, input_fp)) {
    size_t len = strlen(buf);
    size_t art_len;

    char *art = convert_to_art(buf, len, &art_len);
    if (!art) {
      fprintf(stderr, "failed to create a glyph matrix\n");
      return EXIT_FAILURE;
    }
    print_glyphs(art, art_len);

    free(art);
  };

  return EXIT_SUCCESS;
}
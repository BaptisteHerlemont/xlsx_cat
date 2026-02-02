#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <xlsxio_read.h>

static int parse_sheet_index(const char* s, int* out_index) {
    char* end = NULL;
    long v;

    errno = 0;
    v = strtol(s, &end, 10);
    if (errno != 0 || end == s || *end != '\0' || v <= 0 || v > INT_MAX) {
        return 0;
    }
    *out_index = (int)v;
    return 1;
}

static char* sheet_name_by_index(xlsxioreader reader, int index) {
    xlsxioreadersheetlist sheetlist;
    const char* name;
    int i = 0;

    sheetlist = xlsxioread_sheetlist_open(reader);
    if (sheetlist == NULL) {
        return NULL;
    }

    while ((name = xlsxioread_sheetlist_next(sheetlist)) != NULL) {
        i++;
        if (i == index) {
            char* copy = strdup(name);
            xlsxioread_sheetlist_close(sheetlist);
            return copy;
        }
    }

    xlsxioread_sheetlist_close(sheetlist);
    return NULL;
}

int main(int argc, char* argv[]) {
    int sheet_index = 1;
    char* sheet_name = NULL;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: xlsx_cat <xlsx_file> [sheet_index]\n");
        return 1;
    }

    const char* filename = argv[1];
    xlsxioreader xlsxioread;
    xlsxioreadersheet sheet;
    char* value;

    if ((xlsxioread = xlsxioread_open(filename)) == NULL) {
        fprintf(stderr, "Error opening .xlsx file: %s\n", filename);
        return 1;
    }

    if (argc == 3) {
        if (!parse_sheet_index(argv[2], &sheet_index)) {
            fprintf(stderr, "Invalid sheet index: %s\n", argv[2]);
            xlsxioread_close(xlsxioread);
            return 1;
        }
    }

    sheet_name = sheet_name_by_index(xlsxioread, sheet_index);
    if (sheet_name == NULL) {
        fprintf(stderr, "Sheet index out of range: %d\n", sheet_index);
        xlsxioread_close(xlsxioread);
        return 1;
    }

    if ((sheet = xlsxioread_sheet_open(xlsxioread, sheet_name, XLSXIOREAD_SKIP_EMPTY_ROWS)) == NULL) {
        fprintf(stderr, "Error opening sheet in file: %s\n", filename);
        free(sheet_name);
        xlsxioread_close(xlsxioread);
        return 1;
    }
    free(sheet_name);

    while (xlsxioread_sheet_next_row(sheet)) {
        int first = 1;
        while ((value = xlsxioread_sheet_next_cell(sheet)) != NULL) {
            if (!first) printf("\t");
            printf("%s", value);
            free(value);
            first = 0;
        }
        printf("\n");
    }

    xlsxioread_sheet_close(sheet);
    xlsxioread_close(xlsxioread);

    return 0;
}

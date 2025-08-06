#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxio_read.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: xlsx_cat <xlsx_file>\n");
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

    if ((sheet = xlsxioread_sheet_open(xlsxioread, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS)) == NULL) {
        fprintf(stderr, "Error opening sheet in file: %s\n", filename);
        xlsxioread_close(xlsxioread);
        return 1;
    }

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

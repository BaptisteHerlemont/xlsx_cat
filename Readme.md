# xlsx_cat

A Unix-style command-line tool to print `.xlsx` spreadsheet content to standard output (like `cat` but for Excel files).

## Requirements

- [libxlsxio_read](https://github.com/brechtsanders/xlsxio) (must be installed system-wide)
- `libzip`, `libexpat`

## Installation

```bash
git clone https://github.com/BaptisteHerlemont/xlsx_cat.git
cd xlsx_cat
make
sudo make install

# xlsx_cat

A Unix-style command-line tool to print `.xlsx` spreadsheet content to standard output (like `cat` but for modern Excel files).
Note: only `.xlsx` (Office Open XML) files are supported.

## Requirements (automated setup available)

To compile and use `xlsx_cat`, you need the following libraries:

- [`libxlsxio_read`](https://github.com/brechtsanders/xlsxio) (for reading `.xlsx` files)
- `libzip` and `libexpat` (used internally by `libxlsxio`)

You can install everything automatically with the provided script:

```bash
bash install_deps.sh
```
## Installation

```bash
git clone https://github.com/BaptisteHerlemont/xlsx_cat.git
cd xlsx_cat
bash install_deps.sh
make
sudo make install
```

## Usage

```bash
xlsx_cat <xlsx_file> [sheet_index]
```

- `sheet_index` is 1-based (default: 1).

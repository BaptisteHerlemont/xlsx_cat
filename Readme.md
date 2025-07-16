# xlsx_cat

A Unix-style command-line tool to print `.xlsx` spreadsheet content to standard output (like `cat` but for Excel files).

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
make
sudo make install

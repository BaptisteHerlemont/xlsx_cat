#!/bin/bash

set -e

echo "Installing system dependencies..."
sudo apt update
sudo apt install -y libzip-dev libexpat1-dev libminizip-dev cmake git

echo "Cloning and building libxlsxio_read..."
git clone https://github.com/brechtsanders/xlsxio.git
cd xlsxio
mkdir -p build && cd build
cmake -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF -DBUILD_READ=ON -DBUILD_WRITE=OFF ..
make
sudo make install
sudo ldconfig

echo "Dependencies installed successfully."

RPP_IMP_ROOT="$(dirname "$(pwd)")"

if [ -n "$BASH_VERSION" ]; then
  #!/bin/bash
  DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  echo "Script is located at: $DIR"
  RPP_IMP_ROOT="$(dirname "$DIR")"
elif [ -n "$ZSH_VERSION" ]; then
  #!/usr/bin/env zsh
  SCRIPT_PATH="${(%):-%N}"
  SCRIPT_DIR="$(cd "$(dirname "$SCRIPT_PATH")" && pwd)"
  RPP_IMP_ROOT="$(dirname "$SCRIPT_DIR")"
else
    echo "Unknown shell"
fi
echo "RPP_IMP_ROOT: $RPP_IMP_ROOT"

export RPP_IMP_ROOT

cd "$RPP_IMP_ROOT"
# source $RPP_IMP_ROOT/scripts/install.sh

echo "[+] RPP_IMP_ROOT set to: $RPP_IMP_ROOT"

# Step 1: Create a fresh build directory (if not already)
rm -rf build && mkdir build && cd build

# Step 2: Run CMake, pointing to the parent directory (source dir)
cmake ..

# Step 3: Build the executable
make -j$(nproc)

echo -e "\n==============================\n"
echo "Running RPP-imp application..."
echo -e "\n==============================\n"

./RPP-imp

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

export RPP_IMP_ROOT

cd "$RPP_IMP_ROOT"

BUILD_DIR="$RPP_IMP_ROOT/build"

if [ -d "$BUILD_DIR" ]; then
  echo "Build directory exists, building..."
else
  echo "Build directory does not exist, configuring..."
  mkdir -p "$BUILD_DIR"
fi

# cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -S "$RPP_IMP_ROOT" -B "$BUILD_DIR"
cmake -G Ninja -S "$RPP_IMP_ROOT" -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"

echo -e "\n==============================\n"
echo "Running RPP-imp application..."
echo -e "\n==============================\n"

./build/RPP-imp


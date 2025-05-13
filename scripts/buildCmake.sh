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
# echo "[+] RPP_IMP_ROOT set to: $RPP_IMP_ROOT"

cd "$RPP_IMP_ROOT"
# source $RPP_IMP_ROOT/scripts/install.sh

#  export CMAKE_ROOT=$(cmake --system-information | grep '^CMAKE_ROOT' | cut -d= -f2- | xargs)
#  export CMAKE_ROOT=$(echo $CMAKE_ROOT | sed 's/^CMAKE_ROOT //')

BUILD_DIR="$RPP_IMP_ROOT/build"

if [ -d "$BUILD_DIR" ] || [ -d "$BUILD_DIR/RPP-imp" ]; then
  echo "Build directory exists, building..."
  cmake --build "$BUILD_DIR"
else
  echo "Build directory does not exist, configuring and building..."
  rm -rf "$BUILD_DIR"
  cmake -G Ninja -S "$RPP_IMP_ROOT" -B "$BUILD_DIR" 
  cmake --build "$BUILD_DIR" 
fi

echo -e "\n==============================\n"
echo "Running RPP-imp application..."
echo -e "\n==============================\n"

./build/RPP-imp


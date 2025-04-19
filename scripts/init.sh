#!/bin/bash

# Resolve absolute path to this script
SCRIPT_PATH="$(realpath "${BASH_SOURCE[0]}")"
# Go to the parent of 'scripts' (assumes script is inside rpp-imp/scripts/)
RPP_IMP_ROOT="$(dirname "$(dirname "$SCRIPT_PATH")")"

# Export the env var
export RPP_IMP_ROOT

cd "$RPP_IMP_ROOT"

# Optional: Show confirmation
echo "[+] RPP_IMP_ROOT set to: $RPP_IMP_ROOT"
echo "[+] Current dir: $(pwd)"

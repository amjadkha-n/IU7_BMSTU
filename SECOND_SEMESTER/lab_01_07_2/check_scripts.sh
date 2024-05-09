#!/bin/bash

SCRIPTS=(build_debug.sh build_debug_asan.sh build_debug_msan.sh build_debug_ubsan.sh build_release.sh collect_coverage.sh check_scripts.sh clean.sh)

for script in "${SCRIPTS[@]}"; do
    shellcheck "$script"
done


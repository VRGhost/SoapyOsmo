#!/bin/bash

DRIVER_SOURCE_ROOT=$(python -c "import os; print os.path.abspath(os.path.dirname('${BASH_SOURCE[0]}') + '/..')")

BUILD_DIR="${DRIVER_SOURCE_ROOT}/build"

echo ${BUILD_DIR}

if [ -e "${BUILD_DIR}" ]; then
	rm -r "${BUILD_DIR}"
fi

mkdir "${BUILD_DIR}"
cd "${BUILD_DIR}"

cmake .. && make -j4
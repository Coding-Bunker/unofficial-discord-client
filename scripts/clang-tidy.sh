#!/usr/bin/env bash

echo "lint source code with clang-tidy..."

if command -v clang-tidy >/dev/null 2>&1 ; then
	CLANG_TIDY=clang-tidy
else
	echo "clang-tidy is not available, but C or C++ files need linting! Skip this script or install clang-tidy."
	exit 1
fi

for OUTPUT in $(git ls-files -- '*.cpp' '*.hpp')
do
	"${CLANG_TIDY}" -p $1 $OUTPUT
done

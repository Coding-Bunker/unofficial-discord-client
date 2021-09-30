#!/usr/bin/env bash

echo "lint source code with clang-format..."

if command -v clang-format-11 >/dev/null 2>&1 ; then
	CLANG_FORMAT=clang-format-11
elif command -v clang-format >/dev/null 2>&1 ; then
	CLANG_FORMAT=clang-format
	if ! "${CLANG_FORMAT}" --version | awk '{ if (substr($NF, 1, index($NF, ".") - 1) < 11) exit 1; }'; then
		echo "You are using '$("${CLANG_FORMAT}" --version)', which appears to not be clang-format 11 or later."
		echo "It is very likely that the resulting changes are not what you wanted."
	fi
else
	echo "clang-format-11 is not available, but C or C++ files need linting! Skip this script or install clang-format-11."
	echo "(If you install a package 'clang-format', please make sure it's version 11 or later.)"
	exit 1
fi

for OUTPUT in $(git ls-files -- '*.cpp' '*.hpp')
do
	"${CLANG_FORMAT}" -style=file -i $OUTPUT
done

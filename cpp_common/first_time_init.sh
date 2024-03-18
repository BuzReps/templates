#!/bin/bash

rm -- "$0"

cpp_common="$MY_TEMPLATES_DIR/cpp_common"
cp "$cpp_common/.clang-format" .
cp "$cpp_common/.clang-tidy" .
cp "$cpp_common/.editorconfig" .
cp "$cpp_common/.gitignore" .
cp "$cpp_common/CMakePresets.json" .
cp "$cpp_common/Makefile" .
cp "$cpp_common/README.md" .

if [ ! -d ".git" ]; then
	git init
	git add -A
	git submodule add git@github.com:microsoft/vcpkg.git
	./vcpkg/bootstrap-vcpkg.sh --disableMetrics
fi

make configure
make build

make run


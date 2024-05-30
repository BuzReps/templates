#!/bin/bash

cp $MY_TEMPLATES_DIR/common/clang-format/.clang-format .
cp $MY_TEMPLATES_DIR/common/clang-tidy/.clang-tidy .
cp $MY_TEMPLATES_DIR/common/.editorconfig .

if [ ! -d ".git" ]; then
	git init
	git add src/* \
		.clang-format \
		.clang-tidy \
		.editorconfig \
		.gitignore \
		.gitmodules \
		CMakeLists.txt \
		CMakePresets.json \
		Makefile \
		README.md
fi

make configure
make build

rm -- "$0"

make run


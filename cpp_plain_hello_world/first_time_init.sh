#!/bin/bash

if [ ! -d ".git" ]; then
	git init
	git add src/* \
		.clang-format \
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


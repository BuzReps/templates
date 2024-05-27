#!/bin/bash

if [ ! -d ".git" ]; then
	git init
	git add src/* \
		vcpkg.json \
		.clang-format \
		.editorconfig \
		.gitignore \
		.gitmodules \
		CMakeLists.txt \
		CMakePresets.json \
		Makefile \
		README.md
	git submodule add git@github.com:microsoft/vcpkg.git
	./vcpkg/bootstrap-vcpkg.sh --disableMetrics
fi

make configure
make build

rm -- "$0"

make run


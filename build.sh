#!/bin/bash

script_path="$(realpath "$0")"
here="$(dirname "$script_path")"
build_dir="$here/build"
if [[ ! -d "$build_dir" ]]; then
	mkdir -p "$build_dir"
fi

clean_build() {
	rm -rf "$build_dir"
}

build_all() {
	cd "$build_dir" || return 1
	cmake ..
	make
}

build_and_run_unittest() {
	cd "$build_dir" || return 1
	cmake ..
	make hunt_test
	./hunt_test
}

build_app_only() {
	cd "$build_dir" || return 1
	cmake ..
	make hunt
}

build_and_run() {
	cd "$build_dir" || return 1
	cmake ..
	make hunt
	./hunt
}

format_cpp() {
	cd "$here" || return 1
	clang-format --verbose -i *.cpp *.h
}

format_sh() {
	cd "$here" || return 1
	shfmt -w -l *.sh
}

case "$1" in
clean)
	clean_build
	;;
unitest | test)
	build_and_run_unittest
	;;
run)
	build_and_run
	;;
all)
	build_all
	;;
fmt | format)
	format_cpp
	format_sh
	;;
*)
	build_app_only
	;;
esac

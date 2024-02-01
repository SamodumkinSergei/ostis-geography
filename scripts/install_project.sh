#!/usr/bin/env bash
set -eo pipefail

source "$(cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)/set_vars.sh"

do_build_kb=1
do_build_problem_solver=1
do_build_sc_web=1


build_kb()
{
	echo "Building KB"
	cd "${APP_ROOT_PATH}"/scripts
	./build_kb.sh
}

build_problem_solver()
{
	cd "${APP_ROOT_PATH}"/scripts
	./install_problem_solver_deps.sh
	./install_py_sc_server_deps.sh
	./build_problem_solver.sh
}

build_sc_web() {
	cd "${APP_ROOT_PATH}"/sc-web || (echo "sc-web not downloaded." && exit 1)
	(cd scripts && .install_problem_solver_deps.sh)
	pip3 install -r requirements.txt
	./install_interface_deps.sh
}

set -eo pipefail

cd "${APP_ROOT_PATH}"

git submodule update --init --recursive
build_problem_solver
build_sc_web

while [ "$1" != "" ]; do
	case $1 in
		"--no_build_kb" )
			do_build_kb=0
			;;
		"--no_build_problem_solver" )
			do_build_problem_solver=0
			do_build_kb=0
			;;
		"--no_build_sc_web" )
			do_build_sc_web=0
	esac
	shift
done

if [ $do_build_problem_solver == 1 ]; then
	build_problem_solver
fi

if [ $do_build_sc_web == 1 ]; then
	build_sc_web
fi

if [ $do_build_kb == 1 ]; then
	build_kb
fi

pip3 install "${APP_ROOT_PATH}"/problem-solver/py/py-sc-kpm

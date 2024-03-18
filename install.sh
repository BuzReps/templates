#!/bin/bash

# @brief Templates installer
#
# To add new template to the installer:
# 1. Add new menu entry in ${templates_menu_entries} and its directory name into ${templates_dirnames}
# 2. [Optional] Provide custom installation logic in case statement at the end of the file

# User menu entries
templates_menu_entries=(
	"[C++] [vcpkg] Hello world"
	"[C++] [vcpkg] [GLFW] Hello triangle"
)

# Templates directory in repository. Used for simple copying
# Indices should match entries in user menu
templates_dirnames=(
	"cpp_vcpkg_hello_world"
	"cpp_vcpkg_opengl_hello_triangle"
)

# Set templates directory path in ${templates_dir}
function get_templates_dir() {
	if [[ -v MY_TEMPLATES_DIR ]]; then
		templates_dir="${MY_TEMPLATES_DIR}"
	else
		templates_dir=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
	fi
}

# Ask user for project name and store result in ${project_name}
function get_project_name() {
	echo -n "Project name: "
	read -r project_name
}

# Ask user for template to intsall and store selected 1-indexed menu entry in ${REPLY}
function get_template_to_install() {
	local exit_option_index=$(( ${#templates_menu_entries[@]} + 1))
	PS3="> "
	echo "Select project template:"
	select selected_option in "${templates_menu_entries[@]}" "Exit"; do
		if [[ ${REPLY} -eq ${exit_option_index} ]]; then
			exit 0
		elif [[ -n "${selected_option}" ]]; then
			break
		fi
	done
}

get_template_to_install
# Installer return code
ret=0
case ${REPLY} in
	# Add custom install logic here
	# Warning: REPLY is 1-indexed menu entry index,
	#          ${templates_dirnames} is 0-indexed
	# Example:
	# "1")
	# 	get_project_name
	# 	get_templates_dir
	# 	cp -r "${templates_dir}/cpp_hello_world" "$(pwd)/${project_name}"
	# 	ret=$?
	# 	;;

	# Default: Ask user for dirname and install template by simply copying it
	*)
		get_project_name
		get_templates_dir
		template_index=$(( REPLY - 1 ))
		template_path="${templates_dir}/${templates_dirnames[$template_index]}"
		destination="$(pwd)/${project_name}"
		echo "Installing ${template_path} into ${destination}"
		cp -r "${template_path}" "${destination}"
		ret=$?
		;;
esac
exit $ret


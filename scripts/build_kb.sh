#!/usr/bin/env bash
set -eo pipefail

source "$(cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)/set_vars.sh"
"${BINARY_PATH}/sc-builder" -i "${APP_ROOT_PATH}/repo.path" -o "${APP_ROOT_PATH}/kb.bin" --clear

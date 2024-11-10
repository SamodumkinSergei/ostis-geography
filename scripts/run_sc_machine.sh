#!/usr/bin/env bash
set -eo pipefail

source "$(cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)/set_vars.sh"

"$APP_ROOT_PATH"/bin/sc-machine -c "$APP_ROOT_PATH"/ostis-geography.ini "$@"

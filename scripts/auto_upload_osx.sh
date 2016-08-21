#!/bin/bash

fswatch="/usr/local/bin/fswatch"

PROJECT_DIR="$(dirname "${BASH_SOURCE[0]}")/.."
RPI_HOST="192.168.116.29"

function run_rsync {
	echo -n "$(date +"%T"): Sync start... "
	echo -ne "\033]0;Uploading...\007"
	rsync -azPq --delete \
		--exclude ".*/" --exclude ".*" --exclude "tmp/" \
		. \
		pi@${RPI_HOST}:/home/pi/Devel/SoapyOsmo
	echo "done."
	echo -ne "\033]0;Idle\007"
}

cd ${PROJECT_DIR}
run_rsync
${fswatch} -o . | while read f; do run_rsync; done
#!/bin/sh
# Script that synchronizes the local test data

TESTS_INPUT_DIRECTORY="tests/input"
TEST_SET="public"
TEST_FILES="image.bin image.cue"

mkdir -p "${TESTS_INPUT_DIRECTORY}/${TEST_SET}"

for TEST_FILE in ${TEST_FILES}
do
	URL="https://raw.githubusercontent.com/dfirlabs/cue-specimens/refs/heads/main/specimens/cdrdao/${TEST_FILE}"

	curl -L -o "${TESTS_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL}
done

sed -i'~' 's?specimens/cdrdao/??' "${TESTS_INPUT_DIRECTORY}/${TEST_SET}/image.cue"

mkdir -p "${TESTS_INPUT_DIRECTORY}/.libodraw/${TEST_SET}"
echo "image.cue" > "${TESTS_INPUT_DIRECTORY}/.libodraw/${TEST_SET}/files"

mkdir -p "${TESTS_INPUT_DIRECTORY}/.odrawinfo/${TEST_SET}"
echo "image.cue" > "${TESTS_INPUT_DIRECTORY}/.odrawinfo/${TEST_SET}/files"

mkdir -p "${TESTS_INPUT_DIRECTORY}/.odrawverify/${TEST_SET}"
echo "image.cue" > "${TESTS_INPUT_DIRECTORY}/.odrawverify/${TEST_SET}/files"

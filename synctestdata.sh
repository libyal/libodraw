#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20161009

TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="image.bin image.cue";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	URL="https://github.com/dfirlabs/cue-specimens/blob/main/specimens/cdrdao/${TEST_FILE}?raw=true";

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL};
done

mkdir -p "${TEST_INPUT_DIRECTORY}/.libodraw/${TEST_SET}";
echo "image.cue" > "${TEST_INPUT_DIRECTORY}/.libodraw/${TEST_SET}/files";

mkdir -p "${TEST_INPUT_DIRECTORY}/.odrawinfo/${TEST_SET}";
echo "image.cue" > "${TEST_INPUT_DIRECTORY}/.odrawinfo/${TEST_SET}/files";

mkdir -p "${TEST_INPUT_DIRECTORY}/.odrawverify/${TEST_SET}";
echo "image.cue" > "${TEST_INPUT_DIRECTORY}/.odrawverify/${TEST_SET}/files";


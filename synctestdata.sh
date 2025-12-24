#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20251217

REPOSITORY="dfirlabs/cue-specimens";
TEST_DATA_PATH="specimens/cdrdao";
TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="image.bin image.cue";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";
mkdir -p "${TEST_INPUT_DIRECTORY}/.libodraw/${TEST_SET}";
mkdir -p "${TEST_INPUT_DIRECTORY}/.odrawinfo/${TEST_SET}";
mkdir -p "${TEST_INPUT_DIRECTORY}/.odrawverify/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	URL="https://raw.githubusercontent.com/${REPOSITORY}/refs/heads/main/${TEST_DATA_PATH}/${TEST_FILE}";

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL};
done

echo "image.cue" > "${TEST_INPUT_DIRECTORY}/.libodraw/${TEST_SET}/files";
echo "image.cue" > "${TEST_INPUT_DIRECTORY}/.odrawinfo/${TEST_SET}/files";
echo "image.cue" > "${TEST_INPUT_DIRECTORY}/.odrawverify/${TEST_SET}/files";

sed 's?specimens/cdrdao/??' -i "${TEST_INPUT_DIRECTORY}/${TEST_SET}/image.cue";


#!/usr/bin/env bash

mkdir release

cp dogma-editor release
cp readme.org release
cp bulkdata.db release
cp LICENSE release

tar -czvf dogma-editor-release.tar.gz release

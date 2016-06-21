#!/usr/bin/bash

CUR_VER=`sed -n \
           's/\(.*DIARYENGINE\_VERSION=.*\"\)\([0-9]*.[0-9]*\).*/\2/p' \
            < common.pri`

NEW_VER=`echo "$CUR_VER" | awk -F '.' '{printf "%d.%d", $1, $2+1}'`

sed \
's/\(.*DIARYENGINE\_VERSION=.*\"\)\([0-9]*.[0-9]*\)\(.*\)/\1'"$NEW_VER"'\3/' \
< common.pri > common.pri.tmp

mv common.pri.tmp common.pri

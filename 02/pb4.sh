#!/bin/bash

LIST=`find . -name "*c"`
for FNAME in $LIST
do
    LINES=`cat $FNAME | wc -l`
    if test $LINES -gt 20
    then
        echo "$FNAME are $LINES linii"
    fi
done
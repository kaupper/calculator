#!/bin/sh
find ./* -type d | while read line; do
	cp $1 $line
done

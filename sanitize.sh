#!/bin/bash

source=$1

if [[ ! -f "$source" ]]; then
  echo $source not found
  exit 1
fi

tmp=$(mktemp)

awk '
  {
    sub(/[[:space:]]+$/, "")

    if ($0 == "") {
      blank = 1
      next
    }

    if (seen && blank) print ""
    print
    seen = 1
    blank = 0
  }

  END {
    if (!seen) print ""
  }
' "$source" > $tmp && mv $tmp "$source"

#!/usr/bin/env bash

function main() {
  echo "Copying build/bin/barrierc to /usr/local/bin/..." >&2
  sudo cp build/bin/barrierc /usr/local/bin/
}

main "$@"


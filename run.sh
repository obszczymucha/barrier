#!/usr/bin/env bash

function main() {
  sudo systemctl stop barrier.service
  ./build.sh && sudo build/bin/barrierc -f --name pi 192.168.1.198:9696
}

main "$@"


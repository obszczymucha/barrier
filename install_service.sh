#!/usr/bin/env bash

function main() {
  sudo cp service/* /etc/systemd/system/
  sudo systemctl daemon-reload
  sudo systemctl enable barrier.timer
  sudo systemctl enable barrier_stop.timer
  sudo systemctl restart barrier.timer
  sudo systemctl restart barrier_stop.timer
}

main "$@"


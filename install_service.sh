#!/usr/bin/env bash
# shellcheck disable=SC2155 # Declare and assign separately.

function systemctl_property() {
  systemctl show --property="$1" barrier.service | sed 's/.*=//'
}

function main() {
  sudo cp service/* /etc/systemd/system/
  sudo systemctl daemon-reload
  sudo systemctl enable barrier.timer
  sudo systemctl enable barrier_stop.timer
  sudo systemctl restart barrier.timer
  sudo systemctl restart barrier_stop.timer

  echo "barrier.service status:" >&2

  local loaded=$(systemctl_property "LoadState")
  local active=$(systemctl_property "ActiveState")
  local triggered_by=$(systemctl_property "TriggeredBy")
  local next_trigger=$(systemctl_property "NextElapseUSecRealtime")

  echo "Status: $active ($loaded)"
  echo "Next trigger: $next_trigger ($triggered_by)"
}

main "$@"


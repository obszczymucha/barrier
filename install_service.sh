#!/usr/bin/env bash
# shellcheck disable=SC2155 # Declare and assign separately.

function systemctl_property() {
  systemctl show --property="$2" barrier."$1" | sed 's/.*=//'
}

function main() {
  sudo cp service/* /etc/systemd/system/
  sudo systemctl daemon-reload
  sudo systemctl enable barrier.service
  sudo systemctl enable barrier.timer
  sudo systemctl enable barrier_stop.timer
  sudo systemctl restart barrier.timer
  sudo systemctl restart barrier_stop.timer

  local loaded=$(systemctl_property "service" "LoadState")
  local active=$(systemctl_property "service" "ActiveState")
  local triggered_by=$(systemctl_property "service" "TriggeredBy")
  local next_trigger=$(systemctl_property "timer" "NextElapseUSecRealtime")

  echo "barrier.service status: $active ($loaded)" >&2
  echo "Next trigger: $next_trigger (by $triggered_by)" >&2
}

main "$@"


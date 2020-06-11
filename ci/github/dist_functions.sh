function get_package_name() {
  if git describe --match 'nightly_*' --exact-match then
    echo $(git describe --match  "nightly_*" --exact-match)
    return
  fi

  if git describe --match 'release_*' --exact-match then
    local releaseTag = $(git describe --match "release_*" --exact-match)
  fi

  echo "unknown_config"
}

#!/usr/bin/env bash
# Make sure all dependencies are installed and ready to go.

# Have everything in the Docker container use vim instead of Joe.
export VISUAL=vim
export EDITOR="$VISUAL"

# Check if package is installed, install it otherwise.
function maybe-install {
  if ! dpkg-query -W -f='${Status}' "$1" | grep "ok installed"; then
    apt install --yes --no-install-recommends "$1"
  fi
}

# Check if directory exists and is not empty.
function dir-ok {
  if [[ -d "$1" && -n "$(ls -A "$1")" ]]; then
    true
  else
    false
  fi
}

apt autoremove -y

apt update \
  && apt upgrade -y \
  && maybe-install screen \
  && maybe-install rsync \
  && maybe-install gdb \
  && maybe-install curl

# Manually install go, to get a more recent version.
# If we don't, we can't use go install, and we can't
# use shfmt.

# If go isn't found, manually source the ~/.bashrc file.
if ! dir-ok /usr/local/go; then
  curl -OL https://go.dev/dl/go1.17.6.linux-amd64.tar.gz \
    && tar -C /usr/local -xvf go1.17.6.linux-amd64.tar.gz \
    && rm -rf go1.17.6.linux-amd64.tar.gz \
    && echo "export PATH=$PATH:/usr/local/go/bin" >>"$HOME"/.bashrc
  source "$HOME"/.bashrc
  go version || exit
fi

cd || exit
if ! dir-ok src; then
  mkdir -p src
  cd src || exit
  git clone https://github.com/jfoote/exploitable.git
fi

cd || exit
if ! dir-ok go; then
  mkdir -p go
  go get -u github.com/bnagy/crashwalk/cmd/...
  go install mvdan.cc/sh/v3/cmd/shfmt@latest
fi

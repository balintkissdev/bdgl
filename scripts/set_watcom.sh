#!/usr/bin/env bash

# Include
. "$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/internal/common.sh"

# Use ". setwatcom.sh" command to set Open Watcom build environment

# Modify Open Watcom installation path here
WATCOM=$DEPS_DIR/open-watcom-v2

# Do not touch these!

# TODO: Tidy code
if type chmod > /dev/null; then
  chmod u+x $SCRIPTS_DIR/internal/*.sh
fi

if [ -z $WATCOM_P ]; then
  WATCOM_P=$WATCOM

  # Detect architecture and set PATH
  if [ "msys" == "$OSTYPE" ] || [ "win32" == "$OSTYPE" ]; then
    if [ "x86_64" == $(uname -m) ]; then
      OS_TEXT="Windows 64-bit"
      WATCOM_BINDIRS=$WATCOM_P/binnt64:$WATCOM_P/binnt
    else
      OS_TEXT="Windows 32-bit"
      WATCOM_BINDIRS=$WATCOM_P/binnt:$WATCOM_P/binnw
    fi
  else
    if [ "x86_64" == $(uname -m) ]; then
      OS_TEXT="Unix 64-bit"
      WATCOM_BINDIRS=$WATCOM_P/binl64:$WATCOM_P/binl
    else
      OS_TEXT="Unix 32-bit"
      WATCOM_BINDIRS=$WATCOM_P/binl
    fi
  fi

  PATH=$WATCOM_BINDIRS:$PATH
  EDPATH=$WATCOM_P/eddat
  WIPFC=$WATCOM_P/wipfc
  INCLUDE=$WATCOM_P/h

  # Exporting variables separately works with more different shells
  export WATCOM
  export WATCOM_BINDIRS
  export PATH
  export EDPATH
  export WIPFC
  export INCLUDE

  echo "Watcom root: $WATCOM"
  echo "System: $OS_TEXT"
  echo "Watcom binaries: $WATCOM_BINDIRS"
  echo
  echo "Open Watcom build environment is set! Use \"wmake\" to build the library.";
else
  echo "Open Watcom build environment was already set. Use \"wmake\" to build the library."
fi


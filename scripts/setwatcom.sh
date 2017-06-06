# Use ". setwatcom.sh" command to set Open Watcom build environment

# Modify Open Watcom installation path here
WATCOM=$HOME/bin/open-watcom

# Do not touch these!
if [ -z $WATCOM_P ]; then
  WATCOM_P=$WATCOM

  # Detect architecture and set PATH
  if [ 'x86_64' == $(uname -m) ]; then
    PATH=$WATCOM_P/binl64:$WATCOM_P/binl:$PATH
  else
    PATH=$WATCOM_P/binl:$PATH
  fi

  EDPATH=$WATCOM_P/eddat
  WIPFC=$WATCOM_P/wipfc
  INCLUDE=$WATCOM_P/h

  # Exporting variables separately works with more different shells
  export WATCOM
  export PATH
  export EDPATH
  export WIPFC
  export INCLUDE

  echo "Open Watcom build environment is set! Use \"wmake\" to build the library.";
else
  echo "Open Watcom build environment was already set. Use \"wmake\" to build the library."
fi

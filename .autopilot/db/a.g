#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/gregory/git/reconfigurable/Reconfigurable/solution1/.autopilot/db/a.g.bc ${1+"$@"}

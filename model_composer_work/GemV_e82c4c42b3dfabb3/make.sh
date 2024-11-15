#!/bin/bash
# This script sets up the environment for the Vitis AI Engine tools and runs
# 'make'.
. $XILINX_VITIS/.settings64-Vitis.sh
set -x
make "${@:1}"
   
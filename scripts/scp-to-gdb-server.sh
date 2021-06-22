#!/bin/bash

thisdir=$(dirname ${BASH_SOURCE[0]})

echo $thisdir

scp $thisdir/../cmake-build-debug/src/stm32f4-bootloader steve@192.168.1.18:/tmp/

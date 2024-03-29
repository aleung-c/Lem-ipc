#!/bin/bash

IPCS_S=`ipcs -s | grep aleung-c | cut -f2 -d" "`
IPCS_M=`ipcs -m | grep aleung-c | cut -f2 -d" "`
IPCS_Q=`ipcs -q | grep aleung-c | cut -f2 -d" "`


for id in $IPCS_M; do
  ipcrm -m $id;
done

for id in $IPCS_S; do
  ipcrm -s $id;
done

for id in $IPCS_Q; do
  ipcrm -q $id;
done

#!/bin/bash

if [ "$1" = "release" ]
then
    ./bin/release/fake-paint 
else
    ./bin/debug/fake-paint 
fi
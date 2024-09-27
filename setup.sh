#!/bin/bash

# Copy Eigen headers to the system include directory
wget -O eigen.zip https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip
unzip eigen.zip
cp -r eigen-3.4.0/Eigen /usr/local/include 
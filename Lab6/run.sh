#! /bin/sh
echo "Multi-threaded with Mutex lock"
./pi_mtnoRC 1000000
echo "Multi-threaded without Mutex lock"
./pi_mt 1000000

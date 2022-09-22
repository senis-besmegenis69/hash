
#!/bin/sh

set -xe

cc -O3 -I./../../include -o timed_hash.out ./../../source/hash256.c ./timed_hash.c
./timed_hash.out

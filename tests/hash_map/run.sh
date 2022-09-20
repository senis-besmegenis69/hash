
#!/bin/sh

set -xe

cc -O3 -I./../../include -o hash_map.out ./../../source/hash256.c ./hash_map.c
./hash_map.out

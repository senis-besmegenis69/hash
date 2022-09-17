
#!/bin/sh

set -xe

cc -O3 -I./../include -o test_suite.out ./../source/hash256.c ./test_suite.c
./test_suite.out

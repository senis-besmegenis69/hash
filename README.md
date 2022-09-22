
# hash256

TODO: add description, analysis, and more


## Usage:
```
Usage: ./hash256 [Commands] <args>

Commands:
    [ --text | -t ] <string>       Provide a string to be hashed
    [ --file | -f ] <path>         Provide file to be hashed
```

## To build:

```shell
> cd ./root-of-the-project
> make
```

## To run:

```shell
> cd ./root-of-the-project
> make run args-"any args you want"
```
or

```shell
> cd ./root-of-the-project/bin/<os>/<configuration>
> ./hash256 <args>
```

## Personal analysis:
I have run the hash function with 30k inputs from a single file with hopes to not get any collisions and it worked. The test file is in the repo/tests/\<somewhere\>.<br>
Next test was with 500k pharses and words in the secodn tests file. After a lot of fixes and experimentation, it also does not have any collisions.<br>
So that's good..<br>
I would like to add, that the hashinh algorithm also was deterministic, quite fast for my code quality and it WORKED!

## Required analysis and comparisons:
Tests from requirements file...

1. Testing files with one different symbol:
    - [x] [file1](./tests/one_symbol_file_1.txt)'s hash: 0d59b57c0c6841da422a51e9560b2490ca72e8f33a2693854b690aa581419b34
    - [x] [file2](./tests/one_symbol_file_2.txt)'s hash: 515fe97991ab42d73f482ad5d75e63898019673d5e181ea13e526c8d69ab91c1

2. Testing files with one different symbol:
    - [x] [file1](./tests/1000_plus_random_1.txt)'s hash: dcd5365c19f172bc9237915520825acc3286b928cd7ac7b94b334a32c8796b60
    - [x] [file2](./tests/1000_plus_random_2.txt)'s hash: 6de5b4c6c84b91958f655e48e225335aa9e6ad3afbc8d6ef1c5ebc627b5d6016

3. Testing files with one different symbol:
    - [x] [file1](./tests/1000_plus_one_diff_1.txt)'s hash: 6de5b4c6c84b91958f655e48e225335aa9e6ad3afbc8d6ef1c5ebc627b5d6016
    - [x] [file2](./tests/1000_plus_one_diff_2.txt)'s hash: d01b43f59ccf6d99cb140de413bdcf7f20486a3f27ddbfa707585f9943344fe3

4. Generated file for 4 test case. Used python. It is in ./tests folder.

5. Testing that test file from point 4 with my 'very good hashmap..'. To test it, open hash_map.c file, edit the file name to be read. And runt it. In case of a collision, it will inform the user in the terminal. RESULTS: no collisions!

6. TODO!!!

Conslusion: all of the files were hashed properly. Each file was produced with a hash unique to itself, each hash was 64 bytes long in hex format.


## Notes:
1. Bare in mind that HashMap in the repo is the worst possible implementation of that specific data structure. I just needed faster wayt to test huge amounts of inputs, and bubble-type solution was just the worst in terms of performance, thus my shitty HashMap is there...
2. I have deleted bubble test suite, because it had very poor performance and was not needed for further investigation of the algorithm's effectiveness. I strongly propose not to look for it, but if you want some meme content, try to look it up in the commits. It is somewhere there...

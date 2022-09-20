
# hash256

TODO: add description, analysis, and more


## Usage:
```
Usage: ./hash256 [Commands] <args>

Commands:
    [ --text | -t ] <string>       Provide a string to be hashed
    [ --file | -f ] <path>         Provide file to be hashed
```

## To build:<br>
```shell
> cd ./root-of-the-project
> make
```

## To run:<br>
```shell
> cd ./root-of-the-project
> make run args-"any args you want"
```
or<br>
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
Tests from requirements file...<br>


Notes:<br>
1. Bare in mind that HashMap in the repo is the worst possible implementation of that specific data structure. I just needed faster wayt to test huge amounts of inputs, and bubble-type solution was just the worst in terms of performance, thus my shitty HashMap is there...
2. I have deleted bubble test suite, because it had very poor performance and was not needed for further investigation of the algorithm's effectiveness. I strongly propose not to look for it, but if you want some meme content, try to look it up in the commits. It is somewhere there...

**Very basic** test, comparing output of `cross_reference` with `test_input.txt` as input and `test_output.txt` as expected result:

```bash
$ cat test_input.txt | ./cross_reference.out | diff test_output.txt -
```

**Very basic** test, comparing output of `getword_c` with `test_input.txt` as input and `test_output.txt` as expected result:

```bash
$ cat test_input.txt | ./getword_c.out | diff test_output.txt -
```

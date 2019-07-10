**Very basic** test, comparing output of `distinct_count` with `test_input.txt` as input and `test_output.txt` as expected result:

```bash
$ cat test_input.txt | ./distinct_count.out | diff test_output.txt -
```

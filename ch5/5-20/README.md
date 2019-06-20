Expand `dcl` to handle declarations with function argument types and qualifiers -.

- types = `int`, `char` etc
- qualifiers = `const`, `volatile` etc

**N.B** this does not support argument *names*:
- `dcl int func(char, const int)` :heavy_check_mark:
- `dcl int func(char foo, const int bar)` :x:

Original Grammar:

- `dcl`: optional `*`'s `direct-dcl`
- `direct-dcl`:
  - `name`
  - `(dcl)`
  - `direct-dcl()`
  - `direct-dcl[]`
  - `direct-dcl[size]`

Extended Grammar:
- `dcl`: optional `*`'s `direct-dcl`
- `direct-dcl`:
  - `name`
  - `(dcl)`
  - `direct-dcl()`
  - `direct-dcl(parameter-dcl)`
  - `direct-dcl[]`
  - `direct-dcl[size]`
- `parameter-dcl`: `parameter-dcl, specification dcl`
- `specification`:
    - `type specification`
    - `qualifier specification`
- `type`: `{int, char, float, double}`
- `qualifier`: `{const, volatile, restrict}`


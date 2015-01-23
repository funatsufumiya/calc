# Calc command for C and JavaScript

This is a practice for porting from javascript to c.

## Usage

#### JavaScript

- Add `<script>path/to/calc.js</script>`

```javascript
calc("(1 + 2^4) * 5"); // returns 85
calc("-2 * 4.3"); // -8.6
calc("sqrt(4) * log2(8)"); // 6
calc("exp(2) + log2(2)"); // 8.389056098930649
calc("logN(12^5, 12)"); // 5
calc("floor(4.6) * ceil(4.2)"); // 20
calc("max(3^2, 2^3) * min(floor(4.5), ceil(4.5))"); // 36
calc("sqrt(2) + cbrt(2)"); // 2.6741346122679683
calc("sq(sq(sq(3)))"); // 6561
calc("sin(PI) + cos(TWO_PI)"); // 1.0000000000000002
calc("atan(1) + acos(1)"); // 0.7853981633974483
```

#### C

- You can compile with `gcc -O3 calc.c -o calc` quickly
- Usage is like `calc [expression]`
- Type just `calc` to show help

```bash
calc "(1 + 2^4) * 5" # returns 85
calc "-2 * 4.3" # -8.6
calc "sqrt(4) * log2(8)" # 6
calc "exp(2) + log2(2)" # 8.389056098930649
calc "logN(12^5, 12)" # 5
calc "floor(4.6) * ceil(4.2)" # 20
calc "max(3^2, 2^3) * min(floor(4.5), ceil(4.5))" # 36
calc "sqrt(2) + cbrt(2)" # 2.6741346122679683
calc "sq(sq(sq(3)))" # 6561
calc "sin(PI) + cos(TWO_PI)" # 1.0000000000000002
calc "atan(1) + acos(1)" # 0.7853981633974483
```

## Build

type `rake all` or `rake js`, `rake c`

#### Requirements

- kmyacc [(official site in japanese)](http://www005.upp.so-net.ne.jp/kmori/kmyacc/)
- POSIX regex.h
- rake

## Differences between the javascript version and the C version

- `calc.jsy` has 190 lines, but `calc.y` has 401 lines (> 2x long).
- The javaScript version is simple and easy, but the c version is difficult to understand.
- The c version is blazingly fast when compared to the js.
- The javaScript has the garbage collector and are the higher level language, but the c isn't so. So the c must be controlled resources manually. That's why.

## License

You can use, copy, share and modify with any conditions.
# Lispy
Lispy is a yet another general purpose functional language written using Daniel Holden's tutorial ["Build your own Lisp"](https://buildyourownlisp.com/).

# Usage
- Download the latest release [here](https://github.com/KazakovDenis/lispy/releases/latest):
```bash
wget -O lispy https://github.com/KazakovDenis/lispy/releases/download/<version>/lispy_<version>_<platform>
chmod +x lispy
```
- Run: 
```
./lispy
````
- Play with it:
```
// define variables
def {x y} {1 2}

// do arithmetic operations
+ x y
/ x y

// define functions
(func {fib n} {
  select
    { (== n 0) 0 }
    { (== n 1) 1 }
    { otherwise (+ (fib (- n 1)) (fib (- n 2))) }
})

// call functions
fib 5
sum {1 2 3}
```
  
You can also check out the standard library `stdlib/stdlib.lispy` for examples.

# Devemopment
## Installation
```
make install
make run
```

## Troubleshooting
Do not forget to include actual paths:
```
./mpc/**
./include/**
./src/**
```

# Sources
- [Build your own Lisp](https://buildyourownlisp.com/)
- [Beej's Guide to C Programming](https://beej.us/guide/bgc/html/split/)

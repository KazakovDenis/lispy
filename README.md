# Lispy
Yet another Lisp.  
This is a pet project just to find out how programming languages work.

# Devemopment
## Installation
- `make install`
  
## Getting started
- `make run`

## Use
Check out `src/stdlib/stdlib.lispy` for basic definitions like:
```lisp
// define variables
def {x y} {1 2}

// arithmetic operations
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

## Troubleshooting
Do not forget to include actual paths:
```json
# .vscode/c_cpp_properties.json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}/mpc/**",
                "${workspaceFolder}/include/**",
                "${workspaceFolder}/src/**",
                "/usr/include/**",
                "/usr/include/x86_64-linux-gnu/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "gnu17",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-gcc-x64",
            "configurationProvider": "ms-vscode.makefile-tools"
        }
    ],
    "version": 4
}
```

# Sources
- [Build your own Lisp](https://buildyourownlisp.com/)
- [Beej's Guide to C Programming](https://beej.us/guide/bgc/html/split/)
- [Microsoft C reference](https://docs.microsoft.com/ru-ru/cpp/c-language/)

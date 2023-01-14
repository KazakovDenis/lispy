# Lispy
Yet another Lisp.

# Devemopment
## Installation
- `git clone --recurse-submodules https://github.com/KazakovDenis/lispy.git`
- `sudo apt install make`
- `make install`
  
## Getting started
- `make run`

## Troubleshooting
Do not forget to include actual paths:
```shell
# .vscode/c_cpp_properties.json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/**",
                "/usr/include/x86_64-linux-gnu/**"
            ],
            ...
        }
    ],
}
```

# Sources
- [Build your own Lisp](https://buildyourownlisp.com/)
- [Microsoft C reference](https://docs.microsoft.com/ru-ru/cpp/c-language/)

# ls-rewritten

Just some personal C project to learn the language, inspired by [Tony's C tutorial](https://www.youtube.com/watch?v=GqEeOrDk5DI).

This is basically temu version `ls` command provided by `GNU Core Utils`.

![Screenshot](res/ss.png)

## Features

- List directory contents
- `-a` show hidden files
- `-l` verbose output
- Multiple path arguments

## Usage

```
ls [-al] [path...]
```

## Download

[Download here if you don't want to compile](https://github.com/BaiduNano/ls-rewritten/releases)

## Build

```bash
./scripts/configure-release.sh
./scripts/build-release.sh
```

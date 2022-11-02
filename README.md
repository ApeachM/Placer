# Placement TermProject

[![Build Status](https://img.shields.io/badge/develop-ongoing%20-green)]()

This repository is for implementing the placement algorithm.
Used API is based on [OpenDB](https://github.com/The-OpenROAD-Project/OpenDB) API.

Currently, this project is for giving template of term project, which is for coursework of POSTECH, Korea:

## External Dependencies

You can use `Dockerfile` in the `OpenDB` submodule,
or you are required to install `cmake`, `siwg`, `spdlog`, `boost` in the `Ubuntu` Environment.

## How to build

```shell
git clone --recurse-submodules https://github.com/ApeachM/Placer.git
cd Placer
```

```shell
mkdir build
cd build
cmake ..
make
./placer
```

## Contributor

[Minjae Kim](https://github.com/ApeachM) in POSTECH
Email: kmj0824@postech.ac.kr
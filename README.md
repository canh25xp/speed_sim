# Speed sensor simulation and data analaysis Mini Project

## How to build

### Prerequisites

git, cmake, g++

#### Windows

```pwsh
winget install Git.Git
winget install Kitware.CMake
choco install mingw
```

#### Ubuntu/Debian

```bash
sudo apt install git cmake g++
```

### Build

```sh
git clone https://github.com/canh25xp/speed_sim
mkdir build
cd build
cmake .. -G "MinGW Makefiles"   # Windows
cmake .. -G "Unix Makefiles"    # Linux
cmake --build .                 # Or just `make` is enough
```

# Mystical Ninja Starring Goemon Decompilation
## Building
### Linux
#### Step 1: Install Dependencies
##### Debian/Ubuntu
Install the following dependencies using `apt`:
```bash
sudo apt install build-essential python3 git binutils-mips-linux-gnu
```

##### Arch Linux
Install the following depencies using `pacman`:
```bash
sudo pacman -S base-devel python
```

and then install the following AUR package: 
* [mips64-elf-binutils](https://aur.archlinux.org/packages/mips64-elf-binutils)

#### Step 2: Create Python Virtual Environment
Create a Python virtual environment and activate it:
```bash
python3 -m venv .venv
source .venv/bin/activate
```

#### Step 3: Install Python Dependencies
Install the required Python dependencies:
```bash
pip install -r requirements.txt
```

#### Step 4: Copy `baserom` Files
For each version of the game you want to build, copy a retail ROM of the version into the root directory of the repository and name it `baserom.<version>.z64`. For example, for the US version, copy the US retail ROM and name it `baserom.us.z64`.

**This is required for asset extraction.**

#### Step 5: Setup
Run the following command to extract assets from the ROM:
```bash
make setup
```

#### Step 6: Build
Run the following command to build the game:
```bash
make
```

if you want to build a specific version, you can specify it like this:
```bash
make VERSION=us
```

or change the default version at the top of the `Makefile`.

### Windows
Install Windows Subsystem for Linux (WSL) and follow the Linux instructions.

Here is a guide on how to install WSL: [How to install Linux on Windows with WSL](https://docs.microsoft.com/en-us/windows/wsl/install)

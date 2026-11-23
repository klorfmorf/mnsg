# Mystical Ninja Starring Goemon Decompilation

## Building

### Prerequisites

#### 1. Install `uv`

Install [`uv`](https://docs.astral.sh/uv/), which manages Python, project dependencies, and Ninja for the build:

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
```

#### 2. Install MIPS Binutils and a Host C Compiler

A host C compiler like GCC is required to perform C syntax checks and collect header dependencies. You do not need to install IDO 5.3 or `asm-processor` manually, as they are downloaded automatically during the build.

**Debian / Ubuntu:**

```bash
sudo apt install build-essential git binutils-mips-linux-gnu
```

**Fedora:**

```bash
sudo dnf install gcc git binutils-mips64-linux-gnu
```

**Arch Linux:**

```bash
sudo pacman -S base-devel
# Also install the mips64-elf-binutils package from the AUR.
```

### Setup and Build

1. Clone the repository along with its submodules:

   ```bash
   git clone https://github.com/klorfmorf/mnsg.git --recurse-submodules
   cd mnsg
   ```

2. Place a copy of your US retail ROM at `config/usa/baserom.z64`.

3. Configure and build the ROM:

   ```bash
   uv run configure.py
   uv run ninja
   ```

The first time you run `ninja`, it downloads `ido` and `asm-processor` into `build/tools/`, decompresses the base ROM, splits it with `splat`, builds `build/usa/mnsg.z64`, and verifies its SHA-1 checksum. If you later modify `config/usa/splat.yaml`, `symbol_addrs.txt`, or `reloc_addrs.txt`, Ninja will automatically re-split the ROM on the next build.

Here are the most common `configure.py` options (run `uv run configure.py --help` to view the full list):

| Option | Description |
| --- | --- |
| `--compressed` | Build and verify the compressed version of the ROM. |
| `--cross PREFIX` | Override the default prefix used for MIPS binutils. |
| `--tool NAME=PATH` | Use a local executable instead of downloading the tool automatically (for example, `--tool ido=/path/to/cc`). |
| `--host-cc CC` | Override the host C compiler used for syntax checks (`gcc` by default). |
| `--no-check` | Disable host C syntax checking. |

You can also use the following `ninja` commands for common build tasks:

| Command | Description |
| --- | --- |
| `uv run ninja` | Build the ROM and verify its SHA-1 checksum. |
| `uv run ninja build/usa/src/system/anime.c.o` | Build a single object file. |
| `uv run ninja tools` | Download all optional tools (`m2c`, `asm-differ`, `decomp-permuter`, and `objdiff-cli`). |
| `uv run ninja -t clean` | Remove build outputs (pass `-g` to remove downloaded tools and split files as well). |

## Decompilation Tools

Once you have downloaded the optional tools with `uv run ninja tools`, you can run the Python-based utilities through `uv`:

```bash
uv run python build/tools/m2c-*/m2c.py -t mips-ido-c asm/usa/nonmatchings/...
uv run python build/tools/asm-differ-*/diff.py -mw FUNC
uv run python build/tools/decomp-permuter-*/permuter.py DIR
```

Running `configure.py` also generates an `objdiff.json` configuration file for use with `objdiff`.

# Mystical Ninja Starring Goemon Decompilation

## Building

### Prerequisites

#### 1. Install `uv`

Install [`uv`](https://docs.astral.sh/uv/), which manages Python, project dependencies, and Ninja:

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
```

#### 2. Install MIPS Binutils and a Host C Compiler

GCC performs C syntax checks and collects header dependencies. IDO 5.3 and `asm-processor` are downloaded automatically during the build.

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
# Install the mips64-elf-binutils package from the AUR.
```

### Setup and Build

1. Clone the repository:

   ```bash
   git clone https://github.com/klorfmorf/mnsg.git --recurse-submodules
   cd mnsg
   ```

2. Copy your US retail ROM to `config/usa/baserom.z64`.

3. Configure and build the ROM:

   ```bash
   uv run configure.py
   uv run ninja
   ```

The first `ninja` invocation downloads `ido` and `asm-processor` into `build/tools/`, decompresses the base ROM, splits it with `splat`, builds `build/usa/mnsg.z64`, and verifies its SHA-1 checksum. Modifying `config/usa/splat.yaml`, `symbol_addrs.txt`, or `reloc_addrs.txt` triggers re-splitting automatically.

Common `configure.py` options (run `uv run configure.py --help` for the full list):

* `--compressed`: Build and verify the compressed ROM.
* `--cross PREFIX`: Override the MIPS binutils prefix.
* `--tool NAME=PATH`: Use a local executable instead of downloading the tool (for example, `--tool ido=/path/to/cc`).
* `--host-cc CC` / `--no-check`: Override or disable the host C syntax check (`gcc` by default).

Common `ninja` commands:

| Command | Description |
| --- | --- |
| `uv run ninja` | Build the ROM and verify its SHA-1 checksum. |
| `uv run ninja build/usa/src/system/anime.c.o` | Build a single object file. |
| `uv run ninja tools` | Download all optional tools (`m2c`, `asm-differ`, `decomp-permuter`, and `objdiff-cli`). |
| `uv run ninja -t clean` | Remove build outputs (pass `-g` to remove downloaded tools and split files as well). |

## Decompilation Tools

After running `uv run ninja tools`, invoke the Python tools via `uv`:

```bash
uv run python build/tools/m2c-*/m2c.py -t mips-ido-c asm/usa/nonmatchings/...
uv run python build/tools/asm-differ-*/diff.py -mw FUNC
uv run python build/tools/decomp-permuter-*/permuter.py DIR
```

Running `configure.py` also generates `objdiff.json` for `objdiff`.

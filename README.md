# Mystical Ninja Starring Goemon Decompilation

## Building

### Prerequisites

#### 1. Install `uv`
This project uses `uv` to manage Python tools and dependencies automatically. No manual Python setup is required.
*   **Windows:** `powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"`
*   **macOS / Linux:** `curl -LsSf https://astral.sh/uv/install.sh | sh`

#### 2. Install System Build Tools
**Debian/Ubuntu:**
```bash
sudo apt install build-essential git binutils-mips-linux-gnu
```

**Arch Linux:**
```bash
sudo pacman -S base-devel
# Install AUR package: mips64-elf-binutils
```

### Setup & Build

#### Step 1: Clone
Clone the repository:
```bash
git clone https://github.com/klorfmorf/mnsg.git
cd mnsg
```

#### Step 2: Place Baserom
Place your retail US ROM in the configuration directory and name it `baserom.z64`:

`config/usa/baserom.z64`

*(If you are building a different version, place the ROM in `config/<version>/baserom.z64`)*

#### Step 3: Setup
Run the setup command. `uv` will automatically download the correct Python version and install dependencies defined in the lockfile before extracting assets.
```bash
make setup
```

#### Step 4: Build
Build the ROM:
```bash
make
```

### Development (Optional)
If you are editing Python scripts and want your editor (Visual Studio Code, PyCharm, etc.) to recognize libraries, run:
```bash
uv sync
```
This creates a standard `.venv` folder that your editor can use for autocomplete and linting.
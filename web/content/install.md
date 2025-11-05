---
title: Installation
menu:
  after:
    name: install
    weight: 9
---

# 🧰 Installing `GDB` and `Make` on macOS and Windows

This guide provides detailed, step-by-step instructions to install and configure  
**GNU Debugger (GDB)** and **GNU Make** on both **macOS** and **Windows** systems.

---

## 🧩 Part 1: Installation on macOS

### ✅ Option 1: Using Homebrew (Recommended)

#### Step 1. Install Homebrew
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

After installation, add Homebrew to your shell:
```bash
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
eval "$(/opt/homebrew/bin/brew shellenv)"
```

#### Step 2. Install `make` and `gdb`
```bash
brew install make
brew install gdb
```

> ℹ️ **Note:** macOS ships with Apple’s version of `make`.  
> To use GNU Make (for better compatibility), run it as `gmake`, or alias it:
> ```bash
> echo "alias make=gmake" >> ~/.zshrc
> source ~/.zshrc
> ```

---

### ⚙️ Step 3. Code-signing `gdb` (Required by macOS Security)

macOS requires signed binaries for debugging.  
Follow these steps to create and trust a self-signed certificate.

#### 1. Open **Keychain Access**
- Press `Cmd + Space` → type **Keychain Access** → press **Enter**

#### 2. Create a Certificate
- Menu: **Keychain Access → Certificate Assistant → Create a Certificate**
  - **Name:** `gdb-cert`
  - **Identity Type:** Self Signed Root  
  - **Certificate Type:** Code Signing  
  - Check **“Let me override defaults”** and continue until you can select the **System** keychain.

#### 3. Trust the Certificate
- In Keychain, double-click **gdb-cert**
- Expand **Trust** → set **Code Signing** to **Always Trust**
- Close and authenticate when prompted

#### 4. Sign the GDB binary
```bash
codesign -s gdb-cert $(which gdb)
```

#### 5. Test the Installation
```bash
gdb --version
```

If no “not codesigned” error appears, setup is complete!

---

### 🧪 Step 4. Verify Installations
```bash
make --version
gdb --version
```

Expected output: version numbers for both tools (GNU Make ≥ 4.x, GDB ≥ 13.x)

---

## 🪟 Part 2: Installation on Windows

### ✅ Option 1: Using MinGW (Lightweight Native Toolchain)

#### Step 1. Download MinGW
- Visit [https://osdn.net/projects/mingw/](https://osdn.net/projects/mingw/)
- Download and run **mingw-get-setup.exe**

#### Step 2. Install Required Packages
1. In **MinGW Installation Manager**:
   - Under **Basic Setup**, mark:
     - `mingw32-base`
     - `mingw32-gdb`
2. Menu → **Installation → Apply Changes**

#### Step 3. Add MinGW to PATH
1. Open **Start → Edit System Environment Variables**
2. **Environment Variables → System Variables → Path → Edit**
3. Add:
   ```
   C:\MinGW\bin
   ```

#### Step 4. Verify Installation
Open **Command Prompt** or **PowerShell**:
```bash
gcc --version
make --version
gdb --version
```

---

### ✅ Option 2: Using MSYS2 (Modern GNU/Linux-like Environment)

#### Step 1. Install MSYS2
- Download from [https://www.msys2.org/](https://www.msys2.org/)
- Open **MSYS2 terminal** and update packages:
  ```bash
  pacman -Syu
  ```

#### Step 2. Install Toolchain
```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
pacman -S mingw-w64-ucrt-x86_64-gdb
```

#### Step 3. Add to PATH
Add:
```
C:\msys64\mingw64\bin
```
to your **System PATH**.

#### Step 4. Verify Installation
```bash
gcc --version
make --version
gdb --version
```

---

### ✅ Option 3: Using WSL (Windows Subsystem for Linux)

If you prefer a Linux environment inside Windows:

#### Step 1. Install WSL + Ubuntu
```powershell
wsl --install -d Ubuntu
```

#### Step 2. Install Developer Tools
Inside the Ubuntu terminal:
```bash
sudo apt update
sudo apt install build-essential gdb -y
```

#### Step 3. Verify
```bash
make --version
gdb --version
```

---

## 🧾 Summary Table

| Platform | Recommended Method | Tools Installed | Notes |
|-----------|-------------------|-----------------|-------|
| macOS | Homebrew | `make`, `gdb` | GDB must be code-signed |
| Windows | MinGW / MSYS2 | `gcc`, `make`, `gdb` | Add `bin` folder to PATH |
| Windows (Linux-like) | WSL (Ubuntu) | `build-essential`, `gdb` | No code-signing needed |

---

## 🧰 Troubleshooting Tips

| Issue | Possible Fix |
|-------|---------------|
| `gdb: not codesigned` on macOS | Repeat Step 3 (code-signing) |
| `make` not found | Ensure `brew` or `C:\MinGW\bin` is in PATH |
| Permission denied | Run terminal as Administrator (Windows) or use `sudo` (macOS/Linux) |
| `gcc` missing | Install compiler via `xcode-select --install` (macOS) or `mingw32-base` (Windows) |

---

## ✅ Verification Checklist

- [x] `make --version` works  
- [x] `gdb --version` works  
- [x] Code compiles with `gcc`  
- [x] PATH variables are correctly set  

---

*Prepared for classroom / lab setup in C programming & systems courses.*

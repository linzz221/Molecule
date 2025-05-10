# ✨ Simple Molecule

using [Libint](https://github.com/evaleev/libint) and [RapidJSON](https://github.com/Tencent/rapidjson) calculate integral.

- Read XYZ molecular geometry files
- Load basis sets from JSON files (compatible with [Basis Set Exchange](https://www.basissetexchange.org/))

## 📦 Dependencies
- [Libint v2](https://github.com/evaleev/libint) — for integral evaluation
- [RapidJSON](https://github.com/Tencent/rapidjson) — for parsing basis set files in JSON format
- C++20 or later
- Intel oneAPI (using `icpx` compiler)

## 🛠️ Compileing

```bash
mkdir build && cd build
cmake .. -DCMAKE_CXX_COMPILER=icpx
make -j10086
```

## 🚀 Usage 

```cpp
#include "Mol.h"

using namespace std;

int main() {
    // Load H2O molecule from XYZ file with sto-3g basis set (in Angstrom units)
    mole::Mol a("./h2o.xyz", "sto-3g", mole::c_unit::Ang);

    // Print basis set environment
    a.show_basis_env();

    // Compute and display overlap integrals
    auto overlap = a.intor_1e(mole::c_int1e::overlap);
    overlap.show();
    overlap.show_limited_columns();
    overlap.show_col(5);

    // Compute and display 2-electron integrals
    auto int2e = a.intor_2e();
    int2e.show_int2e();
}
```

- **Basis Set File (JSON):**
  Download from [Basis Set Exchange](https://www.basissetexchange.org/) and save as, for example, `sto-3g.json`.


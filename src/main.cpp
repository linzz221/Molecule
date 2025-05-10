#include "Mol.h"

using namespace std;

int main() {
    // basis file is xxx.json, can download from https://www.basissetexchange.org/
    mole::Mol a("./h2o.xyz","sto-3g",mole::c_unit::Ang);
    a.show_basis_env();
    auto overlap = a.intor_1e(mole::c_int1e::overlap);
    overlap.show();
    overlap.show_limited_columns();
    overlap.show_col(5);
    auto int2e = a.intor_2e();
    int2e.show_int2e();
}
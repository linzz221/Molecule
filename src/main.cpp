#include "Mol.h"

using namespace std;

int main() {
    mole::Mol a("./h2o.xyz","6-31+g",mole::c_unit::Ang);
    //a.show_basis_env();
    auto ov = a.intor_1e(mole::c_int1e::overlap);
    ov.show_row(0);
    ov.show_col(0);
    ov.show_limited_columns(5);

}
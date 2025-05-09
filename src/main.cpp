#include "Mol.h"
#include "int2e.h"

using namespace std;

int main() {
    mole::Mol a("./h2o.xyz","sto-3g",mole::c_unit::Ang);
    //a.show_basis_env();
    auto int2e = std::move(a.intor_2e());
    int2e.show_int2e();
    // intor_2e.show_int2e();

}
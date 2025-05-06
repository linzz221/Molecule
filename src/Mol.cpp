#include <numeric>
#include <algorithm>

#include "Mol.h"
#include "constant.h"

namespace mole {
	using std::ifstream;

	Mol::Mol(const std::string& xyzname_, const std::string& basis_, const c_unit& unit_) :
        xyzname(xyzname_), basis(basis_), unit(unit_) {

        readxyz(xyzname_);
        nele = std::accumulate(atomnumsequ.begin(), atomnumsequ.end(), 0);
		make_atoms_intor();
		intor_env = std::move(intor::basisenv(basis, atoms_intor));
    }

	void Mol::readxyz(const std::string& xyzname_) {
		ifstream xyzfile(xyzname_);
		if (!xyzfile.is_open()) {
			throw std::runtime_error("Failed to open file: " + xyzname_);
		}
		xyzfile >> natom;
		atomlabel.resize(natom);
		atomnumsequ.resize(natom);

		vd coor_temp(natom * 3, 0.0);

		std::string name;
		double x, y, z;
		for (ll i = 0; i < natom; ++i) {
			xyzfile >> name >> x >> y >> z;

			atomlabel[i] = name;
			atomnumsequ[i] = cs::atomic_number.at(name);

			coor_temp[i * 3] = x;
			coor_temp[i * 3 + 1] = y;
			coor_temp[i * 3 + 2] = z;
		}
		xyzfile.close();

		if (unit == c_unit::Ang) {
			std::ranges::transform(coor_temp, coor_temp.begin(), 
				[](double x) { return x / cs::coor_au2A; });
		}

		coor = math::Mat2d(natom, 3, coor_temp);
	}

	void Mol::make_atoms_intor() {
		atoms_intor.resize(natom);
		for (ll i = 0; i < natom; ++i) {
			atoms_intor[i].atom_number = atomnumsequ[i];
			atoms_intor[i].x = coor.index(i, 0);
			atoms_intor[i].y = coor.index(i, 1);
			atoms_intor[i].z = coor.index(i, 2);
		}
	}


	vector<pair<double, array<double, 3>>> Mol::make_nuc_int_need() {
		vector<pair<double, array<double, 3>>> result(natom);
		for (ll i = 0; i < natom;++i) {
			result[i] = { atomnumsequ[i], 
				{{coor.index(i, 0), coor.index(i, 1), coor.index(i, 2)}} };
		}
		return result;
	}


	math::Mat2d Mol::intor_1e(const c_int1e need) {

		intor::Libint_guard libguard;

		switch (need) {
		case c_int1e::overlap: {
			return in_intor.calc_other_1e(c_int1e::overlap, intor_env);
		}
		case c_int1e::kinetic: {
			return in_intor.calc_other_1e(c_int1e::kinetic, intor_env);
		}
		case c_int1e::nuclear: {
			return in_intor.calc_nuclear(intor_env, make_nuc_int_need());
		}
		default:
			throw std::invalid_argument("Invalid integral type");
		}
	}

	void Mol::show_basis_env() const {
		intor_env.show_data();
	}
}

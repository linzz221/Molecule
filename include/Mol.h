#ifndef MOLE_MOL_H
#define MOLE_MOL_H

#include <fstream>
#include <array>

#include "Mat2d.h"
#include "int1e.h"
#include "base_struct.h"

namespace mole {
	using std::vector;
	using std::pair;
	using std::array;
	using vd = std::vector<double>;
	using vs = std::vector<std::string>;
	using ll = long long;

	enum class c_unit { AU, Ang };

	class Mol {
	public:
		std::string xyzname;
		std::string basis;
		c_unit unit;
		ll natom;
		ll nele;
		vs atomlabel;
		vd atomnumsequ;
		math::Mat2d coor;

		Mol() = default;
		Mol(const std::string& xyzname_, const std::string& basis_, 
			const c_unit& unit_);
		~Mol() = default;

		void showcoor() const { coor.show(); }
		ll get_nbasis() const { return intor_env.nbasis; }
		ll get_nshell() const { return intor_env.nshell; }

		math::Mat2d intor_1e(const c_int1e need);

		void show_basis_env() const;

	private:
		vector<Atom> atoms_intor;
		intor::int1e in_intor;
		intor::basisenv intor_env;

		bool ok_for_intor = false;

		void readxyz(const std::string& xyzname_);
		void make_atoms_intor();
		vector<pair<double, array<double, 3>>> make_nuc_int_need();
	};

}

#endif // MOLE_MOL_H



#ifndef MOLE_BASIS_H
#define MOLE_BASIS_H

#include <string>
#include <vector>

#include "libint2.hpp"

#include "base_struct.h"

namespace mole::intor {
	using std::string;
	using std::vector;

	struct Libint_guard {
		Libint_guard() { libint2::initialize(); }
		~Libint_guard() { libint2::finalize(); }
	};

	class basisenv {
	public:
		long long nshell = 0;
		long long nbasis = 0;
		int max_l = 0;
		size_t max_nprim = 0;
		vector<long long> shell2bf;
		vector<libint2::Shell> shells{};

		basisenv() = default;
		~basisenv() = default;
		basisenv(const string& basis, vector<mole::Atom> atoms);
		void show_data() const;

	private:
		size_t calc_max_nprim() const;
		int calc_max_l() const;
		void calc_shell2bf();

	};
}


#endif // MOLE_BASIS_H



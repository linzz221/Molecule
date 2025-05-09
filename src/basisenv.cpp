#include <fstream>

#include "rapidjson/document.h"

#include "basisenv.h"

namespace mole::intor {
	using std::ifstream;
	using rapidjson::Value;

	basisenv::basisenv(const string& basis, vector<mole::Atom> atoms) {
		ifstream basisfile(basis + ".json");
		if (!basisfile.is_open()) {
			throw std::runtime_error("Basis file not found");
		}
		string basis_str((std::istreambuf_iterator<char>(basisfile)),
			std::istreambuf_iterator<char>());
		basisfile.close();
		rapidjson::Document basisjson;
		basisjson.Parse(basis_str.c_str());

		string funtype;
		int spdf_size;
		libint2::svector<double> exponents;
		libint2::svector<double> coeff_temp;
		libint2::svector<libint2::Shell::Contraction> contractions;
		std::array<double, 3> coor = { 0.0, 0.0, 0.0 };
		

		for (const auto& atom : atoms) {
			coor[0] = atom.x;
			coor[1] = atom.y;
			coor[2] = atom.z;

			const Value& allshell = basisjson["elements"]
				[std::to_string(atom.atom_number).c_str()]["electron_shells"];

			for (const auto& s : allshell.GetArray()) {
				funtype = s["function_type"].GetString();

				for (const auto& e : s["exponents"].GetArray()) {
					exponents.push_back(std::stod(e.GetString()));
				}

				spdf_size = s["angular_momentum"].Size();
				for (int i = 0; i < spdf_size; ++i) {
					for (const auto& c : s["coefficients"][i].GetArray()) {
						coeff_temp.push_back(std::stod(c.GetString()));
					}
					contractions.emplace_back(s["angular_momentum"][i].GetInt(), false, coeff_temp);
					shells.emplace_back(exponents, contractions, coor);
					contractions.clear();
					coeff_temp.clear();
				}	
				exponents.clear();
			}
		}

		nshell = shells.size();
		nbasis = std::accumulate(shells.begin(), shells.end(), 0,
			[](int sum, const libint2::Shell& shell) { return sum + shell.size(); });
		max_nprim = calc_max_nprim();
		max_l = calc_max_l();
		calc_shell2bf();
	}

	size_t basisenv::calc_max_nprim() const {
		const auto it = std::ranges::max_element(shells,
		                                   [](const libint2::Shell& a, const libint2::Shell& b) {
			                                   return a.nprim() < b.nprim();
		                                   });
		if (it != shells.end()) {
			return it->nprim();
		}
		else {
			throw std::runtime_error("No shells found");
		}
	}

	int basisenv::calc_max_l() const {
		int l = 0;
		for (const auto& s : shells) {
			for (const auto& c : s.contr) {
				l = std::max(l, c.l);
			}
		}
		return l;
	}

	void basisenv::calc_shell2bf() {
		shell2bf.reserve(nshell);
		long long n = 0;
		for(const auto& s : shells) {
			shell2bf.push_back(n);
			n += s.size();
		}
	}

	void basisenv::show_data() const {
		std::cout << "Number of shells: " << nshell << "\n";
		std::cout << "Number of basis functions: " << nbasis << "\n";
		std::cout << "Max angular momentum: " << max_l << "\n";
		std::cout << "Max number of primitives: " << max_nprim << "\n";
		std::cout << "Shell to basis function mapping:\n";
		std::cout << "shell2bf" << "\n";
		std::ranges::copy(shell2bf,
		                  std::ostream_iterator<long long>(std::cout,"\n"));
		std::ranges::copy(shells,
		                  std::ostream_iterator<libint2::Shell>(std::cout,"\n"));
		for(const auto& s : shells) {
			std::cout << s.size() << std::endl;
		}
	}
}
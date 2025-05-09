#include "int1e.h"

namespace mole::intor {
	using math::Mat2d;
	using ll = long long;

	Mat2d int1e::int1e_engine(libint2::Engine eng,const basisenv& env) {

		Mat2d result(env.nbasis, env.nbasis);
		const auto& bas_buffer = env.shell2bf;
		const auto& eng_result = eng.results();

		for (ll s1 = 0; s1 < env.nshell; ++s1) {
			for (ll s2 = 0; s2 <= s1; ++s2) {
				eng.compute(env.shells[s1], env.shells[s2]);
				const auto* int_data = eng_result[0];

				auto s1_start = bas_buffer[s1];
				auto s2_start = bas_buffer[s2];
				auto s1_size = env.shells[s1].size();
				auto s2_size = env.shells[s2].size();
				ll temp_s = 0;
				for (ll i = 0; i < s1_size; ++i) {
					for (ll j = 0; j < s2_size; ++j) {
						result.set_value(s1_start + i, s2_start + j, int_data[temp_s]);
						if (s1 != s2) {
							result.set_value(s2_start + j, s1_start + i, int_data[temp_s]);
						}
						++temp_s;
					}
				}
			}
		}
		return result;
	}

	Mat2d int1e::calc_other_1e(const c_int1e need, const basisenv& env) {
		switch (need) {
		case c_int1e::overlap: {
			libint2::Engine eng_o(libint2::Operator::overlap, env.max_nprim, env.max_l, 0);
			return int1e_engine(eng_o, env);
		}

		case c_int1e::kinetic: {
			libint2::Engine eng_k(libint2::Operator::kinetic, env.max_nprim, env.max_l, 0);
			return int1e_engine(eng_k, env);
		}

		default: {
			throw std::runtime_error("Invalid integral type");
		}
		}
	}

	Mat2d int1e::calc_nuclear(const basisenv& env,
			std::vector<std::pair<double,std::array<double,3>>> coor) {
		libint2::Engine eng_n(libint2::Operator::nuclear, env.max_nprim, env.max_l, 0);
		eng_n.set_params(coor);
		return int1e_engine(eng_n, env);
	}

}
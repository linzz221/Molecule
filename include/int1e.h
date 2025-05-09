#ifndef MOLE_INT1E_H
#define MOLE_INT1E_H

#include <array>

#include "Mat2d.h"
#include "basisenv.h"

namespace mole {
	enum class c_int1e { overlap,kinetic,nuclear };
}

namespace mole::intor {

	class int1e {
	using ll = long long;

	public:
		int1e() = default;
		~int1e() = default;

	static math::Mat2d calc_nuclear(const basisenv& env,
	                                std::vector<std::pair<double, std::array<double, 3>>> coor);

	static math::Mat2d calc_other_1e(mole::c_int1e need, const basisenv& env);

	private:
	static math::Mat2d int1e_engine(libint2::Engine eng, const basisenv& env);
	};
}

#endif // MOLE_INT1E_H


//
// Created by linzz on 25-5-9.
//

#ifndef MOLE_INT2E_H
#define MOLE_INT2E_H

#include "basisenv.h"

namespace mole::intor {
    using ll = long long;

    class int2e {
    public:
        int2e() = default;
        ~int2e() = default;
        bool has_value = false;

        explicit int2e(const ll aosize);
        double index(const ll i, const ll j, const ll k, const ll l) const;
        void set_value(const ll i, const ll j, const ll k, const ll l, const double v);

        void create_int2e_inmem(const basisenv& env);
        void show_int2e() const;

    private:
        vector<double> m_data;
        inline ll get_pair_index(const ll i, const ll j, const ll n) const;
        inline ll get_int2e_index(const ll i, const ll j, const ll k, const ll l) const;
        ll m_aosize;
        ll m_pair_size;
        ll m_int2e_size;
    };

}

#endif //MOLE_INT2E_H

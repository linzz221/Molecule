//
// Created by linzz on 25-5-9.
//

#include "int2e.h"

namespace mole::intor {
    int2e::int2e(const ll aosize) : m_aosize(aosize) , m_pair_size( aosize * (aosize + 1) / 2 ),
    m_int2e_size( m_pair_size * (m_pair_size + 1) / 2 ) {

    }

    ll int2e::get_pair_index(const ll i, const ll j, const ll n) const {
        if (i < j) {
            return j + i * n - i * (i + 1) / 2;
        }
        else {
            return i + j * n - j * (j + 1) / 2;
        }
    }

    ll int2e::get_int2e_index(const ll i, const ll j, const ll k, const ll l) const {
        const ll x = get_pair_index(i, j, m_aosize);
        const ll y = get_pair_index(k, l, m_aosize);
        return get_pair_index(x, y, m_pair_size);
    }


    double int2e::index(const ll i, const ll j, const ll k, const ll l) const {
        return m_data[ get_int2e_index(i, j, k, l) ];
    }

    void int2e::set_value(const ll i, const ll j, const ll k, const ll l, const double v) {
        m_data[ get_int2e_index(i, j, k, l) ] = v;
    }

    void int2e::create_int2e_inmem(const basisenv &env) {
        m_data.resize(m_int2e_size);
        Libint_guard libgu;
        libint2::Engine eng(libint2::Operator::coulomb, env.max_nprim, env.max_l, 0);
        const auto& bas_buffer = env.shell2bf;
        const auto& eng_result = eng.results();

        for (ll s1 = 0; s1 < env.nshell; ++s1) {
            for (ll s2 = 0; s2 <= s1; ++s2) {
                for (ll s3 = 0; s3 <= std::max(s1, s2); ++s3) {
                    ll s4need = s3 < std::max(s1, s2) ? s3 : std::min(s1, s2);
                    for (ll s4 = 0; s4 <= s4need; ++s4) {
                        eng.compute(env.shells[s1], env.shells[s2], env.shells[s3], env.shells[s4]);
                        const auto* int_data = eng_result[0];

                        auto s1_size = env.shells[s1].size();
                        auto s2_size = env.shells[s2].size();
                        auto s3_size = env.shells[s3].size();
                        auto s4_size = env.shells[s4].size();
                        auto s1_start = bas_buffer[s1];
                        auto s2_start = bas_buffer[s2];
                        auto s3_start = bas_buffer[s3];
                        auto s4_start = bas_buffer[s4];

                        ll temp_s = 0;
                        for (ll i = 0; i < s1_size; ++i) {
                            for (ll j = 0; j < s2_size; ++j) {
                                for (ll k = 0; k < s3_size; ++k) {
                                    for (ll l = 0; l < s4_size; ++l) {
                                        set_value(s1_start + i, s2_start + j, s3_start + k, s4_start + l, int_data[temp_s]);
                                        ++temp_s;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        has_value = true;
    }

    void int2e::show_int2e() const {
        if (!has_value) {throw std::runtime_error("Don`t have value now");}

        for (ll s1 = 0; s1 < m_aosize; ++s1) {
            for (ll s2 = 0; s2 <= s1; ++s2) {
                for (ll s3 = 0; s3 <= std::max(s1, s2); ++s3) {
                    ll s4need = s3 < std::max(s1, s2) ? s3 : std::min(s1, s2);
                    for (ll s4 = 0; s4 <= s4need; ++s4) {
                        std::cout << std::format("{} {} {} {}   {:>16.10f}\n", s1, s2, s3, s4, index(s1, s2, s3, s4));
                        }
                    }
                }
            }
        }


}

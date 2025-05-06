#ifndef MOLE_MAT2D_H
#define MOLE_MAT2D_H

#include <vector>

namespace mole::math {
    class Mat2d {

        using ll = long long;
        using vd = std::vector<double>;

    public:
        Mat2d() = default;
        ~Mat2d() = default;

        Mat2d(ll nrow_, ll ncol_, vd raw_data_ = {});

        ll size() const { return m_size; }
        ll row() const { return nrow; }
        ll col() const { return ncol; }

        void resize(ll nr, ll nc);
        double index(const ll i, const ll j) const { return raw_data[i * ncol + j]; }
        void set_value(const ll i, const ll j, const double nv) { raw_data[i * ncol + j] = nv; }

        void show_shape() const;
        void show(int prec = 8) const;
        void show_col(ll j,int prec = 8) const;
        void show_row(ll i,int prec = 8) const;
        void show_limited_columns(ll columns_per_line = 6, int prec = 8) const;

    private:
        ll nrow;
        ll ncol;
        ll m_size;
        vd raw_data;
    };
}

#endif // !MOLE_MAT2D_H



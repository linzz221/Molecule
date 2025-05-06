#include <format>
#include <iostream>

#include "Mat2d.h"

namespace mole::math {
    Mat2d::Mat2d(ll nrow_, ll ncol_, vd raw_data_) :
        nrow(nrow_), ncol(ncol_), m_size(nrow_* ncol_)
    {
        if (raw_data_.empty()) {
            raw_data.resize(m_size, 0.0);
        }
        else if (raw_data_.size() != m_size) {
            throw std::invalid_argument("Raw data size does not match matrix dimensions.");
        }
        else {
            raw_data = std::move(raw_data_);
        }
    }

    void Mat2d::resize(ll nr, ll nc) {
        if (nr * nc != m_size)
            throw std::invalid_argument("New size does not match matrix dimensions.");
        nrow = nr;
        ncol = nc;
    }

    void Mat2d::show_shape() const {
        std::cout << "Matrix shape: " << nrow << " x " << ncol << std::endl;
        std::cout << std::endl;
    }

    void Mat2d::show(int prec) const {
        for (ll i = 0; i < nrow; ++i) {
            for (ll j = 0; j < ncol; ++j) {
                std::cout << std::format("{:>{}.{}f}", index(i, j), prec + 6, prec);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

	void Mat2d::show_col(ll j,int prec) const {
		for(ll i = 0; i < nrow; ++i) {
			std::cout << std::format("{:>{}.{}f}",index(i,j),prec + 6,prec);
		}
		std::cout << "\n\n";
	}

	void Mat2d::show_row(ll i, int prec) const {
		for(ll j = 0; j < ncol; ++j) {
			std::cout << std::format("{:>{}.{}f}",index(i,j),prec + 6,prec);
		}
		std::cout << "\n\n";
	}

	void Mat2d::show_limited_columns(ll columns_per_line,int prec) const {
		if(columns_per_line <= 0) {
			throw std::invalid_argument("Number of columns per line must be greater than 0.");
		}

		// 按列分组打印
		for(ll start_col = 0; start_col < ncol; start_col += columns_per_line) {
			ll end_col = std::min(start_col + columns_per_line,ncol);

			for(ll i = 0; i < nrow; ++i) {
				for(ll j = start_col; j < end_col; ++j) {
					std::cout << std::format("{:>{}.{}f}",index(i,j),prec + 6,prec);
				}
				std::cout << std::endl; // 换行
			}
			std::cout << std::endl; // 每组列结束后换行
		}
		std::cout << std::endl;
	}
}
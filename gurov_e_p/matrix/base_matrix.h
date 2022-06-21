#pragma once
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

template <typename T>
class BaseMatrix {
	public:
		virtual ~BaseMatrix() = default;

		virtual void Resize(const size_t& r, const size_t& c, const T& value = 0) = 0;
		
		virtual T& Get(const size_t& r, const size_t& c) const = 0;
		virtual T* operator[](const size_t& r) const = 0;

		inline size_t Rows() const {
			return num_rows;
		}
		inline size_t Cols() const {
			return num_cols;
		}
		inline bool Empty() const {
			return num_rows * num_cols == 0;
		}

	protected:
		size_t num_rows = 0;
		size_t num_cols = 0;

		virtual void Reallocate(const size_t& r, const size_t& c) = 0;
};

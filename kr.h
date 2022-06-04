#include <initializer_list>
#include <stdexcept>

template <typename T>
class Rectangle {
public:
	Rectangle() = default;
	Rectangle(T _x1, _y1, _x3, _y3)
		: x1(_x1)
		, y1(_y1)
		, x3(_x3)
		, y3(_y3)
	{
		x1 = std::max(x1, x3); // (x1, y1) левая верхняя вершина, (x3, y3) правая нижняя, ими однозначно задается прямоугольник
		y1 = std::max(y1, y3);
		x3 = std::min(x1, x3);
		y3 = std::min(y1, y3);
		x2 = x3;
		y2 = y1;
		x4 = x1;
		y4 = y3;
		if ((x4 == x3) || (y1 == y4)) {
			throw std::exception("side can not be 0 !");
		}
	}
	Rectangle(const& Rectangle<T> other) 
		: x1(other.x1)
		, x2(other.x2)
		, x3(other.x3)
		, x4(other.x4)
		, y1(other.y1)
		, y2(other.y2)
		, y3(other.y3)
		, y4(other.y4) {
		if ((x4 == x3) || (y1 == y4)) {
			throw std::exception("side can not be 0 !");
		}
	}
	Rectangle(const std::initializer_list<T>& list);
	~Rectangle() = default;

	T Area() const {
		return std::abs(x1 - x2) * std::abs(y2 - y3);
	}
	T Perimeter() const {
		return std::abs(x1 - x2) * 2 + std::abs(y2 - y3) * 2;
	}

	Rectangle Unification(const Rectangle<T> &rhs) const {
			int x5 = std::min(x1, rhs.x1);
			int y5 = std::max(y4, rhs.y4);
			int x6 = std::max(x2, rhs.x2);
			int y6 = std::min(y2, rhs.y4);
			return Rectangle(x5, y5, x6, y6);
		}
	T AreaUnification(const Rectangle<T>& rhs) const {
		Rectangle un = Unification(rhs);
		return un.Area();
	}
	Rectangle Intersect(const Rectangle<T>& rhs) const {
		int x5 = std::max(x1, rhs.x1);
		int y5 = std::max(y1, rhs.y1);
		int x6 = std::min(x3, rhs.x3);
		int y6 = std::min(y3, rhs.y3);
		if ((x5 >= x6) || (y5 >= y6)) {
			return Rectangle(0, 0, 0, 0);
		}
		return Rectangle(x5, y5, x6, y6);
	}
	T AreaIntersect(const Rectangle<T>& rhs) const {
		Rectangle in = Intersect(rhs);
		return in.Area();
	}
	std::ostream& operator<<(std::ostream & out)
		{
			out << "(" << x1 << "; " << y1 << " )" << "   " << "(" << x2<< "; " << y2 << " )" << "\n" << "\n" << "(" << x3 << "; " << y3 << " )" << "   " << "(" << x4 << "; " << y4 << " )";
			return out;
		}
private:
	T x1, y1, x2, y2, x3, y3, x4, y4;
};
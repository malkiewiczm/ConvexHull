#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " #what " = " << what << std::endl)

struct vec2 {
	double x, y;
	bool read() {
		return scanf("%lf %lf", &x, &y) == 2;
	}
};

static inline std::ostream &operator<< (std::ostream &o, const vec2 &v)
{
	o << '(' << v.x << ", " << v.y << ')';
	return o;
}

template<typename T>
static inline std::ostream &operator<< (std::ostream &o, const std::vector<T> &v)
{
	for (auto item : v) {
		o << item << ", ";
	}
	return o;
}

using hull_t = std::vector<vec2>;

static inline double cross(const vec2 &a, const vec2 &b, const vec2 &c)
{
	return a.x*(b.y-c.y) - b.x*(a.y-c.y) + c.x*(a.y-b.y);
}

static bool lowest_y_cmp(const vec2 &lhs, const vec2 &rhs)
{
	if (lhs.y == rhs.y)
		return lhs.x < rhs.x;
	return lhs.y < rhs.y;
}

static vec2 origin;

static bool angle_cmp(const vec2 &lhs, const vec2 &rhs)
{
	return cross(origin, lhs, rhs) > 0;
}

static hull_t ch(hull_t &P)
{
	auto iter = std::min_element(P.begin(), P.end(), lowest_y_cmp);
	origin.x = iter->x;
	origin.y = iter->y;
	std::iter_swap(iter, P.begin());
	std::sort(P.begin(), P.end(), angle_cmp);
	hull_t h;
	if (P.size() < 2)
		return h;
	h.push_back(P[0]);
	h.push_back(P[1]);
	unsigned i = 2;
	while (i < P.size()) {
		const unsigned last = h.size() - 1;
		if (cross(h[last - 1], h[last], P[i]) > 0) {
			h.push_back(P[i]);
			++i;
		} else {
			h.pop_back();
		}
	}
	return h;
}

int main()
{
	hull_t P;
	for ( ; ; ) {
		vec2 p;
		if (p.read()) {
			P.push_back(p);
		} else {
			break;
		}
	}
	trace(P.size());
	const hull_t hull = ch(P);
	trace(hull.size());
	trace(hull);
}

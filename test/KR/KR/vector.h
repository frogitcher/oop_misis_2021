#pragma once
class TVector {
public:
	TVector() = default;
	~TVector() = default;

	TVector& operator=(const TVector& rhs);

	bool operator==(const TVector& rhs);
	bool operator!=(const TVector& rhs);

	TVector& operator+(const TVector& rhs);
	TVector& operator-(const TVector& rhs);
	

private:
	double numd;
};
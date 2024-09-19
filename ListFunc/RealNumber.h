#pragma once
#include "Expression.hpp"

class RealNumber : public Comparable {
public:
	RealNumber(double value);

	double getValue() const;
	virtual void print(std::ostream& os) const override;

	virtual bool operator==(const Comparable* other) const;
	virtual bool operator!() const override;

protected:
	virtual bool operator==(const RealNumber* other) const override;
	virtual bool operator==(const class ListLiteral* other) const override;

private:
	double value;
};
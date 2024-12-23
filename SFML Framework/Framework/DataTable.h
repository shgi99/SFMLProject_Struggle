#pragma once
class DataTable
{
public:
	enum class Types
	{
		String,
		Zombie,
		Item,
	};
	static const int TotalTypes = 3;

	DataTable(Types t) : type(t) {}
	~DataTable() = default;

	virtual bool Load() = 0;
	virtual void Release() = 0;

protected:
	Types type;
};


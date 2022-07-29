// Класс для работы с элементом массива

template <class T>
class Optional
{
private:
	static Optional<T>* empty;
	static bool emptyIsSet;
public:
	static Optional<T>* Empty()
	{
		if (!emptyIsSet)
		{
			empty = new Optional<T>();
			emptyIsSet = true;
		}
		return empty;
	}
private:
	T value;
	bool hasValue;
public:
	Optional(T value)
	{
		this->value = value;
		this->hasValue = true;
	}
private:
	Optional()
	{
		this->hasValue = false;
	}
public:
	T GetValue() const
	{
		if (this->hasValue)
			return this->value;
		else
			throw new Exception;
	}
	bool HasValue() const { return this->hasValue; }
	bool TryGetValue(T& value) const
	{
		if (!this->hasValue)
			return false;
		value = this->value;
		return true;
	}
public:
	bool operator==(Optional<T>& other)
	{
		return this->hasValue == other->hasValue && (!this->hasValue || this->value == other->value);
	}
	T operator() const
	{
		if (!this->hasValue)
			return false;
		return this->value;
	}
};
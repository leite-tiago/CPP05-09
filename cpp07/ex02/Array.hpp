#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <exception>
#include <cstddef>

template <typename T>
class Array
{
	private:
		T*				_array;
		unsigned int	_size;

	public:
		// Default constructor - creates empty array
		Array() : _array(NULL), _size(0) {}

		// Constructor with size parameter
		Array(unsigned int n) : _array(new T[n]()), _size(n) {}

		// Copy constructor
		Array(Array const & src) : _array(NULL), _size(0)
		{
			*this = src;
		}

		// Destructor
		~Array()
		{
			if (_array != NULL)
				delete[] _array;
		}

		// Assignment operator
		Array & operator=(Array const & rhs)
		{
			if (this != &rhs)
			{
				if (_array != NULL)
					delete[] _array;

				_size = rhs._size;
				if (_size > 0)
				{
					_array = new T[_size];
					for (unsigned int i = 0; i < _size; i++)
						_array[i] = rhs._array[i];
				}
				else
					_array = NULL;
			}
			return *this;
		}

		// Subscript operator - non-const version
		T & operator[](unsigned int index)
		{
			if (index >= _size)
				throw std::exception();
			return _array[index];
		}

		// Subscript operator - const version
		T const & operator[](unsigned int index) const
		{
			if (index >= _size)
				throw std::exception();
			return _array[index];
		}

		// Size member function
		unsigned int size() const
		{
			return _size;
		}
};

#endif

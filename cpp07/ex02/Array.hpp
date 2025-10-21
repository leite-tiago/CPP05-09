/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:10:54 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/21 16:10:02 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <exception>
#include <cstddef>
#include <cstdlib>

template <typename T>
class Array
{
	private:
		T*				_array;
		unsigned int	_size;

	public:
		Array() : _array(NULL), _size(0) {}

		Array(unsigned int n) : _array(new T[n]()), _size(n) {}

		Array(Array const & src) : _array(NULL), _size(0)
		{
			*this = src;
		}

		~Array()
		{
			if (_array != NULL)
				delete[] _array;
		}

		Array & operator=(Array const & other)
		{
			if (this != &other)
			{
				if (_array != NULL)
					delete[] _array;

				_size = other._size;
				if (_size > 0)
				{
					_array = new T[_size];
					for (unsigned int i = 0; i < _size; i++)
						_array[i] = other._array[i];
				}
				else
					_array = NULL;
			}
			return *this;
		}

		T & operator[](unsigned int index)
		{
			if (index >= _size)
				throw std::exception();
			return _array[index];
		}

		T const & operator[](unsigned int index) const
		{
			if (index >= _size)
				throw std::exception();
			return _array[index];
		}

		unsigned int size() const
		{
			return _size;
		}
};

#endif

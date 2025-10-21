/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:10:08 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/21 15:35:22 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <cstddef>

template <typename T, typename F>
void iter(T* array, const size_t length, F func)
{
	for (size_t i = 0; i < length; i++)
	{
		func(array[i]);
	}
}

#endif

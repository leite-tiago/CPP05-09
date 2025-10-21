/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:10:02 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/21 14:10:03 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template <typename T>
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T const & min(T const & a, T const & b)
{
	return (a < b) ? a : b;
}

template <typename T>
T const & max(T const & a, T const & b)
{
	return (a > b) ? a : b;
}

#endif

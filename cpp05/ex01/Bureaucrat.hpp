/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 21:08:26 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 19:42:49 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <exception>

class Form; // forward declaration para evitar inclusão circular

#define MAX_GRADE 1
#define MIN_GRADE 150

class Bureaucrat
{
	private:
		const std::string	name;
		int					grade;

	public:
		Bureaucrat();
		Bureaucrat(const Bureaucrat &other);
		Bureaucrat(const std::string &name, int grade);
		Bureaucrat &operator=(const Bureaucrat &other);
		~Bureaucrat();

		const std::string &getName() const;
		int getGrade() const;
		void incrementGrade();
		void decrementGrade();

		class GradeTooHighException : public std::exception {
		public:
			const char *what() const throw();
		};

		class GradeTooLowException : public std::exception {
		public:
			const char *what() const throw();
		};

		void signForm(class Form &form) const;
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat);

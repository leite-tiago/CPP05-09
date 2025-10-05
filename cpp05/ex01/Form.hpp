/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:45:13 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 19:50:55 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <exception>

class Bureaucrat; // forward declaration

class Form {
	private:
		std::string const name;
		bool isSigned;
		int const gradeToSign;
		int const gradeToExecute;

	public:
		Form();
		Form(std::string const &name, int gradeToSign, int gradeToExecute);
		Form(Form const &other);
		Form &operator=(Form const &other);
		~Form();

		std::string const &getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		void beSigned(Bureaucrat const &bureaucrat);

		class GradeTooHighException : public std::exception {
			const char* what() const throw();
		};

		class GradeTooLowException : public std::exception {
			const char* what() const throw();
		};

};

std::ostream &operator<<(std::ostream &os, Form const &form);

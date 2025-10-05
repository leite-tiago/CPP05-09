/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:45:13 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 20:20:04 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat; // forward declaration

#define MAX_GRADE 1
#define MIN_GRADE 150
class AForm {
	private:
		std::string const _name;
		bool              _isSigned;
		int const         _gradeToSign;
		int const         _gradeToExecute;
		std::string       _target; // target of the action

	protected:
		// Allow derived classes to access target for their action
		const std::string &getTarget() const;
		virtual void performAction() const = 0; // concrete action implemented by derived classes

	public:
		AForm();
		AForm(std::string const &name, int gradeToSign, int gradeToExecute, std::string const &target);
		AForm(AForm const &other);
		AForm &operator=(AForm const &other);
		virtual ~AForm();

		std::string const &getName() const;
		bool        getIsSigned() const;
		int         getGradeToSign() const;
		int         getGradeToExecute() const;

		void beSigned(Bureaucrat const &bureaucrat);
		void execute(Bureaucrat const &executor) const; // checks then calls performAction

		class GradeTooHighException : public std::exception {
			public: const char* what() const throw(); };
		class GradeTooLowException : public std::exception {
			public: const char* what() const throw(); };
		class NotSignedException : public std::exception {
			public: const char* what() const throw(); };
};

std::ostream &operator<<(std::ostream &os, AForm const &form);

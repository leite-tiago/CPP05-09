/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 21:08:33 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 19:50:55 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

static void printResult(const std::string &name, bool pass, const std::string &detail = "")
{
	std::cout << (pass ? "[OK]   " : "[FAIL] ") << name;
	if (!pass && !detail.empty())
		std::cout << " -> " << detail;
	std::cout << std::endl;
}

int main()
{
	int total = 0;
	int passed = 0;

	// Helper lambdas
	const std::string HIGH_MSG = "Grade too high!";
	const std::string LOW_MSG = "Grade too low!";

	// Test 1: Form default constructor
	++total; {
		try {
			Form f;
			bool ok = f.getName() == "Default" && f.getIsSigned() == false && f.getGradeToSign() == 150 && f.getGradeToExecute() == 150;
			if (ok) ++passed; printResult("FormDefaultConstructor", ok, "Valores inesperados");
		} catch (std::exception &e) { printResult("FormDefaultConstructor", false, e.what()); }
	}

	// Test 2: Form válido limites (1,1)
	++total; {
		try {
			Form f("Top", 1, 1);
			bool ok = f.getGradeToSign() == 1 && f.getGradeToExecute() == 1 && !f.getIsSigned();
			if (ok) ++passed; printResult("FormCtorTop", ok, "Limites incorretos");
		} catch (std::exception &e) { printResult("FormCtorTop", false, e.what()); }
	}

	// Test 3: Form válido limites (150,150)
	++total; {
		try {
			Form f("Low", 150, 150);
			bool ok = f.getGradeToSign() == 150 && f.getGradeToExecute() == 150;
			if (ok) ++passed; printResult("FormCtorLow", ok, "Limites incorretos");
		} catch (std::exception &e) { printResult("FormCtorLow", false, e.what()); }
	}

	// Test 4: Form gradeToSign demasiado alto (0)
	++total; {
		try { Form f("BadHighSign", 0, 10); printResult("FormCtorTooHighSign", false, "Não lançou exceção"); }
		catch (std::exception &e) { bool ok = e.what() == HIGH_MSG; if (ok) ++passed; printResult("FormCtorTooHighSign", ok, e.what()); }
	}

	// Test 5: Form gradeToExecute demasiado alto (0)
	++total; {
		try { Form f("BadHighExec", 10, 0); printResult("FormCtorTooHighExec", false, "Não lançou exceção"); }
		catch (std::exception &e) { bool ok = e.what() == HIGH_MSG; if (ok) ++passed; printResult("FormCtorTooHighExec", ok, e.what()); }
	}

	// Test 6: Form gradeToSign demasiado baixo (151)
	++total; {
		try { Form f("BadLowSign", 151, 10); printResult("FormCtorTooLowSign", false, "Não lançou exceção"); }
		catch (std::exception &e) { bool ok = e.what() == LOW_MSG; if (ok) ++passed; printResult("FormCtorTooLowSign", ok, e.what()); }
	}

	// Test 7: Form gradeToExecute demasiado baixo (151)
	++total; {
		try { Form f("BadLowExec", 10, 151); printResult("FormCtorTooLowExec", false, "Não lançou exceção"); }
		catch (std::exception &e) { bool ok = e.what() == LOW_MSG; if (ok) ++passed; printResult("FormCtorTooLowExec", ok, e.what()); }
	}

	// Test 8: beSigned sucesso
	++total; {
		try {
			Bureaucrat b("Signer", 10);
			Form f("FormA", 42, 50);
			// Ajustar até permissível: grade do bureaucrat tem de ser <= gradeToSign
			while (b.getGrade() > f.getGradeToSign()) b.incrementGrade();
			f.beSigned(b);
			bool ok = f.getIsSigned();
			if (ok) ++passed; printResult("FormBeSignedSuccess", ok, "Não ficou assinado");
		} catch (std::exception &e) { printResult("FormBeSignedSuccess", false, e.what()); }
	}

	// Test 9: beSigned falha (grade demasiado baixa)
	++total; {
		try {
			Bureaucrat b("LowGrade", 100);
			Form f("Need50", 50, 60);
			f.beSigned(b);
			printResult("FormBeSignedFail", false, "Não lançou exceção");
		} catch (std::exception &e) { bool ok = e.what() == LOW_MSG; if (ok) ++passed; printResult("FormBeSignedFail", ok, e.what()); }
	}

	// Test 10: signForm (Bureaucrat wrapper) sucesso
	++total; {
		try {
			Bureaucrat b("Wrapper", 45);
			Form f("Need45", 45, 60);
			b.signForm(f);
			bool ok = f.getIsSigned();
			if (ok) ++passed; printResult("BureaucratSignFormSuccess", ok, "Form não assinada");
		} catch (std::exception &e) { printResult("BureaucratSignFormSuccess", false, e.what()); }
	}

	// Test 11: signForm falha (mensagem de erro impressa)
	++total; {
		try {
			Bureaucrat b("WrapperLow", 100);
			Form f("Need50B", 50, 60);
			b.signForm(f); // Deve imprimir mensagem de falha; não verificamos stdout, só estado
			bool ok = !f.getIsSigned();
			if (ok) ++passed; printResult("BureaucratSignFormFail", ok, "Estado incorreto (assinou indevidamente)");
		} catch (std::exception &e) { printResult("BureaucratSignFormFail", false, e.what()); }
	}

	// Test 12: Repetir beSigned em formulário já assinado (não deve lançar pela lógica atual)
	++total; {
		try {
			Bureaucrat b("Again", 5);
			Form f("Repeat", 10, 20);
			while (b.getGrade() > f.getGradeToSign()) b.incrementGrade();
			f.beSigned(b);
			bool ok1 = f.getIsSigned();
			f.beSigned(b); // idempotente (não muda estado, não lança)
			bool ok = ok1 && f.getIsSigned();
			if (ok) ++passed; printResult("FormBeSignedRepeat", ok, "Estado alterado ou exceção");
		} catch (std::exception &e) { printResult("FormBeSignedRepeat", false, e.what()); }
	}

	// Test 13: Atribuição de Form (apenas isSigned copia)
	++total; {
		try {
			Form f1("Orig", 10, 20);
			Form f2("Dest", 50, 60);
			// Assinar f1
			Bureaucrat b("Sig", 5);
			f1.beSigned(b);
			f2 = f1;
			bool ok = f2.getIsSigned() == true && f2.getGradeToSign() == 50 && f2.getGradeToExecute() == 60 && f2.getName() == "Dest"; // const fields intact
			if (ok) ++passed; printResult("FormAssignment", ok, "Const fields alterados ou isSigned errado");
		} catch (std::exception &e) { printResult("FormAssignment", false, e.what()); }
	}

	// Test 14: operator<< para Form
	++total; {
		try {
			Form f("Printable", 23, 42);
			Bureaucrat b("Printer", 10);
			// assina (b tem grade 10 < 23, precisa subir? na verdade precisa ser <= 23; já é 10, então ok)
			f.beSigned(b);
			std::ostringstream oss;
			oss << f;
			std::string expected = "Form 'Printable' (sign grade 23, exec grade 42, signed: yes)";
			bool ok = (oss.str() == expected);
			if (ok) ++passed; printResult("FormOstreamOperator", ok, oss.str());
		} catch (std::exception &e) { printResult("FormOstreamOperator", false, e.what()); }
	}

	std::cout << "==============================" << std::endl;
	std::cout << "Passed " << passed << "/" << total << " tests" << std::endl;
	std::cout << "==============================" << std::endl;

	return (passed == total) ? 0 : 1;
}

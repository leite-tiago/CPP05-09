/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 21:08:33 by tborges-          #+#    #+#             */
/*   Updated: 2025/10/05 18:32:26 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
#include "Bureaucrat.hpp"

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

	// Test 1: Default constructor
	++total; {
		try {
			Bureaucrat b;
			bool ok = (b.getName() == "Default" && b.getGrade() == MIN_GRADE);
			if (ok) ++passed; printResult("DefaultConstructor", ok, "Unexpected values");
		} catch (std::exception &e) { printResult("DefaultConstructor", false, e.what()); }
	}

	// Test 2: Boundary constructor MAX_GRADE
	++total; {
		try {
			Bureaucrat top("Top", MAX_GRADE);
			bool ok = (top.getGrade() == MAX_GRADE);
			if (ok) ++passed; printResult("CtorMaxGrade", ok, "Grade mismatch");
		} catch (std::exception &e) { printResult("CtorMaxGrade", false, e.what()); }
	}

	// Test 3: Boundary constructor MIN_GRADE
	++total; {
		try {
			Bureaucrat low("Low", MIN_GRADE);
			bool ok = (low.getGrade() == MIN_GRADE);
			if (ok) ++passed; printResult("CtorMinGrade", ok, "Grade mismatch");
		} catch (std::exception &e) { printResult("CtorMinGrade", false, e.what()); }
	}

	// Test 4: Constructor too high
	++total; {
		try {
			Bureaucrat bad("TooHigh", MAX_GRADE - 1);
			printResult("CtorTooHigh", false, "Exception not thrown");
		} catch (std::exception &e) {
			bool ok = std::string(e.what()) == "Grade too high!";
			if (ok) ++passed; printResult("CtorTooHigh", ok, e.what());
		}
	}

	// Test 5: Constructor too low
	++total; {
		try {
			Bureaucrat bad("TooLow", MIN_GRADE + 1);
			printResult("CtorTooLow", false, "Exception not thrown");
		} catch (std::exception &e) {
			bool ok = std::string(e.what()) == "Grade too low!";
			if (ok) ++passed; printResult("CtorTooLow", ok, e.what());
		}
	}

	// Test 6: incrementGrade normal
	++total; {
		try {
			Bureaucrat mid("Mid", 42);
			mid.incrementGrade();
			bool ok = mid.getGrade() == 41;
			if (ok) ++passed; printResult("IncrementNormal", ok, "Wrong grade");
		} catch (std::exception &e) { printResult("IncrementNormal", false, e.what()); }
	}

	// Test 7: incrementGrade at max boundary (should throw)
	++total; {
		try {
			Bureaucrat top("Top", MAX_GRADE);
			top.incrementGrade();
			printResult("IncrementAtMax", false, "Exception not thrown");
		} catch (std::exception &e) {
			bool ok = std::string(e.what()) == "Grade too high!";
			if (ok) ++passed; printResult("IncrementAtMax", ok, e.what());
		}
	}

	// Test 8: decrementGrade normal
	++total; {
		try {
			Bureaucrat mid("Mid2", 42);
			mid.decrementGrade();
			bool ok = mid.getGrade() == 43;
			if (ok) ++passed; printResult("DecrementNormal", ok, "Wrong grade");
		} catch (std::exception &e) { printResult("DecrementNormal", false, e.what()); }
	}

	// Test 9: decrementGrade at min boundary (should throw)
	++total; {
		try {
			Bureaucrat low("Low", MIN_GRADE);
			low.decrementGrade();
			printResult("DecrementAtMin", false, "Exception not thrown");
		} catch (std::exception &e) {
			bool ok = std::string(e.what()) == "Grade too low!";
			if (ok) ++passed; printResult("DecrementAtMin", ok, e.what());
		}
	}

	// Test 10: Copy constructor
	++total; {
		try {
			Bureaucrat a("Alice", 10);
			Bureaucrat b(a);
			bool ok = (b.getName() == "Alice" && b.getGrade() == 10);
			if (ok) ++passed; printResult("CopyConstructor", ok, "Values mismatch");
		} catch (std::exception &e) { printResult("CopyConstructor", false, e.what()); }
	}

	// Test 11: Assignment operator (name não muda)
	++total; {
		try {
			Bureaucrat a("Alice", 10);
			Bureaucrat b("Bob", 20);
			b = a;
			bool ok = (b.getName() == "Bob" && b.getGrade() == 10);
			if (ok) ++passed; printResult("AssignmentOperator", ok, "Name mudou ou grade errada");
		} catch (std::exception &e) { printResult("AssignmentOperator", false, e.what()); }
	}

	// Test 12: operator<<
	++total; {
		try {
			Bureaucrat s("Stream", 5);
			std::ostringstream oss;
			oss << s;
			bool ok = (oss.str() == "Stream, bureaucrat grade 5.");
			if (ok) ++passed; printResult("OstreamOperator", ok, oss.str());
		} catch (std::exception &e) { printResult("OstreamOperator", false, e.what()); }
	}

	// Test 13: Múltiplos increments até limite (de 10 para 1) e exceção ao ultrapassar
	++total; {
		try {
			Bureaucrat x("IncSequence", 10);
			bool seqOk = true;
			for (int expected = 9; expected >= MAX_GRADE; --expected) {
				x.incrementGrade();
				if (x.getGrade() != expected) { seqOk = false; break; }
			}
			bool threw = false;
			try { x.incrementGrade(); } catch (std::exception &e) { threw = (std::string(e.what()) == "Grade too high!"); }
			bool ok = seqOk && threw && x.getGrade() == MAX_GRADE;
			if (ok) ++passed; printResult("IncrementSequenceToLimit", ok, seqOk ? (threw ? "" : "Did not throw at limit") : "Wrong intermediate grade");
		} catch (std::exception &e) { printResult("IncrementSequenceToLimit", false, e.what()); }
	}

	// Test 14: Múltiplos decrements até limite (de 145 para 150) e exceção ao ultrapassar
	++total; {
		try {
			Bureaucrat y("DecSequence", 145);
			bool seqOk = true;
			for (int expected = 146; expected <= MIN_GRADE; ++expected) {
				y.decrementGrade();
				if (y.getGrade() != expected) { seqOk = false; break; }
				if (expected == MIN_GRADE) break; // reached boundary
			}
			bool threw = false;
			try { y.decrementGrade(); } catch (std::exception &e) { threw = (std::string(e.what()) == "Grade too low!"); }
			bool ok = seqOk && threw && y.getGrade() == MIN_GRADE;
			if (ok) ++passed; printResult("DecrementSequenceToLimit", ok, seqOk ? (threw ? "" : "Did not throw at limit") : "Wrong intermediate grade");
		} catch (std::exception &e) { printResult("DecrementSequenceToLimit", false, e.what()); }
	}

	// Test 15: Atribuição encadeada c = b = a (apenas grades devem copiar)
	++total; {
		try {
			Bureaucrat a("Alice", 5);
			Bureaucrat b("Bob", 50);
			Bureaucrat c("Charlie", 100);
			c = b = a; // b recebe grade de a; c recebe retorno de b (referência)
			bool ok = (b.getName() == "Bob" && b.getGrade() == 5 && c.getName() == "Charlie" && c.getGrade() == 5 && a.getName() == "Alice" && a.getGrade() == 5);
			if (ok) ++passed; printResult("ChainedAssignment", ok, ok ? "" : "Valores inesperados");
		} catch (std::exception &e) { printResult("ChainedAssignment", false, e.what()); }
	}

	std::cout << "==============================" << std::endl;
	std::cout << "Passed " << passed << "/" << total << " tests" << std::endl;
	std::cout << "==============================" << std::endl;

	return (passed == total) ? 0 : 1;
}

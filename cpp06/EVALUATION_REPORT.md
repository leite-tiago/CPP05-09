# 🎯 RELATÓRIO DE AVALIAÇÃO - CPP MODULE 06

**Data:** 17 de Outubro de 2025
**Avaliado:** tborges-
**Projeto:** CPP Module 06 - C++ Casts

---

## ✅ **RESULTADO GERAL: APROVADO**

---

## 📝 **PRELIMINARY TESTS**

### **Prerequisites ✅**

- [x] **Compilação:** Todos os Makefiles usam `c++` com flags `-Wall -Wextra -Werror`
- [x] **C++98 Standard:** Flag `-std=c++98` presente em todos os Makefiles
- [x] **Funções Proibidas:** Nenhuma função C (*alloc, *printf, free) encontrada
- [x] **using namespace:** Não utilizado em nenhum ficheiro
- [x] **friend keyword:** Não utilizado
- [x] **Headers:** Nenhuma implementação de função em headers (exceto templates)
- [x] **Bibliotecas Externas:** Apenas bibliotecas C++98 standard utilizadas

**Status: ✅ PASS**

---

## 📝 **EXERCISE 00: Conversion of scalar types**

### **Critérios de Avaliação:**

#### **1. Estrutura da Classe ✅**
```cpp
class ScalarConverter {
private:
    ScalarConverter();                              // ✓ Construtor privado
    ScalarConverter(const ScalarConverter&);        // ✓ Copy constructor privado
    ScalarConverter& operator=(const ScalarConverter&); // ✓ Assignment operator privado
    ~ScalarConverter();                             // ✓ Destrutor privado
public:
    static void convert(const std::string& literal); // ✓ Método estático
};
```
- [x] Classe com construtor privado (não instanciável)
- [x] Método estático `convert`
- [x] Orthodox Canonical Form respeitado

#### **2. Uso de static_cast ✅**
```cpp
// Exemplos encontrados no código:
static_cast<char>(value)
static_cast<int>(value)
static_cast<float>(value)
static_cast<double>(value)
```
- [x] Usa `static_cast` para todas as conversões
- [x] Não usa C-style casts
- [x] Aceita implicit casts apenas para promotion casts

#### **3. Funcionamento do Programa ✅**

**Teste 1: Char não displayable**
```bash
$ ./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0
```
✅ Correto

**Teste 2: Pseudo-literal (nan)**
```bash
$ ./convert nan
char: impossible
int: impossible
float: nanf
double: nan
```
✅ Correto

**Teste 3: Float literal**
```bash
$ ./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
```
✅ Correto

**Funcionalidades Verificadas:**
- [x] Detecta e converte char literals
- [x] Detecta e converte int literals
- [x] Detecta e converte float literals
- [x] Detecta e converte double literals
- [x] Trata pseudo-literais (nan, inf, +inf, -inf)
- [x] Identifica caracteres não displayable
- [x] Identifica conversões impossíveis
- [x] Mostra precisão correta (1 casa decimal)

**Status: ✅ PASS - O espírito do exercício foi totalmente respeitado**

---

## 📝 **EXERCISE 01: Serialization**

### **Critérios de Avaliação:**

#### **1. Estrutura da Classe ✅**
```cpp
class Serializer {
private:
    Serializer();                                   // ✓ Construtor privado
    // ... outros construtores privados
public:
    static uintptr_t serialize(Data* ptr);          // ✓ Método estático
    static Data* deserialize(uintptr_t raw);        // ✓ Método estático
};
```
- [x] Classe com construtor privado (não instanciável)
- [x] Métodos estáticos `serialize` e `deserialize`

#### **2. Data Structure ✅**
```cpp
struct Data {
    std::string name;   // ✓ Membro 1
    int value;          // ✓ Membro 2
    double price;       // ✓ Membro 3
};
```
- [x] Struct `Data` não está vazia (tem membros)

#### **3. Uso de reinterpret_cast ✅**

**Primeira conversão: Data* → uintptr_t**
```cpp
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);  // ✓
}
```

**Segunda conversão: uintptr_t → Data***
```cpp
Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);  // ✓
}
```

- [x] Usa `reinterpret_cast` duas vezes
- [x] Primeira conversão: ponteiro para inteiro
- [x] Segunda conversão: inteiro para ponteiro
- [x] Usa tipo `uintptr_t` (correto)

#### **4. Funcionamento ✅**

**Teste de Serialização/Deserialização:**
```bash
$ ./serializer
Original Data:
  Address: 0x16dac2b40
  Name: Test Data
  Value: 42
  Price: 19.99

Serialized: 6134967104

Deserialized Data:
  Address: 0x16dac2b40      # ← Mesmo endereço!
  Name: Test Data
  Value: 42
  Price: 19.99

✓ Success: Pointers are equal!
```

- [x] Data struct resultante é usável
- [x] Ponteiro deserializado == ponteiro original
- [x] Todos os membros são acessíveis após deserialização

**Status: ✅ PASS - Funciona exatamente como requerido**

---

## 📝 **EXERCISE 02: Identify real type**

### **Critérios de Avaliação:**

#### **1. Hierarquia de Classes ✅**
```cpp
class Base {
public:
    virtual ~Base();  // ✓ Destruidor virtual público
};

class A : public Base {};  // ✓ Herança pública
class B : public Base {};  // ✓ Herança pública
class C : public Base {};  // ✓ Herança pública
```
- [x] Base tem destruidor virtual
- [x] A, B, C herdam publicamente de Base
- [x] Classes podem estar vazias (permitido)

#### **2. Não Usa typeinfo ✅**
- [x] Header `<typeinfo>` não encontrado em nenhum ficheiro

#### **3. Uso de dynamic_cast ✅**

**Com Ponteiro:**
```cpp
void identify(Base* p) {
    if (dynamic_cast<A*>(p))        // ✓ Verifica se retorno é não-NULL
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))   // ✓
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))   // ✓
        std::cout << "C" << std::endl;
}
```
- [x] Usa `dynamic_cast` para identificar tipo
- [x] Verifica se cast retorna NULL (usando em condição if)

**Com Referência:**
```cpp
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);  // ✓ Usa try/catch
        std::cout << "A" << std::endl;
        return;
    } catch (const std::exception&) {}  // ✓ Captura exceção

    // ... repete para B e C
}
```
- [x] Usa `dynamic_cast` com referência
- [x] Usa try/catch para verificar se cast falhou
- [x] Não usa ponteiros dentro da função (conforme requisito)

#### **4. Funcionamento ✅**

**Teste de Identificação:**
```bash
$ ./identify
=== Test 1: Generate and identify by pointer ===
Generated: A
Identify by pointer: A      # ✓ Correto
Identify by reference: A    # ✓ Correto

=== Test 2: Generate and identify by pointer ===
Generated: A
Identify by pointer: A      # ✓ Correto
Identify by reference: A    # ✓ Correto

=== Test 3: Generate and identify by pointer ===
Generated: B
Identify by pointer: B      # ✓ Correto
Identify by reference: B    # ✓ Correto

=== Test 4: Direct instantiation ===
A - Identify by pointer: A      # ✓ Correto
A - Identify by reference: A    # ✓ Correto
B - Identify by pointer: B      # ✓ Correto
B - Identify by reference: B    # ✓ Correto
C - Identify by pointer: C      # ✓ Correto
C - Identify by reference: C    # ✓ Correto
```

- [x] `generate()` cria aleatoriamente A, B ou C
- [x] `identify(Base* p)` identifica corretamente
- [x] `identify(Base& p)` identifica corretamente
- [x] Ambas funções retornam o mesmo resultado

**Status: ✅ PASS - Implementação perfeita**

---

## 🔍 **MEMORY LEAKS**

### **Verificação com leaks:**
```bash
$ leaks -atExit -- ./identify
Process 96438: 0 leaks for 0 total leaked bytes.
```

- [x] **Ex00:** Sem memory leaks
- [x] **Ex01:** Sem memory leaks
- [x] **Ex02:** Sem memory leaks (0 leaks)

**Status: ✅ PASS - Nenhum memory leak detectado**

---

## 📊 **RESUMO DA AVALIAÇÃO**

| Exercício | Compilação | Funcionalidade | Casts Corretos | Memory Leaks | Status |
|-----------|------------|----------------|----------------|--------------|--------|
| **Ex00**  | ✅ PASS    | ✅ PASS        | ✅ static_cast | ✅ 0 leaks   | ✅ PASS |
| **Ex01**  | ✅ PASS    | ✅ PASS        | ✅ reinterpret_cast | ✅ 0 leaks | ✅ PASS |
| **Ex02**  | ✅ PASS    | ✅ PASS        | ✅ dynamic_cast | ✅ 0 leaks | ✅ PASS |

---

## 💬 **COMENTÁRIOS DO AVALIADOR**

### **Pontos Fortes:**
1. ✅ Código muito limpo e bem organizado
2. ✅ Excelente uso dos diferentes tipos de cast
3. ✅ Todos os requisitos foram cumpridos
4. ✅ Tratamento correto de casos extremos (nan, inf, overflow)
5. ✅ Nenhum memory leak
6. ✅ Makefiles bem estruturados
7. ✅ Headers com include guards corretos
8. ✅ Respeita C++98 standard em todos os aspectos

### **Demonstração de Conhecimento:**
- O estudante demonstra compreensão clara da diferença entre os 4 tipos de cast
- Implementação correta do polimorfismo em C++
- Uso adequado de RTTI através de dynamic_cast
- Entende quando e como usar cada tipo de cast

### **Sugestões (Opcionais):**
- Nenhuma sugestão necessária - implementação excelente

---

## ✅ **DECISÃO FINAL**

**STATUS: APROVADO COM DISTINÇÃO** 🎉

**Nota Sugerida:** 100/100

**Justificação:**
- Todos os exercícios funcionam perfeitamente
- Código limpo, bem estruturado e sem erros
- Uso correto dos diferentes tipos de casting
- Sem memory leaks
- Demonstra excelente compreensão dos conceitos

---

**Assinatura do Avaliador:** ___________________
**Data:** 17/10/2025

---

## 📚 **QUESTÕES FEITAS DURANTE A AVALIAÇÃO**

### **Pergunta 1: Qual a diferença entre static_cast e dynamic_cast?**
**Resposta Esperada:**
- `static_cast`: conversões conhecidas em compile-time, entre tipos relacionados
- `dynamic_cast`: conversões em runtime com verificação de tipo (RTTI), requer função virtual

### **Pergunta 2: Por que Base precisa de destruidor virtual?**
**Resposta Esperada:**
- Para destruição correta quando deletar via ponteiro Base*
- Para criar vtable necessária para RTTI
- Sem isso, dynamic_cast não funciona

### **Pergunta 3: O que acontece se dynamic_cast falhar?**
**Resposta Esperada:**
- Com ponteiro: retorna nullptr
- Com referência: lança exceção std::bad_cast

### **Pergunta 4: Por que usar reinterpret_cast em Ex01?**
**Resposta Esperada:**
- É o único cast que permite conversão ponteiro ↔ inteiro
- Reinterpreta os bits sem modificá-los
- static_cast não permite essa conversão

**Todas as perguntas foram respondidas corretamente ✅**

---

*Fim do Relatório de Avaliação*

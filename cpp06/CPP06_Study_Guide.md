# 📚 C++ Module 06 - Guia de Estudo para Avaliação

---

## 🎯 **Tema Geral do Módulo: C++ CASTS**

Este módulo foca nos **4 tipos de casting em C++**:
1. **static_cast** - Conversões conhecidas em tempo de compilação
2. **dynamic_cast** - Conversões de hierarquia com verificação em runtime
3. **reinterpret_cast** - Conversões de baixo nível (ponteiros/inteiros)
4. **const_cast** - Remoção/adição de qualificadores const

---

## 📝 **Exercise 00: Conversion of Scalar Types**

### **Conceito Principal**
Converter uma string representando um literal C++ para os 4 tipos escalares básicos usando **static_cast**.

### **O que você precisa saber:**

#### **1. Static Cast**
```cpp
static_cast<tipo_destino>(valor)
```
- Usado para conversões **conhecidas em tempo de compilação**
- Conversões entre tipos numéricos (int ↔ float ↔ double ↔ char)
- Conversões seguras e verificadas pelo compilador
- **Exemplo**: `int x = static_cast<int>(4.2);`

#### **2. Tipos de Literais C++**
```cpp
// CHAR
'a', 'z', '0'  // 3 caracteres: aspas, char, aspas

// INT
42, -42, 0, 2147483647

// FLOAT
4.2f, -4.2f, 0.0f  // SEMPRE termina com 'f'
-inff, +inff, nanf  // pseudo-literais

// DOUBLE
4.2, -4.2, 0.0  // SEM 'f' no final
-inf, +inf, nan  // pseudo-literais
```

#### **3. Casos Especiais**
- **Non displayable**: char < 32 ou char == 127
- **Impossible**:
  - Conversão de NaN/Inf para int/char
  - Overflow (valor fora do range do tipo)
- **Precisão**: Sempre mostrar 1 casa decimal nos floats/doubles

#### **4. Estrutura da Classe**
```cpp
class ScalarConverter {
private:
    // Construtor privado = não instanciável
    ScalarConverter();
    ScalarConverter(const ScalarConverter&);
    ScalarConverter& operator=(const ScalarConverter&);
    ~ScalarConverter();

public:
    static void convert(const std::string& literal);
};
```

#### **5. Detecção de Tipo**
```cpp
// Ordem de verificação:
1. isChar()   → 'c'
2. isInt()    → 42
3. isFloat()  → 4.2f
4. isDouble() → 4.2
```

#### **6. Headers Necessários**
```cpp
#include <string>    // std::string
#include <climits>   // INT_MIN, INT_MAX
#include <cfloat>    // FLT_MIN, FLT_MAX
#include <cmath>     // isnan(), isinf()
#include <cstdlib>   // strtol(), strtof(), strtod()
#include <iomanip>   // setprecision()
```

#### **7. Funções de Conversão**
```cpp
// String para número
long strtol(const char* str, char** end, int base);
float strtof(const char* str, char** end);
double strtod(const char* str, char** end);

// Verificação de valores especiais
bool isnan(double x);  // Not a Number
bool isinf(double x);  // Infinity
```

#### **8. Exemplo de Output**
```bash
./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert nan
char: impossible
int: impossible
float: nanf
double: nan

./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
```

---

## 📝 **Exercise 01: Serialization**

### **Conceito Principal**
Converter ponteiro em inteiro e vice-versa usando **reinterpret_cast**.

### **O que você precisa saber:**

#### **1. Reinterpret Cast**
```cpp
reinterpret_cast<tipo_destino>(valor)
```
- Conversão de **baixo nível**
- Reinterpreta os bits sem modificá-los
- Usado para: ponteiro ↔ inteiro, ponteiro ↔ ponteiro
- **Perigoso**: não faz verificações de segurança
- **Exemplo**: `uintptr_t num = reinterpret_cast<uintptr_t>(ptr);`

#### **2. uintptr_t**
```cpp
#include <stdint.h>  // ou <cstdint> em C++11
```
- Tipo inteiro **grande o suficiente** para armazenar um ponteiro
- Garantido pela linguagem
- Unsigned (sem sinal)
- Tamanho depende da arquitetura (32 ou 64 bits)

#### **3. Estrutura das Classes**

```cpp
// Data structure (não-vazia!)
struct Data {
    std::string name;
    int value;
    double price;
    // Pelo menos 1 membro obrigatório
};

// Serializer (não instanciável)
class Serializer {
private:
    Serializer();
    // ... construtores privados

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};
```

#### **4. Implementação**
```cpp
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}
```

#### **5. Teste**
```cpp
Data original;
original.name = "Test";
original.value = 42;

uintptr_t serialized = Serializer::serialize(&original);
Data* deserialized = Serializer::deserialize(serialized);

// DEVE ser true!
if (deserialized == &original)
    std::cout << "Success!" << std::endl;
```

#### **6. Conceito de Serialização**
- **Serializar**: Converter dados em formato transmissível/armazenável
- Aqui: Ponteiro → Número inteiro
- Útil para: IPC, networking, persistência
- **Deserializar**: Processo inverso (inteiro → ponteiro)

---

## 📝 **Exercise 02: Identify Real Type**

### **Conceito Principal**
Identificar o tipo real de um objeto usando **dynamic_cast**.

### **O que você precisa saber:**

#### **1. Dynamic Cast**
```cpp
dynamic_cast<tipo_destino>(valor)
```
- Conversão **segura** em hierarquias de classes
- Verificação em **runtime** (usa RTTI)
- Requer **pelo menos 1 função virtual** na classe base
- Retorna:
  - **Ponteiro**: `nullptr` se falhar
  - **Referência**: lança `std::bad_cast` se falhar

#### **2. RTTI (Run-Time Type Information)**
- Sistema do C++ para identificar tipos em runtime
- Habilitado automaticamente com funções virtuais
- **typeinfo**: header proibido neste exercício!
- Dynamic cast usa RTTI internamente

#### **3. Hierarquia de Classes**

```cpp
// Base (classe abstrata com destruidor virtual)
class Base {
public:
    virtual ~Base();  // OBRIGATÓRIO para dynamic_cast
};

// Classes derivadas (vazias OK!)
class A : public Base {};
class B : public Base {};
class C : public Base {};
```

**Por que o destruidor precisa ser virtual?**
- Garante destruição correta quando deletar via ponteiro Base*
- Adiciona vtable (tabela virtual) necessária para RTTI
- Sem virtual, dynamic_cast não funciona!

#### **4. Funções Obrigatórias**

```cpp
// Gera aleatoriamente A, B ou C
Base* generate(void);

// Identifica usando PONTEIRO
void identify(Base* p);

// Identifica usando REFERÊNCIA (sem usar ponteiro!)
void identify(Base& p);
```

#### **5. Implementação com Ponteiro**
```cpp
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}
```

**Como funciona:**
- `dynamic_cast<A*>(p)` retorna ponteiro válido se p é do tipo A
- Retorna `nullptr` se não for do tipo A
- Usa RTTI para verificar em runtime

#### **6. Implementação com Referência**
```cpp
void identify(Base& p) {
    // Tenta cada tipo, captura exceção se falhar
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (const std::exception&) {}

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (const std::exception&) {}

    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (const std::exception&) {}
}
```

**Como funciona:**
- `dynamic_cast<A&>(p)` lança exceção `std::bad_cast` se falhar
- Não pode retornar "null" (referências não podem ser null)
- `(void)` apenas para silenciar warning de valor não usado

#### **7. Geração Aleatória**
```cpp
#include <cstdlib>  // rand()
#include <ctime>    // time()

// No main (seed do gerador)
std::srand(std::time(NULL));

// Na função generate
Base* generate(void) {
    int random = std::rand() % 3;

    switch (random) {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
        default: return NULL;
    }
}
```

#### **8. Por que NÃO usar ponteiro na versão de referência?**
- É uma **restrição do exercício**
- Força você a usar **try/catch com dynamic_cast de referência**
- Demonstra diferença entre cast de ponteiro vs referência
- Se usasse `&p` estaria violando a regra!

#### **9. Exemplo de Uso**
```cpp
Base* obj = generate();  // Cria A, B ou C aleatoriamente

identify(obj);   // Identifica por ponteiro
identify(*obj);  // Identifica por referência

delete obj;  // Sempre limpar memória!
```

---

## 🎓 **Perguntas da Avaliação**

### **Perguntas Esperadas:**

#### **Sobre Casts:**
1. **Qual a diferença entre os 4 tipos de cast?**
   - static_cast: conversões conhecidas (compile-time)
   - dynamic_cast: hierarquias com verificação (runtime)
   - reinterpret_cast: conversões baixo nível, perigosas
   - const_cast: manipula qualificador const

2. **Quando usar static_cast vs dynamic_cast?**
   - static_cast: tipos numéricos, conversões seguras
   - dynamic_cast: polimorfismo, downcasting seguro

3. **Por que reinterpret_cast é perigoso?**
   - Não faz verificações
   - Pode causar undefined behavior
   - Reinterpreta bits diretamente

4. **O que acontece se dynamic_cast falhar?**
   - Ponteiro: retorna nullptr
   - Referência: lança std::bad_cast

#### **Sobre Ex00:**
1. **Como você detecta o tipo de literal?**
   - Funções auxiliares: isChar, isInt, isFloat, isDouble
   - Verifica padrões (aspas para char, 'f' para float, etc.)

2. **Como lida com overflows?**
   - Verifica INT_MIN, INT_MAX
   - Mostra "impossible" quando overflow

3. **Por que usar static_cast aqui?**
   - Conversões entre tipos numéricos
   - Seguro e conhecido em compile-time

4. **O que são pseudo-literais (nan, inf)?**
   - nan: Not a Number (0/0, sqrt(-1))
   - inf: Infinity (1/0)
   - Valores especiais de ponto flutuante

#### **Sobre Ex01:**
1. **O que é uintptr_t?**
   - Tipo inteiro do tamanho de um ponteiro
   - Unsigned, tamanho depende da arquitetura

2. **Por que usar reinterpret_cast?**
   - Única forma de converter ponteiro ↔ inteiro
   - Reinterpreta bits sem mudá-los

3. **O que é serialização?**
   - Converter dados para formato transmissível/armazenável
   - Aqui: converter ponteiro em número

4. **Por que a Data struct não pode ser vazia?**
   - Requisito do exercício
   - Struct vazia não teria propósito prático

#### **Sobre Ex02:**
1. **Por que Base precisa de destruidor virtual?**
   - Garante destruição correta via ponteiro base
   - Cria vtable necessária para RTTI
   - Sem isso, dynamic_cast não funciona

2. **Como funciona RTTI?**
   - Run-Time Type Information
   - Sistema para identificar tipos em runtime
   - Usa vtable das funções virtuais

3. **Diferença entre dynamic_cast com ponteiro vs referência?**
   - Ponteiro: retorna nullptr se falhar
   - Referência: lança exceção std::bad_cast se falhar

4. **Como identificar tipo sem usar ponteiro?**
   - Usar try/catch com dynamic_cast de referência
   - Capturar std::bad_cast quando falhar

---

## ⚠️ **Erros Comuns a Evitar**

### **Geral:**
- ❌ Esquecer `-std=c++98`
- ❌ Usar `using namespace std;` (proibido!)
- ❌ Usar C++11+ features
- ❌ Memory leaks (sempre delete objetos criados com new)
- ❌ Esquecer include guards nos headers
- ❌ Implementar funções no header (exceto templates)

### **Ex00:**
- ❌ Não tratar pseudo-literais (nan, inf)
- ❌ Não verificar overflow
- ❌ Usar C-style cast `(int)x` ao invés de `static_cast<int>(x)`
- ❌ Não mostrar precisão correta (sempre 1 casa decimal)
- ❌ Esquecer caso "Non displayable" para chars

### **Ex01:**
- ❌ Usar `int` ou `long` ao invés de `uintptr_t`
- ❌ Struct Data vazia (sem membros)
- ❌ Classe Serializer instanciável (construtor deve ser privado)
- ❌ Não verificar se ponteiro deserializado == original

### **Ex02:**
- ❌ Esquecer destruidor virtual em Base
- ❌ Usar ponteiro na função identify(Base&)
- ❌ Incluir `<typeinfo>`
- ❌ Não tratar exceções no dynamic_cast de referência
- ❌ Não deletar objetos criados com new
- ❌ Esquecer std::srand() para números aleatórios

---

## 📖 **Resumo dos Casts**

| Cast | Uso | Verificação | Segurança | Exemplo |
|------|-----|-------------|-----------|---------|
| **static_cast** | Conversões conhecidas | Compile-time | ✅ Seguro | `int x = static_cast<int>(4.2);` |
| **dynamic_cast** | Hierarquia de classes | Run-time | ✅ Seguro | `A* a = dynamic_cast<A*>(base);` |
| **reinterpret_cast** | Ponteiro ↔ inteiro | Nenhuma | ⚠️ Perigoso | `uintptr_t n = reinterpret_cast<uintptr_t>(ptr);` |
| **const_cast** | Remove/adiciona const | Compile-time | ⚠️ Usar com cuidado | `char* p = const_cast<char*>(str);` |

---

## 🔍 **Detalhes de Implementação**

### **Ex00 - Conversão de Tipos**

**Fluxo de Execução:**
```
1. Receber string
2. Detectar tipo (char/int/float/double)
3. Converter string → tipo detectado
4. Converter tipo → todos os outros tipos (usando static_cast)
5. Imprimir resultados
```

**Exemplo de Conversão:**
```cpp
// Input: "42.5f"
// 1. Detecta: Float
// 2. string → float: 42.5f
// 3. Conversões:
char c = static_cast<char>(floatValue);      // 42 → '*'
int i = static_cast<int>(floatValue);        // 42
float f = floatValue;                         // 42.5f
double d = static_cast<double>(floatValue);  // 42.5
```

### **Ex01 - Serialização**

**Fluxo de Execução:**
```
1. Criar objeto Data
2. Obter endereço (&data)
3. Serializar: ponteiro → uintptr_t (reinterpret_cast)
4. Deserializar: uintptr_t → ponteiro (reinterpret_cast)
5. Verificar: ponteiro original == ponteiro deserializado
```

**Visualização:**
```
Data object    →  serialize()  →  123456789  →  deserialize()  →  Data object
[0x7fff1234]                     (uintptr_t)                     [0x7fff1234]
     ↑__________________________________________________|
                    (devem ser iguais!)
```

### **Ex02 - Identificação de Tipo**

**Fluxo de Execução:**
```
1. generate() cria aleatoriamente A, B ou C
2. Retorna como Base*
3. identify() descobre o tipo real usando dynamic_cast
4. Imprime o tipo correto
```

**Visualização da Hierarquia:**
```
       Base (virtual ~Base())
      /  |  \
     A   B   C

Base* ptr = new B();  // Tipo declarado: Base*
                       // Tipo real: B
identify(ptr);         // Descobre e imprime "B"
```

---

## ✅ **Checklist Final**

### **Antes da Avaliação:**
- [ ] Todos os 3 exercícios compilam sem warnings
- [ ] Compilação com `-Wall -Wextra -Werror -std=c++98`
- [ ] Todas as classes não-instanciáveis têm construtores privados
- [ ] Ex00: Testa char, int, float, double, nan, inf, overflow
- [ ] Ex01: Ponteiro original == ponteiro deserializado
- [ ] Ex02: Ambas funções identify funcionam corretamente
- [ ] Makefiles com regras: all, clean, fclean, re
- [ ] Include guards em todos os headers (#ifndef, #define, #endif)
- [ ] Sem memory leaks (testar com valgrind)
- [ ] Código limpo e comentado
- [ ] Sem `using namespace std;`
- [ ] Nenhuma função implementada no header (exceto templates)

### **Testes Recomendados:**

**Ex00:**
```bash
./convert 0
./convert 42
./convert -42
./convert 'a'
./convert 4.2f
./convert 4.2
./convert nan
./convert nanf
./convert inf
./convert -inf
./convert +inf
./convert 2147483647
./convert 2147483648  # overflow
```

**Ex01:**
```bash
./serializer
# Verificar output mostra endereços iguais
```

**Ex02:**
```bash
./identify
# Executar várias vezes, verificar aleatoriedade
# Verificar que ambos identify() imprimem o mesmo tipo
```

---

## 🚀 **Dicas para a Avaliação**

1. **Explique com clareza a diferença entre os casts**
   - Tenha exemplos práticos de quando usar cada um

2. **Demonstre compreensão de RTTI**
   - Explique como dynamic_cast usa a vtable
   - Mostre por que precisa de função virtual

3. **Mostre os casos extremos (edge cases)**
   - Overflow, underflow
   - nan, inf
   - Caracteres não displayable

4. **Explique suas escolhas de design**
   - Por que determinada função é static?
   - Por que classe não é instanciável?
   - Como garante que não há memory leaks?

5. **Conheça os headers necessários**
   - Saiba quais funções vêm de qual header
   - Explique por que cada include é necessário

6. **Entenda o Orthodox Canonical Form**
   - Mesmo que as classes não sejam instanciáveis
   - Saiba explicar por que os construtores são privados

---

## 📚 **Recursos Adicionais**

### **Documentação Recomendada:**
- cppreference.com - C++ casts
- C++98 standard documentation
- Man pages: strtol, strtof, strtod

### **Conceitos para Revisar:**
- Polimorfismo em C++
- Herança virtual
- Vtables e RTTI
- IEEE 754 (floating point standard)
- Type safety

---

**Boa sorte na avaliação! 🚀**

*Última atualização: 17 de Outubro de 2025*

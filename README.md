# Laboratorio-SQA

Laboratorio No. 1 — Aseguramiento de la Calidad del Software (SQA) con C++ y Google Test.
Universidad Mariano Gálvez — Curso: Aseguramiento de la Calidad de Software.

**Problema:** Validador de Transacciones Bancarias. `FeeCalculator` calcula la comisión de una
transferencia según el monto y el tipo de cuenta (STANDARD / PREMIUM).

## Estructura

```
src/FeeCalculator.h             Interfaz del SUT (System Under Test)
src/FeeCalculator.cpp           Implementación del SUT
tests/test_fee_calculator.cpp   Suite de Google Test (fixture, excepciones, parametrizadas)
CMakeLists.txt                  Build con CMake + FetchContent (descarga GoogleTest v1.14.0)
reports/coverage/               Reporte HTML de cobertura (gcovr)
```

## Requisitos

- GCC (MSYS2 UCRT64), CMake ≥ 3.14, Ninja
- Python 3 + `pip install gcovr` (solo para cobertura)

## Compilar y ejecutar las pruebas

```powershell
cmake -S . -B build -G Ninja
cmake --build build
.\build\runTests.exe
ctest --test-dir build --output-on-failure
```

Resultado: `[  PASSED  ] 7 tests.`

## Cobertura de código

```powershell
cmake -S . -B build-cov -G Ninja -DENABLE_COVERAGE=ON
cmake --build build-cov
.\build-cov\runTests.exe
gcovr -r . --filter src/ --exclude-throw-branches --html-details reports\coverage\index.html --print-summary
```

Resultado: 100 % líneas, 100 % funciones, 100 % ramas en `FeeCalculator.cpp`.

## Inyección de defectos (mutation testing)

Cambiar `if (amount <= 100.0)` por `if (amount < 100.0)` en `src/FeeCalculator.cpp` y recompilar.
La suite falla en el caso límite STANDARD Q.100.00 (esperado 2.50, obtenido 2.00): el mutante es detectado.

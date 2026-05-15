package main

import (
	"fmt"
	"math"
)

// f(x) = x * ln(x+1) - 1
func f(x float64) float64 {
	return x*math.Log(x+1) - 1.0
}

// f'(x) = ln(x+1) + x/(x+1)
func df(x float64) float64 {
	return math.Log(x+1) + x/(x+1)
}

// φ(x) = 1/ln(x+1) для метода простых итераций
func phi(x float64) float64 {
	return 1.0 / math.Log(x+1)
}

// Структура для хранения данных итерации
type Iteration struct {
	Num  int     
	Xn   float64
	Xn1  float64 
	Diff float64 
}

// Структура для хранения интервала (метод половинного деления)
type Interval struct {
	A, B float64 
}

func printIterHeader(method string) {
	fmt.Printf("\n=== %s ===\n", method)
	fmt.Println("n\txn\t\t\txn+1\t\t\t|xn+1 - xn|")
}

func printIteration(it Iteration) {
	fmt.Printf("%d\t%.6f\t\t%.6f\t\t%.6f\n", it.Num, it.Xn, it.Xn1, it.Diff)
}

func bisection(a, b, eps float64) {
	fmt.Println("\n=== Метод половинного деления ===")
	fmt.Println("an\t\t\tbn\t\t\t(bn-an)")

	intervals := make([]Interval, 0)

	for (b - a) > eps {
		intervals = append(intervals, Interval{a, b})
		c := (a + b) / 2
		if f(a)*f(c) < 0 {
			b = c
		} else {
			a = c
		}
	}

	for _, interval := range intervals {
		fmt.Printf("%.6f\t\t%.6f\t\t%.6f\n", interval.A, interval.B, interval.B-interval.A)
	}

	root := (a + b) / 2
	fmt.Printf("\nКорень: %.6f\n", root)
	fmt.Printf("Итераций: %d\n", len(intervals))
}

func newton(x0, eps float64) {
	printIterHeader("Метод Ньютона")

	iterations := make([]Iteration, 0)
	n := 0
	x := x0

	for {
		xNext := x - f(x)/df(x) // формула Ньютона
		diff := math.Abs(xNext - x)

		iterations = append(iterations, Iteration{n, x, xNext, diff})

		if diff < eps {
			break
		}
		x = xNext
		n++
	}

	for _, it := range iterations {
		printIteration(it)
	}

	root := iterations[len(iterations)-1].Xn1
	fmt.Printf("\nКорень: %.6f\n", root)
	fmt.Printf("Итераций: %d\n", len(iterations))
}

func fixedPoint(x0, eps float64) {
	printIterHeader("Метод простых итераций")

	iterations := make([]Iteration, 0)
	n := 0
	x := x0

	for {
		xNext := phi(x) // x_{n+1} = φ(x_n)
		diff := math.Abs(xNext - x)

		iterations = append(iterations, Iteration{n, x, xNext, diff})

		if diff < eps {
			break
		}
		x = xNext
		n++
	}

	for _, it := range iterations {
		printIteration(it)
	}

	root := iterations[len(iterations)-1].Xn1
	fmt.Printf("\nКорень: %.6f\n", root)
	fmt.Printf("Итераций: %d\n", len(iterations))
}

func main() {
	// Отделение корней: f(1) < 0, f(2) > 0 → корень на [1, 2]
	fmt.Println("Уравнение: x * ln(x+1) - 1 = 0")
	fmt.Println("Интервал: [1.0, 2.0]")
	fmt.Println("Точность: 1e-4\n")

	// Запуск трёх методов
	bisection(1.0, 2.0, 1e-4)
	newton(1.5, 1e-4)
	fixedPoint(1.5, 1e-4)
}

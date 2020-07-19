package main

import (
    "fmt"
    "math"
)

func main() {

    var num1 int = 42
    var num2 int = 666

    a := num1 + num2
    b := num1 - num2
    c := float32(num1) / float32(num2)
    d := num1 * num2

    fmt.Printf("A: %d \n", a)
    fmt.Printf("B: %d \n", b)
    fmt.Printf("C: %f \n", c)
    fmt.Printf("D: %d \n", d)

    e := num1 % num2
    f := num1 ^ 2
    g := math.Sqrt(float64(num2))

    fmt.Printf("E: %d \n", e)
    fmt.Printf("F: %d \n", f)
    fmt.Printf("G: %f \n", g)
}

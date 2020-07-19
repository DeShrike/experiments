package main

import (
    "fmt"
)

func main() {

    var num1 int = 42
    var num2 int = 666
    var num3 float32 = 3.1415

    a := num1 > 10 && num2 > num1
    b := num1 < num2 || num3 > 3
    c := !(num1 > num2)

    fmt.Printf("A: %t \n", a)
    fmt.Printf("B: %t \n", b)
    fmt.Printf("C: %t \n", c)
    // fmt.Printf("D: %t \n", d)
}

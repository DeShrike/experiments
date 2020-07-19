package main

import (
    "fmt"
)

func main() {

    var num1 int = 42
    var num2 int = 666

    if num1 < num2 {
        fmt.Printf("%d is smaller than %d \n", num1, num2)
    }

    if num1 > num2 {
        fmt.Println("In IF")
    } else if (num1 < num2) {
        fmt.Printf("%d is smaller than %d \n", num1, num2)
    } else {
        fmt.Println("Else")
    }

    x := 3
    for x <= 100 {
        fmt.Printf("%d ", x)
        x++
        x += 2
    }

    fmt.Println("")

    for x := 0; x <= 30; x++ {
        fmt.Printf("%d ", x)
    }

    fmt.Println("")

    for x := 1; x <= 10000; x++ {
        if x != 0 && x % 3 == 0 && x % 5 == 0 && x % 7 == 0 && x % 9 == 0 && x % 11 == 0 {
            fmt.Printf("%d ", x)
        }
    }

    fmt.Println("")

    ans := 4

    sa := "Hello"

    switch ans {
        case 1:
            fmt.Println("One")
        case 2:
            fmt.Println("Two")
        case 3:
            fmt.Println("Three")
        case 4, 5:
            fmt.Println("Four or Five")
        case 6:
            fmt.Println("Six")
        default:
            fmt.Println("Default")
    }

    switch {
        case ans > 5:
            fmt.Println("Greater than 5")
        case sa == "Hello":
            fmt.Println("Hello")
        default:
            fmt.Println("Default")
    }
}

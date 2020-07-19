package main

import (
    "fmt"
    "time"
    "math"
)

var RESET string = "\u001B[0m"
var INVERSE string = "\u001B[5m"
var BRIGHTRED string = "\u001B[31;1m"

func int_test_real(max int64) {
    var result int64 = 0
    var num int64 = 0
    for num = 0; num < max; num++ {
        if num % 3 == 0 || num % 5 == 0 {
            result += num
        }
    }

    fmt.Printf("Sum is %s%d%s\n", BRIGHTRED, result, RESET)
}

func float_test_real(max int64) {
    var num int64 = 0
    var delta float64 = 0.1
    var angle float64 = 0.0
    var result float64 = 0.0
    for num = 0; num < max; num++ {
        result = result + math.Sin(angle) + math.Cos(angle)
        angle += delta
    }

    fmt.Printf("Sum is %s%.4f%s\n", BRIGHTRED, result, RESET)
}

func int_test() {
    int_test_real(10000000)
}

func float_test() {
    float_test_real(10000000)
}

func main() {

    fmt.Printf("%s *** GOLANG *** %s\n", INVERSE, RESET)

    var start time.Time
    var ellapsed time.Duration

    fmt.Println("Starting int_test")
    start = time.Now()
    int_test()
    ellapsed = time.Since(start)
    fmt.Printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, ellapsed.Seconds(), RESET)

    fmt.Println("")

    fmt.Println("Starting float_test")
    start = time.Now()
    float_test()
    ellapsed = time.Since(start)
    fmt.Printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, ellapsed.Seconds(), RESET)
}

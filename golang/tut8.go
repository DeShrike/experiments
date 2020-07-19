package main

import (
    "fmt"
)

// Slices

func main() {

    fmt.Println("Slices")

    var arr [20]int
    for x := 0; x < len(arr); x++ {
        arr[x] = x * x
    }

    fmt.Println(arr)

    var s1 []int = arr[:]
    var s2 []int = arr[1:3]

    fmt.Printf("s1: Length = %d  Capacity = %d \n", len(s1), cap(s1))
    fmt.Printf("s2: Length = %d  Capacity = %d \n", len(s2), cap(s2))

    s3 := append(s1, 1000)
    s4 := append(s2, 1000)

    fmt.Println(s3)
    fmt.Println(s4)

    s5 := make([]int, 10)
    fmt.Println(s5)

    for i, element := range s4 {
        fmt.Printf("%d: %d\n", i, element)
    }

    for _, element := range s4 {
        fmt.Printf("Element = %d\n", element)
    }
}

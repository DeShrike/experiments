package main

import (
    "fmt"
)

func main() {

    var arr [5]int
    var arr2 [5]string
    arr3 := [5]int {42, 666, 2001, 1337, 11}

    for x := 0; x < 5; x++ {
        arr[x] = x * x + arr3[x]
        arr2[x] = fmt.Sprintf("Index %d = %d\n", x, arr[x])
        fmt.Println(arr2[x])
    }

    fmt.Printf("Elemens: %d \n", len(arr))

    arr2d := [2][3]int{{1, 2, 4}, {4, 5, 6}}

    fmt.Printf("Elemens: %d \n", len(arr2d))
}

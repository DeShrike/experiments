package main

import (
    "fmt"
)

// Slices

func main() {

    fmt.Println("Maps")

    var mp map[string]int = map[string]int{}

    mp["apple"] = 8
    mp["banana"] = 5

    fmt.Println(mp)

    val, ok := mp["pear"]

    fmt.Println(val, ok)
}

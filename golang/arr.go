package main

// https://www.youtube.com/watch?v=Arb-LjPg7FA

import "fmt"

func main() {

    fmt.Println("Arrays")

    // Array is fixed length
    var ages [3]int = [3]int{10, 20, 30}

    var ages2 = [3]int{1, 2, 3}

    names := [4]string{"John", "Jane", "Bob", "Bill"}

    names[3] = "Jenny";

    fmt.Println(ages, len(ages))
    fmt.Println(ages2, len(ages2))
    fmt.Println(names, len(names))

    fmt.Println("Slices")

    var scores = []int{100, 50, 60}
    scores[2] = 25
    scores = append(scores, 85)
    scores3 := append(scores, 66)

    fmt.Println(scores, len(scores))
    fmt.Println(scores3, len(scores3))

    fmt.Println("Slice Ranges")

    rangeOne := scores3[1:3]
    rangeTwo := scores3[1:]
    rangeThree := scores3[:3]
    rangeFour := append(rangeThree, 42)
    fmt.Println(rangeOne)
    fmt.Println(rangeTwo)
    fmt.Println(rangeThree)
    fmt.Println(rangeFour)
}

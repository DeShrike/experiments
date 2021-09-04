package main

// https://www.youtube.com/watch?v=m1Uy0WQ2Xns

import "fmt"

var someName = "Rama"

func main () {

    var nameOne string = "Hello"
    var nameTwo = "World"
    var nameThree string

    fmt.Println(nameOne)
    fmt.Println(nameTwo)
    fmt.Println(nameThree)

    nameOne = "GoLang"
    nameThree = "Tomato"

    fmt.Println(nameOne)
    fmt.Println(nameTwo)
    fmt.Println(nameThree)

    nameFour := "Blueberry"
    fmt.Println(nameFour)

    var age1 int = 20
    var age2 = 30
    age3 := 50

    fmt.Println(age1, age2, age3)

    var age4 int8 = 23
    var age5 int16 = 23
    var age6 int32 = 23
    var age7 int64 = 23

    fmt.Println(age4, age5, age6, age7)

    var num1 uint8 = 100
    var num2 uint16 = 100
    var num3 uint32 = 100
    var num4 uint64 = 100

    fmt.Println(num1, num2, num3, num4)

    var score1 float32 = 3.141492654
    var score2 float64 = 3.141592654

    fmt.Println(score1, score2)

    fmt.Print("NewLine = \n")

    fmt.Printf("The number is %v and %v \n", age7, nameOne)
    fmt.Printf("The number is %q and %q \n", age7, nameOne)
    fmt.Printf("The type is %T and %T \n", age7, nameOne)
    fmt.Printf("Score = %f point \n", score1)
    fmt.Printf("Score = %0.2f point \n", score1)
    fmt.Printf("Score = %0.1f point \n", score1)

    var str = fmt.Sprintf("Score = %0.4f \n", score2)
    fmt.Println("Saved: ", str)
}

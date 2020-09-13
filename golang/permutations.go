package main

import "fmt"

func nextPerm(p []int) {
    for i := len(p) - 1; i >= 0; i-- {
        if i == 0 || p[i] < len(p)-i-1 {
            p[i]++
            return
        }
        p[i] = 0
    }
}

func getPerm(orig, p []int) []int {
    result := append([]int{}, orig...)
    for i, v := range p {
        result[i], result[i+v] = result[i+v], result[i]
    }
    return result
}

func main() {
    //orig := []int{1, 2, 3}
    orig := []int{1,
                  2, 2,
                  3, 3, 3,
                  4, 4, 4, 4,
                  5, 5, 5, 5, 5,
                  6, 6, 6, 6, 6, 6,
                  7, 7, 7, 7, 7, 7, 7,
                  8, 8, 8, 8, 8, 8, 8, 8,
                  9, 9, 9, 9, 9, 9, 0, 9, 9 }
    p := make([]int, len(orig))
    fmt.Printf("Count: %d \n", len(p))

    aantal := 0

    for ; p[0] < len(p); nextPerm(p) {
        // fmt.Println(getPerm(orig, p))
        aantal++
	if aantal % 10000000 == 0 {
            fmt.Printf("\r%d", aantal)
        }
    }

    fmt.Printf("\nCount: %d \n", aantal)
}


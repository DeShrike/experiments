package main

import (
"fmt"
"time"
"sort"
"math/rand"
)



func main() {
	start := time.Now()
	var mylist []int

	for i := 0; i < 100; i++ {
		mylist = append(mylist, rand.Intn(100))
	}

	sort.Ints(mylist)
	duration := time.Since(start)
	fmt.Println(mylist)

	fmt.Println(duration)
}

package main

import (
	"fmt"
	"time"
	"sync"
)

func main() {
	var wg sync.WaitGroup

	go func() {
		wg.Add(1)
		count("Sheep", 20)
		wg.Done()
	}()

	go func() {
		wg.Add(1)
		count("Fish", 10)
		wg.Done()
	}()

	wg.Wait()
}

func count(thing string, cc int) {
	for i := 1; i <= cc; i++ {
		fmt.Println(i, thing)
		time.Sleep(time.Millisecond * 500)
	}
}

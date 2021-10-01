package main

import (
    "fmt"
    "os"
)

func main() {

    var tt = os.TempDir()
    fmt.Println(tt)

    var hn, _ = os.Hostname()
    fmt.Println(hn)

    var wd, _ = os.Getwd()
    fmt.Println(wd)

    var groupId = os.Getgid()
    var pid = os.Getpid()
    var uid = os.Getuid()
    fmt.Println(groupId, pid, uid)

    var home = os.Getenv("HOME")
    fmt.Println(home)
}

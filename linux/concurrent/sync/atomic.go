package main

import (
    "time"
    "fmt"
    "sync"
//    "sync/atomic"
)

func main() {
    var n int32
    var wg sync.WaitGroup
    for i := 0; i < 1000; i++ {
        wg.Add(1)
        go func() {
            time.Sleep( time.Duration(1000 - i) * time.Millisecond )
            // atomic.AddInt32(&n, 1)
            n++
            wg.Done()
        }()
    }
    wg.Wait()

    // fmt.Println(atomic.LoadInt32(&n)) // 1000
    fmt.Println(n)
}

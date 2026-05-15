package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	var cands int
	var types int

	fmt.Print("количество участников: ")
	fmt.Scan(&cands)
	fmt.Print("количество уникальных голосов: ")
	fmt.Scan(&types)

	pairs := make([][]int, cands)
	for i := range pairs {
		pairs[i] = make([]int, cands)
	}
	scores := make([]int, cands)

	for i := 0; i < types; i++ {
		var cnt int
		fmt.Print("количество голосов и столбец значений: ")
		fmt.Scan(&cnt)

		text, _ := reader.ReadString('\n')
		text = strings.TrimSpace(text)
		parts := strings.Fields(text)
		str := ""
		if len(parts) > 0 {
			str = parts[0]
		} else {
			str = text
		}

		ranks := make([]rune, cands)
		for j := 0; j < cands && j < len(str); j++ {
			ranks[cands-1-j] = rune(str[j])
		}

		for j := 0; j < cands; j++ {
			idx := ranks[j] - 'A'
			if idx >= 0 && int(idx) < cands {
				scores[idx] += j * cnt
			}
		}

		for a := 0; a < cands; a++ {
			for b := a + 1; b < cands; b++ {
				x := ranks[a] - 'A'
				y := ranks[b] - 'A'
				if x >= 0 && x < rune(cands) && y >= 0 && y < rune(cands) {
					pairs[y][x] += cnt
				}
			}
		}
	}

	best := 0
	for _, s := range scores {
		if s > best {
			best = s
		}
	}

	fmt.Print("По Борду: ")
	for i := 0; i < cands; i++ {
		if scores[i] == best {
			fmt.Printf("%c(%d) ", rune('A'+i), best)
		}
	}
	fmt.Println()

	fmt.Print("По Кондорсе: ")
	for i := 0; i < cands; i++ {
		ok := true
		for j := 0; j < cands; j++ {
			if i != j && pairs[i][j] <= pairs[j][i] {
				ok = false
				break
			}
		}
		if ok {
			fmt.Printf("%c\n", rune('A'+i))
			return
		}
	}
	fmt.Println("нет победителя")
}
